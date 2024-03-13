@echo off

pushd %~dp0

REM cmake -B build/debug -DCMAKE_INSTALL_PREFIX=install
cmake -B build -H%~dp0 
