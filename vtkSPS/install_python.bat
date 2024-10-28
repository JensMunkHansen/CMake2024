@echo off

pushd %~dp0

:: Get the user's home directory
set HOME_DIR=%USERPROFILE%

:: Path to the Python installer
set PYTHON_INSTALLER=python-3.12.7-amd64.exe
REM set PYTHON_INSTALL_DIR="C:\Python312"
set PYTHON_INSTALL_DIR=%LOCALAPPDATA%\Programs\Python\Python312

set PYTHON_DOWNLOAD_URL=https://www.python.org/ftp/python/3.12.7/python-3.12.7-amd64.exe

set PYTHON_VENV_PATH=%HOME_DIR%\Environments
set PYTHON_VENV_NAME=Python312

set SITECUSTOMIZE_FILE=%PYTHON_VENV_PATH%\%PYTHON_VENV_NAME%\Lib\site-packages\sitecustomize.py

IF NOT EXIST "%PYTHON_VENV_PATH%" (
    mkdir "%PYTHON_VENV_PATH%"
)

:: Check if Python installer exists in the current directory
IF NOT EXIST %PYTHON_INSTALLER% (
    echo Python installer not found! Downloading %PYTHON_INSTALLER%...
    powershell -Command "(New-Object Net.WebClient).DownloadFile('%PYTHON_DOWNLOAD_URL%', '%CD%\%PYTHON_INSTALLER%')"
    IF ERRORLEVEL 1 (
        echo Failed to download Python installer.
        exit /b 1
    )
)

REM Check if Python installer exists in the current directory
IF NOT EXIST %PYTHON_INSTALLER% (
    echo Python installer not found! Please download %PYTHON_INSTALLER% and place it in the same folder as this script.
    exit /b 1
)

echo Installing Python 3.12 at %PYTHON_INSTALL_DIR%

:: Create the target directory if it doesn't exist
IF NOT EXIST "%PYTHON_INSTALL_DIR%" (
   mkdir "%PYTHON_INSTALL_DIR%"
)

REM ISSUE WITH RIGHTS
REM %PYTHON_INSTALLER% /quiet InstallAllUsers=1 PrependPath=1 Include_dev=1 Include_pip=1 Include_debug=1 
call %PYTHON_INSTALLER% /passive PrependPath=1 Include_dev=1 Include_pip=1 Include_debug=1 TargetDir="%PYTHON_INSTALL_DIR%"

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

:: Check if the virtual environment already exists in the user's home directory
if exist "%PYTHON_VENV_PATH%\%PYTHON_VENV_NAME%\Scripts\activate" (
    echo Virtual environment already exists in %PYTHON_VENV_PATH%.
) else (
    echo Creating virtual environment using virtualenv in %PYTHON_VENV_PATH%...

    :: Create the directory for the environment
    mkdir "%PYTHON_VENV_PATH%"

    cd /D "%PYTHON_VENV_PATH%"
    :: Create the virtual environment in the user's home directory
    "%PYTHON_INSTALL_DIR%\python.exe" -m virtualenv "%PYTHON_VENV_NAME%"

    IF ERRORLEVEL 1 (
        echo Failed to create virtual environment.
        exit /b 1
    )
    cd /D "%~dp0"
)

:: Activate the virtual environment
call "%PYTHON_VENV_PATH%\%PYTHON_VENV_NAME%\Scripts\activate"

:: For debugging. Unfortunately on Windows, binary APIs are not compatible
:: python_d -m ensurepip
:: python_d -m pip install --upgrade pip
:: python_d -m pip install IPython
:: python_d -m pip install numpy


:: Upgrade pip inside the virtual environment
echo Upgrading pip inside the virtual environment...
python -m pip install --upgrade pip

:: Check if IPython is installed in the virtual environment
python -m ipython --version >nul 2>&1
IF ERRORLEVEL 1 (
    echo Installing IPython in the virtual environment...
    pip install ipython
) else (
    echo IPython is already installed.
)

IF ERRORLEVEL 1 (
    echo Failed to install IPython.
    exit /b 1
)

python -m numpy --version >nul 2>&1
IF ERRORLEVEL 1 (
    echo Installing NumPy in the virtual environment...
    pip install numpy
) else (
    echo NumPy is already installed.
)

IF ERRORLEVEL 1 (
    echo Failed to install NumPy.
    exit /b 1
)

:: Activate the virtual environment
call "%PYTHON_VENV_PATH%\%PYTHON_VENV_NAME%\Scripts\deactivate"

echo Python, virtual environment, and IPython installed successfully in %PYTHON_VENV_PATH%\%PYTHON_VENV_NAME%.

:: Create the sitecustomize.py if it does not exist
if not exist "%SITECUSTOMIZE_FILE%" (
    echo Creating sitecustomize.py at %SITECUSTOMIZE_FILE%
    echo. > "%SITECUSTOMIZE_FILE%"
)

:: Add to the sitecustomize.py file
:: - the approach also works in debug, simply replace Release -> Debug and run python_d.exe.
echo import os >> "%SITECUSTOMIZE_FILE%"
echo import sys >> "%SITECUSTOMIZE_FILE%"
echo PKG_ROOT=os.environ.get("TSPKG_ROOT") >> "%SITECUSTOMIZE_FILE%"
echo VTK_BINARY_DIR=(f"{PKG_ROOT}/ArtifactoryInstall/WindowsShared/Release/bin").replace("\\","/") >> "%SITECUSTOMIZE_FILE%"
echo if os.path.exists(VTK_BINARY_DIR): >> "%SITECUSTOMIZE_FILE%"
echo     os.add_dll_directory(VTK_BINARY_DIR) >> "%SITECUSTOMIZE_FILE%"
echo sys.path.insert(0, f"{PKG_ROOT}/ArtifactoryInstall/WindowsShared/Release/lib/site-packages") >> "%SITECUSTOMIZE_FILE%"

exit /b 0
