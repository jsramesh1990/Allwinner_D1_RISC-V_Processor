#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "bit_operations.h"

static void test_set_single_bit(void)
{
    uint32_t value = 0;

    assert(bit_set_u32(&value, 0) == 0);
    assert(value == UINT32_C(0x00000001));

    assert(bit_set_u32(&value, 4) == 0);
    assert(value == UINT32_C(0x00000011));

    assert(bit_set_u32(&value, 31) == 0);
    assert(value == UINT32_C(0x80000011));
}

static void test_set_already_set_bit(void)
{
    uint32_t value = UINT32_C(0x00000008);

    assert(bit_set_u32(&value, 3) == 0);
    assert(value == UINT32_C(0x00000008));
}

static void test_set_multiple_bits(void)
{
    uint32_t value = 0;

    assert(bit_set_mask32(
               &value,
               UINT32_C(0x0000002A)) == 0);

    assert(value == UINT32_C(0x0000002A));
}

static void test_invalid_bit(void)
{
    uint32_t value = 0;

    assert(bit_set_u32(&value, 32) == -1);
    assert(value == 0);
}

static void test_null_pointer(void)
{
    assert(bit_set_u32(NULL, 5) == -1);
}

int main(void)
{
    printf("[TEST] SET BIT\n");

    test_set_single_bit();
    test_set_already_set_bit();
    test_set_multiple_bits();
    test_invalid_bit();
    test_null_pointer();

    printf("[PASS] SET BIT tests completed\n");

    return 0;
}
