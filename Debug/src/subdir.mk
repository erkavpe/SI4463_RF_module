################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/interrupt.c \
../src/main.c \
../src/si4463.c \
../src/spi.c \
../src/system_stm32f0xx.c \
../src/usart.c 

OBJS += \
./src/interrupt.o \
./src/main.o \
./src/si4463.o \
./src/spi.o \
./src/system_stm32f0xx.o \
./src/usart.o 

C_DEPS += \
./src/interrupt.d \
./src/main.d \
./src/si4463.d \
./src/spi.d \
./src/system_stm32f0xx.d \
./src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -DSTM32F030F4Px -DSTM32F0 -DSTM32 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030x6 -I"C:/Users/Patryk/workspace/RF_Module/CMSIS/core" -I"C:/Users/Patryk/workspace/RF_Module/CMSIS/device" -I"C:/Users/Patryk/workspace/RF_Module/inc" -I"C:/Users/Patryk/workspace/RF_Module/src" -I"C:/Users/Patryk/workspace/RF_Module/startup" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


