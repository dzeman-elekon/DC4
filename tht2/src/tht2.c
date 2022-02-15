/**
 * @file tht2.c
 * @author David Zeman (dzeman.elekon@gmail.com)
 * @brief 
 * @date 2022-02-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../inc/tht2.h"


static uint8_t msgData[CFG_THT2_MSG_DATA_BUFFER_SIZE];
static uint8_t msgDataLen;

/**
 * @brief 
 * 
 * @param me 
 */
void THT2_init(THT2_t * me)
{
    SP_MSG_DATA_LEN         = 0;
    SP_MSG_DATA[0]          = 0x00;

    THT2_MSG_INDEX          = 0;
    THT2_MSG_BUFFER[0]      = SP_END_CHAR;
}

/**
 * @brief 
 * 
 * @param me 
 * @return int16_t 
 */
int16_t THT2_getTemp(THT2_t * me)
{
    SP_MSG_DATA_LEN = 1;
    SP_MSG_DATA[0]  = 0x00;

    // PREP MSG
    SPINEL_msgPrepare(me->spData, THT2_MSG_BUFFER, SP_INST_TEMP, 2, SP_MSG_DATA, SP_MSG_DATA_LEN);

    // SEND MSG
    THT2_MSG_SEND(THT2_MSG_BUFFER, (SP_MSG_LEN + SP_MSG_DATA_LEN));

    HAL_Delay(100);

    return me->spData->temp;
}


/**
 * @brief 
 * 
 * @param me 
 * @return int16_t 
 */
int16_t THT2_reset(THT2_t * me)
{
    SP_MSG_DATA_LEN = 0;
    SP_MSG_DATA[0]  = 0x00;

    // PREP MSG
    SPINEL_msgPrepare(me->spData, THT2_MSG_BUFFER, SP_INST_RESET, 2, SP_MSG_DATA, SP_MSG_DATA_LEN);

    // SEND MSG
    THT2_MSG_SEND(THT2_MSG_BUFFER, (SP_MSG_LEN + SP_MSG_DATA_LEN));

    HAL_Delay(100);

    return me->spData->state;
}

int16_t THT2_setUnit(THT2_t * me, uint8_t unit)
{
    SP_MSG_DATA_LEN = 2;
    SP_MSG_DATA[0]  = SP_CH0_ALL;
    SP_MSG_DATA[1]  = unit;

    // PREP MSG
    SPINEL_msgPrepare(me->spData, THT2_MSG_BUFFER, SP_INST_WUNIT, 2, SP_MSG_DATA, SP_MSG_DATA_LEN);

    // SEND MSG
    THT2_MSG_SEND(THT2_MSG_BUFFER, (SP_MSG_LEN + SP_MSG_DATA_LEN));

    HAL_Delay(100);

    return me->spData->state;
}

int16_t THT2_getUnit(THT2_t * me)
{
    SP_MSG_DATA_LEN = 0;
    SP_MSG_DATA[0]  = 0x00;

    // PREP MSG
    SPINEL_msgPrepare(me->spData, THT2_MSG_BUFFER, SP_INST_RUNIT, 2, SP_MSG_DATA, SP_MSG_DATA_LEN);

    // SEND MSG
    THT2_MSG_SEND(THT2_MSG_BUFFER, (SP_MSG_LEN + SP_MSG_DATA_LEN));

    HAL_Delay(100);

    return me->spData->tempUnit;
}

/**
 * @brief 
 * 
 * @param me 
 * @param data 
 * @param dataLen 
 * @return true 
 * @return false 
 */
bool THT2_msgReceive (THT2_t * me, uint8_t * data, uint8_t dataLen)
{
    if ((data == NULL) || (dataLen == 0)) return false;

    for (uint8_t i = 0; i < dataLen; i++)
    {
        // BEGIN OF MSG
        if (data[i] == SP_PREXIF)
        {
            THT2_MSG_INDEX = 0;
        }

        THT2_MSG_BUFFER[THT2_MSG_INDEX++] = data[i];
        THT2_MSG_BUFFER[THT2_MSG_INDEX]   = SP_END_CHAR;

        // END OF MSG
        if (data[i] == SP_END_CHAR)
        {
            return true;
        }
    }

    return false;
}
