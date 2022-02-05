/*
 * APP.c
 *
 *  Created on: Jan 25, 2022
 *      Author: abdalah
 */
#include "primitive_data_types.h"
#include "DIO_interface.h"
#include "UART_INTERFACE.h"
#include "LCD_interface.h"
/***************************************************************************/
/************************UAET TEST CASE*************************************/
/***************************************************************************/


int main ()
{

       /*UART INIT*/

	USART_VoidInit(PORTD ,PIN1 ,PIN0);
        /*LCD INIT*/
	LCD_VoidInit4b();
          /*receiving Array*/
     uint8_t ptr[8]= {0};

           /*Send data */
     UART_U8SendBufferSyn("ABDULLA",7);
           /*Receiving  data   */
    UART_U8ReciveBufferSyn(ptr ,7);
            /*write data on LCD*/
    LCD_VoidWriteStringfor4bits(ptr);
	while(1)
	{

	}
return 1;

}

