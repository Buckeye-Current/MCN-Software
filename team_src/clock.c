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

	Clock_Ticks.AmbientRadiatorOut++;
	Clock_Ticks.FrontBrakeOut++;
	Clock_Ticks.FrontWheelOut++;
	Clock_Ticks.SteeringSuspensionOut++;

	if (Clock_Ticks.AmbientRadiatorOut >= FIVE_HZ_TICKS)
	{
		//send data or fill data
		SendCAN(AMBIENT_BOX);
		SendCAN(RADIATOR_BOX);
		Clock_Ticks.AmbientRadiatorOut = 0;
	}
	if (Clock_Ticks.FrontBrakeOut >= TEN_HZ_TICKS)
	{
		SendCAN(FRONT_BRAKE_BOX);
		Clock_Ticks.FrontBrakeOut = 0;
	}
	if (Clock_Ticks.FrontWheelOut >= TWO_HUNDRED_HZ_TICKS)
	{
		SendCAN(FRONT_WHEEL_BOX);
		Clock_Ticks.FrontWheelOut = 0;
	}
	if (Clock_Ticks.SteeringSuspensionOut >= FIVE_HUNDRED_HZ_TICKS)
	{
		SendCAN(FRONT_SUSPENSION_BOX);
		SendCAN(STEERING_BOX);
		Clock_Ticks.SteeringSuspensionOut = 0;
	}

	RestartCpuTimer2();
	DINT;

}

