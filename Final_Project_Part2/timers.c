/***************************************************************************************************************
 * File Name    : timers.c
 * Author       : Rana Mohamed
 * Date Created : 19 Jul 2021
 * Description  : This is the Source File of the Timer Driver for Timers 0 ,1 ,2.
 **************************************************************************************************************/




/************************************************* INCLUDES ***************************************************/
#include "timers.h"





/************************************************ GLOBAL VARIABLES ********************************************/

int seconds=0;
int count=0;


/******************************************* Interrupt Service Routines ***************************************/

ISR(TIMER0_OVF_vect){
count++;
   if(count ==144){
	count=0;
	seconds++;
   }
}



/******************************************* FUNCTIONS DEFINITIONS ********************************************/

#if ( ACTIVATE_TIMER0 ==1 )

/***************************************************************************************************************
 *  Function Name : SET_timer0
 * Description    : This Function is responsible for setting the registers of timer 0
 * Arguments      : Constant Pointer to Structure to carry the address of the Structure
 *                  that carries the information of Timer 0.
 * Return         : None
 **************************************************************************************************************/

void SET_timer0(const Timer0_setup* Timer0_Data)
{

	  /*
	  *
	  * TCCR0 :
	  *   1- Check if Timer 0 is in Non PWM Mode to activate the Force Output Compare.
	  *   2- Set the WGM00, WGM01 bits from the input data of the Function.
	  *   3- Set the COM00/COM01 from the input data of the Function
	  *   4- Set the Clock prescaler.
	  *
	  * TIMSK :
	  *   Set the Interrupt Enables according to the activated mode in the Timer 0.
	  */

	if(Timer0_Data->Timer_zeroMode != 1){
       TCCR0 |=1 << FOC0 ;

	}
	TCCR0 |= (TCCR0 & 0xB7) | (Timer0_Data->Timer_zeroMode << 3) | (Timer0_Data->Timer_zeroMode << 5);
	TCCR0 |= (TCCR0 & 0xCF) | (Timer0_Data->Timer0_mode);
	//TCCR0 |= (TCCR0 & 0xF8) | (Timer0_Data->Clock0);
	if(Timer0_Data->Timer_zeroMode == 0){
		TIMSK |= (1<<TOIE0);
	}
	else{
		TIMSK |= (1<<OCIE0);
		OCR0 =OUTPUT_COMPARE_MATCH_REGISTER0 ;
	}

	TCNT0=TIMER_COUNTER_INITIAL_VALUE;
}



/***************************************************************************************************************
 * Function Name  : ACTIVATE_timer0
 * Description    : This Function is responsible for giving clock to Timer 0.
 * Arguments      : Constant Pointer to Structure to carry the address of the Structure
 *                  that carries the information of Timer 0.
 * Return         : None.
 **************************************************************************************************************/
void ACTIVATE_timer0(const Timer0_setup* Timer0_Data){
	TCCR0 |= (TCCR0 & 0xF8) | (Timer0_Data->Clock0);
}



/***************************************************************************************************************
 * Function Name  : DEACTIVATE_timer0
 * Description    : This Function is responsible for stop clock to Timer 0.
 * Arguments      : None.
 * Return         : None.
 **************************************************************************************************************/
void DEACTIVATE_timer0(){
	TCCR0 |= (TCCR0 & 0xF8) | (0);
}

#endif



#if ( ACTIVATE_TIMER1 == 1)

/***************************************************************************************************************
 * Function Name : SET_timer1
 * Description   : This Function is responsible for setting the registers of timer 1
 * Arguments     : Constant Pointer to Structure to carry the address of the Structure
 *                 that carries the information of Timer 1.
 * Return        : None
 **************************************************************************************************************/
void SET_timer1(const Timer1_setup* Timer1_Data){

  /*
  *
  * TCCRR1A :
  *   1- Check if Timer 1 is in Non PWM Mode to activate the Force Output Compare for Channel A / B.
  *   2- Check which channels are Activated.
  *   3- Set the WGM10, WGM11, WGM12 bits from the input data of the Function.
  *   4- Set the COM1A0/COM1A1  /  COM1B0/COM1B1 bits from the input data of the Function.
  *
  * TCCR1B :
  *   1- Set the Clock prescaler from the data passed to the function.
  *
  * TIMSK :
  *   Set the Interrupt Enables according to the activated mode in the Timer 1.
  */


 if((Timer1_Data->Timer_oneMode != 1)||(Timer1_Data->Timer_oneMode != 2)||(Timer1_Data->Timer_oneMode != 3)){
        #if( (TIMER1_CHANNEL_A  == 1 )&& (TIMER1_CHANNEL_B == 0 ))
		TCCR1A |=1 << FOC1A ;
        #elif((TIMER1_CHANNEL_B  == 1)&& (TIMER1_CHANNEL_A == 0 ))
	    TCCR1A |=1 << FOC1B ;
        #elif((TIMER1_CHANNEL_A  == 1 )&&(TIMER1_CHANNEL_B == 1 ))
	    TCCR1A |=(1 << FOC1A) | (1 << FOC1B );
        #endif
	}

  #if( (TIMER1_CHANNEL_A  == 1 )&& (TIMER1_CHANNEL_B == 0 ))
	TCCR1A |= (TCCR1A & 0x3F)|(Timer1_Data->Timer1_mode <<6) ;
  #elif((TIMER1_CHANNEL_B  == 1)&& (TIMER1_CHANNEL_A == 0 ))
	TCCR1A |= (TCCR1A & 0xCF)|(Timer1_Data->Timer1_mode <<4) ;
  #elif((TIMER1_CHANNEL_A  == 1 )&&(TIMER1_CHANNEL_B == 1 ))
	TCCR1A |= (TCCR1A & 0x0F)|(Timer1_Data->Timer1_mode <<4)|(Timer1_Data->Timer1_mode <<6);
  #endif

	TCCR1A |= (TCCR1A & 0xFC) | (Timer1_Data->Timer_oneMode);
	TCCR1B |= (TCCR1B & 0xE7) | ((Timer1_Data->Timer_oneMode)<<3);
	TCCR1B |= (TCCR1B & 0xF8) | (Timer1_Data->Clock1);

  if(Timer1_Data->Timer_oneMode ==0){
			TIMSK |= 1<<TOIE1;
  }

  else {
  #if(( TIMER1_CHANNEL_A  == 1 )&& (TIMER1_CHANNEL_B == 0 ))
	TIMSK |= 1<<OCIE1A;
	DDRD |=1<<PD5;
	OCR1A=OUTPUT_COMPARE_MATCH_REGISTERA;
  #elif((TIMER1_CHANNEL_B  == 1)&& (TIMER1_CHANNEL_A == 0 ))
	TIMSK |= 1<<OCIE1B;
	OCR1B=OUTPUT_COMPARE_MATCH_REGISTERB;
  #elif((TIMER1_CHANNEL_A  == 1 ) && (TIMER1_CHANNEL_B == 1 ))
	TCCR1A |=(1<<OCIE1A) | (1 <<OCIE1B );
	OCR1A = OUTPUT_COMPARE_MATCH_REGISTERA;
	OCR1B = OUTPUT_COMPARE_MATCH_REGISTERB;

  #endif
  }

    TCNT1=TIMER_COUNTER_INITIAL_VALUE;

 }




/***************************************************************************************************************
 * Function Name  : ACTIVATE_timer1
 * Description    : This Function is responsible for giving clock to Timer 1.
 * Arguments      : Constant Pointer to Structure to carry the address of the Structure
 *                  that carries the information of Timer 1.
 * Return         : None.
 **************************************************************************************************************/
void ACTIVATE_timer1(const Timer1_setup* Timer1_Data){
	TCCR1B |= (TCCR1B & 0xF8) | (Timer1_Data->Clock1);
}



/***************************************************************************************************************
 * Function Name  : DEACTIVATE_timer1
 * Description    : This Function is responsible for stop clock to Timer 1.
 * Arguments      : None.
 * Return         : None.
 **************************************************************************************************************/
void DEACTIVATE_timer1(){
	TCCR1B |= (TCCR1B & 0xF8) | (0);
}

#endif



#if ( ACTIVATE_TIMER2 == 1 )

/***************************************************************************************************************
 * Function Name : SET_timer2
 * Description   : This Function is responsible for setting the registers of Timer 2
 * Arguments     : Constant Pointer to Structure to carry the address of the Structure
 *                 that carries the information of Timer 2.
 * Return        : None
 **************************************************************************************************************/
void SET_timer2(const Timer2_setup* Timer2_Data)
{

	  /*
	  *
	  * TCCR2 :
	  *   1- Check if Timer 2 is in Non PWM Mode to activate the Force Output Compare.
	  *   2- Set the WGM20, WGM21 bits from the input data of the Function.
	  *   3- Set the COM20/COM21 from the input data of the Function
	  *   4- Set the Clock prescaler.
	  *
	  * TIMSK :
	  *   Set the Interrupt Enables according to the activated mode in the Timer 2.
	  */

	if(Timer2_Data->Timer_twoMode != 1){
         TCCR2 |=1 << FOC2 ;
         OCR2=OUTPUT_COMPARE_MATCH_REGISTER;
	}
	TCCR2 |= (TCCR2 & 0xB7) | (Timer2_Data->Timer_twoMode << 3) | (Timer2_Data->Timer_twoMode << 5);
	TCCR2 |= (TCCR2 & 0xCF) | (Timer2_Data->Timer2_mode);
	TCCR2 |= (TCCR2 & 0xF8) | (Timer2_Data->Clock2);
	if(Timer2_Data->Timer_twoMode == 0){
		TIMSK |= (1<<TOIE2);
	}
	else{
		TIMSK |= (1<<OCIE2);
		OCR2=OUTPUT_COMPARE_MATCH_REGISTER;
	}

   TCNT2= TIMER_COUNTER_INITIAL_VALUE;

}



/***************************************************************************************************************
 * Function Name  : ACTIVATE_timer2
 * Description    : This Function is responsible for giving clock to Timer 2.
 * Arguments      : Constant Pointer to Structure to carry the address of the Structure
 *                  that carries the information of Timer 2.
 * Return         : None.
 **************************************************************************************************************/
void ACTIVATE_timer2(const Timer2_setup* Timer2_Data){
	TCCR2 |= (TCCR2 & 0xF8) | (Timer2_Data->Clock2);
}



/***************************************************************************************************************
 * Function Name  : DEACTIVATE_timer2
 * Description    : This Function is responsible for stop clock to Timer 2.
 * Arguments      : None.
 * Return         : None.
 **************************************************************************************************************/
void DEACTIVATE_timer2(){
	TCCR2|= (TCCR1B & 0xF8) | (0);
}
#endif









