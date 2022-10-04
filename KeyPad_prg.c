/*
 *  File : KeyPad_prg.h
 *  DATE: þ1/9/2022
 *  Author: Shehab aldeen
 *  Version : V1
 *  Describtion : --------------
 */
#include<util/delay.h>
#include"../LIB/STD_TYPES.h"
#include"../LIB/Bit_math.h"
#include "LCD_Interface.h"
#include"KeyPad_interface.h"
#include"KeyPad_cfg.h"
#include"KeyPad_Private.h"

/*
 be care to write in main :
    while (1)
    {
	 num = KeyPad_U8GetNUM () ;
	 if ( !( num == 50 ||  num == '/' ||  num == '*' ||  num == '+' ||  num == '-' ||  num == '=')  )
	 {
		 LCD_VidPrintVar(num ) ;
	 }//end if
	 else if (num != 50){
	     LCD_VidSendChar(num);
	 }

   }//end while loop
 */

/*prg*/

#ifdef KEYPAD_4_4

void KeyPad_VidInit(void){

	/*to define first 4 pins as inputs for rows
	and second 4 pins as output for columns*/
	DIO_VidSetPortDirection( KEYPAD_PORT , 0xf0 ) ;

	/*to active Pull_up_resistor for 4 pins input for rows
	and output high on columns*/
	DIO_VidSetPortValue( KEYPAD_PORT , 0xff );
     }
#endif

#ifdef KEYPAD_3_3

void KeyPad_VidInit(void){

	/*to define first 3 pins as inputs for rows
	and second 3 pins as output for columns*/
	DIO_VidSetPortDirection( KEYPAD_PORT , 0x28 );

	/*to active Pull_up_resistor for 3 pins input for rows
	and output high on columns*/
	DIO_VidSetPortValue( KEYPAD_PORT , 0x3f );
	}
#endif


u8 KeyPad_U8Num(u8 Copy_num){
	switch (Copy_num){
	case 0 : return 1 ;
	case 1 : return 2 ;
	case 2 : return 3 ;
	case 3 : return '/' ;
	case 4 : return 4 ;
	case 5 : return 5 ;
	case 6 : return 6 ;
	case 7 : return '*' ;
	case 8 : return 7 ;
	case 9 : return 8 ;
	case 10 : return 9 ;
	case 11 : return '-' ;
	case 12 : return 50 ;
	case 13 : return 0 ;
	case 14 : return '=' ;
	case 15 : return '+' ;
	default : return Copy_num ;
	}
}


u8 KeyPad_U8GetNUM (void){
	u8 local_key = 50 ;
	for (u8 C=0 ; C<KEYPAD_NUM_COL ; C++){
		DIO_VidSetPinValue( KEYPAD_PORT , C+KEYPAD_NUM_COL , LOW ) ;
		for (u8 R=0 ; R<KEYPAD_NUM_ROW ; R++){
			u8 pressed = DIO_U8GetPinValue(KEYPAD_PORT,R);
			if (LOW == pressed )
			{
				local_key = (KEYPAD_NUM_ROW*R)+C ;
				while(LOW == pressed)
				{
				    pressed = DIO_U8GetPinValue(KEYPAD_PORT,R) ;
				}//end while loop
				_delay_ms(5);
			}//end if loop
		}//end 1st for loop
	DIO_VidSetPinValue( KEYPAD_PORT , C+KEYPAD_NUM_COL , HIGH );
	}//end 2nd for loop
     local_key = KeyPad_U8Num( local_key ) ;
	return local_key ;
}//end FUNC KeyPad_U8GetNUM
