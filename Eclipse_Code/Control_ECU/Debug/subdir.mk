################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Buzzer.c \
../Control_Main.c \
../Control_functions.c \
../EEPROM.c \
../I2C.c \
../MOTOR.c \
../Timer.c \
../USART.c \
../gpio.c 

OBJS += \
./Buzzer.o \
./Control_Main.o \
./Control_functions.o \
./EEPROM.o \
./I2C.o \
./MOTOR.o \
./Timer.o \
./USART.o \
./gpio.o 

C_DEPS += \
./Buzzer.d \
./Control_Main.d \
./Control_functions.d \
./EEPROM.d \
./I2C.d \
./MOTOR.d \
./Timer.d \
./USART.d \
./gpio.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


