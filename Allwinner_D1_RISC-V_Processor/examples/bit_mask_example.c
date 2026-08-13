#include <stdio.h>
#include <stdint.h>

/*
 * Allwinner D1 RISC-V Processor
 * Example: Bit Mask Operations
 *
 * Demonstrates:
 *  - Creating a bit mask
 *  - Setting selected bits
 *  - Clearing selected bits
 *  - Checking selected bits
 *  - Toggling selected bits
 */

#define BIT(n)              (1U << (n))

#define SET_BITS(reg, mask)    ((reg) |= (mask))
#define CLEAR_BITS(reg, mask)  ((reg) &= ~(mask))
#define TOGGLE_BITS(reg, mask) ((reg) ^= (mask))
#define CHECK_BITS(reg, mask)  ((reg) & (mask))

static void print_binary(uint32_t value)
{
    for (int i = 31; i >= 0; i--) {
        printf("%u", (value >> i) & 1U);

        if (i % 4 == 0)
            printf(" ");
    }

    printf("\n");
}

int main(void)
{
    uint32_t reg = 0x00000000;

    /* Create mask for bits 1, 3 and 5 */
    uint32_t mask = BIT(1) | BIT(3) | BIT(5);

    printf("====================================\n");
    printf(" Allwinner D1 RISC-V Bit Mask Demo\n");
    printf("====================================\n\n");

    printf("Initial Register : 0x%08X\n", reg);
    printf("Initial Binary   : ");
    print_binary(reg);

    printf("\nMask             : 0x%08X\n", mask);
    printf("Mask Binary      : ");
    print_binary(mask);

    /* Set selected bits */
    SET_BITS(reg, mask);

    printf("\nAfter SET        : 0x%08X\n", reg);
    printf("Binary           : ");
    print_binary(reg);

    /* Check selected bits */
    if (CHECK_BITS(reg, mask) == mask)
        printf("Check            : All masked bits are SET\n");
    else
        printf("Check            : Masked bits are not all SET\n");

    /* Clear selected bits */
    CLEAR_BITS(reg, mask);

    printf("\nAfter CLEAR      : 0x%08X\n", reg);
    printf("Binary           : ");
    print_binary(reg);

    /* Toggle selected bits */
    TOGGLE_BITS(reg, mask);

    printf("\nAfter TOGGLE     : 0x%08X\n", reg);
    printf("Binary           : ");
    print_binary(reg);

    printf("\nBit mask test completed successfully.\n");

    return 0;
}
