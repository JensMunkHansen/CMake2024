@echo off

:: Path to the Python installer
set installer=python-3.12.7-amd64.exe

:: Run the installer with the specified options
%installer% /passive InstallAllUsers=1 PrependPath=1 Include_dev=1 Include_pip=1
