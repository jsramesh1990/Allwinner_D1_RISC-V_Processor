/*
 * Allwinner D1 RISC-V Processor
 * Advanced Example: Clear Bit Operations
 *
 * Demonstrates:
 *  - Single-bit clearing
 *  - Multi-bit clearing
 *  - 32-bit / 64-bit values
 *  - Mask inversion
 *  - Safe bit-position validation
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>

#define BIT32(n)          (UINT32_C(1) << (n))
#define BIT64(n)          (UINT64_C(1) << (n))

#define CLEAR_BIT32(v,n)  ((v) &= ~BIT32(n))
#define CLEAR_BIT64(v,n)  ((v) &= ~BIT64(n))

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

static int clear_bit32(uint32_t *value, unsigned int bit)
{
    if (value == NULL || !valid_bit32(bit))
        return -1;

    *value &= ~BIT32(bit);

    return 0;
}

static int clear_bit64(uint64_t *value, unsigned int bit)
{
    if (value == NULL || !valid_bit64(bit))
        return -1;

    *value &= ~BIT64(bit);

    return 0;
}

int main(void)
{
    uint32_t reg32 = UINT32_C(0xFFFFFFFF);
    uint64_t reg64 = UINT64_MAX;

    const unsigned int bit32 = 7;
    const unsigned int bit64 = 40;

    printf("============================================\n");
    printf(" Allwinner D1 - Advanced CLEAR BIT Example\n");
    printf("============================================\n\n");

    printf("[32-bit]\n");

    printf("Before : 0x%08" PRIX32 "\n", reg32);
    printf("Binary : ");
    print_binary32(reg32);

    if (clear_bit32(&reg32, bit32) == 0) {
        printf("Clear Bit: %u\n", bit32);
        printf("After   : 0x%08" PRIX32 "\n", reg32);
        printf("Binary  : ");
        print_binary32(reg32);
    }

    printf("\n[64-bit]\n");

    printf("Before : 0x%016" PRIX64 "\n", reg64);
    printf("Binary : ");
    print_binary64(reg64);

    if (clear_bit64(&reg64, bit64) == 0) {
        printf("Clear Bit: %u\n", bit64);
        printf("After    : 0x%016" PRIX64 "\n", reg64);
        printf("Binary   : ");
        print_binary64(reg64);
    }

    /*
     * Clear multiple bits using a mask.
     */
    uint32_t mask = BIT32(0) |
                    BIT32(4) |
                    BIT32(8) |
                    BIT32(12);

    uint32_t register_value = UINT32_C(0xFFFFFFFF);

    printf("\n[Multi-Bit CLEAR]\n");
    printf("Before : 0x%08" PRIX32 "\n", register_value);
    printf("Mask   : 0x%08" PRIX32 "\n", mask);

    register_value &= ~mask;

    printf("After  : 0x%08" PRIX32 "\n", register_value);

    printf("\nCLEAR BIT operation completed.\n");

    return 0;
}
