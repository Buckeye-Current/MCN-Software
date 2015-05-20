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

	CreateCANMailbox(CONTACTOR_BOX_BOX,0,0,1,4,CONTACTOR_BOX_ID,0); //CHECK AAM
	CreateCANMailbox(FRAME_FAULT_BOX,0,0,1,4,FRAME_FAULT_ID,0);
	CreateCANMailbox(SHUNTS_BOX,0,0,1,4,SHUNTS_ID, 0);
	CreateCANMailbox(REAR_WHEEL_SPEED_BOX,0,0,1,4,REAR_WHEEL_SPEED_ID,0);
	CreateCANMailbox(REAR_BRAKE_BOX,0,0,1,8,REAR_BRAKE_ID,0);
	CreateCANMailbox(REAR_SUSPENSION_BOX,0,0,1,4,REAR_SUSPENSION_ID,0);

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
		case CONTACTOR_BOX_BOX:
			InsertCANMessage(CONTACTOR_BOX_BOX, 0, user_data.DC_DC_temp.U32);
			return 1;
		case FRAME_FAULT_BOX:
			if(ECanaRegs.CANMD.bit.MD3 == 1) return 0;
			ECanaMboxes.MBOX3.MDH.all = 0;
			ECanaMboxes.MBOX3.MDL.all = 0;
			ECanaMboxes.MBOX3.MDL.byte.BYTE3 = user_data.frame_fault;
			break;
			return 1;
		case SHUNTS_BOX:
			InsertCANMessage(SHUNTS_BOX, 0, user_data.v12_shunt.U32);
			return 1;
		case REAR_WHEEL_SPEED_BOX:
			InsertCANMessage(REAR_WHEEL_SPEED_BOX, 0, user_data.wheel_speed.U32);
			return 1;
		case REAR_BRAKE_BOX:
			InsertCANMessage(REAR_BRAKE_BOX, 0, user_data.rear_brake.U32);
			return 1;
		case REAR_SUSPENSION_BOX:
			InsertCANMessage(REAR_SUSPENSION_BOX, 0, user_data.rear_susp.U32);
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
	FillCAN(CONTACTOR_BOX_BOX);
	FillCAN(FRAME_FAULT_BOX);
	FillCAN(SHUNTS_BOX);
	FillCAN(REAR_WHEEL_SPEED_BOX);
	FillCAN(REAR_BRAKE_BOX);
	FillCAN(REAR_SUSPENSION_BOX);
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
