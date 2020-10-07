#!/usr/bin/env python
#
# Upstream: https://github.com/goostengine/goost
# Version: 1.4 (Godot Engine 3.2.2+)
# License: MIT
#
# `SConstruct` which allows to build any C++ module just like Godot Engine.
#
# Usage: 
# 1. Copy this `SConstruct` to your module's source root.
# 2. Compile the module with the same build command, for instance:
#
#   scons target=release_debug tools=yes bits=64
#
# This will clone the Godot repository directly into this module and compile the
# engine with the module automatically. `GODOT_SOURCE_PATH` environment variable
# can be used instead pointing to the existing Godot source.
#
# Run `scons --help` for other build options to configure the default behavior.
#
import os
import sys
import pickle
import subprocess

import config

env = Environment()

# Module name is determined from directory name.
module_name = os.path.basename(Dir(".").abspath)
print("Configuring %s module ..." % module_name.capitalize())

# Environment variables (can override default build options).
godot_version = os.getenv("GODOT_VERSION", "3.2") # A branch, commit, tag etc.

# Find a path to Godot source to build with this module.
godot_dir = Dir("godot")
godot_search_dirs = [
    # Try environment variable pointing to the Godot source, should be first.
    Dir(os.getenv("GODOT_SOURCE_PATH")),
    # Search for the Godot source in the parent directory.
    Dir("../godot"),
    # Use the Godot source within the module, should be last.
    # If not found, the source is fetched from the remote URL.
    Dir("godot"),
]
for path in godot_search_dirs:
    if not path.exists():
        continue
    godot_dir = path
    break

godot_url = os.getenv("GODOT_REPO_URL", "https://github.com/godotengine/godot")

# Setup SCons command-line options.
opts = Variables("custom.py", ARGUMENTS)
opts.Add("godot_version", "Godot Engine version (branch, tags, commit hashes)", godot_version)
opts.Add(BoolVariable("godot_sync", "Synchronize Godot Engine version from remote URL before building", False))
opts.Add(BoolVariable("godot_modules_enabled", "Build all Godot builtin modules", True))
opts.Add(BoolVariable("parent_modules_enabled", "Build all modules which may reside in the same parent directory", False))

# Generate help text.
Help("\n\n%s top-level build options:\n" % module_name.capitalize(), append=True)

opts.Update(env)
Help(opts.GenerateHelpText(env), append=True)

help_msg = """
{module} environment variables:

GODOT_VERSION: such as 3.2, 3.2.2-stable, master, commit hash etc.
    Current: {version}
GODOT_SOURCE_PATH: a directory path to the existing Godot source code.
    Current: {path}
GODOT_REPO_URL: URL from which the engine source code is fetched.
    Current: {url}
""".format(
    module = module_name.capitalize(),
    version = env["godot_version"],
    path = godot_dir,
    url = godot_url,
)
Help(help_msg, append=True)

# A method which allows us to run `git`, `scons`, and other commands.
def run(args, dir="."):
    if sys.platform.startswith("win32"):
        return subprocess.run(args, check=True, shell=True, cwd=dir).returncode
    else:
        return subprocess.run(args, check=True, cwd=dir).returncode

def godot_check_if_branch(ref):
    try:
        return run(["git", "show-ref", "--verify", "--quiet", 
                "refs/heads/%s" % ref], godot_dir.abspath) == 0
    except:
        return False

def godot_verify_min_version():
    sys.path.insert(0, godot_dir.abspath)
    import version
    compatible = (version.major, version.minor, version.patch) >= (3, 2, 2)
    if not compatible:
        print("Cannot compile %s without `custom_modules` support." % module_name.capitalize())
        print("The minimum required Godot version is 3.2.2 (current: %s)" % env["godot_version"])
    sys.path.remove(godot_dir.abspath)
    sys.modules.pop("version")
    return compatible

if godot_dir == Dir("godot"):
    if not godot_dir.exists():
        # Checkout Godot repository directly into this module.
        run(["git", "clone", godot_url])
        run(["git", "checkout", env["godot_version"], "--quiet"], godot_dir.abspath)
        if not godot_verify_min_version():
            Exit(255)
    elif env["godot_sync"]:
        # Reset the engine, checkout, and update with remote.
        print("Synchronizing Godot version ...")
        run(["git", "reset", "--hard", "HEAD", "--quiet"], godot_dir.abspath)
        run(["git", "checkout", env["godot_version"], "--quiet"], godot_dir.abspath)
        if not godot_verify_min_version():
            Exit(255)
        if godot_check_if_branch(env["godot_version"]):
            run(["git", "pull"], godot_dir.abspath)

# Setup base SCons arguments to the Godot build command.
# Copy all from the command line, except for options in this SConstruct.
build_args = ["scons"]
for arg in ARGLIST:
    if arg[0] in opts.keys():
        continue
    opt = "%s=%s" % (arg[0], arg[1])
    build_args.append(opt)

# Link this module as a custom module.
modules = []
modules.append(Dir("..").abspath)

# This module may provide other nested modules, just like this one.
try:
    modules_path = config.get_modules_path()
    modules.append(os.path.join(Dir(".").abspath, modules_path))
except AttributeError:
    pass

# We use the `custom_modules` build option to build this module, 
# but allow to specify additional modules to build along this one.
if "custom_modules" in ARGUMENTS:
    custom_modules = ARGUMENTS.get("custom_modules").split(",")
    modules.extend(custom_modules)

build_args.append("custom_modules=%s" % ",".join(modules))

# We cannot link to a single module using the `custom_modules` build option,
# so this may compile other modules which reside in the same location as this 
# module. To prevent this, we disable all modules there, excluding this one.
if not env["parent_modules_enabled"]:
    DIRNAMES = 1
    dirs = next(os.walk(Dir("..").abspath))[DIRNAMES]
    parent_modules = []

    for d in dirs:
        if d == module_name:
            continue
        if os.path.exists(os.path.join(Dir("..").abspath, d, "SCsub")):
            parent_modules.append(d)

    for m in parent_modules:
        build_args.append("module_%s_enabled=no" % m)

# Optionally disable Godot's built-in modules which are non-essential in order
# to test out this module in the engine. For more details, refer to Godot docs:
# https://docs.godotengine.org/en/latest/development/compiling/optimizing_for_size.html
if not env["godot_modules_enabled"]:
    if "profile" in ARGUMENTS:
        build_args.append("profile=%s" % ARGUMENTS.get("profile"))
    else:
        try:
            import modules_disabled
            build_args.append("profile=%s" % 
                    os.path.join(Dir(".").abspath, "modules_disabled.py"))
        except ImportError:
            pass

# Append the default `extra_suffix` to distinguish between other builds.
# Extend the suffix if `extra_suffix` is specified via the command line.
module_suffix = module_name
if "extra_suffix" in ARGUMENTS:
    module_suffix += "." + ARGUMENTS.get("extra_suffix")
build_args.append("extra_suffix=%s" % module_suffix)

# Set custom build name from the module name.
# Extend the build name if it's already overridden.
build_name = module_name.capitalize()
if os.getenv("BUILD_NAME"):
    build_name += "." + os.getenv("BUILD_NAME")
os.environ["BUILD_NAME"] = build_name

# Avoid issues when building with different versions of Python.
SConsignFile(".sconsign{0}.dblite".format(pickle.HIGHEST_PROTOCOL))

# Enable cache if required, this is reused by Godot and CI.
scons_cache_path = os.environ.get("SCONS_CACHE")
if scons_cache_path != None:
    CacheDir(scons_cache_path)
    print("SCons cache enabled... (path: '" + scons_cache_path + "')")

# Some SCons-specific options may not trigger an actual build.
skip_build = False

# Pass commonly used SCons options to the Godot build.
scons_options = ["help", "clean"]
for opt in scons_options:
    if not GetOption(opt):
        continue
    skip_build |= opt in ["help", "clean"]
    build_args.append("--%s" % opt)

# The following can be overridden using the `SCONSFLAGS` environment variable,
# but for convenience, we just copy those options here.
if GetOption("num_jobs") > 1:
    build_args.append("--jobs=%s" % GetOption("num_jobs"))

if not skip_build:
    print("Building Godot with %s ..." % module_name.capitalize())

# Run SCons to build Godot with the module, check the build configuration etc.
run(build_args, godot_dir.abspath)
