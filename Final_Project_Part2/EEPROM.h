/***************************************************************************************************************
 * File Name    : EEPROM.c
 * Author       : Rana Mohamed
 * Date Created : 19 Jul 2021
 * Description  : This is the Source File of the EEPROM Driver.
 ***************************************************************************************************************/

#ifndef EEPROM_H_
#define EEPROM_H_

/****************************************************INCLUDES***************************************************/
#include <avr/io.h>
#include <util/delay.h>
#include "I2C.h"
#include "std_types.h"





/*********************************************** Preprocessor Macros *******************************************/
#define ERROR 0
#define SUCCESS 1
#define FIRST_LOC_EEPROM 0x0311




/********************************************* FUNCTION DECLARATIONS ******************************************/


/**************************************************************************************************************
 * Function Name : EEPROM_init().
 * Description   : This Function is responsible for calling the TWI_init() function to initialise the I2C.
 * Arguments     : None.
 * Return        : None.
 **************************************************************************************************************/
void EEPROM_init();



/***************************************************************************************************************
 * Function Name : EEPROM_writeByte.
 * Description   : This Function is responsible for writing bytes to EEPROM.
 * Arguments     : unsigned short variable , pointer to character that carries an address..
 * Return        : char.
 ***************************************************************************************************************/
uint8 EEPROM_writeByte(uint16 u16addr, uint8 u8data);


/**************************************************************************************************************
 * Function Name : EEPROM_readByte.
 * Description   : This Function is responsible for reading bytes from EEPROM.
 * Arguments     : unsigned short variable , pointer to character that carries an address.
 * Return        : char.
 **************************************************************************************************************/
uint8 EEPROM_readByte(uint16 u16addr, uint8 *u8data);



/**************************************************************************************************************
 * Function Name : EEPROM_readPassword.
 * Description   : This Function is responsible for reading bytes from EEPROM.
 * Arguments     : Array to carry data read from EEPROM ,char k.
 * Return        : None.
 **************************************************************************************************************/
void EEPROM_readPassword(uint8 buffer[],uint8 k);




#endif /* EEPROM_H_ */
