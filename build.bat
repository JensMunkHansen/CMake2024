@echo off

REM TODO: Ensure GTEST is build with CMAKE_DEBUG_POSTFIX=d and BUILD_SHARED_LIBS=ON

SetLocal EnableDelayedExpansion

set "myArg=%~1"

call :TOUPPERCASE myArg
echo %myArg%

if "!myArg!"=="" (
  echo "Please select debug or release"
  goto :eof
)

pushd %~dp0

call "C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvarsall.bat" x64

set "GTEST_DIR=C:\Program Files (x86)\googletest-distribution"
set "GTEST_BIN_DIR=%GTEST_DIR%\bin"
set "GTEST_CMAKE_DIR=%GTEST_DIR%\lib\cmake"

set PATH=%PATH%;%GTEST_BIN_DIR%

if %myArg% == DEBUG (
  goto :Debug
)

cmake -H%~dp0/Library -B%~dp0/Library/build -G "Visual Studio 17 2022" -A "x64" -DBUILD_SHARED_LIBS=ON -DCMAKE_PREFIX_PATH="%GTEST_CMAKE_DIR%"
cmake -H%~dp0/LibraryUsage -B%~dp0/LibraryUsage/build -G "Visual Studio 17 2022" -A "x64" -DBUILD_SHARED_LIBS=ON

cd %~dp0\Library\build
MSBuild.exe -maxCpuCount:20 Library.sln /p:Configuration=Release
cd %~dp0\LibraryUsage\build
MSBuild.exe -maxCpuCount:20 LibraryUsage.sln /p:Configuration=Release

goto :eof

:Debug

cmake -H%~dp0/Library -B%~dp0/Library/build -G "Visual Studio 17 2022" -A "x64" -DBUILD_SHARED_LIBS=ON -DCMAKE_PREFIX_PATH="%GTEST_CMAKE_DIR%"
cmake -H%~dp0/LibraryUsage -B%~dp0/LibraryUsage/build -G "Visual Studio 17 2022" -A "x64" -DBUILD_SHARED_LIBS=ON

cd %~dp0\Library\build
MSBuild.exe -maxCpuCount:20 Library.sln /p:Configuration=Debug
cd %~dp0\LibraryUsage\build
MSBuild.exe -maxCpuCount:20 LibraryUsage.sln /p:Configuration=Debug


cd %~dp0

:TOUPPERCASE
if not defined %~1 exit /b
for %%a in ("a=A" "b=B" "c=C" "d=D" "e=E" "f=F" "g=G" "h=H" "i=I" "j=J" "k=K" "l=L" "m=M" "n=N" "o=O" "p=P" "q=Q" "r=R" "s=S" "t=T" "u=U" "v=V" "w=W" "x=X" "y=Y" "z=Z" "ä=Ä" "ö=Ö" "ü=Ü") do (
call set %~1=%%%~1:%%~a%%
)
