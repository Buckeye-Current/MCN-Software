################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
ti_src/DSP2803x_CodeStartBranch.obj: ../ti_src/DSP2803x_CodeStartBranch.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --include_path="C:/Users/Chris/Documents/BuckeyeCurrent/MCN_Library/template_headers" --include_path="C:/ti/controlSUITE/libs/math/IQmath/v160/include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/include" --include_path="C:/Users/Chris/Documents/BuckeyeCurrent/MCN_Library/ti_headers" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/include" --include_path="C:/Users/Chris/Documents/BuckeyeCurrent/MCN-Software/RC Headers" --include_path="C:/Users/Chris/Documents/BuckeyeCurrent/MCN-Software/cmd" -g --define="_DEBUG" --define=MCN1 --define="_FLASH" --define="LARGE_MODEL" --verbose_diagnostics --diag_warning=225 --display_error_number --diag_wrap=off --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="ti_src/DSP2803x_CodeStartBranch.pp" --obj_directory="ti_src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

ti_src/DSP2803x_DefaultIsr.obj: ../ti_src/DSP2803x_DefaultIsr.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --include_path="C:/Users/Chris/Documents/BuckeyeCurrent/MCN_Library/template_headers" --include_path="C:/ti/controlSUITE/libs/math/IQmath/v160/include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/include" --include_path="C:/Users/Chris/Documents/BuckeyeCurrent/MCN_Library/ti_headers" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.6/include" --include_path="C:/Users/Chris/Documents/BuckeyeCurrent/MCN-Software/RC Headers" --include_path="C:/Users/Chris/Documents/BuckeyeCurrent/MCN-Software/cmd" -g --define="_DEBUG" --define=MCN1 --define="_FLASH" --define="LARGE_MODEL" --verbose_diagnostics --diag_warning=225 --display_error_number --diag_wrap=off --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="ti_src/DSP2803x_DefaultIsr.pp" --obj_directory="ti_src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


