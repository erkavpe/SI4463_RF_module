/*
 * si4463.h
 *
 *  Created on: 29 oct 2017
 *  Author: Rekawekp
 */


#ifndef SI4463_H_
#define SI4463_H_

void SI4463_TX_FIFO ( uint8_t *buff_tx, uint8_t len );
void SI4463_RX_FIFO ( uint8_t *buff_rx, uint8_t len );

void SI4463_RX_Start( uint8_t channel_rx, uint8_t size );
void SI4463_TX_Start( uint8_t channel_tx, uint8_t size );

void SI4463_Read_Buffor( uint8_t *rd_buff, uint8_t len );
void SI4463_Init( void );

void SI4463_Set_Property( uint8_t *set_buff, uint8_t len );
void SI4463_Get_Property( uint8_t *get_buff, uint8_t len );

void SI4463_Wait_CTS( void );
void SI4463_Get_Interrupt( uint8_t *inter_buff );

void SI4463_Delay( void );

void SI4463_Clear_TX_FIFO( void );
void SI4463_Clear_RX_FIFO( void );

void SI4463_Send_Data( uint8_t *send_dt, uint8_t size, uint8_t channel );
void SI4463_Read_Data( uint8_t *read_dt, uint8_t size, uint8_t channel );

void SI4463_Patch( void );

uint8_t SI4463_Device_Info( void );

#endif /* SI4463_H_ */
