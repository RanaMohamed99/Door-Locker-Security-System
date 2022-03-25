################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../EEPROM.c \
../I2C.c \
../MOTOR.c \
../MP2.c \
../UART.c \
../timers.c 

OBJS += \
./EEPROM.o \
./I2C.o \
./MOTOR.o \
./MP2.o \
./UART.o \
./timers.o 

C_DEPS += \
./EEPROM.d \
./I2C.d \
./MOTOR.d \
./MP2.d \
./UART.d \
./timers.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


