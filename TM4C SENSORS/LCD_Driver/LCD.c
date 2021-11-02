
#include "LCD.h"


/* start position for x & y location as described in data sheet*/ 
static uint8_t column_position [2] = {0x80,0xc0};


/*
 * brief  : this function used to convert integer to string 
 * param. : num this is the integer value that you want to convert
 * param. : BUFF pointer to buffer to hold the converted numbers
 * return : void 
 */
static void int_to_str(uint32_t num , uint8_t* BUFF);
	


/*
 * brief  : this function used to set enable bit in LCD
 * return : void 
 */
static void LCD_Triger_Enable(void);



/*
 * brief  : this function used to send Data to LCD in 4 bit form 
 * param. : data the specific byte that you want to send to LCD 
 * return : void 
 */
static void LCD_Send_4BitData(uint8_t data)
{
	
		for(int i =3 ; i < 7 ;i++)		
		{	
			LcdBitSelect.LcdBits[i].Port->DATA   &= ~LcdBitSelect.LcdBits[i].Pin ;
			LcdBitSelect.LcdBits[i].Port->DATA   |= (((data)&(1<<(i+1)))>>(i+1))<<(31-__clz(LcdBitSelect.LcdBits[i].Pin));
		}
		LCD_Triger_Enable();
		int x =0 ;
		for(int i =3 ; i < 7 ;i++)		
		{	
			x = __clz(LcdBitSelect.LcdBits[i].Pin);
			LcdBitSelect.LcdBits[i].Port->DATA   &= ~LcdBitSelect.LcdBits[i].Pin ;
			LcdBitSelect.LcdBits[i].Port->DATA   |= (((data)&(1<<(i-3)))>>(i-3))<<(31-__clz(LcdBitSelect.LcdBits[i].Pin));
		}
		LCD_Triger_Enable();		
		

} /* END_FUN LCD_Send_4BitData()*/




/*
 * brief  : this function used to set enable bit in LCD
 * return : void 
 */
static void LCD_Triger_Enable(void)
{
	LcdBitSelect.LcdBits[LCD_BIT_E_PIN].Port->DATA  |=  LcdBitSelect.LcdBits[LCD_BIT_E_PIN].Pin;  /* remmeber to always connect LCD_RW to ground */
	delayUs(400);
	LcdBitSelect.LcdBits[LCD_BIT_E_PIN].Port->DATA  &=~ LcdBitSelect.LcdBits[LCD_BIT_E_PIN].Pin;  /* remmeber to always connect LCD_RW to ground */
	delayUs(400);
	
} /* END_FUN LCD_Triger_Enable()*/




/*
 *brief  : this function used to send an character to LCD with the current location 
 * param. : Character the specific character to send to LCD 
 * return : void 
 */  
void LCD_Send_Character_CurrLoc(uint8_t character)
{
	LcdBitSelect.LcdBits[LCD_BIT_RS_PIN].Port->DATA  |= LcdBitSelect.LcdBits[LCD_BIT_RS_PIN].Pin;  /* remmeber to always connect LCD_RW to ground */
	delayMs(1);
	LCD_Send_4BitData(character);
	
}/* ECD_FUN LCD_Send_Character_CurrLoc */





/*
 * brief  : this function used to send command to LCD  
 * param. : command the specific command to send to LCD chose one of @ LCD_COMMANED_ 
 * return : void 
 */
void LCD_Send_Command(uint8_t command)
{
	
	LcdBitSelect.LcdBits[LCD_BIT_RS_PIN].Port->DATA  &=~  LcdBitSelect.LcdBits[LCD_BIT_RS_PIN].Pin; /* remmeber to always connect LCD_RW to ground */
	LCD_Send_4BitData(command);
	
	
} /* END_FUN LCD_Send_Command()*/




/*
 *brief  : this function used to initialize (GPIO &LCD) 
 * return : void 
 */  
void LCD_Initializaion(void)
{
SYSCTL->RCGCGPIO |= 0x01;    /* enable GPIOA clock */
__NOP();__NOP();__NOP();    /* wait 3 cycles */

	for(int i = 0;i< 7 ;i++)
	{
		LcdBitSelect.LcdBits[i].Port->DEN |= LcdBitSelect.LcdBits[i].Pin ;
		LcdBitSelect.LcdBits[i].Port->DIR |= LcdBitSelect.LcdBits[i].Pin ;
	}
	
	delayMs(20);
	
	/* LCD Initialization command*/
	LCD_Send_Command(0x33U);  
	LCD_Send_Command(0x32U);
	LCD_Send_Command(LCD_COMMANED2LINE_4_BIT_MODE);
	LCD_Send_Command(LCD_COMMANED_CLEAR_CURSOR_OFF);
	LCD_Send_Command(LCD_COMMANED_CLEAR_LCD);
	
	
} /* END_FUN LCD_Initializaion()*/




/*
 * brief  : this function used to modify the current cursor location 
 * param. :  y  is specify the new Y axises( 1-->16)
 * param. :  x  is specify the new X axises( 1-->16)
 * return : void 
 */
void LCD_Goto_Location(uint8_t y,uint8_t x)
{
	if((x<1) || (y<1) ||(x>16)||(y<16))  /* check if the chosen cursor is wrong */
	LCD_Send_Command(0x80);
	else
	LCD_Send_Command(column_position[y-1]+(x-1));
	
}/* END_FUN LCD_Goto_Location()*/






/*
 * brief  : this function used to send an string to LCD with the chosen location 
 * param. :  y  is specify y axises location start from 1-->16
 * param. :  x  is specify x axises location start from 1-->16
 * param. : StringOfCharacters pointer to string that you want to display
 * return : void 
 */
void LCD_Send_String_WithLoc(uint8_t y, uint8_t x, char *StringOfCharacters)
{

	
LCD_Goto_Location(y,x);
while((*StringOfCharacters) != NULL)
	{
		LCD_Send_Character_CurrLoc(*StringOfCharacters);
		StringOfCharacters ++;
	}
	
} /* END_FUN Send_A_String_WithLoc()*/




/*
 * brief  : this function used to send an string to LCD with the current location 
 * param. : StringOfCharacters pointer to string that you want to display
 * return : void 
 */
void LCD_Send_String_With_CurrLoc(char *StringOfCharacters)
{

	while((*StringOfCharacters) != NULL)
	{
		LCD_Send_Character_CurrLoc(*StringOfCharacters);
		StringOfCharacters ++;
	}
	
}/* END_FUN LCD_Send_String_With_CurrLoc */




/*
 * brief  : this function used to send an 64 bit integer to LCD with the chosen location 
 * param. :  y  is specify y axises location start from 1-->16
 * param. :  x  is specify x axises location start from 1-->16
 * param. : IntegerToDisplay this is the integer value that you want to display
 * return : void 
 */
void LCD_Send_Integer_WithLoc(uint8_t y, uint8_t x, uint32_t IntegerToDisplay)
{
	
	
		uint8_t arr[20];
		int_to_str(IntegerToDisplay,arr);
		LCD_Send_String_WithLoc(y,x,(char *)arr);
	
	
}/* END_FUN LCD_Send_Integer_WithLoc() */






/*
 * brief  : this function used to send an 16 bit integer to LCD with the current location 
 * param. : IntegerToDisplay this is the integer value that you want to display
 * return : void 
 */
void LCD_Send_Integer_CurrLoc(uint64_t IntegerToDisplay)
{
		uint8_t arr[20];
		int_to_str(IntegerToDisplay,arr);
		LCD_Send_String_With_CurrLoc((char*)arr);
	
	
}/* END_FUN LCD_Send_Integer_CurrLoc()*/







/*
 * brief  : this function used to convert integer to string 
 * param. : num this is the integer value that you want to convert
 * param. : BUFF pointer to buffer to hold the converted numbers
 * return : void 
 */
static void int_to_str(uint32_t num , uint8_t* BUFF)
{
		uint32_t num1=num;
	  uint16_t  len=0,rem=0;
		while(num1 != 0) /* measure the length of the given number */
		{
			len++;
			num1 = num1/10;
			
		}
		
		*(BUFF+len)= NULL ;  /* put null this important when you deal with strings most c string stanerd library make null as terminate condition */
		while(num != 0)
		{
			rem = num%10;
			num = num/10;
			*(BUFF+len-1)=rem + '0' ; /* convet hte measured number as an ascii code */ 
			len--;
		}
		
		
}/* END_FUN int_to_str */





/*
 * brief  : this function used to send an floating point number to LCD with the chosen location 
 * param. :  y  is specify y axises location start from 1-->16
 * param. :  x  is specify y axises location start from 1-->16
 * param. : FlaotToDisplay this is the integer value that you want to display
 * param. : precision number of digits of the float section that you want to display 
 * return : void 
 */
void LCD_Send_Float_Withloc(uint8_t y, uint8_t x ,  float FlaotToDisplay , uint16_t precision)
{
		uint16_t intValue =0;
	float diffValue=0;
	double after=10.0;
	uint16_t decimalValue ;
	LCD_Goto_Location(y,x);
	


	if (precision == 1 )		after = after *1;  /* chose the precision */

	else if (precision==2)	after = 100.0;

	else if (precision==3)	after = 1000.0;

	else if (precision==4)	after = 10000.0;

	else if (precision==5)	after = 100000.0;

	else if (precision==6)	after = 1000000.0;

	intValue = (uint16_t)FlaotToDisplay;                    /* calculate the int value */
	diffValue = FlaotToDisplay - (float)intValue;              
	decimalValue = (uint16_t)((double)diffValue * after);			  /* calculate the float value */
	
	
	LCD_Send_Integer_CurrLoc(intValue);
	LCD_Send_Character_CurrLoc('.');
	LCD_Send_Integer_CurrLoc(decimalValue);
	
} /* END_FUN LCD_Send_Float_Withloc()*/



/* delay Ms milliseconds (16 MHz CPU clock) */
void delayMs(int Ms)
{
int i, j;
for(i = 0 ; i < Ms; i++) /* wait for Ms delay */
for(j = 0; j < (16000000/4000); j++)/*each for loop 4 instructions means take 4 cycle per loop so 1ms will equal 16000 cycle or 4000 loop */
{} /* do nothing for 1 ms */
}
/* delay Us microseconds (16 MHz CPU clock) */
void delayUs(int Us)
{
int i, j;
for(i = 0 ; i < Us; i++)/* wait for Us delay */
for(j = 0; j < 4; j++)/* each loop require 4 cycles so at 16mhz 4 loops will generate 1Us delay */

{} /* do nothing for 1 us */
}
