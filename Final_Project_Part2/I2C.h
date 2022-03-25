/***************************************************************************************************************
 * File Name    : I2C.h
 * Author       : Rana Mohamed
 * Date Created : 19 Jul 2021
 * Description  : This is the Header File of the I2C Driver.
 ***************************************************************************************************************/

#ifndef I2C_H_
#define I2C_H_

/****************************************************INCLUDES***************************************************/
#include <avr/io.h>





/*********************************************** Preprocessor Macros *******************************************/
#define SCL_FREUQENCY 400.000
#define TWPS_PRESCALER 0
#define SLAVE_ADDRESS  1


#define TW_START         0x08 // start has been sent
#define TW_REP_START     0x10 // repeated start
#define TW_MT_SLA_W_ACK  0x18 // Master transmit ( slave address + Write request ) to slave + Ack received from slave
#define TW_MT_SLA_R_ACK  0x40 // Master transmit ( slave address + Read request ) to slave + Ack received from slave
#define TW_MT_DATA_ACK   0x28 // Master transmit data and ACK has been received from Slave.
#define TW_MR_DATA_ACK   0x50 // Master received data and send ACK to slave
#define TW_MR_DATA_NACK  0x58 // Master received data but doesn't send ACK to slave







/********************************************* FUNCTION DECLARATIONS ******************************************/



/**************************************************************************************************************
 * Function Name : TWI_init().
 * Description   : This Function is responsible for initialising the I2C.
 * Arguments     : None.
 * Return        : None.
 **************************************************************************************************************/
void TWI_init();

/**************************************************************************************************************
 * Function Name : TWI_start().
 * Description   : This Function is responsible for sending the start bit of the I2C.
 * Arguments     : None.
 * Return        : None.
 **************************************************************************************************************/
void TWI_start();


/**************************************************************************************************************
 * Function Name : TWI_stop.
 * Description   : This Function is responsible for sending the stop bit of the I2C.
 * Arguments     : None.
 * Return        : None.
 **************************************************************************************************************/
void TWI_stop();



/**************************************************************************************************************
 * Function Name : TWI_write.
 * Description   : This Function is responsible for writing data the I2C.
 * Arguments     : char data.
 * Return        : None.
 **************************************************************************************************************/
void TWI_write(char data);



/**************************************************************************************************************
 * Function Name : TWI_readWithACK().
 * Description   : This Function is responsible for reading data of TWDR.
 * Arguments     : None.
 * Return        : TWDR (char).
 **************************************************************************************************************/
char TWI_readWithACK();



/**************************************************************************************************************
 * Function Name : TWI_readWithACK().
 * Description   : This Function is responsible for reading data of TWDR.
 * Arguments     : None.
 * Return        : TWDR (char).
 **************************************************************************************************************/
char TWI_readWithNACK();



/**************************************************************************************************************
 * Function Name : TWI_getStatus().
 * Description   : This Function is responsible for reading data of TWDR.
 * Arguments     : None.
 * Return        : TWDR (char).
 **************************************************************************************************************/
char TWI_getStatus();



#endif /* I2C_H_ */
