#!/bin/bash

# ============================================================================
# Allwinner D1 RISC-V Processor
# Clean Script
# ============================================================================

set -e

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

cd "$PROJECT_ROOT"

echo "=============================================="
echo " Allwinner D1 RISC-V Processor"
echo " Clean"
echo "=============================================="

echo
echo "[INFO] Project Root:"
echo "       $PROJECT_ROOT"

if [ -f Makefile ]; then

    echo
    echo "[INFO] Running make clean..."

    make clean

else

    echo
    echo "[WARN] Makefile not found."

fi

echo
echo "[INFO] Removing generated binaries..."

rm -f bit_manipulation
rm -f bit_mask_example
rm -f set_bit_example
rm -f clear_bit_example
rm -f toggle_bit_example
rm -f check_bit_example
rm -f shift_operation_example

echo
echo "[INFO] Removing object files..."

find . -type f -name "*.o" -delete

echo
echo "=============================================="
echo " Clean completed successfully"
echo "=============================================="
