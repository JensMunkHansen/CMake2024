@echo off

pushd %~dp0

cmake -B %~dp0build  -DCMAKE_PREFIX_PATH=%~dp0../Library/install
