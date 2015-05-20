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
	user_data.DC_DC_temp.U32 = 0;
	user_data.frame_fault = 0;
	user_data.rear_brake.U32 = 0;
	user_data.rear_susp.U32 = 0;
	user_data.v12.U32 = 0;
	user_data.v12_shunt.U32 = 0;
	user_data.v12_standby.U32 = 0;
	user_data.v1_5.U32 = 0;
	user_data.v2_3.U32 = 0;
	user_data.v3_3.U32 = 0;
	user_data.wheel_speed.U32 = 0;
}

