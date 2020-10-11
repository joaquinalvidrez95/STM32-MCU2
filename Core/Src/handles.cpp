/*
 * handles.cpp
 *
 *  Created on: Oct 10, 2020
 *      Author: joaquin.alvidrez
 */

#include "handles.h"

#include "stm32f4xx_hal.h"

namespace handles
{
    static inline void handle_error(void);

    void init_uart(UART_HandleTypeDef &h)
    {
        h.Instance = USART2;
        h.Init.BaudRate = 115200u;
        h.Init.WordLength = UART_WORDLENGTH_8B;
        h.Init.StopBits = UART_STOPBITS_1;
        h.Init.Parity = UART_PARITY_NONE;
        h.Init.HwFlowCtl = UART_HWCONTROL_NONE;
        h.Init.Mode = UART_MODE_TX_RX;

        if (HAL_OK != HAL_UART_Init(&h))
        {
            handle_error();
        }
    }

    static inline void handle_error(void)
    {
        for (;;)
        {
        }
    }

} // namespace handles
