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


/****************************************************************************************************************
 * @brief Funkce k inicializaci protokolu Spinel
 * 
 * @param me            vlastni struktura protokolu Spinel
 * 
 ****************************************************************************************************************/
void SPINEL_init(SPINEL_t * me)
{
    me->temp        = 0;
    me->tempUnit    = 0;
    me->humi        = 0;
    me->dewp        = 0;

    me->inst        = 0;
    me->ack         = 0;
}

/****************************************************************************************************************
 * @brief Funkce k vytvoreni kompletni zpravy s instrukci (k odeslani) dle protokolu Spinel
 * 
 * @param me            vlastni struktura protokolu Spinel
 * @param message       ukazatel na pole, kde bude Spinel zprava vytvorena
 * @param inst          instrukce Spinel zpravy
 * @param sign          podpis Spinel zpravy
 * @param msgData       ukazatel na data k vlozeni do Spinel zpravy
 * @param msgDataLen    delka dat (pocet bajtu) k vlozeni do Spinel zpravy
 * 
 ****************************************************************************************************************/
void SPINEL_msgPrepare(SPINEL_t * me, uint8_t * message, uint8_t msgInst, uint8_t msgSign, uint8_t * msgData, uint8_t msgDataLen)
{
    me->inst = msgInst;
    me->ack  = 0xFF;

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

/****************************************************************************************************************
 * @brief Funkce pro parsovani prijate zpravy dle protokolu Spinel
 * 
 * @param me            vlastni struktura protokolu Spinel
 * @param message       ukazatel na pole se Spinel zpravou
 * @return uint8_t      hodnota 0 - ok; jinak chyba
 * 
 ****************************************************************************************************************/
uint8_t SPINEL_msgParse(SPINEL_t * me, uint8_t * message)
{
    uint8_t dataIndex = 0;

    // MSG PRE
    if (message[SP_PRE] != SP_PREXIF) return 4;                                     // is data in buff
 
    // MSG FRM
    if (message[SP_FRM] != SP_FRM_97) return 3;

    // MSG ACK/INST
    if (message[SP_ACK] == me->inst)  return 2;                                     // is inst echo

    me->ack = message[SP_ACK];

    if (message[SP_ACK] != SP_ACK_OK) return 1;                                     // is ack ok

    // MSG DATA
    switch (me->inst)
    {
        case SP_INST_MEASR:

            if (message[SP_DATA + dataIndex] == SP_SENS_CH1_TEMP)                   // is temp channel
            {
                dataIndex++;

                if (message[SP_DATA + dataIndex] == SP_VALID_DATA)                  // is temp data
                {
                    dataIndex++;

                    me->temp  = (((uint16_t)message[SP_DATA + dataIndex++]) << 8);
                    me->temp |= (((uint16_t)message[SP_DATA + dataIndex++]) << 0);
                }
            }

            if (message[SP_DATA + dataIndex] == SP_SENS_CH2_HUMI)                   // is humi channel
            {
                dataIndex++;

                if (message[SP_DATA + dataIndex] == SP_VALID_DATA)                  // is temp data
                {
                    dataIndex++;

                    me->humi  = (((uint16_t)message[SP_DATA + dataIndex++]) << 8);
                    me->humi |= (((uint16_t)message[SP_DATA + dataIndex++]) << 0);
                }
            }


            if (message[SP_DATA + dataIndex] == SP_SENS_CH3_DEWP)                   // is dewp channel
            {
                dataIndex++;

                if (message[SP_DATA + dataIndex] == SP_VALID_DATA)                  // is temp data
                {
                    dataIndex++;

                    me->dewp  = (((uint16_t)message[SP_DATA + dataIndex++]) << 8);
                    me->dewp |= (((uint16_t)message[SP_DATA + dataIndex++]) << 0);
                }
            }

            break;

        case SP_INST_RUNIT:

            if (message[SP_DATA + dataIndex] == SP_SENS_CH1_TEMP)                   // is temp channel
            {
                dataIndex++;

                me->tempUnit = (uint16_t)message[SP_DATA + dataIndex++];
            }

            break;

        case SP_INST_STYPE:

            me->sensID = (uint16_t)message[SP_DATA + dataIndex++];
            
            break;

        case SP_INST_RESET:

            // NO DATA TO PARSE

            break;
    
        default:
            break;
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
    return 0;
}
