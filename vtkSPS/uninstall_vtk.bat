@echo off
IF "%PKG_ROOT%"=="" (
	ECHO Environment variable PKG_ROOT is NOT set. Example "PKG_ROOT = C:\Artifactory"
) else (
        ECHO Uninstall VTK
	cmake --build "%PKG_ROOT%\ArtifactoryCache\WindowsShared\Release" --target uninstall
	cmake --build "%PKG_ROOT%\ArtifactoryCache\WindowsShared\Debug" --target uninstall
)
