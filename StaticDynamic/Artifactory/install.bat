@echo off

pushd %~dp0

cmake -Bbuild -S. -DCMAKE_INSTALL_PREFIX=%~dp0../install 
cmake --build build --config Release
