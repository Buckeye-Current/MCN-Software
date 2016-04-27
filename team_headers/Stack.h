/*
 * Stack.h
 *
 *  Created on: Apr 10, 2016
 *      Author: David
 */

#ifndef TEAM_HEADERS_STACK_H_
#define TEAM_HEADERS_STACK_H_

#define STACK_CHECK_VALUE	(0xAAAA)


//initializes a variable to a location on the stack
void Stack_Initialize(void);

//checks to see if that variable is in the same spot. Returns 1 if true, 0 if false
int Stack_Check(void);

#endif /* TEAM_HEADERS_STACK_H_ */
