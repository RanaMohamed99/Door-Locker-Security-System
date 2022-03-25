/***************************************************************************************************************
 * File Name    : MOTOR.c
 * Author       : Rana Mohamed
 * Date Created : 19 Jul 2021
 * Description  : This is the Source File of the Motor Driver.
 ***************************************************************************************************************/






/************************************************* INCLUDES ****************************************************/
#include "MOTOR.h"




/********************************************* FUNCTION DEFENITIONS ********************************************/


/***************************************************************************************************************
 * Function Name : MOTOR_init.
 * Description   : This Function is responsible for setting the Motor enable and direction.
 * Arguments     : None.
 * Return        : None.
 **************************************************************************************************************/
void MOTOR_init(){
	MOTOR_PORT_DIRECTION |= ( 1<< MOTOR_INPUT1 );
	MOTOR_PORT_DIRECTION |=	( 1<< MOTOR_INPUT2 );
	MOTOR_DIRECTION |= (MOTOR_DIRECTION & 0xBF) | ( 0<< MOTOR_INPUT1 );
	MOTOR_DIRECTION |= (MOTOR_DIRECTION & 0x7F)	| ( 0 << MOTOR_INPUT2  );


}


/***************************************************************************************************************
 * Function Name : STOP_motor.
 * Description   : This Function is responsible for stopping the Motor.
 * Arguments     : None.
 * Return        : None.
 **************************************************************************************************************/
void STOP_motor(){
	/*
	 * To Stop the Motor first let INPUT1 -> 0
	 * INPUT2 -> 0.
	 */
	MOTOR_DIRECTION |= (MOTOR_DIRECTION & 0xBF) | ( 0<< MOTOR_INPUT1 );
	MOTOR_DIRECTION |= (MOTOR_DIRECTION & 0x7F)	| ( 0 << MOTOR_INPUT2  );
	TCCR1B |= (TCCR1B & 0xF8) | (0);
}


/***************************************************************************************************************
 * Function Name : MOTOR_init.
 * Description   : This Function is responsible for rotating the Motor Clockwise.
 * Arguments     : None.
 * Return        : None.
 **************************************************************************************************************/
void ROTATE_motorClockwise(){
	/*
    * To Rotate the Motor Clockwise first let INPUT1 -> 0
    * INPUT2 -> 1.
	*/
	MOTOR_DIRECTION |= (MOTOR_DIRECTION & 0xBF) | ( 0<< MOTOR_INPUT1 );
	MOTOR_DIRECTION |= (MOTOR_DIRECTION & 0x7F)	| ( 1 << MOTOR_INPUT2  );
	TCNT0=0;
	OCR1A=2000;
}


/***************************************************************************************************************
 * Function Name : MOTOR_init.
 * Description   : This Function is responsible for rotating the Motor Anti-Clockwise.
 * Arguments     : None.
 * Return        : None.
 **************************************************************************************************************/
void ROTATE_motorAntiClockwise(){
	/*
	* To Rotate the Motor Anti-Clockwise first let INPUT1 -> 1
	* INPUT2 -> 0.
    */
	MOTOR_DIRECTION |= (MOTOR_DIRECTION & 0xBF) | ( 1<< MOTOR_INPUT1 );
	MOTOR_DIRECTION |= (MOTOR_DIRECTION & 0x7F)	| ( 0 << MOTOR_INPUT2  );
	TCNT0=0;
	OCR1A=2000;

}


