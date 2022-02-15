/**
 * @file tht2.h
 * @author David Zeman (dzeman.elekon@gmail.com)
 * @brief 
 * @date 2022-02-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef THT2_H_
#define THT2_H_


#include <stdint.h>
#include <stdbool.h>
#include "spinel.h"
#include "tht2_cfg.h"
#include "tht2_def.h"


typedef struct THT2_t
{
    uint8_t             msgBuffer[CFG_THT2_MSG_BUFFER_SIZE];
    uint8_t             msgIndex;

    SPINEL_t          * spData;

}   THT2_t;


void    THT2_init       (THT2_t * me);
int16_t THT2_getTemp    (THT2_t * me);
int16_t THT2_reset      (THT2_t * me);
int16_t THT2_setUnit    (THT2_t * me, uint8_t unit);
int16_t THT2_getUnit    (THT2_t * me);


// UART RS485 RX
bool    THT2_msgReceive (THT2_t * me, uint8_t * data, uint8_t dataLen);


#endif /* THT2_H_ */
