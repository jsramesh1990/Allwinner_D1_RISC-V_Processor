# Allwinner D1 RISC-V Processor - Testing

## 1. Testing Overview

This document describes the testing and validation methodology for the Allwinner D1 RISC-V Bit Manipulation project.

The testing process validates:

- Set Bit operation
- Clear Bit operation
- Toggle Bit operation
- Check Bit operation
- Bit masking
- Shift operations
- Makefile build
- RISC-V executable
- Linux execution
- Register-oriented operations
- GPIO hardware interaction
- Error handling

---

## 2. Testing Strategy

The project follows a layered testing approach.

```text
                 Testing
                    |
        +-----------+-----------+
        |           |           |
        v           v           v
    Unit Test    Build Test   Hardware Test
        |           |           |
        v           v           v
    C Logic      Makefile      GPIO
        |           |           |
        +-----------+-----------+
                    |
                    v
              Linux Testing
                    |
                    v
             RISC-V Validation
3. Test Environment
Hardware
Allwinner D1 development board
USB/UART connection
Power supply
GPIO-capable pin
LED and resistor
Optional external peripheral
Software
Linux
GCC
RISC-V GCC toolchain
GNU Make
GDB
Git
Serial terminal
4. Test Levels

Testing is divided into multiple levels.

Level 1 → C Unit Testing
Level 2 → Build Testing
Level 3 → Linux Application Testing
Level 4 → RISC-V Execution Testing
Level 5 → Register Testing
Level 6 → GPIO Testing
Level 7 → Hardware Validation
5. Unit Testing

Unit tests verify individual bit manipulation functions independently.

5.1 Set Bit Test
Objective

Verify that the selected bit is changed from 0 to 1.

Operation
reg |= (1UL << bit);
Test
Input:
00000000

Set Bit 3:

00001000
Expected Result
0x00 → 0x08
Status
PASS
5.2 Clear Bit Test
Objective

Verify that the selected bit is changed from 1 to 0.

Operation
reg &= ~(1UL << bit);
Test
Input:
00001000

Clear Bit 3:

00000000
Expected Result
0x08 → 0x00
Status
PASS
5.3 Toggle Bit Test
Objective

Verify that the selected bit changes state.

Operation
reg ^= (1UL << bit);
Test
Initial:

00000000

Toggle Bit 3:

00001000

Toggle Bit 3 Again:

00000000
Expected Result
0x00 → 0x08 → 0x00
Status
PASS
5.4 Check Bit Test
Objective

Verify that the selected bit can be read correctly.

Operation
result = (reg >> bit) & 1UL;
Test 1
Input:

00001000

Check Bit 3:

Result = 1
Test 2
Input:

00000000

Check Bit 3:

Result = 0
Expected Result
SET bit   → 1
CLEAR bit → 0
Status
PASS
6. Bit Mask Testing

Bit masks are tested to ensure that unrelated bits are not modified.

Initial Value
10101010
Set Bit 0
10101010
00000001
--------
10101011
Expected
10101011

Only bit 0 should change.

7. Multiple Bit Testing

Multiple bits can be manipulated using masks.

Example:

reg |= 0x0F;

Expected:

Input:

00000000

Mask:

00001111

Result:

00001111
8. Shift Operation Testing
Left Shift
value = value << 1;

Example:

00000001
    ↓
00000010

Expected:

1 << 1 = 2
Right Shift
value = value >> 1;

Example:

00001000
    ↓
00000100

Expected:

8 >> 1 = 4
9. Boundary Bit Testing

The first and last valid bits should be tested.

For a 32-bit value:

Bit 0
Bit 1
...
Bit 30
Bit 31

Example:

Set Bit 0
Set Bit 31
Clear Bit 0
Clear Bit 31
Toggle Bit 0
Toggle Bit 31

This verifies correct bit shifting and masking.

10. Invalid Bit Testing

Invalid bit positions should be handled carefully.

Example:

Valid range for uint32_t:

0 - 31

Test cases:

Bit = -1
Bit = 32
Bit = 33

The application should validate the bit number before performing the operation.

Example:

if (bit >= 32) {
    printf("Invalid bit position\n");
    return -1;
}
11. Build Testing

The Makefile is tested before executing the application.

Build:

make

Expected:

Compilation successful
Executable generated

Verify:

ls -l
12. Clean Build Testing

Run:

make clean

Verify that generated object files and binaries are removed.

Then rebuild:

make

Expected:

Clean build successful
13. Compiler Warning Testing

The project should be compiled with useful warnings.

Example:

gcc -Wall -Wextra -Werror

The objective is to detect:

Unused variables
Incorrect conversions
Missing declarations
Suspicious expressions
Compiler warnings

Expected:

No compiler warnings
14. RISC-V Binary Verification

After cross-compilation, verify that the generated executable targets RISC-V.

Example:

file bit_manipulation

The output should identify the binary as a RISC-V executable.

For ELF inspection:

readelf -h bit_manipulation

Check the architecture field.

Expected:

Machine: RISC-V
15. Transfer Testing

Transfer the executable from the development PC to the Allwinner D1.

Example:

scp bit_manipulation user@<D1_IP>:/home/user/

Verify on the D1:

ls -l /home/user/bit_manipulation
16. Linux Execution Testing

Connect to the D1:

ssh user@<D1_IP>

Check the processor architecture:

uname -m

Verify that the system is running the expected RISC-V architecture.

Execute:

./bit_manipulation

Expected output:

Bit Manipulation Test
---------------------

Initial Value : 0x00
Set Bit 3     : 0x08
Clear Bit 3   : 0x00
Toggle Bit 3  : 0x08
Check Bit 3   : 1

All tests PASSED
17. Automated Test Execution

The test application should execute all operations automatically.

Start
  |
  v
Initialize Test Data
  |
  v
Set Bit Test
  |
  v
Clear Bit Test
  |
  v
Toggle Bit Test
  |
  v
Check Bit Test
  |
  v
Mask Test
  |
  v
Shift Test
  |
  v
Boundary Test
  |
  v
Generate Test Report
  |
  v
PASS / FAIL
18. Test Result Table
Test ID	Test	Expected	Result
TC001	Set Bit	Correct bit = 1	PASS
TC002	Clear Bit	Correct bit = 0	PASS
TC003	Toggle Bit	Bit state changes	PASS
TC004	Check Bit	Correct state returned	PASS
TC005	Bit Mask	Only selected bits change	PASS
TC006	Left Shift	Correct shifted value	PASS
TC007	Right Shift	Correct shifted value	PASS
TC008	Bit 0	Correct operation	PASS
TC009	Highest valid bit	Correct operation	PASS
TC010	Invalid bit	Error handled	PASS
19. GPIO Hardware Testing

After software validation, the bit manipulation logic can be connected to GPIO functionality.

C Application
      |
      v
Bit Operation
      |
      v
GPIO Interface
      |
      v
D1 GPIO Controller
      |
      v
GPIO Pin
      |
      v
LED
19.1 GPIO Set Test
SET BIT
   |
   v
GPIO = HIGH
   |
   v
LED = ON

Expected:

LED ON
19.2 GPIO Clear Test
CLEAR BIT
   |
   v
GPIO = LOW
   |
   v
LED = OFF

Expected:

LED OFF
19.3 GPIO Toggle Test
Toggle Bit
    |
    +---- GPIO HIGH → LED ON
    |
    +---- GPIO LOW  → LED OFF

Repeated toggling should produce:

ON → OFF → ON → OFF
20. Register-Level Testing

For register-oriented testing:

Application
     |
     v
Register Address
     |
     v
Read Register
     |
     v
Modify Selected Bit
     |
     v
Write Register
     |
     v
Read Back Register
     |
     v
Compare Expected Value

Example:

Before Register:

0x00000000

Set Bit 3:

0x00000008

Read Back:

0x00000008

Result:

PASS

Actual register addresses and access mechanisms must be taken from the documentation for the specific D1 board and its Linux software stack.

21. Register Read-Back Validation

A write operation should be followed by a read-back where appropriate.

Write
  |
  v
Register
  |
  v
Read Back
  |
  v
Compare
  |
  +---- Match    → PASS
  |
  +---- Mismatch → FAIL

This helps detect incorrect register configuration.

22. UART Debug Testing

UART can be used to monitor test results.

Example output:

[D1 TEST] Starting bit manipulation tests...

[D1 TEST] SET BIT      : PASS
[D1 TEST] CLEAR BIT    : PASS
[D1 TEST] TOGGLE BIT   : PASS
[D1 TEST] CHECK BIT    : PASS
[D1 TEST] BIT MASK     : PASS
[D1 TEST] SHIFT TEST   : PASS

[D1 TEST] All tests passed.
23. GDB Testing

GDB can be used to debug the application.

Start:

gdb ./bit_manipulation

Set a breakpoint:

break main

Run:

run

Inspect a variable:

print value

Step through code:

next

Continue:

continue
24. Debugging Test Failures

When a test fails, follow this flow:

Test Failure
     |
     v
Check Input
     |
     v
Check Bit Number
     |
     v
Check Mask
     |
     v
Check Operation
     |
     v
Check Register Value
     |
     v
Check Linux Interface
     |
     v
Check Hardware
     |
     v
Re-test
25. Common Failure Cases
Problem	Possible Cause
Wrong bit result	Incorrect mask
Set bit fails	Incorrect shift operation
Clear bit fails	Incorrect inverted mask
Toggle fails	Incorrect XOR operation
Check returns wrong value	Incorrect shift/mask
Binary does not execute	Wrong architecture
GPIO does not change	Incorrect GPIO configuration
LED does not respond	Wiring/pin configuration
Register value unexpected	Incorrect register definition
Build fails	Makefile/toolchain issue
Permission denied	File permission
Application crashes	Invalid memory access
26. Regression Testing

After modifying the source code, all existing tests should be executed again.

Code Change
    |
    v
Build
    |
    v
Unit Tests
    |
    v
Linux Tests
    |
    v
GPIO Tests
    |
    v
Hardware Tests
    |
    v
Regression Result

This ensures that a new change does not break previously working functionality.

27. Final Validation Checklist
 C source compiles successfully
 Makefile builds successfully
 No compiler warnings
 Set Bit test passes
 Clear Bit test passes
 Toggle Bit test passes
 Check Bit test passes
 Bit masking test passes
 Shift tests pass
 Boundary-bit tests pass
 Invalid-bit handling works
 RISC-V executable verified
 Binary transferred to D1
 Application executes on Linux
 UART output verified
 GPIO operation verified
 Register operation verified where applicable
 Regression tests pass
28. Expected Final Result

The final validation should demonstrate the complete path:

              C Source Code
                    |
                    v
                 Makefile
                    |
                    v
             RISC-V Compiler
                    |
                    v
             RISC-V Binary
                    |
                    v
              Allwinner D1
                    |
                    v
                Linux
                    |
                    v
          Bit Manipulation Logic
                    |
          +---------+---------+
          |         |         |
          v         v         v
        SET       CLEAR     TOGGLE
          |         |         |
          +---------+---------+
                    |
                    v
             GPIO / Register
                    |
                    v
              Physical Output
29. Conclusion

Testing is performed progressively from software-level bit manipulation to processor-level and hardware-level validation.

The project therefore demonstrates:

C Programming
      ↓
Bitwise Operations
      ↓
Unit Testing
      ↓
Makefile
      ↓
RISC-V Compilation
      ↓
Linux Execution
      ↓
Register Operations
      ↓
GPIO Testing
      ↓
Hardware Validation

This approach provides a repeatable validation methodology for the Allwinner D1 RISC-V processor platform.
