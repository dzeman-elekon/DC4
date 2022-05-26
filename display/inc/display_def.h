/**
 * @file display_def.h
 * @author David Zeman (dzeman.elekon@gmail.com)
 * @brief 
 * @date 2022-05-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef DISPLAY_DEF_H_
#define DISPLAY_DEF_H_


// DIGIT NUMS
#define NUM_0               0b11111100 // 252
#define NUM_1               0b01100000 //  96
#define NUM_2               0b11011010 // 218
#define NUM_3               0b11110010 // 242
#define NUM_4               0b01100110 // 102
#define NUM_5               0b10110110 // 182
#define NUM_6               0b10111110 // 190
#define NUM_7               0b11100000 // 224
#define NUM_8               0b11111110 // 254
#define NUM_9               0b11110110 // 246
#define NUM_A               0b11101110 // 238
#define NUM_B               0b00111110 //  62
#define NUM_C               0b10011100 // 156
#define NUM_D               0b01111010 // 122
#define NUM_E               0b10011110 // 158
#define NUM_F               0b10001110 // 142
#define DOT                 0b00000001


typedef struct display_brLvlProfile_t
{
    uint8_t     text;
    uint8_t     dots;

}	display_brLvlProfile_t;


#endif /* DISPLAY_DEF_H_ */
