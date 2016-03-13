/*
 * SensorCov().c
 *
 *  Created on: Oct 30, 2013
 *      Author: Nathan
 */

#include "../MCN1 Headers/all.h"

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
	initDSPfilter(&A0filter, 2027); //Strain Gauge 6
	initDSPfilter(&A1filter, 206); //Motor Plate Temp 2
	initDSPfilter(&A2filter, ALPHA_SYS);
	initDSPfilter(&A3filter, 206); //Motor Plate Temp 1
	initDSPfilter(&A4filter, 206); //Motor Coolant Temp
	initDSPfilter(&A5filter, 206); //Motor Controller Coolant Temp
	initDSPfilter(&A6filter, ALPHA_SYS); //12v
	initDSPfilter(&A7filter, 410); //Motor Air Pressure 1
	initDSPfilter(&B0filter, 2027); //Strain Gauge 5
	initDSPfilter(&B1filter, 410); //Motor Air Pressure 2
	initDSPfilter(&B2filter, 2027); //Strain Gauge 1
	initDSPfilter(&B3filter, 2027); //Strain Gauge 4
	initDSPfilter(&B4filter, 2027); //Strain Gauge 3
	initDSPfilter(&B5filter, ALPHA_SYS);
	initDSPfilter(&B6filter, 2027); //Strain Gauge 2
	initDSPfilter(&B7filter, ALPHA_SYS);
	ConfigGPIOSensor(410, 10000, 26, 0, 2); // Coolant Flow
	ConfigGPIOSensor(410, 10000, 19, 0, 2);
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

	data_temp.controller_coolant_flow_rate.F32 = (GPIO26filter.filtered_value)

	data_temp.coolant_flow.F32 = (GPIO26filter.filtered_value*0.283);

	v_in = (A4RESULT/4096.0);
	r_th = (10000 * v_in) / (-1*v_in+1);
	data_temp.motor_coolant_temp.F32 = (3435.0)/(log((r_th/0.0991912))) - 273.15;

	v_in = (A5RESULT/4096.0);
	//r_th = -1.0*(R1*R2*v_in)/((-1.0*R2*V5)+(R1*v_in)+(R2*v_in));
	r_th = (10000 * v_in) / (-1*v_in+1);
	data_temp.motor_control_coolant_temp.F32 = (3435.0)/(log((r_th/0.0991912))) - 273.15;

	v_in = 3.3*(A3RESULT/4096.0);
	r_th = -1.0*(R1*R2*v_in)/((-1.0*R2*V5)+(R1*v_in)+(R2*v_in));
	data_temp.motor_plate_temp_1.F32 = (3380.0)/(log((r_th/0.119286))) - 273.15;

	v_in = 3.3*(A1RESULT/4096.0);
	r_th = -1.0*(R1*R2*v_in)/((-1.0*R2*V5)+(R1*v_in)+(R2*v_in));
	data_temp.motor_plate_temp_2.F32 = (3380.0)/(log((r_th/0.119286))) - 273.15;

	v_in = 3.3 * (A7RESULT/4096.0);
	data_temp.motor_air_pressure_1.F32 = (v_in/(Vs*0.004)) + 0.04;

	v_in = 3.3 * (B1RESULT/4096.0);
	data_temp.motor_air_pressure_2.F32 = (v_in/(Vs*0.004)) + 0.04;

	data_temp.strain_gauge_1.F32 = 0;
	data_temp.strain_gauge_2.F32 = 0;
	data_temp.strain_gauge_3.F32 = 0;
	data_temp.strain_gauge_4.F32 = 0;
	data_temp.strain_gauge_5.F32 = 0;
	data_temp.strain_gauge_6.F32 = 0;

	v_in = 3.3 * (A6RESULT/4096.0);
	data_temp.v12.F32 = v_in*((36+10)/10);

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
