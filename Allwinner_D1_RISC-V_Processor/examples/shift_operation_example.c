/*
 * Allwinner D1 RISC-V Processor
 * Advanced Example: Shift Operations
 *
 * Demonstrates:
 *  - Logical left shift
 *  - Logical right shift
 *  - Bit extraction
 *  - Field insertion
 *  - Field extraction
 *  - Mask generation
 *  - 32-bit / 64-bit operations
 */

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define BIT32(n) (UINT32_C(1) << (n))
#define BIT64(n) (UINT64_C(1) << (n))

#define FIELD_MASK(width) \
    ((UINT32_C(1) << (width)) - UINT32_C(1))

#define FIELD_GET(value, mask, shift) \
    (((value) >> (shift)) & (mask))

#define FIELD_PREP(value, mask, shift) \
    (((value) & (mask)) << (shift))

static void print_binary32(uint32_t value)
{
    for (int i = 31; i >= 0; --i) {
        putchar((value & BIT32(i)) ? '1' : '0');

        if ((i % 4) == 0)
            putchar(' ');
    }

    putchar('\n');
}

static void print_binary64(uint64_t value)
{
    for (int i = 63; i >= 0; --i) {
        putchar((value & BIT64(i)) ? '1' : '0');

        if ((i % 4) == 0)
            putchar(' ');
    }

    putchar('\n');
}

int main(void)
{
    printf("==============================================\n");
    printf(" Allwinner D1 - Advanced SHIFT Example\n");
    printf("==============================================\n\n");

    /*
     * --------------------------------------------------
     * 1. LEFT SHIFT
     * --------------------------------------------------
     */

    uint32_t value = UINT32_C(1);

    printf("[1] LEFT SHIFT\n");

    for (unsigned int i = 0; i < 8; ++i) {
        uint32_t result = value << i;

        printf("1 << %-2u = 0x%08" PRIX32 "\n",
               i,
               result);
    }

    /*
     * --------------------------------------------------
     * 2. RIGHT SHIFT
     * --------------------------------------------------
     */

    value = UINT32_C(0x00000080);

    printf("\n[2] RIGHT SHIFT\n");

    for (unsigned int i = 0; i < 8; ++i) {
        uint32_t result = value >> i;

        printf("0x80 >> %-2u = 0x%08" PRIX32 "\n",
               i,
               result);
    }

    /*
     * --------------------------------------------------
     * 3. BIT EXTRACTION
     * --------------------------------------------------
     */

    uint32_t reg = UINT32_C(0x000000A8);

    unsigned int bit = 5;

    uint32_t bit_value = (reg >> bit) & 1U;

    printf("\n[3] BIT EXTRACTION\n");

    printf("Register : 0x%08" PRIX32 "\n", reg);
    printf("Bit      : %u\n", bit);
    printf("Value    : %u\n", bit_value);

    /*
     * --------------------------------------------------
     * 4. FIELD EXTRACTION
     *
     * Example:
     *
     * Bits [7:4] represent a 4-bit field.
     * --------------------------------------------------
     */

    printf("\n[4] FIELD EXTRACTION\n");

    uint32_t field_mask = UINT32_C(0x0F);
    unsigned int field_shift = 4;

    uint32_t field =
        FIELD_GET(reg, field_mask, field_shift);

    printf("Register : 0x%08" PRIX32 "\n", reg);
    printf("Field    : Bits [7:4]\n");
    printf("Value    : 0x%02" PRIX32 "\n", field);

    /*
     * --------------------------------------------------
     * 5. FIELD INSERTION
     * --------------------------------------------------
     */

    printf("\n[5] FIELD INSERTION\n");

    uint32_t register_value = 0;

    uint32_t new_field = UINT32_C(0x0A);

    register_value |=
        FIELD_PREP(new_field,
                   field_mask,
                   field_shift);

    printf("Field Value : 0x%02" PRIX32 "\n", new_field);

    printf("Register    : 0x%08" PRIX32 "\n",
           register_value);

    printf("Binary      : ");
    print_binary32(register_value);

    /*
     * --------------------------------------------------
     * 6. MASK GENERATION
     * --------------------------------------------------
     */

    printf("\n[6] MASK GENERATION\n");

    for (unsigned int width = 1; width <= 8; ++width) {

        uint32_t mask =
            FIELD_MASK(width);

        printf("Width %-2u -> Mask = 0x%02" PRIX32 "\n",
               width,
               mask);
    }

    /*
     * --------------------------------------------------
     * 7. 64-BIT SHIFT
     * --------------------------------------------------
     */

    printf("\n[7] 64-BIT SHIFT\n");

    uint64_t value64 = UINT64_C(1);

    for (unsigned int shift = 0;
         shift <= 56;
         shift += 8) {

        uint64_t result = value64 << shift;

        printf("1 << %-2u = 0x%016" PRIX64 "\n",
               shift,
               result);
    }

    /*
     * --------------------------------------------------
     * 8. REGISTER FIELD EXAMPLE
     * --------------------------------------------------
     *
     * Simulated hardware register:
     *
     * Bits [1:0]  = MODE
     * Bits [4:2]  = SPEED
     * Bit  [7]    = ENABLE
     */

    printf("\n[8] REGISTER FIELD CONFIGURATION\n");

    #define MODE_SHIFT      0U
    #define MODE_MASK       UINT32_C(0x03)

    #define SPEED_SHIFT     2U
    #define SPEED_MASK      UINT32_C(0x07)

    #define ENABLE_SHIFT    7U
    #define ENABLE_MASK     UINT32_C(0x01)

    uint32_t control_reg = 0;

    uint32_t mode = 2;
    uint32_t speed = 5;
    uint32_t enable = 1;

    control_reg |=
        FIELD_PREP(mode, MODE_MASK, MODE_SHIFT);

    control_reg |=
        FIELD_PREP(speed, SPEED_MASK, SPEED_SHIFT);

    control_reg |=
        FIELD_PREP(enable, ENABLE_MASK, ENABLE_SHIFT);

    printf("Control Register : 0x%08" PRIX32 "\n",
           control_reg);

    printf("MODE   : %" PRIu32 "\n",
           FIELD_GET(control_reg,
                     MODE_MASK,
                     MODE_SHIFT));

    printf("SPEED  : %" PRIu32 "\n",
           FIELD_GET(control_reg,
                     SPEED_MASK,
                     SPEED_SHIFT));

    printf("ENABLE : %" PRIu32 "\n",
           FIELD_GET(control_reg,
                     ENABLE_MASK,
                     ENABLE_SHIFT));

    printf("\nBinary:\n");
    print_binary32(control_reg);

    printf("\nSHIFT operation completed.\n");

    return 0;
}
