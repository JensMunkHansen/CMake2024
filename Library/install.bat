@echo off

pushd %~dp0

cmake -S. -Bbuild -DCMAKE_INSTALL_PREFIX=%~dp0install
cmake --build build --config Release --target install
cmake --build build --config Debug --target install
