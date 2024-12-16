#!/bin/bash

if [ -f /etc/os-release ]; then
    . /etc/os-release
    OS=$ID
else
    echo "Cannot determine the OS."
    exit 1
fi

# Save the result
if [ "$OS" == "debian" ]; then
    OS_TYPE="Debian"
elif [ "$OS" == "ubuntu" ]; then
    OS_TYPE="Ubuntu"
else
    OS_TYPE="Unknown"
fi

# Demonstrate usage of the result
echo "Detected OS: $OS_TYPE"

(
    source "$HOME/github/emsdk/emsdk_env.sh"
    if [ "$OS_TYPE" == "Debian" ]; then
	emcmake cmake -S. -Bbuild -DVTK_DIR=/home/jmh/github/VTKCMake/install/lib/cmake/vtk  -DCMAKE_BUILD_TYPE=Release -DSPS_BUILD_TESTING=ON
    else
	emcmake cmake -S. -Bbuild -DVTK_DIR=$TSPKG_ROOT/ArtifactoryInstall/Wasm32StaticMT/Release/lib/cmake/vtk -DVTKEmbinding_BUILD_EXAMPLES=ON -DVTKEmbinding_ENABLE_WEBGPU=OFF -DVTKEmbinding_BUILD_TESTING=OFF -DCMAKE_BUILD_TYPE=Release -DVTKEmbinding_ENABLE_THREADING=ON
    fi	
    cmake --build build -j 8
)

