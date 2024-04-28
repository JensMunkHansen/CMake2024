@echo off

pushd %~dp0

cmake -Bbuild -S. -DCMAKE_PREFIX_PATH=%~dp0../install -DBUILD_SHARED_LIBS=ON
cmake --build build --config Release
