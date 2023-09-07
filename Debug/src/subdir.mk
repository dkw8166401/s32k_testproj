################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/CRC16.c \
../src/LPSPI.c \
../src/bq79600.c \
../src/clocks_and_modes.c \
../src/fs4500.c \
../src/main.c \
../src/systick.c 

OBJS += \
./src/CRC16.o \
./src/LPSPI.o \
./src/bq79600.o \
./src/clocks_and_modes.o \
./src/fs4500.o \
./src/main.o \
./src/systick.o 

C_DEPS += \
./src/CRC16.d \
./src/LPSPI.d \
./src/bq79600.d \
./src/clocks_and_modes.d \
./src/fs4500.d \
./src/main.d \
./src/systick.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/CRC16.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


