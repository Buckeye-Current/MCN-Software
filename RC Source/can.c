/*
 * can.c
 *
 *  Created on: Nov 12, 2013
 *      Author: Nathan, edited by David
 */
#include "../RC Headers/all.h"

#define MTOF_BIT	0x00020000

// Convert from seconds to CAN ticks
#define SECS_TO_CAN_TICKS(seconds)	(Uint32)(seconds * 1000000)

#define CAN_TIMEOUT_IN_SECS(time)	(ECanaRegs.CANTSC + SECS_TO_CAN_TICKS(time))

#define TIMEOUT_ENALBED_MAILBOXES (0x07FFFFFC)

struct ECAN_REGS ECanaShadow;
extern SafetyVar32_t safety;
//static filter throttle_filter;
Uint32 mailbox_timeouts = 0;

static void setupCANTimeout(void);
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

	CreateCANMailbox(CellTemp1_BOX, 0, 0, 0, 8, CellTemp1_ID, 1);
	CreateCANMailbox(CellTemp2_BOX, 0, 0, 0, 8, CellTemp2_ID, 1);
	CreateCANMailbox(CellTemp3_BOX, 0, 0, 0, 8, CellTemp3_ID, 1);
	CreateCANMailbox(CellTemp4_BOX, 0, 0, 0, 8, CellTemp4_ID, 1);
	CreateCANMailbox(CellTemp5_BOX, 0, 0, 0, 8, CellTemp5_ID, 1);
	CreateCANMailbox(CellTemp6_BOX, 0, 0, 0, 8, CellTemp6_ID, 1);
	CreateCANMailbox(CellTemp7_BOX, 0, 0, 0, 8, CellTemp7_ID, 1);
	CreateCANMailbox(CellTemp8_BOX, 0, 0, 0, 8, CellTemp8_ID, 1);
	CreateCANMailbox(CellTemp9_BOX, 0, 0, 0, 8, CellTemp9_ID, 1);
	CreateCANMailbox(CellTemp10_BOX, 0, 0, 0, 8, CellTemp10_ID, 1);
	CreateCANMailbox(CellTemp11_BOX, 0, 0, 0, 8, CellTemp11_ID, 1);
	CreateCANMailbox(CellTemp12_BOX, 0, 0, 0, 8, CellTemp12_ID, 1);
	CreateCANMailbox(CellTemp13_BOX, 0, 0, 0, 8, CellTemp13_ID, 1);
	CreateCANMailbox(CellTemp14_BOX, 0, 0, 0, 8, CellTemp14_ID, 1);
	CreateCANMailbox(CellTemp15_BOX, 0, 0, 0, 8, CellTemp15_ID, 1);
	CreateCANMailbox(CellTemp16_BOX, 0, 0, 0, 8, CellTemp16_ID, 1);
	CreateCANMailbox(CellTemp17_BOX, 0, 0, 0, 8, CellTemp17_ID, 1);
	CreateCANMailbox(CellTemp18_BOX, 0, 0, 0, 8, CellTemp18_ID, 1);
	CreateCANMailbox(CellTemp19_BOX, 0, 0, 0, 8, CellTemp19_ID, 1);
	CreateCANMailbox(CellTemp20_BOX, 0, 0, 0, 8, CellTemp20_ID, 1);
	CreateCANMailbox(CellTemp21_BOX, 0, 0, 0, 8, CellTemp21_ID, 1);
	CreateCANMailbox(CellTemp22_BOX, 0, 0, 0, 8, CellTemp22_ID, 1);
	CreateCANMailbox(CellTemp23_BOX, 0, 0, 0, 8, CellTemp23_ID, 1);
	CreateCANMailbox(CellTemp24_BOX, 0, 0, 0, 8, CellTemp24_ID, 1);
	CreateCANMailbox(RPM_BOX, 0, 0, 0, 8, RPM_ID, 1);
	CreateCANMailbox(DriverControl_BOX, 0, 0, 0, 5, DriverControl_ID, 0);
	CreateCANMailbox(DriverThrottle_BOX, 0, 0, 0, 8, DriverThrottle_ID, 0);
	CreateCANMailbox(no_filter_BOX, 0, 0, 0, 4, no_filter_ID, 0);

	ECanaRegs.CANGIF0.all = 0xFFFFFFFF; /* Clear all interrupt flag bits */
    ECanaRegs.CANGIF1.all = 0xFFFFFFFF;

    ECanaShadow.CANGIM.bit.MTOM = 1;
    /*
    ECanaShadow.CANGIM.bit.TCOM = 0;
    ECanaShadow.CANGIM.bit.WDIM = 0;
    ECanaShadow.CANGIM.bit.RMLIM = 0;
    ECanaShadow.CANGIM.bit.BOIM = 0;
    ECanaShadow.CANGIM.bit.EPIM = 0;
    ECanaShadow.CANGIM.bit.WLIM = 0;
    ECanaShadow.CANGIM.bit.GIL = 0;
    //ECanaShadow.CANGIM.bit.I0EN = 1;
    ECanaShadow.CANGIM.bit.I1EN = 1;
    */

    setupCANTimeout();

    EDIS;
    FinishCANInit();
}

char FillCAN(unsigned int Mbox)
{
	CopyMCToShadow(&ECanaShadow);

	//Try to fill heartbeat. If not heartbeat mailbox, see if it's a user mailbox
	if((FillHeartbeat(Mbox, user_ops.UserFlags.all) != 1) && SafetyVar_CheckValue(&safety))
	{
		//todo USER: setup for all transmit MBOXs
		//InsertCANMessage(int Mbox, unsigned int MDH, unsigned int MDL)
		Uint32 mdl;
		switch (Mbox)
		{
		case DriverControl_BOX:
			mdl = (user_data.max_cell_temp.I32 << 8) + user_data.driver_control_limits.I32;
			InsertCANMessage(DriverControl_BOX, user_data.max_cell_temp.I32 >> 24, mdl);
			break;
		case DriverThrottle_BOX:
			InsertCANMessage(DriverThrottle_BOX, (SafetyVar_getValue(&safety)), user_data.RPM_const.I32);
			break;
		case no_filter_BOX:
			InsertCANMessage(no_filter_BOX, 0, user_data.no_filter.I32);
			break;
		default:
			return 0;
		}
	}
	else
	{
		return 1;
	}
	return 0;
}

void FillCANData()
{
	//todo USER: use FillCAN to put data into correct mailboxes
	FillCAN(DriverControl_BOX);
	FillCAN(DriverThrottle_BOX);
	FillCAN(no_filter_BOX);
}

static void setupCANTimeout(void){
	ECanaShadow.CANTOC.all = 0;
	ECanaShadow.CANTOC.all = 0;

	ECanaMOTORegs.MOTO2 = CAN_TIMEOUT_IN_SECS(3.0);
	ECanaShadow.CANTOC.bit.TOC2 = 1;

	ECanaMOTORegs.MOTO3 = CAN_TIMEOUT_IN_SECS(3.0);
	ECanaShadow.CANTOC.bit.TOC3 = 1;

	ECanaMOTORegs.MOTO4 = CAN_TIMEOUT_IN_SECS(3.0);
	ECanaShadow.CANTOC.bit.TOC4 = 1;

	ECanaMOTORegs.MOTO5 = CAN_TIMEOUT_IN_SECS(3.0);
	ECanaShadow.CANTOC.bit.TOC5 = 1;

	ECanaMOTORegs.MOTO6 = CAN_TIMEOUT_IN_SECS(3.0);
	ECanaShadow.CANTOC.bit.TOC6 = 1;

	ECanaMOTORegs.MOTO7 = CAN_TIMEOUT_IN_SECS(3.0);
	ECanaShadow.CANTOC.bit.TOC7 = 1;

	ECanaMOTORegs.MOTO8 = CAN_TIMEOUT_IN_SECS(3.0);
	ECanaShadow.CANTOC.bit.TOC8 = 1;

	ECanaMOTORegs.MOTO9 = CAN_TIMEOUT_IN_SECS(3.0);
	ECanaShadow.CANTOC.bit.TOC9 = 1;

	ECanaMOTORegs.MOTO10 = CAN_TIMEOUT_IN_SECS(3.0);
	ECanaShadow.CANTOC.bit.TOC10 = 1;

	ECanaMOTORegs.MOTO11 = CAN_TIMEOUT_IN_SECS(3.0);
	ECanaShadow.CANTOC.bit.TOC11 = 1;

	ECanaMOTORegs.MOTO12 = CAN_TIMEOUT_IN_SECS(3.0);
	ECanaShadow.CANTOC.bit.TOC12 = 1;

	ECanaMOTORegs.MOTO13 = CAN_TIMEOUT_IN_SECS(3.0);
	ECanaShadow.CANTOC.bit.TOC13 = 1;

	ECanaMOTORegs.MOTO14 = CAN_TIMEOUT_IN_SECS(3.0);
	ECanaShadow.CANTOC.bit.TOC14 = 1;

	ECanaMOTORegs.MOTO15 = CAN_TIMEOUT_IN_SECS(3.0);
	ECanaShadow.CANTOC.bit.TOC15 = 1;

	ECanaMOTORegs.MOTO16 = CAN_TIMEOUT_IN_SECS(3.0);
	ECanaShadow.CANTOC.bit.TOC16 = 1;

	ECanaMOTORegs.MOTO17 = CAN_TIMEOUT_IN_SECS(3.0);
	ECanaShadow.CANTOC.bit.TOC17 = 1;

	ECanaMOTORegs.MOTO18 = CAN_TIMEOUT_IN_SECS(3.0);
	ECanaShadow.CANTOC.bit.TOC18 = 1;

	ECanaMOTORegs.MOTO19 = CAN_TIMEOUT_IN_SECS(3.0);
	ECanaShadow.CANTOC.bit.TOC19 = 1;

	ECanaMOTORegs.MOTO20 = CAN_TIMEOUT_IN_SECS(3.0);
	ECanaShadow.CANTOC.bit.TOC20 = 1;

	ECanaMOTORegs.MOTO21 = CAN_TIMEOUT_IN_SECS(3.0);
	ECanaShadow.CANTOC.bit.TOC21 = 1;

	ECanaMOTORegs.MOTO22 = CAN_TIMEOUT_IN_SECS(3.0);
	ECanaShadow.CANTOC.bit.TOC22 = 1;

	ECanaMOTORegs.MOTO23 = CAN_TIMEOUT_IN_SECS(3.0);
	ECanaShadow.CANTOC.bit.TOC23 = 1;

	ECanaMOTORegs.MOTO24 = CAN_TIMEOUT_IN_SECS(3.0);
	ECanaShadow.CANTOC.bit.TOC24 = 1;

	ECanaMOTORegs.MOTO25 = CAN_TIMEOUT_IN_SECS(3.0);
	ECanaShadow.CANTOC.bit.TOC25 = 1;

	ECanaMOTORegs.MOTO26 = CAN_TIMEOUT_IN_SECS(3.0);
	ECanaShadow.CANTOC.bit.TOC26 = 1;
}

// INT9.6

__interrupt void ECAN1INTA_ISR(void)  // eCAN-A
{

	Uint32 ops_id;
	Uint32 dummy;
  	unsigned int mailbox_nr;
  	mailbox_nr = getMailboxNR();
  	//todo USER: Setup ops command
  	//CAN RECEIVE

  	if ((ECanaRegs.CANGIF1.all & MTOF_BIT) > 0){
  	 	// Store which mailboxes timed out.
  		mailbox_timeouts = ECanaRegs.CANGIF1.all;

  		// Disable timeout interrupt on the mailbox that timed out
  		/*
  		 * NOTE: Reducing this down to ECanaRegs.CANTOC.all &= ~ECanaRegs.CANTOS.all;
  		 * The instruction can be disassembled to determine the cause.
  		 * This is a slightly more inefficient workaround.
  		 */

  		Uint32 timeoutToggled = ECanaRegs.CANTOC.all;
  		Uint32 timeoutStatus = ECanaRegs.CANTOS.all;
  		timeoutToggled &= ~timeoutStatus;
  		ECanaRegs.CANTOC.all = timeoutToggled;

  		SafetyVar_NewValue(&safety, 0);
  	}

  	// If CANTOC is not set for all mailboxes that should have timeout enabled, we have
  	// disabled a mailbox because it timed out.
  	if ((ECanaRegs.CANTOC.all != TIMEOUT_ENALBED_MAILBOXES)) {
  		user_data.timeout_limit.I32 = 1;
  	}
  	else
  	{
  		user_data.timeout_limit.I32 = 0;
  	}

  	while (ECanaRegs.CANRMP.all > 0){

		switch (mailbox_nr)
		{
		case COMMAND_BOX:
			ReadCommand();
			break;
		case CellTemp1_BOX:
			user_data.CellTemp1.I32 = ECanaMboxes.MBOX2.MDL.all;
			user_data.CellTemp2.I32 = ECanaMboxes.MBOX2.MDH.all;
			ECanaShadow.CANRMP.bit.RMP2 = 1;
			// Set TOC back to 1 to enable timeout incase the mailbox was previously timed out.
			ECanaShadow.CANTOC.bit.TOC2 = 1;
			ECanaMOTORegs.MOTO2 = CAN_TIMEOUT_IN_SECS(3.0);
			break;
		case CellTemp2_BOX:
			//user_data.CellTemp3.I32 = ECanaMboxes.MBOX3.MDL.all;
			user_data.CellTemp4.I32 = ECanaMboxes.MBOX3.MDH.all;
			ECanaShadow.CANRMP.bit.RMP3 = 1;
			ECanaShadow.CANTOC.bit.TOC3 = 1;
			ECanaMOTORegs.MOTO3 = CAN_TIMEOUT_IN_SECS(3.0);
			break;
		case CellTemp3_BOX:
			user_data.CellTemp5.I32 = ECanaMboxes.MBOX4.MDL.all;
			user_data.CellTemp6.I32 = ECanaMboxes.MBOX4.MDH.all;
			ECanaShadow.CANRMP.bit.RMP4 = 1;
			ECanaShadow.CANTOC.bit.TOC4 = 1;
			ECanaMOTORegs.MOTO4 = CAN_TIMEOUT_IN_SECS(3.0);
			break;
		case CellTemp4_BOX:
			user_data.CellTemp7.I32 = ECanaMboxes.MBOX5.MDL.all;
			user_data.CellTemp8.I32 = ECanaMboxes.MBOX5.MDH.all;
			ECanaShadow.CANRMP.bit.RMP5 = 1;
			ECanaShadow.CANTOC.bit.TOC5 = 1;
			ECanaMOTORegs.MOTO5 = CAN_TIMEOUT_IN_SECS(3.0);
			break;
		case CellTemp5_BOX:
			user_data.CellTemp9.I32 = ECanaMboxes.MBOX6.MDL.all;
			user_data.CellTemp10.I32 = ECanaMboxes.MBOX6.MDH.all;
			ECanaShadow.CANRMP.bit.RMP6 = 1;
			ECanaShadow.CANTOC.bit.TOC6 = 1;
			ECanaMOTORegs.MOTO6 = CAN_TIMEOUT_IN_SECS(3.0);
			break;
		case CellTemp6_BOX:
			//user_data.CellTemp11.I32 = ECanaMboxes.MBOX7.MDL.all;
			user_data.CellTemp12.I32 = ECanaMboxes.MBOX7.MDH.all;
			ECanaShadow.CANRMP.bit.RMP7 = 1;
			ECanaShadow.CANTOC.bit.TOC7 = 1;
			ECanaMOTORegs.MOTO7 = CAN_TIMEOUT_IN_SECS(3.0);
			break;
		case CellTemp7_BOX:
			user_data.CellTemp13.I32 = ECanaMboxes.MBOX8.MDL.all;
			user_data.CellTemp14.I32 = ECanaMboxes.MBOX8.MDH.all;
			ECanaShadow.CANRMP.bit.RMP8 = 1;
			ECanaShadow.CANTOC.bit.TOC8 = 1;
			ECanaMOTORegs.MOTO8 = CAN_TIMEOUT_IN_SECS(3.0);
			break;
		case CellTemp8_BOX:
			user_data.CellTemp15.I32 = ECanaMboxes.MBOX9.MDL.all;
			user_data.CellTemp16.I32 = ECanaMboxes.MBOX9.MDH.all;
			ECanaShadow.CANRMP.bit.RMP9 = 1;
			ECanaShadow.CANTOC.bit.TOC9 = 1;
			ECanaMOTORegs.MOTO9 = CAN_TIMEOUT_IN_SECS(3.0);
			break;
		case CellTemp9_BOX:
			user_data.CellTemp17.I32 = ECanaMboxes.MBOX10.MDL.all;
			user_data.CellTemp18.I32 = ECanaMboxes.MBOX10.MDH.all;
			ECanaShadow.CANRMP.bit.RMP10 = 1;
			ECanaShadow.CANTOC.bit.TOC10 = 1;
			ECanaMOTORegs.MOTO10 = CAN_TIMEOUT_IN_SECS(3.0);
			break;
		case CellTemp10_BOX:
			//user_data.CellTemp19.I32 = ECanaMboxes.MBOX11.MDL.all;
			user_data.CellTemp20.I32 = ECanaMboxes.MBOX11.MDH.all;
			ECanaShadow.CANRMP.bit.RMP11 = 1;
			ECanaShadow.CANTOC.bit.TOC11 = 1;
			ECanaMOTORegs.MOTO11 = CAN_TIMEOUT_IN_SECS(3.0);
			break;
		case CellTemp11_BOX:
			user_data.CellTemp21.I32 = ECanaMboxes.MBOX12.MDL.all;
			user_data.CellTemp22.I32 = ECanaMboxes.MBOX12.MDH.all;
			ECanaShadow.CANRMP.bit.RMP12 = 1;
			ECanaShadow.CANTOC.bit.TOC12 = 1;
			ECanaMOTORegs.MOTO12 = CAN_TIMEOUT_IN_SECS(3.0);
			break;
		case CellTemp12_BOX:
			user_data.CellTemp23.I32 = ECanaMboxes.MBOX13.MDL.all;
			user_data.CellTemp24.I32 = ECanaMboxes.MBOX13.MDH.all;
			ECanaShadow.CANRMP.bit.RMP13 = 1;
			ECanaShadow.CANTOC.bit.TOC13 = 1;
			ECanaMOTORegs.MOTO13 = CAN_TIMEOUT_IN_SECS(3.0);
			break;
		case CellTemp13_BOX:
			user_data.CellTemp25.I32 = ECanaMboxes.MBOX14.MDL.all;
			user_data.CellTemp26.I32 = ECanaMboxes.MBOX14.MDH.all;
			ECanaShadow.CANRMP.bit.RMP14 = 1;
			ECanaShadow.CANTOC.bit.TOC14 = 1;
			ECanaMOTORegs.MOTO14 = CAN_TIMEOUT_IN_SECS(3.0);
			break;
		case CellTemp14_BOX:
			//user_data.CellTemp27.I32 = ECanaMboxes.MBOX15.MDL.all;
			user_data.CellTemp28.I32 = ECanaMboxes.MBOX15.MDH.all;
			ECanaShadow.CANRMP.bit.RMP15 = 1;
			ECanaShadow.CANTOC.bit.TOC15 = 1;
			ECanaMOTORegs.MOTO15 = CAN_TIMEOUT_IN_SECS(3.0);
			break;
		case CellTemp15_BOX:
			user_data.CellTemp29.I32 = ECanaMboxes.MBOX16.MDL.all;
			user_data.CellTemp30.I32 = ECanaMboxes.MBOX16.MDH.all;
			ECanaShadow.CANRMP.bit.RMP16 = 1;
			ECanaShadow.CANTOC.bit.TOC16 = 1;
			ECanaMOTORegs.MOTO16 = CAN_TIMEOUT_IN_SECS(3.0);
			break;
		case CellTemp16_BOX:
			user_data.CellTemp31.I32 = ECanaMboxes.MBOX17.MDL.all;
			user_data.CellTemp32.I32 = ECanaMboxes.MBOX17.MDH.all;
			ECanaShadow.CANRMP.bit.RMP17 = 1;
			ECanaShadow.CANTOC.bit.TOC17 = 1;
			ECanaMOTORegs.MOTO17 = CAN_TIMEOUT_IN_SECS(3.0);
			break;
		case CellTemp17_BOX:
			user_data.CellTemp33.I32 = ECanaMboxes.MBOX18.MDL.all;
			user_data.CellTemp34.I32 = ECanaMboxes.MBOX18.MDH.all;
			ECanaShadow.CANRMP.bit.RMP18 = 1;
			ECanaShadow.CANTOC.bit.TOC18 = 1;
			ECanaMOTORegs.MOTO18 = CAN_TIMEOUT_IN_SECS(3.0);
			break;
		case CellTemp18_BOX:
			//user_data.CellTemp35.I32 = ECanaMboxes.MBOX19.MDL.all;
			user_data.CellTemp36.I32 = ECanaMboxes.MBOX19.MDH.all;
			ECanaShadow.CANRMP.bit.RMP19 = 1;
			ECanaShadow.CANTOC.bit.TOC19 = 1;
			ECanaMOTORegs.MOTO19 = CAN_TIMEOUT_IN_SECS(3.0);
			break;
		case CellTemp19_BOX:
			user_data.CellTemp37.I32 = ECanaMboxes.MBOX20.MDL.all;
			user_data.CellTemp38.I32 = ECanaMboxes.MBOX20.MDH.all;
			ECanaShadow.CANRMP.bit.RMP20 = 1;
			ECanaShadow.CANTOC.bit.TOC20 = 1;
			ECanaMOTORegs.MOTO20 = CAN_TIMEOUT_IN_SECS(3.0);
			break;
		case CellTemp20_BOX:
			user_data.CellTemp39.I32 = ECanaMboxes.MBOX21.MDL.all;
			user_data.CellTemp40.I32 = ECanaMboxes.MBOX21.MDH.all;
			ECanaShadow.CANRMP.bit.RMP21 = 1;
			ECanaShadow.CANTOC.bit.TOC21 = 1;
			ECanaMOTORegs.MOTO21 = CAN_TIMEOUT_IN_SECS(3.0);
			break;
		case CellTemp21_BOX:
			user_data.CellTemp41.I32 = ECanaMboxes.MBOX22.MDL.all;
			user_data.CellTemp42.I32 = ECanaMboxes.MBOX22.MDH.all;
			ECanaShadow.CANRMP.bit.RMP22 = 1;
			ECanaShadow.CANTOC.bit.TOC22 = 1;
			ECanaMOTORegs.MOTO22 = CAN_TIMEOUT_IN_SECS(3.0);
			break;
		case CellTemp22_BOX:
			//user_data.CellTemp43.I32 = ECanaMboxes.MBOX23.MDL.all;
			user_data.CellTemp44.I32 = ECanaMboxes.MBOX23.MDH.all;
			ECanaShadow.CANRMP.bit.RMP23 = 1;
			ECanaShadow.CANTOC.bit.TOC23 = 1;
			ECanaMOTORegs.MOTO23 = CAN_TIMEOUT_IN_SECS(3.0);
			break;
		case CellTemp23_BOX:
			user_data.CellTemp45.I32 = ECanaMboxes.MBOX24.MDL.all;
			user_data.CellTemp46.I32 = ECanaMboxes.MBOX24.MDH.all;
			ECanaShadow.CANRMP.bit.RMP24 = 1;
			ECanaShadow.CANTOC.bit.TOC24 = 1;
			ECanaMOTORegs.MOTO24 = CAN_TIMEOUT_IN_SECS(3.0);
			break;
		case CellTemp24_BOX:
			user_data.CellTemp47.I32 = ECanaMboxes.MBOX25.MDL.all;
			user_data.CellTemp48.I32 = ECanaMboxes.MBOX25.MDH.all;
			ECanaShadow.CANRMP.bit.RMP25 = 1;
			ECanaShadow.CANTOC.bit.TOC25 = 1;
			ECanaMOTORegs.MOTO25 = CAN_TIMEOUT_IN_SECS(3.0);
			break;
		case RPM_BOX:
			user_data.RPM.I32 = ECanaMboxes.MBOX26.MDL.all;
			ECanaShadow.CANRMP.bit.RMP26 = 1;
			ECanaShadow.CANTOC.bit.TOC26 = 1;
			ECanaMOTORegs.MOTO26 = CAN_TIMEOUT_IN_SECS(3.0);
			break;
		}

		ECanaRegs.CANRMP.all = ECanaShadow.CANRMP.all;
		ECanaRegs.CANTOC.all = ECanaShadow.CANTOC.all;
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
