


#include "BASE64_VAR.h"
#include "BASE64_FUN.h"
#include "stdio.h"


/*
 * Encode a buffer into base64 format
 */
/**
 * @brief Encode a buffer into base64 format.
 * @param destination buffer
 * @param destination buffer length
 * @param source buffer
 * @param source buffer length
 * @return error, 0 is OK
 */
int BASE64_FUN_encode(volatile unsigned char *src, volatile unsigned char *dst )
{
//	unsigned char *src = BASE64_Input_Arr;
//	unsigned char *dst = BASE64_Output_Arr;
    size_t i, n;
    int C1, C2, C3;
    volatile unsigned char *p;

    if( BASE64_Ctrl.Input_Length == 0 )
        return( 0 );

    n = (BASE64_Ctrl.Input_Length  << 3) / 6;

    switch( (BASE64_Ctrl.Input_Length  << 3) - (n * 6) )
    {
        case  2: n += 3; break;
        case  4: n += 2; break;
        default: break;
    }

    if( BASE64_Arr_Len < n + 1 )
    {
        BASE64_Ctrl.Output_Length = n + 1;
        return( POLARSSL_ERR_BASE64_BUFFER_TOO_SMALL );
    }

    n = (BASE64_Ctrl.Input_Length  / 3) * 3;

    for( i = 0, p = dst; i < n; i += 3 )
    {
        C1 = *src++;
        C2 = *src++;
        C3 = *src++;

        *p++ = base64_enc_map[(C1 >> 2) & 0x3F];
        *p++ = base64_enc_map[(((C1 &  3) << 4) + (C2 >> 4)) & 0x3F];
        *p++ = base64_enc_map[(((C2 & 15) << 2) + (C3 >> 6)) & 0x3F];
        *p++ = base64_enc_map[C3 & 0x3F];
    }

    if( i < BASE64_Ctrl.Input_Length  )
    {
        C1 = *src++;
        C2 = ((i + 1) < BASE64_Ctrl.Input_Length ) ? *src++ : 0;

        *p++ = base64_enc_map[(C1 >> 2) & 0x3F];
        *p++ = base64_enc_map[(((C1 & 3) << 4) + (C2 >> 4)) & 0x3F];

        if( (i + 1) < BASE64_Ctrl.Input_Length  )
             *p++ = base64_enc_map[((C2 & 15) << 2) & 0x3F];
        else *p++ = '=';

        *p++ = '=';
    }

    BASE64_Ctrl.Output_Length = p - dst;
    *p = 0;

    return( 0 );
}
/*
 * Decode a base64-formatted buffer
 */
/**
 * @brief Decode a base64-formatted buffer.
 * @param destination buffer
 * @param destination buffer length
 * @param source buffer
 * @param source buffer length
 * @return error, 0 is OK
 */
int BASE64_FUN_decode(volatile unsigned char *src, volatile unsigned char *dst)
{
//	unsigned char *src = BASE64_Input_Arr;
//	unsigned char *dst = BASE64_Output_Arr;

	BASE64_Ctrl.Busy_Flag=1;
	size_t i, n;
    uint32_t j, x;
    volatile unsigned char *p;

    for( i = j = n = 0; i < BASE64_Ctrl.Input_Length; i++ )
    {
        if( ( BASE64_Ctrl.Input_Length - i ) >= 2 &&
            src[i] == '\r' && src[i + 1] == '\n' )
            continue;

        if( src[i] == '\n' )
            continue;

        if( src[i] == '=' && ++j > 2 )
            return( POLARSSL_ERR_BASE64_INVALID_CHARACTER );

        if( src[i] > 127 || base64_dec_map[src[i]] == 127 )
            return( POLARSSL_ERR_BASE64_INVALID_CHARACTER );

        if( base64_dec_map[src[i]] < 64 && j != 0 )
            return( POLARSSL_ERR_BASE64_INVALID_CHARACTER );

        n++;
    }

    if( n == 0 )
        return( 0 );

    n = ((n * 6) + 7) >> 3;

    if( BASE64_Arr_Len < n )
    {
        BASE64_Ctrl.Output_Length = n;
        return( POLARSSL_ERR_BASE64_BUFFER_TOO_SMALL );
    }

   for( j = 3, n = x = 0, p = dst; i > 0; i--, src++ )
   {
        if( *src == '\r' || *src == '\n' )
            continue;

        j -= ( base64_dec_map[*src] == 64 );
        x  = (x << 6) | ( base64_dec_map[*src] & 0x3F );

        if( ++n == 4 )
        {
            n = 0;
            if( j > 0 ) *p++ = (unsigned char)( x >> 16 );
            if( j > 1 ) *p++ = (unsigned char)( x >>  8 );
            if( j > 2 ) *p++ = (unsigned char)( x       );
        }
    }

    BASE64_Ctrl.Output_Length = p - dst;

	BASE64_Ctrl.Busy_Flag=0;

    return( 0 );
}






