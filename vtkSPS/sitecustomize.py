import os
import sys

PKG_ROOT = os.environ.get("PKG_ROOT")
os.add_dll_directory(f"{PKG_ROOT}/ArtifactoryInstall/WindowsShared/VTK/bin")
sys.path.insert(0, f"{PKG_ROOT}/ArtifactoryInstall/WindowsShared/VTK/lib/site-packages")


