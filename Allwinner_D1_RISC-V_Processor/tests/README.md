Test flow
             bit_operations.c
                    │
                    ▼
          ┌───────────────────┐
          │ Bit Manipulation  │
          │       APIs        │
          └─────────┬─────────┘
                    │
       ┌────────────┼────────────┐
       ▼            ▼            ▼
    SET TEST     CLEAR TEST   TOGGLE TEST
       │            │            │
       └────────────┼────────────┘
                    ▼
                CHECK TEST
                    │
                    ▼
              assert() checks
                    │
          ┌─────────┴─────────┐
          ▼                   ▼
        PASS                 FAIL

This gives you positive tests, boundary tests, mask tests, invalid-bit tests, and NULL-pointer tests rather than only checking the normal path.

One more useful test to add next is:

tests/
├── test_check_bit.c
├── test_clear_bit.c
├── test_set_bit.c
├── test_toggle_bit.c
└── test_shift_operation.c

That would complete the testing coverage for the five major operations in your project.
