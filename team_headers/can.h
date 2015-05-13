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

#define COMMAND_ID 		0x3E8
#define HEARTBEAT_ID 	0x3E7

#define AIN1_ID 		0x01
#define AIN1_BOX 		2
#define AIN1_TRS 		TRS2

#define AIN2_ID			0x02
#define AIN2_BOX		3
#define AIN2_TRS		TRS3

#define AIN3_ID			0x03
#define AIN3_BOX		4
#define AIN3_TRS		TRS4

#define AIN4_ID			0x04
#define AIN4_BOX		5
#define AIN4_TRS		TRS5

#define AIN5_ID			0x05
#define AIN5_BOX		6
#define AIN5_TRS		TRS6

#define AIN6_ID			0x06
#define AIN6_BOX		7
#define AIN6_TRS		TRS7

#define AIN7_ID			0x07
#define AIN7_BOX		8
#define AIN7_TRS		TRS8

#define AIN8_ID			0x08
#define AIN8_BOX		9
#define AIN8_TRS		TRS9

#define AIN9_ID			0x09
#define AIN9_BOX		10
#define AIN9_TRS		TRS10

#define AIN10_ID		0x0A
#define AIN10_BOX		11
#define AIN10_TRS		TRS11

#define AIN11_ID		0x0B
#define AIN11_BOX		12
#define AIN11_TRS		TRS12

#define AIN12_ID		0x0C
#define AIN12_BOX		13
#define AIN12_TRS		TRS13

#define GP0_ID			0x0D
#define GP0_BOX			14
#define GP0_TRS			TRS14

#define GP1_ID			0x0E
#define GP1_BOX			15
#define GP1_TRS			TRS15


#endif /* CAN_H_ */
