# Prerequisites: compile the module with `scons` command.
# Usage: ./tests/run.ps1 under the module directory.
Start-Process "${PSScriptRoot}/../godot/bin/godot.windows.tools.64.anl.exe" "--no-window -d -s tests/test_runner.gd"
