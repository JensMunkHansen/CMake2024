#!/bin/bash

rm ~/.cmake/packages/Foo* -Rf

bear -- cmake -B./Library/build -H./Library
cd Library/build
bear -- make
cd ../..

bear -- cmake -B./LibraryUsage/build -H./LibraryUsage
cd LibraryUsage/build
bear -- make
cd ../..

./LibraryUsage/build/FooUsage
