/*
 * CRC.h
 *
 *  Created on: Apr 17, 2016
 *      Author: David
 */

#ifndef TEAM_HEADERS_SAFETYVAR_H_
#define TEAM_HEADERS_SAFETYVAR_H_

typedef struct {

	Uint32 origVal;
	Uint32 inverseVal;

}SafetyVar32_t;

/// This function sets a new value for a given SafetyVar and computes
/// it's inverse to make sure the value
///
/// Input:	ptr (SafetyVar32_t *) - pointer to SafetyVar32_t type
void SafetyVar_NewValue(SafetyVar32_t *ptr, Uint32 value);

Uint32 SafetyVar_getValue(SafetyVar32_t *ptr);

int SafetyVar_CheckValue(SafetyVar32_t *ptr);



#endif /* TEAM_HEADERS_SAFETYVAR_H_ */
