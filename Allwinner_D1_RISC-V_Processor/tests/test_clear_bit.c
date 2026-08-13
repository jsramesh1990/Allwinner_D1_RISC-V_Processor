#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "bit_operations.h"

static void test_clear_single_bit(void)
{
    uint32_t value = UINT32_C(0xFFFFFFFF);

    assert(bit_clear_u32(&value, 0) == 0);
    assert(value == UINT32_C(0xFFFFFFFE));

    assert(bit_clear_u32(&value, 4) == 0);
    assert(value == UINT32_C(0xFFFFFFEE));

    assert(bit_clear_u32(&value, 31) == 0);
    assert(value == UINT32_C(0x7FFFFFEE));
}

static void test_clear_already_clear_bit(void)
{
    uint32_t value = UINT32_C(0x00000008);

    assert(bit_clear_u32(&value, 0) == 0);
    assert(value == UINT32_C(0x00000008));
}

static void test_clear_multiple_bits(void)
{
    uint32_t value = UINT32_C(0xFFFFFFFF);

    assert(bit_clear_mask32(
               &value,
               UINT32_C(0x0000002A)) == 0);

    assert(value == UINT32_C(0xFFFFFFD5));
}

static void test_invalid_bit(void)
{
    uint32_t value = UINT32_C(0xFFFFFFFF);

    assert(bit_clear_u32(&value, 32) == -1);

    assert(value == UINT32_C(0xFFFFFFFF));
}

static void test_null_pointer(void)
{
    assert(bit_clear_u32(NULL, 10) == -1);
}

int main(void)
{
    printf("[TEST] CLEAR BIT\n");

    test_clear_single_bit();
    test_clear_already_clear_bit();
    test_clear_multiple_bits();
    test_invalid_bit();
    test_null_pointer();

    printf("[PASS] CLEAR BIT tests completed\n");

    return 0;
}
