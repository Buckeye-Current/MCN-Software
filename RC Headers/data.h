/*
 * data.h
 *
 *  Created on: Oct 30, 2013
 *      Author: Nathan, edited by David
 */

#ifndef DATA_H_
#define DATA_H_

typedef union CANFLOAT
{
	float F32;
	long I32;
} canfloat;

typedef struct USER_DATA
{
	canfloat CellTemp1;
	canfloat CellTemp2;
	canfloat CellTemp3;
	canfloat CellTemp4;
	canfloat CellTemp5;
	canfloat CellTemp6;
	canfloat CellTemp7;
	canfloat CellTemp8;
	canfloat CellTemp9;
	canfloat CellTemp10;
	canfloat CellTemp11;
	canfloat CellTemp12;
	canfloat CellTemp13;
	canfloat CellTemp14;
	canfloat CellTemp15;
	canfloat CellTemp16;
	canfloat CellTemp17;
	canfloat CellTemp18;
	canfloat CellTemp19;
	canfloat CellTemp20;
	canfloat CellTemp21;
	canfloat CellTemp22;
	canfloat CellTemp23;
	canfloat CellTemp24;
	canfloat CellTemp25;
	canfloat CellTemp26;
	canfloat CellTemp27;
	canfloat CellTemp28;
	canfloat CellTemp29;
	canfloat CellTemp30;
	canfloat CellTemp31;
	canfloat CellTemp32;
	canfloat CellTemp33;
	canfloat CellTemp34;
	canfloat CellTemp35;
	canfloat CellTemp36;
	canfloat CellTemp37;
	canfloat CellTemp38;
	canfloat CellTemp39;
	canfloat CellTemp40;
	canfloat CellTemp41;
	canfloat CellTemp42;
	canfloat CellTemp43;
	canfloat CellTemp44;
	canfloat CellTemp45;
	canfloat CellTemp46;
	canfloat CellTemp47;
	canfloat CellTemp48;

	canfloat throttle_percent_cap;
	canfloat throttle_percent_ratio;
	canfloat throttle_output;
	canfloat no_filter;
	canfloat RPM;
	canfloat max_cell_temp;
	canfloat battery_limit;
	canfloat rpm_limit;
	canfloat stack_limit;
	canfloat timeout_limit;
	canfloat throttle_lock;
	canfloat driver_control_limits;
	canfloat throttle_flag;
	char gp_button;
} user_data_struct;

#endif /* DATA_H_ */
