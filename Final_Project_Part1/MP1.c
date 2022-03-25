/***************************************************************************************************************
 * File Name    : MP1.c
 * Author       : Rana Mohamed
 * Date Created : 19 Jul 2021
 * Description  : This is the Main Source File.
 **************************************************************************************************************/




/************************************************* INCLUDES ***************************************************/
#include<string.h>
#include"lcd.h"
#include"keypad.h"
#include"UART.h"
#include"timers.h"
#include<avr/eeprom.h>


/******************************************** PREPROCESSOR MACROS **********************************************/

#define INTERNAL_MEMORY_ADD  0x0F
#define INTERNAL_MEMORY_DATA 0x10

/*********************************************** GLOBAL VARIABLES **********************************************/
char a_firstPassword[5];
char a_secondPassword[5];
char a_message[5];
char a_oldPass[5];
char a_oldPassMess[5];
static uint8 firstTimeFlag = 0;
uint8 compare ;
uint8 memValue;
uint8 operation;
uint8 screen = 0;
uint8 state;
uint8 wrongPW = 0;
int i;
/******************************************** FUNCTIONS DEFINITIONS ********************************************/

/***************************************************************************************************************
 * Function Name  : READ_password
 * Description    : This Function is responsible for reading the password form the keypad.
 * Arguments      : pointer to character to carry an address of the password array.
 * Return         : None
 **************************************************************************************************************/
void READ_password(char*password){
	char password_characters;
    char key;
    for (password_characters = 0 ; password_characters < 5 ; password_characters++ )
    	{
    		key = KeyPad_getPressedKey();

    	if(password_characters == 4)
    	{

    			 if(key == 13)
    			{
    				break;
    			}
    			else
    			{
    				password_characters = password_characters-1;
    				continue;
    			}
    	}

    	else
    	{

    		   if (key >= 0 && key<=9)
    			{
    				password[password_characters] = key;
    			}

    			else
    			{
    				password_characters = password_characters-1;
    				continue;
    			}
    		_delay_ms(500);
    		LCD_goToRowColumn(1 , password_characters);
    		LCD_displayCharacter('*');
    	}


    	}
}



/***************************************************************************************************************
 * Function Name  : PASSWORD_toString
 * Description    : This Function is responsible for transforming the password to a string to be sent to the UART.
 * Arguments      : pointer to character to carry an address of the password array.
 * Return         : None
 **************************************************************************************************************/
void PASSWORD_toString(char*password){
	int i=0;
	for(i=0;i<=4;i++){
	  if(i==4){
        password[i]='#';
	  }
}

}



/***************************************************************************************************************
 * Function Name  : getPassword
 * Description    : This Function is responsible for reading the password form the keypad.
 * Arguments      : pointer to character to carry an address of the password array.
 * Return         : None
 **************************************************************************************************************/
void getPassword(char*password)
{
	sint8 i;
	uint8 key;
	for (i = 0 ; i < 5 ; i++ )
	{
		key = KeyPad_getPressedKey();
		if(i == 4)
		{

			if ( key == '*')
			{
				LCD_displayStringRowColumn(1, 0, "                ");
							i = -1;
							continue ;
			}
			else if(key == 13)
			{
				break;
			}
			else
			{
				i = i-1;
				continue;
			}
		}

		else
		{


					if (key == '*')
					{
						LCD_displayStringRowColumn(1, 0, "                ");
						i = -1;
						continue ;
					}

					else if (key >= 0 && key<=9)
					{
						password[i] = key;
					}

					else
					{
						i = i-1;
						continue;
					}
					_delay_ms(500);
					LCD_goToRowColumn(1 , i);
					LCD_displayCharacter('*');
		}


	}

}


/***************************************************************************************************************
 * Function Name  : readyToSend
 * Description    : This Function is responsible for transforming the password to a string to be sent to the UART.
 * Arguments      : pointer to character to carry an address of the password array.
 * Return         : None
 **************************************************************************************************************/
void readyToSend(char*password1, char*password2)
 {
	int i ;
	for(i = 0 ; i < 5 ; i++)
	{
		if(i==4)
		{
			password2[i] = '#';
		}
		else
		{
			password2[i] = password1[i];
		}
	}

 }




/*************************************************** Main *****************************************************/

int main(){

	SREG |=1<<7;
    UCSRBC_init mp1={Eight_bit ,Asynchronous ,Enable_EvenParity ,stop2_bit ,Rising_XCK_EDGE};
	UART_init(&mp1);
	Timer0_setup timer0={Normal02,Normal_NonPWM,Prescaler_256};
	SET_timer0(&timer0);
	LCD_init();
	LCD_displayStringRowColumn(0,4," Welcome ");
	LCD_displayStringRowColumn(1,0," Final Project");
	_delay_ms(1000);
	LCD_clearScreen();
		SREG |=(1<<7);
		_delay_ms(50);
		while(1)
		{
			memValue = eeprom_read_byte((uint8 *)INTERNAL_MEMORY_ADD);
			if(memValue != INTERNAL_MEMORY_DATA)
			{
				firstTimeFlag = 0;
			}
			else if (memValue == INTERNAL_MEMORY_DATA)
			{
				firstTimeFlag = 1;
			}
			if(firstTimeFlag == 0)
				{
				    LCD_clearScreen();
					LCD_displayString("Enter 4-dig Pass");
					getPassword(a_firstPassword);
					LCD_clearScreen();
					LCD_displayString("Re-enter Pass");
					getPassword(a_secondPassword);
					compare = strcmp(a_firstPassword ,a_secondPassword );
					if(compare == 0)
					{
						eeprom_write_byte((uint8 *)INTERNAL_MEMORY_ADD,INTERNAL_MEMORY_DATA);

						LCD_clearScreen();
						LCD_displayStringRowColumn(0, 0, "password");
						LCD_displayStringRowColumn(1, 0, "Match");
						_delay_ms(1000);
						readyToSend(a_firstPassword , a_message);
						UART_sendByte(SAVE_PASSWORD);
						UART_sendString(a_message);

					}
					else
					{
						LCD_clearScreen();
						LCD_displayStringRowColumn(0, 0, "password");
						LCD_displayStringRowColumn(1, 0, " don't Match");
						_delay_ms(1000);
						LCD_clearScreen();

					}
				}
			else if(firstTimeFlag == 1)
			{
				if(screen == 0)
				{

					LCD_clearScreen();
					LCD_displayStringRowColumn(0, 0, "0:Open Door");
					LCD_displayStringRowColumn(1, 0, "1:Change PW");
					operation = KeyPad_getPressedKey();
					_delay_ms(400);
					if(operation == 0)
					{
						LCD_clearScreen();
						LCD_displayStringRowColumn(0, 0, "please enter PW");
						getPassword(a_firstPassword);
						readyToSend(a_firstPassword , a_message);
						UART_sendByte(OPEN_DOOR);
						UART_sendString(a_message);
						screen = 1;
					}
					else if(operation == 1)
					{
						LCD_clearScreen();
						LCD_displayStringRowColumn(0, 0, " enter old PW");
						getPassword(a_firstPassword);
						for( i = 0 ; i < 5 ; i++)
						{
							a_oldPass[i] = a_firstPassword[i];
						}
						readyToSend(a_oldPass , a_oldPassMess);
						readyToSend(a_firstPassword , a_message);
						UART_sendByte(CHANGE_PASSWORD);
						UART_sendString(a_message);
						screen = 2 ;
					}
				}
				else if(screen == 1)
				{
					state = UART_receiveByte();
					LCD_clearScreen();
					if(state == CORRECT_PW)
					{
						LCD_displayStringRowColumn(0, 0, "OPENING DOOR 10s");
						ACTIVATE_timer0(&timer0);

						while(seconds != 10)
						{
							LCD_goToRowColumn(1,0);
							LCD_intgerToString(seconds+1);
						}
						seconds = 0;
						LCD_clearScreen();
						LCD_displayStringRowColumn(0, 0, "CLOSING DOOR 10s");
						ACTIVATE_timer0(&timer0);
						while(seconds != 10)
						{
							LCD_goToRowColumn(1,0);
							LCD_intgerToString(seconds+1);
						}
						LCD_clearScreen();
						wrongPW = 0;
						state = 0;
						screen = 0;
					}
					else if(state == WRONG_PASSWORD)
					{
						if(wrongPW != 3)
						{
						LCD_displayStringRowColumn(0, 0, "WRONG PW TRY AGAIN");
						_delay_ms(2000);
						}
						wrongPW++;
						screen = 0;
						state  = 0;
						if(wrongPW == 3)
						{
							LCD_displayStringRowColumn(0, 0, " ALARM !!!      ");
							ACTIVATE_timer0(&timer0);
							while(seconds != 10);
							wrongPW = 0;
							screen = 0;
							state  = 0;
						}

					}
				}
				else if(screen == 2)
				{
					state = UART_receiveByte();
					LCD_clearScreen();
					if (state == CORRECT_PW)
					{


						LCD_displayStringRowColumn(0, 0,"Enter 4-digit PW      ");
						getPassword(a_firstPassword);
						LCD_clearScreen();
						LCD_displayStringRowColumn(0, 0, "Reenter 4-digit PW");
						getPassword(a_secondPassword);
						compare = strcmp(a_firstPassword ,a_secondPassword );
						if(compare == 0)
						{
							LCD_clearScreen();
							LCD_displayStringRowColumn(0, 0, "password");
							LCD_displayStringRowColumn(1, 0, "Match");
							_delay_ms(1000);
							readyToSend(a_firstPassword , a_message);
							UART_sendByte(NEW_PASSWORD);
							UART_sendString(a_message);
							screen = 0;
							state  = 0;
						}
						else
						{
							LCD_clearScreen();
							LCD_displayStringRowColumn(0, 0, "password");
							LCD_displayStringRowColumn(1, 0, " don't Match");
							_delay_ms(1000);
							UART_sendByte(NEW_PASSWORD);
							UART_sendString(a_oldPassMess);
							LCD_clearScreen();

						}
						screen = 0;
					}
					else if (state == WRONG_PASSWORD)
					{

						LCD_displayStringRowColumn(0, 0, "WRONG PW TRY AGAIN");
						_delay_ms(2000);
						wrongPW++;
						screen = 0;
						state  = 0;
						if(wrongPW == 3)
						{
							LCD_displayStringRowColumn(0, 0, " ALARM !!!      ");
							ACTIVATE_timer0(&timer0);
							while(seconds != 10);
							wrongPW = 0;
							screen = 0;
							state  = 0;
						}
					}
				}

			}
		}

	}
