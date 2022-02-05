/*
 * UART_PROGRAM.c
 *
 *  Created on: Jan 25, 2022
 *      Author: abdalah
 */

#include "primitive_data_types.h"
#include "BIT_MATH.h"
#include "UART_PRIVET.h"
#include "UART_CONFIG.h"
                          /*global variable for initialization */

                         static void (*g_ptr_func)(void) =NULL ;

                        static uint8_t g_8Counter =INIT_VALUE ;

                        static uint8_t *ptr_data =NULL;

                        static uint8_t g_size =INIT_VALUE;

         /************************************************************************************/
         /************************************************************************************/
         /*************************    UART initialization   *********************************/
         /************************************************************************************/




 void USART_VoidInit(uint8_t PORT ,uint8_t PIN_TX,uint8_t PIN_RX)
 {

	uint8_t UCSRC_Value=INIT_VALUE;

	DIO_SetPinDirection(PORT ,PIN_RX ,INPUT);
	DIO_SetPinDirection(PORT ,PIN_RX ,OUTPUT);


	       /*UCSRC register select*/
	    SET_BIT(UCSRC_Value,UCSRC_URSEL);
	          /*number of char*/
	#if  NUMBER_OF_BITS ==  REG_8_BITS
		SET_BIT(UCSRC_Value,UCSRC_UCSZ0);
		SET_BIT(UCSRC_Value,UCSRC_UCSZ1);
	#elif NUMBER_OF_BITS ==  REG_7_BITS
		CLR_BIT(UCSRC_Value,UCSRC_UCSZ0);
		SET_BIT(UCSRC_Value,UCSRC_UCSZ1);

	#elif 	NUMBER_OF_BITS ==  REG_9_BITS
		SET_BIT(UCSRC_Value,UCSRC_UCSZ0);
		SET_BIT(UCSRC_Value,UCSRC_UCSZ1);
		SET_BIT(UCSRC_Value,UCSRC_UCSZ2);
	#endif
		         /*select mode*/
	#if  ASY_OR_SYN ==  ASYNCHRONOUS
		CLR_BIT(UCSRC_Value,UCSRC_UMSEL);
	#elif ASY_OR_SYN ==  SYNCHRONOUS
		SET_BIT(UCSRC_Value,UCSRC_UMSEL);

	#endif
		             /*parity select*/
	#if  PARTY_SELECT ==  NO_PARTY_SELECT

		CLR_BIT(UCSRC_Value,UCSRC_UPM0);
		CLR_BIT(UCSRC_Value,UCSRC_UPM1);
	#elif PARTY_SELECT ==  EVEN_PARTY_SELECT
		CLR_BIT(UCSRC_Value,UCSRC_UPM0);
		SET_BIT(UCSRC_Value,UCSRC_UPM1);

	#elif PARTY_SELECT == ODD_PARTY_SELECT
		SET_BIT(UCSRC_Value,UCSRC_UPM0);
		SET_BIT(UCSRC_Value,UCSRC_UPM1);
	#endif
		              /*number of stop bits*/
	#if NUMBER_OF_STOP_BITS == ONE_BIT
		CLR_BIT(UCSRC_Value,UCSRC_USBS);
	#elif 	NUMBER_OF_STOP_BITS == TWO_BIT
		SET_BIT(UCSRC_Value,UCSRC_USBS);
	#endif
		/*set the register configration*/
		UCSRC=UCSRC_Value;
	#if BOUD_RATE == RATE_9600
		UBRRL=51;
	#elif 	BOUD_RATE == RATE_4600
		UBRRL=12;
	#endif

		/*Receiver and transmitter enable*/
	#if TRANSMITER_CIRCUT == ENABLE
		SET_BIT(UCSRB,UCSRB_TXEN);
	#elif TRANSMITER_CIRCUT == DISABLE
		CLR_BIT(UCSRB,UCSRB_TXEN);
	#endif


	#if RECEIVER_CIRCUT == ENABLE
		SET_BIT(UCSRB,UCSRB_RXEN);
	#elif RECEIVER_CIRCUT == DISABLE
		CLR_BIT(UCSRB,UCSRB_RXEN);
	#endif

}



 /*************************************************************************************/
 /*************************************************************************************/
 /************************     UART receive data   ************************************/
 /*************************************************************************************/



uint8_t UART_U8GetData(uint8_t* au_ptr)
{
	uint8_t error_state =INIT_VALUE ;
	if(au_ptr!=NULL)
	{
	/*wait until the transmit buffer is empty*/
	while((GET_BIT(UCSRA,UCSRA_RXC))==0);

	/*recive the data*/
	*au_ptr =UDR;
     }
	else
	{
		error_state =HIGH ;
	}
	return error_state;
}




/*************************************************************************************/
/*************************************************************************************/
/************************     UART SEND DATA   ***************************************/
/*************************************************************************************/




uint8_t UART_U8_SendData(uint8_t * au_ptr)
{
	uint8_t error_state =INIT_VALUE ;
     if(au_ptr!=NULL )
     {
    UDR =*au_ptr ;
	while((GET_BIT(UCSRA,UCSRA_TXC))==LOW);

	/*To clear flag*/
     SET_BIT(UCSRA,UCSRA_TXC);
     }
     else
     {
    	 error_state =HIGH;
     }
return error_state;

}


/*************************************************************************************/
/*************************************************************************************/
/************************     UART send buffer synchronous   *************************/
/*************************************************************************************/






uint8_t UART_U8SendBufferSyn(uint8_t *au_ptr ,uint8_t size)
{
    uint8_t error_state =INIT_VALUE;
	if(au_ptr !=NULL)
      {
	for(uint8_t au8_counter =INIT_VALUE ; au8_counter < size ;au8_counter ++)
	{
		UART_U8_SendData(&(*(au_ptr +au8_counter)));
	}
       }
	else
	{
		error_state =HIGH;
	}
	return error_state ;
}



/*************************************************************************************/
/*************************************************************************************/
/************************     UART receive buffer synchronous   **********************/
/*************************************************************************************/


uint8_t UART_U8ReciveBufferSyn(uint8_t *au_ptr ,uint8_t size )
{
	uint8_t error_state =LOW;

	if(au_ptr != NULL)
	{
		for(uint8_t au8_counter=LOW ;au8_counter <size ;au8_counter++)
		{
			UART_U8GetData(&(*(au_ptr+au8_counter)));
		}
	}
	else
	{
		error_state =HIGH;
	}
	return error_state ;
}


/*************************************************************************************/
/*************************************************************************************/
/************************     UART receive buffer Asynchronous   *********************/
/*************************************************************************************/





uint8_t UART_U8ReciveBufferAsyn(uint8_t *au_ptr ,uint8_t size ,void (*Notification)(void))
{
	uint8_t error_state =LOW;
	/*variables initialization*/
	if(au_ptr !=NULL)
	{
	ptr_data =au_ptr ;

	g_size =size;

	 g_ptr_func= Notification;

	/*ENABLE interrupt*/

    SET_BIT(UCSRB ,UCSRB_RXCIE);
	}
	else
	{
		error_state=HIGH;
	}
	return error_state;
}



/*************************************************************************************/
/*************************************************************************************/
/************************     ISR for receiving complete   ***************************/
/*************************************************************************************/


void __vector_13(void) __attribute__((signal));

void __vector_13(void)
{
	if(g_8Counter <g_size-1)
	{
		ptr_data [g_8Counter]=UDR;
		g_8Counter++;
	}
	else
	{
		g_ptr_func();
		/*clear interrupt*/

	    CLR_BIT(UCSRB ,UCSRB_RXCIE);
	}


}

