#!/bin/bash
rm -Rf ./Library/release
rm -Rf ./Library/debug

cd Library
bear -- cmake -B./release -H. -DCMAKE_BUILD_TYPE=Release
cd release
bear -- make
cd ..
bear -- cmake -B./debug -H. -DCMAKE_BUILD_TYPE=Debug
cd debug
bear -- make
cd ..
cpack --config MultiCPackConfig.cmake
