/**
 * @file tht2_cfg.h
 * @author David Zeman (dzeman.elekon@gmail.com)
 * @brief 
 * @date 2022-02-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef THT2_CFG_H_
#define THT2_CFG_H_


#include "stm32f4xx_hal.h"


// THT2 UART
extern  UART_HandleTypeDef                * UART_RS485;
#define THT2_UART_TX(pData, dataLen)        HAL_UART_Transmit   (UART_RS485, pData, dataLen, 100)
#define THT2_UART_RX(pData, dataLen)        HAL_UART_Receive_DMA(UART_RS485, pData, dataLen)
#define OK									HAL_OK

// THT2 GPIO DE
#define THT2_GPIO_DE_ENABLE()               HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET)
#define THT2_GPIO_DE_DISABLE()              HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET)

// THT2 GONFIG
#define CFG_THT2_UART_BUFFER_SIZE           30



#endif /* THT2_CFG_H_ */
