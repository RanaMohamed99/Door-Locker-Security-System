/*****************************************************************************************************************************************
 * File Name    : timers.h
 * Author       : Rana Mohamed
 * Date Created : 19 Jul 2021
 * Description  : This File is the Timer Header Driver for Timers 0 ,1 ,2.
 ****************************************************************************************************************************************/

#ifndef TIMERS_H_
#define TIMERS_H_






/**************************************************** INCLUDES ***************************************************************************/

#include <avr/io.h>






/************************************************ Preprocessor Macros *******************************************************************/


/******************************************************************************************************************************************
 * Set the Timer you want to activate to 1
******************************************************************************************************************************************/

#define ACTIVATE_TIMER0 1
#define ACTIVATE_TIMER1 1
#define ACTIVATE_TIMER2 0



/******************************************************************************************************************************************
 * Initial value to be put in register TCNT0 so Timer can start counting from it.
 *****************************************************************************************************************************************/
#define TIMER_COUNTER_INITIAL_VALUE 0



/******************************************************************************************************************************************
 *  Determines whether channel A or B is used  : set the channel that will be used
******************************************************************************************************************************************/
#define TIMER1_CHANNEL_A  1

#define TIMER1_CHANNEL_B  0

#define OUTPUT_COMPARE_MATCH_REGISTER0 0

#define OUTPUT_COMPARE_MATCH_REGISTERA 2000

#define	OUTPUT_COMPARE_MATCH_REGISTERB 0

#define OUTPUT_COMPARE_MATCH_REGISTER2 0



/************************************************** GLOBAL VARIABLES *********************************************************************/





/*************************************************** ENUMUMERATIONS **********************************************************************/


/******************************************************************************************************************************************
 *  Enumeration Name: Timer0_modes
 * Enumeration Description:
 *  0- Normal02  : Set Timer 0/2 to Normal mode.
 *  1- PWM02     : Set Timer 0/2 to PWM mode.
 *  2- CTC02     : Set Timer 0/2 to CTC mode.
 *  3- FastPwm02 : Set Timer 0/2 to Fast PWM mode.
 *
 *****************************************************************************************************************************************/
typedef enum{

	Normal02,PWM02,CTC02,FastPwm02
}Timer02_modes;





/*****************************************************************************************************************************************
 * Enumeration Name: Timer1_modes
 * Enumeration Description:
 *  0- normal1               : Set Timer 1 to Normal mode.
 *  1- PWM8bit_mode1         : Set Timer 1 to PWM mode 8 bit.
 *  2- PWM9bit_mode2         : Set Timer 1 to PWM mode 9 bit.
 *  3- PWM10bit_mode3        : Set Timer 1 to PWM mode 10 bit.
 *  4- CTC_mode4             : Set Timer 1 to CTC mode.
 *  5- FastPWM8bit_mode5     : Set Timer 1 to Fast PWM mode 8 bit.
 *  6- FastPWM9bit_mode6     : Set Timer 1 to Fast PWM mode 9 bit.
 *  7- FastPWM10bit_mode7    : Set Timer 1 to Fast PWM mode 10 bit.
 *  8- PWM_PAFCORRECT_mode8  : Set Timer 1 to PWM Phase and Frequency correct mode.
 *  9- PWM_PAFCORRECT_mode9  : Set Timer 1 to PWM Phase and Frequency correct mode.
 * 10- PWM_PAFCORRECT_mode10 : Set Timer 1 to PWM Phase correct mode.
 * 11- PWM_PAFCORRECT_mode11 : Set Timer 1 to PWM Phase correct mode.
 * 12- CTC_mode12            : Set Timer 1 to CTC mode.
 * 13- FASTPWM_mode14        : Set Timer 1 to Fast PWM mode.
 * 14- FASTPWM_mode15        : Set Timer 1 to Fast PWM mode.
 *****************************************************************************************************************************************/
typedef enum{

	normal1 , PWM8bit_mode1 , PWM9bit_mode2 , PWM10bit_mode3 , CTC_mode4 ,

	FastPWM8bit_mode5 , FastPWM9bit_mode6 , FastPWM10bit_mode7,

	PWM_PAFCORRECT_mode8, PWM_PAFCORRECT_mode9, PWM_PHASECORRECT_mode10,

	PWM_PHASECORRECT_mode11, CTC_mode12 , FASTPWM_mode14 , FASTPWM_mode15

}Timer1_modes;




/******************************************************************************************************************************************
 * Enumeration Name: Compare_OutputModesTimer1
 * Enumeration Description:
 *  0- Normal_NonPWM    : Set Timer 0/2 to Normal in Non PWM Compare Output Match mode (COM00/COM01,COM20/COM21).
 *  1- Toggle_NonPWM    : Set Timer 0/2 to Toggle 0C0/0C2 Non PWM Compare Output Match mode (COM00/COM01,COM20/COM21).
 *  2- Clear_NonPWM     : Set Timer 0/2 to Clear 0C0/0C2 Non PWM Compare Output Match mode (COM00/COM01,COM20/COM21).
 *  3- Set_NonPWM       : Set Timer 0/2 to Set 0C0/0C2 Non PWM Compare Output Match mode (COM00/COM01,COM20/COM21).
 *  0- Normal_FastPWM   : Set Timer 0/2 to Normal in Fast PWM Compare Output Match mode (COM00/COM01,COM20/COM21).
 *  2- Clear_FastPWM    : Set Timer 0/2 to Clear 0C0/0C2 in Fast PWM Compare Output Match mode (COM00/COM01,COM20/COM21).
 *  3- 3- Set_FastPWMT1 : Set Timer 0/2 to Set 0C0/0C2 in Fast PWM Compare Output Match mode (COM00/COM01,COM20/COM21).
******************************************************************************************************************************************/
typedef enum{
	Normal_NonPWM=0, Toggle_NonPWM=1 , Clear_NonPWM=2 , Set_NonPWM=3,
	Normal_FastPWM=0, Clear_FastPWM=2 , Set_FastPWM=3
}Compare_OutputModesTimer02;




/******************************************************************************************************************************************
 * Enumeration Name: Compare_OutputModesTimer1
 * Enumeration Description:
 *  0- Normal_NonPWMT1 : Set Timer 1 to Normal in Non PWM Compare Output Match mode COM1A0/1 /COM1B0/1).
 *  1- Toggle_NonPWMT1 : Set Timer 1 to Toggle 0C1A/OC1B Non PWM Compare Output Match mode COM1A0/1 /COM1B0/1).
 *  2- Clear_NonPWMT1  : Set Timer 1 to Clear 0C1A/OC1B Non PWM Compare Output Match mode COM1A0/1 /COM1B0/1).
 *  3- Set_NonPWMT1    : Set Timer 1 to Set 0C1A/OC1B Non PWM Compare Output Match mode COM1A0/1 /COM1B0/1).
 *  0- Normal_FastPWMT1 : Set Timer 1 to Normal in Fast PWM Compare Output Match mode COM1A0/1 /COM1B0/1).
 *  1- Toggle_FastPWMT1  : Set Timer 1 to Toggle 0C1A/OC1B in Fast PWM Compare Output Match mode COM1A0/1 /COM1B0/1).
 *  2- Clear_FastPWMT1  : Set Timer 1 to Clear 0C1A/OC1B in Fast PWM Compare Output Match mode COM1A0/1 /COM1B0/1).
 *  3- Set_FastPWMT1    : Set Timer 1 to Set 0C1A/OC1B in Fast PWM Compare Output Match mode COM1A0/1 /COM1B0/1).
 *  0- Normal_PhaseCorrect : Set Timer 1 to Normal in Phase Correct Compare Output Match mode COM1A0/1 /COM1B0/1).
 *  1- Toggle_PhaseCorrect : Set Timer 1 to Toggle 0C1A/OC1B in Phase Correct Compare Output Match mode COM1A0/1 /COM1B0/1).
 *  2- Clear_PhaseCorrect  : Set Timer 1 to Clear 0C1A/OC1B in Phase Correct Compare Output Match mode COM1A0/1 /COM1B0/1).
 *  3- Set_PhaseCorrect    : Set Timer 1 to Set 0C1A/OC1B in Phase Correct Compare Output Match mode COM1A0/1 /COM1B0/1).
 *  0- Normal_PhaseAndFrequencyCorrect :Set Timer 1 to Normal in Phase and Frequency Correct Compare Output Match mode COM1A0/1 /COM1B0/1).
 *  1- Toggle_PhaseAndFrequencyCorrect :Set Timer 1 to Toggle 0C1A/OC1B in Phase and Frequency Correct Compare Output Match mode COM1A0/1 /COM1B0/1).
 *  2- Clear_PhaseAndFrequencyCorrect  :Set Timer 1 to Clear 0C1A/OC1B in Phase and Frequency Correct Compare Output Match mode COM1A0/1 /COM1B0/1).
 *  3- Set_PhaseAndFrequencyCorrect    :Set Timer 1 to Set 0C1A/OC1B in Phase and Frequency Correct Compare Output Match mode COM1A0/1 /COM1B0/1).
 *****************************************************************************************************************************************/
typedef enum{
	Normal_NonPWMT1=0, Toggle_NonPWMT1=1 , Clear_NonPWMT1=2 , Set_NonPWMT1=3,
    Normal_FastPWMT1=0,Toggle_FastPWMT1 =1, Clear_FastPWMT1=2 , Set_FastPWMT1=3,
	Normal_PhaseCorrect=0,Toggle_PhaseCorrect=1,Clear_PhaseCorrect=2,Set_PhaseCorrect=3,
	Normal_PhaseAndFrequencyCorrect=0,Toggle_PhaseAndFrequencyCorrect=1,
	Clear_PhaseAndFrequencyCorrect=2,Set_PhaseAndFrequencyCorrect=3,

}Compare_OutputModesTimer1;



/*****************************************************************************************************************************************
 * Enumeration Name : CLOCK_PRESCALER
 * Enumeration Description:
 *   can be either 1 /8 /64 /256 /1024/external :
 * 0- Stop_clock                     : Stop the clock
 * 1 No_Prescaler                    : For no prescaling.
 * 2 Prescaler_8                     : For clock/8
 * 3 Prescaler_64                    : For clock/64
 * 4 Prescaler_256                   : For clock/ 256
 * 5 Prescaler_1024                  : For clock/ 1024
 * 6 External_Clock_T0_Falling_Edge  : For external clock source T0 pin (clock on FALLING edge)
 * 7 External_Clock_T0_Rising_Edge   : For external clock source T0 pin (clock on RISING edge)
 ******************************************************************************************************************************************/
typedef enum {
	Stop_clock,No_Prescaler,Prescaler_8,Prescaler_64,
	Prescaler_256,Prescaler_1024,External_Clock_T0_Falling_Edge,External_Clock_T0_Rising_Edge
}CLOCK_PRESCALER;



/*******************************************************************************************************************************************
 * Structure Name: Timer0_setup
 * Structure Members Description:
 *  1- Timer_zeroMode  : Variable of type Timer02_modes Enumeration.
 *  2- Timer0_mode     : Variable of type Compare_OutputModesTimer02 Enumeration.
 *  3- Clock0          : Variable of type CLOCK_PRESCALER Enumeration.
 *
 ******************************************************************************************************************************************/
typedef struct{
	Timer02_modes Timer_zeroMode;
	Compare_OutputModesTimer02 Timer0_mode;
	CLOCK_PRESCALER Clock0;
}Timer0_setup;



/*******************************************************************************************************************************************
 * Structure Name: Timer1_setup
 * Structure Members Description:
 *  1- Timer_oneMode   : Variable of type Timer1_modes Enumeration.
 *  2- Timer1_mode     : Variable of type Compare_OutputModesTimer1 Enumeration.
 *  3- Clock1          : Variable of type CLOCK_PRESCALER Enumeration.
 *
 ******************************************************************************************************************************************/
typedef struct{
	Timer1_modes Timer_oneMode;
	Compare_OutputModesTimer1 Timer1_mode;
	CLOCK_PRESCALER Clock1;

}Timer1_setup;



/*******************************************************************************************************************************************
 * Structure Name: Timer2_setup
 * Structure Members Description:
 *  1- Timer_twoMode   : Variable of type Timer02_modes Enumeration.
 *  2- Timer2_mode     : Variable of type Compare_OutputModesTimer02 Enumeration.
 *  3- Clock2          : Variable of type CLOCK_PRESCALER Enumeration.
 *
 ******************************************************************************************************************************************/
typedef struct{
	Timer02_modes Timer_twoMode;
	Compare_OutputModesTimer02 Timer2_mode;
	CLOCK_PRESCALER Clock2;
}Timer2_setup;






/********************************************* FUNCTION DECLARATIONS *********************************************************************/


/*****************************************************************************************************************************************
 *  Function Name : SET_timer0
 * Description    : This Function is responsible for setting the registers of timer 0
 * Arguments      : Constant Pointer to Structure to carry the address of the Structure
 *                  that carries the information of Timer 0.
 * Return         : None
 *****************************************************************************************************************************************/
void SET_timer0(const Timer0_setup* Timer0_Data);


/***************************************************************************************************************
 * Function Name  : ACTIVATE_timer0
 * Description    : This Function is responsible for giving clock to Timer 0.
 * Arguments      : Constant Pointer to Structure to carry the address of the Structure
 *                  that carries the information of Timer 0.
 * Return         : None.
 **************************************************************************************************************/
void ACTIVATE_timer0(const Timer0_setup* Timer0_Data);



/***************************************************************************************************************
 * Function Name  : DEACTIVATE_timer0
 * Description    : This Function is responsible for stop clock to Timer 0.
 * Arguments      : None.
 * Return         : None.
 **************************************************************************************************************/
void DEACTIVATE_timer0();


/******************************************************************************************************************************************
 * Function Name : SET_timer1
 * Description   : This Function is responsible for setting the registers of timer 1
 * Arguments     : Constant Pointer to Structure to carry the address of the Structure
 *                 that carries the information of Timer 1.
 * Return        : None
 *****************************************************************************************************************************************/
void SET_timer1(const Timer1_setup* Timer1_Data);


/***************************************************************************************************************
 * Function Name  : ACTIVATE_timer1
 * Description    : This Function is responsible for giving clock to Timer 1.
 * Arguments      : Constant Pointer to Structure to carry the address of the Structure
 *                  that carries the information of Timer 1.
 * Return         : None.
 **************************************************************************************************************/
void ACTIVATE_timer1(const Timer1_setup* Timer1_Data);


/***************************************************************************************************************
 * Function Name  : DEACTIVATE_timer1
 * Description    : This Function is responsible for stop clock to Timer 1.
 * Arguments      : None.
 * Return         : None.
 **************************************************************************************************************/
void DEACTIVATE_timer1();




/*****************************************************************************************************************************************
 * Function Name : SET_timer2
 * Description   : This Function is responsible for setting the registers of Timer 2
 * Arguments     : Constant Pointer to Structure to carry the address of the Structure
 *                 that carries the information of Timer 2.
 * Return        : None
 *****************************************************************************************************************************************/
void SET_timer2(const Timer2_setup* Timer2_Data);



/***************************************************************************************************************
 * Function Name  : ACTIVATE_timer2
 * Description    : This Function is responsible for giving clock to Timer 2.
 * Arguments      : Constant Pointer to Structure to carry the address of the Structure
 *                  that carries the information of Timer 2.
 * Return         : None.
 **************************************************************************************************************/
void ACTIVATE_timer2(const Timer2_setup* Timer2_Data);



/***************************************************************************************************************
 * Function Name  : DEACTIVATE_timer2
 * Description    : This Function is responsible for stop clock to Timer 2.
 * Arguments      : None.
 * Return         : None.
 **************************************************************************************************************/
void DEACTIVATE_timer2();
#endif /* TIMERS_H_ */
