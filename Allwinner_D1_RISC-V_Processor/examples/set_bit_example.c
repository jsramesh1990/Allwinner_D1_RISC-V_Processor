/*
 * Allwinner D1 RISC-V Processor
 * Advanced Example: Set Bit Operations
 *
 * Demonstrates:
 *  - 32-bit and 64-bit bit manipulation
 *  - Single-bit setting
 *  - Multi-bit masks
 *  - Compile-time bit masks
 *  - Runtime validation
 *  - Binary visualization
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>

#define BIT32(n)        (UINT32_C(1) << (n))
#define BIT64(n)        (UINT64_C(1) << (n))

#define SET_BIT32(v, n) ((v) |= BIT32(n))
#define SET_BIT64(v, n) ((v) |= BIT64(n))

static bool valid_bit32(unsigned int bit)
{
    return bit < 32U;
}

static bool valid_bit64(unsigned int bit)
{
    return bit < 64U;
}

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

static int set_bit32(uint32_t *value, unsigned int bit)
{
    if (value == NULL || !valid_bit32(bit))
        return -1;

    *value |= BIT32(bit);

    return 0;
}

static int set_bit64(uint64_t *value, unsigned int bit)
{
    if (value == NULL || !valid_bit64(bit))
        return -1;

    *value |= BIT64(bit);

    return 0;
}

int main(void)
{
    uint32_t reg32 = UINT32_C(0x00000001);
    uint64_t reg64 = UINT64_C(0x0000000000000001);

    const unsigned int bit32 = 7;
    const unsigned int bit64 = 40;

    printf("============================================\n");
    printf(" Allwinner D1 - Advanced SET BIT Example\n");
    printf(" RISC-V 64-bit Processor\n");
    printf("============================================\n\n");

    printf("[32-bit]\n");
    printf("Before : 0x%08" PRIX32 "\n", reg32);
    printf("Binary : ");
    print_binary32(reg32);

    if (set_bit32(&reg32, bit32) == 0) {
        printf("Set Bit: %u\n", bit32);
        printf("After  : 0x%08" PRIX32 "\n", reg32);
        printf("Binary : ");
        print_binary32(reg32);
    }

    printf("\n[64-bit]\n");
    printf("Before : 0x%016" PRIX64 "\n", reg64);
    printf("Binary : ");
    print_binary64(reg64);

    if (set_bit64(&reg64, bit64) == 0) {
        printf("Set Bit: %u\n", bit64);
        printf("After  : 0x%016" PRIX64 "\n", reg64);
        printf("Binary : ");
        print_binary64(reg64);
    }

    /*
     * Multi-bit mask.
     *
     * Bits 4, 8 and 12 are set simultaneously.
     */
    uint32_t mask = BIT32(4) | BIT32(8) | BIT32(12);

    printf("\n[Multi-Bit Mask]\n");
    printf("Mask   : 0x%08" PRIX32 "\n", mask);

    SET_BIT32(reg32, 4);
    SET_BIT32(reg32, 8);
    SET_BIT32(reg32, 12);

    printf("Result : 0x%08" PRIX32 "\n", reg32);

    printf("\nSET BIT operation completed.\n");

    return 0;
}
