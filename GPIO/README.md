# GPIO

MCU Pins are grouped into PORT

PA1 = PORT A Pin #1

2 Types of GPIO

- General Purpose Input/Output (General function of the pin)
- Special Purpose Input/Output (Special -or- Alternate function of the pin eg: UART,I2C, ADC etc.)


# GPIO Common Registers

MCUs GPIO Modules have atleast 2 registers

- Direction Register: Used to Set pin as Input -or- Output
- Data Register     : Used to Write to pin -or- Read from pin

# MCU Buses

- Advanced High-Performance Bus (AHB)
  - 1 Clock Cycle access to peripeheral
- Advanced Peripheral Bus (APB)
  - Minimum of 2 clock cycles access to peripherals 

# MCU Clock Sources

1. On-Chip RC Oscillator - Least Precise
2. Externally Connected Crystal - Most Precise
3. Phase Locked Loop (PLL) - Programmable

