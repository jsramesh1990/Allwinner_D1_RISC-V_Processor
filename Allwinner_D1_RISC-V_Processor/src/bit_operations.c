/*
 * ============================================================================
 * Allwinner D1 RISC-V Processor
 * bit_operations.c
 *
 * Core bit manipulation implementation.
 * ============================================================================
 */

#include "bit_operations.h"
#include "d1_registers.h"

#include <stdio.h>
#include <stddef.h>


/* ============================================================================
 * Internal Validation
 * ========================================================================== */

static bool valid_bit32(unsigned int bit)
{
    return D1_IS_VALID_BIT32(bit);
}


static bool valid_bit64(unsigned int bit)
{
    return D1_IS_VALID_BIT64(bit);
}


/* ============================================================================
 * 32-bit Operations
 * ========================================================================== */

int bit_set_u32(uint32_t *value,
                unsigned int bit)
{
    if (value == NULL || !valid_bit32(bit))
        return -1;

    D1_SET_BIT32(*value, bit);

    return 0;
}


int bit_clear_u32(uint32_t *value,
                  unsigned int bit)
{
    if (value == NULL || !valid_bit32(bit))
        return -1;

    D1_CLEAR_BIT32(*value, bit);

    return 0;
}


int bit_toggle_u32(uint32_t *value,
                   unsigned int bit)
{
    if (value == NULL || !valid_bit32(bit))
        return -1;

    D1_TOGGLE_BIT32(*value, bit);

    return 0;
}


int bit_check_u32(uint32_t value,
                  unsigned int bit,
                  bool *result)
{
    if (result == NULL || !valid_bit32(bit))
        return -1;

    *result = D1_IS_BIT_SET32(value, bit);

    return 0;
}


/* ============================================================================
 * 64-bit Operations
 * ========================================================================== */

int bit_set_u64(uint64_t *value,
                unsigned int bit)
{
    if (value == NULL || !valid_bit64(bit))
        return -1;

    D1_SET_BIT64(*value, bit);

    return 0;
}


int bit_clear_u64(uint64_t *value,
                  unsigned int bit)
{
    if (value == NULL || !valid_bit64(bit))
        return -1;

    D1_CLEAR_BIT64(*value, bit);

    return 0;
}


int bit_toggle_u64(uint64_t *value,
                   unsigned int bit)
{
    if (value == NULL || !valid_bit64(bit))
        return -1;

    D1_TOGGLE_BIT64(*value, bit);

    return 0;
}


int bit_check_u64(uint64_t value,
                  unsigned int bit,
                  bool *result)
{
    if (result == NULL || !valid_bit64(bit))
        return -1;

    *result = D1_IS_BIT_SET64(value, bit);

    return 0;
}


/* ============================================================================
 * Mask Operations
 * ========================================================================== */

int bit_set_mask32(uint32_t *value,
                   uint32_t mask)
{
    if (value == NULL)
        return -1;

    D1_SET_MASK32(*value, mask);

    return 0;
}


int bit_clear_mask32(uint32_t *value,
                     uint32_t mask)
{
    if (value == NULL)
        return -1;

    D1_CLEAR_MASK32(*value, mask);

    return 0;
}


int bit_toggle_mask32(uint32_t *value,
                      uint32_t mask)
{
    if (value == NULL)
        return -1;

    D1_TOGGLE_MASK32(*value, mask);

    return 0;
}


bool bit_all_set32(uint32_t value,
                   uint32_t mask)
{
    return D1_ALL_BITS_SET32(value, mask);
}


bool bit_any_set32(uint32_t value,
                   uint32_t mask)
{
    return D1_ANY_BIT_SET32(value, mask);
}


/* ============================================================================
 * Field Operations
 * ========================================================================== */

int bit_field_get32(uint32_t value,
                    uint32_t mask,
                    unsigned int shift,
                    uint32_t *result)
{
    if (result == NULL)
        return -1;

    *result = D1_FIELD_GET32(value, mask, shift);

    return 0;
}


int bit_field_set32(uint32_t *value,
                    uint32_t mask,
                    unsigned int shift,
                    uint32_t field_value)
{
    if (value == NULL)
        return -1;

    D1_FIELD_MODIFY32(*value,
                      mask,
                      shift,
                      field_value);

    return 0;
}


/* ============================================================================
 * Binary Display
 * ========================================================================== */

void bit_print_binary32(uint32_t value)
{
    for (int i = 31; i >= 0; --i) {

        putchar((value & D1_BIT32(i)) ? '1' : '0');

        if ((i % 4) == 0)
            putchar(' ');
    }

    putchar('\n');
}


void bit_print_binary64(uint64_t value)
{
    for (int i = 63; i >= 0; --i) {

        putchar((value & D1_BIT64(i)) ? '1' : '0');

        if ((i % 4) == 0)
            putchar(' ');
    }

    putchar('\n');
}
