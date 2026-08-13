#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "bit_operations.h"

static void test_check_set_bit(void)
{
    uint32_t value = UINT32_C(0x00000020);
    bool result = false;

    assert(bit_check_u32(
               value,
               5,
               &result) == 0);

    assert(result == true);
}

static void test_check_clear_bit(void)
{
    uint32_t value = UINT32_C(0x00000020);
    bool result = true;

    assert(bit_check_u32(
               value,
               4,
               &result) == 0);

    assert(result == false);
}

static void test_check_multiple_bits(void)
{
    uint32_t value =
        UINT32_C(0x0000002A);

    uint32_t mask =
        UINT32_C(0x0000002A);

    assert(bit_all_set32(value, mask) == true);
}

static void test_check_any_bit(void)
{
    uint32_t value =
        UINT32_C(0x00000008);

    uint32_t mask =
        UINT32_C(0x00000028);

    assert(bit_any_set32(value, mask) == true);
}

static void test_check_no_bits(void)
{
    uint32_t value = 0;

    uint32_t mask =
        UINT32_C(0x0000002A);

    assert(bit_any_set32(value, mask) == false);
}

static void test_invalid_bit(void)
{
    uint32_t value = 0;
    bool result = false;

    assert(bit_check_u32(
               value,
               32,
               &result) == -1);
}

static void test_null_result(void)
{
    uint32_t value = UINT32_C(0x20);

    assert(bit_check_u32(
               value,
               5,
               NULL) == -1);
}

int main(void)
{
    printf("[TEST] CHECK BIT\n");

    test_check_set_bit();
    test_check_clear_bit();
    test_check_multiple_bits();
    test_check_any_bit();
    test_check_no_bits();
    test_invalid_bit();
    test_null_result();

    printf("[PASS] CHECK BIT tests completed\n");

    return 0;
}
