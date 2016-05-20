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
#define CLOCK_PERIOD 10000 //uS //so a hundredth of a second

#define FIVE_HZ_TICKS			20  // 5 Hz

//todo USER: CLOCK_TICKS_CLEAR should have the same number of zeros as clock_struct has elements (as seen below)
//#define CLOCK_TICKS_CLEAR {0,0}
#define CLOCK_TICKS_CLEAR	{0}

typedef struct CLOCK_TICKS
{
	int group1_ticks;
}clock_struct;


#endif /* CLOCK_H_ */
