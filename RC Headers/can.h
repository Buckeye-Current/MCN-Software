/*
 * can.h
 *
 *  Created on: Nov 13, 2013
 *      Author: Nathan, edited by David
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

#define COMMAND_ID 		487
#define HEARTBEAT_ID 	486

#define CellTemp1_ID 		825
#define CellTemp1_BOX 		2
#define CellTemp1_TRS 		TRS2

#define CellTemp2_ID 		826
#define CellTemp2_BOX 		3
#define CellTemp2_TRS 		TRS3

#define CellTemp3_ID 		827
#define CellTemp3_BOX 		4
#define CellTemp3_TRS 		TRS4

#define CellTemp4_ID 		828
#define CellTemp4_BOX 		5
#define CellTemp4_TRS 		TRS5

#define CellTemp5_ID 		829
#define CellTemp5_BOX 		6
#define CellTemp5_TRS 		TRS6

#define CellTemp6_ID 		830
#define CellTemp6_BOX 		7
#define CellTemp6_TRS 		TRS7

#define CellTemp7_ID 		831
#define CellTemp7_BOX 		8
#define CellTemp7_TRS 		TRS8

#define CellTemp8_ID 		832
#define CellTemp8_BOX 		9
#define CellTemp8_TRS 		TRS9

#define CellTemp9_ID 		833
#define CellTemp9_BOX 		10
#define CellTemp9_TRS 		TRS10

#define CellTemp10_ID 		834
#define CellTemp10_BOX 		11
#define CellTemp10_TRS 		TRS11

#define CellTemp11_ID 		835
#define CellTemp11_BOX 		12
#define CellTemp11_TRS 		TRS12

#define CellTemp12_ID 		836
#define CellTemp12_BOX 		13
#define CellTemp12_TRS 		TRS13

#define CellTemp13_ID 		837
#define CellTemp13_BOX 		14
#define CellTemp13_TRS 		TRS14

#define CellTemp14_ID 		838
#define CellTemp14_BOX 		15
#define CellTemp14_TRS 		TRS15

#define CellTemp15_ID 		839
#define CellTemp15_BOX 		16
#define CellTemp15_TRS 		TRS16

#define CellTemp16_ID 		840
#define CellTemp16_BOX 		17
#define CellTemp16_TRS 		TRS17

#define CellTemp17_ID 		841
#define CellTemp17_BOX 		18
#define CellTemp17_TRS 		TRS18

#define CellTemp18_ID 		842
#define CellTemp18_BOX 		19
#define CellTemp18_TRS 		TRS19

#define CellTemp19_ID 		843
#define CellTemp19_BOX 		20
#define CellTemp19_TRS		TRS20

#define CellTemp20_ID 		844
#define CellTemp20_BOX 		21
#define CellTemp20_TRS		TRS21

#define CellTemp21_ID 		845
#define CellTemp21_BOX 		22
#define CellTemp21_TRS		TRS22

#define CellTemp22_ID 		846
#define CellTemp22_BOX 		23
#define CellTemp22_TRS		TRS23

#define CellTemp23_ID 		847
#define CellTemp23_BOX 		24
#define CellTemp23_TRS		TRS24

#define CellTemp24_ID 		848
#define CellTemp24_BOX 		25
#define CellTemp24_TRS		TRS25

#define DriverThrottle_ID 	484
#define DriverThrottle_BOX 	28
#define DriverThrottle_TRS 	TRS28

#define no_filter_ID		485
#define no_filter_BOX		29
#define no_filter_TRS 		TRS29

#define DriverControl_ID 	1281
#define DriverControl_BOX 	31
#define DriverControl_TRS	TRS31






#endif /* CAN_H_ */
