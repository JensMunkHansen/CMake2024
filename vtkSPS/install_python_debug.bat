@echo off
REM Batch script to download, build, and install Python 3.12.0 with debug info.

REM Set Python version and directories
set PYTHON_VERSION=v3.12.0
set SOURCE_DIR=%cd%\python_src
set BUILD_DIR=%SOURCE_DIR%\PCbuild\amd64
set PYTHON_INSTALL_DIR=C:\Python312debug

REM Check if Git is installed
git --version >nul 2>&1
IF ERRORLEVEL 1 (
    echo Git is not installed. Please install Git and try again.
    exit /b 1
)

REM Manually set the Visual Studio environment (adjust path if needed)
echo Setting up Visual Studio 2022 environment...

REM Replace this with the correct path to your Visual Studio's vcvarsall.bat for VS2022
call "C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvarsall.bat" x64

IF ERRORLEVEL 1 (
    echo Failed to set up Visual Studio environment.
    exit /b 1
)

REM Check if the source code has already been cloned
IF NOT EXIST "%SOURCE_DIR%" (
    echo Cloning Python source code repository...
    git clone --branch %PYTHON_VERSION% https://github.com/python/cpython %SOURCE_DIR%
    
    IF ERRORLEVEL 1 (
        echo Failed to clone Python repository.
        exit /b 1
    )
) ELSE (
    echo Python source code is already downloaded. Pulling latest updates...
    cd %SOURCE_DIR%
    git fetch --all
    git checkout %PYTHON_VERSION%
)

REM Change to the source directory
cd %SOURCE_DIR%

echo Building Python with debug information...
PCbuild\build.bat -d

IF ERRORLEVEL 1 (
    echo Python build failed.
    exit /b 1
)

REM Verify if python_d.exe was built successfully
IF NOT EXIST "%BUILD_DIR%\python_d.exe" (
    echo Debug build of Python failed. Please check your setup.
    exit /b 1
)

echo Installing Python to %PYTHON_INSTALL_DIR%...
xcopy "%BUILD_DIR%" "%PYTHON_INSTALL_DIR%" /s /e /y

IF ERRORLEVEL 1 (
    echo Failed to copy files to the installation directory.
    exit /b 1
)

REM Adding Python to system PATH
echo Adding Python to system PATH...
setx /M PATH "%PYTHON_INSTALL_DIR%;%PYTHON_INSTALL_DIR%\Scripts;%PATH%"

IF ERRORLEVEL 1 (
    echo Failed to add Python to system PATH. Please do it manually.
    exit /b 1
)

echo Python 3.12.0 with debug symbols has been successfully installed in %PYTHON_INSTALL_DIR%.
pause
exit /b 0




