/***************************************************************************************************************
 * File Name    : UART.h
 * Author       : Rana Mohamed
 * Date Created : 19 Jul 2021
 * Description  : This is the Header File of the UART Driver.
 ***************************************************************************************************************/
#ifndef UART_H_
#define UART_H_





/****************************************************INCLUDES***************************************************/
#include <avr/io.h>
#include "micro_config.h"




/********************************************* Preprocessor Macros *******************************************/


/**************************************************************************************************************
 * Set ASYNCHRONOUS_DOUBLE_SPEED_MODE_ACTIVATION -> 1 activate
 * Set ASYNCHRONOUS_DOUBLE_SPEED_MODE_ACTIVATION -> 0 Deactivate
 *************************************************************************************************************/
#define ASYNCHRONOUS_DOUBLE_SPEED_MODE_ACTIVATION 1



/**************************************************************************************************************
 * Set MULTI_PROCESSOR_COMM_MODE -> 1 activate
 * Set MULTI_PROCESSOR_COMM_MODE -> 0 Deactivate
 *************************************************************************************************************/
#define MULTI_PROCESSOR_COMM_MODE 0



/**************************************************************************************************************
 * Set USART_DATA_REGISTER_EMPTY_INT_EN -> 1 activate
 * Set USART_DATA_REGISTER_EMPTY_INT_EN -> 0 Deactivate
 *************************************************************************************************************/
#define USART_DATA_REGISTER_EMPTY_INT_EN 0



/**************************************************************************************************************
 * Set TX_COMPLETE_INTERRUPT_ENABLE -> 1 activate
 * Set TX_COMPLETE_INTERRUPT_ENABLE -> 0 Deactivate
 *************************************************************************************************************/
#define TX_COMPLETE_INTERRUPT_ENABLE  0



/**************************************************************************************************************
 * Set RX_COMPLETE_INTERRUPT_ENABLE -> 1 activate
 * Set RX_COMPLETE_INTERRUPT_ENABLE -> 0 Deactivate
 *************************************************************************************************************/
#define RX_COMPLETE_INTERRUPT_ENABLE  0


/**************************************************************************************************************
 * Set the value of the BAUD_RATE as required
 *************************************************************************************************************/
#define BAUD_RATE 9600



/**************************************************************************************************************
 * Set the value of Number_X_BAUD_RATE accordingnto the operating mode:
 * 16UL -> For Asynchronous Normal Mode.
 * 8UL  -> For Asynchronous Double Speed Mode.
 * 2UL  -> For Synchronous Double Speed Mode.
 *************************************************************************************************************/
#define Number_X_BAUD_RATE 8UL




#define CHECK_PASSWORD	0x0A
#define SAVE_PASSWORD	0x0B
#define WRONG_PASSWORD  0x0C
#define OPEN_DOOR		0x0D
#define CHANGE_PASSWORD 0x0E
#define CORRECT_PW		0x0F
#define NEW_PASSWORD	0x10


/*********************************************** ENUMUMERATIONS **********************************************/


/**************************************************************************************************************
 * Enumeration Name: Data_bitMode
 * Enumeration Description:
 *  0- Five_bit  : Set the Character size to 5 bit mode.
 *  1- Six_bit   : Set the Character size to 6 bit mode.
 *  2- Seven_bit : Set the Character size to 7 bit mode.
 *  3- Eight_bit : Set the Character size to 8 bit mode.
 *  4- Nine_bit  : Set the Character size to 9 bit mode.
 *
 *************************************************************************************************************/
typedef enum {
	Five_bit =0 , Six_bit =1, Seven_bit =2, Eight_bit =3 , Nine_bit =7
}Data_bitMode;



/**************************************************************************************************************
 * Enumeration Name: Usart_modeSelect
 * Enumeration Description:
 *  0- Asynchronous  : Set the USART into Asynchronous mode.
 *  1- Synchronous   : Set the USART into Synchronous mode.
 *
 *************************************************************************************************************/
typedef enum {
	Asynchronous,Synchronous
}Usart_modeSelect;




/**************************************************************************************************************
 * Enumeration Name: Usart_paritymode
 * Enumeration Description:
 *  0- Disabled          : Disables the Parity Mode.
 *  1- Enable_EvenParity : Enables the Even Parity Mode.
 *  2- Enable_OddParity  : Enables the Odd Parity Mode.
 *
 **************************************************************************************************************/
typedef enum {
	Disabled=0,Enable_EvenParity=2,Enable_OddParity=2
}Usart_paritymode;




/**************************************************************************************************************
 * Enumeration Name: Usart_stopbits
 * Enumeration Description:
 *  0- stop1_bit   : Set the USART number of stop bits to 1.
 *  1- stop2_bit   : Set the USART number of stop bits to 2.
 *
 *************************************************************************************************************/
typedef enum {
	stop1_bit , stop2_bit
}Usart_stopbits;




/**************************************************************************************************************
 * Enumeration Name: Usart_clockPolarity
 * Enumeration Description:
 *  0- Rising_XCK_EDGE    : Set the Clock Polarity to 0 for the USART in Asynchronous mode.
 *  1- Falling_XCK_EDGE   : Set the Clock Polarity to 1 for the USART in Synchronous mode.
 *
 *************************************************************************************************************/
typedef enum {
	Rising_XCK_EDGE , Falling_XCK_EDGE
}Usart_clockPolarity;




/**************************************************************************************************************
 * Structure Name: UCSRBC_init
 * Structure Members Description:
 *  1- datamode       : Variable of type Data_bitMode Enumeration
 *  2- Usart_mode     : Variable of type Usart_modeSelect Enumeration
 *  3- parity_mode    : Variable of type Usart_paritymode Enumeration
 *  4- stopbit        : Variable of type Usart_stopbits Enumeration
 *  5- clock_Polarity : Variable of type Usart_clockPolarity Enumeration
 *
 *************************************************************************************************************/
typedef struct{

	Data_bitMode        Data_mode;
	Usart_modeSelect    Usart_mode ;
	Usart_paritymode    parity_mode;
	Usart_stopbits      stopbit;
	Usart_clockPolarity clock_Polarity;

}UCSRBC_init;





/********************************************* FUNCTION DECLARATIONS ******************************************/



/***************************************************************************************************************
 * Function Name : UART_init
 * Description   : This Function is responsible for setting the USART Registers (UCSRA- UCSRB- UCSRC)
 * Arguments     : A Pointer to Structure
 * Return        : None
 ***************************************************************************************************************/
void UART_init(const UCSRBC_init *DataPtr);



/***************************************************************************************************************
 * Function Name : UART_sendByte
 * Description   : This Function is responsible for sending a byte through the UART Transmitter
 * Arguments     : Data
 * Return        : None
 ***************************************************************************************************************/
void UART_sendByte( char data);



/***************************************************************************************************************
 * Function Name : UART_sendString
 * Description   : This Function is responsible for sending a String through the UART Transmitter
 * Arguments     : Pointer to Character
 *                 The Function is passed an address which is the address of the String array
 *                 so it is carried by a pointer to character.
 * Return        : None
 ***************************************************************************************************************/
void UART_sendString( char* dataa);


/**************************************************************************************************************
 * Function Name : UART_receiveByte
 * Description   : This Function is responsible for receiving a byte through the UART Receiver.
 * Arguments     : None
 * Return        : UDR value (1 Byte -> char)
 **************************************************************************************************************/
char UART_receiveByte();

/***************************************************************************************************************
 * Function Name : UART_receiveString
 * Description   : This Function is responsible for receiving a String through the UART Receiver.
 * Arguments     : None
 * Return        : None
 ***************************************************************************************************************/
void UART_receiveString(char *dataa);





#endif /* UART_H_ */
