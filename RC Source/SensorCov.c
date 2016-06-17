/*
 * SensorCov().c
 *
 *  Created on: Oct 30, 2013
 *      Author: Nathan, edited by David
 */

#include "../RC Headers/all.h"

extern DSPfilter A0filter;
extern DSPfilter A1filter;
extern DSPfilter A2filter;
extern DSPfilter A3filter;
extern DSPfilter A4filter;
extern DSPfilter A5filter;
extern DSPfilter A6filter;
extern DSPfilter A7filter;
extern DSPfilter B0filter;
extern DSPfilter B1filter;
extern DSPfilter B2filter;
extern DSPfilter B3filter;
extern DSPfilter B4filter;
extern DSPfilter B5filter;
extern DSPfilter B6filter;
extern DSPfilter B7filter;
extern DSPfilter GPIO19filter;
extern DSPfilter GPIO26filter;
extern clock_struct Clock_Ticks;

#define EMA_FILTER_ENABLED 1

// The total number of cell temperatures that are measured and that are expected to be received.
#define TOTAL_CELL_TEMPS (48)

// The temperature in degree C where the throttle derating begins
#define TEMP_LIMIT_START   (50.0)
#define RPM_LIMIT_START	   (2000.0)

// The temperature in degree C where the throttle derating begins and the throttle is completely 0. This value must be larger than #TEMP_LIMIT_START
#define TEMP_LIMIT_END (60.0)
#define RPM_LIMIT_END  (3000.0)

#define RPM_SCALE_FACTOR (250.0)

// The size of the throttle limit lookup table. The lookup table is size (#TEMP_LIMIT_END - #TEMP_LIMIT_START) + 1 for the value 0 when temperature exceeds #TEMP_LIMIT_END.
#define LOOKUP_SIZE (((Uint16)(TEMP_LIMIT_END - TEMP_LIMIT_START)) + 1)
#define RPM_LOOKUP_SIZE ((Uint16)((RPM_LIMIT_END - RPM_LIMIT_START) / RPM_SCALE_FACTOR) + 1)

user_ops_struct ops_temp;
user_data_struct data_temp;

static filter throttle_filter;
SafetyVar32_t safety;

// The lookup table for throttle scale value during a temperature limit. The last value of the lookup should always be 0.
static const int BAT_THROTTLE[LOOKUP_SIZE + 1] = {100, 90, 80, 70, 60, 50, 40, 30, 20, 10, 0};
static const int RPM_THROTTLE[RPM_LOOKUP_SIZE + 1] = {100, 75, 50, 25, 0};

//pointer float array storing the battery temperatures
float* BATT_CELL_TEMPS[48] = {&user_data.CellTemp1.F32, &user_data.CellTemp2.F32, &user_data.CellTemp3.F32,
		                     &user_data.CellTemp4.F32, &user_data.CellTemp5.F32, &user_data.CellTemp6.F32,
							 &user_data.CellTemp7.F32, &user_data.CellTemp8.F32, &user_data.CellTemp9.F32,
							 &user_data.CellTemp10.F32, &user_data.CellTemp11.F32, &user_data.CellTemp12.F32,
							 &user_data.CellTemp13.F32, &user_data.CellTemp14.F32, &user_data.CellTemp15.F32,
							 &user_data.CellTemp16.F32, &user_data.CellTemp17.F32, &user_data.CellTemp18.F32,
							 &user_data.CellTemp19.F32, &user_data.CellTemp20.F32, &user_data.CellTemp21.F32,
							 &user_data.CellTemp22.F32, &user_data.CellTemp23.F32, &user_data.CellTemp24.F32,
							 &user_data.CellTemp25.F32, &user_data.CellTemp26.F32, &user_data.CellTemp27.F32,
							 &user_data.CellTemp28.F32, &user_data.CellTemp29.F32, &user_data.CellTemp30.F32,
							 &user_data.CellTemp31.F32, &user_data.CellTemp32.F32, &user_data.CellTemp33.F32,
							 &user_data.CellTemp34.F32, &user_data.CellTemp35.F32, &user_data.CellTemp36.F32,
							 &user_data.CellTemp37.F32, &user_data.CellTemp38.F32, &user_data.CellTemp39.F32,
							 &user_data.CellTemp40.F32, &user_data.CellTemp41.F32, &user_data.CellTemp42.F32,
							 &user_data.CellTemp43.F32, &user_data.CellTemp44.F32, &user_data.CellTemp45.F32,
							 &user_data.CellTemp46.F32, &user_data.CellTemp47.F32, &user_data.CellTemp48.F32};

void SensorCov()
{
	SensorCovInit(4);
	while (sys_ops.State == STATE_SENSOR_COV)
	{
		LatchStruct();
		if (!Stack_Check()){
			SafetyVar_NewValue(&safety, 0);
			user_data.stack_limit.I32 = 1;
			user_data.driver_control_limits.I32 = user_data.stack_limit.I32 << 3;
			UpdateStruct();
			FillCANData();
		}
		else {
			SensorCovMeasure();
			UpdateStruct();
			FillCANData();
		}

	}
	SensorCovDeInit();
}

void SensorCovInit()
{
	//todo USER: SensorCovInit()
	SystemSensorInit(SENSOR_COV_STOPWATCH);

	initDSPfilter(&A5filter, 818);
	initDSPfilter(&A7filter, 818);
	EMA_Filter_Init(&throttle_filter, 50000, 100);
}

void SensorCovMeasure()
{
#define R1 10000.0 //Before ADC, Ohms
#define R2 20000.0
#define V5 5.08
#define B 1568.583480 //Ohm
//#define ADC_SCALE 4095.0
#define ADC_SCALE 3071.25
	SensorCovSystemInit();
	//initialize used variables

	//value which represents the position in the BAT_THROTTLE array which holds the calculated throttle percentage
	//int THROTTLE_LOOKUP = 0;

	//*******************************************************************************************************
	//*                                           TODO                                                      *
	//*                Clean up Sensor Conversion to make it cleaner  				                        *
	//*                                                                                                     *
	//*******************************************************************************************************


	// Percent of throttle input calculated by measured signal ADC value and divided by max ADC value
	_iq temp_limit = _IQ(1.0);
	_iq rpm_temp_limit = _IQ(1.0);
	user_data.throttle_percent_ratio.F32 = _IQtoF(_IQdiv(_IQ(A7RESULT), _IQ(ADC_SCALE)));

	if (user_data.throttle_percent_ratio.F32 > 1.0)
	{
		user_data.throttle_percent_ratio.F32 = 1.0;
	}
	user_data.max_cell_temp.I32 = MIN_CELL_TEMP;

	// Find maximum received cell temperature
	Uint16 i;
	for (i = 0; i < TOTAL_CELL_TEMPS; i++) {
	     if (*BATT_CELL_TEMPS[i] > user_data.max_cell_temp.F32) {
	          user_data.max_cell_temp.F32 = *BATT_CELL_TEMPS[i];
	     }
	}

	// If max temperature is above lookup table, throttle should be limited to 0
	if (user_data.max_cell_temp.F32 >= TEMP_LIMIT_END)
	{
	     user_data.throttle_percent_cap.F32 = 0;
	     user_data.battery_limit.I32 = 1;
	}

	// If max temperature is above the start of the temperature limit, determine how much and limit
	else if (user_data.max_cell_temp.F32 >= TEMP_LIMIT_START)
	{
	     Uint16 lookupIndex = (Uint16) _IQtoF(_IQ(user_data.max_cell_temp.F32) - _IQ(TEMP_LIMIT_START));
	     Uint16 lookupValuesDiff = BAT_THROTTLE[lookupIndex] - BAT_THROTTLE[lookupIndex + 1];
	     _iq limitFraction = _IQ(1.0) - _IQmpy(_IQ((float) lookupValuesDiff), _IQ((user_data.max_cell_temp.F32 - ((Uint16) user_data.max_cell_temp.F32))));
	     _iq limit = _IQmpy((limitFraction + _IQ(((float) BAT_THROTTLE[lookupIndex]))), _IQ(0.01));

	     if (_IQ(user_data.throttle_percent_ratio.F32) >= limit)
	     {
	    	 temp_limit = limit;
	     }

	     user_data.battery_limit.I32 = 1;
	}

	// No limit needed due to maximum cell temperature. Let motor command output be the rider's desired throttle
	else
	{
	     user_data.battery_limit.I32 = 0;
	}

	if (user_data.RPM.F32 >= RPM_LIMIT_END)
		{
		     user_data.throttle_percent_cap.F32 = 0;
		     user_data.rpm_limit.I32 = 1;
		}

	else if (user_data.RPM.F32 >= RPM_LIMIT_START)
		{
		     Uint16 rpmlookupIndex = (Uint16) _IQtoF(_IQdiv(_IQ(user_data.RPM.F32) - _IQ(RPM_LIMIT_START), _IQ(RPM_SCALE_FACTOR)));
		     Uint16 rpmlookupValuesDiff = RPM_THROTTLE[rpmlookupIndex] - RPM_THROTTLE[rpmlookupIndex + 1];
		     _iq rpmlimitFraction = _IQ(1.0) - _IQmpy(_IQ((float) rpmlookupValuesDiff), _IQ((user_data.RPM.F32 - ((Uint16) user_data.RPM.F32))));
		     _iq rpmlimit = _IQmpy((rpmlimitFraction + _IQ(((float) RPM_THROTTLE[rpmlookupIndex]))), _IQ(0.01));

		     if (_IQ(user_data.throttle_percent_ratio.F32) >= rpmlimit)
		     {
		    	 rpm_temp_limit = rpmlimit;
		     }
		     user_data.rpm_limit.I32 = 1;
		}
	else {
		user_data.rpm_limit.I32 = 1;
	}

	if (rpm_temp_limit < temp_limit){
		user_data.throttle_percent_cap.F32 = _IQtoF(rpm_temp_limit);
	}
	else {
		user_data.throttle_percent_cap.F32 = _IQtoF(temp_limit);
	}

    //capping the throttle output - checking to see if the trottle is enabled and that there are no CAN timeouts
	if ( throttle_toggle() ){
		user_data.throttle_lock.I32 = 1;
		if (!user_data.timeout_limit.I32){
				user_data.throttle_output.F32 = user_data.throttle_percent_ratio.F32;
				if (user_data.throttle_output.F32 > user_data.throttle_percent_cap.F32){
					#ifdef EMA_FILTER_ENABLED
					EMA_Filter_NewInput(&throttle_filter, user_data.throttle_percent_cap.F32);
					user_data.throttle_output.F32 = EMA_Filter_GetFilteredOutput(&throttle_filter);
					#else
					user_data.throttle_output.F32 = user_data.throttle_percent_cap.F32;
					#endif

				}
		  }
	}
	else {
			#ifdef EMA_FILTER_ENABLED
			EMA_Filter_NewInput(&throttle_filter, 0);
			user_data.throttle_output.F32 = EMA_Filter_GetFilteredOutput(&throttle_filter);
			#else
			user_data.throttle_output.F32 = 0;
			#endif
	}

	//unfiltered throttle value
	user_data.no_filter.F32 = user_data.throttle_percent_ratio.F32;

	//sets throttle lock to 0 if the throttle is off
	if (!throttle_toggle()){
		user_data.throttle_lock.I32 = 0;
	}

	//initializes CRC
	if (!user_data.timeout_limit.I32){
		SafetyVar_NewValue(&safety, user_data.throttle_output.I32);
	}

	data_temp.gp_button = READGPBUTTON();

	//checks to see if the stack is close to overflowing
	//If it is, then the throttle is set to 0 and the stack limit is activated

	//sending the driver control limmits information
	user_data.driver_control_limits.I32 = user_data.rpm_limit.I32 << 4;
	user_data.driver_control_limits.I32 += user_data.stack_limit.I32 << 3;
	user_data.driver_control_limits.I32 += user_data.timeout_limit.I32 << 2;
	user_data.driver_control_limits.I32 += user_data.battery_limit.I32 << 1;
	user_data.driver_control_limits.I32 += user_data.throttle_lock.I32;

	PerformSystemChecks();
}

void LatchStruct()
{
	LatchSystemStruct();
	ops_temp = user_ops;
	data_temp = user_data;
}

void UpdateStruct()
{
	SaveOpStates();
	//user_data = data_temp;
	//todo USER: UpdateStruct
	//update with node specific op changes

	//if ops is not changed outside of sensor conversion copy temp over, otherwise don't change

	//Change bit is only set by ops changes outside of SensorCov.


	DetermineOpStates();
}

void SensorCovDeInit()
{
	//todo USER: SensorCovDeInit()
	SystemSensorDeInit();
}
