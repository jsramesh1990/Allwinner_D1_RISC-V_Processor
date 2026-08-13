Resulting src/ structure
src/
├── bit_operations.c
├── bit_operations.h
├── main.c
├── register_access.c
└── register_access.h

And the architecture becomes:

                    main.c
                      │
          ┌───────────┴───────────┐
          ▼                       ▼
 bit_operations.c          register_access.c
          │                       │
          ▼                       ▼
 bit_operations.h          register_access.h
          │                       │
          └───────────┬───────────┘
                      ▼
              d1_registers.h
                      │
        ┌─────────────┼─────────────┐
        ▼             ▼             ▼
      SET           CLEAR         TOGGLE
        │             │             │
        └─────────────┼─────────────┘
                      ▼
               Register / Field
                      │
                      ▼
              Allwinner D1
                RISC-V CPU
One structural change I strongly recommend

Once the project grows, change:

src/
├── bit_operations.h
└── register_access.h

to:

include/
├── d1_registers.h
├── bit_operations.h
└── register_access.h

src/
├── bit_operations.c
├── register_access.c
└── main.c

That is the more standard Embedded C / BSP-style repository structure: headers/API definitions under include/, implementations under src/, examples under examples/, and hardware-specific definitions separated from application logic.
