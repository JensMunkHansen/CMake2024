@echo off

pushd %~dp0

REM cmake -B build/debug
cmake -B build -H%~dp0 -DCMAKE_INSTALL_PREFIX=install
