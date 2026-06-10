#!/bin/bash

# ========================================
# Assistant de Traduction - Installation Unix/Linux/macOS
# ========================================

set -e

echo ""
echo "========================================"
echo "  Assistant de Traduction Contextuel"
echo "  Installation automatique Unix/Linux/macOS"
echo "========================================"
echo ""

# Check if GCC is installed
if ! command -v gcc &> /dev/null; then
    echo "ERROR: GCC not found!"
    echo ""
    echo "Please install GCC:"
    echo "  Ubuntu/Debian: sudo apt-get install build-essential"
    echo "  macOS: xcode-select --install"
    echo "  Fedora/RHEL: sudo yum install gcc make"
    echo ""
    exit 1
fi

# Check if Make is installed
if ! command -v make &> /dev/null; then
    echo "ERROR: Make not found!"
    echo ""
    echo "Please install Make:"
    echo "  Ubuntu/Debian: sudo apt-get install build-essential"
    echo "  macOS: xcode-select --install"
    echo "  Fedora/RHEL: sudo yum install make"
    echo ""
    exit 1
fi

echo "[1/4] Verifying tools..."
echo "  - GCC: $(gcc --version | head -1)"
echo "  - Make: $(make --version | head -1)"
echo ""

# Create necessary directories
echo "[2/4] Creating directories..."
mkdir -p bin
mkdir -p data
echo "  - bin/ created"
echo "  - data/ created"
echo ""

# Clean previous builds
echo "[3/4] Cleaning previous builds..."
rm -f bin/app bin/test
echo "  - Cleaned old executables"
echo ""

# Build the project
echo "[4/4] Building project..."
make clean
make

echo ""
echo "========================================"
echo "  Installation Complete!"
echo "========================================"
echo ""
echo "Next steps:"
echo "  1. Run: ./bin/app"
echo "  2. Or run tests: make test"
echo ""
echo "For help, see usage.md"
echo ""
