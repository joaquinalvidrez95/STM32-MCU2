/*
 * Uartecho.cpp
 *
 *  Created on: Oct 10, 2020
 *      Author: joaquin.alvidrez
 */

#include "uartecho.h"

#include <cctype>
#include <iterator>

#include "stm32f4xx_hal.h"

Uart_echo::Uart_echo(UART_HandleTypeDef &h_uart) : h_uart{h_uart}
{
}

Uart_echo::~Uart_echo()
{
	// TODO Auto-generated destructor stub
}

void Uart_echo::receive()
{
	for (num_bytes_received = 0u; num_bytes_received < bytes.size(); num_bytes_received++)
	{
		HAL_UART_Receive(&this->h_uart, &this->bytes.at(num_bytes_received), sizeof(uint8_t), HAL_MAX_DELAY);
		if ('\r' == static_cast<char>(bytes.at(num_bytes_received)))
		{
			break;
		}
	}
}

void Uart_echo::transmit()
{
	convert_to_uppercase();
	HAL_UART_Transmit(&this->h_uart, this->bytes.data(), this->num_bytes_received, HAL_MAX_DELAY);
}

void Uart_echo::convert_to_uppercase()
{
	const auto end = bytes.begin() + this->num_bytes_received;
	for (auto it = bytes.begin(); it != end; it++)
	{
		*it = std::toupper(*it);
	}
}
