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

#define CellTemp1_ID 		812
#define CellTemp1_BOX 		2
#define CellTemp1_TRS 		TRS2

#define CellTemp2_ID 		813
#define CellTemp2_BOX 		3
#define CellTemp2_TRS 		TRS3

#define CellTemp3_ID 		814
#define CellTemp3_BOX 		4
#define CellTemp3_TRS 		TRS4

#define CellTemp4_ID 		815
#define CellTemp4_BOX 		5
#define CellTemp4_TRS 		TRS5

#define CellTemp5_ID 		816
#define CellTemp5_BOX 		6
#define CellTemp5_TRS 		TRS6

#define CellTemp6_ID 		817
#define CellTemp6_BOX 		7
#define CellTemp6_TRS 		TRS7

#define CellTemp7_ID 		818
#define CellTemp7_BOX 		8
#define CellTemp7_TRS 		TRS8

#define CellTemp8_ID 		819
#define CellTemp8_BOX 		9
#define CellTemp8_TRS 		TRS9

#define CellTemp9_ID 		820
#define CellTemp9_BOX 		10
#define CellTemp9_TRS 		TRS10

#define CellTemp10_ID 		821
#define CellTemp10_BOX 		11
#define CellTemp10_TRS 		TRS11

#define CellTemp11_ID 		822
#define CellTemp11_BOX 		12
#define CellTemp11_TRS 		TRS12

#define CellTemp12_ID 		823
#define CellTemp12_BOX 		13
#define CellTemp12_TRS 		TRS13

#define CellTemp13_ID 		824
#define CellTemp13_BOX 		14
#define CellTemp13_TRS 		TRS14

#define CellTemp14_ID 		825
#define CellTemp14_BOX 		15
#define CellTemp14_TRS 		TRS15

#define CellTemp15_ID 		826
#define CellTemp15_BOX 		16
#define CellTemp15_TRS 		TRS16

#define CellTemp16_ID 		827
#define CellTemp16_BOX 		17
#define CellTemp16_TRS 		TRS17

#define CellTemp17_ID 		828
#define CellTemp17_BOX 		18
#define CellTemp17_TRS 		TRS18

#define CellTemp18_ID 		829
#define CellTemp18_BOX 		19
#define CellTemp18_TRS 		TRS19

#define CellTemp19_ID 		830
#define CellTemp19_BOX 		20
#define CellTemp19_TRS		TRS20

#define CellTemp20_ID 		830
#define CellTemp20_BOX 		21
#define CellTemp20_TRS		TRS21

#define RPM_ID 				1027
#define RPM_BOX				22
#define RPM_TRS				TRS22

#define DriverThrottle_ID 	484
#define DriverThrottle_BOX 	28
#define DriverThrottle_TRS 	TRS28

#define no_filter_ID		900
#define no_filter_BOX		29
#define no_filter_TRS 		TRS29

#define DriverControl_ID 	483
#define DriverControl_BOX 	31
#define DriverControl_TRS	TRS31






#endif /* CAN_H_ */
