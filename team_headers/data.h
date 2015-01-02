/*
 * data.h
 *
 *  Created on: Oct 30, 2013
 *      Author: Nathan
 */

#ifndef DATA_H_
#define DATA_H_


typedef struct USER_DATA
{
	float coolant_flow;
	float motor_coolant_temp;
	float motor_control_coolant_temp;
	float radiator_coolant_temp;
	float coolant_pressure_1;
	float coolant_pressure_2;
	char gp_button;
} user_data_struct;

#endif /* DATA_H_ */
