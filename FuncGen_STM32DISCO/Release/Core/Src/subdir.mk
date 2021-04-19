################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/arm_common_tables.c \
../Core/Src/arm_cos_f32.c \
../Core/Src/arm_sin_f32.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c 

CPP_SRCS += \
../Core/Src/main.cpp 

C_DEPS += \
./Core/Src/arm_common_tables.d \
./Core/Src/arm_cos_f32.d \
./Core/Src/arm_sin_f32.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d 

OBJS += \
./Core/Src/arm_common_tables.o \
./Core/Src/arm_cos_f32.o \
./Core/Src/arm_sin_f32.o \
./Core/Src/main.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o 

CPP_DEPS += \
./Core/Src/main.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/arm_common_tables.o: ../Core/Src/arm_common_tables.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 '-D__FPU_PRESENT = 1' -DDEBUG -DSTM32F407xx -c -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Function_Generator" -I"D:/STM32Cube/Repository/STM32Cube_FW_F4_V1.25.2/Drivers/CMSIS/DSP/Include" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Menu" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Push_Buttons" -I../Core/Inc -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Display_20x4" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/arm_common_tables.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/arm_cos_f32.o: ../Core/Src/arm_cos_f32.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 '-D__FPU_PRESENT = 1' -DDEBUG -DSTM32F407xx -c -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Function_Generator" -I"D:/STM32Cube/Repository/STM32Cube_FW_F4_V1.25.2/Drivers/CMSIS/DSP/Include" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Menu" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Push_Buttons" -I../Core/Inc -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Display_20x4" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/arm_cos_f32.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/arm_sin_f32.o: ../Core/Src/arm_sin_f32.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 '-D__FPU_PRESENT = 1' -DDEBUG -DSTM32F407xx -c -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Function_Generator" -I"D:/STM32Cube/Repository/STM32Cube_FW_F4_V1.25.2/Drivers/CMSIS/DSP/Include" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Menu" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Push_Buttons" -I../Core/Inc -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Display_20x4" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/arm_sin_f32.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/main.o: ../Core/Src/main.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DSTM32F407xx -c -I../Core/Inc -I"D:/STM32Cube/Repository/STM32Cube_FW_F4_V1.25.2/Drivers/CMSIS/DSP/Include" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Function_Generator" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Menu" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Push_Buttons" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Display_20x4" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Core/Src/main.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/stm32f4xx_hal_msp.o: ../Core/Src/stm32f4xx_hal_msp.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 '-D__FPU_PRESENT = 1' -DDEBUG -DSTM32F407xx -c -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Function_Generator" -I"D:/STM32Cube/Repository/STM32Cube_FW_F4_V1.25.2/Drivers/CMSIS/DSP/Include" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Menu" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Push_Buttons" -I../Core/Inc -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Display_20x4" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32f4xx_hal_msp.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/stm32f4xx_it.o: ../Core/Src/stm32f4xx_it.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 '-D__FPU_PRESENT = 1' -DDEBUG -DSTM32F407xx -c -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Function_Generator" -I"D:/STM32Cube/Repository/STM32Cube_FW_F4_V1.25.2/Drivers/CMSIS/DSP/Include" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Menu" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Push_Buttons" -I../Core/Inc -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Display_20x4" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32f4xx_it.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/syscalls.o: ../Core/Src/syscalls.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 '-D__FPU_PRESENT = 1' -DDEBUG -DSTM32F407xx -c -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Function_Generator" -I"D:/STM32Cube/Repository/STM32Cube_FW_F4_V1.25.2/Drivers/CMSIS/DSP/Include" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Menu" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Push_Buttons" -I../Core/Inc -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Display_20x4" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/syscalls.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/sysmem.o: ../Core/Src/sysmem.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 '-D__FPU_PRESENT = 1' -DDEBUG -DSTM32F407xx -c -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Function_Generator" -I"D:/STM32Cube/Repository/STM32Cube_FW_F4_V1.25.2/Drivers/CMSIS/DSP/Include" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Menu" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Push_Buttons" -I../Core/Inc -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Display_20x4" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/sysmem.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/system_stm32f4xx.o: ../Core/Src/system_stm32f4xx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 '-D__FPU_PRESENT = 1' -DDEBUG -DSTM32F407xx -c -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Function_Generator" -I"D:/STM32Cube/Repository/STM32Cube_FW_F4_V1.25.2/Drivers/CMSIS/DSP/Include" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Menu" -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Push_Buttons" -I../Core/Inc -I"D:/STM32Cube/STM32CubeIDE/workspace_1.4.0/FuncGen/Core/FuncGen_Libraries/Display_20x4" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/system_stm32f4xx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

