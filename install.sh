#!/bin/bash

# Install Library and LibraryUsage

dir=$PWD

bear -- cmake -B./Library/build -H./Library -DCMAKE_BUILD_TYPE=Release
cd Library/build
bear -- make
cmake --install . --prefix="$dir/install"
cd ../..

bear -- cmake -B./LibraryUsage/build -H./LibraryUsage -DCMAKE_BUILD_TYPE=Release
cd LibraryUsage/build
bear -- make
cmake --install . --prefix="$dir/install"
cd ../..
