
#ifndef __LCD__
#define __LCD__
#include <stdint.h>
#include "TM4C123GH6PM.h"
#include "string.h"
#include "LCD_Bits.h"




/* 
 * this is a LCD 2*16 driver library you can choose which port by modify LCD_PORT you connect your lcd 
 * for more information about how to use this driver please check attatchment  pdf file
 * that contain all you need to start with this driver 
*/ 


typedef GPIOA_Type GPIO_TypeDef;

typedef struct 
{
		GPIO_TypeDef   * Port ;
		uint8_t          Pin  ;
	}LCD_bit;

typedef struct   
{
	LCD_bit LcdBits[7];
}LcdBitSelect_t;



extern LcdBitSelect_t LcdBitSelect ;







/*some of common commands that used with LCD*/
#define LCD_COMMANED_CLEAR_LCD								0X01U
#define LCD_COMMANED_RETURN_HOME							0X02U
#define LCD_COMMANED_SHIFT_RIGHT							0X05U
#define LCD_COMMANED_SHIFT_LEFT								0X07U
#define LCD_COMMANED_CLEAR_CURSOR_ON					0X0AU
#define LCD_COMMANED_CLEAR_CURSOR_OFF					0X0CU
#define LCD_COMMANED2LINE_4_BIT_MODE          0x28U




/*
 *brief  : this function used to initialize (GPIO &LCD) 
 * return : void 
 */  
void LCD_Initializaion(void);






/* 
 *brief  : this function used to send an character to LCD with the current location 
 * param. : Character the specific character to send to LCD 
 * return : void 
 */  
void LCD_Send_Character_CurrLoc(uint8_t character);






/*
 * brief  : this function used to send an character to LCD with the chosen location 
 * param. :  y  is specify the new Y axises
 * param. :  x  is specify the new X axises
 * param. : character the specific character to send to LCD 
 * return : void 
 */
void LCD_Send_Character_WithLoc(uint8_t y,uint8_t x,uint8_t character);





/*
 * brief  : this function used to send an string to LCD with the current location 
 * param. : string the specific character to send to LCD 
 * return : void 
 */
void LCD_Send_String_CurrLoc(uint8_t *string);





/*
 * brief  : this function used to send command to LCD  
 * param. : command the specific command to send to LCD chose one of @ LCD_COMMANED_ 
 * return : void 
 */
void LCD_Send_Command(uint8_t command);





/*
 * brief  : this function used to modify the current cursor location 
 * param. :  y  is specify the new Y axises 1-->16
 * param. :  x  is specify the new X axises 1-->16
 * return : void 
 */
void LCD_Goto_Location(uint8_t x , uint8_t y);






/*
 * brief  : this function used to send an string to LCD with the chosen location 
 * param. :  y  is specify y axises location start from 1-->16
 * param. :  x  is specify y axises location start from 1-->16
 * param. : StringOfCharacters pointer to string that you want to display
 * return : void 
 */
void LCD_Send_String_WithLoc(uint8_t loc_x_, uint8_t loc_y_, char *StringOfCharacters);




/*
 * brief  : this function used to send an 16 bit integer to LCD with the chosen location 
 * param. :  y  is specify y axises location start from 1-->16
 * param. :  x  is specify y axises location start from 1-->16
 * param. : IntegerToDisplay this is the integer value that you want to display
 * param. : NumberOfDigits number of digits of the integer number that you want to display
 * return : void 
 */
void LCD_Send_Integer_WithLoc(uint8_t loc_x_, uint8_t loc_y_, uint32_t IntegerToDisplay);

/*
 * brief  : this function used to send an floating point number to LCD with the chosen location 
 * param. :  y  is specify y axises location start from 1-->16
 * param. :  x  is specify y axises location start from 1-->16
 * param. : IntegerToDisplay this is the integer value that you want to display
 * param. : precision number of digits of the float section that you want to display 
 * return : void 
 */
void LCD_Send_Float_withloc(uint8_t x, uint8_t y ,  float FlaotToDisplay ,uint16_t precision);









/*
 * brief  : this function used to send an floating point number to LCD with the chosen location 
 * param. :  y  is specify y axises location start from 1-->16 
 * param. :  x  is specify y axises location start from 1-->16
 * param. : IntegerToDisplay this is the integer value that you want to display
 * param. : NumberOfDigits number of digits of the integer number that you want to display 
 * return : void 
 */
void LCD_Send_Float_Withloc(uint8_t y, uint8_t x ,  float number , uint16_t precision);



/*
 * brief  : this function used to send an 16 bit integer to LCD with the current location 
 * param. : IntegerToDisplay this is the integer value that you want to display
 * return : void 
 */
void LCD_Send_Integer_CurrLoc(uint64_t IntegerToDisplay);




/*
 * brief  : this function used to send an string to LCD with the current location 
 * param. : StringOfCharacters pointer to string that you want to display
 * return : void 
 */
void LCD_Send_String_With_CurrLoc(char *StringOfCharacters);




/* this function used to generate delay in ms */
void delayMs(int Ms);
/* this function used to generate delay in Us */
void delayUs(int Us);


#endif
