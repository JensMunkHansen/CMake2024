@echo off

pushd %~dp0

cmake -Bbuild -S. -DCMAKE_PREFIX_PATH=%~dp0/../install
cmake --build build --config Release
