################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/adc.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/systick.c \
../Src/uart.c 

OBJS += \
./Src/adc.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/systick.o \
./Src/uart.o 

C_DEPS += \
./Src/adc.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/systick.d \
./Src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/adc.o: ../Src/adc.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DSTM32F446xx -c -I../Inc -I"D:/Sivapraveen/Sivapraveen/ST/STM32-Baremetal Workspace/chip_headers/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Sivapraveen/Sivapraveen/ST/STM32-Baremetal Workspace/chip_headers/Drivers/CMSIS/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/adc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/main.o: ../Src/main.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DSTM32F446xx -c -I../Inc -I"D:/Sivapraveen/Sivapraveen/ST/STM32-Baremetal Workspace/chip_headers/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Sivapraveen/Sivapraveen/ST/STM32-Baremetal Workspace/chip_headers/Drivers/CMSIS/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/main.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/syscalls.o: ../Src/syscalls.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DSTM32F446xx -c -I../Inc -I"D:/Sivapraveen/Sivapraveen/ST/STM32-Baremetal Workspace/chip_headers/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Sivapraveen/Sivapraveen/ST/STM32-Baremetal Workspace/chip_headers/Drivers/CMSIS/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/syscalls.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/sysmem.o: ../Src/sysmem.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DSTM32F446xx -c -I../Inc -I"D:/Sivapraveen/Sivapraveen/ST/STM32-Baremetal Workspace/chip_headers/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Sivapraveen/Sivapraveen/ST/STM32-Baremetal Workspace/chip_headers/Drivers/CMSIS/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/sysmem.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/systick.o: ../Src/systick.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DSTM32F446xx -c -I../Inc -I"D:/Sivapraveen/Sivapraveen/ST/STM32-Baremetal Workspace/chip_headers/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Sivapraveen/Sivapraveen/ST/STM32-Baremetal Workspace/chip_headers/Drivers/CMSIS/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/systick.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/uart.o: ../Src/uart.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DSTM32F446xx -c -I../Inc -I"D:/Sivapraveen/Sivapraveen/ST/STM32-Baremetal Workspace/chip_headers/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Sivapraveen/Sivapraveen/ST/STM32-Baremetal Workspace/chip_headers/Drivers/CMSIS/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/uart.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

