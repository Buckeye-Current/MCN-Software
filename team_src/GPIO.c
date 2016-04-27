/*
 * GPIO.c
 *
 *  Created on: Apr 27, 2016
 *      Author: David
 */

#include "all.h"

int throttle_toggle(){

	if (GpioDataRegs.GPADAT.bit.GPIO0 == 1){
		return 1;
	}
	else {
		return 0;
	}

}
