#!/bin/bash

# Install Library and LibraryUsage

dir=$PWD

bear -- cmake -B./build -H. -DCMAKE_BUILD_TYPE=Release
cd build
bear -- make
cmake --install . --prefix="$dir/install"
cd ..

# bear -- cmake -B./LibraryUsage/build -H./LibraryUsage -DCMAKE_BUILD_TYPE=Release
# cd LibraryUsage/build
# bear -- make
# cmake --install . --prefix="$dir/install"
# cd ../..
