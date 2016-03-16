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

#ifdef MCN2

#define COMMAND_ID 							0x25D
#define HEARTBEAT_ID 						0x25C

#define MOTOR_COOLANT_TEMPS_ID 				0x258
#define MOTOR_COOLANT_TEMPS_BOX 			2
#define MOTOR_COOLANT_TEMPS_TRS 			TRS2

#define CONTROLLER_COOLANT_TEMPS_ID			0x259
#define CONTROLLER_COOLANT_TEMPS_BOX		3
#define CONTROLLER_COOLANT_TEMPS_TRS		TRS3

#define CONTACTOR_BOX_TEMP_ID				0x25A
#define CONTACTOR_BOX_TEMP_BOX				4
#define CONTACTOR_BOX_TEMP_TRS				TRS4

#define COOLANT_FLOWS_ID					0x25B
#define COOLANT_FLOWS_BOX					5
#define COOLANT_FLOWS_TRS					TRS5

#endif

#ifdef MCN1

#endif

#ifdef MCN3

#endif
#endif /* CAN_H_ */
