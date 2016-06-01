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
	canfloat front_suspension_travel;
	canfloat rear_suspension_travel;
	canfloat steering_angle;
	canfloat ambient_temperature;
	canfloat ambient_pressure;
	canfloat motor_inlet_pressure;

	char gp_button;
} user_data_struct;

#endif /* DATA_H_ */
