/**
 * @file tht2.c
 * @author David Zeman (dzeman.elekon@gmail.com)
 * @brief 
 * @date 2022-02-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../inc/tht2.h"
#include "../inc/tht2_cfg.h"


unsigned char THT2_UART_txBuffer[CFG_THT2_UART_BUFFER_SIZE];
unsigned char THT2_UART_rxBuffer[CFG_THT2_UART_BUFFER_SIZE];


/**
 * @brief 
 * 
 */
void THT2_init(void)
{
    // TODO
}

/**
 * @brief 
 * 
 * @return int16_t 
 */
int16_t THT2_getTemp (void)
{
    int16_t       retValue  = 0x7FFF;
    uint16_t      temp      = 0x7FFF;
    unsigned char data      = 0;
    unsigned char dataLen   = 1;

    // PREPARE BUFFERS
    THT2_prepareMsgRqst(THT2_UART_txBuffer, C_TEMP, 2, &data, dataLen);
    THT2_UART_rxBuffer[0] = '\0';

    // TRANSMIT REQUEST  
    THT2_GPIO_DE_ENABLE();
    THT2_UART_TX(THT2_UART_txBuffer, (9+dataLen));
    THT2_GPIO_DE_DISABLE();

    // RECEIVE RESPONCE
    while (0 != THT2_UART_RX(THT2_UART_rxBuffer, 13));

    HAL_Delay(100);

    // RECEIVED DATA PARSING
//  THT2_processMsgResp;
    if (THT2_UART_rxBuffer[0] == '*')                       // is data in buff
    {
        if (THT2_UART_rxBuffer[INST] == ACK_OK)             // is ack ok
        {
            if (THT2_UART_rxBuffer[DATA + 0] == 0x01)       // is temp
            {
                if (THT2_UART_rxBuffer[DATA + 1] == 0x80)   // is valid
                {
                    temp  = (((uint16_t)THT2_UART_rxBuffer[DATA + 2]) << 8);
                    temp |= (((uint16_t)THT2_UART_rxBuffer[DATA + 3]) << 0);
                }
            }
        }
    }

    // NEGATIVE TEMP CONVERSION
    if (temp > 0x7FFF)
    {
        retValue = temp - 0x10000;
    }
    else
    if (temp < 0x7FFF)
    {
        retValue = temp;
    }

    return retValue;
}
