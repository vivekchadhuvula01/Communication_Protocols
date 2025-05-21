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

void CAN_SendData(struct CAN_CTRL_Struct *CAN1_Master_Ctrl);

void CAN_RecieveData(struct CAN_CTRL_Struct *CAN1_Master_Ctrl);






#endif /* SRC_CAN_MASTER_DRIVER_LIB_CAN_MASTER_DRIVER_FUNCTIONS_H_ */
