#!/bin/bash

# ============================================================================
# Allwinner D1 RISC-V Processor
# Run Script
#
# Usage:
#
#   ./scripts/run.sh
#
#   ./scripts/run.sh bit_mask
#   ./scripts/run.sh set_bit
#   ./scripts/run.sh clear_bit
#   ./scripts/run.sh toggle_bit
#   ./scripts/run.sh check_bit
#   ./scripts/run.sh shift
# ============================================================================

set -e

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

cd "$PROJECT_ROOT"

echo "=============================================="
echo " Allwinner D1 RISC-V Processor"
echo " Runtime"
echo "=============================================="

TARGET="${1:-main}"

case "$TARGET" in

    main)
        BINARY="./bin/bit_manipulation"
        ;;

    bit_mask)
        BINARY="./bin/bit_mask_example"
        ;;

    set_bit)
        BINARY="./bin/set_bit_example"
        ;;

    clear_bit)
        BINARY="./bin/clear_bit_example"
        ;;

    toggle_bit)
        BINARY="./bin/toggle_bit_example"
        ;;

    check_bit)
        BINARY="./bin/check_bit_example"
        ;;

    shift)
        BINARY="./bin/shift_operation_example"
        ;;

    *)
        echo
        echo "[ERROR] Unknown target: $TARGET"
        echo
        echo "Available targets:"
        echo "  main"
        echo "  bit_mask"
        echo "  set_bit"
        echo "  clear_bit"
        echo "  toggle_bit"
        echo "  check_bit"
        echo "  shift"
        exit 1
        ;;

esac

if [ ! -f "$BINARY" ]; then

    echo
    echo "[WARN] Binary not found:"
    echo "       $BINARY"

    echo
    echo "[INFO] Building project..."

    ./scripts/build.sh

fi

echo
echo "[INFO] Executing:"
echo "       $BINARY"

echo
echo "----------------------------------------------"

"$BINARY"

RET=$?

echo "----------------------------------------------"

echo
if [ "$RET" -eq 0 ]; then
    echo "[PASS] Program completed successfully."
else
    echo "[FAIL] Program exited with code: $RET"
fi

exit "$RET"
