#include "stm32f4xx_it.h"

#include <functional>

#include "stm32f4xx_hal.h"

namespace interrupt
{
    static UART_HandleTypeDef *gph_uart = nullptr;
    static std::function<void()> g_rx_callback{};
    void set_uart_handle(UART_HandleTypeDef *ph_uart, std::function<void()> rx_callback)
    {
        gph_uart = ph_uart;
        g_rx_callback = rx_callback;
    }
} // namespace interrupt

extern "C" void SysTick_Handler(void)
{
    HAL_IncTick();
    HAL_SYSTICK_IRQHandler();
}

extern "C" void USART2_IRQHandler(void)
{
    if (nullptr != interrupt::gph_uart)
    {
        HAL_UART_IRQHandler(interrupt::gph_uart);
    }
}

extern "C" void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (interrupt::g_rx_callback)
    {
        interrupt::g_rx_callback();
    }
}
