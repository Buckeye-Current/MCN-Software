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

#define COMMAND_ID 							0x22B
#define HEARTBEAT_ID 						0x22A

#define SUSPENSION_TRAVELS_ID 				0x226
#define SUSPENSION_TRAVELS_BOX 				2
#define SUSPENSION_TRAVELS_TRS 				TRS2

#define STEERING_ID							0x227
#define STEERING_BOX						3
#define STEERING_TRS						TRS3

#define AMBIENT_MEASUREMENTS_ID				0x228
#define AMBIENT_MEASUREMENTS_BOX			4
#define AMBIENT_MEASUREMENTS_TRS			TRS4

#define COOLANT_PRESSURES_ID				0x229
#define COOLANT_PRESSURES_BOX				5
#define COOLANT_PRESSURES_TRS				TRS5

#endif /* CAN_H_ */
