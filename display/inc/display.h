/**
 * @file display.h
 * @author David Zeman (dzeman.elekon@gmail.com)
 * @brief 
 * @date 2022-05-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdint.h>
#include <stdbool.h>
#include "display_def.h"


void display_setData(const uint8_t * pData, uint8_t dataLen);
void display_setBrightLvl(display_brLvlProfile_t brLvlProfile);

// called by timer interrupt
void display_sendData(void);


#endif /* DISPLAY_H_ */
