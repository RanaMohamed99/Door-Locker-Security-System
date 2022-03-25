/***************************************************************************************************************
 * File Name    : I2C.c
 * Author       : Rana Mohamed
 * Date Created : 19 Jul 2021
 * Description  : This is the Source File of the I2C Driver.
 ***************************************************************************************************************/



/****************************************************INCLUDES***************************************************/
#include "I2C.h"



#define TWBR_VALUE (((F_CPU/SCL_FREUQENCY)-16)/(1/(2*pow(4,TWPS_PRESCALER))))

/********************************************* FUNCTION DEFENITIONS ********************************************/


/**************************************************************************************************************
 * Function Name : TWI_init().
 * Description   : This Function is responsible for initialising the I2C.
 * Arguments     : None.
 * Return        : None.
 **************************************************************************************************************/
void TWI_init(){

	/*
	 * TWBR -> The calculated TWBR_Value.
	 * TWSR :
	 *   TWPS -> TWPS_PRESCALER.
	 * TWAR :
	 *    Bits for (1:7) -> SLAVE_ADDRESS
	 * TWCR :
	 *    TWI ENABLE BIT ->1.
	 */

	TWBR = TWBR_VALUE;
	TWSR = TWPS_PRESCALER;
	TWAR= ( 1<<SLAVE_ADDRESS );
	TWCR= 1<< TWEN;
}


/**************************************************************************************************************
 * Function Name : TWI_start().
 * Description   : This Function is responsible for sending the start bit of the I2C.
 * Arguments     : None.
 * Return        : None.
 **************************************************************************************************************/
void TWI_start(){
	/*
	 * TWCR :
	 * TWI INTERERUPT FLAG -> 1 (Clear the flag by setting it to one).
	 * TWI STOP CONDITION BIT -> 1.
	 * TWI ENABLE BIT ->1.
	 */
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
	while((TWCR &(1<<TWINT))==0);
}



/**************************************************************************************************************
 * Function Name : TWI_stop.
 * Description   : This Function is responsible for sending the stop bit of the I2C.
 * Arguments     : None.
 * Return        : None.
 **************************************************************************************************************/
void TWI_stop(){
    /*
	 * TWCR :
	 * TWI INTERERUPT FLAG -> 1 (Clear the flag by setting it to one).
	 * TWI STOP CONDITION BIT -> 1.
	 * TWI ENABLE BIT.
	 */
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}



/**************************************************************************************************************
 * Function Name : TWI_write.
 * Description   : This Function is responsible for writing data the I2C.
 * Arguments     : char data.
 * Return        : None.
 **************************************************************************************************************/
void TWI_write(char data){
     /*
     * TWDR : -> Data to be written.
	 * TWCR :
	 * TWI INTERERUPT FLAG -> 1 (Clear the flag by setting it to one).
	 * TWI ENABLE BIT.
	 */
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while((TWCR &(1<<TWINT))==0);
}



/**************************************************************************************************************
 * Function Name : TWI_readWithACK().
 * Description   : This Function is responsible for reading data of TWDR.
 * Arguments     : None.
 * Return        : TWDR (char).
 **************************************************************************************************************/
char TWI_readWithACK(){
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1
	 * Wait for TWINT flag set in TWCR Register (data received successfully)
	 * Read Data
	 */
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    while((TWCR &(1<<TWINT))==0);
    return TWDR;
}



/**************************************************************************************************************
 * Function Name : TWI_readWithACK().
 * Description   : This Function is responsible for reading data of TWDR.
 * Arguments     : None.
 * Return        : TWDR (char).
 **************************************************************************************************************/
char TWI_readWithNACK(){

	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1
	 * Wait for TWINT flag set in TWCR Register (data received successfully)
     * Read Data
	 */
	TWCR = (1 << TWINT) | (1 << TWEN);
    while((TWCR &(1<<TWINT))==0);
    return TWDR;
}


/**************************************************************************************************************
 * Function Name : TWI_getStatus().
 * Description   : This Function is responsible for reading data of TWDR.
 * Arguments     : None.
 * Return        : TWDR (char).
 **************************************************************************************************************/
char TWI_getStatus(){

	/* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
    char status;
    status = TWSR & 0xF8;
    return status;
}




