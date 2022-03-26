################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/energia-0101E0017/hardware/tools/msp430

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./utility/diskio.o" \
"./utility/pff.o" \
"./pfatfs.o" \
"./SDCardTutorialWithEnergia3.o" \
"./SPI/SPI.o" \
"./utility/eusci_spi.o" \
"./utility/usci_spi.o" \
"./utility/usi_spi.o" \
"./VC0706_try1.o" \
$(GEN_CMDS__FLAG) \
-Wl,--start-group \
-l"lpmsp430f5529_25_core" \
-Wl,--end-group \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include utility/subdir_vars.mk
-include SPI/subdir_vars.mk
-include subdir_rules.mk
-include utility/subdir_rules.mk
-include SPI/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
JPEGcameraToSDcardUsingEnergia01.out \

EXE_OUTPUTS__QUOTED += \
"JPEGcameraToSDcardUsingEnergia01.out" \

BIN_OUTPUTS += \
JPEGcameraToSDcardUsingEnergia01.hex \

BIN_OUTPUTS__QUOTED += \
"JPEGcameraToSDcardUsingEnergia01.hex" \


# All Target
all: JPEGcameraToSDcardUsingEnergia01.out secondary-outputs

dependents:
	-cd M:/_EE3123_Embedded_Systems/ccs6_workspace/lpmsp430f5529_25_core/Debug && $(MAKE) clean all

# Tool invocations
JPEGcameraToSDcardUsingEnergia01.out: $(OBJS) $(GEN_CMDS) M:/_EE3123_Embedded_Systems/ccs6_workspace/lpmsp430f5529_25_core/Debug/liblpmsp430f5529_25_core.a
	@echo 'Building target: $@'
	@echo 'Invoking: GNU Linker'
	"C:/energia-0101E0017/hardware/tools/msp430/bin/msp430-gcc.exe" -mmcu=msp430f5529 -DF_CPU=25000000L -D__MSP430_HAS_USCI_A0__ -DARDUINO=101 -DENERGIA=13 -Os -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -v -Wl,--gc-sections -L"M:/_EE3123_Embedded_Systems/ccs6_workspace/lpmsp430f5529_25_core/Debug" -Wl,--undefined,main -o"JPEGcameraToSDcardUsingEnergia01.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

JPEGcameraToSDcardUsingEnergia01.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: GNU Objcopy Utility'
	"C:/energia-0101E0017/hardware/tools/msp430/bin/msp430-objcopy.exe" -O ihex --remove-section .eeprom $(EXE_OUTPUTS__QUOTED) "JPEGcameraToSDcardUsingEnergia01.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "SDCardTutorialWithEnergia3.d" "VC0706_try1.d" "pfatfs.d" "utility\eusci_spi.d" "utility\usci_spi.d" "utility\usi_spi.d" "SPI\SPI.d" 
	-$(RM) "utility\diskio.d" "utility\pff.d" 
	-$(RM) "SDCardTutorialWithEnergia3.o" "VC0706_try1.o" "pfatfs.o" "utility\diskio.o" "utility\eusci_spi.o" "utility\pff.o" "utility\usci_spi.o" "utility\usi_spi.o" "SPI\SPI.o" 
	-@echo 'Finished clean'
	-@echo ' '

secondary-outputs: $(BIN_OUTPUTS)

.PHONY: all clean dependents
.SECONDARY:
M:/_EE3123_Embedded_Systems/ccs6_workspace/lpmsp430f5529_25_core/Debug/liblpmsp430f5529_25_core.a:

-include ../makefile.targets

