@echo off

SetLocal EnableDelayedExpansion

set "myArg=%~1"

call :TOUPPERCASE myArg

if "!myArg!"=="" (
  echo "Please select debug or release"
  goto :eof
)

pushd %~dp0

if %myArg% == DEBUG (
  goto :Debug
)

cmake --build build --config Release -DCMAKE_INSTALL_PREFIX=install
%~dp0\build\Release\bin\FooApp.exe

goto :eof

:Debug

cmake --build build --config Debug -DCMAKE_INSTALL_PREFIX=install
%~dp0\build\Debug\bin\FooAppd.exe

cd %~dp0

:TOUPPERCASE
if not defined %~1 exit /b
for %%a in ("a=A" "b=B" "c=C" "d=D" "e=E" "f=F" "g=G" "h=H" "i=I" "j=J" "k=K" "l=L" "m=M" "n=N" "o=O" "p=P" "q=Q" "r=R" "s=S" "t=T" "u=U" "v=V" "w=W" "x=X" "y=Y" "z=Z" "ä=Ä" "ö=Ö" "ü=Ü") do (
call set %~1=%%%~1:%%~a%%
)
