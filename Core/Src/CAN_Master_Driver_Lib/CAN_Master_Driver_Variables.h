/*
 * CAN_Master_Driver_Variables.h
 *
 *  Created on: May 20, 2025
 *      Author: CH.Vivek
 */

#ifndef SRC_CAN_MASTER_DRIVER_LIB_CAN_MASTER_DRIVER_VARIABLES_H_
#define SRC_CAN_MASTER_DRIVER_LIB_CAN_MASTER_DRIVER_VARIABLES_H_

#include "main.h"

#define CAN_RTR_DATA 0x00  // RTR = 0: Data frame (write)
#define CAN_RTR_REMOTE 0x01  // RTR = 1: Remote frame (read request)

#define CAN_Node1  0x101
#define CAN_Node2  0x102
#define CAN_Node3  0x103
#define CAN_Node4  0x104
#define CAN_Node5  0x105

#define CAN_Master_Communication_Success   0      // 0 - not established communication, 1 - established communication



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
	__IO uint8_t Send_Flag;
	__IO uint8_t	Recv_Flag;
	__IO uint8_t	Recv_Enable;
	__IO uint8_t	Recv_Data_Byte;
	__IO uint16_t	Recv_Arr_Index;
	__IO uint32_t	Resend_Delay_Cntr;
	__IO uint8_t	Recv_Error_Flag;
	__IO uint8_t  Send_Error_Flag;
	__IO uint8_t Recv_Msg_len;

	__IO uint8_t Set_Filter;

	__IO uint8_t Send_Arr[];
	__IO uint8_t Recive_Arr[];

	__IO uint8_t Node1_Active;
	__IO uint8_t Node2_Active;
	__IO uint8_t Node3_Active;
	__IO uint8_t Node4_Active;
	__IO uint8_t Node5_Active;

};
extern struct CAN_CTRL_Struct CAN1_Master_Ctrl;


extern struct Recv_Struct
{
	uint16_t id;
	uint8_t data[8];
	uint8_t dlc;
} CAN_Recv_Message;


//extern struct CAN_Filter_Struct
//{
//	CAN_FilterTypeDef *filterConfig;
//	__IO uint8_t FilterBank;
//	__IO uint8_t FilterMode;
//
//
//} CAN1_Filter_struct;


struct CAN_Msg_Struct
{
	__IO uint16_t Send_Array_Length;
	__IO uint16_t Recv_Array_Length;

};

extern const struct CAN_Msg_Struct CAN1_Msg;

#endif /* SRC_CAN_MASTER_DRIVER_LIB_CAN_MASTER_DRIVER_VARIABLES_H_ */
