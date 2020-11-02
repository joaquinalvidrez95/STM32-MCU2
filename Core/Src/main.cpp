#include <cstring>
#include <cstdint>

#include "stm32f4xx_hal.h"
#include "stm32f4xx_it.h"
#include "handles.h"
#include "nucleo_board.h"
#include "stm32f446xx.h"

static void system_clock_config(void);

int main(void)
{
  HAL_Init();
  system_clock_config();
  TIM_HandleTypeDef h_timer_6{0};
  handles::init_timer_6(h_timer_6);
  interrupt::set_timer_handle(&h_timer_6);
  Nucleo_board::init_led();
  HAL_TIM_Base_Start_IT(&h_timer_6);

  for (;;)
  {
  }

  return 0;
}

static void system_clock_config(void)
{
}
