@echo off
echo "Simple installer for compiling VTK in C:/VTK without Qt and Python support"
SetLocal EnableDelayedExpansion

@echo off
IF "%PKG_ROOT%"=="" (
   ECHO Environment variable PKG_ROOT is NOT set. Example "PKG_ROOT = C:\Artifactory"
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
  git -c advice.detachedHead=false clone --depth 1 https://gitlab.kitware.com/vtk/vtk.git VTK
)

REM git@github.com:3ShapeInternal/VTK.git

if %myArg% == DEBUG (
  goto :Debug
)

set PATH="%PYTHON_INSTALL_DIR%";%PATH%

call "C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvarsall.bat" x64

:Release

if exist "PYTHON_INSTALL_DIR=%LOCALAPPDATA%\Programs\Python\Python312" (
   cmake -H%~dp0/VTK -B%"%ROOT%/ArtifactoryCache/WindowsShared/Release" -G "Visual Studio 17 2022" -A "x64" -DCMAKE_CXX_MP_FLAG=ON -DVTK_WRAP_PYTHON=ON -DCMAKE_INSTALL_PREFIX="%ROOT%/ArtifactoryInstall/WindowsShared"
) else (
  cmake -H%~dp0/VTK -B%"%ROOT%/ArtifactoryCache/WindowsShared/Release" -G "Visual Studio 17 2022" -A "x64" -DCMAKE_CXX_MP_FLAG=ON -DCMAKE_INSTALL_PREFIX="%ROOT%/ArtifactoryInstall/WindowsShared"
)

cmake --build %"%ROOT%/ArtifactoryCache/WindowsShared/Release" --config Release --target install -j 8

:Debug

cmake -H%~dp0/VTK -B%"%ROOT%/ArtifactoryCache/WindowsShared/Debug" -G "Visual Studio 17 2022" -A "x64" -DCMAKE_CXX_MP_FLAG=ON -DCMAKE_INSTALL_PREFIX="%ROOT%/ArtifactoryInstall/WindowsShared"
)
cmake --build %"%ROOT%/ArtifactoryCache/WindowsShared/Release" --config Release --target install -j 8

goto :eof
