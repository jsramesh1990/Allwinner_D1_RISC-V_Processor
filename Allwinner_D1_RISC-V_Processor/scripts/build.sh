#!/bin/bash

# ============================================================================
# Allwinner D1 RISC-V Processor
# Build Script
#
# Usage:
#   ./scripts/build.sh
#   ./scripts/build.sh clean
#   ./scripts/build.sh debug
# ============================================================================

set -e

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

cd "$PROJECT_ROOT"

echo "=============================================="
echo " Allwinner D1 RISC-V Processor"
echo " Build System"
echo "=============================================="

echo
echo "[INFO] Project Root:"
echo "       $PROJECT_ROOT"

echo
echo "[INFO] Checking build tools..."

if ! command -v gcc >/dev/null 2>&1; then
    echo "[ERROR] gcc not found."
    exit 1
fi

if ! command -v make >/dev/null 2>&1; then
    echo "[ERROR] make not found."
    exit 1
fi

echo "[OK] gcc found: $(gcc --version | head -n 1)"
echo "[OK] make found: $(make --version | head -n 1)"

echo
echo "[INFO] Starting build..."

case "${1:-release}" in

    release)
        echo "[BUILD] Release configuration"
        make
        ;;

    debug)
        echo "[BUILD] Debug configuration"
        make CFLAGS="-Wall -Wextra -O0 -g"
        ;;

    clean)
        echo "[BUILD] Cleaning previous build"
        make clean
        ;;

    *)
        echo
        echo "Usage:"
        echo "  $0              Build release"
        echo "  $0 release      Build release"
        echo "  $0 debug        Build debug version"
        echo "  $0 clean        Clean build"
        exit 1
        ;;

esac

echo
echo "=============================================="
echo " Build completed successfully"
echo "=============================================="
