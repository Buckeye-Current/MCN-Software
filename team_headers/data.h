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
	canfloat ain1;
	canfloat ain2;
	canfloat ain3;
	canfloat ain4;
	canfloat ain5;
	canfloat ain6;
	canfloat ain7;
	canfloat ain8;
	canfloat ain9;
	canfloat ain10;
	canfloat ain11;
	canfloat ain12;
	canfloat gp0;
	canfloat gp1;
	char gp_button;
} user_data_struct;

#endif /* DATA_H_ */
