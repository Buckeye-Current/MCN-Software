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
	user_data.ain1.U32 = 0;
	user_data.ain2.U32 = 0;
	user_data.ain3.U32 = 0;
	user_data.ain4.U32 = 0;
	user_data.ain5.U32 = 0;
	user_data.ain6.U32 = 0;
	user_data.ain7.U32 = 0;
	user_data.ain8.U32 = 0;
	user_data.ain9.U32 = 0;
	user_data.ain10.U32 = 0;
	user_data.ain11.U32 = 0;
	user_data.ain12.U32 = 0;
	user_data.gp0.U32 = 0;
	user_data.gp1.U32 = 0;

}

