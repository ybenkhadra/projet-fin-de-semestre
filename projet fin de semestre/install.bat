@echo off
REM ========================================
REM Assistant de Traduction - Installation Windows
REM ========================================

setlocal enabledelayedexpansion

echo.
echo ========================================
echo   Assistant de Traduction Contextuel
echo   Installation automatique Windows
echo ========================================
echo.

REM Check if MinGW is installed
where mingw32-make >nul 2>&1
if errorlevel 1 (
    where make >nul 2>&1
    if errorlevel 1 (
        echo ERROR: MinGW/Make not found!
        echo.
        echo Please install MinGW with Make support from:
        echo https://www.mingw-w64.org/
        echo.
        pause
        exit /b 1
    )
)

REM Check if GCC is installed
where gcc >nul 2>&1
if errorlevel 1 (
    echo ERROR: GCC not found!
    echo.
    echo Please install MinGW with GCC support.
    echo.
    pause
    exit /b 1
)

echo [1/4] Verifying tools...
echo   - GCC: OK
echo   - Make: OK
echo.

REM Create necessary directories
echo [2/4] Creating directories...
if not exist bin mkdir bin
if not exist data mkdir data
echo   - bin\ created
echo   - data\ created
echo.

REM Clean previous builds
echo [3/4] Cleaning previous builds...
if exist bin\app.exe del bin\app.exe
if exist bin\test.exe del bin\test.exe
echo   - Cleaned old executables
echo.

REM Build the project
echo [4/4] Building project...
where mingw32-make >nul 2>&1
if errorlevel 0 (
    mingw32-make clean
    mingw32-make
) else (
    make clean
    make
)

if errorlevel 1 (
    echo.
    echo ERROR: Build failed!
    echo.
    pause
    exit /b 1
)

echo.
echo ========================================
echo   Installation Complete!
echo ========================================
echo.
echo Next steps:
echo   1. Run: bin\app.exe
echo   2. Or run tests: mingw32-make test
echo.
echo For help, see usage.md
echo.
pause
exit /b 0
