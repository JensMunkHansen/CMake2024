@echo off

pushd %~dp0

cmake --build build --config Release
cmake --build build --config Debug
