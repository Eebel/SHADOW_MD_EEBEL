################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
EebelBodyMaster.lss \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: EebelBodyMaster.elf secondary-outputs

# Tool invocations
EebelBodyMaster.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,EebelBodyMaster.map -mmcu=atmega328p -o "EebelBodyMaster.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

EebelBodyMaster.lss: EebelBodyMaster.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S EebelBodyMaster.elf  >"EebelBodyMaster.lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: EebelBodyMaster.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p EebelBodyMaster.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: EebelBodyMaster.elf
	@echo 'Invoking: AVRDude'
	/usr/local/CrossPack-AVR-20131216/bin/avrdude -pm328p -cusbtiny -Uflash:w:EebelBodyMaster.hex:a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(ELFS)$(OBJS)$(ASM_DEPS)$(AVRDUDEDUMMY)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) EebelBodyMaster.elf
	-@echo ' '

secondary-outputs: $(LSS) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
