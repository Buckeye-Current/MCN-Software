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
	canfloat steering_angle;
	canfloat front_wheel_speed;
	canfloat front_brake_pressure;
	canfloat ambient_temperature;
	canfloat ambient_pressure;
	canfloat radiator_air_pressure;
	canfloat radiator_coolant_temp;
	char gp_button;
} user_data_struct;

#endif /* DATA_H_ */
