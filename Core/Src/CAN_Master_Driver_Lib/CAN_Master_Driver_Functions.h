/*
 * CAN_Master_Driver_Functions.h
 *
 *  Created on: May 20, 2025
 *      Author: CH.Vivek
 */

#ifndef SRC_CAN_MASTER_DRIVER_LIB_CAN_MASTER_DRIVER_FUNCTIONS_H_
#define SRC_CAN_MASTER_DRIVER_LIB_CAN_MASTER_DRIVER_FUNCTIONS_H_

#include "CAN_Master_Driver_Variables.h"

//void CAN1_Init_Communication(struct CAN_CTRL_Struct  *CAN1_Master_Ctrl);

void CAN1_Init();  // initialization

unsigned char CAN_crcCheck(__IO unsigned char message[], uint32_t nbyte);   //CRC calculation

void CAN_SetFilter(uint8_t nodeId);  //filter reduces CPU load

void CAN_SendData(uint16_t stdId, uint8_t *data);  //sends the data through CAN

void CAN_RecieveData(struct CAN_CTRL_Struct *CAN1_Master_Ctrl);

//
//void CAN_Init(CAN_Node *node);
//void CAN_Transmit(CAN_Node *node, uint32_t std_id, uint8_t *data, uint8_t len);
//void CAN_Filter_Config(CAN_Node *node, uint8_t filter_id);
//void CAN_IRQ_Handler(CAN_Node *node);

uint8_t CAN_Control_Transmit(CAN_Control_t *ctrl, uint16_t std_id, uint8_t *data, uint8_t len);

uint8_t CAN_Control_Receive(CAN_Control_t *ctrl);




#endif /* SRC_CAN_MASTER_DRIVER_LIB_CAN_MASTER_DRIVER_FUNCTIONS_H_ */
