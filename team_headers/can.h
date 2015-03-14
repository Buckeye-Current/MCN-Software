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

#define COMMAND_ID 					0xD0
#define HEARTBEAT_ID 				0xCF

#define FRONT_SUSPENSION_ID 		0xC8
#define FRONT_SUSPENSION_BOX 		2
#define FRONT_SUSPENSION_TRS 		TRS2

#define STEERING_ID					0xC9
#define STEERING_BOX				3
#define STEERING_TRS				TRS3

#define FRONT_WHEEL_ID				0xCA
#define FRONT_WHEEL_BOX				4
#define FRONT_WHEEL_TRS				TRS4

#define FRONT_BRAKE_ID				0xCB
#define FRONT_BRAKE_BOX				5
#define FRONT_BRAKE_TRS				TRS5

//#define FRONT_ID		0xCC
//#define COOLANT_PRESSURES_BOX		6
//#define COOLANT_PRESSURES_TRS		TRS6

#define AMBIENT_ID					0xCD
#define AMBIENT_BOX					7
#define AMBIENT_TRS					TRS7

#define RADIATOR_ID			0xCE
#define RADIATOR_BOX		8
#define RADIATOR_TRS		TRS8



#endif /* CAN_H_ */
