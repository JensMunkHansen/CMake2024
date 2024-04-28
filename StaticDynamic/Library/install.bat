@echo off

pushd %~dp0

cmake -Bbuild -S. -DCMAKE_PREFIX_PATH=$(pwd)/../install -DCMAKE_INSTALL_PREFIX=$(pwd)/../install -DBUILD_SHARED_LIBS=OFF
cmake --build build --config Release --target install
