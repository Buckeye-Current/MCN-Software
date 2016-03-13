/*
 * Init.c
 *
 *  Created on: Oct 30, 2013
 *      Author: Nathan
 */

#include "../MCN1 Headers/all.h"


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
	user_data.coolant_flow.U32 = 0;
	user_data.motor_air_pressure_1.U32 = 0;
	user_data.motor_air_pressure_2.U32 = 0;
	user_data.motor_plate_temp_1.U32 = 0;
	user_data.motor_plate_temp_2.U32 = 0;
	user_data.motor_control_coolant_temp.U32 = 0;
	user_data.motor_coolant_temp.U32 = 0;
	user_data.strain_gauge_1.U32 = 0;
	user_data.strain_gauge_2.U32 = 0;
	user_data.strain_gauge_3.U32 = 0;
	user_data.strain_gauge_4.U32 = 0;
	user_data.strain_gauge_5.U32 = 0;
	user_data.strain_gauge_6.U32 = 0;
}

