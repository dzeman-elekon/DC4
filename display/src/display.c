/**
 * @file display.c
 * @author David Zeman (dzeman.elekon@gmail.com)
 * @brief 
 * @date 2022-05-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../inc/display.h"
#include "../inc/display_cfg.h"
#include "../inc/display_adapter.h"


uint8_t display_text[]      = {NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6};
uint8_t display_textBrLvl[] = {    4,    16,    32,    64,   128, 	255};

uint8_t display_dots[]      = {    0,     1,     0,     1,     0,     0};
uint8_t display_dotsBrLvl[] = {    0,   128,    32,    64,    16,     4};

uint8_t display_frame[]     = {    0,     0,     0,     0,     0,     0};
uint8_t display_frameNum    = 0;


/**
 * @brief 
 * 
 * @param pData 
 * @param dataLen 
 */
void display_setData(const uint8_t * pData, uint8_t dataLen)
{
    // TODO
}

/**
 * @brief 
 * 
 * @param brLvlProfile 
 */
void display_setBrightLvl(display_brLvlProfile_t brLvlProfile)
{
    for (uint8_t i = 0; i < DISPLAY_DIGIT_NUM; i++)
    {
        display_textBrLvl[i] = brLvlProfile.text;
        display_dotsBrLvl[i] = brLvlProfile.dots;
    }
}

/**
 * @brief 
 * 
 * @param frameNum 
 */
void display_renderFrame (uint8_t frameNum)
{
    for (uint8_t i = 0; i < DISPLAY_DIGIT_NUM; i++)
    {
        display_frame[i] = 0;

        if (display_textBrLvl[i] & (1 << frameNum))
        {
          display_frame[i] |= display_text[i];
        }

        if (display_dotsBrLvl[i] & (1 << frameNum))
        {
          display_frame[i] |= display_dots[i];
        }
    }
}

/**
 * @brief 
 * 
 */
void display_sendFrame()
{
    // SEND
    display_SPI_Transmit(display_frame, DISPLAY_DIGIT_NUM);

    // LATCH
    display_GPIO_Latch_Enable();
    display_GPIO_Latch_Disable();

    // OUTPUT
    display_GPIO_Output_Enable();
    display_GPIO_Output_Disable();
}

/**
 * @brief 
 * 
 */
void display_sendData(void)
{
    display_frameNum += 1;
    display_frameNum &= 7;

    // TIMER SET
    display_TIM_setForFrameNum(display_frameNum);

    // DISPLAY DATA FRAME
    display_renderFrame(display_frameNum);

    // SPI SEND
    display_sendFrame();
}
