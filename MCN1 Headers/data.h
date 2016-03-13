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
	canfloat coolant_flow;
	canfloat motor_coolant_temp;
	canfloat motor_control_coolant_temp;
	canfloat motor_air_pressure_1;
	canfloat motor_air_pressure_2;
	canfloat motor_plate_temp_1;
	canfloat motor_plate_temp_2;
	canfloat strain_gauge_1;
	canfloat strain_gauge_2;
	canfloat strain_gauge_3;
	canfloat strain_gauge_4;
	canfloat strain_gauge_5;
	canfloat strain_gauge_6;
	canfloat v12;

	char gp_button;
} user_data_struct;

#endif /* DATA_H_ */
