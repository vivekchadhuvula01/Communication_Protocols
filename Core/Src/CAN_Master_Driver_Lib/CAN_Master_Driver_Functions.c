/*
 * CAN_Master_Driver_Functions.c
 *
 *  Created on: May 20, 2025
 *      Author: CH.Vivek
 */

#include "main.h"
#include "CAN_Master_Driver_Functions.h"
#include "CAN_Master_Driver_Variables.h"



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

void CAN1_Init()
{
	CAN1_Master_Ctrl.hcanx = hcan1;
	CAN1_Master_Ctrl.CAN_Busy_Flag = 0;
	CAN1_Master_Ctrl.CAN_Busy_Flag_TimeOut_Cntr = 0;
	CAN1_Master_Ctrl.CAN_Recv_TimeOut_Cntr = 0;

	CAN1_Master_Ctrl.Message_ID = 0;

	CAN1_Master_Ctrl.Send_Msg_Len = 8;
	CAN1_Master_Ctrl.Send_Index = 0;
	CAN1_Master_Ctrl.Send_Enable = 0;
	CAN1_Master_Ctrl.Send_Flag = 0;
	CAN1_Master_Ctrl.Send_Error_Flag = 1;

	CAN1_Master_Ctrl.Recv_Arr_Index = 0;
	CAN1_Master_Ctrl.Recv_Enable = 0;
	CAN1_Master_Ctrl.Recv_Error_Flag = 0;
	CAN1_Master_Ctrl.Recv_Flag = 0;
	CAN1_Master_Ctrl.Recv_Msg_len = 8;

	CAN1_Master_Ctrl.Set_Filter = 0;  // 1 - filter is set , 0 - filter is not set

	CAN1_Master_Ctrl.Node1_Active = 0;
	CAN1_Master_Ctrl.Node2_Active = 0;
	CAN1_Master_Ctrl.Node3_Active = 0;
	CAN1_Master_Ctrl.Node4_Active = 0;
	CAN1_Master_Ctrl.Node5_Active = 0;

}



void CAN_SetFilter()
{
	CAN1_Init();
	CAN_FilterTypeDef filterConfig;

	filterConfig.FilterBank = 0;
	filterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	filterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	filterConfig.FilterIdHigh = 0x0000;
	filterConfig.FilterIdLow = 0x0000;
	filterConfig.FilterMaskIdHigh = 0x0000;
	filterConfig.FilterMaskIdLow = 0x0000;
	filterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
	filterConfig.FilterActivation = ENABLE;

	CAN1_Master_Ctrl.Set_Filter = 1;  //set this flag 1 after filter is set

	if(HAL_CAN_ConfigFilter(&hcan1, &filterConfig) != HAL_OK){
		Error_Handler();
		CAN1_Master_Ctrl.Set_Filter = 0;
	}
}

void CAN_SendData(uint16_t stdId, uint8_t *data)
{

	CAN_TxHeaderTypeDef txHeader;
	uint32_t txMailbox;

	if(CAN1_Master_Ctrl.Set_Filter == 0)
	{
		CAN_SetFilter();
	}

	switch(stdId)
	{
	 case CAN_Node1:
	            // Node 1 specific action
	        	CAN1_Master_Ctrl.Node1_Active = 1;
	            break;
	        case CAN_Node2:
	            // Node 2 specific action
	        	CAN1_Master_Ctrl.Node2_Active = 1;
	            break;
	        case CAN_Node3:
	            // Node 3 specific action
	        	CAN1_Master_Ctrl.Node3_Active = 1;
	            break;
	        case CAN_Node4:
	            // Node 4 specific action
	        	CAN1_Master_Ctrl.Node4_Active = 1;
	            break;
	        case CAN_Node5:
	            // Node 5 specific action
	        	CAN1_Master_Ctrl.Node5_Active = 1;
	            break;
	        default:
	            // default ID
	        	CAN_ID_STD;
	            break;

	}

	//prepare CAN frame
	txHeader.DLC = CAN1_Master_Ctrl.Send_Msg_Len;  //Data Length 0-8
	txHeader.IDE = CAN_ID_STD;  //standard ID 11bits
	txHeader.RTR = CAN_RTR_DATA ; //Data frame
	txHeader.StdId = stdId; //messageId
	txHeader.TransmitGlobalTime = DISABLE;

	// send CAN frame
	if(HAL_CAN_AddTxMessage(&hcan1, &txHeader, data, &txMailbox) != HAL_OK)
	{
		CAN1_Master_Ctrl.Send_Error_Flag = HAL_ERROR;
		Error_Handler();
	}
	if(HAL_CAN_AddTxMessage(&hcan1, &txHeader, data, &txMailbox) == HAL_OK)
	{
		CAN1_Master_Ctrl.Send_Flag = 1;
	}
}


#define RX_QUEUE_SIZE 10
CAN_Message_t can_rx_queue[RX_QUEUE_SIZE];
uint8_t can_rx_index = 0;


void CAN_HandleMessage(CAN_RxHeaderTypeDef *header, uint8_t *data)
{
    // Store into ring buffer
    if (CAN1_Master_Ctrl.Recv_Arr_Index < CAN1_Master_Ctrl.Recv_Msg_len)
    {
        can_rx_queue[can_rx_index].id = header->StdId;
        can_rx_queue[can_rx_index].dlc = header->DLC;
        memcpy(can_rx_queue[can_rx_index].data, data, header->DLC);
        can_rx_index++;
    }
    // Handle message based on ID
    switch (header->StdId)
    {
        case CAN_Node1:
            // Node 1 specific action
        	CAN1_Master_Ctrl.Node1_Active = 1;
            break;
        case CAN_Node2:
            // Node 2 specific action
        	CAN1_Master_Ctrl.Node2_Active = 1;
            break;
        case CAN_Node3:
            // Node 3 specific action
        	CAN1_Master_Ctrl.Node3_Active = 1;
            break;
        case CAN_Node4:
            // Node 4 specific action
        	CAN1_Master_Ctrl.Node4_Active = 1;
            break;
        case CAN_Node5:
            // Node 5 specific action
        	CAN1_Master_Ctrl.Node5_Active = 1;
            break;
        default:
            // default ID
        	CAN1_Master_Ctrl.Node1_Active = 0;
        	CAN1_Master_Ctrl.Node2_Active = 0;
        	CAN1_Master_Ctrl.Node3_Active = 0;
        	CAN1_Master_Ctrl.Node4_Active = 0;
        	CAN1_Master_Ctrl.Node5_Active = 0;
            break;
    }
}


void CAN_RecieveData(struct CAN_CTRL_Struct *CAN1_Master_Ctrl)
{

}

uint8_t CAN_Control_Transmit(CAN_Control_t *CAN_CTRL_2, uint16_t std_id, uint8_t *data, uint8_t len) {
    if (len > 8 || ctrl == NULL || data == NULL)
        return 0; // Invalid input

    // Check available TX mailbox
    uint8_t mailbox;
    if (CAN_CTRL_2->Instance->TSR & CAN_TSR_TME0)
        mailbox = 0;
    else if (CAN_CTRL_2->Instance->TSR & CAN_TSR_TME1)
        mailbox = 1;
    else if (CAN_CTRL_2->Instance->TSR & CAN_TSR_TME2)
        mailbox = 2;
    else
        return 0; // No mailbox available

    CAN_CTRL_2->TxMailbox = mailbox;

    // Clear pending flags
    CAN_CTRL_2->TxPending = 1;
    CAN_CTRL_2->TxComplete = 0;

    // Load TX mailbox
    CAN_TxMailBox_TypeDef *mb = &CAN_CTRL_2->Instance->sTxMailBox[mailbox];
    mb->TIR = 0;
    mb->TIR |= ((uint32_t)std_id << 21) & CAN_TI0R_STID; // Set standard ID
    mb->TIR &= ~CAN_TI0R_IDE;                            // Standard frame
    mb->TIR &= ~CAN_TI0R_RTR;                            // Data frame

    mb->TDTR = len & 0x0F;
    mb->TDLR = ((uint32_t)data[3] << 24) | ((uint32_t)data[2] << 16) |
               ((uint32_t)data[1] << 8) | data[0];
    mb->TDHR = ((uint32_t)data[7] << 24) | ((uint32_t)data[6] << 16) |
               ((uint32_t)data[5] << 8) | data[4];

    mb->TIR |= CAN_TI0R_TXRQ; // Request transmission

    return 1; // Success
}

uint8_t CAN_Control_Receive(CAN_Control_t *CAN_CTRL_2) {
    if (!(CAN_CTRL_2->Instance->RF0R & CAN_RF0R_FMP0)) {
        return 0; // No message pending
    }

    CAN_FIFOMailBox_TypeDef *mb = &CAN_CTRL_2->Instance->sFIFOMailBox[0];

    // Extract ID
    CAN_CTRL_2->RxStdId = (mb->RIR >> 21) & 0x7FF; //Mask with 0x7FF to get only 11 bits.

    // Extract DLC
    CAN_CTRL_2->RxDLC = mb->RDTR & 0x0F;  //Lower 4 bits of the RDTR register tell how many bytes (0–8) are in the data field.

    // Extract data
    uint32_t low = mb->RDLR; //RDLR = Receive Data Low Register (bytes 0–3)
    uint32_t high = mb->RDHR; //RDHR = Receive Data High Register (bytes 4–7)

    CAN_CTRL_2->RxData[0] = low & 0xFF;
    CAN_CTRL_2->RxData[1] = (low >> 8) & 0xFF;
    CAN_CTRL_2->RxData[2] = (low >> 16) & 0xFF;
    CAN_CTRL_2->RxData[3] = (low >> 24) & 0xFF;
    CAN_CTRL_2->RxData[4] = high & 0xFF;
    CAN_CTRL_2->RxData[5] = (high >> 8) & 0xFF;
    CAN_CTRL_2->RxData[6] = (high >> 16) & 0xFF;
    CAN_CTRL_2->RxData[7] = (high >> 24) & 0xFF;

    // Mark received
    CAN_CTRL_2->RxPending = 1;

    // Release FIFO
    CAN_CTRL_2->Instance->RF0R |= CAN_RF0R_RFOM0;

    return 1; // Success
}

