/*
 * ============================================================================
 * Allwinner D1 RISC-V Processor
 * d1_registers.h
 *
 * Central register and bit manipulation definitions.
 *
 * This header provides:
 *   - Generic bit macros
 *   - Bit masks
 *   - Field manipulation macros
 *   - Register read/write helpers
 *   - 32-bit / 64-bit register types
 *   - Compile-time constants
 *
 * NOTE:
 * Actual Allwinner D1 peripheral physical addresses must be taken from
 * the official D1 documentation, board documentation, device tree, or
 * appropriate Linux kernel headers.
 * ============================================================================
 */

#ifndef D1_REGISTERS_H
#define D1_REGISTERS_H

#include <stdint.h>
#include <stddef.h>

/* ============================================================================
 * Basic Types
 * ========================================================================== */

typedef volatile uint8_t  d1_reg8_t;
typedef volatile uint16_t d1_reg16_t;
typedef volatile uint32_t d1_reg32_t;
typedef volatile uint64_t d1_reg64_t;


/* ============================================================================
 * Bit Definitions
 * ========================================================================== */

/*
 * Single-bit masks.
 *
 * Example:
 *
 * BIT32(5)
 *
 * Result:
 *
 * 00000000 00000000 00000000 00100000
 */

#define D1_BIT32(n) \
    (UINT32_C(1) << (n))

#define D1_BIT64(n) \
    (UINT64_C(1) << (n))


/* ============================================================================
 * Bit Set / Clear / Toggle
 * ========================================================================== */

/*
 * SET
 *
 * Changes selected bit to 1.
 */

#define D1_SET_BIT32(reg, bit) \
    ((reg) |= D1_BIT32(bit))

#define D1_SET_BIT64(reg, bit) \
    ((reg) |= D1_BIT64(bit))


/*
 * CLEAR
 *
 * Changes selected bit to 0.
 */

#define D1_CLEAR_BIT32(reg, bit) \
    ((reg) &= ~D1_BIT32(bit))

#define D1_CLEAR_BIT64(reg, bit) \
    ((reg) &= ~D1_BIT64(bit))


/*
 * TOGGLE
 *
 * 0 -> 1
 * 1 -> 0
 */

#define D1_TOGGLE_BIT32(reg, bit) \
    ((reg) ^= D1_BIT32(bit))

#define D1_TOGGLE_BIT64(reg, bit) \
    ((reg) ^= D1_BIT64(bit))


/* ============================================================================
 * Bit Test
 * ========================================================================== */

#define D1_IS_BIT_SET32(reg, bit) \
    (((reg) & D1_BIT32(bit)) != 0U)

#define D1_IS_BIT_SET64(reg, bit) \
    (((reg) & D1_BIT64(bit)) != 0U)


#define D1_IS_BIT_CLEAR32(reg, bit) \
    (((reg) & D1_BIT32(bit)) == 0U)

#define D1_IS_BIT_CLEAR64(reg, bit) \
    (((reg) & D1_BIT64(bit)) == 0U)


/* ============================================================================
 * Mask Operations
 * ========================================================================== */

/*
 * Set multiple bits.
 */

#define D1_SET_MASK32(reg, mask) \
    ((reg) |= (uint32_t)(mask))

#define D1_SET_MASK64(reg, mask) \
    ((reg) |= (uint64_t)(mask))


/*
 * Clear multiple bits.
 */

#define D1_CLEAR_MASK32(reg, mask) \
    ((reg) &= ~(uint32_t)(mask))

#define D1_CLEAR_MASK64(reg, mask) \
    ((reg) &= ~(uint64_t)(mask))


/*
 * Toggle multiple bits.
 */

#define D1_TOGGLE_MASK32(reg, mask) \
    ((reg) ^= (uint32_t)(mask))

#define D1_TOGGLE_MASK64(reg, mask) \
    ((reg) ^= (uint64_t)(mask))


/*
 * Check whether ALL bits in a mask are set.
 */

#define D1_ALL_BITS_SET32(reg, mask) \
    (((reg) & (uint32_t)(mask)) == (uint32_t)(mask))

#define D1_ALL_BITS_SET64(reg, mask) \
    (((reg) & (uint64_t)(mask)) == (uint64_t)(mask))


/*
 * Check whether ANY bit in a mask is set.
 */

#define D1_ANY_BIT_SET32(reg, mask) \
    (((reg) & (uint32_t)(mask)) != 0U)

#define D1_ANY_BIT_SET64(reg, mask) \
    (((reg) & (uint64_t)(mask)) != 0U)


/* ============================================================================
 * Field Operations
 * ========================================================================== */

/*
 * Generate a field mask.
 *
 * Example:
 *
 * D1_GEN_MASK32(4)
 *
 * Result:
 *
 * 0x0000000F
 */

#define D1_GEN_MASK32(width) \
    ((UINT32_C(1) << (width)) - UINT32_C(1))

#define D1_GEN_MASK64(width) \
    ((UINT64_C(1) << (width)) - UINT64_C(1))


/*
 * Extract field.
 *
 * Example:
 *
 * register = 0x000000A0
 *
 * mask  = 0x0F
 * shift = 4
 */

#define D1_FIELD_GET32(reg, mask, shift) \
    (((uint32_t)(reg) >> (shift)) & (uint32_t)(mask))

#define D1_FIELD_GET64(reg, mask, shift) \
    (((uint64_t)(reg) >> (shift)) & (uint64_t)(mask))


/*
 * Prepare a field value before insertion.
 */

#define D1_FIELD_PREP32(value, mask, shift) \
    (((uint32_t)(value) & (uint32_t)(mask)) << (shift))

#define D1_FIELD_PREP64(value, mask, shift) \
    (((uint64_t)(value) & (uint64_t)(mask)) << (shift))


/*
 * Replace a field inside a register.
 *
 * Existing field value is cleared first.
 */

#define D1_FIELD_MODIFY32(reg, mask, shift, value)       \
    do {                                                  \
        (reg) &= ~((uint32_t)(mask) << (shift));         \
        (reg) |= D1_FIELD_PREP32(value, mask, shift);    \
    } while (0)


#define D1_FIELD_MODIFY64(reg, mask, shift, value)       \
    do {                                                  \
        (reg) &= ~((uint64_t)(mask) << (shift));         \
        (reg) |= D1_FIELD_PREP64(value, mask, shift);    \
    } while (0)


/* ============================================================================
 * Register Access Helpers
 * ========================================================================== */

/*
 * Read a 32-bit register.
 */

static inline uint32_t d1_read32(const volatile uint32_t *addr)
{
    return *addr;
}


/*
 * Write a 32-bit register.
 */

static inline void d1_write32(volatile uint32_t *addr,
                              uint32_t value)
{
    *addr = value;
}


/*
 * Read a 64-bit register.
 */

static inline uint64_t d1_read64(const volatile uint64_t *addr)
{
    return *addr;
}


/*
 * Write a 64-bit register.
 */

static inline void d1_write64(volatile uint64_t *addr,
                              uint64_t value)
{
    *addr = value;
}


/* ============================================================================
 * Register Read / Modify / Write Helpers
 * ========================================================================== */

/*
 * Set bits in a hardware register.
 */

static inline void d1_reg_set_bits(volatile uint32_t *addr,
                                   uint32_t mask)
{
    *addr |= mask;
}


/*
 * Clear bits in a hardware register.
 */

static inline void d1_reg_clear_bits(volatile uint32_t *addr,
                                     uint32_t mask)
{
    *addr &= ~mask;
}


/*
 * Toggle bits in a hardware register.
 */

static inline void d1_reg_toggle_bits(volatile uint32_t *addr,
                                      uint32_t mask)
{
    *addr ^= mask;
}


/*
 * Read-modify-write operation.
 */

static inline void d1_reg_update_bits(volatile uint32_t *addr,
                                      uint32_t mask,
                                      uint32_t value)
{
    uint32_t reg;

    reg = *addr;

    reg &= ~mask;
    reg |= (value & mask);

    *addr = reg;
}


/* ============================================================================
 * Example Register Structure
 * ========================================================================== */

/*
 * Generic register layout example.
 *
 * This is NOT a real D1 peripheral register map.
 *
 * It is only a software model for register-oriented examples.
 */

typedef struct
{
    d1_reg32_t CONTROL;
    d1_reg32_t STATUS;
    d1_reg32_t CONFIG;
    d1_reg32_t DATA;

} d1_example_regs_t;


/* ============================================================================
 * Example CONTROL Register Fields
 * ========================================================================== */

/*
 * CONTROL register:
 *
 * Bit 0       : ENABLE
 * Bits [2:1]  : MODE
 * Bits [5:3]  : SPEED
 * Bit 7       : INTERRUPT ENABLE
 */

#define D1_CTRL_ENABLE_BIT       0U
#define D1_CTRL_MODE_SHIFT       1U
#define D1_CTRL_MODE_MASK        UINT32_C(0x03)

#define D1_CTRL_SPEED_SHIFT      3U
#define D1_CTRL_SPEED_MASK       UINT32_C(0x07)

#define D1_CTRL_IRQ_ENABLE_BIT   7U


#define D1_CTRL_ENABLE \
    D1_BIT32(D1_CTRL_ENABLE_BIT)

#define D1_CTRL_IRQ_ENABLE \
    D1_BIT32(D1_CTRL_IRQ_ENABLE_BIT)


/* ============================================================================
 * Example STATUS Register Fields
 * ========================================================================== */

/*
 * STATUS register:
 *
 * Bit 0 : READY
 * Bit 1 : BUSY
 * Bit 2 : ERROR
 * Bit 3 : INTERRUPT
 */

#define D1_STATUS_READY_BIT       0U
#define D1_STATUS_BUSY_BIT        1U
#define D1_STATUS_ERROR_BIT       2U
#define D1_STATUS_IRQ_BIT         3U

#define D1_STATUS_READY \
    D1_BIT32(D1_STATUS_READY_BIT)

#define D1_STATUS_BUSY \
    D1_BIT32(D1_STATUS_BUSY_BIT)

#define D1_STATUS_ERROR \
    D1_BIT32(D1_STATUS_ERROR_BIT)

#define D1_STATUS_IRQ \
    D1_BIT32(D1_STATUS_IRQ_BIT)


/* ============================================================================
 * Example Register Validation
 * ========================================================================== */

#define D1_IS_VALID_BIT32(bit) \
    ((bit) < 32U)

#define D1_IS_VALID_BIT64(bit) \
    ((bit) < 64U)


/* ============================================================================
 * Memory Barrier Helpers
 * ========================================================================== */

/*
 * These compiler barriers prevent the compiler from freely reordering
 * memory operations around the barrier.
 *
 * For actual device I/O ordering on RISC-V, use the appropriate Linux
 * kernel primitives / architecture-specific mechanisms rather than relying
 * solely on this macro.
 */

#define D1_COMPILER_BARRIER() \
    __asm__ __volatile__("" ::: "memory")


/* ============================================================================
 * End of Header
 * ========================================================================== */

#endif /* D1_REGISTERS_H */
