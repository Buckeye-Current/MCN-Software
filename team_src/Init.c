/*
 * Init.c
 *
 *  Created on: Oct 30, 2013
 *      Author: Nathan
 */

#include "all.h"


user_ops_struct user_ops;
user_data_struct user_data;

void Initialize()
{
	OperationsSetup();
	DataSetup();
	CANSetup();
	ClockSetup();
	StartPowerDownInt();			//start power down interrupt, this will change state to PowerDown if necessary
	StopWatchSetUp(10);
}

void OperationsSetup()
{
	//todo USER: OperationsSetup()
	//add here and ops.h
	SetupSystemOperations();
}

void DataSetup()
{
	//todo USER: DataSetup()
	//add here and data.h
	user_data.ambient_pressure.U32 = 0;
	user_data.ambient_temperature.U32 = 0;
	user_data.front_brake_pressure.U32 = 0;
	user_data.front_suspension_travel.U32 = 0;
	user_data.front_wheel_speed.U32 = 0;
	user_data.radiator_air_pressure.U32 = 0;
	user_data.radiator_coolant_temp.U32 = 0;
	user_data.radiator_coolant_temp.U32 = 0;
}

