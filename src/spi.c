/*
 * spi.c
 *
 *  Created on: 28 oct 2017
 *  Author: Rekawekp
 */

#include "stm32f0xx.h"
#include "spi.h"

//------------------------------- SPI_Write ------------------------------
void SPI_Write( uint8_t val_write )
{
	SPI1->DR;
	*( volatile uint8_t * ) ( &(SPI1->DR) ) = val_write;
	while( !(SPI1->SR & SPI_SR_TXE) );
}

//------------------------------- SPI_Read ------------------------------
uint8_t SPI_Read( void )
{
	while( !(SPI1->SR & SPI_SR_RXNE) )
	{
		return 0x00; // In this while is a problem
	}

	return (uint8_t) SPI1->DR;
}
