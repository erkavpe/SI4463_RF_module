/*
 * si4463.c
 *
 *  Created on: 28 oct 2017
 *  Author: Rekawekp
 */

#include "stm32f0xx.h"
#include "si4463.h"

#include "radio_config_Si4463.h"
#include "si446x_patch.h"
#include "spi.h"

//------------------------------- SI4463_Read_Buffor ------------------------------
void SI4463_Read_Buffor( uint8_t *rd_buff, uint8_t len )
{
	uint8_t cts_val = 0;

	while( cts_val != 0xFF )
	{
		GPIOA->BRR = GPIO_BRR_BR_4;

		SPI_Write( 0x44 );
		SPI_Write( 0x00 );

		cts_val = SPI_Read( );

		if( cts_val != 0xFF )
			GPIOA->BSRR	= GPIO_BSRR_BS_4;
	}

	for (uint8_t i = 0 ; i < len ; i++)
	{
		SPI_Write( 0x00 );
		*( rd_buff + i ) = SPI_Read( );
	}
	GPIOA->BSRR	= GPIO_BSRR_BS_4;
}

//------------------------------- SI4463_Delay ------------------------------
void SI4463_Delay( void )
{
	for( volatile uint32_t i = 0; i <= 0x1F40; i++); // will be change to a TIMER
}

//------------------------------- SI4463_Wait_CTS ------------------------------
void SI4463_Wait_CTS( void )
{
	uint8_t cts_val = 0;

	while( cts_val != 0xFF )
	{
		GPIOA->BRR = GPIO_BRR_BR_4;

		SPI_Write( 0x44 );
		SPI_Write( 0x00 );

		cts_val = SPI_Read( );

		GPIOA->BSRR	= GPIO_BSRR_BS_4;
	}
	SI4463_Delay( );
}

//------------------------------- SI4463_Get_Property ------------------------------
void SI4463_Get_Property( uint8_t *get_buff, uint8_t len )
{
	GPIOA->BRR = GPIO_BRR_BR_4;
	for (uint8_t i = 0 ; i < len ; i++)
	{
		SPI_Write( *(get_buff+i) );
	}
	GPIOA->BSRR	= GPIO_BSRR_BS_4;

//	SI4463_Wait_CTS( );
}

//------------------------------- SI4463_Set_Property ------------------------------
void SI4463_Set_Property( uint8_t *set_buff, uint8_t len )
{
	GPIOA->BRR = GPIO_BRR_BR_4;
	for (uint8_t i = 0 ; i < len ; i++)
	{
		SPI_Write( *(set_buff+i) );
	}
	GPIOA->BSRR	= GPIO_BSRR_BS_4;

	SI4463_Wait_CTS( );
}

//------------------------------- SI4463_Get_Interrupt ------------------------------
void SI4463_Get_Interrupt( uint8_t *inter_buff )
{
	uint8_t clear_buff[] = { 0x20, 0x00, 0x00, 0x00 };
	SI4463_Get_Property( clear_buff, 4 );
	SI4463_Read_Buffor( inter_buff, 9 );
}

//------------------------------- SI4463_TX_Start ------------------------------
void SI4463_TX_Start( uint8_t channel_tx, uint8_t size )
{
	uint8_t tx_buff[] = { 0x31, channel_tx, 0x00, 0x00, size };
	SI4463_Set_Property( tx_buff, 5 );
}

//------------------------------- SI4463_RX_Start ------------------------------
void SI4463_RX_Start( uint8_t channel_rx, uint8_t size )
{
	uint8_t rx_buff[] = { 0x32, channel_rx , 0x00, 0x00, size, 0x00, 0x00, 0x00 };
	SI4463_Set_Property( rx_buff, 7 );
}

//------------------------------- SI4463_TX_FIFO ------------------------------
void SI4463_TX_FIFO ( uint8_t *buff_tx, uint8_t len )
{
	uint8_t buff[len+1];

	buff[0] = 0x66;

	for(uint8_t i = 0 ; i < len ; i++)
	{
		buff[i+1] = *(buff_tx + i);
	}

	GPIOA->BRR = GPIO_BRR_BR_4;
	for (uint8_t i = 0 ; i < sizeof(buff)/sizeof(uint8_t) ; i++)
	{
		SPI_Write( buff[i] );
	}
	GPIOA->BSRR	= GPIO_BSRR_BS_4;
}

//------------------------------- SI4463_RX_FIFO ------------------------------
void SI4463_RX_FIFO ( uint8_t *buff_rx, uint8_t len )
{
	GPIOA->BRR = GPIO_BRR_BR_4;

	SPI_Write( 0x77 );

	for (uint8_t i = 0 ; i < len ; i++)
	{
		SPI_Write( 0x00 );

		*(buff_rx+i) = SPI_Read( );
	}
	GPIOA->BSRR	= GPIO_BSRR_BS_4;
}

//------------------------------- SI4463_Clear_TX_FIFO ------------------------------
void SI4463_Clear_TX_FIFO( void )
{
	uint8_t buff_1[] = { 0x15, 0x01 };
	SI4463_Set_Property( buff_1, 2 );
}

//------------------------------- SI4463_Clear_RX_FIFO ------------------------------
void SI4463_Clear_RX_FIFO( void )
{
	uint8_t buff_2[] = { 0x15, 0x02 };
	SI4463_Set_Property( buff_2, 2 );
}

//------------------------------- SI4463_Device_Info ------------------------------
uint8_t SI4463_Device_Info( void )
{
	uint8_t patch[8];
	uint8_t buff = 0x01;
	SI4463_Get_Property( &buff, 1 );
	SI4463_Read_Buffor( patch, 8 );

	return patch[7];
}

//------------------------------- SI4463_Send_Data ------------------------------
void SI4463_Send_Data( uint8_t *send_dt, uint8_t size, uint8_t channel )
{
	GPIOA->BSRR	= GPIO_BSRR_BS_1;									// Red diode SENDING -> ON
	uint8_t get_inter[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	SI4463_Clear_TX_FIFO( );
	while ( !(get_inter[2] & 0x20) )
		{
			SI4463_TX_FIFO ( send_dt, size );
			SI4463_TX_Start( channel, size );
			SI4463_Get_Interrupt( get_inter );
//			SI4463_RX_Start( 0, 1 );   // In future to delay
		}

	GPIOA->BRR = GPIO_BRR_BR_1;										// Red diode SENDING -> OFF
}

//------------------------------- SI4463_Read_Data ------------------------------
void SI4463_Read_Data( uint8_t *read_dt, uint8_t size, uint8_t channel )
{
	GPIOA->BSRR	= GPIO_BSRR_BS_0;									// Green diode RECIEVING -> ON
	uint8_t get_inter[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	SI4463_Get_Interrupt( get_inter );
	if( ( get_inter[2] & 0x10) )
		{
			SI4463_RX_FIFO ( read_dt, size );
		}

	SI4463_Clear_RX_FIFO();
//	SI4463_RX_Start( 0, 1 ); // In future to delay

	GPIOA->BRR = GPIO_BRR_BR_0;										// Green diode RECIEVING -> OFF

}

//------------------------------- SI4463_Init ------------------------------
void SI4463_Init( )
{
	uint8_t Radio_Conf_Array[] = RADIO_CONFIGURATION_DATA_ARRAY;
	uint16_t place = 0;

	while( *(Radio_Conf_Array + place) != 0x00 )
	{
		SI4463_Set_Property( (Radio_Conf_Array + place + 1), *(Radio_Conf_Array + place) );

		place += *(Radio_Conf_Array + place) + 1;
	}
//	SI4463_RX_Start( 0, 1 );   // In future to delay
}

//------------------------------- SI4463_Patch ------------------------------
void SI4463_Patch( void )
{
	uint8_t Radio_Patch_Array[][8] = { SI446X_PATCH_CMDS };
	uint8_t buff_patch[8];
	uint16_t size = sizeof( Radio_Patch_Array ) / 8*sizeof( uint8_t );

	for (uint16_t row = 0 ; row < size; row++)
	{
		for( uint8_t col = 0 ; col < 8 ; col++)
		{
			buff_patch[col] = Radio_Patch_Array[row][col];
		}
		SI4463_Set_Property( buff_patch, 8 );
	}
}

