################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/BASE64/BASE64_FUN.c \
../Core/Src/BASE64/BASE64_VAR.c 

OBJS += \
./Core/Src/BASE64/BASE64_FUN.o \
./Core/Src/BASE64/BASE64_VAR.o 

C_DEPS += \
./Core/Src/BASE64/BASE64_FUN.d \
./Core/Src/BASE64/BASE64_VAR.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/BASE64/%.o Core/Src/BASE64/%.su Core/Src/BASE64/%.cyclo: ../Core/Src/BASE64/%.c Core/Src/BASE64/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Core/Src/BASE64 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-BASE64

clean-Core-2f-Src-2f-BASE64:
	-$(RM) ./Core/Src/BASE64/BASE64_FUN.cyclo ./Core/Src/BASE64/BASE64_FUN.d ./Core/Src/BASE64/BASE64_FUN.o ./Core/Src/BASE64/BASE64_FUN.su ./Core/Src/BASE64/BASE64_VAR.cyclo ./Core/Src/BASE64/BASE64_VAR.d ./Core/Src/BASE64/BASE64_VAR.o ./Core/Src/BASE64/BASE64_VAR.su

.PHONY: clean-Core-2f-Src-2f-BASE64

