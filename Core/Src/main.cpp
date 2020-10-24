#include <cstring>
#include <cstdint>

#include "stm32f4xx_hal.h"
#include "stm32f4xx_it.h"
#include "uartecho.h"
#include "handles.h"

static void system_clock_config(void);
static UART_HandleTypeDef gh_uart2{0};

int main(void)
{
  HAL_Init();
  system_clock_config();
  handles::init_uart(gh_uart2);

  Uart_echo echo{gh_uart2};
  interrupt::set_uart_handle(&gh_uart2, std::bind(&Uart_echo::byte_received_callback, &echo));

  for (;;)
  {
    echo.work(Mechanism::interrupt);
  }

  return 0;
}

static void system_clock_config(void)
{
}
