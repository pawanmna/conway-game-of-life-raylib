#!/bin/bash

# Default settings
APP_NAME="GameOfLifeSphere"
SRC_DIR="src"
BUILD_DIR="build"
VENDOR_DIR="vendor"
RAYLIB_DIR="$VENDOR_DIR/raylib"
RAYLIB_LIB_PATH="$RAYLIB_DIR/src/libraylib.a"
RAYLIB_INCLUDE_PATH="$RAYLIB_DIR/src"

# Detect OS
UNAME_S=$(uname -s)
if [[ "$UNAME_S" == "Darwin" ]]; then
    PLATFORM="OSX"
    COMPILER="clang++"
    LIBS="-framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL"
else
    PLATFORM="LINUX"
    COMPILER="g++"
    LIBS="-lGL -lm -lpthread -ldl -lrt -lX11"
fi

# Create build directory
mkdir -p $BUILD_DIR

# Function to check if raylib is installed globally
check_global_raylib() {
    if pkg-config --exists raylib; then
        echo "Raylib found globally."
        return 0
    fi
    # Check common locations
    if [ -f "/usr/local/lib/libraylib.a" ] || [ -f "/usr/lib/libraylib.a" ]; then
        echo "Raylib found in standard library paths."
        return 0
    fi
    return 1
}

# Function to install raylib locally
install_raylib_local() {
    echo "Raylib not found globally."
    read -p "Do you want to download and build Raylib locally in ./vendor? (y/n) " -n 1 -r
    echo
    if [[ ! $REPLY =~ ^[Yy]$ ]]; then
        echo "Aborting. Please install Raylib manually."
        exit 1
    fi

    mkdir -p $VENDOR_DIR
    if [ ! -d "$RAYLIB_DIR" ]; then
        echo "Cloning Raylib..."
        git clone --depth 1 https://github.com/raysan5/raylib.git $RAYLIB_DIR
    fi

    echo "Building Raylib..."
    cd $RAYLIB_DIR/src
    make PLATFORM=PLATFORM_DESKTOP
    cd ../../..
}

# Check dependencies
if ! check_global_raylib; then
    if [ ! -f "$RAYLIB_LIB_PATH" ]; then
        install_raylib_local
    else
        echo "Using local Raylib at $RAYLIB_DIR"
    fi
    INCLUDE_FLAGS="-I$RAYLIB_INCLUDE_PATH"
    LIB_FLAGS="-L$RAYLIB_DIR/src -lraylib"
else
    INCLUDE_FLAGS=$(pkg-config --cflags raylib 2>/dev/null)
    LIB_FLAGS=$(pkg-config --libs raylib 2>/dev/null || echo "-lraylib")
fi

echo "Compiling $APP_NAME for $PLATFORM..."

$COMPILER $SRC_DIR/*.cpp -o $BUILD_DIR/$APP_NAME -O2 -std=c++11 $INCLUDE_FLAGS $LIB_FLAGS $LIBS

if [ $? -eq 0 ]; then
    echo "Build successful! Run with: ./$BUILD_DIR/$APP_NAME"
else
    echo "Build failed."
fi
