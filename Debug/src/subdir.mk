################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/DHT11_humidity_temp.c \
../src/DS18B20_water_temp.c \
../src/LCD_pcf8574.c \
../src/RTC_ds3231.c \
../src/_write.c \
../src/alarms_and_security.c \
../src/blinds.c \
../src/boiler.c \
../src/light_mgmt.c \
../src/main.c \
../src/misc.c \
../src/stm32f4xx_hal_msp.c \
../src/stm32f4xx_it.c \
../src/syscalls.c \
../src/system_init.c \
../src/system_stm32f4xx.c \
../src/ventilation_and_heating.c 

OBJS += \
./src/DHT11_humidity_temp.o \
./src/DS18B20_water_temp.o \
./src/LCD_pcf8574.o \
./src/RTC_ds3231.o \
./src/_write.o \
./src/alarms_and_security.o \
./src/blinds.o \
./src/boiler.o \
./src/light_mgmt.o \
./src/main.o \
./src/misc.o \
./src/stm32f4xx_hal_msp.o \
./src/stm32f4xx_it.o \
./src/syscalls.o \
./src/system_init.o \
./src/system_stm32f4xx.o \
./src/ventilation_and_heating.o 

C_DEPS += \
./src/DHT11_humidity_temp.d \
./src/DS18B20_water_temp.d \
./src/LCD_pcf8574.d \
./src/RTC_ds3231.d \
./src/_write.d \
./src/alarms_and_security.d \
./src/blinds.d \
./src/boiler.d \
./src/light_mgmt.d \
./src/main.d \
./src/misc.d \
./src/stm32f4xx_hal_msp.d \
./src/stm32f4xx_it.d \
./src/syscalls.d \
./src/system_init.d \
./src/system_stm32f4xx.d \
./src/ventilation_and_heating.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DSTM32F429xx -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4xx" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


