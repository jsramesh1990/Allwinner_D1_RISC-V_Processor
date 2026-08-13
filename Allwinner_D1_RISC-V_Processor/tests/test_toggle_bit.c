#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "bit_operations.h"

static void test_toggle_clear_to_set(void)
{
    uint32_t value = 0;

    assert(bit_toggle_u32(&value, 5) == 0);
    assert(value == UINT32_C(0x00000020));
}

static void test_toggle_set_to_clear(void)
{
    uint32_t value = UINT32_C(0x00000020);

    assert(bit_toggle_u32(&value, 5) == 0);
    assert(value == 0);
}

static void test_double_toggle(void)
{
    uint32_t value = UINT32_C(0x00000055);
    uint32_t original = value;

    assert(bit_toggle_u32(&value, 3) == 0);
    assert(bit_toggle_u32(&value, 3) == 0);

    assert(value == original);
}

static void test_toggle_multiple_bits(void)
{
    uint32_t value = 0;

    uint32_t mask =
        UINT32_C(0x0000002A);

    assert(bit_toggle_mask32(&value, mask) == 0);

    assert(value == mask);

    assert(bit_toggle_mask32(&value, mask) == 0);

    assert(value == 0);
}

static void test_invalid_bit(void)
{
    uint32_t value = 0;

    assert(bit_toggle_u32(&value, 32) == -1);
    assert(value == 0);
}

static void test_null_pointer(void)
{
    assert(bit_toggle_u32(NULL, 5) == -1);
}

int main(void)
{
    printf("[TEST] TOGGLE BIT\n");

    test_toggle_clear_to_set();
    test_toggle_set_to_clear();
    test_double_toggle();
    test_toggle_multiple_bits();
    test_invalid_bit();
    test_null_pointer();

    printf("[PASS] TOGGLE BIT tests completed\n");

    return 0;
}
