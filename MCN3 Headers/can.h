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

#define COMMAND_ID 							0x28E
#define HEARTBEAT_ID 						0x28D

#define TIRE_TEMPS_ID 						0x28A
#define TIRE_TEMPS_BOX	 					2
#define TIRE_TEMPS_TRS	 					TRS2

#define FLEX_SENSOR_BANK_1_ID				0x28B
#define FLEX_SENSOR_BANK_1_BOX				3
#define FLEX_SENSOR_BANK_1_TRS				TRS3

#define FLEX_SENSOR_BANK_2_ID				0x28C
#define FLEX_SENSOR_BANK_2_BOX				4
#define FLEX_SENSOR_BANK_2_TRS				TRS4

#endif /* CAN_H_ */
