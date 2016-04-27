/*
 * clock.c
 *
 *  Created on: Nov 12, 2013
 *      Author: Nathan, edited by David
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

	Clock_Ticks.DataOutThrottle++;
	Clock_Ticks.DataOutLimits++;

	if (Clock_Ticks.DataOutThrottle >= THROTTLE_TICKS)
	{
		//send data or fill data
		SendCAN(DriverThrottle_BOX);
		SendCAN(no_filter_BOX);
		Clock_Ticks.DataOutThrottle = 0;
	}
	if (Clock_Ticks.DataOutLimits >= STATUS_TICKS)
	{
		SendCAN(DriverControl_BOX);
		Clock_Ticks.DataOutLimits = 0;
	}

	EMA_Filter_Update();

	RestartCpuTimer2();
	DINT;

}

