/*
 * interrupt.c
 *
 *  Created on: 28 oct 2017
 *  Author: Rekawekp
 */

#include "stm32f0xx.h"
#include "interrupt.h"

#include "usart.h"
#include "si4463.h"

uint8_t buffor_rx[9];
uint8_t rx_urt;
uint8_t tx_urt[] = { 'S', 'E', 'N', 'D', '\n', '\r' };

//------------------------------- USART1_IRQHandler ------------------------------
void USART1_IRQHandler( void )
{
	NVIC_ClearPendingIRQ( USART1_IRQn );
	rx_urt = USART1_Read_Byte( );

	SI4463_Send_Data( &rx_urt, 1, 0 );

	USART1_Write_Buffor( tx_urt, 6 );
	SI4463_RX_Start( 0, 1 );
}
//------------------------------- EXTI2_3_IRQHandler ------------------------------
void EXTI2_3_IRQHandler( void )
{
	NVIC_ClearPendingIRQ( EXTI2_3_IRQn );

	SI4463_Read_Data( buffor_rx, 1, 0 );
//	SI4463_Delay( );

	USART1_Write_Buffor( buffor_rx, 1 );
	SI4463_RX_Start( 0, 1 );

	EXTI->PR = EXTI_PR_PR3;
}

//------------------------------- TIM3_IRQHandler ------------------------------
void TIM3_IRQHandler( void )
{
	NVIC_ClearPendingIRQ( TIM3_IRQn );

	TIM3->CNT = 0;
	TIM3->SR = 0;

}
