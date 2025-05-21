/*
 * CAN_Master_Driver_Functions.c
 *
 *  Created on: May 20, 2025
 *      Author: CH.Vivek
 */

#include "main.h"
#include "CAN_Master_Driver_Functions.h"
#include "CAN_Master_Driver_Variables.h"



void CAN1_Init()
{
	CAN1_Master_Ctrl.hcanx = hacn1;
	CAN1_Master_Ctrl.CAN_Busy_Flag = 0;
	CAN1_Master_Ctrl.CAN_Busy_Flag_TimeOut_Cntr = 0;
	CAN1_Master_Ctrl.CAN_Recv_TimeOut_Cntr = 0;

	CAN1_Master_Ctrl.Message_ID = 0;

	CAN1_Master_Ctrl.Send_Msg_Len = 0;
	CAN1_Master_Ctrl.Send_Index = 0;
	CAN1_Master_Ctrl.Send_Enable = 0;
	CAN1_Master_Ctrl.Send_Flag = 0;
	CAN1_Master_Ctrl.Send_Error_Flag = 1;

	CAN1_Master_Ctrl.Recv_Arr_Index = 0;
	CAN1_Master_Ctrl.Recv_Enable = 0;
	CAN1_Master_Ctrl.Recv_Error_Flag = 0;
	CAN1_Master_Ctrl.Recv_Flag = 0;

}


unsigned char CAN_crcCheck(__IO unsigned char message[], uint32_t nbyte)
{
	unsigned char data ,remainder = 0;
	uint32_t byte ;
	for (byte = 0 ; byte < nbyte; ++byte)
	{
		data = (message[byte] ) ^ (remainder);
		remainder = crc_Table[data] ^ (message[byte] << 8);

	}
	return (remainder);
}
