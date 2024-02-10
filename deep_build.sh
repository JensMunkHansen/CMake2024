#!/bin/bash

bear -- cmake -B./DeepLibrary/build -H./DeepLibrary
cd DeepLibrary/build
bear -- make
cd ../..

bear -- cmake -B./DeepLibraryUsage/build -H./DeepUsageLibrary
cd DeepLibraryUsage/build
bear -- make
cd ../..

