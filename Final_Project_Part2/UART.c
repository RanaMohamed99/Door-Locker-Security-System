/**************************************************************************************************************
 * File Name    : UART.c
 * Author       : Rana Mohamed
 * Date Created : 19 Jul 2021
 * Description  : This is the Source File of the UART Driver.
 *************************************************************************************************************/




/****************************************************INCLUDES**************************************************/
#include "UART.h"


/********************************************** Preprocessor Macros *******************************************/

#define UBRR_value ((F_CPU/((Number_X_BAUD_RATE)*BAUD_RATE))-1)





/********************************************** FUNCTIONS DEFINITIONS *****************************************/

/**************************************************************************************************************
 * Function Name : UART_init
 * Description   : This Function is responsible for setting the USART Registers (UCSRA- UCSRB- UCSRC)
 * Arguments     : A Pointer to Structure
 * Return        : None
 **************************************************************************************************************/
void UART_init(const UCSRBC_init *DataPtr){
	/*
	 * 1- Initalise USART I/O data register UDR -> 0
	 * UCSRA :
	 * 2- If Double speed mode is activated U2X -> 1
	 * UCSRB :
	 * 3- Enable the Transmitter Interrupt
	 * 4- Enable the Receiver Interrupt
	 * 5- Set the UCSRA  U2X -> 1
	 * 6- Set the UCSRB bits according to the values of the Structure members that is passed by address
	 *    1- Character Data Size bits (UCSZ2, UCSZ1,UCSZ0).
	 * UCSRC :
	 * 7- Set the UCSRC bits according to the values of the Structure members that is passed by address
	 *    1- USART Mode Select (UMSEL)
	 *    2- Parity Mode (UPM1:0)
	 *    3- Stop Bit (USBS)
	 *    4- Clock Polarity (UCPOL)
	 */
    #if(ASYNCHRONOUS_DOUBLE_SPEED_MODE_ACTIVATION ==1)
	   UCSRA = 1<<U2X;
    #endif
	UCSRB  = ( 1<<TXEN ) | ( 1<<RXEN );
	UCSRB |= (UCSRB & 0xFB) | ((DataPtr-> Data_mode));
	UCSRC |= (1<<URSEL);
	UCSRC |= (UCSRC & 0xF9) | ((DataPtr-> Data_mode) <<1);
	UCSRC |= (UCSRC & 0xBF) | ((DataPtr->Usart_mode) <<6);
	UCSRC |= (UCSRC & 0xCF) | ((DataPtr->parity_mode) <<4);
	UCSRC |= (UCSRC & 0xF7) | ((DataPtr->stopbit) <<3);
	UCSRC |= (UCSRC & 0xFE) | (DataPtr->clock_Polarity);
	UBRRH  = UBRR_value >>8;
	UBRRL  = UBRR_value;

    #if(MULTI_PROCESSOR_COMM_MODE ==1)
	   UCSRA |= 1<<MPCM;
    #endif
    #if(USART_DATA_REGISTER_EMPTY_INT_EN)
	   UCSRB |=1<<UDRIE;
    #endif
    #if(TX_COMPLETE_INTERRUPT_ENABLE)
	   UCSRB |=1<<TXCIE;
    #endif
    #if(RX_COMPLETE_INTERRUPT_ENABLE)
	   UCSRB |=1<<RXCIE;
    #endif





}



/**************************************************************************************************************
 * Function Name : UART_sendByte
 * Description   : This Function is responsible for sending a byte through the UART Transmitter
 * Arguments     : Data
 * Return        : None
 *************************************************************************************************************/
void UART_sendByte( char data){
	/*
	 * 1- Set the data into the USART DATA REGISTER UDR-> Data
	 * 2- Wait until the Transmit complete flag is 1 meaning that data is fully transmitted.
	 * 3- Finally Clear the Transmitter flag by setting it to  1  TXC -> 1
	 */
	UDR=data;
	while(((UCSRA) & (1<<TXC))==0);
    UCSRA |= (1<<TXC);

}



/**************************************************************************************************************
 * Function Name : UART_sendByte
 * Description   : This Function is responsible for receiving a byte through the UART Receiver.
 * Arguments     : None
 * Return        : UDR value (1 Byte -> char)
 **************************************************************************************************************/
char UART_receiveByte(){
	/*
	 * 1- Wait until the Receive complete flag is 1 meaning that data is fully received.
	 * 2- Read the value of the UDR (Return the value of the USART DATA REGISTER).
	 */
	while(((UCSRA) & (1<<RXC))==0);
	return UDR;

}



/**************************************************************************************************************
 * Function Name : UART_sendString
 * Description   : This Function is responsible for sending a String through the UART Transmitter
 * Arguments     : Pointer to Character
 *                 The Function is passed an address which is the address of the String array
 *                 so it is carried by a pointer to character.
 * Return        : None
 *************************************************************************************************************/
void UART_sendString( char* dataa){
	/*
	 * 1- Initialise the Counter to zero
	 * 2- Keep looping in the string array until you reach '\0' character which indicates the end of the string.
	 * 3- Call the UART_sendByte() Function and pass each character from the string.
	 * 4- Increment the Counter.
	 */
	int i=0;
	while(dataa[i] !='\0'){
		UART_sendByte(dataa[i]);
		i++;
	}

}



/**************************************************************************************************************
 * Function Name : UART_receiveString
 * Description   : This Function is responsible for receiving a String through the UART Receiver.
 * Arguments     : None
 * Return        : None
 **************************************************************************************************************/
void UART_receiveString(char *dataa){
	/*
    * 1- Initialise the Counter to zero
    * 2- Create a pointer to Character.
    * 3- Call the UART_receiveByte() function and put the first byte in location 0.
	* 4- Keep looping in the string array until you reach the '#' character.
	*      4.1 Increment the counter.
	*      4.2 Call the UART_receiveByte() function and put the byte in string array.
	* 5- After exiting the Loop replace the '#' character with '\0' character.
	*/

	int i=0;
	dataa[i]=UART_receiveByte();
	while(dataa[i] !='#'){
		i++;
		dataa[i]=UART_receiveByte();
	}
	dataa[i]='\0';
}
