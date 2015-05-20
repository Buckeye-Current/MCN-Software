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
	initDSPfilter(&A0filter, ALPHA_SYS);		//12standby
	initDSPfilter(&A1filter, ALPHA_SYS); 		//12v_shunt
	//initDSPfilter(&A2filter, ALPHA_SYS);
	initDSPfilter(&A3filter, ALPHA_REAR_BRAKE); // REAR_BRAKE
	//initDSPfilter(&A4filter, ALPHA_SYS);
	//initDSPfilter(&A5filter, ALPHA_SYS);
	//initDSPfilter(&A6filter, ALPHA_SYS);
	initDSPfilter(&A7filter, ALPHA_REAR_SUSP); 	//REAR susp
	initDSPfilter(&B0filter, ALPHA_SYS);		//12v
	//initDSPfilter(&B1filter, ALPHA_SYS);
	initDSPfilter(&B2filter, ALPHA_SYS); 		//DC_DC_TEMP
	initDSPfilter(&B3filter, ALPHA_SYS);		//3_3v
	initDSPfilter(&B4filter, ALPHA_SYS);		//2_3v
	//initDSPfilter(&B5filter, ALPHA_SYS);
	initDSPfilter(&B6filter, ALPHA_SYS);		//1_5V
	//initDSPfilter(&B7filter, ALPHA_SYS);
	ConfigGPIOSensor(410, 10000, 26, 0, 2);		//wheel speed
	//ConfigGPIOSensor(410, 10000, 19, 0, 2);

	//Frame Fault
	GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 0;	//GPIO
	GpioCtrlRegs.GPADIR.bit.GPIO19 = 0; 	//input
	GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 0;	//Synch to SYSCLKOUT only
	GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;		//enable pull up											//frame fault
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

	data_temp.DC_DC_temp.F32 = DC_TEMP_VALUE; 	// need more information about resistors and thermistors.

	data_temp.frame_fault = FRAME_FAULT_VALUE;

	#define BRAKE_COV (3.3*(5.6+10))/(5.6*0.015*4096)
	data_temp.rear_brake.F32 = REAR_BRAKE_VALUE*BRAKE_COV;

	data_temp.rear_susp.F32 = REAR_SUSP_VALUE/4096.0;

	#define V12_COV (3.3*(36+10))/(36*4096)
	data_temp.v12.F32 = V12_VALUE * V12_COV;
	data_temp.v12_standby.F32 = V12_STANDBY_VALUE* V12_COV;

	#define SHUNT_COV (3.3)/(4096*20*.01)
	data_temp.v12_shunt.F32 =  V12_SHUNT_VALUE * SHUNT_COV;
	#define V1_5_COV (3.3*(5.6+10))/(5.6*4096)
	data_temp.v1_5.F32 = V1_5_VALUE *  V1_5_COV;

	#define VOLT_COV (3.3)/(4096)
	data_temp.v2_3.F32 = V2_3_VALUE * VOLT_COV;
	data_temp.v3_3.F32 = V3_3_VALUE * VOLT_COV;

	data_temp.wheel_speed.F32 = WHEEL_SPEED_VALUE; //need more information about tone wheel

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
