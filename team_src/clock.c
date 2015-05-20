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

	Clock_Ticks.brake++;
	Clock_Ticks.other++;
	Clock_Ticks.shunts++;
	Clock_Ticks.speed++;
	Clock_Ticks.susp++;

	if (Clock_Ticks.brake >= TICKS_BRAKE)
	{
		//send data or fill data
		SendCAN(REAR_BRAKE_BOX);
		Clock_Ticks.brake = 0;
	}
	if (Clock_Ticks.other >= TICKS_OTHER)
	{
		//send data or fill data
		SendCAN(FRAME_FAULT_BOX);
		SendCAN(CONTACTOR_BOX_BOX);
		Clock_Ticks.other = 0;
	}
	if (Clock_Ticks.shunts >= TICKS_SHUNTS)
	{
		//send data or fill data
		SendCAN(SHUNTS_BOX);
		Clock_Ticks.shunts = 0;
	}
	if (Clock_Ticks.speed >= TICKS_SPEED)
	{
		//send data or fill data
		SendCAN(REAR_WHEEL_SPEED_BOX);
		Clock_Ticks.speed = 0;
	}
	if (Clock_Ticks.susp >= TICKS_SUSP)
	{
		//send data or fill data
		SendCAN(REAR_SUSPENSION_BOX);
		Clock_Ticks.susp = 0;
	}



	RestartCpuTimer2();
	DINT;

}

