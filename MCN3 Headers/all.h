/*
 * all.h
 *
 *  Created on: Oct 29, 2013
 *      Author: Nathan
 */

#ifndef ALL_H_
#define ALL_H_

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include <stdlib.h>
#include <math.h>
#include "../../MCN_Library/template_headers/adc_template.h"
#include "../../MCN_Library/template_headers/boot_template.h"
#include "../../MCN_Library/template_headers/can_template.h"
#include "../../MCN_Library/template_headers/clock_template.h"
#include "../../MCN_Library/template_headers/common_template.h"
#include "../../MCN_Library/template_headers/gpio_template.h"
#include "../../MCN_Library/template_headers/Init_template.h"
#include "../../MCN_Library/template_headers/PowerDown_template.h"
#include "../../MCN_Library/template_headers/stopwatch_template.h"
#include "../../MCN_Library/template_headers/sys_data.h"
#include "../../MCN_Library/template_headers/sys_op.h"
#include "../../MCN_Library/template_headers/SensorCov_template.h"
#include "../../MCN_Library/template_headers/template_all.h"
#include "../MCN3 Headers/can.h"
#include "../MCN3 Headers/clock.h"
#include "../MCN3 Headers/data.h"
#include "../MCN3 Headers/Init.h"
#include "../MCN3 Headers/main.h"
#include "../MCN3 Headers/op.h"
#include "../MCN3 Headers/PowerDown.h"
#include "../MCN3 Headers/SensorCov.h"
#include "DSP2803x_GlobalPrototypes.h"
#include "Flash2803x_API_Library.h"
#include "IQmathlib.h"

extern sys_ops_struct sys_ops;
extern user_ops_struct user_ops;
extern sys_data_struct sys_data;
extern user_data_struct user_data;

#define CPU_FREQ_MHZ	60

#endif /* ALL_H_ */
