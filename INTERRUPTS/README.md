# Interrupts

## Interrupts Vs Polling

- Interrupt 
  - When module needs service, it notifies the CPU by sending an interrupt signal. When the CPU receives the signal the CPU interrupts whatever it is doing and services the module.

- Polling
  - The CPU continuously monitors the status of a given module, when a particular status condition is met the CPU then services the modules. it's like a loop running and the every time loop runs it will checks the status flag. If status flag matches the condition then the CPU services/executes the modules or else it will not. 

## Interrupt Service Routine

<p> The function that gets executed when an interrupt occurs is called the **Interrupt Service Routine(ISR)** or **Interrupt Handler** </p>

 ## NVIC - Nest Vector Interrupt Controller
 
 - A Dedicated hardware inside the cortex-MCU
 - It is responsible for handling interrupts.
 - NVIC will be handled from SysTick, EXTI (External Interrupts), CSS (Clock security system) and Also the processor core
 - Interrupts from the Processor core are know as **Exceptions**
 - Interrupts from outside the processor core are known as **Hardware Exceptions** or **Interrupt Requests/IRQ**
 - The vector table contains the address of the Interrupt Handler and Exception Handlers
 
 
 ## External Interrupt (EXTI) lines
 
 - GPIO Pins are connected to EXTI Lines
 - It is possible to enable interrupt for any GPIO Pin
 - Multiple pins share the same EXTI Lines
   - Pin 0 of Every PORT is connected **EXTI0_IRQ**
   - Pin 1 of Every PORT is connected **EXTI1_IRQ**
   - Pin 2 of Every PORT is connected **EXTI2_IRQ**
   - Pin 3 of Every PORT is connected **EXTI3_IRQ**
- This means we cannot have PB0 and PA0 as Input interrupt pins at the same time since they are connected to the same multiplexe i.e. EXTI0
- Same for PC4 and PA4 at the same time and so on...
- Pins 10 to 15 share the same IRQ inside the NVIC and therefore are serviced by the same Interrupt Service Routine (ISR)
- Application code must be able to find which pin from 10 to 15 generated the interrupt
 
## Interrupt States

- Disabled: This is the default state
- Enabled: Interrupt is enabled
- Pending: Waiting to be serviced
- Active: Being serviced
- Notes
  - Pending vs Active state: If one interrupt is triggered and another interrupt is triggerd after 3 seconds or 3 clock cycles then the CPU checks about the Interrupt priority which should excute first. The Higher priority task will execute first and hold the state once it is executed then the second triggered interrupt will execute.

## Interrupt Priorities
- Priorities allow us to set which interrupt should execute first
- They also allow us to set which interrupt can interrupt which
- Some interrupt priorities are defined by ARM these cannot be changed. E.g:
  - RESET - priority of -3
  - NMI   - priority of -2
  - HardFault - priority of -1
- Lower number is equal to Higher Priority

### Priorities in M3/M4/M7
- Priority of each interrupt is defined using one of the **Interrupt priority Register (IPR)**
- Each Interrupt Request(IRQ) uses 8-bits inside a single IPR register
- Therefore **one IPR** register allows us to configure the priorities of four different Interrupt requests
- Example IPR0 holds the priorities of IRQ0, IRQ1, IRQ2 and IRQ3
- There are 60 interrupt priority registers: IPR0 - IPR59
- There are 60 x 4 = 240 Interrupt Requests(IRQ)
- 8 Bits to configure the priority of an IRQ implies there are 2 power 8 = 255 priority levels
- STM32 MCU's use only the 4 upper bits to configure the priority pfeach IRQ this implies that in STM32 MCUs there are 2 power 4 = 16 priority levels
- IPRn = IRQ(4n+3), IRQ(4n+2), IRQ(4n+1) and IRQ(4n) 
- The 16 priority levels: 0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xA0, 0xB0, 0xC0, 0xD0, 0xE0, 0xF0
- Highest priority = 0x00 = 0 & lowest priority = 0xF0 = 16
- To find the IPR number, we divide the IRQ number by 4, the remainder will determine which byte it is in the IPR register.
- Because only the highest 4 bits are used for priority, the priority number needs to be multiplied by 16 or left shift 4 bits
- To simply to calculation, the NVIC_IPRx are defined as an array of 8-bit registers IP[x] in the core_cm3.h, core_cm4.h, core_cm7.h files. Such that the priority of IRQx is controlled by IP[x]
- Eg. Setting TIM2 interrupt to 3, TIM2 interrupt is IRQ 28 (provided in stm32f411xe/stm32f4xxxx.h). NVIC->IP[28] = 3<<4; or NVIC_SetPriority(TIM2_IRQn, 3);

#### Sub-priorities
- The interrupt priority registers (IPR) can also be divided into sub-priorities
- In this configuration there are a series of bits defining preemption priority and a series of bits defined the sub-priority
- The sub-priority will determine which IRQ will be executed first in the case of multiple pending IRQs



