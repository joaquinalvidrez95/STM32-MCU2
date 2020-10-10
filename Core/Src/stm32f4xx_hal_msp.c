#include "stm32f4xx_hal.h"

void HAL_MspInit(void)
{
  /* Sets up the priority grouping of the ARM Cortex MX Processor */
  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  /* Enables the required system exceptions */
  SCB->SHCSR |= 0b111u << 16u;

  /* Configures the priority for the system exceptions */
  HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0u, 0u);
  HAL_NVIC_SetPriority(BusFault_IRQn, 0u, 0u);
  HAL_NVIC_SetPriority(UsageFault_IRQn, 0u, 0u);
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
  /* Enables clock for USART2 peripheral */
  __HAL_RCC_USART2_CLK_ENABLE();

  /* Does the pin muxing cfgs */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  GPIO_InitTypeDef pin_cfg = {0};
  pin_cfg.Pin = GPIO_PIN_2;
  pin_cfg.Mode = GPIO_MODE_AF_PP;
  pin_cfg.Speed = GPIO_SPEED_FREQ_LOW;
  pin_cfg.Pull = GPIO_PULLUP;
  pin_cfg.Alternate = GPIO_AF7_USART2;
  /* Tx */
  HAL_GPIO_Init(GPIOA, &pin_cfg);

  /* Rx */
  pin_cfg.Pin = GPIO_PIN_3;
  HAL_GPIO_Init(GPIOA, &pin_cfg);

  /* Enables the IRQ ans sets up the priority */
  HAL_NVIC_EnableIRQ(USART2_IRQn);
  HAL_NVIC_SetPriority(USART2_IRQn, 15u, 0u);
}
