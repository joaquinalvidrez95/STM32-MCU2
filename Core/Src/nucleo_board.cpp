/*
 * Nucleoboard.cpp
 *
 *  Created on: Nov 1, 2020
 *      Author: joaquin.alvidrez
 */

#include "nucleo_board.h"

#include "stm32f4xx_hal.h"

Nucleo_board::Nucleo_board()
{
	// TODO Auto-generated constructor stub
}

Nucleo_board::~Nucleo_board()
{
	// TODO Auto-generated destructor stub
}

void Nucleo_board::init_led()
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef h_led{0};
	h_led.Pin = GPIO_PIN_5;
	h_led.Mode = GPIO_MODE_OUTPUT_PP;
	h_led.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &h_led);
}
