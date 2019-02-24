/*
 * usart.c
 *
 *  Created on: 28 oct 2017
 *  Author: Rekawekp
 */

#include "stm32f0xx.h"
#include "usart.h"

//------------------------------- USART1_Read_Byte ------------------------------
uint8_t USART1_Read_Byte( void )
{
	while(!(USART1->ISR & USART_ISR_RXNE));

	if(USART1->ISR & USART_ISR_ORE)
	{
		USART1->ICR = USART_ICR_ORECF;
	}
	return (uint8_t) USART1->RDR;
}

//------------------------------- USART1_Write_Byte ------------------------------
void USART1_Write_Byte( uint8_t uart_val )
{
	while(!(USART1->ISR & USART_ISR_TXE));
	USART1->TDR = uart_val;
}

//------------------------------- USART1_Write_Buffor ------------------------------
void USART1_Write_Buffor( uint8_t *uart_val, uint8_t size )
{
	for ( uint8_t i = 0; i < size ; i++ )
	{
		while(!(USART1->ISR & USART_ISR_TXE));
		USART1->TDR = *( uart_val+i );
	}
}
