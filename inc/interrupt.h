/*
 * interrupt.h
 *
 *  Created on: 29 oct 2017
 *  Author: Rekawekp
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

void USART1_IRQHandler( void ) __attribute__ (( interrupt ));
void EXTI2_3_IRQHandler( void ) __attribute__ (( interrupt ));
void TIM3_IRQHandler( void ) __attribute__ (( interrupt ));

#endif /* INTERRUPT_H_ */
