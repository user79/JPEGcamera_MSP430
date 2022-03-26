################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
SPI/%.o: ../SPI/%.cpp $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Compiler'
	"C:/energia-0101E0017/hardware/tools/msp430/bin/msp430-gcc.exe" -c -mmcu=msp430f5529 -DF_CPU=25000000L -D__MSP430_HAS_USCI_A0__ -DARDUINO=101 -DENERGIA=13 -I"C:/energia-0101E0017/hardware/msp430/cores/msp430" -I"C:/energia-0101E0017/hardware/msp430/variants/launchpad_f5529" -I"M:/_EE3123_Embedded_Systems/ccs6_workspace/JPEGcameraToSDcardUsingEnergia01" -I"C:/energia-0101E0017/hardware/tools/msp430/msp430/include" -Os -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -v -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


