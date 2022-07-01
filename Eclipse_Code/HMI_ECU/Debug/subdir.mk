################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HMI_Main.c \
../HMI_functions.c \
../LCD.c \
../Timer.c \
../USART.c \
../gpio.c \
../keypad.c 

OBJS += \
./HMI_Main.o \
./HMI_functions.o \
./LCD.o \
./Timer.o \
./USART.o \
./gpio.o \
./keypad.o 

C_DEPS += \
./HMI_Main.d \
./HMI_functions.d \
./LCD.d \
./Timer.d \
./USART.d \
./gpio.d \
./keypad.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


