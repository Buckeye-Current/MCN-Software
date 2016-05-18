/*
 * GPIO.c
 *
 *  Created on: Apr 27, 2016
 *      Author: David
 */

#include "../RC Headers/all.h"

void Gpio_Init(void){

	EALLOW;
	GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO26 = 0;
	GpioCtrlRegs.GPAPUD.bit.GPIO26 = 1;
	EDIS;

}

int throttle_toggle(){

	if (GpioDataRegs.GPADAT.bit.GPIO26 == 1){
		return 1;
	}
	else {
		return 0;
	}

}
