/*
 * can.c
 *
 *  Created on: Nov 12, 2013
 *      Author: Nathan
 */
#include "../MCN3 Headers/all.h"

struct ECAN_REGS ECanaShadow;

/*
 * Function responsible for initializing the CAN module.
 *
 * For simple CAN setup the function CreateCANMailbox can be used to specify user
 * mailboxes.
 */
void CANSetup()
{
	//System specific CAN setup
	SystemCANInit(&ECanaShadow);

	EALLOW;
	//MBOX 0 - 1
	CommandBoxInit(COMMAND_ID);   // Mbox 0
	HeartbeatBoxInit(HEARTBEAT_ID); // Mbox 1
	/*
	* todo USER: Node specifc CAN setup
	* create mailbox for all Receive and transmit IDs
	* MBOX2 - MBOX31
    *
	* CreateCANMailbox(int mailboxNum, int IDE, int AME, int AAM, int DLC, int STDMSGID, int Mode)
	*/

	//adc TRANSMIT
	//CreateCANMailbox(2,0,0,1,8,ADC_ID,0);
	//gp_button TRANSMIT
	//CreateCANMailbox(3,0,0,1,8,GP_BUTTON_ID,0);

	CreateCANMailbox(TIRE_TEMPS_BOX,0,0,1,8,TIRE_TEMPS_ID,0);
	CreateCANMailbox(FLEX_SENSOR_BANK_1_BOX,0,0,1,8,FLEX_SENSOR_BANK_1_ID,0);
	CreateCANMailbox(FLEX_SENSOR_BANK_2_BOX,0,0,1,4,FLEX_SENSOR_BANK_2_ID,0);

	ECanaShadow.CANMD.bit.MD9 = 1;			//receive
	ECanaShadow.CANME.bit.ME9 = 1;			//enable
	ECanaShadow.CANMIM.bit.MIM9  = 1; 		//int enable
	ECanaShadow.CANMIL.bit.MIL9  = 1;   	// Int.-Level MB#0  -> I1EN

    EDIS;
    FinishCANInit();
}

char FillCAN(unsigned int Mbox)
{
	CopyMCToShadow(&ECanaShadow);

	//Try to fill heartbeat. If not heartbeat mailbox, see if it's a user mailbox
	if(FillHeartbeat(Mbox, user_ops.UserFlags.all) != 1)
	{
		//todo USER: setup for all transmit MBOXs
		//InsertCANMessage(int Mbox, unsigned int MDH, unsigned int MDL)
		switch (Mbox)
		{
		case TIRE_TEMPS_BOX:
			InsertCANMessage(TIRE_TEMPS_BOX, user_data.rear_tire_temp.U32, user_data.front_tire_temp.U32);
			return 1;
		case FLEX_SENSOR_BANK_1_BOX:
			InsertCANMessage(FLEX_SENSOR_BANK_1_BOX, user_data.flex_sensor_2.U32, user_data.flex_sensor_1.U32);
			return 1;
		case FLEX_SENSOR_BANK_2_BOX:
			InsertCANMessage(FLEX_SENSOR_BANK_2_BOX, 0, user_data.flex_sensor_3.U32);
			return 1;
		default:
			return 0;
		}
	}
	else
	{
		return 1;
	}
}

void FillCANData()
{
	//todo USER: use FillCAN to put data into correct mailboxes
	FillCAN(TIRE_TEMPS_BOX);
	FillCAN(FLEX_SENSOR_BANK_1);
	FillCAN(FLEX_SENSOR_BANK_2);
}

// INT9.6
__interrupt void ECAN1INTA_ISR(void)  // eCAN-A
{
	Uint32 ops_id;
	Uint32 dummy;
	Uint16 errors;
  	unsigned int mailbox_nr;
  	mailbox_nr = getMailboxNR();
  	//todo USER: Setup ops command
  	if(mailbox_nr == COMMAND_BOX)
  	{
  		ReadCommand();
  	}
  	/*
  	else if(mailbox_nr == TRITIUM_ERRORS_BOX)
  	{
  		errors = ECanaMboxes.MBOX9.MDL.byte.BYTE1;
  		if(errors > 0)
  		{
  			SendCAN(TRITIUM_RESET_BOX);
  		}
		ECanaRegs.CANRMP.bit.RMP9 = 1;

  	}
  	*/
  	//todo USER: Setup other reads



  	//To receive more interrupts from this PIE group, acknowledge this interrupt
  	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}

// INT9.5
__interrupt void ECAN0INTA_ISR(void)   // eCAN-A
{

	// To receive more interrupts from this PIE group, acknowledge this interrupt
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}
