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

#ifdef MCN1

#define COMMAND_ID 							0x102
#define HEARTBEAT_ID 						0x101

#define COOLANT_FLOW_ID 					0xFA
#define COOLANT_FLOW_BOX 					2
#define COOLANT_FLOX_TRS 					TRS2

#define POWERTRAIN_COOLANT_TEMP_ID			0xFB
#define POWERTRAIN_COOLANT_TEMP_BOX			3
#define POWERTRAIN_COOLANT_TEMP_BOX_TRS		TRS3

#define MOTOR_AIR_PRESSURES_ID				0xFC
#define MOTOR_AIR_PRESSURES_BOX				4
#define MOTOR_AIR_PRESSURES_TRS				TRS4

#define MOTOR_PLATE_TEMPS_ID				0xFD
#define MOTOR_PLATE_TEMPS_BOX				5
#define MOTOR_PLATE_TEMPS_TRS				TRS5

#define STRAIN_GAUGE_12_ID					0xFE
#define STRAIN_GAUGE_12_BOX					6
#define STRAIN_GAUGE_12_TRS					TRS6

#define STRAIN_GAUGE_34_ID					0xFF
#define STRAIN_GAUGE_34_BOX					7
#define STRAIN_GAUGE_34_TRS					TRS7

#define STRAIN_GAUGE_56_ID					0x100
#define STRAIN_GAUGE_56_BOX					8
#define STRAIN_GAUGE_56_TRS					TRS8

#define TRITIUM_ERRORS_ID					0x401
#define TRITIUM_ERRORS_BOX					9
#define TRITIUM_ERRORS_TRS					TRS9

#define TRITIUM_RESET_ID					0x503
#define TRITIUM_RESET_BOX					10
#define TRITIUM_RESET_TRS					TRS10

#define SUPPLY_ID							1284
#define SUPPLY_BOX							11
#define SUPPLY_TRS							TRS11

#endif

#ifdef MCN2

#endif

#ifdef MCN3

#endif
#endif /* CAN_H_ */
