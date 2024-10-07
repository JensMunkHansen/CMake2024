@echo off

:: Path to the Python installer
set PYTHON_INSTALLER=python-3.12.7-amd64.exe

set PYTHON_INSTALL_DIR=%LOCALAPPDATA%\Programs\Python\Python312

:: Run the installer with the specified options
%PYTHON_INSTALLER% /uninstall 

rmdir /Q /S %PYTHON_INSTALL_DIR%
