# Direct Memory Access (DMA)

## Introduction

- DMA allows data transfers to take place in the background, without the intervention of the Cortex-M Processor
- During this operation, the main processor can execute other tasks and it is only interrupted when a whole data block is available for processing
- Large amounts of data can be transferred with no major impact on the system performance

## DMA - Transfer Properties
- DMA Stream/Channel
- Stream Priority
- Source and destination address
- Transfer mode
- Transfer size
- source/Destination address incrementing or non-incrementing
- Source and destination data width
- Transfer type
- FIFO mode
- Source/Destination burst size
- Double-buffer mode
- flow control

## DMA Ports
- DMA has 2 ports
  - One peripheral port
  - One memory port

## DMA - Streams/Channels for STM32 F2/F4/F7

![DMA Streams_Channels](https://user-images.githubusercontent.com/84496147/152940191-6104f7bb-ba0d-4a4a-86ac-8519464126f2.PNG)

- There are 2 DMA Modules
- Each module implements 8 different streams
- Each Stream is dedicated to managing memory access requests from one -or- more peripherals
- Each stream has up to eight selectable channels (requests) in total 
- The seletion is software-Configurable and allows several peripheral to initiate DMA Requests.
- Only one channel/request can be active at the same time in a stream

## DMA - Streams Priority

- DMA has an arbiter for handling the priority between the DMA Streams
- Stream priority is software configurable
- There are four levels
- If two -or- more DMA streams have the same software priority level, the hardware priority is used
- Hardware priority - Stream 0 has priority over stream 1 etc.

## DMA - Source and Destination addresses
- DMA transfer is defined by a source address and a destination address.
- Both the source and destination should be in the AHB or APB memory ranges

## DMA - Transfer Modes
- DMA is capable of performing three different transfer modes:
  - Peripheral to memory
  - Memory to peripheral
  - Memory to memory - only available on DMA2 module

## DMA - Transfer Size
- Has to be defined only when the DMA is the Flow controller
- This value defines the volume of data to be transferred from source to destination
- DMA Can automatically increment source and destination addresses after each transfer

## DMA - Source and Destination Data Width
- Byte (8bits)
- Half-word  (16bits)
- Word (32bits)

## DMA - Transfer Types

- Circular Mode:
  - For handling circular buffers and continuous data flows
  - The DMA_SxNDTR register is then reloaded automatically with the previously programmed value

- Normal Mode:
  - Once the DMA_SxNDTR register reached zero, the stream is disabled


## DMA - FIFO Mode in F2/F4/F7

- Each stream has an independent 4-word (4 * 32bits) FIFO
- The FIFO is used to temporarily store data coming from the source before transmitting it to the destination
- If DMA FIFO is enabled, the data packing/unpacking and/or burst mode can be used.
- The configured DMA FIFO threshold defines the DMA memory port request time
- Reduces SRAM access and so gives more time for the other masters to access the bus matrix without additional concurrency
- Allow software to do burst transactions which optimize the transfer bandwidth
- Allow packing/unpacking data to adapt source and destination data width with no extra DMA access


