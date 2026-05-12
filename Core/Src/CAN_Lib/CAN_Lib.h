/*
 * CAN_Lib.h
 *
 *  Created on: Apr 18, 2026
 *      Author: Vivek
 */

#ifndef SRC_CAN_LIB_CAN_LIB_H_
#define SRC_CAN_LIB_CAN_LIB_H_

#include "main.h"
#include "BASE64_FUN.h"
#include "BASE64_VAR.h"

#define MAX_LENGTH BASE64_Arr_Len

extern CAN_HandleTypeDef hcan1;

typedef struct{

	volatile uint16_t Send_Array_Length;
	volatile uint16_t Recv_Array_Length;
	volatile void (*Callback_Fnc)();

}CAN_Msg_Struct;

extern const CAN_Msg_Struct CAN_Msg_List[20];

typedef struct{
	CAN_HandleTypeDef CANx;
	volatile uint8_t Rx_arr[MAX_LENGTH];
	volatile uint8_t Tx_arr[MAX_LENGTH];

	volatile uint8_t B64_Rx_arr[MAX_LENGTH];
	volatile uint8_t B64_Tx_arr[MAX_LENGTH];


	volatile uint8_t Rx_Recieved;
	volatile uint8_t RDB[8];    			//Recieved Data BUFFER
	volatile uint8_t TDB[8];    			//Transmit Data BUFFER
	volatile uint8_t CAN_Busy_Flag;			// CAN Busy flag while sending and recieving data from CAN Bus
	volatile uint8_t CAN_Msg_List_Length;   // CAN msg List length
	volatile uint8_t Calculated_CRC;        // used to calculate crc of incoming data
	volatile uint8_t CAN_Slave_Id;
	volatile uint8_t start_bit;
	volatile uint8_t end_bit;

	volatile uint16_t Rx_Index;
	volatile uint16_t Index;
	volatile uint16_t Tx_Length;
	volatile uint16_t Tx_Index;

	volatile uint32_t CAN_Mstr_Node_StdID_1;
	volatile uint32_t CAN_Mstr_Node_StdId_2;

	const CAN_Msg_Struct* CAN_Msg_list;

}CAN_Ctrl_Struct;

extern CAN_Ctrl_Struct CAN_Ctrl;


void CAN_Struct_Init();

unsigned char Calculate_CRC_8(volatile unsigned char message[],uint32_t nbyte);

void Handle_CAN_Msgs(CAN_Ctrl_Struct* xCAN_Ctrl);

void CAN_Send_Msg(CAN_Ctrl_Struct* xCAN_Ctrl);

void CAN_Recive_Msg(CAN_Ctrl_Struct* xCAN_Ctrl);

void CAN_Data_Handler(CAN_Ctrl_Struct* xCan_Ctrl);

void Dummy_func();

#endif /* SRC_CAN_LIB_CAN_LIB_H_ */
