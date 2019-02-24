/*
 * usart.h
 *
 *  Created on: 29 oct 2017
 *  Author: Rekawekp
 */


#ifndef USART_H_
#define USART_H_

uint8_t USART1_Read_Byte( void );
void USART1_Write_Byte( uint8_t uart_val );
void USART1_Write_Buffor( uint8_t *uart_val, uint8_t size );

#endif /* USART_H_ */
