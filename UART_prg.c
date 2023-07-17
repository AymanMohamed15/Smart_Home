/*
 * UART_prg.c
 *
 *  Created on: Oct 22, 2022
 *      Author: kayed
 */

/******************************************************/
/******************************************************/
/*****************Author: Baraa Adel*******************/
/********************File: UART_prg.c  ****************/
/******************Date: 22th Oct 2022******************/
/*********************Version: V1.2********************/
/***************Desc:main source file******************/
/******************************************************/
/******************************************************/


#include <avr/delay.h>
#include"../LIB/STD_TYPES.h"
#include"../LIB/BIT_MATH.h"
#include "DIO_interface.h"
#include "UART_private.h"



void UART_Vidinit(){

	u8 UCSRC_REG_help=0b10000000;
		DIO_VidSetPinDirection(3,0,0);//D0 input
		DIO_VidSetPinDirection(3,1,1);//D1 output
		
	SET_BIT(UCSRB_REG,4); //Enable Receiver
	SET_BIT(UCSRB_REG,3); //Enable Transmitter

	/*UCSRC_REG*/
	//SET_BIT(UCSRC_REG_help,7); //URSEL Register Select
	/*USART Mode Select-> Asynchronous*/
	CLR_BIT(UCSRC_REG_help,6); //UMSEL (Asynchronous)
	/*Parity Mode Disabled*/
	CLR_BIT(UCSRC_REG_help,5); //UPM1
	CLR_BIT(UCSRC_REG_help,4); //UPM0
	/*Stop Bit Select*/
	CLR_BIT(UCSRC_REG_help,3);  //USBS 1-bit
	/* Character Size 8-bits */
	SET_BIT(UCSRC_REG_help,2);  //UCSZ1
	SET_BIT(UCSRC_REG_help,1);  //UCSZ0
	/*Clock Polarity For Sync*/
	CLR_BIT(UCSRC_REG_help,0);

	UCSRC_REG=UCSRC_REG_help;

	UBRRH_REG=0;
	UBRRL_REG=51;

}

u8 UART_U8GetChar(){
	  // Wait until Reception Complete
	  while(!GET_BIT(UCSRA_REG,7)); //RXC
	  return UDR_REG;
}


void UART_U8SendChar(u8 data){
	  // Wait until transmission Register Empty
	  while(!GET_BIT(UCSRA_REG,5)); //UDRE
	  UDR_REG = data;
}

void UART_U8StringWriter(u8 *str){
		u8 i=0;
		while(str[i])
		{
		UART_U8SendChar(str[i]);
		i++;
		}
}

