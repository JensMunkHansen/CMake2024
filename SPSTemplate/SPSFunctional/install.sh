#!/bin/bash

if command -v bear &> /dev/null
then
    bear -- cmake -Bbuild -S. -DCMAKE_INSTALL_PREFIX=../install -DCMAKE_CXX_COMPILER=clang++
    bear -- cmake --build build --target install
else
    cmake -Bbuild -S. -DCMAKE_INSTALL_PREFIX=../install
    cmake --build build --target install
fi
