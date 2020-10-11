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
#include "mechanism.h"

class Uart_echo
{
public:
	Uart_echo(UART_HandleTypeDef &h_uart);
	void work(Mechanism mechanism);
	void byte_received_callback();
	virtual ~Uart_echo();

private:
	void receive(Mechanism mechanism);
	void transmit();
	void convert_to_uppercase();

	UART_HandleTypeDef &h_uart;
	std::array<uint8_t, 100u> bytes{0u};
	size_t num_bytes_received{0u};
	bool is_rx_done{false};

	static constexpr char final_character{'\r'};
};

#endif /* INC_UARTECHO_H_ */
