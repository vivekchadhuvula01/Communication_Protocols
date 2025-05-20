/*
 * CAN_Master_Driver_Variables.h
 *
 *  Created on: May 20, 2025
 *      Author: Admin
 */

#ifndef SRC_CAN_MASTER_DRIVER_LIB_CAN_MASTER_DRIVER_VARIABLES_H_
#define SRC_CAN_MASTER_DRIVER_LIB_CAN_MASTER_DRIVER_VARIABLES_H_

#include "main.h"

#define CAN_RTR_DATA 0x00  // RTR = 0: Data frame (write)
#define CAN_RTR_REMOTE 0x01  // RTR = 1: Remote frame (read request)

#define CAN_Master_Communication_Success   1
#define CAN_Master_Communication_Error_Data  2
#define CAN_Master_Communication_Error_Reciever 3
#define CAN_Master_Communication_Error_ACK  4


extern const uint8_t crc_Table[256];


struct CAN_CTRL_Struct
{
	HAL_CAN_StateTypeDef  *hcanx;
	__IO uint32_t CAN_Busy_Flag_TimeOut_Cntr;
	__IO uint8_t  CAN_Busy_Flag;
	__IO uint32_t CAN_Recv_TimeOut_Cntr;
	__IO uint8_t CRC_Value;
	__IO uint8_t Message_ID;
	__IO uint16_t	Send_Index;
	__IO uint16_t	Send_Msg_Len;
	__IO uint8_t	Send_Enable;
	__IO uint8_t	Recv_Flag;
	__IO uint8_t	Recv_Enable;
	__IO uint8_t	Recv_Data_Byte;
	__IO uint16_t	Recv_Arr_Index;
	__IO uint32_t	Resend_Delay_Cntr;
	__IO uint8_t	Recv_Eror_Flag;


	__IO uint8_t Send_Arr[];
	__IO uint8_t Recive_Arr[];

};
extern struct CAN_CTRL_Struct CAN1_Master_Ctrl;


struct CAN_Msg_Struct
{
	__IO uint16_t Send_Array_Length;
	__IO uint16_t Recv_Array_Length;

};

extern const struct CAN_Msg_Struct CAN1_Msg;

#endif /* SRC_CAN_MASTER_DRIVER_LIB_CAN_MASTER_DRIVER_VARIABLES_H_ */
