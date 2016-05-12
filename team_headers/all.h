/*
 * all.h
 *
 *  Created on: Oct 29, 2013
 *      Author: Nathan, edited by David
 */

#ifndef ALL_H_
#define ALL_H_

#include "template_all.h"
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "stopwatch_template.h"
#include "op.h"
#include "sys_op.h"
#include "data.h"
#include "sys_data.h"
#include "Init.h"
#include "Init_template.h"
#include "can_template.h"
#include "SensorCov.h"
#include "SensorCov_template.h"
#include "boot_template.h"
#include "PowerDown.h"
#include "PowerDown_template.h"
#include "common_template.h"
#include "main.h"
#include "clock.h"
#include "clock_template.h"
#include "can.h"
#include <stdlib.h>
#include <math.h>
#include "adc_template.h"
#include "gpio_template.h"
#include "DSP2803x_GlobalPrototypes.h"
#include "Flash2803x_API_Library.h"
#include "IQmathLib.h"
#include "EMA.h"
#include "Stack.h"
#include <stdbool.h>
#include "SafetyVar.h"
#include "GPIO.h"


extern sys_ops_struct sys_ops;
extern user_ops_struct user_ops;
extern sys_data_struct sys_data;
extern user_data_struct user_data;

#define CPU_FREQ_MHZ	60
#define EMA_FILTER_ENABLED 1

#endif /* ALL_H_ */
