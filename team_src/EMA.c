/*
 * EMA.c
 *
 *  Created on: Mar 20, 2016
 *      Author: David
 */

#include "all.h"

static filter *currentFilter;
static filter *headFilter;

static int counter = 0;

void EMA_Filter_Init(filter *f, Uint16 sampleRate){

	f->_input = 0;
	f->_sampleRate = sampleRate;
	f->_lastSampleTime = 0;
	f->_alpha = _IQ(1.0) - _IQexp(_IQdiv(_IQint(sampleRate),_IQint(CLOCK_PERIOD)) * _IQ(3.14) * _IQ(-2.0));
	f->_filteredOutput = 0;

	if (headFilter == NULL){

		headFilter = f;
	}
	else {
		currentFilter = headFilter;
		while(currentFilter->_nextFilter != NULL)
		{
			currentFilter = currentFilter->_nextFilter;
		}
		currentFilter->_nextFilter = f;
	}
}

void EMA_Filter_Update(void)
{
	counter++;
	Uint32 currentTime = counter * CLOCK_PERIOD;

	currentFilter = headFilter;
	while(currentFilter != NULL)
	{
		if((currentTime - currentFilter->_lastSampleTime) > 0)
		{
			currentFilter->_lastSampleTime = currentTime;

			_iq newScale = _IQmpy(currentFilter->_alpha, currentFilter->_input);
			_iq oldScale = _IQmpy((_IQ(1.0) - currentFilter->_alpha), currentFilter->_filteredOutput);
			currentFilter->_filteredOutput = newScale + oldScale;
		}
		currentFilter = currentFilter->_nextFilter;
	}
}

float EMA_Filter_NewInput(filter *f, float input)
{
	return f->_input = _IQ(input);
}

float EMA_Filter_GetFilteredOutput(filter *f)
{
	return _IQtoF(f->_filteredOutput);
}


