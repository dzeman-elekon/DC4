/**
 * @file spinel.c
 * @author David Zeman (dzeman.elekon@gmail.com)
 * @brief 
 * @date 2022-02-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../inc/spinel.h"


/**
 * @brief 
 * 
 * @param me 
 * @param message 
 * @param inst 
 * @param sign 
 * @param msgData 
 * @param msgDataLen 
 */
void SPINEL_msgPrepare(SPINEL_t * me, uint8_t * message, uint8_t msgInst, uint8_t msgSign, uint8_t * msgData, uint8_t msgDataLen)
{
#   if (CFG_SP_FORMAT == SP_FRM_97)

    message[SP_PRE]             = SP_PREXIF;
    message[SP_FRM]             = CFG_SP_FORMAT;
    message[SP_LEN_H]           = 0x00;                                 // (char)(len >> 4);
    message[SP_LEN_L]           = SP_MSG_DATA_LEN + SP_MSG_BODY_LEN;    // (char)(len & 0x00FF);
    message[SP_ADR]             = CFG_SP_ADDRESS;
    message[SP_SIG]             = msgSign;
    message[SP_INST]            = msgInst;

    for (int i = 0; i < SP_MSG_DATA_LEN; i++)
    {
//      message[DATA + i*2 + 0] = BIN2HEX_H(*(pData + i));              // Hnible
//      message[DATA + i*2 + 1] = BIN2HEX_L(*(pData + i));              // Lnible
        message[SP_DATA + i]    = *(SP_MSG_DATA + i);
    }

    message[SP_SUM]             = 0x00;

    for (int i = 0; i < SP_SUM; i++)                                    // spocitat Check Sum
    {
        message[SP_SUM]        += message[i];
    }

    message[SP_SUM]             = ~message[SP_SUM];
    message[SP_END]             = SP_END_CHAR;

#   elif (CFG_SP_FORMAT == SP_FRM_66)

#   warning Not finished for FORMAT_66

#   endif
}

/**
 * @brief 
 * 
 * @param me 
 * @param message 
 * @return uint8_t 
 */
uint8_t SPINEL_msgParse(SPINEL_t * me, uint8_t * message)
{
    if (message[SP_PRE] == SP_PREXIF)                               // is data in buff
    {
        if (message[SP_ACK] == SP_ACK_OK)                           // is ack ok
        {
            if (message[SP_DATA + 0] == SP_CH1_TEMP)                // is temp channel
            {
                if (message[SP_DATA + 1] == SP_VALID_DATA)          // is temp data
                {
                    me->temp  = (((uint16_t)message[SP_DATA + 2]) << 8);
                    me->temp |= (((uint16_t)message[SP_DATA + 3]) << 0);
                }
                else                                                // is temp unit
                {
                    me->tempUnit = (uint16_t)message[SP_DATA + 1];
                }
            }
        }
    }
/*
    // NEGATIVE TEMP CONVERSION
    if (temp > 0x7FFF)
    {
        retValue = temp - 0x10000;
    }
    else
    if (temp < 0x7FFF)
    {
        retValue = temp;
    }
*/
    if((message[SP_ACK] == SP_ACK_OK)      ||\
       (message[SP_ACK] == SP_ACK_BAD_I)   ||\
       (message[SP_ACK] == SP_ACK_BAD_D)   ||\
       (message[SP_ACK] == SP_ACK_WD_AD)   ||\
       (message[SP_ACK] == SP_ACK_DEV_ERR) ||\
       (message[SP_ACK] == SP_ACK_AUTO))
    {
        me->state = message[SP_ACK];

        return me->state;
    }
    else
    {
        return 0xFF;
    }
}
