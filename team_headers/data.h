/*
 * data.h
 *
 *  Created on: Oct 30, 2013
 *      Author: Nathan
 */

#ifndef DATA_H_
#define DATA_H_

typedef union CANFLOAT
{
	float F32;
	unsigned long U32;
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
	canfloat BIM1;
	canfloat BIM2;
	canfloat BIM3;
	canfloat BIM4;
	canfloat BIM5;
	canfloat throttle_percent_cap;
	canfloat throttle_percent_ratio;
	canfloat throttle_output;
	canfloat no_filter;
	canfloat RPM;
	canfloat max_cell_temp;
	canfloat battery_limit;
	canfloat rpm_limit;
	canfloat status_limit;
	canfloat throttle_lock;
	canfloat driver_control_limits;
	char gp_button;
} user_data_struct;

#endif /* DATA_H_ */
