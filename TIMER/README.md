# Timer

## Timer Usage
- Counting Events
- Creating Delays
- Measuring time between event, etc.


## Timer vs Counter
- Timer = Internal Clock Source ( PLL, XTAL, RC)
- Counter = External Clock Source ( Clock fed to CPU)


## STM32 Timers

- Can be used as time base generator
- Can be used to measure the frequency of an external event - Input capture mode
- Control an output waveform, or to indicate when a period of time has elapsed - Output compare mode
- one pulse mode(OPM) - allows the counter to be started in response to a stimulus and to generate a pulse with a programmable length after a programmable delay



## Timer - Registers

### Timer Count Register(TIMx_CNT)
   - shows the current counter value. Size could be 32 bit or 16 bit depending on timer module used
   
### Timer Auto Reload Register(TIMx_ARR)
   - Timer raises a flag and the counter restarts automatically when counter value reaches the value in the auto-reload register.
   -  The counter is an up counter by default but can also be configured to be a down counter.
   
### Timer Prescaler Register(TIMx_PSC)
   - The prescaler slows down the counting speed of the timer by dividing the input clock of the timer.

## Timer Clock Pre-scaling 

![timer_prescaler](https://user-images.githubusercontent.com/84496147/151922036-41064624-6916-4d63-85cf-45a2c6692787.PNG)

- Timer prescaler(TIMx_PSC) determines how fast the timer counter(TIMx_CNT) increases/decreases.
- with each change in the counter(TIMx_CNT) value, the new value is compared to the value in the timer auto-reload register(TIM_ARR), when the values match, a flag is raised and an interrupt occurs.
- Flow
  - AHB Prescaler (1,2,4,8 ... 512) => HCLK (1,2,4,8 ... 256) => APB1 & APB2 Prescaler (1,2,4,8,15) => TIMx_PSC (1,2,4,8 ... 65535) => to TIM_CNT
  
  
## Timer Terms

- Update Event
  - When Timeout occurs or how long it takes for flag to be raised

- Period
  - Value loaded into auto-reload register(TIM_ARR)

- Up Counter
  - Counts from zero to set value

- Down Counter
  - Counts from a set value down to zero

## Timer - Computing Update Event

- Formula
  ```
  Update Event = Timer clock / (Prescaler + 1)(Period + 1)
  ```

- Example
  ```
  Timer clock = APB1 Clock    = 48 MHz
  Prescaler   = TIM_PSC value = 47999 + 1
  Period      = TIM_ARR value = 499 + 1
  
  Update Event = 48 000 000 / (47999 + 1)(499 + 1)
               = 2 Hz
               = 1/2 second
               = 0.5 second
  ```
  
