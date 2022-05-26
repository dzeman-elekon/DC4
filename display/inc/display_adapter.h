/**
 * @file display_adapter.h
 * @author David Zeman (dzeman.elekon@gmail.com)
 * @brief 
 * @date 2022-05-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef DISPLAY_ADAPTER_H_
#define DISPLAY_ADAPTER_H_


#include "stm32f4xx_hal.h"


// SPI - SEND
extern SPI_HandleTypeDef hspi3;

#define display_SPI_Transmit(pData, dataLen)     HAL_SPI_Transmit(&hspi3, pData, dataLen, 100);


// GPIO - LATCH
#define display_GPIO_Latch_Enable()              HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_SET);
#define display_GPIO_Latch_Disable()             HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_RESET);

// GPIO - OE
#define display_GPIO_Output_Enable()             HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_SET);
#define display_GPIO_Output_Disable()            HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_RESET);

// TIMER
extern TIM_HandleTypeDef htim9;
extern TIM_OC_InitTypeDef sConfigOC;

#define display_TIM_setForFrameNum(x)           if (x == 0)                                                                 \
                                                {                                                                           \
                                                    sConfigOC.Pulse = 1;                                                    \
                                                }                                                                           \
                                                else                                                                        \
                                                {                                                                           \
                                                    sConfigOC.Pulse = sConfigOC.Pulse << 1;                                 \
                                                }                                                                           \
                                                                                                                            \
                                                /* SET TIMER OC */                                                          \
                                                if (HAL_TIM_OC_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)  \
                                                {                                                                           \
                                                    Error_Handler();                                                        \
                                                }                                                                           \
                                                                                                                            \
                                                /* RESET TIMER COUNTER */                                                   \
                                                __HAL_TIM_SET_COUNTER(&htim9 , 0);                                          \


#endif /* DISPLAY_ADAPTER_H_ */
