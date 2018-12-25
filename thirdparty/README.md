# Third party libraries

## Accidental Noise Library

- Upstream: https://github.com/JTippetts/accidental-noise-library
- Version: git (f51f6b3087bffc91362fc9e7e6f5899fe6af43e3, Nov 14, 2017)
- License: zlib

### Changes:
  - removed source unrelated to noise generation (Bindings, Framework, Thirdparty etc);
  - converted header-only library back to source/header (adapted to Scons build system);
  - separated camelCase and snake_case in expression builder using static string tokens;
  - allow to retrieve instruction index as integer;
  - add method to clear the kernel;
  - reorder noise constants from smallest to largest when initializing;
  - make the library to be more exception-safe for Godot Engine (required for some platforms);
  - some compiler warning fixes.

An actual diff for these changes can be found in [thirdparty/anl/changes.diff](/thirdparty/anl/changes.diff).