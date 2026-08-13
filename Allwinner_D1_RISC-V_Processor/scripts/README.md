Make the scripts executable

From the project root:

chmod +x scripts/build.sh
chmod +x scripts/clean.sh
chmod +x scripts/run.sh

Verify:

ls -l scripts/

You should see:

-rwxr-xr-x build.sh
-rwxr-xr-x clean.sh
-rwxr-xr-x run.sh
5. Usage
Build
./scripts/build.sh
Debug build
./scripts/build.sh debug
Clean
./scripts/clean.sh
Run main program
./scripts/run.sh
Run bit-mask example
./scripts/run.sh bit_mask
Run SET BIT
./scripts/run.sh set_bit
Run CLEAR BIT
./scripts/run.sh clear_bit
Run TOGGLE BIT
./scripts/run.sh toggle_bit
Run CHECK BIT
./scripts/run.sh check_bit
Run SHIFT example
./scripts/run.sh shift
6. Recommended final project structure

Your GitHub repository is now becoming nicely organized:

Allwinner_D1_RISC-V_Processor/
│
├── README.md
├── Makefile
│
├── include/
│   └── d1_registers.h
│
├── src/
│   ├── main.c
│   ├── bit_operations.c
│   └── register_access.c
│
├── examples/
│   ├── bit_mask_example.c
│   ├── set_bit_example.c
│   ├── clear_bit_example.c
│   ├── toggle_bit_example.c
│   ├── check_bit_example.c
│   └── shift_operation_example.c
│
├── tests/
│   ├── test_bit_operations.c
│   └── test_register_access.c
│
├── scripts/
│   ├── build.sh
│   ├── clean.sh
│   └── run.sh
│
├── docs/
│   ├── architecture.md
│   ├── hardware.md
│   ├── software_flow.md
│   └── testing.md
│
└── bin/
    └── ...

The resulting workflow is:

                 Developer
                     │
                     ▼
              ┌─────────────┐
              │  Source C   │
              └──────┬──────┘
                     │
                     ▼
              scripts/build.sh
                     │
                     ▼
                  Makefile
                     │
                     ▼
              RISC-V Compiler
                     │
                     ▼
                   bin/
                     │
          ┌──────────┼──────────┐
          ▼          ▼          ▼
       run.sh      GDB       D1 Board
          │
          ▼
     Test Examples
          │
          ▼
 SET → CLEAR → TOGGLE → CHECK → SHIFT

This gives the repository a much more Embedded Linux/RISC-V engineering style rather than looking like a collection of simple C programs.
