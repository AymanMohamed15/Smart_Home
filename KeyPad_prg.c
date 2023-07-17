/*
 *  File : KeyPad_prg.h
 *  DATE: þ9/9/2022
 *  Author: Shehab aldeen
 *  Version : V1
 *  Describtion : --------------
 */
#include<util/delay.h>
#include"../LIB/STD_TYPES.h"
#include"../LIB/Bit_math.h"
#include "DIO_interface.h"
#include "ADC_interface.h"
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



#ifdef KEYPAD_4_4
u8 KeyPad_U8Num(u8 Copy_num){
	switch (Copy_num){
	case 0 : return 7 ;
	case 1 : return 8 ;
	case 2 : return 9 ;
	case 3 : return '/' ;
	case 4 : return 4 ;
	case 5 : return 5 ;
	case 6 : return 6 ;
	case 7 : return '*' ;
	case 8 : return 1 ;
	case 9 : return 2 ;
	case 10 : return 3 ;
	case 11 : return '-' ;
	case 12 : return 50 ;
	case 13 : return 0 ;
	case 14 : return '=' ;
	case 15 : return '+' ;
	default : return Copy_num ;
	}
}
#endif


u8 KeyPad_U8GetNUM (void){
	u8 local_key=0;
    switch (ADC_VidReadChannel(0)){
    case 4002 : local_key=7; break ;
    case 3504 : local_key=4; break ;
    case 1500 : local_key=1; break ;
    case 1603 : local_key=8; break ;
    case 801  : local_key=9; break ;
    case 1402 : local_key=5; break ;
    case 698  : local_key=6; break ;
    case 601  : local_key=2; break ;
    case 298  : local_key=3; break ;
    }
	return local_key ;
}//end FUNC KeyPad_U8GetNUM
