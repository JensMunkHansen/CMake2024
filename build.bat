@echo off

pushd %~dp0

del /F /Q /S %~dp0\LibraryUsage\build
del /F /Q /S %~dp0\Library\build
mkdir %~dp0\Library\build
mkdir %~dp0\LibraryUsage\build
cmake -H%~dp0/Library -B%~dp0/Library/build -G "Visual Studio 17 2022" -A "x64" -DBUILD_SHARED_LIBS=ON
cmake -H%~dp0/LibraryUsage -B%~dp0/LibraryUsage/build -G "Visual Studio 17 2022" -A "x64" -DBUILD_SHARED_LIBS=ON

cd %~dp0\Library\build
MSBuild.exe -maxCpuCount:20 Library.sln /p:Configuration=Release
REM 
cd %~dp0\LibraryUsage\build
MSBuild.exe -maxCpuCount:20 LibraryUsage.sln /p:Configuration=Release

cd %~dp0
