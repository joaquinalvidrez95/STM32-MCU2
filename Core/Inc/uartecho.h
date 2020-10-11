/*
 * Uartecho.h
 *
 *  Created on: Oct 10, 2020
 *      Author: joaquin.alvidrez
 */

#ifndef INC_UARTECHO_H_
#define INC_UARTECHO_H_

#include <array>
#include <cstdint>
#include "stm32f4xx_hal.h"

class Uart_echo
{
public:
	Uart_echo(UART_HandleTypeDef &h_uart);
	void receive();
	void transmit();
	virtual ~Uart_echo();

private:
	void convert_to_uppercase();
	std::array<uint8_t, 100u> bytes{0u};
	UART_HandleTypeDef &h_uart;
	size_t num_bytes_received{0u};
};

#endif /* INC_UARTECHO_H_ */
