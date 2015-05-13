/*
 * can.c
 *
 *  Created on: Nov 12, 2013
 *      Author: Nathan
 */
#include "all.h"

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

	CreateCANMailbox(AIN1_BOX,0,0,1,4,AIN1_ID,0); //CHECK AAM
	CreateCANMailbox(AIN2_BOX,0,0,1,4,AIN2_ID,0);
	CreateCANMailbox(AIN3_BOX,0,0,1,4,AIN3_ID, 0);
	CreateCANMailbox(AIN4_BOX,0,0,1,4,AIN4_ID,0);
	CreateCANMailbox(AIN5_BOX,0,0,1,8,AIN5_ID,0);
	CreateCANMailbox(AIN6_BOX,0,0,1,4,AIN6_ID,0);
	CreateCANMailbox(AIN7_BOX,0,0,1,4,AIN7_ID,0);
	CreateCANMailbox(AIN8_BOX,0,0,1,8,AIN8_ID,0);
	CreateCANMailbox(AIN9_BOX,0,0,1,8,AIN9_ID,0);
	CreateCANMailbox(AIN10_BOX,0,0,1,8,AIN10_ID,0);
	CreateCANMailbox(AIN11_BOX,0,0,1,8,AIN11_ID,0);
	CreateCANMailbox(AIN12_BOX,0,0,1,8,AIN12_ID,0);
	CreateCANMailbox(GP0_BOX,0,0,1,8,GP0_ID,0);
	CreateCANMailbox(GP1_BOX,0,0,1,8,GP1_ID,0);

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
		case AIN1_BOX:
			InsertCANMessage(AIN1_BOX, 0, user_data.ain1.U32);
			return 1;
		case AIN2_BOX:
			InsertCANMessage(AIN2_BOX, 0, user_data.ain2.U32);
			return 1;
		case AIN3_BOX:
			InsertCANMessage(AIN3_BOX, 0, user_data.ain3.U32);
			return 1;
		case AIN4_BOX:
			InsertCANMessage(AIN4_BOX, 0, user_data.ain4.U32);
			return 1;
		case AIN5_BOX:
			InsertCANMessage(AIN5_BOX, 0, user_data.ain5.U32);
			return 1;
		case AIN6_BOX:
			InsertCANMessage(AIN6_BOX, 0, user_data.ain6.U32);
			return 1;
		case AIN7_BOX:
			InsertCANMessage(AIN7_BOX, 0, user_data.ain7.U32);
			return 1;
		case AIN8_BOX:
			InsertCANMessage(AIN8_BOX, 0, user_data.ain8.U32);
			return 1;
		case AIN9_BOX:
			InsertCANMessage(AIN9_BOX, 0, user_data.ain9.U32);
			return 1;
		case AIN10_BOX:
			InsertCANMessage(AIN10_BOX, 0, user_data.ain10.U32);
			return 1;
		case AIN11_BOX:
			InsertCANMessage(AIN11_BOX, 0, user_data.ain11.U32);
			return 1;
		case AIN12_BOX:
			InsertCANMessage(AIN12_BOX, 0, user_data.ain12.U32);
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
	FillCAN(AIN1_BOX);
	FillCAN(AIN2_BOX);
	FillCAN(AIN3_BOX);
	FillCAN(AIN4_BOX);
	FillCAN(AIN5_BOX);
	FillCAN(AIN6_BOX);
	FillCAN(AIN7_BOX);
	FillCAN(AIN8_BOX);
	FillCAN(AIN9_BOX);
	FillCAN(AIN10_BOX);
	FillCAN(AIN11_BOX);
	FillCAN(AIN12_BOX);
	FillCAN(GP0_BOX);
	FillCAN(GP1_BOX);

}

// INT9.6
__interrupt void ECAN1INTA_ISR(void)  // eCAN-A
{
	Uint32 ops_id;
	Uint32 dummy;
  	unsigned int mailbox_nr;
  	mailbox_nr = getMailboxNR();
  	//todo USER: Setup ops command
  	if(mailbox_nr == COMMAND_BOX)
  	{
  		ReadCommand();
  	}
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
