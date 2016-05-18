/*
 * Stack.c
 *
 *  Created on: Apr 10, 2016
 *      Author: David
 */


#include "../RC Headers/all.h"

extern void _stack;
extern void _STACK_SIZE;

Uint16 *loc = ((Uint16 *)&_stack);
Uint16 stackIndex = 0;

void Stack_Initialize(){
	for (stackIndex = 0; stackIndex < ((Uint16)&_STACK_SIZE); stackIndex++){
		*loc = STACK_CHECK_VALUE;
		loc += 1;
	}
	return;
}

int Stack_Check(){

	int x = 1;
	int i = 0;
	loc = (Uint16 *)0x38d;
	for (i = 0; i < 19; i++){
		if (*loc != STACK_CHECK_VALUE){
			x = 0;
		}
		loc += 1;
	}

	return x;
}
