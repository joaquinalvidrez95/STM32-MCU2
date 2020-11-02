#include "stm32f4xx_hal.h"
#include "stm32f446xx.h"
#include "stm32f4xx_hal_gpio_ex.h"

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

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *ph)
{
  __HAL_RCC_TIM6_CLK_ENABLE();

  HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
  HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 15u, 0u);
}