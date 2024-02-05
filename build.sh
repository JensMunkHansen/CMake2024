#!/bin/bash
rm -Rf ./Library/build
rm -Rf ./LibraryUsage/build

bear -- cmake -B./Library/build -H./Library
cd Library/build
bear -- make
cd ../..

bear -- cmake -B./LibraryUsage/build -H./LibraryUsage
cd LibraryUsage/build
# TODO: Figure out linking
bear -- make
cd ../..
