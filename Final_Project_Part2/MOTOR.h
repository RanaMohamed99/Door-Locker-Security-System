/***************************************************************************************************************
 * File Name    : MOTOR.h
 * Author       : Rana Mohamed
 * Date Created : 19 Jul 2021
 * Description  : This is the Header File of the Motor Driver.
 ***************************************************************************************************************/

#ifndef MOTOR_H_
#define MOTOR_H_




/****************************************************INCLUDES***************************************************/


#include <avr/io.h>





/********************************************* Preprocessor Macros *********************************************/
#define MOTOR_PORT_DIRECTION DDRD
#define MOTOR_DIRECTION DDRD
#define MOTOR_ENABLE PD5
#define MOTOR_INPUT1 PD6
#define MOTOR_INPUT2 PD7


/********************************************* FUNCTION DECLARATIONS ******************************************/


/***************************************************************************************************************
 * Function Name : MOTOR_init.
 * Description   : This Function is responsible for setting the Motor enable and direction.
 * Arguments     : None.
 * Return        : None.
 **************************************************************************************************************/
void MOTOR_init();




/***************************************************************************************************************
 * Function Name : STOP_motor.
 * Description   : This Function is responsible for stopping the Motor.
 * Arguments     : None.
 * Return        : None.
 **************************************************************************************************************/
void STOP_motor();



/***************************************************************************************************************
 * Function Name : MOTOR_init.
 * Description   : This Function is responsible for rotating the Motor Clockwise.
 * Arguments     : None.
 * Return        : None.
 **************************************************************************************************************/
void ROTATE_motorClockwise();



/***************************************************************************************************************
 * Function Name : MOTOR_init.
 * Description   : This Function is responsible for rotating the Motor Anti-Clockwise.
 * Arguments     : None.
 * Return        : None.
 **************************************************************************************************************/
void ROTATE_motorAntiClockwise();







#endif /* MOTOR_H_ */
