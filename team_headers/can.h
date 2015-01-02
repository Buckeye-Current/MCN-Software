/*
 * can.h
 *
 *  Created on: Nov 13, 2013
 *      Author: Nathan
 */

#ifndef CAN_H_
#define CAN_H_

void CANSetup();
char FillCAN(unsigned int Mbox);
void FillCANData();
void FillSendCAN(unsigned int Mbox);
void ClearMailBoxes();
void BUS_OFF();

//todo USER: DEFINE IDs for all output
//           DEFINE mailboxes for all output except heartbeat and command
//			 Mailboxes and ID's 0 or 1 are reserved for system use.

#define COMMAND_ID 		0x1
#define HEARTBEAT_ID 	0x0

#define COOLANT_FLOW_ID 		0x3E2
#define COOLANT_FLOW_BOX 		2
#define COOLANT_FLOX_TRS 		TRS2

#define MOTOR_TEMP_ID			0x3E3
#define MOTOR_TEMP_BOX			3
#define MOTOR_TEMP_TRS			TRS3

#define MOTOR_CONT_TEMP_ID		0x3E4
#define MOTOR_CONT_TEMP_BOX		4
#define MOTOR_CONT_TEMP_TRS		TRS4

#define RADIATOR_TEMP_ID		0x3E5
#define RADIATOR_TEMP_BOX		5
#define RADIATOR_TEMP_TRS		TRS5

#define COOLANT_PRESSURES_ID		0x3E6
#define COOLANT_PRESSURES_BOX	6
#define COOLANT_PRESSURES_TRS	TRS6


#endif /* CAN_H_ */
