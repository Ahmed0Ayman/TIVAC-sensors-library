

#include "LCD_Bits.h"
#include "TM4C123GH6PM.h"


LcdBitSelect_t LcdBitSelect ={

	
	
	.LcdBits[LCD_BIT_D7_PIN].Port = GPIOA ,
	.LcdBits[LCD_BIT_D7_PIN].Pin  = GPIO_PIN_7	,
	
	
	.LcdBits[LCD_BIT_D6_PIN].Port = GPIOA ,
	.LcdBits[LCD_BIT_D6_PIN].Pin  = GPIO_PIN_6	,
	
	
	.LcdBits[LCD_BIT_D5_PIN].Port = GPIOA ,
	.LcdBits[LCD_BIT_D5_PIN].Pin  = GPIO_PIN_5	,
	
	
	.LcdBits[LCD_BIT_D4_PIN].Port = GPIOA ,
	.LcdBits[LCD_BIT_D4_PIN].Pin  = GPIO_PIN_4	,
	
	
	.LcdBits[LCD_BIT_E_PIN].Port = GPIOA ,
	.LcdBits[LCD_BIT_E_PIN].Pin  = GPIO_PIN_3	,

	.LcdBits[LCD_BIT_RS_PIN].Port = GPIOA ,
	.LcdBits[LCD_BIT_RS_PIN].Pin  = GPIO_PIN_2	,
	
	.LcdBits[LCD_BIT_RW_PIN].Port = GPIOA ,
	.LcdBits[LCD_BIT_RW_PIN].Pin  = GPIO_PIN_1	
			
	};
