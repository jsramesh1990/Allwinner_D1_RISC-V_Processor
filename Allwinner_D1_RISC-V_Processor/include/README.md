How d1_registers.h fits into the project
                  Allwinner D1
                 RISC-V Processor
                       │
                       ▼
              ┌─────────────────┐
              │ d1_registers.h  │
              └────────┬────────┘
                       │
          ┌────────────┼────────────┐
          ▼            ▼            ▼
       Bit APIs    Field APIs   Register APIs
          │            │            │
          ▼            ▼            ▼
        SET        FIELD_GET     READ
        CLEAR      FIELD_PREP    WRITE
        TOGGLE     FIELD_MODIFY  UPDATE
        CHECK
          │            │            │
          └────────────┼────────────┘
                       ▼
                 C Application
                       │
                       ▼
              Linux / Hardware

Important for the GitHub project: this header currently gives you a register-programming framework, not a verified D1 hardware register map. When you later add real D1 GPIO/UART/SPI/clock register addresses, keep those definitions in dedicated headers such as d1_gpio.h, d1_uart.h, etc., rather than putting the entire SoC register map into d1_registers.h.
