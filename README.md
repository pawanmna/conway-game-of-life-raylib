# Conway's Game of Life on a Sphere

A 3D implementation of Conway's Game of Life projected onto a sphere, built with C++ and Raylib.

## Features
- 3D Spherical Grid
- Interactive Camera (Orbit)
- Pause/Resume and Reset controls
- Cross-platform support (Windows, Linux, macOS)

## Controls
- **Mouse**: Orbit camera
- **Space**: Pause/Resume simulation
- **R**: Reset grid

## Build and Run

### Windows
1.  Ensure you have a C++ compiler (MinGW/w64devkit) and Git installed.
2.  Double-click `build.bat` or run it from a terminal:
    ```powershell
    .\build.bat
    ```
    *If Raylib is not found, the script will offer to download and build it for you.*

### Linux / macOS
1.  Ensure you have `git`, `make`, and a C++ compiler (`g++` or `clang++`) installed.
    *   **Ubuntu/Debian**: `sudo apt install build-essential git libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev`
    *   **macOS**: `xcode-select --install`
2.  Run the build script:
    ```bash
    chmod +x build.sh
    ./build.sh
    ```
    *If Raylib is not found, the script will offer to download and build it for you.*

## License
This project is licensed under the MIT License - see the LICENSE file for details.