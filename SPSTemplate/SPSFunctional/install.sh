#!/bin/bash

if command -v bear &> /dev/null
then
    bear -- cmake -Bbuild -S. -DCMAKE_INSTALL_PREFIX=../install
    bear -- cmake --build build --target install
else
    cmake -Bbuild -S. -DCMAKE_INSTALL_PREFIX=../install
    cmake --build build --target install
fi
