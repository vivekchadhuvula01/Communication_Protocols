



#ifndef SRC_BASE64_BASE64_VAR_H_
#define SRC_BASE64_BASE64_VAR_H_


#include "main.h"

#define POLARSSL_ERR_BASE64_BUFFER_TOO_SMALL               -0x002A  /**< Output buffer too small. */
#define POLARSSL_ERR_BASE64_INVALID_CHARACTER              -0x002C  /**< Invalid character in input. */
#define BASE64_Success										0

extern const unsigned char base64_enc_map[64];
extern const unsigned char base64_dec_map[128];

#define BASE64_Arr_Len 600
extern __IO unsigned char BASE64_Input_Arr[BASE64_Arr_Len];
extern __IO unsigned char BASE64_Output_Arr[BASE64_Arr_Len];

struct BASE64_Control_Struct
{
	volatile uint8_t Busy_Flag;
	volatile uint8_t Encode_Flag;
	volatile uint8_t Decode_Req_Flag;
	volatile uint16_t Input_Length;
	volatile uint16_t Output_Length;
};


extern struct BASE64_Control_Struct  BASE64_Ctrl;

#endif /* SRC_BASE64_BASE64_VAR_H_ */
