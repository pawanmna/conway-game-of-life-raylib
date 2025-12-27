@echo off
setlocal

set OUT_EXE=GameOfLifeSphere.exe

:: --- CONFIGURATION ---
set RAYLIB_INCLUDE=
set RAYLIB_LIB=
set COMPILER=g++

:: Check for w64devkit compiler and update PATH
if exist "C:\raylib\w64devkit\bin\g++.exe" (
    set "PATH=C:\raylib\w64devkit\bin;%PATH%"
    set COMPILER=g++
)

:: Check default Zip location 
if exist "C:\raylib\lib\libraylib.a" (
    set RAYLIB_INCLUDE=C:\raylib\include
    set RAYLIB_LIB=C:\raylib\lib
)

:: Check default Installer location
if exist "C:\raylib\raylib\lib\libraylib.a" (
    set RAYLIB_INCLUDE=C:\raylib\raylib\include
    set RAYLIB_LIB=C:\raylib\raylib\lib
)

:: Check Source location (common in w64devkit bundle)
if exist "C:\raylib\raylib\src\libraylib.a" (
    set RAYLIB_INCLUDE=C:\raylib\raylib\src
    set RAYLIB_LIB=C:\raylib\raylib\src
)

:: Check Local Vendor location
if exist "vendor\raylib\src\libraylib.a" (
    set RAYLIB_INCLUDE=vendor\raylib\src
    set RAYLIB_LIB=vendor\raylib\src
)

if "%RAYLIB_LIB%"=="" (
    echo.
    echo [WARNING] Could not find libraylib.a in standard locations.
    echo.
    set /p INSTALL="Do you want to download and build Raylib locally? (y/n): "
    if /i "%INSTALL%"=="y" (
        if not exist "vendor" mkdir vendor
        if not exist "vendor\raylib" (
            echo Cloning Raylib...
            git clone --depth 1 https://github.com/raysan5/raylib.git vendor\raylib
        )
        echo Building Raylib...
        pushd vendor\raylib\src
        mingw32-make PLATFORM=PLATFORM_DESKTOP
        popd
        
        if exist "vendor\raylib\src\libraylib.a" (
            set RAYLIB_INCLUDE=vendor\raylib\src
            set RAYLIB_LIB=vendor\raylib\src
        ) else (
            echo [ERROR] Failed to build Raylib. Please install manually.
            pause
            exit /b 1
        )
    ) else (
        echo.
        echo Please edit this script and set RAYLIB_INCLUDE and RAYLIB_LIB manually.
        pause
        exit /b 1
    )
)

echo Found Raylib lib at: %RAYLIB_LIB%
echo Found Raylib include at: %RAYLIB_INCLUDE%
echo Using compiler: %COMPILER%

echo Compiling %OUT_EXE%...

:: Compile command
"%COMPILER%" src/*.cpp -o %OUT_EXE% -O2 -I"%RAYLIB_INCLUDE%" -L"%RAYLIB_LIB%" -lraylib -lopengl32 -lgdi32 -lwinmm

if %ERRORLEVEL% EQU 0 (
    echo Build successful! Launching...
    %OUT_EXE%
) else (
    echo.
    echo Build failed.
    pause
)
