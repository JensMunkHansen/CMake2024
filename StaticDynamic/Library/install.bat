@echo off

pushd %~dp0

cmake -Bbuild -S. -DCMAKE_PREFIX_PATH=%~dp0../install -DCMAKE_INSTALL_PREFIX=%~dp0../install -DBUILD_SHARED_LIBS=OFF
cmake --build build --config Release --target install
