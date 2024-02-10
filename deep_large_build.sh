#!/bin/bash

bear -- cmake -B./DeepLibraryLarge/build -H./DeepLibraryLarge
cd DeepLibraryLarge/build
bear -- make
cd ../..

bear -- cmake -B./DeepLibraryLargeUsage/build -H./DeepLibraryLargeUsage
cd DeepLibraryLargeUsage/build
bear -- make
cd ../..

