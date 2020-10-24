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
#include "mechanism.h"

Uart_echo::Uart_echo(UART_HandleTypeDef &h_uart) : h_uart{h_uart}
{
}

Uart_echo::~Uart_echo()
{
	// TODO Auto-generated destructor stub
}

void Uart_echo::work(Mechanism mechanism)
{
	receive(mechanism);
	convert_to_uppercase();
	transmit();
}

void Uart_echo::receive(Mechanism mechanism)
{
	if (Mechanism::polling == mechanism)
	{
		for (num_bytes_received = 0u; num_bytes_received < rx_tx_buf.size(); num_bytes_received++)
		{
			HAL_UART_Receive(&this->h_uart, &this->rx_tx_buf.at(num_bytes_received), sizeof(uint8_t), HAL_MAX_DELAY);
			if (final_character == static_cast<char>(rx_tx_buf.at(num_bytes_received)))
			{
				break;
			}
		}
	}
	else
	{
		for (num_bytes_received = 0u; num_bytes_received < rx_tx_buf.size();)
		{
			HAL_UART_Receive_IT(&this->h_uart, &this->rx_tx_buf.at(num_bytes_received), sizeof(uint8_t));
			while (this->h_uart.RxState != HAL_UART_STATE_READY)
			{
			}
			if (final_character == static_cast<char>(rx_tx_buf.at(num_bytes_received - 1u)))
			{
				break;
			}
		}
	}
}

void Uart_echo::transmit()
{
	HAL_UART_Transmit(&this->h_uart, const_cast<uint8_t *>(this->rx_tx_buf.data()), this->num_bytes_received, HAL_MAX_DELAY);
}

void Uart_echo::convert_to_uppercase()
{
	const auto end = rx_tx_buf.begin() + this->num_bytes_received;
	for (auto it = rx_tx_buf.begin(); it != end; it++)
	{
		*it = std::toupper(*it);
	}
}

void Uart_echo::byte_received_callback()
{
	num_bytes_received++;
}
