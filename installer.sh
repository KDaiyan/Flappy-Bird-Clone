#!/bin/bash

# Create the build directory if it doesn't exist
if [ ! -d "build-mingw" ]; then
    mkdir build-mingw
fi

# Run cmake to configure the project and generate the Makefiles
cmake -B build-mingw -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER=g++

# Build the project
cmake --build build-mingw