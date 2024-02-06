
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

