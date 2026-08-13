/*
 * ============================================================================
 * Allwinner D1 RISC-V Processor
 * register_access.h
 * ============================================================================
 */

#ifndef REGISTER_ACCESS_H
#define REGISTER_ACCESS_H

#include <stdint.h>
#include <stdbool.h>


/* ============================================================================
 * Register Operations
 * ========================================================================== */

uint32_t register_read32(volatile uint32_t *address);

void register_write32(volatile uint32_t *address,
                      uint32_t value);

void register_set_bits32(volatile uint32_t *address,
                         uint32_t mask);

void register_clear_bits32(volatile uint32_t *address,
                           uint32_t mask);

void register_toggle_bits32(volatile uint32_t *address,
                            uint32_t mask);

void register_update_bits32(volatile uint32_t *address,
                            uint32_t mask,
                            uint32_t value);


/* ============================================================================
 * Register Field Operations
 * ========================================================================== */

uint32_t register_get_field32(volatile uint32_t *address,
                              uint32_t mask,
                              unsigned int shift);

void register_set_field32(volatile uint32_t *address,
                          uint32_t mask,
                          unsigned int shift,
                          uint32_t value);


/* ============================================================================
 * Register Status
 * ========================================================================== */

bool register_test_bits32(volatile uint32_t *address,
                          uint32_t mask);

#endif /* REGISTER_ACCESS_H */
