/*
 * Init.c
 *
 *  Created on: Oct 30, 2013
 *      Author: Nathan
 */

#include "../MCN2 Headers/all.h"


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
	user_data.motor_coolant_inlet_temp.U32 = 0;
	user_data.motor_coolant_outlet_temp.U32 = 0;
	user_data.controller_coolant_inlet_temp.U32 = 0;
	user_data.controller_coolant_outlet_temp.U32 = 0;
	user_data.contactor_box_temp.U32 = 0;
	user_data.controller_coolant_flow_rate.U32 = 0;
	user_data.motor_coolant_flow_rate.U32 = 0;
}

