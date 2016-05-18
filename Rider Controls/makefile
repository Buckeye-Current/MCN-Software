################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"C:/Users/Chris/Documents/BuckeyeCurrent/MCN_Library/Debug/ti_src/DSP2803x_GlobalVariableDefs.obj" \
"./ti_src/DSP2803x_CodeStartBranch.obj" \
"./ti_src/DSP2803x_DefaultIsr.obj" \
"./RC Source/EMA.obj" \
"./RC Source/GPIO.obj" \
"./RC Source/Init.obj" \
"./RC Source/PowerDown.obj" \
"./RC Source/SafetyVar.obj" \
"./RC Source/SensorCov.obj" \
"./RC Source/Stack.obj" \
"./RC Source/can.obj" \
"./RC Source/clock.obj" \
"./RC Source/main.obj" \
"../lib/2803x_FlashAPI_BootROMSymbols.lib" \
"../lib/Flash2803x_API_V100.lib" \
"../lib/IQmath.lib" \
"../cmd/DSP2803x_Headers_nonBIOS.cmd" \
"../cmd/F28035.cmd" \
$(GEN_CMDS__FLAG) \
-l"libc.a" \
-l"C:\Users\Chris\Documents\BuckeyeCurrent\MCN_Library\Debug\MCN_Library.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include ti_src/subdir_vars.mk
-include lib/subdir_vars.mk
-include cmd/subdir_vars.mk
-include RC\ Source/subdir_vars.mk
-include subdir_rules.mk
-include ti_src/subdir_rules.mk
-include lib/subdir_rules.mk
-include cmd/subdir_rules.mk
-include RC\ Source/subdir_rules.mk
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
Magic\ CAN\ Node\ 2.0.out \

EXE_OUTPUTS__QUOTED += \
"Magic CAN Node 2.0.out" \


# All Target
all: Magic\ CAN\ Node\ 2.0.out

# Tool invocations
Magic\ CAN\ Node\ 2.0.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/bin/cl2000" -v28 -ml -mt --cla_support=cla0 -g --define="_DEBUG" --define=MCN1 --define="_FLASH" --define="LARGE_MODEL" --verbose_diagnostics --diag_warning=225 --display_error_number --diag_wrap=off --output_all_syms --cdebug_asm_data -z -m"Magic CAN Node 2.0.map" --heap_size=0x400 --stack_size=0x300 --warn_sections -i"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/include" -i"C:/ti/controlSUITE/libs/math/IQmath/v160/include" -i"C:/Users/Chris/Documents/BuckeyeCurrent/MCN_Library/Debug" -i"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/lib" -i"C:/Users/Chris/Documents/BuckeyeCurrent/MCN-Software/cmd" -i"C:/Users/Chris/Documents/BuckeyeCurrent/MCN-Software/lib" --reread_libs --display_error_number --diag_wrap=off --xml_link_info="Magic CAN Node 2.0_linkInfo.xml" --rom_model --far_heapsize=0x400 -o "Magic CAN Node 2.0.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "ti_src\DSP2803x_DefaultIsr.pp" "RC Source\EMA.pp" "RC Source\GPIO.pp" "RC Source\Init.pp" "RC Source\PowerDown.pp" "RC Source\SafetyVar.pp" "RC Source\SensorCov.pp" "RC Source\Stack.pp" "RC Source\can.pp" "RC Source\clock.pp" "RC Source\main.pp" 
	-$(RM) "ti_src\DSP2803x_CodeStartBranch.obj" "ti_src\DSP2803x_DefaultIsr.obj" "RC Source\EMA.obj" "RC Source\GPIO.obj" "RC Source\Init.obj" "RC Source\PowerDown.obj" "RC Source\SafetyVar.obj" "RC Source\SensorCov.obj" "RC Source\Stack.obj" "RC Source\can.obj" "RC Source\clock.obj" "RC Source\main.obj" 
	-$(RM) "ti_src\DSP2803x_CodeStartBranch.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

