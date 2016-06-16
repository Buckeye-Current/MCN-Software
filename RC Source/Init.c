/*
 * Init.c
 *
 *  Created on: Oct 30, 2013
 *      Author: Nathan, edited by David
 */

#include "../RC Headers/all.h"


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
	user_data.CellTemp1.I32 = MIN_CELL_TEMP;
	user_data.CellTemp2.F32 = MIN_CELL_TEMP;
	user_data.CellTemp3.I32 = MIN_CELL_TEMP;
	user_data.CellTemp4.I32 = MIN_CELL_TEMP;
	user_data.CellTemp5.I32 = MIN_CELL_TEMP;
	user_data.CellTemp6.I32 = MIN_CELL_TEMP;
	user_data.CellTemp7.I32 = MIN_CELL_TEMP;
	user_data.CellTemp8.I32 = MIN_CELL_TEMP;
	user_data.CellTemp9.I32 = MIN_CELL_TEMP;
	user_data.CellTemp10.I32 = MIN_CELL_TEMP;
	user_data.CellTemp11.I32 = MIN_CELL_TEMP;
	user_data.CellTemp12.I32 = MIN_CELL_TEMP;
	user_data.CellTemp13.I32 = MIN_CELL_TEMP;
	user_data.CellTemp14.I32 = MIN_CELL_TEMP;
	user_data.CellTemp15.I32 = MIN_CELL_TEMP;
	user_data.CellTemp16.I32 = MIN_CELL_TEMP;
	user_data.CellTemp17.I32 = MIN_CELL_TEMP;
	user_data.CellTemp18.I32 = MIN_CELL_TEMP;
	user_data.CellTemp19.I32 = MIN_CELL_TEMP;
	user_data.CellTemp20.I32 = MIN_CELL_TEMP;
	user_data.CellTemp21.I32 = MIN_CELL_TEMP;
	user_data.CellTemp22.I32 = MIN_CELL_TEMP;
	user_data.CellTemp23.I32 = MIN_CELL_TEMP;
	user_data.CellTemp24.I32 = MIN_CELL_TEMP;
	user_data.CellTemp25.I32 = MIN_CELL_TEMP;
	user_data.CellTemp26.I32 = MIN_CELL_TEMP;
	user_data.CellTemp27.I32 = MIN_CELL_TEMP;
	user_data.CellTemp28.I32 = MIN_CELL_TEMP;
	user_data.CellTemp29.I32 = MIN_CELL_TEMP;
	user_data.CellTemp30.I32 = MIN_CELL_TEMP;
	user_data.CellTemp31.I32 = MIN_CELL_TEMP;
	user_data.CellTemp32.I32 = MIN_CELL_TEMP;
	user_data.CellTemp33.I32 = MIN_CELL_TEMP;
	user_data.CellTemp34.I32 = MIN_CELL_TEMP;
	user_data.CellTemp35.I32 = MIN_CELL_TEMP;
	user_data.CellTemp36.I32 = MIN_CELL_TEMP;
	user_data.CellTemp37.I32 = MIN_CELL_TEMP;
	user_data.CellTemp38.I32 = MIN_CELL_TEMP;
	user_data.CellTemp39.I32 = MIN_CELL_TEMP;
	user_data.CellTemp40.I32 = MIN_CELL_TEMP;
	user_data.CellTemp41.I32 = MIN_CELL_TEMP;
	user_data.CellTemp42.I32 = MIN_CELL_TEMP;
	user_data.CellTemp43.I32 = MIN_CELL_TEMP;
	user_data.CellTemp44.I32 = MIN_CELL_TEMP;
	user_data.CellTemp45.I32 = MIN_CELL_TEMP;
	user_data.CellTemp46.I32 = MIN_CELL_TEMP;
	user_data.CellTemp47.I32 = MIN_CELL_TEMP;
	user_data.CellTemp48.I32 = MIN_CELL_TEMP;

	user_data.throttle_percent_cap.I32 = 0;
	user_data.throttle_percent_ratio.I32 = 0;
	user_data.throttle_output.I32 = 0;
	user_data.no_filter.I32 = 0;
	user_data.RPM.I32 = 0;
	user_data.rpm_limit.I32 = 0;
	user_data.max_cell_temp.F32 = MIN_CELL_TEMP;
	user_data.battery_limit.I32 = 0;
	user_data.stack_limit.I32 = 0;
	user_data.timeout_limit.I32 = 0;
	user_data.throttle_lock.I32 = 0;
	user_data.driver_control_limits.I32 = 0;
	user_data.throttle_flag.I32 = 0;
}

