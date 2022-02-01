# SYSTICK

## Introduction

- Found in all ARM Cortex MCU regardless of silicon manufacturer.
- SysTick is a core peripheral for any ARM Cortex MCU is different from other peripherals such ADC, UART etc.
- Used for taking actions periodically. Often used as time-base for real-time operating systems.
- The Systick is a **24-bit down Counter** driven by the processor clock.
- Systick can be configured as heartbeat of the RTOS.

## SysTick Couting

- Counts from Initial value down to zero
- 24 bits imply maximum initial value of 2 power 24 = 0xFFFFFF = 16,777,216
- Initial value can be set to a value between 0x000000 to 0xFFFFFF

## SysTick Registers

- SysTick Current Value Register (STCVR)
  - This register contains the current count value

- SysTick Control and Status Register (STCSR)
  - This register allows us to configure the systick clock source, enable/disable interrupts and enable/disable the systick counter

- Systick Reload Value Register (STRVR)
  - This is where the initial count value is placed.

## SysTick Computations

Compute the delay achieved by loading 10 in the SysTick reload value register (STRVR) given system clock = 16Mhz

Written as: Systick -> LOAD = 9 ( counter 0 to 9 = 10 counts)

**Soultion**

System clock = 16Mhz = 16 000 000 Cycles/Second

Q: if 1 second executes 16000000 cycles, how many seconds execute 1 cycle?

A: 1/16000000 = 62.5 ns = 62.5 x 10 powerof (-9) s
   
Then 10 cycles, 10 x 62.5 x 10 powerof(-9)s = 625 x 10 (-9)s = 625 ns

System Clock(SYSCLK) is chosen as clock source.

if: Systick->LOAD = N

**Delay Achieved = N x 1 / SYSCLK = N / SYSCLK**

### Example

- Compute N value for achieving a 1ms delay given SYSCLK as 16MHz

Solution: 

```
1 ms = 0.001 seconds

Delay = N / SYSCLK

0.001 = N / SYSCLK

N = 0.001 x 16000000

N = 16000

```

