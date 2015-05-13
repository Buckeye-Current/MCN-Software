/*
 * SensorCov().c
 *
 *  Created on: Oct 30, 2013
 *      Author: Nathan
 */

#include "all.h"

extern DSPfilter A0filter;
extern DSPfilter A1filter;
extern DSPfilter A2filter;
extern DSPfilter A3filter;
extern DSPfilter A4filter;
extern DSPfilter A5filter;
extern DSPfilter A6filter;
extern DSPfilter A7filter;
extern DSPfilter B0filter;
extern DSPfilter B1filter;
extern DSPfilter B2filter;
extern DSPfilter B3filter;
extern DSPfilter B4filter;
extern DSPfilter B5filter;
extern DSPfilter B6filter;
extern DSPfilter B7filter;
extern DSPfilter GPIO19filter;
extern DSPfilter GPIO26filter;

user_ops_struct ops_temp;
user_data_struct data_temp;

int max = 2000, min = 2000;
float r_th;
float v_in;

void SensorCov()
{
	SensorCovInit(4);
	while (sys_ops.State == STATE_SENSOR_COV)
	{
		LatchStruct();
		SensorCovMeasure();
		UpdateStruct();
		FillCANData();
	}
	SensorCovDeInit();
}

void SensorCovInit()
{
	//todo USER: SensorCovInit()
	SystemSensorInit(SENSOR_COV_STOPWATCH);
	initDSPfilter(&A0filter, ALPHA_SYS);
	initDSPfilter(&A1filter, ALPHA_SYS);
	initDSPfilter(&A2filter, ALPHA_SYS);
	initDSPfilter(&A3filter, ALPHA_SYS);
	initDSPfilter(&A4filter, ALPHA_SYS);
	initDSPfilter(&A5filter, ALPHA_SYS);
	initDSPfilter(&A6filter, ALPHA_SYS);
	initDSPfilter(&A7filter, ALPHA_SYS);
	initDSPfilter(&B0filter, ALPHA_SYS);
	initDSPfilter(&B1filter, ALPHA_SYS);
	initDSPfilter(&B2filter, ALPHA_SYS);
	initDSPfilter(&B3filter, ALPHA_SYS);
	initDSPfilter(&B4filter, ALPHA_SYS);
	initDSPfilter(&B5filter, ALPHA_SYS);
	initDSPfilter(&B6filter, ALPHA_SYS);
	initDSPfilter(&B7filter, ALPHA_SYS);
	ConfigGPIOSensor(410, 10000, 26, 0, 2);
	ConfigGPIOSensor(410, 10000, 19, 0, 2);
}



void SensorCovMeasure()
{
	#define R1 10000.0 //Before ADC, Ohms
	#define R2 20000.0
	#define V5 5.08
	#define B 1568.583480 //Ohm

	SensorCovSystemInit();

	//todo USER: Sensor Conversion
	//update data_temp and ops_temp
	//use stopwatch to catch timeouts
	//waiting should poll isStopWatchComplete() to catch timeout and throw StopWatchError

	data_temp.ain1.F32 = A7RESULT;
	data_temp.ain2.F32 = A3RESULT;
	data_temp.ain3.F32 = A1RESULT;
	data_temp.ain4.F32 = B1RESULT;
	data_temp.ain5.F32 = B2RESULT;
	data_temp.ain6.F32 = B6RESULT;
	data_temp.ain7.F32 = B4RESULT;
	data_temp.ain8.F32 = B3RESULT;
	data_temp.ain9.F32 = B0RESULT;
	data_temp.ain10.F32 = A0RESULT;
	data_temp.ain11.F32 = A4RESULT;
	data_temp.ain12.F32 = A5RESULT;
	data_temp.gp0.F32 = GPIO19filter.filtered_value;
	data_temp.gp1.F32 = GPIO26filter.filtered_value;





	data_temp.gp_button = READGPBUTTON();
	/*
	if(A7RESULT > max)
	{
		max = A7RESULT;
	}
	if(A7RESULT < min)
	{
		min = A7RESULT;
	}
	*/
	PerformSystemChecks();
}

void LatchStruct()
{
	LatchSystemStruct();
	ops_temp = user_ops;
	data_temp = user_data;
}

void UpdateStruct()
{
	SaveOpStates();
	user_data = data_temp;
	//todo USER: UpdateStruct
	//update with node specific op changes

	//if ops is not changed outside of sensor conversion copy temp over, otherwise don't change

	//Change bit is only set by ops changes outside of SensorCov.


	DetermineOpStates();
}

void SensorCovDeInit()
{
	//todo USER: SensorCovDeInit()
	SystemSensorDeInit();
}
