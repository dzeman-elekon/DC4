/**
 * @file spinel.h
 * @author David Zeman (dzeman.elekon@gmail.com)
 * @brief 
 * @date 2022-02-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef SPINEL_H_
#define SPINEL_H_


#include <stdint.h>
#include "spinel_def.h"
#include "spinel_cfg.h"


typedef struct SPINEL_t
{
    uint16_t    temp;
    uint16_t    tempUnit;
    uint16_t    humi;
    uint16_t    dewp;

    uint8_t     sensID;

    uint8_t     inst;
    uint8_t     ack;

}   SPINEL_t;


void    SPINEL_init      (SPINEL_t * me);
void    SPINEL_msgPrepare(SPINEL_t * me, uint8_t * message, uint8_t msgInst, uint8_t msgSign, uint8_t * msgData, uint8_t msgDataLen);
uint8_t SPINEL_msgParse  (SPINEL_t * me, uint8_t * message);


#endif /* SPINEL_H_ */
