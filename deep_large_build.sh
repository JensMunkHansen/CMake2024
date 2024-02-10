#!/bin/bash

bear -- cmake -B./DeepLibraryLarge/build -H./DeepLibraryLarge
cd DeepLibraryLarge/build
bear -- make
cd ../..

