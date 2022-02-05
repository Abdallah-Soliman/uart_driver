
#ifndef _LCD_INTERFACE_H_
#define _LCD_INTERFACE_H_

	

	void LCD_VoidWriteData(uint8_t Copy_U8Data);
	void LCD_WriteCommand(uint8_t Copy_U8Command);
	uint8_t LCD_WriteNum(int num);
	uint8_t LCD_SetCursor(uint8_t Copy_U8Row, uint8_t Copy_U8Column);
	uint8_t LCD_WriteData4b(uint8_t Copy_U8Data);
	void LCD_VoidInit4b(void);

#endif
