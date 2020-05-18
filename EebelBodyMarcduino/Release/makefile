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
EebelBodyMarcduino.lss \

FLASH_IMAGE += \
EebelBodyMarcduino.hex \

EEPROM_IMAGE += \
EebelBodyMarcduino.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: EebelBodyMarcduino.elf secondary-outputs

# Tool invocations
EebelBodyMarcduino.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,EebelBodyMarcduino.map -mmcu=atmega328p -o "EebelBodyMarcduino.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

EebelBodyMarcduino.lss: EebelBodyMarcduino.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S EebelBodyMarcduino.elf  >"EebelBodyMarcduino.lss"
	@echo 'Finished building: $@'
	@echo ' '

EebelBodyMarcduino.hex: EebelBodyMarcduino.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex EebelBodyMarcduino.elf  "EebelBodyMarcduino.hex"
	@echo 'Finished building: $@'
	@echo ' '

EebelBodyMarcduino.eep: EebelBodyMarcduino.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex EebelBodyMarcduino.elf  "EebelBodyMarcduino.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: EebelBodyMarcduino.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p EebelBodyMarcduino.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) EebelBodyMarcduino.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
