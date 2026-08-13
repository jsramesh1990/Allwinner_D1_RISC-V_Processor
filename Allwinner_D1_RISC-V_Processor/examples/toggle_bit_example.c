/*
 * Allwinner D1 RISC-V Processor
 * Advanced Example: Toggle Bit Operations
 *
 * Demonstrates:
 *  - XOR-based toggling
 *  - 32-bit / 64-bit operations
 *  - Multiple-bit toggling
 *  - State transitions
 */

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define BIT32(n)         (UINT32_C(1) << (n))
#define BIT64(n)         (UINT64_C(1) << (n))

#define TOGGLE_BIT32(v,n) ((v) ^= BIT32(n))
#define TOGGLE_BIT64(v,n) ((v) ^= BIT64(n))

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
    uint32_t reg32 = 0;
    uint64_t reg64 = 0;

    printf("============================================\n");
    printf(" Allwinner D1 - Advanced TOGGLE BIT Example\n");
    printf("============================================\n\n");

    printf("[32-bit Toggle]\n");

    printf("Initial : 0x%08" PRIX32 "\n", reg32);

    TOGGLE_BIT32(reg32, 3);

    printf("Toggle  : Bit 3\n");
    printf("Result  : 0x%08" PRIX32 "\n", reg32);
    printf("Binary  : ");
    print_binary32(reg32);

    TOGGLE_BIT32(reg32, 3);

    printf("\nToggle Again: Bit 3\n");
    printf("Result      : 0x%08" PRIX32 "\n", reg32);
    printf("Binary      : ");
    print_binary32(reg32);

    printf("\n[64-bit Toggle]\n");

    printf("Initial : 0x%016" PRIX64 "\n", reg64);

    TOGGLE_BIT64(reg64, 40);

    printf("Toggle  : Bit 40\n");
    printf("Result  : 0x%016" PRIX64 "\n", reg64);
    printf("Binary  : ");
    print_binary64(reg64);

    /*
     * Toggle multiple bits simultaneously.
     */
    uint32_t mask = BIT32(1) |
                    BIT32(5) |
                    BIT32(9) |
                    BIT32(13);

    printf("\n[Multi-Bit Toggle]\n");
    printf("Mask    : 0x%08" PRIX32 "\n", mask);

    reg32 ^= mask;

    printf("Result  : 0x%08" PRIX32 "\n", reg32);

    /*
     * Demonstrate XOR state transition.
     */
    printf("\n[XOR State Transition]\n");

    uint32_t state = BIT32(0);

    for (int i = 0; i < 4; ++i) {
        state ^= BIT32(0);

        printf("Toggle %d -> Bit 0 = %u\n",
               i + 1,
               (state & BIT32(0)) ? 1U : 0U);
    }

    printf("\nTOGGLE BIT operation completed.\n");

    return 0;
}
