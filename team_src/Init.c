/*
 * Init.c
 *
 *  Created on: Oct 30, 2013
 *      Author: Nathan, edited by David
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
	user_data.CellTemp1.F32 = 0;
	user_data.CellTemp2.F32 = 0;
	user_data.CellTemp3.F32 = 0;
	user_data.CellTemp4.F32 = 0;
	user_data.CellTemp5.F32 = 0;
	user_data.CellTemp6.F32 = 0;
	user_data.CellTemp7.F32 = 0;
	user_data.CellTemp8.F32 = 0;
	user_data.CellTemp9.F32 = 0;
	user_data.CellTemp10.F32 = 0;
	user_data.CellTemp11.F32 = 0;
	user_data.CellTemp12.F32 = 0;
	user_data.CellTemp13.F32 = 0;
	user_data.CellTemp14.F32 = 0;
	user_data.CellTemp15.F32 = 0;
	user_data.CellTemp16.F32 = 0;
	user_data.CellTemp17.F32 = 0;
	user_data.CellTemp18.F32 = 0;
	user_data.CellTemp19.F32 = 0;
	user_data.CellTemp20.F32 = 0;
	user_data.CellTemp21.F32 = 0;
	user_data.CellTemp22.F32 = 0;
	user_data.CellTemp23.F32 = 0;
	user_data.CellTemp24.F32 = 0;
	user_data.CellTemp25.F32 = 0;
	user_data.CellTemp26.F32 = 0;
	user_data.CellTemp27.F32 = 0;
	user_data.CellTemp28.F32 = 0;
	user_data.CellTemp29.F32 = 0;
	user_data.CellTemp30.F32 = 0;
	user_data.CellTemp31.F32 = 0;
	user_data.CellTemp32.F32 = 0;
	user_data.CellTemp33.F32 = 0;
	user_data.CellTemp34.F32 = 0;
	user_data.CellTemp35.F32 = 0;
	user_data.CellTemp36.F32 = 0;
	user_data.CellTemp37.F32 = 0;
	user_data.CellTemp38.F32 = 0;
	user_data.CellTemp39.F32 = 0;
	user_data.CellTemp40.F32 = 0;
	user_data.CellTemp41.F32 = 0;
	user_data.CellTemp42.F32 = 0;
	user_data.CellTemp43.F32 = 0;
	user_data.CellTemp44.F32 = 0;
	user_data.CellTemp45.F32 = 0;
	user_data.CellTemp46.F32 = 0;
	user_data.CellTemp47.F32 = 0;
	user_data.CellTemp48.F32 = 0;

	user_data.throttle_percent_cap.U32 = 0;
	user_data.throttle_percent_ratio.U32 = 0;
	user_data.throttle_output.U32 = 0;
	user_data.no_filter.U32 = 0;
	user_data.RPM.U32 = 0;
	user_data.max_cell_temp.F32 = 0;
	user_data.battery_limit.U32 = 0;
	user_data.stack_limit.U32 = 0;
	user_data.timeout_limit.U32 = 0;
	user_data.throttle_lock.U32 = 0;
	user_data.driver_control_limits.U32 = 0;
	user_data.throttle_flag.U32 = 0;
}

