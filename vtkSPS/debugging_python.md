# Debugging VTK with Python

For debugging your own code, when calling from python (on windows)

1. Install IPython with debug support
```batchfile
"%USERPROFILE%\Environments\Python312\Scripts\activate.bat"
python_d -m ensurepip
python_d -m pip install --upgrade pip
python_d -m pip install IPython
python_d -m pip install numpy
```

2. Create the file `%USERPROFILE%\.ipython\profile_default\startup\00-debug-setup.py` with the following content

```python
import os 
import sys

PKG_ROOT=os.environ.get("TSPKG_ROOT") 

is_debug_mode = sys.executable.endswith('_d.exe')
if is_debug_mode:
    VTK_BINARY_DIR=(f"{PKG_ROOT}/ArtifactoryInstall/WindowsShared/Debug/bin").replace("\\","/") 
    if os.path.exists(VTK_BINARY_DIR): 
        os.add_dll_directory(VTK_BINARY_DIR) 
    sys.path.insert(0, f"{PKG_ROOT}/ArtifactoryInstall/WindowsShared/Debug/lib/site-packages") 
else:
    VTK_BINARY_DIR=(f"{PKG_ROOT}/ArtifactoryInstall/WindowsShared/Release/bin").replace("\\","/") 
    if os.path.exists(VTK_BINARY_DIR): 
        os.add_dll_directory(VTK_BINARY_DIR) 
    sys.path.insert(0, f"{PKG_ROOT}/ArtifactoryInstall/WindowsShared/Release/lib/site-packages") 
```
