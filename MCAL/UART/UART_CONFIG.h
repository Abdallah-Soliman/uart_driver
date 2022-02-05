/*
 * UART_CONFIG.h
 *
 *  Created on: Jan 25, 2022
 *      Author: abdalah
 */

#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

	/*1- receiver, transmitter enable
	 * 2- 8 bits
	 * 3- Asynchronous
	 * 4- no interrupts
	 * 5- normal speed
	 * 6- baud rate = 9600bps
	 * 7- no parity, 1 stop bit
	 * */
   /**
    * REG_8_BITS
    * REG_7_BITS
    * REG_9_BITS
    */

#define  NUMBER_OF_BITS   REG_8_BITS

   /**
    * ASYNCHRONOUS
    * SYNCHRONOUS
    */

#define  ASY_OR_SYN   ASYNCHRONOUS

   /*
    * NO_PARTY_SELECT
    * EVEN_PARTY_SELECT
    * ODD_PARTY_SELECT
    */

#define  PARTY_SELECT  NO_PARTY_SELECT

/*
 * ONE_BIT
 * TWO_BIT
 */


#define  NUMBER_OF_STOP_BITS    ONE_BIT


/*
 * RATE_9600
 * RATE_4600
 */



#define  BOUD_RATE    RATE_9600

/*
 * ENABLE
 * DISABLE
 */

#define  TRANSMITER_CIRCUT   ENABLE



#define  RECEIVER_CIRCUT   ENABLE

#endif /* UART_CONFIG_H_ */
