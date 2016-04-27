/*
 * GPIO.h
 *
 *  Created on: Apr 27, 2016
 *      Author: David
 */

#ifndef TEAM_HEADERS_GPIO_H_
#define TEAM_HEADERS_GPIO_H_

//This function determines wether the GPIO switch corresponding to the throttle (GPIO 1) is turned on or not
//Returns 1 if turned on
//Returns 0 if turned off

int throttle_toggle(void);

#endif /* TEAM_HEADERS_GPIO_H_ */
