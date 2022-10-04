/*
 *  File : LCD_Interface.h
 *  DATE: 11/9/2022
 *  Author: Shehab aldeen
 *  Version : V1
 *  Describtion :LCD_DRIVER
 */
#include"../LIB/STD_TYPES.h"
#include"../LIB/BIT_MATH.h"
#include"LCD_private.h"

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_
 
void LCD_VidInit();                                                  //initialize LCD
void LCD_VidSendCommend(u8 Copy_U8Commend);                          //to send commends to LCD
void LCD_VidSendChar(u8 Copy_U8Char);                                //to write characters
void LCD_VidSendString(u8 Copy_U8String[] );                         //to send statements
void LCD_VidPrintVar(u32 Copy_U8Var);                                //to print numbers variables
u32 LCD_U32Pow(u8 Copy_U8Base , u8 Copy_U8Bow );                     //to help us in print numbers
void LCD_VidPosCur(u8 Copy_U8Row , u8 Copy_U8Col ) ;                 //to shift cursor
void LCD_VidClear ();                                                //to clear LCD
void Lcd_vidDisplay_Custom_Character_Array(char Lcd[16][80]);        //to write on all LCD
void Lcd_vidSaveCustomChar(u8 Location , u8 *Char);                  //to write in CGRAM specific shapes

#endif
