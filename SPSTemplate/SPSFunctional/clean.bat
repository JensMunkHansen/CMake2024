@echo off

pushd %~dp0

rmdir /S /Q %~dp0build
rmdir /S /Q %~dp0..\install
