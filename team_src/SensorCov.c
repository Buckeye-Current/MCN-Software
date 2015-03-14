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
float voltage;

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
	ConfigGPIOSensor(410, 10000, 26, 0, 2); //Wheel Speed
	//ConfigGPIOSensor(410, 10000, 19, 0, 2); //Change CAN freq
}



void SensorCovMeasure()
{
	#define R1 10000.0 //Before ADC, Ohms
	#define R2 20000.0
	#define V5 5.08
	#define B 1568.583480 //Ohm
	#define PI 3.141593
	#define Vs 5.1 // Vdc ... Find out what this actually is

	SensorCovSystemInit();

	//todo USER: Sensor Conversion
	//update data_temp and ops_temp
	//use stopwatch to catch timeouts
	//waiting should poll isStopWatchComplete() to catch timeout and throw StopWatchError

	// Wheel Speed (rad/sec)
	//  deltaX / Time
	//  (2*pi/50 slots) * gpio_count = radians
	//  (1/sample rate) == (1/10000) = 0.0001 sec

	data_temp.front_wheel_speed.F32 = (GPIO26filter.filtered_value * ((2*PI)/50))/(0.0001);

	//Front suspension travel
	data_temp.front_suspension_travel.F32 = (B1RESULT/4096.0);

	data_temp.steering_angle.F32 = (A1RESULT/4096.0); //A1RESULT

	v_in = 3.3 * (A3RESULT/4096.0);	 				//Vm
	v_in = v_in * (15.6/10); 						//Vout
	data_temp.front_brake_pressure.F32 = ((v_in-.5)*3000)/(4); //P

	v_in = 3.3*(B1RESULT/4096.0);
	r_th = -1.0*(R1*R2*v_in)/((-1.0*R2*V5)+(R1*v_in)+(R2*v_in));
	data_temp.ambient_temperature.F32 = (3380.0)/(log((r_th/0.119286))) - 273.15;

	v_in = 3.3 * (B4RESULT/4096.0);
	data_temp.ambient_pressure.F32 = (v_in/(Vs*0.004)) + 0.04;

	v_in = 3.3 * (B2RESULT/4096.0);
	data_temp.radiator_air_pressure.F32 = (v_in/(Vs*0.004)) + 0.04;

	v_in = 3.3*(A0RESULT/4096.0);
	r_th = -1.0*(R1*R2*v_in)/((-1.0*R2*V5)+(R1*v_in)+(R2*v_in));
	data_temp.radiator_coolant_temp.F32 = (3435.0)/(log((r_th/0.0991912))) - 273.15;


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
