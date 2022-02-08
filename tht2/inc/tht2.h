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
#include "tht2_spinel.h"


void    THT2_init    (void);
int16_t THT2_getTemp (void);


#endif /* THT2_H_ */
