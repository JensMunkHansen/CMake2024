#!/bin/bash

cmake --build build/debug --target install
cmake --build build/release --target install

./build/debug/bin/FooAppd
./build/release/bin/FooApp

# TODO: Check this out
# cmake -B build -S . -G "Visual Studio 16 2019"
# cmake --build build --config Debug
# cmake --install build --config Debug --prefix install
# 
# cmake --build build --config Release
# cmake --install build --config Release --prefix install
