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
		for (num_bytes_received = 0u; num_bytes_received < bytes.size(); num_bytes_received++)
		{
			HAL_UART_Receive(&this->h_uart, &this->bytes.at(num_bytes_received), sizeof(uint8_t), HAL_MAX_DELAY);
			if (final_character == static_cast<char>(bytes.at(num_bytes_received)))
			{
				break;
			}
		}
	}
	else
	{
		this->num_bytes_received = 0u;
		while (!is_rx_done)
		{
			HAL_UART_Receive_IT(&h_uart, &this->bytes.at(num_bytes_received), sizeof(uint8_t));
		}
	}
}

void Uart_echo::transmit()
{
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

void Uart_echo::byte_received_callback()
{
	if (final_character == static_cast<char>(bytes.at(num_bytes_received)))
	{
		this->is_rx_done = true;
	}
	this->num_bytes_received++;
}
