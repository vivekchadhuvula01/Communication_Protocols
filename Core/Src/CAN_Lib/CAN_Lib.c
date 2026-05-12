/*
 * CAN_Lib.c
 *
 *  Created on: Apr 18, 2026
 *      Author: Vivek
 */

#include "CAN_Lib.h"



CAN_Ctrl_Struct CAN_Ctrl;

const uint8_t crcTable[256] = {0, 7, 14, 9, 28, 27, 18, 21, 56, 63, 54, 49, 36, 35, 42, 45, 112, 119, 126, 121,
									108, 107, 98, 101, 72, 79, 70, 65, 84, 83, 90, 93, 224, 231, 238, 233, 252, 251,
									242, 245, 216, 223, 214, 209, 196, 195, 202, 205, 144, 151, 158, 153, 140, 139,
									130, 133, 168, 175, 166, 161, 180, 179, 186, 189, 199, 192, 201, 206, 219, 220,
									213, 210, 255, 248, 241, 246, 227, 228, 237, 234, 183, 176, 185, 190, 171, 172, 165,
									162, 143, 136, 129, 134, 147, 148, 157, 154, 39, 32, 41, 46, 59, 60, 53, 50, 31, 24, 17, 22,
									3, 4, 13, 10, 87, 80, 89, 94, 75, 76, 69, 66, 111, 104, 97, 102, 115, 116, 125, 122, 137, 142,
									135, 128, 149, 146, 155, 156, 177, 182, 191, 184, 173, 170, 163, 164, 249, 254, 247, 240,
									229, 226, 235, 236, 193, 198, 207, 200, 221, 218, 211, 212, 105, 110, 103, 96, 117, 114, 123, 124, 81, 86,
									95, 88, 77, 74, 67, 68, 25, 30, 23, 16, 5, 2, 11, 12, 33, 38, 47, 40, 61, 58, 51, 52, 78, 73, 64, 71, 82, 85, 92,
									91, 118, 113, 120, 127, 106, 109, 100, 99, 62, 57, 48, 55, 34, 37, 44, 43, 6, 1, 8, 15, 26, 29, 20, 19, 174,
									169, 160, 167, 178, 181, 188, 187, 150, 145, 152, 159, 138, 141, 132, 131, 222, 217, 208, 215, 194, 197,
									204, 203, 230, 225, 232, 239, 250, 253, 244, 243};


const CAN_Msg_Struct CAN_Msg_List[20] = {
		{//0
			.Recv_Array_Length = 4,
			.Send_Array_Length = 4,
			.Callback_Fnc = &Dummy_func
		},
		{//1
			.Recv_Array_Length = 4,
			.Send_Array_Length = 4,
			.Callback_Fnc = &Dummy_func
		},
		{//2
			.Recv_Array_Length = 4,
			.Send_Array_Length = 4,
			.Callback_Fnc = &Dummy_func
		},
		{//3
			.Recv_Array_Length = 4,
			.Send_Array_Length = 4,
			.Callback_Fnc = &Dummy_func
		},
		{//4
			.Recv_Array_Length = 4,
			.Send_Array_Length = 4,
			.Callback_Fnc = &Dummy_func
		}
};


void CAN_Struct_Init()
{
	CAN_Ctrl.CANx 				 	= hcan1;
	CAN_Ctrl.CAN_Mstr_Node_StdID_1 	= 0x5FF;
	CAN_Ctrl.Rx_Recieved 		 	= 0;
	CAN_Ctrl.Rx_Index            	= 0;
	CAN_Ctrl.Tx_Index               = 0;
	CAN_Ctrl.Tx_Length              = 0;
	CAN_Ctrl.CAN_Busy_Flag          = 0;
	CAN_Ctrl.Calculated_CRC         = 0;

	CAN_Ctrl.start_bit              = 0;
	CAN_Ctrl.end_bit                = 1;


	CAN_Ctrl.CAN_Msg_list 	     	= CAN_Msg_List;
	CAN_Ctrl.CAN_Msg_List_Length    = (sizeof(CAN_Msg_List)) / (sizeof(CAN_Msg_List[0]));
}



/* Not required, as CAN Protocol itself have an internal CRC check */
unsigned char Calculate_CRC_8(volatile unsigned char message[],uint32_t nbyte)
{
   unsigned char  data,remainder =0;
   uint32_t  byte;

    for (byte = 0; byte < nbyte; ++byte)
    {
       data =(message[byte]) ^ (remainder);
       remainder = crcTable[data] ^ (message[byte] << 8);

    }
     return (remainder);
}


void CAN_Data_Handler(CAN_Ctrl_Struct* xCan_Ctrl)
{
	if(xCan_Ctrl->Rx_Recieved == 1 && BASE64_Ctrl.Busy_Flag == 0 && xCan_Ctrl->CAN_Busy_Flag == 0)
	{
		int status = BASE64_FUN_decode(xCan_Ctrl->B64_Rx_arr, xCan_Ctrl->Rx_arr);
		if(status == BASE64_Success)
		{
			if((xCan_Ctrl->Rx_arr[0] == xCan_Ctrl->CAN_Slave_Id) && (xCan_Ctrl->Rx_arr[1] == xCan_Ctrl->CAN_Mstr_Node_StdID_1 || xCan_Ctrl->Rx_arr[1] == xCan_Ctrl->CAN_Mstr_Node_StdId_2))
			{
				if(BASE64_Ctrl.Output_Length == xCan_Ctrl->CAN_Msg_list[xCan_Ctrl->Rx_arr[2]].Recv_Array_Length)
				{
					xCan_Ctrl->Calculated_CRC = Calculate_CRC_8(xCan_Ctrl->Rx_arr, xCan_Ctrl->CAN_Msg_list[xCan_Ctrl->Rx_arr[2]].Recv_Array_Length -1);
					if(xCan_Ctrl->Calculated_CRC == xCan_Ctrl->Rx_arr[xCan_Ctrl->CAN_Msg_list[xCan_Ctrl->Rx_arr[2]].Recv_Array_Length - 1])
					{
						xCan_Ctrl->CAN_Msg_list[xCan_Ctrl->Rx_arr[2]].Callback_Fnc();
					}
					else
					{
						xCan_Ctrl->CAN_Busy_Flag = 0;
					}
				}
				else
				{
					xCan_Ctrl->CAN_Busy_Flag = 0;
				}
			}
			else
			{
				xCan_Ctrl->CAN_Busy_Flag = 0;
			}
		}
		else
		{
			xCan_Ctrl->CAN_Busy_Flag = 0;
		}
	}
}



void CAN_Recive_Msg(CAN_Ctrl_Struct* xCAN_Ctrl)
{
	CAN_RxHeaderTypeDef Rx_Header;

	if(HAL_CAN_GetRxMessage(&(xCAN_Ctrl->CANx), CAN_RX_FIFO0, &Rx_Header, (uint8_t*)xCAN_Ctrl->RDB) == HAL_OK)
	{
		if((Rx_Header.StdId == xCAN_Ctrl->CAN_Mstr_Node_StdID_1) || (Rx_Header.StdId == xCAN_Ctrl->CAN_Mstr_Node_StdId_2))
		{
			xCAN_Ctrl->Index = 0; xCAN_Ctrl->CAN_Busy_Flag = 1;
			while(xCAN_Ctrl->Index < 8)
			{
				if((xCAN_Ctrl->RDB[xCAN_Ctrl->Index] != 0) && (xCAN_Ctrl->RDB[xCAN_Ctrl->Index] != 1))
				{
					xCAN_Ctrl->B64_Rx_arr[xCAN_Ctrl->Rx_Index];
					xCAN_Ctrl->Rx_Index++;
				}
				if(xCAN_Ctrl->RDB[xCAN_Ctrl->Index] == 1){
					xCAN_Ctrl->Rx_Recieved = 1;
					xCAN_Ctrl->Rx_Index = 0;
				}
				xCAN_Ctrl->Index++;
			}
			xCAN_Ctrl->CAN_Busy_Flag = 0;
		}
	}
}


void CAN_Send_Msg(CAN_Ctrl_Struct* xCAN_Ctrl)
{
	xCAN_Ctrl->Index = 0;
	while(xCAN_Ctrl->B64_Rx_arr[xCAN_Ctrl->Index] != 1){

		memcpy((void*)xCAN_Ctrl->TDB,(void*)&xCAN_Ctrl->B64_Tx_arr[xCAN_Ctrl->Index],8);
		CAN_TxHeaderTypeDef TxHeader;
		uint32_t TxMailBox;
		TxHeader.StdId = 0x5FF;
		TxHeader.IDE = CAN_ID_STD;
		TxHeader.RTR = CAN_RTR_DATA;
		TxHeader.DLC = 8;
		TxHeader.TransmitGlobalTime = DISABLE;

		if(HAL_CAN_GetTxMailboxesFreeLevel(&hcan1) > 0)
		{
			if(HAL_CAN_AddTxMessage(&hcan1, &TxHeader, (uint8_t*)xCAN_Ctrl->TDB, &TxMailBox)!= HAL_OK)
			{
				Error_Handler();
			}
		}
		while(HAL_CAN_IsTxMessagePending(&hcan1, TxMailBox));
		xCAN_Ctrl->Index = xCAN_Ctrl->Index + 8;
	}
}

void CAN_Send_Init(CAN_Ctrl_Struct* xCan_Ctrl)
{

	BASE64_Ctrl.Input_Length = 12;
	int status = BASE64_FUN_encode(xCan_Ctrl->Tx_arr, xCan_Ctrl->B64_Tx_arr);
	if(status == BASE64_Success)
	{
		xCan_Ctrl->B64_Tx_arr[BASE64_Ctrl.Output_Length + 1] = xCan_Ctrl->end_bit;
		if(status == BASE64_Success)
		{
			xCan_Ctrl->Tx_Length = BASE64_Ctrl.Output_Length;
			if(HAL_CAN_ActivateNotification(&(xCan_Ctrl->CANx), CAN_IT_TX_MAILBOX_EMPTY) != HAL_OK)
			{
				Error_Handler();
			}
		}
	}
}


void Dummy_func(){

	CAN_Ctrl.Tx_arr[0] 	= 'A';
	CAN_Ctrl.Tx_arr[1] 	= 'B';
	CAN_Ctrl.Tx_arr[2] 	= 'C';
	CAN_Ctrl.Tx_arr[3] 	= 'D';
	CAN_Ctrl.Tx_arr[4] 	= 'E';
	CAN_Ctrl.Tx_arr[5] 	= 'F';
	CAN_Ctrl.Tx_arr[6] 	= 'G';
	CAN_Ctrl.Tx_arr[7] 	= 'H';
	CAN_Ctrl.Tx_arr[8] 	= 'I';
	CAN_Ctrl.Tx_arr[9] 	= 'J';
	CAN_Ctrl.Tx_arr[10] = 'K';
	CAN_Ctrl.Tx_arr[11]	= 'L';

	CAN_Send_Init(&CAN_Ctrl);
}
