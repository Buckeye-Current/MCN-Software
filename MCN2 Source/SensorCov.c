/*
 * SensorCov().c
 *
 *  Created on: Oct 30, 2013
 *      Author: Nathan
 */

#include "../MCN2 Headers/all.h"
#include "../MCN2 Headers/data.h"

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
	/*
	 * alpha = (1.0 - exp(-2.0 * PI * (CANFrequency / samplingFrequency))) * 2^16;
	 */
	// 50 Hz: 2027
	// 10 Hz: 410
	// 5 Hz: 206 = ALPHA_SYS
	initDSPfilter(&A0filter, 2027);
	initDSPfilter(&A1filter, 206);			// Controller Inlet Temp
	initDSPfilter(&A2filter, ALPHA_SYS);
	initDSPfilter(&A3filter, 206); 			// Motor Outlet Temp
	initDSPfilter(&A4filter, 206);
	initDSPfilter(&A5filter, 206);
	initDSPfilter(&A6filter, ALPHA_SYS);
	initDSPfilter(&A7filter, 410); 			// Motor Inlet Temp
	initDSPfilter(&B0filter, 2027);
	initDSPfilter(&B1filter, 410);			// Controller Outlet Temp
	initDSPfilter(&B2filter, 2027);			// Contactor Box Temp
	initDSPfilter(&B3filter, 2027);
	initDSPfilter(&B4filter, 2027);
	initDSPfilter(&B5filter, ALPHA_SYS);
	initDSPfilter(&B6filter, 2027);
	initDSPfilter(&B7filter, ALPHA_SYS);
	ConfigGPIOSensor(410, 10000, 26, 0, 2); // Coolant Flow Controller Loop
	ConfigGPIOSensor(410, 10000, 19, 0, 2); // Coolant Flow Motor Loop
}



void SensorCovMeasure()
{
	#define R1 10000.0 //Before ADC, Ohms
	#define R2 20000.0
	#define V5 5.08
	//#define B 1568.583480 //Ohm
	#define B 3435
	#define Vs 5.1 // Vdc ... Find out what this actually is

	SensorCovSystemInit();

	//todo USER: Sensor Conversion
	//update data_temp and ops_temp
	//use stopwatch to catch timeouts
	//waiting should poll isStopWatchComplete() to catch timeout and throw StopWatchError

	ratio = (A1RESULT/4096.0);
	r_th = (R1 / ratio) - R1;
	data_temp.controller_coolant_inlet_temp.F32 = B / (log(r_th/0.11929)) - 273.15;

	ratio = (B1RESULT/4096.0);
	r_th = (R1 / ratio) - R1;
	data_temp.controller_coolant_outlet_temp.F32 = B / (log(r_th/0.11929)) - 273.15;

	ratio = (A7RESULT/4096.0);
	r_th = (R1 / ratio) - R1;
	data_temp.motor_coolant_inlet_temp.F32 = B / (log(r_th/0.11929)) - 273.15;

	ratio = (A3RESULT/4096.0);
	r_th = (R1 / ratio) - R1;
	data_temp.motor_coolant_outlet_temp.F32 = B / (log(r_th/0.11929)) - 273.15;

	data_temp.controller_coolant_flow_rate.F32 = (GPIO26filter.filtered_value);

	data_temp.motor_coolant_flow_rate.F32 = (GPIO19filter.filtered_value);

	ratio = (B2RESULT/4096.0);
	r_th = (R1 / ratio) - R1;
	data_temp.contactor_box_temp.F32 = B / (log(r_th/0.11929)) - 273.15;

	data_temp.gp_button = READGPBUTTON();

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
