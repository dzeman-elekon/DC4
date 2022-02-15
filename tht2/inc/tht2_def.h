/**
 * @file tht2_def.h
 * @author David Zeman (dzeman.elekon@gmail.com)
 * @brief 
 * @date 2022-02-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef THT2_DEF_H_
#define THT2_DEF_H_


#define THT2_MSG_SEND(msg, msgLen)  THT2_GPIO_DE_ENABLE();      \
                                    THT2_UART_TX(msg, msgLen);  \
                                    THT2_GPIO_DE_DISABLE();

#define THT2_MSG_BUFFER             me->msgBuffer
#define THT2_MSG_INDEX              me->msgIndex



#endif /* THT2_DEF_H_ */
