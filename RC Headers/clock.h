/*
 * clock.h
 *
 *  Created on: Nov 12, 2013
 *      Author: Nathan, edited by David
 */

#ifndef CLOCK_H_
#define CLOCK_H_

void ClockSetup();

//todo USER: define clock
#define CLOCK_PERIOD 5000 //uS //

#define THROTTLE_TICKS		10	//20hz
#define STATUS_TICKS 		200	//1hz
#define FILTER_TICKS		1

//todo USER: CLOCK_TICKS_CLEAR should have the same number of zeros as clock_struct has elements (as seen below)
//#define CLOCK_TICKS_CLEAR {0,0}
#define CLOCK_TICKS_CLEAR	{0,0}

typedef struct CLOCK_TICKS
{
	int DataOutThrottle;
	int DataOutLimits;
}clock_struct;


#endif /* CLOCK_H_ */
