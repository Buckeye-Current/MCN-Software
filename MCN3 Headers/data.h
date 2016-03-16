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
	canfloat front_tire_temp;
	canfloat rear_tire_temp;
	canfloat flex_sensor_1;
	canfloat flex_sensor_2;
	canfloat flex_sensor_3;

	char gp_button;
} user_data_struct;

#endif /* DATA_H_ */
