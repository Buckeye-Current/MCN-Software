/*
 * clock.c
 *
 *  Created on: Nov 12, 2013
 *      Author: Nathan
 */
#include "all.h"


clock_struct Clock_Ticks = CLOCK_TICKS_CLEAR;

void ClockSetup()
{
	SystemClockSetup();
	InitializeCpuTimer2(CLOCK_PERIOD);
	StartCpuTimer2();
}

// Connected to INT13 of CPU (use MINT13 mask):
__interrupt void INT13_ISR(void)     // INT13 or CPU-Timer1
{
	 //***********************************WARNING!!********************************************\\
	//BE CAREFUL YOU NEED TO ALLOW NESTING FOR ANY INTERRUPT THAT MIGHT HAPPEN IN THIS INTERRUPT\\

	EINT;		//enable all interrupts

	ClockHeartbeat(user_ops.UserFlags.all);

	RestartCPUTimer1();
	DINT;
}

// Connected to INT14 of CPU (use MINT14 mask):
// ISR can be used by the user.
__interrupt void INT14_ISR(void)     // INT14 or CPU-Timer2
{
	//***********************************WARNING!!********************************************\\
	//BE CAREFUL YOU NEED TO ALLOW NESTING FOR ANY INTERRUPT THAT MIGHT HAPPEN IN THIS INTERRUPT\\

	 EINT;		//enable all interrupts

	//todo USER: Define Clock ISR

	Clock_Ticks.DataOut++;

	if (Clock_Ticks.DataOut >= DATAOUT_TICKS)
	{
		//send data or fill data
		SendCAN(AIN1_BOX);
		SendCAN(AIN2_BOX);
		SendCAN(AIN3_BOX);
		SendCAN(AIN4_BOX);
		SendCAN(AIN5_BOX);
		SendCAN(AIN6_BOX);
		SendCAN(AIN7_BOX);
		SendCAN(AIN8_BOX);
		SendCAN(AIN9_BOX);
		SendCAN(AIN10_BOX);
		SendCAN(AIN11_BOX);
		SendCAN(AIN12_BOX);
		SendCAN(GP0_BOX);
		SendCAN(GP1_BOX);

		Clock_Ticks.DataOut = 0;
	}

	RestartCpuTimer2();
	DINT;

}

