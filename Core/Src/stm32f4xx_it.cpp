#include "stm32f4xx_it.h"

#include "stm32f4xx_hal.h"
#include "stm32f446xx.h"

namespace interrupt
{
    static TIM_HandleTypeDef *gph_timer = nullptr;
    void set_timer_handle(TIM_HandleTypeDef *ph)
    {
        gph_timer = ph;
    }

} // namespace interrupt

extern "C"
{
    void SysTick_Handler(void)
    {
        HAL_IncTick();
        HAL_SYSTICK_IRQHandler();
    }

    void TIM6_DAC_IRQHandler(void)
    {
        if (nullptr != interrupt::gph_timer)
        {
            HAL_TIM_IRQHandler(interrupt::gph_timer);
        }
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}
