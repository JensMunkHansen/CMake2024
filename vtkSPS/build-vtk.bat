@echo off
echo "Simple installer for compiling VTK in C:/VTK without Qt and Python support"
SetLocal EnableDelayedExpansion

set myArg=%1

call :TOUPPERCASE myArg
echo %myArg%

pushd %~dp0
cd /D c:
mkdir VTK
cd /D C:/VTK

if exist "C:\VTK\VTK\" (
  echo "Folder exists"
) else (
  git -c advice.detachedHead=false clone --depth 1 https://gitlab.kitware.com/vtk/vtk.git VTK
)

if %myArg% == DEBUG (
  goto :Debug
)

:Release
mkdir build_Release
cmake -HC:/VTK/VTK -BC:/VTK/build_Release -G "Visual Studio 17 2022" -A "x64" -DCMAKE_CXX_MP_FLAG=ON -DVTK_WRAP_PYTHON=ON -DVTK_WINDOWS_PYTHON_DEBUGGABLE=ON

set PATH="C:/Program Files/Python312";%PATH%

call "C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvarsall.bat" x64
cd build_Release

cmake --build . --config Release --target install
goto :eof

:Debug
mkdir build_Debug

cmake -HC:/VTK/VTK -BC:/VTK/build_Debug -G "Visual Studio 17 2022" -A "x64" -DCMAKE_CXX_MP_FLAG=ON -DVTK_WRAP_PYTHON=ON -DVTK_WINDOWS_PYTHON_DEBUGGABLE=ON

call "C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvarsall.bat" x64

cd build_Debug

cmake --build . --config Debug --target install

goto :eof

:TOUPPERCASE
if not defined %~1 exit /b
for %%a in ("a=A" "b=B" "c=C" "d=D" "e=E" "f=F" "g=G" "h=H" "i=I" "j=J" "k=K" "l=L" "m=M" "n=N" "o=O" "p=P" "q=Q" "r=R" "s=S" "t=T" "u=U" "v=V" "w=W" "x=X" "y=Y" "z=Z" "ä=Ä" "ö=Ö" "ü=Ü") do (
call set %~1=%%%~1:%%~a%%
)

goto :eof
