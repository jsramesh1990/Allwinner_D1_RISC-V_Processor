# Allwinner D1 RISC-V Processor - Software Flow

## 1. Overview

This document describes the software development and execution flow for the Allwinner D1 RISC-V processor project.

The project demonstrates bit manipulation operations using C and extends the concepts toward processor registers, memory-mapped I/O, GPIO, and Embedded Linux.

---

## 2. Complete Software Flow

```text
                 Developer PC
                      |
                      v
              C Source Code
                      |
                      v
                   Makefile
                      |
                      v
              RISC-V GCC Toolchain
                      |
                      v
                Object Files
                      |
                      v
                   Linker
                      |
                      v
              RISC-V Executable
                      |
                      v
              Transfer to D1
                      |
                      v
             Allwinner D1 Linux
                      |
                      v
              Execute Application
                      |
                      v
             Bit Manipulation
                      |
          +-----------+-----------+
          |           |           |
          v           v           v
       SET BIT    CLEAR BIT    TOGGLE BIT
          |           |           |
          +-----------+-----------+
                      |
                      v
               Register / GPIO
                      |
                      v
                 Hardware
3. Development Environment

The development environment consists of:

Developer PC
    |
    +-- Linux
    |
    +-- GCC / RISC-V GCC
    |
    +-- Make
    |
    +-- Git
    |
    +-- GDB
    |
    +-- Serial Terminal

Typical tools:

Tool	Purpose
GCC	C compilation
RISC-V GCC	RISC-V cross compilation
Make	Build automation
GDB	Debugging
Git	Version control
SSH	Application transfer
Serial Terminal	D1 console/debugging
4. Source Code Flow

The source code is divided into multiple modules.

src/
 |
 +-- main.c
 |      |
 |      +--> Application entry point
 |
 +-- bit_operations.c
 |      |
 |      +--> SET
 |      +--> CLEAR
 |      +--> TOGGLE
 |      +--> CHECK
 |
 +-- register_access.c
        |
        +--> Register access
        +--> Hardware interaction

Header files provide the required declarations and macros.

include/
 |
 +-- bit_operations.h
 |
 +-- d1_registers.h
5. Bit Manipulation Flow

The basic software operation follows this sequence:

Input Value
     |
     v
Select Bit Number
     |
     v
Generate Bit Mask
     |
     v
Perform Operation
     |
     +---- SET
     |
     +---- CLEAR
     |
     +---- TOGGLE
     |
     +---- CHECK
     |
     v
Updated Value
6. Set Bit

The SET operation changes the selected bit to 1.

reg |= (1UL << bit);

Flow:

Register
   |
   v
Generate Mask
   |
   v
1 << bit
   |
   v
OR Operation
   |
   v
Selected Bit = 1

Example:

Before:

00000000

Set Bit 3:

00000000
00001000
--------
00001000
7. Clear Bit

The CLEAR operation changes the selected bit to 0.

reg &= ~(1UL << bit);

Flow:

Register
   |
   v
Generate Mask
   |
   v
1 << bit
   |
   v
Invert Mask
   |
   v
AND Operation
   |
   v
Selected Bit = 0

Example:

Before:

00001000

Clear Bit 3:

00001000
11110111
--------
00000000
8. Toggle Bit

The TOGGLE operation changes the selected bit.

reg ^= (1UL << bit);

Flow:

Register
   |
   v
Generate Mask
   |
   v
1 << bit
   |
   v
XOR Operation
   |
   v
0 -> 1
1 -> 0

Example:

Before:

00001000

Toggle Bit 3:

00001000
00001000
--------
00000000

Toggle again:

00000000
00001000
--------
00001000
9. Check Bit

The CHECK operation determines whether a selected bit is 0 or 1.

result = (reg >> bit) & 1UL;

Flow:

Register
   |
   v
Right Shift
   |
   v
Selected Bit -> Bit 0
   |
   v
AND 1
   |
   v
Result

Result:

0 -> Bit is CLEAR

1 -> Bit is SET
10. Makefile Build Flow

The Makefile automates the complete compilation process.

                 make
                  |
                  v
          Read Makefile
                  |
                  v
          Compile main.c
                  |
                  v
       Compile bit_operations.c
                  |
                  v
       Compile register_access.c
                  |
                  v
             Object Files
                  |
                  v
                Link
                  |
                  v
          RISC-V Executable

Example:

make

Clean build files:

make clean
11. Native vs Cross Compilation

There are two possible development models.

Native Compilation

If compilation is performed directly on the D1 Linux system:

D1 Linux
   |
   v
GCC
   |
   v
RISC-V Executable

Example:

gcc main.c bit_operations.c -o bit_manipulation
Cross Compilation

For development on a PC, use a RISC-V cross compiler.

Developer PC
     |
     | RISC-V GCC
     v
RISC-V Binary
     |
     v
Transfer
     |
     v
Allwinner D1
     |
     v
Linux
     |
     v
Execute

The exact compiler prefix depends on the selected D1 Linux toolchain.

12. Binary Transfer Flow

After compilation, the executable can be transferred to the D1.

Developer PC
     |
     | SCP / USB / Network
     v
Allwinner D1
     |
     v
/home/user/
     |
     v
bit_manipulation

Example using SSH/SCP:

scp bit_manipulation user@<D1_IP>:/home/user/

Then connect to the board:

ssh user@<D1_IP>

Execute:

./bit_manipulation
13. Runtime Flow

Once the application is executed:

Linux Shell
    |
    v
./bit_manipulation
    |
    v
Program Loader
    |
    v
ELF Executable
    |
    v
Process Creation
    |
    v
main()
    |
    v
Bit Operations
    |
    v
Output
14. Application Architecture
+-------------------------------------+
|             main.c                  |
|                                     |
|  Application / Test Control         |
+------------------+------------------+
                   |
                   v
+-------------------------------------+
|        bit_operations.c             |
|                                     |
| SET | CLEAR | TOGGLE | CHECK        |
+------------------+------------------+
                   |
                   v
+-------------------------------------+
|        register_access.c            |
|                                     |
| Register Read / Write               |
+------------------+------------------+
                   |
                   v
+-------------------------------------+
|          Linux / Hardware           |
+-------------------------------------+
15. Linux Interaction

When the project is extended toward hardware control, the application interacts with Linux interfaces.

User Application
       |
       v
System Call / Linux API
       |
       v
Linux Kernel
       |
       v
Device Driver
       |
       v
Hardware Controller
       |
       v
D1 Peripheral

Examples of Linux interfaces that may be used include:

/sys
/dev
/proc
ioctl()
mmap()

The appropriate interface depends on the hardware and driver implementation.

16. Memory-Mapped I/O Flow

For register-level hardware work, the processor accesses peripheral registers through memory-mapped addresses.

RISC-V CPU
    |
    | Read / Write
    v
Memory Address
    |
    v
Peripheral Register
    |
    v
GPIO / UART / SPI / I2C
    |
    v
Hardware

Conceptually:

register_value |= (1UL << bit);

can be used to modify a specific bit in a register value.

For actual hardware register access, the register address and access method must match the D1 hardware documentation and Linux architecture.

17. GPIO Software Flow

The project can be extended to GPIO testing.

C Application
      |
      v
GPIO Configuration
      |
      v
GPIO Driver / Interface
      |
      v
D1 GPIO Controller
      |
      v
GPIO Register
      |
      v
GPIO Pin
      |
      v
LED / External Device

Example concept:

SET BIT
   |
   v
GPIO Output = HIGH
   |
   v
LED ON

and:

CLEAR BIT
   |
   v
GPIO Output = LOW
   |
   v
LED OFF
18. Debugging Flow

Debugging can be performed at multiple levels.

Application
    |
    +--> printf()
    |
    +--> Serial Console
    |
    +--> dmesg
    |
    +--> GDB
    |
    +--> Register Inspection
    |
    v
Hardware Validation

Useful commands:

dmesg
uname -a
file bit_manipulation
gdb ./bit_manipulation
19. Testing Flow

Testing starts with software and gradually moves toward hardware.

             Test
               |
               v
       +---------------+
       | Unit Testing  |
       +-------+-------+
               |
               v
       +---------------+
       | Linux Testing |
       +-------+-------+
               |
               v
       +---------------+
       | GPIO Testing  |
       +-------+-------+
               |
               v
       +---------------+
       | Register Test |
       +-------+-------+
               |
               v
       +---------------+
       | Hardware Test |
       +---------------+
20. Test Cases
Test	Input	Operation	Expected Result
Set Bit	0x00	Set bit 3	0x08
Clear Bit	0x08	Clear bit 3	0x00
Toggle Bit	0x00	Toggle bit 3	0x08
Toggle Bit	0x08	Toggle bit 3	0x00
Check Bit	0x08	Check bit 3	1
Check Bit	0x00	Check bit 3	0
21. Complete Development Cycle
                 START
                   |
                   v
             Write C Code
                   |
                   v
            Create Makefile
                   |
                   v
             Compile Code
                   |
                   v
             Build Binary
                   |
                   v
          Transfer to D1
                   |
                   v
             Run on Linux
                   |
                   v
          Execute Test Cases
                   |
                   v
          Verify Bit Operations
                   |
                   v
          Test GPIO / Hardware
                   |
                   v
              Debug Issues
                   |
                   v
             Update Code
                   |
                   +----------+
                              |
                              v
                         Rebuild/Test
22. GitHub Development Workflow
Developer
    |
    v
Edit Source
    |
    v
git add
    |
    v
git commit
    |
    v
git push
    |
    v
GitHub Repository

Typical commands:

git status
git add .
git commit -m "Add bit manipulation operations"
git push
23. Final Software Architecture
+------------------------------------------------------+
|                 Developer PC                         |
|                                                      |
| C Source | Makefile | GCC | GDB | Git               |
+---------------------------+--------------------------+
                            |
                            | Build / Transfer
                            v
+------------------------------------------------------+
|               Allwinner D1                          |
|                                                      |
| +--------------------------------------------------+ |
| |                   Linux                          | |
| |                                                  | |
| |  +--------------------------------------------+  | |
| |  |        Bit Manipulation Application        |  | |
| |  |                                            |  | |
| |  | SET | CLEAR | TOGGLE | CHECK | MASK       |  | |
| |  +---------------------+----------------------+  | |
| |                        |                         | |
| |                        v                         | |
| |               Linux Driver / API                 | |
| +------------------------+-------------------------+ |
|                          |                           |
|                          v                           |
|                D1 Hardware Peripherals               |
|                          |                           |
|                  GPIO / UART / SPI / I2C             |
+--------------------------+---------------------------+
                           |
                           v
                    Physical Hardware
24. Summary

The software flow demonstrates how a simple C bit manipulation program can be developed and extended into an Embedded Linux and RISC-V processor project.

C
 ↓
Bitwise Operations
 ↓
Bit Masks
 ↓
Makefile
 ↓
RISC-V Compilation
 ↓
Linux Application
 ↓
Linux Driver / API
 ↓
Register Operations
 ↓
GPIO
 ↓
Allwinner D1 Hardware

This layered approach provides a clear path from basic C programming to processor-level Embedded Linux development.
