
CDash
=======
Test is executed using

```
ctest -D Experimental
```
Navigate to 
https://my.cdash.org/index.php?project=CMakeTutorial
and you see the result

Packaging
============
For binaries

``` shell
cpack
```

For source distribution

``` shell
cpack --config CPackSourceConfig.cmake
```

Library/LibraryUsage works also when installed

DeepLibrary (works on linux: build and install)
DeepLibraryLarge (works on linux: build)
