@echo off
echo "Simple installer for compiling VTK in C:/VTK without Qt and Python support"
SetLocal EnableDelayedExpansion

IF "%PKG_ROOT%"=="" (
   ECHO Environment variable PKG_ROOT is NOT set. Example "PKG_ROOT = C:\Artifactory"
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
  git -c advice.detachedHead=false clone --depth 1 https://gitlab.kitware.com/vtk/vtk.git VTK
)

if %myArg% == DEBUG (
  goto :Debug
)

set PATH="%PYTHON_INSTALL_DIR%";%PATH%

call "C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvarsall.bat" x64

:Release

if exist "%LOCALAPPDATA%\Programs\Python\Python312" (
   cmake -H%~dp0/VTK -B"%PKG_ROOT%/ArtifactoryCache/WindowsShared/Release" -G "Visual Studio 17 2022" -A "x64" -DCMAKE_CXX_MP_FLAG=ON -DVTK_WRAP_PYTHON=ON -DCMAKE_INSTALL_PREFIX="%PKG_ROOT%/ArtifactoryInstall/WindowsShared"
) else (
  cmake -H%~dp0/VTK -B"%PKG_ROOT%/ArtifactoryCache/WindowsShared/Release" -G "Visual Studio 17 2022" -A "x64" -DCMAKE_CXX_MP_FLAG=ON -DCMAKE_INSTALL_PREFIX="%PKG_ROOT%/ArtifactoryInstall/WindowsShared"
)

cmake --build "%PKG_ROOT%/ArtifactoryCache/WindowsShared/Release" --config Release --target install -j 8

goto :eof

:Debug

cmake -H%~dp0/VTK -B"%PKG_ROOT%/ArtifactoryCache/WindowsShared/Debug" -G "Visual Studio 17 2022" -A "x64" -DCMAKE_CXX_MP_FLAG=ON -DCMAKE_INSTALL_PREFIX="%PKG_ROOT%/ArtifactoryInstall/WindowsShared"
)
cmake --build "%PKG_ROOT%/ArtifactoryCache/WindowsShared/Debug" --config Debug --target install -j 8

goto :eof

:TOUPPERCASE
if not defined %~1 exit /b
for %%a in ("a=A" "b=B" "c=C" "d=D" "e=E" "f=F" "g=G" "h=H" "i=I" "j=J" "k=K" "l=L" "m=M" "n=N" "o=O" "p=P" "q=Q" "r=R" "s=S" "t=T" "u=U" "v=V" "w=W" "x=X" "y=Y" "z=Z" "ä=Ä" "ö=Ö" "ü=Ü") do (
call set %~1=%%%~1:%%~a%%
)

exit /b 0


