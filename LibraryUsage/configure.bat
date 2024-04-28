@echo off

pushd %~dp0

cmake -B %~dp0build -G Ninja -DCMAKE_PREFIX_PATH=$(pwd)/../Library/install
