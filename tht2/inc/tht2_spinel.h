/**
 * @file tht2_spinel.h
 * @author David Zeman (dzeman.elekon@gmail.com)
 * @brief 
 * @date 2022-02-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef THT2_SPINEL_H_
#define THT2_SPINEL_H_


#include <stdint.h>
#include "tht2_spinel_def.h"
#include "tht2_spinel_cfg.h"


void THT2_prepareMsgRqst(unsigned char * message, unsigned char inst, unsigned char sign, unsigned char * data, unsigned char dataLen);
void THT2_processMsgResp(void);


#endif /* THT2_SPINEL_H_ */
