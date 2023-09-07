################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include Project_Settings/Linker_Files/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_SIZE += \
S32K148_Project_LPSPI.siz \
S32K148_Project_LPSPI.siz \

SECONDARY_SIZE += \
S32K148_Project_LPSPI.siz \
S32K148_Project_LPSPI.siz \


# All Target
all: S32K148_Project_LPSPI.elf secondary-outputs

# Tool invocations
S32K148_Project_LPSPI.elf: $(OBJS) E:/S32stu_workspace/S32K148_Project_LPSPI/Project_Settings/Linker_Files/S32K1xx_flash.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Standard S32DS C Linker'
	arm-none-eabi-gcc -o "S32K148_Project_LPSPI.elf" "@S32K148_Project_LPSPI.args"  $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

S32K148_Project_LPSPI.siz: S32K148_Project_LPSPI.elf
	@echo 'Invoking: Standard S32DS Print Size'
	arm-none-eabi-size --format=berkeley S32K148_Project_LPSPI.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) ./*
	-@echo ' '

secondary-outputs: $(SECONDARY_SIZE) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
