#!/bin/sh
cmake --preset linux-release
cmake --build --preset release-build-linux
ctest --preset core-test-linux 
