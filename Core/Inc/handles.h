/*
 * handles.h
 *
 *  Created on: Oct 10, 2020
 *      Author: joaquin.alvidrez
 */

#ifndef INC_HANDLES_H_
#define INC_HANDLES_H_

#include "stm32f4xx_hal.h"

namespace handles
{
    void init_uart(UART_HandleTypeDef &h);

} // namespace handles

#endif /* INC_HANDLES_H_ */
