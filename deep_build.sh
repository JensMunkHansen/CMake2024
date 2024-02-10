#!/bin/bash

bear -- cmake -B./DeepLibrary/build -H./DeepLibrary
cd DeepLibrary/build
bear -- make
cd ../..

