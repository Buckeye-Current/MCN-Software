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

	CreateCANMailbox(FRONT_SUSPENSION_BOX,0,0,1,4,FRONT_SUSPENSION_ID,0); //CHECK AAM
	CreateCANMailbox(STEERING_BOX,0,0,1,4,STEERING_ID,0);
	CreateCANMailbox(FRONT_WHEEL_BOX,0,0,1,4,FRONT_WHEEL_ID, 0);
	CreateCANMailbox(FRONT_BRAKE_BOX,0,0,1,4,FRONT_BRAKE_ID,0);
	CreateCANMailbox(AMBIENT_BOX,0,0,1,8,AMBIENT_ID,0);
	CreateCANMailbox(RADIATOR_BOX,0,0,1,4,RADIATOR_ID,0);

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
		case FRONT_SUSPENSION_BOX:
			InsertCANMessage(FRONT_SUSPENSION_BOX, 0, user_data.front_suspension_travel.U32);
			return 1;
		case STEERING_BOX:
			InsertCANMessage(STEERING_BOX, 0, user_data.steering_angle.U32);
			return 1;
		case FRONT_WHEEL_BOX:
			InsertCANMessage(FRONT_WHEEL_BOX, 0, user_data.front_wheel_speed.U32);
			return 1;
		case FRONT_BRAKE_BOX:
			InsertCANMessage(FRONT_BRAKE_BOX, 0, user_data.front_brake_pressure.U32);
			return 1;
		case AMBIENT_BOX:
			InsertCANMessage(AMBIENT_BOX, user_data.ambient_temperature.U32, user_data.ambient_pressure.U32);
			return 1;
		case RADIATOR_BOX:
			InsertCANMessage(RADIATOR_BOX, user_data.radiator_coolant_temp.U32, user_data.radiator_air_pressure.U32);
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
	FillCAN(FRONT_SUSPENSION_BOX);
	FillCAN(STEERING_BOX);
	FillCAN(FRONT_WHEEL_BOX);
	FillCAN(FRONT_BRAKE_BOX);
	FillCAN(AMBIENT_BOX);
	FillCAN(RADIATOR_BOX);
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
