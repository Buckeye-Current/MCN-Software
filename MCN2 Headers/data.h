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
	canfloat motor_coolant_inlet_temp;
	canfloat motor_coolant_outlet_temp;
	canfloat controller_coolant_inlet_temp;
	canfloat controller_coolant_outlet_temp;
	canfloat contactor_box_temp;
	canfloat controller_coolant_flow_rate;
	canfloat motor_coolant_flow_rate;

	char gp_button;
} user_data_struct;

#endif /* DATA_H_ */
