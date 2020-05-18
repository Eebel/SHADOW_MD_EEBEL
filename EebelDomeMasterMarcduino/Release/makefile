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
EebelDomeMasterMarcduino.lss \

FLASH_IMAGE += \
EebelDomeMasterMarcduino.hex \

EEPROM_IMAGE += \
EebelDomeMasterMarcduino.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: EebelDomeMasterMarcduino.elf secondary-outputs

# Tool invocations
EebelDomeMasterMarcduino.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,EebelDomeMasterMarcduino.map -mmcu=atmega328p -o "EebelDomeMasterMarcduino.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

EebelDomeMasterMarcduino.lss: EebelDomeMasterMarcduino.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S EebelDomeMasterMarcduino.elf  >"EebelDomeMasterMarcduino.lss"
	@echo 'Finished building: $@'
	@echo ' '

EebelDomeMasterMarcduino.hex: EebelDomeMasterMarcduino.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex EebelDomeMasterMarcduino.elf  "EebelDomeMasterMarcduino.hex"
	@echo 'Finished building: $@'
	@echo ' '

EebelDomeMasterMarcduino.eep: EebelDomeMasterMarcduino.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex EebelDomeMasterMarcduino.elf  "EebelDomeMasterMarcduino.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: EebelDomeMasterMarcduino.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p EebelDomeMasterMarcduino.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) EebelDomeMasterMarcduino.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
