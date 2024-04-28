#!/bin/bash

cmake -Bbuild -S. -DCMAKE_PREFIX_PATH=$(pwd)/../install -DBUILD_SHARED_LIBS=ON
cmake --build build --verbose
