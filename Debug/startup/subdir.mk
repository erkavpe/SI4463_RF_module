################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32.s 

OBJS += \
./startup/startup_stm32.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo %cd%
	arm-none-eabi-as -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -I"C:/Users/Patryk/workspace/RF_Module/CMSIS/core" -I"C:/Users/Patryk/workspace/RF_Module/CMSIS/device" -I"C:/Users/Patryk/workspace/RF_Module/inc" -I"C:/Users/Patryk/workspace/RF_Module/src" -I"C:/Users/Patryk/workspace/RF_Module/startup" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


