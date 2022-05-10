/**
 * @file display_cfg.h
 * @author David Zeman (dzeman.elekon@gmail.com)
 * @brief 
 * @date 2022-05-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef DISPLAY_CFG_H_
#define DISPLAY_CFG_H_


#define DISPLAY_DIGIT_NUM               6

#define DISPLAY_TEXT_DFL                {NUM_8, NUM_8, NUM_8, NUM_8, NUM_8, NUM_8}
#define DISPLAY_TEXT_TEST               {NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6}

#define DISPLAY_TEXT_BRLVL_DFL          {   15,    15,    15,    15,    15,    15}
#define DISPLAY_TEXT_BRLVL_TEST         {    4,    16,    32,    64,   128,   255}

#define DISPLAY_DOTS_DFL                {    1,     1,     1,     1,     1,     1};
#define DISPLAY_DOTS_TEST               {    0,     1,     0,     1,     0,     0};

#define DISPLAY_DOTS_BRLVL_DFL          {  255,   255,   255,   255,   255,   255};;
#define DISPLAY_DOTS_BRLVL_TEST         {    0,   128,    32,    64,    16,     4};


#endif /* DISPLAY_CFG_H_ */