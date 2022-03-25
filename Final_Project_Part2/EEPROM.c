/***************************************************************************************************************
 * File Name    : EEPROM.h
 * Author       : Rana Mohamed
 * Date Created : 19 Jul 2021
 * Description  : This is the Header File of the EEPROM Driver.
 ***************************************************************************************************************/



/****************************************************INCLUDES***************************************************/
#include "EEPROM.h"




/********************************************* FUNCTION DEFENITIONS ********************************************/




/**************************************************************************************************************
 * Function Name : EEPROM_init().
 * Description   : This Function is responsible for calling the TWI_init() function to initialise the I2C.
 * Arguments     : None.
 * Return        : None.
 **************************************************************************************************************/
void EEPROM_init()
{
	/*
	 * Call the TWI_init() function to initialise the I2C.
	 */
	TWI_init();
}


/**************************************************************************************************************
 * Function Name : EEPROM_writeByte.
 * Description   : This Function is responsible for writing bytes to EEPROM.
 * Arguments     : unsigned short variable , pointer to character that carries an address..
 * Return        : char.
 **************************************************************************************************************/
uint8 EEPROM_writeByte(uint16 u16addr, uint8 u8data)
{
	/*
	 * 1- Call the TWI_start() -> Send the Start Bit.
	 * 2- Send the device address, we need to get A8 A9 A10 address bits from the
     *    memory location address and R/W=0 (write).
	 * 3- Send the required memory location address.
	 * 4- Write byte to EEprom.
	 * 5- Send the Stop Bit.
	 *
	 *
	 */
    TWI_start();
    if (TWI_getStatus() != TW_START){
    	return ERROR;
    }
    TWI_write((uint8)(0xA0 | ((u16addr & 0x0700)>>7)));
    if (TWI_getStatus() != TW_MT_SLA_W_ACK){
        return ERROR;
    }
    TWI_write((uint8)(u16addr));
    if (TWI_getStatus() != TW_MT_DATA_ACK){
        return ERROR;
    }

    TWI_write(u8data);
    if (TWI_getStatus() != TW_MT_DATA_ACK){
        return ERROR;
    }
    TWI_stop();

    return SUCCESS;
}



/**************************************************************************************************************
 * Function Name : EEPROM_readByte.
 * Description   : This Function is responsible for reading bytes from EEPROM.
 * Arguments     : unsigned short variable , pointer to character that carries an address.
 * Return        : char.
 **************************************************************************************************************/
uint8 EEPROM_readByte(uint16 u16addr, uint8 *u8data)
{
	/*
	 * 1- Call the TWI_start() -> Send the Start Bit.
	 * 2- Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write).
	 * 3- Send the required memory location address
	 * 4- Send the Repeated Start Bit.
	 * 5- Send the device address, we need to get A8 A9 A10 address bits from the
       memory location address and R/W=1 (Read)
	 * 6- Read Byte from Memory without send ACK.
	 * 7- Send the Stop Bit.
	 *
	 *
     */

    TWI_start();
    if (TWI_getStatus() != TW_START){
        return ERROR;
    }

    TWI_write((uint8)((0xA0) | ((u16addr & 0x0700)>>7)));
    if (TWI_getStatus() != TW_MT_SLA_W_ACK)
        return ERROR;

    TWI_write((uint8)(u16addr));
    if (TWI_getStatus() != TW_MT_DATA_ACK)
        return ERROR;

    TWI_start();
    if (TWI_getStatus() != TW_REP_START)
        return ERROR;


    TWI_write((uint8)((0xA0) | ((u16addr & 0x0700)>>7) | 1));
    if (TWI_getStatus() != TW_MT_SLA_R_ACK)
        return ERROR;


    *u8data = TWI_readWithNACK();
    if (TWI_getStatus() != TW_MR_DATA_NACK)
        return ERROR;

    TWI_stop();
    return SUCCESS;
}



/**************************************************************************************************************
 * Function Name : EEPROM_readPassword.
 * Description   : This Function is responsible for reading bytes from EEPROM.
 * Arguments     : Array to carry data read from EEPROM ,char k.
 * Return        : None.
 **************************************************************************************************************/
void EEPROM_readPassword(uint8 buffer[],uint8 k)
{
	uint8 read;
	for(uint8 i = 0; i < k ;i++)
	{
		EEPROM_readByte(FIRST_LOC_EEPROM + i, &read);
		_delay_ms(50);
		buffer[i] = read;
	}
}
