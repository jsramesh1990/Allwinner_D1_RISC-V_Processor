/*
 * Allwinner D1 RISC-V Processor
 * Advanced Example: Check Bit Operations
 *
 * Demonstrates:
 *  - Bit testing
 *  - Mask testing
 *  - Individual bit state
 *  - 32-bit / 64-bit values
 *  - Register status decoding
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>

#define BIT32(n) (UINT32_C(1) << (n))
#define BIT64(n) (UINT64_C(1) << (n))

#define IS_BIT_SET32(v,n) (((v) & BIT32(n)) != 0U)
#define IS_BIT_SET64(v,n) (((v) & BIT64(n)) != 0U)

static void print_binary32(uint32_t value)
{
    for (int i = 31; i >= 0; --i) {
        putchar((value & BIT32(i)) ? '1' : '0');

        if ((i % 4) == 0)
            putchar(' ');
    }

    putchar('\n');
}

static bool check_mask32(uint32_t value, uint32_t mask)
{
    return (value & mask) == mask;
}

static bool check_any_mask32(uint32_t value, uint32_t mask)
{
    return (value & mask) != 0U;
}

int main(void)
{
    uint32_t status_reg = UINT32_C(0x0000002A);

    printf("============================================\n");
    printf(" Allwinner D1 - Advanced CHECK BIT Example\n");
    printf("============================================\n\n");

    printf("Status Register : 0x%08" PRIX32 "\n", status_reg);

    printf("Binary          : ");
    print_binary32(status_reg);

    printf("\nIndividual Bit Status:\n");

    for (unsigned int bit = 0; bit < 16; ++bit) {
        printf("Bit %2u : %s\n",
               bit,
               IS_BIT_SET32(status_reg, bit) ? "SET" : "CLEAR");
    }

    /*
     * Check whether all bits represented by the mask are set.
     */
    uint32_t required_mask =
        BIT32(1) |
        BIT32(3) |
        BIT32(5);

    printf("\nRequired Mask : 0x%08" PRIX32 "\n",
           required_mask);

    if (check_mask32(status_reg, required_mask))
        printf("ALL required bits are SET\n");
    else
        printf("NOT all required bits are SET\n");

    /*
     * Check whether at least one bit from the mask is set.
     */
    uint32_t event_mask =
        BIT32(2) |
        BIT32(3) |
        BIT32(7);

    printf("\nEvent Mask : 0x%08" PRIX32 "\n",
           event_mask);

    if (check_any_mask32(status_reg, event_mask))
        printf("At least one event bit is SET\n");
    else
        printf("No event bit is SET\n");

    /*
     * 64-bit check.
     */
    uint64_t reg64 = UINT64_C(0x0000010000000000);

    printf("\n64-bit Register : 0x%016" PRIX64 "\n", reg64);

    printf("Bit 40 : %s\n",
           IS_BIT_SET64(reg64, 40) ? "SET" : "CLEAR");

    printf("\nCHECK BIT operation completed.\n");

    return 0;
}
