/*
 * ============================================================================
 * Allwinner D1 RISC-V Processor
 * register_access.c
 *
 * Register-level read/modify/write implementation.
 * ============================================================================
 */

#include "register_access.h"
#include "d1_registers.h"


/* ============================================================================
 * Basic Register Access
 * ========================================================================== */

uint32_t register_read32(volatile uint32_t *address)
{
    if (address == NULL)
        return 0;

    return d1_read32(address);
}


void register_write32(volatile uint32_t *address,
                      uint32_t value)
{
    if (address == NULL)
        return;

    d1_write32(address, value);
}


/* ============================================================================
 * Register Bit Operations
 * ========================================================================== */

void register_set_bits32(volatile uint32_t *address,
                         uint32_t mask)
{
    if (address == NULL)
        return;

    d1_reg_set_bits(address, mask);
}


void register_clear_bits32(volatile uint32_t *address,
                           uint32_t mask)
{
    if (address == NULL)
        return;

    d1_reg_clear_bits(address, mask);
}


void register_toggle_bits32(volatile uint32_t *address,
                            uint32_t mask)
{
    if (address == NULL)
        return;

    d1_reg_toggle_bits(address, mask);
}


/* ============================================================================
 * Read / Modify / Write
 * ========================================================================== */

void register_update_bits32(volatile uint32_t *address,
                            uint32_t mask,
                            uint32_t value)
{
    if (address == NULL)
        return;

    d1_reg_update_bits(address, mask, value);
}


/* ============================================================================
 * Field Operations
 * ========================================================================== */

uint32_t register_get_field32(volatile uint32_t *address,
                              uint32_t mask,
                              unsigned int shift)
{
    uint32_t reg;

    if (address == NULL)
        return 0;

    reg = register_read32(address);

    return D1_FIELD_GET32(reg, mask, shift);
}


void register_set_field32(volatile uint32_t *address,
                          uint32_t mask,
                          unsigned int shift,
                          uint32_t value)
{
    if (address == NULL)
        return;

    register_update_bits32(address,
                           mask << shift,
                           value << shift);
}


/* ============================================================================
 * Register Status
 * ========================================================================== */

bool register_test_bits32(volatile uint32_t *address,
                          uint32_t mask)
{
    uint32_t value;

    if (address == NULL)
        return false;

    value = register_read32(address);

    return (value & mask) == mask;
}
