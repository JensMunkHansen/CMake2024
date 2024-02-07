@echo off

pushd %~dp0

REM We could show STDERR using 1>NUL
del /F /Q /S %~dp0\Library\build >NUL 2>&1
del /F /Q /S %~dp0\LibraryUsage\build >NUL 2>&1
del /F /Q /S %~dp0\Library\release >NUL 2>&1
del /F /Q /S %~dp0\Library\debug >NUL 2>&1
del /F /Q /S %~dp0\LibraryUsage\release >NUL 2>&1
del /F /Q /S %~dp0\LibraryUsage\debug >NUL 2>&1
del /F /Q /S %~dp0\install
