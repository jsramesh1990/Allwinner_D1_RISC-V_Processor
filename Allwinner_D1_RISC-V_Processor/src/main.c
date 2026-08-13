/*
 * ============================================================================
 * Allwinner D1 RISC-V Processor
 * main.c
 *
 * Main application demonstrating the bit manipulation API.
 * ============================================================================
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>

#include "bit_operations.h"
#include "register_access.h"


static void print_result(const char *operation,
                         int status)
{
    printf("%-20s : %s\n",
           operation,
           status == 0 ? "PASS" : "FAIL");
}


int main(void)
{
    uint32_t value = 0;

    bool bit_status = false;

    uint32_t mask =
        (UINT32_C(1) << 1) |
        (UINT32_C(1) << 3) |
        (UINT32_C(1) << 5);

    printf("\n");
    printf("================================================\n");
    printf(" Allwinner D1 RISC-V Processor\n");
    printf(" Bit Manipulation Framework\n");
    printf("================================================\n");

    printf("\nInitial Value : 0x%08" PRIX32 "\n",
           value);

    /*
     * SET BIT
     */
    print_result("SET BIT 3",
                 bit_set_u32(&value, 3));

    printf("Value         : 0x%08" PRIX32 "\n",
           value);

    /*
     * CHECK BIT
     */
    if (bit_check_u32(value, 3, &bit_status) == 0) {

        printf("BIT 3 STATUS  : %s\n",
               bit_status ? "SET" : "CLEAR");
    }

    /*
     * CLEAR BIT
     */
    print_result("CLEAR BIT 3",
                 bit_clear_u32(&value, 3));

    printf("Value         : 0x%08" PRIX32 "\n",
           value);

    /*
     * TOGGLE BIT
     */
    print_result("TOGGLE BIT 4",
                 bit_toggle_u32(&value, 4));

    printf("Value         : 0x%08" PRIX32 "\n",
           value);

    /*
     * MULTI-BIT MASK
     */
    print_result("SET MASK",
                 bit_set_mask32(&value, mask));

    printf("Mask          : 0x%08" PRIX32 "\n",
           mask);

    printf("Value         : 0x%08" PRIX32 "\n",
           value);

    /*
     * MASK STATUS
     */
    printf("ALL MASK BITS  : %s\n",
           bit_all_set32(value, mask)
               ? "SET"
               : "NOT SET");

    /*
     * Binary output
     */
    printf("\nBinary Value:\n");

    bit_print_binary32(value);

    /*
     * FIELD OPERATION
     *
     * Bits [7:4]
     */
    uint32_t field_mask = UINT32_C(0x0F);
    unsigned int field_shift = 4;

    printf("\nField Operation\n");

    if (bit_field_set32(&value,
                        field_mask,
                        field_shift,
                        0x0A) == 0) {

        printf("Field Value   : 0x0A\n");
        printf("Register      : 0x%08" PRIX32 "\n",
               value);
    }

    uint32_t extracted = 0;

    if (bit_field_get32(value,
                        field_mask,
                        field_shift,
                        &extracted) == 0) {

        printf("Extracted     : 0x%08" PRIX32 "\n",
               extracted);
    }

    printf("\n================================================\n");
    printf(" Test execution completed\n");
    printf("================================================\n");

    return 0;
}
