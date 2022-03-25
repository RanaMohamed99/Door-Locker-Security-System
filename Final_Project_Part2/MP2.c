/***************************************************************************************************************
 * File Name    : MP2.c
 * Author       : Rana Mohamed
 * Date Created : 19 Jul 2021
 * Description  : This is the Main Source File.
 **************************************************************************************************************/



#include "UART.h"
#include "MOTOR.h"
#include "timers.h"
#include "I2C.h"
#include "EEPROM.h"


/******************************************** PREPROCESSOR MACROS **********************************************/


#define FIRST_LOC_EEPROM 0x0311
#define N 5

/*********************************************** GLOBAL VARIABLES **********************************************/

char newPassword[N];
char openPassword[N];
char changePassword[N];
uint8 buffer[N];
uint8 state = 0;
uint8 screen = 0;
uint8 checkPassword;
uint8 wrongCount = 0;
extern uint8 seconds;


/******************************************** FUNCTIONS DEFINITIONS ********************************************/


/***************************************************************************************************************
 * Function Name  : PW_checkPassword
 * Description    : This Function is responsible for checking that 2 passwords are similar.
 * Arguments      : 2 character array.
 * Return         : char
 **************************************************************************************************************/

uint8 PW_checkPassword(uint8 *password1,char *password2)
{
	char compare = 0;
	for(int i = 0 ; i < 4 ; i++)
	{
		if(password1[i] == password2[i])
		{
			compare ++;
		}
	}

	if(compare == 4)
		return TRUE;
	else
		return FALSE;
}




int main(){

    SREG |=1<<7;
    TWI_init();
    EEPROM_init();
	UCSRBC_init mp2={Eight_bit ,Asynchronous ,Enable_EvenParity ,stop2_bit ,Rising_XCK_EDGE};
    UART_init(&mp2);
	Timer1_setup timer1={FASTPWM_mode15,Clear_FastPWMT1,No_Prescaler};
	Timer0_setup timer0={Normal02,Normal_NonPWM,Prescaler_256};
	SET_timer0( &timer0);
	SET_timer1( &timer1);
	MOTOR_init();
	_delay_ms(50);
    DDRD |= (1<<PD3);
	PORTD &= ~(1<<PD3);
    while(1)
	  {
			if(screen == 0)
			{
				state = UART_receiveByte();
				if (state == SAVE_PASSWORD)
				{
					UART_receiveString(newPassword);
					screen = 1;
					state = 0;
				}

				else if (state == OPEN_DOOR)
				{
					UART_receiveString(openPassword);
					screen = 2;
					state = 0;
				}
				else if (state == CHANGE_PASSWORD)
				{
					UART_receiveString(openPassword);
					screen = 3;
					state = 0;
				}

			}

			else if(screen == 1)
			{
				sint8 i = 0 ;
				while (newPassword[i] != '\0')
				{
					 EEPROM_writeByte(FIRST_LOC_EEPROM +i , newPassword[i]);
					 _delay_ms(50);
					 i++;
				}
				screen = 0;
			}
			else if(screen == 2)
			{
				EEPROM_readPassword(buffer,N);
				checkPassword = PW_checkPassword(buffer , openPassword);
				if(checkPassword == TRUE)
				{
					UART_sendByte(CORRECT_PW);
					ROTATE_motorClockwise();
					ACTIVATE_timer0(&timer0);
					while(seconds != 10);
					ROTATE_motorAntiClockwise();
					ACTIVATE_timer0(&timer0);
					while(seconds != 10);
					STOP_motor();
					wrongCount = 0;
					screen = 0;

				}
				else
				{
					UART_sendByte(WRONG_PASSWORD);
					wrongCount++;
					if(wrongCount == 3)
					{
						PORTD |= (1<<PD7);
						ACTIVATE_timer0(&timer0);
						while(seconds != 10);
						PORTD &= ~(1<<PD7);
						wrongCount = 0;
						screen = 0;
					}
					screen = 0;
				}

			}
			else if (screen == 3)
			{
				EEPROM_readPassword(buffer,N);
				checkPassword = PW_checkPassword(buffer , openPassword);
				if(checkPassword == TRUE)
				{
					UART_sendByte(CORRECT_PW);
					while(UART_receiveByte() != NEW_PASSWORD );
					UART_receiveString(changePassword);
					sint8 i = 0 ;
					while (changePassword[i] != '\0')
					{
						 EEPROM_writeByte(FIRST_LOC_EEPROM +i , changePassword[i]);
						 _delay_ms(50);
						 i++;
					}
					wrongCount = 0;
					screen = 0;
				}
				else
				{
					UART_sendByte(WRONG_PASSWORD);
					wrongCount++;
					if(wrongCount == 3)
					{
						PORTD |= (1<<PD3);
						ACTIVATE_timer0(&timer0);
						while(seconds != 10);
						PORTD &= ~(1<<PD3);
						wrongCount = 0;
						screen = 0;
					}
				screen = 0;
				}
			}

		}
	}
