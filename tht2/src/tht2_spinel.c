/**
 * @file tht2_spinel.c
 * @author David Zeman (dzeman.elekon@gmail.com)
 * @brief 
 * @date 2022-02-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../inc/tht2_spinel.h"


/**
 * @brief Prepare message for THT2 request
 * 
 * @param message
 * @param inst 
 * @param sign 
 * @param data 
 * @param dataLen 
 */
void THT2_prepareMsgRqst(unsigned char * message, unsigned char inst, unsigned char sign, unsigned char * data, unsigned char dataLen)
{
#   if (CFG_THT2_FORMAT == FORMAT_97)

    message[PRE]                = PREXIF;
    message[FRM]                = CFG_THT2_FORMAT;
    message[LEN_H]              = 0x00;                     // (char)(len >> 4);
    message[LEN_L]              = dataLen + 5;              // (char)(len & 0x00FF);  // ADR + SIG + INST + SUM + CR => 5
    message[ADR]                = CFG_THT2_ADDRESS;
    message[SIG]                = sign;
    message[INST]               = inst;

    for (int i = 0; i < dataLen; i++)
    {
//      message[DATA + i*2 + 0] = BIN2HEX_H(*(pData + i));   // Hnible
//      message[DATA + i*2 + 1] = BIN2HEX_L(*(pData + i));   // Lnible
        message[DATA + i]       = *(data + i);
    }

    message[SUM]                = 0x00;

    for (int i = 0; i < (SUM); i++)                         // spocitat Check Sum
    {
        message[SUM]           += message[i];
    }

    message[SUM]                = ~message[SUM];
    message[END]                = END_CHAR;

#   elif (CFG_THT2_FORMAT == FORMAT_66)

#   warning Not finished for FORMAT_66

#   endif
}

/**
 * @brief 
 * 
 */
void THT2_processMsgResp(void)
{
    // TODO
}
