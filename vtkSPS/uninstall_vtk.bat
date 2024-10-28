@echo off
IF "%TSPKG_ROOT%"=="" (
	ECHO Environment variable TSPKG_ROOT is NOT set. Example "TSPKG_ROOT = C:\Artifactory"
) else (
  if exist "%PKG_ROOT%\ArtifactoryCache\WindowsShared\Release" (
    ECHO Uninstall VTK
    cmake --build "%PKG_ROOT%\ArtifactoryCache\WindowsShared\Release" --target uninstall
    cmake --build "%PKG_ROOT%\ArtifactoryCache\WindowsShared\Debug" --target uninstall
  )
)
