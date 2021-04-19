################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/FuncGen_Libraries/Menu/arb.cpp \
../Core/FuncGen_Libraries/Menu/dutycycle.cpp \
../Core/FuncGen_Libraries/Menu/frequency.cpp \
../Core/FuncGen_Libraries/Menu/magnitude.cpp \
../Core/FuncGen_Libraries/Menu/main_screen.cpp \
../Core/FuncGen_Libraries/Menu/menu.cpp \
../Core/FuncGen_Libraries/Menu/waveforms.cpp 

OBJS += \
./Core/FuncGen_Libraries/Menu/arb.o \
./Core/FuncGen_Libraries/Menu/dutycycle.o \
./Core/FuncGen_Libraries/Menu/frequency.o \
./Core/FuncGen_Libraries/Menu/magnitude.o \
./Core/FuncGen_Libraries/Menu/main_screen.o \
./Core/FuncGen_Libraries/Menu/menu.o \
./Core/FuncGen_Libraries/Menu/waveforms.o 

CPP_DEPS += \
./Core/FuncGen_Libraries/Menu/arb.d \
./Core/FuncGen_Libraries/Menu/dutycycle.d \
./Core/FuncGen_Libraries/Menu/frequency.d \
./Core/FuncGen_Libraries/Menu/magnitude.d \
./Core/FuncGen_Libraries/Menu/main_screen.d \
./Core/FuncGen_Libraries/Menu/menu.d \
./Core/FuncGen_Libraries/Menu/waveforms.d 


# Each subdirectory must supply rules for building sources it contributes
Core/FuncGen_Libraries/Menu/arb.o: ../Core/FuncGen_Libraries/Menu/arb.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DSTM32F407xx -c -I../Core/Inc -I"D:/STM32Cube/Repository/STM32Cube_FW_F4_V1.25.2/Drivers/CMSIS/DSP/Include" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Function_Generator" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Menu" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Push_Buttons" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Display_20x4" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Core/FuncGen_Libraries/Menu/arb.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/FuncGen_Libraries/Menu/dutycycle.o: ../Core/FuncGen_Libraries/Menu/dutycycle.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DSTM32F407xx -c -I../Core/Inc -I"D:/STM32Cube/Repository/STM32Cube_FW_F4_V1.25.2/Drivers/CMSIS/DSP/Include" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Function_Generator" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Menu" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Push_Buttons" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Display_20x4" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Core/FuncGen_Libraries/Menu/dutycycle.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/FuncGen_Libraries/Menu/frequency.o: ../Core/FuncGen_Libraries/Menu/frequency.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DSTM32F407xx -c -I../Core/Inc -I"D:/STM32Cube/Repository/STM32Cube_FW_F4_V1.25.2/Drivers/CMSIS/DSP/Include" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Function_Generator" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Menu" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Push_Buttons" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Display_20x4" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Core/FuncGen_Libraries/Menu/frequency.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/FuncGen_Libraries/Menu/magnitude.o: ../Core/FuncGen_Libraries/Menu/magnitude.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DSTM32F407xx -c -I../Core/Inc -I"D:/STM32Cube/Repository/STM32Cube_FW_F4_V1.25.2/Drivers/CMSIS/DSP/Include" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Function_Generator" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Menu" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Push_Buttons" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Display_20x4" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Core/FuncGen_Libraries/Menu/magnitude.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/FuncGen_Libraries/Menu/main_screen.o: ../Core/FuncGen_Libraries/Menu/main_screen.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DSTM32F407xx -c -I../Core/Inc -I"D:/STM32Cube/Repository/STM32Cube_FW_F4_V1.25.2/Drivers/CMSIS/DSP/Include" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Function_Generator" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Menu" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Push_Buttons" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Display_20x4" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Core/FuncGen_Libraries/Menu/main_screen.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/FuncGen_Libraries/Menu/menu.o: ../Core/FuncGen_Libraries/Menu/menu.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DSTM32F407xx -c -I../Core/Inc -I"D:/STM32Cube/Repository/STM32Cube_FW_F4_V1.25.2/Drivers/CMSIS/DSP/Include" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Function_Generator" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Menu" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Push_Buttons" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Display_20x4" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Core/FuncGen_Libraries/Menu/menu.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/FuncGen_Libraries/Menu/waveforms.o: ../Core/FuncGen_Libraries/Menu/waveforms.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DSTM32F407xx -c -I../Core/Inc -I"D:/STM32Cube/Repository/STM32Cube_FW_F4_V1.25.2/Drivers/CMSIS/DSP/Include" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Function_Generator" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Menu" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Push_Buttons" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Display_20x4" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Core/FuncGen_Libraries/Menu/waveforms.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

