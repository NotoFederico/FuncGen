################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/FuncGen_Libraries/Function_Generator/common_waves.cpp 

OBJS += \
./Core/FuncGen_Libraries/Function_Generator/common_waves.o 

CPP_DEPS += \
./Core/FuncGen_Libraries/Function_Generator/common_waves.d 


# Each subdirectory must supply rules for building sources it contributes
Core/FuncGen_Libraries/Function_Generator/common_waves.o: ../Core/FuncGen_Libraries/Function_Generator/common_waves.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DSTM32F407xx -c -I../Core/Inc -I"D:/STM32Cube/Repository/STM32Cube_FW_F4_V1.25.2/Drivers/CMSIS/DSP/Include" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Function_Generator" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Menu" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Push_Buttons" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Display_20x4" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Core/FuncGen_Libraries/Function_Generator/common_waves.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

