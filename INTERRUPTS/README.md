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
