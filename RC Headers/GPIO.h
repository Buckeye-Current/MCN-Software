/*
 * GPIO.h
 *
 *  Created on: Apr 27, 2016
 *      Author: David
 */

#ifndef RC_HEADERS_GPIO_H_
#define RC_HEADERS_GPIO_H_

//This function determines wether the GPIO switch corresponding to the throttle (GPIO 1) is turned on or not
//Returns 1 if turned on
//Returns 0 if turned off

void Gpio_Init(void);

int throttle_toggle(void);

#endif /* RC_HEADERS_GPIO_H_ */
