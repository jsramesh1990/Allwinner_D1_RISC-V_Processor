/*
 * ============================================================================
 * Allwinner D1 RISC-V Processor
 * bit_operations.h
 *
 * High-level bit manipulation API.
 * ============================================================================
 */

#ifndef BIT_OPERATIONS_H
#define BIT_OPERATIONS_H

#include <stdint.h>
#include <stdbool.h>

/* --------------------------------------------------------------------------
 * Single-bit operations
 * -------------------------------------------------------------------------- */

int bit_set_u32(uint32_t *value, unsigned int bit);

int bit_clear_u32(uint32_t *value, unsigned int bit);

int bit_toggle_u32(uint32_t *value, unsigned int bit);

int bit_check_u32(uint32_t value,
                 unsigned int bit,
                 bool *result);


/* --------------------------------------------------------------------------
 * 64-bit operations
 * -------------------------------------------------------------------------- */

int bit_set_u64(uint64_t *value, unsigned int bit);

int bit_clear_u64(uint64_t *value, unsigned int bit);

int bit_toggle_u64(uint64_t *value, unsigned int bit);

int bit_check_u64(uint64_t value,
                  unsigned int bit,
                  bool *result);


/* --------------------------------------------------------------------------
 * Mask operations
 * -------------------------------------------------------------------------- */

int bit_set_mask32(uint32_t *value,
                   uint32_t mask);

int bit_clear_mask32(uint32_t *value,
                     uint32_t mask);

int bit_toggle_mask32(uint32_t *value,
                      uint32_t mask);

bool bit_all_set32(uint32_t value,
                   uint32_t mask);

bool bit_any_set32(uint32_t value,
                   uint32_t mask);


/* --------------------------------------------------------------------------
 * Field operations
 * -------------------------------------------------------------------------- */

int bit_field_get32(uint32_t value,
                    uint32_t mask,
                    unsigned int shift,
                    uint32_t *result);

int bit_field_set32(uint32_t *value,
                    uint32_t mask,
                    unsigned int shift,
                    uint32_t field_value);


/* --------------------------------------------------------------------------
 * Utility functions
 * -------------------------------------------------------------------------- */

void bit_print_binary32(uint32_t value);

void bit_print_binary64(uint64_t value);

#endif /* BIT_OPERATIONS_H */
