/*
 *  file : main.c
 *  Date : 1/10/2022 ~ 3/10/2022
 *  Created on: shehab aldeen
 *  describe : snake application
 */
#include"../LIB/STD_TYPES.h"
#include"../LIB/BIT_MATH.h"
#include "DIO_interface.h"
#include "LCD_Interface.h"
#include "KeyPad_Interface.h"
#include <avr/delay.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_BYTES 16                //to express about rows on LCD
#define MAX_COL 80                  //to express about columns on LCD
#define PORT_G_L 3                  //to define port that used to make direction right left
#define PIN_RIGHT 0                 //to define pin used to make direction
#define PIN_LEFT 1                  //to define pin used to make direction
#define HIGH 1                      // high voltage
#define LOW 0                       //low voltage

u8 right = 1 ;                      //to move continues in right direction while it's true
u8 left = 0 ;                       //to move continues in left direction while it's true
u8 up = 0 ;                         //to move continues in up direction while it's true
u8 down = 0 ;                       //to move continues in down direction while it's true

void direction_left (void);                            //to edit direction in left
void direction_Right (void);                           //to edit direction in right
void direction_up (void);                              //to edit direction in up
void direction_down (void);                            //to edit direction in down
u8 check_on_moving (u8 Copy_U8col );                   // to check on the direction of moving is intersected or not

u8 Char[8];                                            //to define the ones on one digit
s8 Snake_Row[MAX_BYTES-1] = {7,7,7} ;                  //to store the values of moving snake in rows
s8 Snake_Column[MAX_COL-1] = {0,1,2};                  //to store the values of moving snake in columns

void main (void){
	LCD_VidInit();                                //to initialize LCD in beginning
	KeyPad_VidInit();                             //to initialize KEYPAD in beginning
	u8 Lcd[MAX_BYTES][MAX_COL] =  {0} ;           //to write on LCD

	u8 apple = 0 ;                                //food correspending to snake
	u8 Status = 0 ;                               //to express about status of food on LCD
	u8 button = 0 ;                               //to store num that Get from KEYPAD
	s8 last_index = 2 ;                           //last index in array
	s8 first_index = 0 ;                          //first index in array
    u8 flag_intersection = 0 ;                    //to check if it intersect it's self or not

	/* to get random position of apple on LCD*/
	srand(apple);
	apple++;
	u8 Dot_Row = rand() % 16;
	u8 Dot_Column = rand() % 75;
   /******************************************/

	while(1)
	{
		//to clear the following snake on LCD after moving
		_delay_ms(100);
		LCD_VidClear();

		/*to continue moving in LCD even if reach to the borders*/
		if(Snake_Row[last_index] > 15 ) {
			Snake_Row[last_index] = 0 ;
		}
		else if(Snake_Row[last_index] < 0 ){
			Snake_Row[last_index] = 15 ;
		}
		else if(Snake_Column[last_index] > 79 ){
			Snake_Column[last_index] = 0 ;
		}
		else if(Snake_Column[last_index] < 0){
			Snake_Column[last_index] = 79 ;
		}
        /**********************************************************/

		//to store snake in matrix
		for (u8 i=first_index ; i<=last_index ; i++){
		    Lcd[ Snake_Row[i] ][ Snake_Column[i] ] = 1 ;
		}

		/*to display next apple in other position in LCD if the apple on any parts of snake*/
		while(Status == 0)
		{
			u8 FlagNotOnSnake = 0 ;
			srand(apple);
			apple++;
			Dot_Row = rand() % 16;
			Dot_Column = rand() % 75;

			for (u8 i = 0 ; i<= last_index ; i++){
				if ( Snake_Column[Dot_Row] != Snake_Column[i] && Snake_Row[Dot_Row] != Snake_Row[i] ){
					FlagNotOnSnake = 1 ;
					break ;
				}//end if
			}//end for

			if (FlagNotOnSnake == 1 ){
				break ;
			}//end if

		}//end while
		/**************************************************************************************/

		//to store the apple in matrix
		Status = 1;
		Lcd[Dot_Row][Dot_Column] = 1;

		//Display motion
		Lcd_vidDisplay_Custom_Character_Array(Lcd);

		//to check if Snake eats apple
		if(((Dot_Row == Snake_Row[last_index] && Dot_Column == Snake_Column[last_index])) && Status == 1)
		{
			srand(apple);
			apple++;
			Dot_Row = rand() % 16;
			Dot_Column = rand() % 75;

			last_index++ ;
			Snake_Row[last_index]=Snake_Row[last_index-1] ;
			Snake_Column[last_index]=Snake_Column[last_index-1] ;

			Status = 0;
		}//end if

		//to shift snake
		Lcd[Snake_Row[first_index] ][Snake_Column[first_index] ] = 0 ;
		for (u8 i = first_index ; i < last_index ; i++){
			Snake_Column[i] = Snake_Column[i+1] ;
			Snake_Row[i] = Snake_Row[i+1] ;
		}//end for loop

		/*to check the input number*/
		button = KeyPad_U8GetNUM() ;
		if (button == 4){
			direction_left();
		}
		else if ( button == 2 ){
			direction_up();
		}
		else if (button == 6){
			direction_Right();
		}
		else if (button== 8){
			direction_down();
		}
		/**************************/

		/*to continue moving in specific direction*/
		if (right) {
			Snake_Column[last_index]++;
		}
		else if (left){
			Snake_Column[last_index]--;
		}
		else if (up){
			Snake_Row[last_index]--;
		}
		else if (down){
			Snake_Row[last_index]++;
		}
		/*******************************************/

		/***** to display GAME OVER with intersected snake **********/
	    flag_intersection = check_on_moving(last_index) ;
	    if (flag_intersection){
	    	LCD_VidPosCur(0,0);
	    	LCD_VidSendString(" GAME OVER ") ;
	    	LCD_VidPosCur(1,0);
	    	LCD_VidSendString(" GAME OVER ") ;
	    	_delay_ms(2000);
	    }
	    /*************************************************************/

	}//end while (1)
}//end main


void direction_left (void){
     right = 0 ;                       //to edit direction to move left
     left = 1 ;                        //to edit direction to move left
     up = 0 ;                          //to edit direction to move left
     down = 0 ;                        //to edit direction to move left
}

void direction_Right (void){
    right = 1 ;                       //to edit direction to move right
    left = 0 ;                        //to edit direction to move right
    up = 0 ;                          //to edit direction to move right
    down = 0 ;                        //to edit direction to move right
}

void direction_up (void){
     right = 0 ;                       //to edit direction to move up
     left = 0 ;                        //to edit direction to move up
     up = 1 ;                          //to edit direction to move up
     down = 0 ;                        //to edit direction to move up
}


void direction_down (void){
    right = 0 ;                       //to edit direction to move down
    left = 0 ;                        //to edit direction to move down
    up = 0 ;                          //to edit direction to move down
    down = 1 ;                        //to edit direction to move down
}

u8 check_on_moving (u8 Copy_U8col ){
	/*sequential search to check if the snake intersected it's self or not*/
	for (u8 i = 0 ; i< Copy_U8col ; i++){
		if ( Snake_Column[Copy_U8col] == Snake_Column[i] && Snake_Row[Copy_U8col] == Snake_Row[i] ){
			return 1 ;
		}//end if
	}//end for loop
	/*********************************************************************/

	//if no iontersection
	return 0 ;
}//end FUNC
