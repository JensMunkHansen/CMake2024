@echo off

pushd %~dp0

cmake -Bbuild -S. -DCMAKE_INSTALL_PREFIX=%~dp0install 
cmake --build build --config Release
