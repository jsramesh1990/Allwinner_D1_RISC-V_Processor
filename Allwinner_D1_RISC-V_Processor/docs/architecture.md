# Allwinner D1 RISC-V Processor - Architecture

## 1. Overview

The Allwinner D1 is a 64-bit RISC-V based application processor designed for embedded Linux systems. The D1 integrates a RISC-V C906 CPU core along with memory controllers, GPIO, timers, UART, SPI, I2C, PWM, ADC, and other peripheral interfaces.

This project uses the Allwinner D1 platform to demonstrate bit manipulation, register operations, bit masking, and hardware-oriented programming concepts.

---

## 2. High-Level Architecture

```text
+-------------------------------------------------------+
|                 User Application                      |
|                                                       |
|       Bit Manipulation C Application                  |
|                                                       |
|  SET BIT | CLEAR BIT | TOGGLE BIT | CHECK BIT        |
+---------------------------+---------------------------+
                            |
                            v
+-------------------------------------------------------+
|                    Linux User Space                   |
|                                                       |
|              C Library / System Calls                |
+---------------------------+---------------------------+
                            |
                            v
+-------------------------------------------------------+
|                    Linux Kernel                       |
|                                                       |
|   GPIO Driver | Device Drivers | Memory Management   |
+---------------------------+---------------------------+
                            |
                            v
+-------------------------------------------------------+
|              Allwinner D1 Hardware                   |
|                                                       |
|   RISC-V C906 CPU | GPIO | UART | SPI | I2C | Timer |
+---------------------------+---------------------------+
                            |
                            v
+-------------------------------------------------------+
|                   Physical Hardware                  |
|                                                       |
|                GPIO / LED / Peripheral               |
+-------------------------------------------------------+
3. Processor Architecture

The Allwinner D1 uses a RISC-V based C906 processor core.

+--------------------------------------+
|            Allwinner D1             |
|                                      |
|       +----------------------+       |
|       |    RISC-V C906 CPU  |       |
|       |                      |       |
|       |   64-bit RISC-V     |       |
|       +----------+-----------+       |
|                  |                   |
|       +----------+-----------+       |
|       |                      |       |
|       v                      v       |
|    Memory                 Peripherals|
|       |                      |       |
|       v                      v       |
|     DDR/ROM       GPIO / UART / SPI |
|                    I2C / PWM / Timer |
+--------------------------------------+
4. CPU and Memory

The CPU executes the compiled C application instructions.

C Source
   |
   v
GCC
   |
   v
RISC-V Executable
   |
   v
CPU
   |
   +----> Registers
   |
   +----> Cache
   |
   +----> DDR Memory
   |
   +----> Peripheral Registers

Bit manipulation operations are performed using CPU registers and memory operands.

5. Bit Manipulation Architecture

The application performs operations on integer values or hardware register values.

                Register Value
                      |
          +-----------+-----------+
          |           |           |
          v           v           v
       SET BIT     CLEAR BIT    TOGGLE BIT
          |           |           |
          +-----------+-----------+
                      |
                      v
                  CHECK BIT
                      |
                      v
                 Result Value
Set Bit
reg |= (1UL << bit);

Sets the selected bit to 1.

Clear Bit
reg &= ~(1UL << bit);

Clears the selected bit to 0.

Toggle Bit
reg ^= (1UL << bit);

Changes 0 to 1 or 1 to 0.

Check Bit
result = (reg >> bit) & 1UL;

Reads the selected bit.

6. Register-Level Concept

Embedded processors control peripherals through hardware registers.

CPU
 |
 | Read / Write
 v
+-----------------------+
| Peripheral Register   |
|                       |
| 31 .............. 0   |
|  |   |    |       |   |
|  |   |    |       +--- Bit 0
|  |   |    +----------- Bit n
|  |   +---------------- Register Field
|  +-------------------- Control Bits
+-----------------------+
          |
          v
      Peripheral

A register can contain multiple control and status fields.

Bit masking allows individual fields to be modified without changing unrelated bits.

7. GPIO Architecture

For hardware testing, GPIO can be used to observe the effect of bit operations.

+------------------+
| RISC-V C906 CPU  |
+--------+---------+
         |
         v
+------------------+
| Linux GPIO Layer |
+--------+---------+
         |
         v
+------------------+
| GPIO Controller  |
+--------+---------+
         |
         v
+------------------+
| GPIO Pin         |
+--------+---------+
         |
         v
       LED

A GPIO control register can contain multiple bit fields controlling:

GPIO direction
GPIO output value
GPIO input state
Pull-up / pull-down configuration
Pin multiplexing
8. Software Architecture
+-----------------------------------+
|           main.c                  |
|                                   |
| Test / User Interface             |
+----------------+------------------+
                 |
                 v
+-----------------------------------+
|       bit_operations.c            |
|                                   |
| Set / Clear / Toggle / Check      |
+----------------+------------------+
                 |
                 v
+-----------------------------------+
|       register_access.c           |
|                                   |
| Register Read / Write Operations  |
+----------------+------------------+
                 |
                 v
+-----------------------------------+
|       Linux / Hardware            |
+-----------------------------------+
9. Build Architecture
             Source Files
                  |
        +---------+---------+
        |                   |
     main.c        bit_operations.c
        |                   |
        +---------+---------+
                  |
                  v
             RISC-V GCC
                  |
                  v
              Object Files
                  |
                  v
                Linker
                  |
                  v
          Executable Binary
                  |
                  v
          Allwinner D1 Linux
10. Makefile Flow

The Makefile automates compilation.

make
 |
 +--> Compile main.c
 |
 +--> Compile bit_operations.c
 |
 +--> Generate object files
 |
 +--> Link object files
 |
 +--> Generate executable
 |
 +--> Ready for execution

Example:

make

Clean the generated files:

make clean
11. Runtime Flow
Power ON
   |
   v
Allwinner D1 Boot
   |
   v
Bootloader
   |
   v
Linux Kernel
   |
   v
Root Filesystem
   |
   v
User Application
   |
   v
Bit Manipulation
   |
   +----> Set Bit
   |
   +----> Clear Bit
   |
   +----> Toggle Bit
   |
   +----> Check Bit
   |
   v
Result / Hardware Operation
12. Project Data Flow
Input Register Value
        |
        v
     Bit Mask
        |
        v
Bit Manipulation Operation
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
Updated Register Value
        |
        v
Output / Hardware State
13. Key Concepts Demonstrated
RISC-V processor architecture
C bitwise operators
Bit masking
Register manipulation
Memory-mapped I/O concepts
GPIO control
Linux user-space programming
Makefile-based compilation
Cross-compilation
Embedded Linux architecture
Hardware-oriented C programming

**This `architecture.md` should be the technical architecture document.** Then your `hardware.md` can focus specifically on the **D1 board, pinout, GPIO, memory, interfaces, and hardware connections**, while `software_flow.md` can focus on the **source → GCC → Makefile → executable → D1 Linux → hardware** flow.
