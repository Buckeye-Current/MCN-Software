/*
 * clock.h
 *
 *  Created on: Nov 12, 2013
 *      Author: Nathan
 */

#ifndef CLOCK_H_
#define CLOCK_H_

void ClockSetup();

//todo USER: define clock
#define CLOCK_PERIOD 1000 //uS //so a tenth of a second

#define FIVE_HZ_TICKS			200	//5 Hz
#define FIVE_HUNDRED_HZ_TICKS	2   //500 Hz
#define TWO_HUNDRED_HZ_TICKS	5   //200 Hz
#define TEN_HZ_TICKS			100 //10 Hz

//todo USER: CLOCK_TICKS_CLEAR should have the same number of zeros as clock_struct has elements (as seen below)
//#define CLOCK_TICKS_CLEAR {0,0}
#define CLOCK_TICKS_CLEAR	{0}

typedef struct CLOCK_TICKS
{
	int AmbientRadiatorOut;
	int SteeringSuspensionOut;
	int FrontWheelOut;
	int FrontBrakeOut;

}clock_struct;


#endif /* CLOCK_H_ */
