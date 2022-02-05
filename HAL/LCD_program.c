#include "primitive_data_types.h"

#include <util/delay.h>
#include <string.h>
#include "LCD_interface.h"
#include "DIO_interface.h"
#include "lcd_privet.h"
#include "LCD_interface.h"
#include "LCD_Config.h"

uint32_t LCD_VoidDelay(uint8_t au8_delayper_milli)
{

	uint32_t au32_delay_micro =(uint32_t) au8_delayper_milli *(uint32_t)1000;

	uint32_t au32_counter=0;
	 au32_counter = au32_delay_micro *8;
	 for(uint32_t au64_Local_counter =0 ;au64_Local_counter<(au32_counter/8) ;au64_Local_counter++)
	 {

	 }
	 return au32_counter ;
}



void LCD_WriteCommand(uint8_t Copy_U8Command)
{
	uint8_t au8_error = NOK;

	DIO_SetPinValue(CONTROL_PORT, RS, LOW);
	DIO_SetPinValue(CONTROL_PORT, RW, LOW);
	
	switch(Copy_U8Command)
	{
		case ERASE:
			DIO_Setau8_PORTValue(DATA_PORT, 1);
			break;
		default:
			DIO_Setau8_PORTValue(DATA_PORT, Copy_U8Command);
	}

	DIO_SetPinValue(CONTROL_PORT, EN, HIGH);

	LCD_VoidDelay(2);

	DIO_SetPinValue(CONTROL_PORT, EN, LOW);

	LCD_VoidDelay(1);

}
uint8_t LCD_WriteData4b(uint8_t Copy_U8Data)
{

	uint8_t au8_error = OK;
          if(Copy_U8Data <32)
		     au8_error = NOK;
	DIO_SetPinValue(CONTROL_PORT, RS, HIGH);
	DIO_SetPinValue(CONTROL_PORT, RW, LOW);
	LCD_VoidDelay(2);

	DIO_SetPinValue(CONTROL_PORT, PIN4 , ((( Copy_U8Data)>>4) &1));
	DIO_SetPinValue(CONTROL_PORT, PIN5 , ((( Copy_U8Data)>>5) &1));
	DIO_SetPinValue(CONTROL_PORT, PIN6 , ((( Copy_U8Data)>>6) &1));
	DIO_SetPinValue(CONTROL_PORT, PIN7 , ((( Copy_U8Data)>>7) &1));

	LCD_VoidDelay(2);

	DIO_SetPinValue(CONTROL_PORT, EN, HIGH);
	LCD_VoidDelay(2);

	DIO_SetPinValue(CONTROL_PORT, EN, LOW);
	LCD_VoidDelay(1);

	DIO_SetPinValue(CONTROL_PORT, PIN4, ((( Copy_U8Data)) &1));
	DIO_SetPinValue(CONTROL_PORT, PIN5, ((( Copy_U8Data)>>1) &1));
	DIO_SetPinValue(CONTROL_PORT, PIN6, ((( Copy_U8Data)>>2) &1));
	DIO_SetPinValue(CONTROL_PORT, PIN7, ((( Copy_U8Data)>>3) &1));
	LCD_VoidDelay(1);

	DIO_SetPinValue(CONTROL_PORT, EN, HIGH);

	LCD_VoidDelay(2);

	DIO_SetPinValue(CONTROL_PORT, EN, LOW);

	LCD_VoidDelay(1);
return au8_error ;
}
void LCD_VoidWriteCommand4b(uint8_t Copy_U8Command)
{
	DIO_SetPinValue(CONTROL_PORT, RS, LOW);
	DIO_SetPinValue(CONTROL_PORT, RW, LOW);

			            /*higher bits*/

			DIO_SetPinValue(CONTROL_PORT, PIN4 , (((Copy_U8Command)>>4) &1));
			DIO_SetPinValue(CONTROL_PORT, PIN5 , (((Copy_U8Command)>>5) &1));
			DIO_SetPinValue(CONTROL_PORT, PIN6 , (((Copy_U8Command)>>6) &1));
			DIO_SetPinValue(CONTROL_PORT, PIN7 , (((Copy_U8Command)>>7) &1));




			DIO_SetPinValue(CONTROL_PORT, EN, HIGH);

			LCD_VoidDelay(1);
			DIO_SetPinValue(CONTROL_PORT, EN, LOW);


			                        /* lower bits */


			DIO_SetPinValue(CONTROL_PORT, PIN4, ((( Copy_U8Command))    &1));
			DIO_SetPinValue(CONTROL_PORT, PIN5, ((( Copy_U8Command)>>1) &1));
			DIO_SetPinValue(CONTROL_PORT, PIN6, ((( Copy_U8Command)>>2) &1));
			DIO_SetPinValue(CONTROL_PORT, PIN7, ((( Copy_U8Command)>>3) &1));

	DIO_SetPinValue(CONTROL_PORT, EN, HIGH);

    LCD_VoidDelay(2);
	DIO_SetPinValue(CONTROL_PORT, EN, LOW);

	LCD_VoidDelay(1);
}



uint8_t LCD_VoidWriteStringfor4bits(uint8_t* Copy_U8String)
{
	uint8_t au8_error = NOK;

		au8_error =OK;
	for(int au8_counter=0; au8_counter< strlen(Copy_U8String); au8_counter++)
	{
		LCD_WriteData4b(Copy_U8String[au8_counter]);
	}

	return au8_error ;
}
uint8_t LCD_WriteNum(int Copy_U16Num)
{
	/*print all positive number*/
uint8_t	au8_error =OK ;
        if(Copy_U16Num<0)
        	au8_error =NOK;
	if(Copy_U16Num == 0)
	{
		LCD_WriteData4b('0');
	}
	else
	{
		uint8_t str[10]="";
		int au32_counter = 0;
		while( Copy_U16Num > 0)
		{
			switch(Copy_U16Num%10)
			{
				case 0:str[au32_counter] = '0';break;
				case 1:str[au32_counter] = '1';break;
				case 2:str[au32_counter] = '2';break;
				case 3:str[au32_counter] = '3';break;
				case 4:str[au32_counter] = '4';break;
				case 5:str[au32_counter] = '5';break;
				case 6:str[au32_counter] = '6';break;
				case 7:str[au32_counter] = '7';break;
				case 8:str[au32_counter] = '8';break;
				case 9:str[au32_counter] = '9';break;
			}
			Copy_U16Num /= 10;
			au32_counter++;
		}
		for( au32_counter= strlen(str)-1; au32_counter>=0 ; au32_counter--)
			LCD_WriteData4b(str[au32_counter]);
	   }
	return au8_error;
}


void LCD_VoidInit4b(void)
{

	DIO_SetPinDirection(DATA_PORT, PIN4, OUTPUT);
	DIO_SetPinDirection(DATA_PORT, PIN5, OUTPUT);
	DIO_SetPinDirection(DATA_PORT, PIN6, OUTPUT);
	DIO_SetPinDirection(DATA_PORT, PIN7, OUTPUT);

	DIO_SetPinDirection(CONTROL_PORT, RS, OUTPUT);

	DIO_SetPinDirection(CONTROL_PORT, RW, OUTPUT);

	DIO_SetPinDirection(CONTROL_PORT, EN, OUTPUT);

	LCD_VoidDelay(20);

	LCD_WriteCommand(0b00100000);
	LCD_WriteCommand(0b00100000);
	LCD_WriteCommand(0b10000000);

	LCD_VoidDelay(1);

	LCD_WriteCommand(0b00000000);
	LCD_WriteCommand(0b11110000);

	LCD_VoidDelay(1);
	LCD_WriteCommand(0b00000000);
	LCD_WriteCommand(0b00010000);

	LCD_VoidDelay(2);

}


uint8_t LCD_SetCursorFor4bits(uint8_t Copy_U8Row,uint8_t Copy_U8Column)
{
	uint8_t au_8address =0;
    uint8_t au8_error =OK ;
	au_8address = Copy_U8Row+Copy_U8Column;
        if(Copy_U8Row == 0)
        	LCD_VoidWriteCommand4b((1<<7)|(au_8address));
        else if(Copy_U8Row == 1)
        	LCD_VoidWriteCommand4b((1<<7)|(au_8address)+0x40);
        else
        	au8_error =NOK;

        return au8_error ;
}

