@echo off

:: Path to the Python installer
set PYTHON_INSTALLER=python-3.12.7-amd64.exe
set PYTHON_INSTALL_DIR="C:\Python312"

:: Run the installer with the specified options
%installer% 

REM Check if Python installer exists in the current directory
IF NOT EXIST %PYTHON_INSTALLER% (
    echo Python installer not found! Please download %PYTHON_INSTALLER% and place it in the same folder as this script.
    exit /b 1
)

echo Installing Python 3.12.7...

call %PYTHON_INSTALLER% /quiet InstallAllUsers=1 PrependPath=1 Include_dev=1 Include_pip=1 Include_debug=1 TargetDir="%PYTHON_INSTALL_DIR%" >nul 2>&1

IF ERRORLEVEL 1 (
    echo Python installation failed.
    exit /b 1
)

REM Verify Python installation
"%PYTHON_INSTALL_DIR%\python.exe" --version
IF ERRORLEVEL 1 (
    echo Python was not installed correctly.
    exit /b 1
)

REM Upgrade pip and install virtualenv
echo Installing virtualenv...
"%PYTHON_INSTALL_DIR%\python.exe" -m pip install --upgrade pip
"%PYTHON_INSTALL_DIR%\python.exe" -m pip install virtualenv

IF ERRORLEVEL 1 (
    echo Failed to install virtualenv.
    exit /b 1
)

echo Python 3.12 and virtualenv installed successfully in %PYTHON_INSTALL_DIR%.
exit /b 0
