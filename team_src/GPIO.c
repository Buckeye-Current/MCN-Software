/*
 * GPIO.c
 *
 *  Created on: Apr 27, 2016
 *      Author: David
 */

#include "all.h"

void Gpio_Init(void){

	GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO26 = 0;
	GpioCtrlRegs.GPAPUD.bit.GPIO26 = 1;

}

int throttle_toggle(){

	if (GpioDataRegs.GPADAT.bit.GPIO26 == 1){
		return 1;
	}
	else {
		return 0;
	}

}
