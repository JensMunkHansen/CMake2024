@echo off
echo "Simple installer for installing VTK with and without Python support"
SetLocal EnableDelayedExpansion

IF "%TSPKG_ROOT%"=="" (
   ECHO Environment variable TSPKG_ROOT is NOT set. Example "TSPKG_ROOT = C:\Artifactory"
   goto :eof
)

if "%~1"=="" (
   echo ERROR: This script requires exactly 1 argument.
   echo Usage: install_vtk.bat [debug/release]
   goto :eof
)

set PYTHON_INSTALL_DIR=%LOCALAPPDATA%\Programs\Python\Python312
 
set myArg=%1

call :TOUPPERCASE myArg
echo %myArg%

pushd %~dp0

if exist "%~dp0\VTK" (
  echo "Folder exists"
) else (
  git -c advice.detachedHead=false clone --branch v9.3.20241014 --depth 1 git@github.com:3ShapeInternal/VTK.git VTK
)

call "C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvarsall.bat" x64

if %myArg% == DEBUG (
  goto :Debug
)

set PATH="%PYTHON_INSTALL_DIR%";%PATH%

:Release

set INSTALL_PREFIX=%TSPKG_ROOT%\ArtifactoryInstall\WindowsShared\Release

if exist "%PYTHON_INSTALL_DIR%" (
  cmake -H"%~dp0VTK" -B"%TSPKG_ROOT%\ArtifactoryCache\WindowsShared\Release" -G "Visual Studio 17 2022" -A "x64" -DCMAKE_CXX_MP_FLAG=ON -DVTK_WRAP_PYTHON=ON -DCMAKE_INSTALL_PREFIX="%INSTALL_PREFIX%" -DBUILD_SHARED_LIBS=ON  -DVTK_MODULE_ENABLE_VTK_FiltersFlowPaths:STRING=NO
) else (
  cmake -H"%~dp0VTK" -B"%TSPKG_ROOT%\ArtifactoryCache\WindowsShared\Release" -G "Visual Studio 17 2022" -A "x64" -DCMAKE_CXX_MP_FLAG=ON -DCMAKE_INSTALL_PREFIX="%INSTALL_PREFIX%" -DBUILD_SHARED_LIBS=ON -DVTK_MODULE_ENABLE_VTK_FiltersFlowPaths:STRING=NO
)

cmake --build "%TSPKG_ROOT%\ArtifactoryCache\WindowsShared\Release" --config Release --target install -j 8

goto :eof

:Debug

set INSTALL_PREFIX=%TSPKG_ROOT%\ArtifactoryInstall\WindowsShared\Debug

REM: We do not support python binding in debug mode, TODO: Check if disabling VTK_VERSIONED_INSTALL works on Windows

cmake -H"%~dp0VTK" -B"%TSPKG_ROOT%\ArtifactoryCache\WindowsShared\Debug" -G "Visual Studio 17 2022" -A "x64" -DCMAKE_CXX_MP_FLAG=ON -DCMAKE_INSTALL_PREFIX="%INSTALL_PREFIX%" -DBUILD_SHARED_LIBS=ON -DVTK_MODULE_ENABLE_VTK_FiltersFlowPaths:STRING=NO -DCMAKE_DEBUG_POSTFIX=d

cmake --build "%TSPKG_ROOT%\ArtifactoryCache\WindowsShared\Debug" --config Debug --target install -j 8

goto :eof

:TOUPPERCASE
if not defined %~1 exit /b
for %%a in ("a=A" "b=B" "c=C" "d=D" "e=E" "f=F" "g=G" "h=H" "i=I" "j=J" "k=K" "l=L" "m=M" "n=N" "o=O" "p=P" "q=Q" "r=R" "s=S" "t=T" "u=U" "v=V" "w=W" "x=X" "y=Y" "z=Z" "ä=Ä" "ö=Ö" "ü=Ü") do (
call set %~1=%%%~1:%%~a%%
)

exit /b 0


