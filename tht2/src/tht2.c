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


/****************************************************************************************************************
 * @brief Funkce k inicializaci senzoru THT2
 * 
 * @param me     vlastni struktura senzoru THT2
 * 
 ****************************************************************************************************************/
void THT2_init(THT2_t * me)
{
    // SPINEL
    SPINEL_init(me->spinel);

    // LOCAL
    SP_MSG_DATA_LEN         = 0;
    SP_MSG_DATA[0]          = 0x00;

    // STRUCT ME (THT2_t)
    THT2_MSG_INDEX          = 0;
    THT2_MSG_BUFFER[0]      = SP_END_CHAR;
}

/****************************************************************************************************************
 * @brief Funkce k ziskani aktualniho stavu vsech merenych hodnot ze senzoru THT2
 * 
 * @param me     vlastni struktura senzoru THT2
 * 
 ****************************************************************************************************************/
void THT2_getMeasure(THT2_t * me)
{
    // PREP MSG DATA
    SP_MSG_DATA_LEN = 1;
    SP_MSG_DATA[0]  = 0x00;

    // PREP MSG
    SPINEL_msgPrepare(me->spinel, THT2_MSG_BUFFER, SP_INST_MEASR, 2, SP_MSG_DATA, SP_MSG_DATA_LEN);

    // SEND MSG
    THT2_MSG_SEND(THT2_MSG_BUFFER, (SP_MSG_LEN + SP_MSG_DATA_LEN));
}


/****************************************************************************************************************
 * @brief Funkce k volani resetu senzoru THT2
 * 
 * @param me     vlastni struktura senzoru THT2
 * 
 ****************************************************************************************************************/
void THT2_reset(THT2_t * me)
{
    SPINEL_init(me->spinel);

    // PREP MSG DATA
    SP_MSG_DATA_LEN = 0;
    SP_MSG_DATA[0]  = 0x00;

    // PREP MSG
    SPINEL_msgPrepare(me->spinel, THT2_MSG_BUFFER, SP_INST_RESET, 2, SP_MSG_DATA, SP_MSG_DATA_LEN);

    // SEND MSG
    THT2_MSG_SEND(THT2_MSG_BUFFER, (SP_MSG_LEN + SP_MSG_DATA_LEN));
}

/****************************************************************************************************************
 * @brief Funkce k nastaveni pozadovane jednotky pro teplotu senzoru THT2
 * 
 * @param me     vlastni struktura senzoru THT2
 * @param unit   pozadovana jednotka teploty
 * 
 ****************************************************************************************************************/
void THT2_setUnit(THT2_t * me, uint8_t unit)
{
    // PREP MSG DATA
    SP_MSG_DATA_LEN = 2;
    SP_MSG_DATA[0]  = SP_SENS_CH0_ALL;
    SP_MSG_DATA[1]  = unit;

    // PREP MSG
    SPINEL_msgPrepare(me->spinel, THT2_MSG_BUFFER, SP_INST_WUNIT, 2, SP_MSG_DATA, SP_MSG_DATA_LEN);

    // SEND MSG
    THT2_MSG_SEND(THT2_MSG_BUFFER, (SP_MSG_LEN + SP_MSG_DATA_LEN));
}

/****************************************************************************************************************
 * @brief Funkce k ziskani aktualne nastavene jednotky pro teplotu senzoru THT2
 * 
 * @param me     vlastni struktura senzoru THT2
 * 
 ****************************************************************************************************************/
void THT2_getUnit(THT2_t * me)
{
    // PREP MSG DATA
    SP_MSG_DATA_LEN = 0;
    SP_MSG_DATA[0]  = 0x00;

    // PREP MSG
    SPINEL_msgPrepare(me->spinel, THT2_MSG_BUFFER, SP_INST_RUNIT, 2, SP_MSG_DATA, SP_MSG_DATA_LEN);

    // SEND MSG
    THT2_MSG_SEND(THT2_MSG_BUFFER, (SP_MSG_LEN + SP_MSG_DATA_LEN));
}

/****************************************************************************************************************
 * @brief Funkce pro ziskani ID propojeneho cidla k senzoru THT2
 * 
 * @param me     vlastni struktura senzoru THT2
 * 
 ****************************************************************************************************************/
void THT2_getSensID(THT2_t * me)
{
    // PREP MSG DATA
    SP_MSG_DATA_LEN = 0;
    SP_MSG_DATA[0]  = 0x00;

    // PREP MSG
    SPINEL_msgPrepare(me->spinel, THT2_MSG_BUFFER, SP_INST_STYPE, 2, SP_MSG_DATA, SP_MSG_DATA_LEN);

    // SEND MSG
    THT2_MSG_SEND(THT2_MSG_BUFFER, (SP_MSG_LEN + SP_MSG_DATA_LEN));
}

/****************************************************************************************************************
 * @brief Funkce pro detekci prijate zpravy dle protokolu Spinel. Volana funkci pro prijem dat ze senzoru THT2
 * 
 * @param me      vlastni struktura senzoru THT2
 * @param data    prijate bajty zpravy Spinel
 * @param dataLen pocet prijatych bajtu zpravy Spinel
 * @return true   prijata kompletni zprava Spinel (pripravena pro parsovani)
 * @return false  prijimani zpravy zatim neni kompletni
 * 
 ****************************************************************************************************************/
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

/****************************************************************************************************************
 * @brief Funkce pro parsovani kompletni prijate zpravy prot. Spinel ze senzoru THT2.
 * 
 * @param me     vlastni struktura senzoru THT2
 * @return true  parsovani zpravy dopadlo v poradku
 * @return false parsovani zpravy skoncilo chybou
 * 
 ****************************************************************************************************************/
bool THT2_msgParse (THT2_t * me)
{
    return SPINEL_msgParse(me->spinel, me->msgBuffer);
}

/****************************************************************************************************************
 * @brief Funkce cekajici na odpoved (+platna data) ze senzoru THT2 (prijem -> parsovani -> vyhodnoceni). 
 * 
 * @param me     vlastni struktura senzoru THT2
 * @param time   limit pro cekani v milisekundach
 * @return true  odpoved dorazila v casovem limitu (platna data k dispozici) 
 * @return false odpoved nedorazila v casovem limitu (data nejsou k dispozici)
 * 
 ****************************************************************************************************************/
bool THT2_waitForACK (THT2_t * me, uint16_t time)
{
    uint8_t delay = 0;

    while (me->spinel->ack == SP_ACK_UNKN)
    {
        delay++;

        if (delay == time) return false;

        HAL_Delay(1);
    }

    return true;
}
