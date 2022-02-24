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

    SPINEL_t          * spinel;

}   THT2_t;


// MSG INST
void THT2_init          (THT2_t * me);
void THT2_getMeasure    (THT2_t * me);
void THT2_reset         (THT2_t * me);
void THT2_setUnit       (THT2_t * me, uint8_t unit);
void THT2_getUnit       (THT2_t * me);
void THT2_getSensID     (THT2_t * me);

bool THT2_waitForACK    (THT2_t * me, uint16_t time);

// MSG ACK (RX CLBCK)
bool THT2_msgReceive    (THT2_t * me, uint8_t * data, uint8_t dataLen);
bool THT2_msgParse      (THT2_t * me);



#endif /* THT2_H_ */
