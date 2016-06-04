################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
ti_src/DSP2803x_CodeStartBranch.obj: ../ti_src/DSP2803x_CodeStartBranch.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --include_path="C:/Users/Sean/Documents/Buckeye Current New/MCN_Library/template_headers" --include_path="C:/ti/controlSUITE/libs/math/IQmath/v160/include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/include" --include_path="C:/Users/Sean/Documents/Buckeye Current New/MCN_Library/ti_headers" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/include" --include_path="C:/Users/Sean/Documents/Buckeye Current New/MCN-Software/RC Headers" --include_path="C:/Users/Sean/Documents/Buckeye Current New/MCN-Software/cmd" -g --define="_DEBUG" --define=MCN1 --define="_FLASH" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --verbose_diagnostics --diag_wrap=off --cdebug_asm_data --output_all_syms --preproc_with_compile --preproc_dependency="ti_src/DSP2803x_CodeStartBranch.pp" --obj_directory="ti_src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

ti_src/DSP2803x_DefaultIsr.obj: ../ti_src/DSP2803x_DefaultIsr.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --include_path="C:/Users/Sean/Documents/Buckeye Current New/MCN_Library/template_headers" --include_path="C:/ti/controlSUITE/libs/math/IQmath/v160/include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/include" --include_path="C:/Users/Sean/Documents/Buckeye Current New/MCN_Library/ti_headers" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/include" --include_path="C:/Users/Sean/Documents/Buckeye Current New/MCN-Software/RC Headers" --include_path="C:/Users/Sean/Documents/Buckeye Current New/MCN-Software/cmd" -g --define="_DEBUG" --define=MCN1 --define="_FLASH" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --verbose_diagnostics --diag_wrap=off --cdebug_asm_data --output_all_syms --preproc_with_compile --preproc_dependency="ti_src/DSP2803x_DefaultIsr.pp" --obj_directory="ti_src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


