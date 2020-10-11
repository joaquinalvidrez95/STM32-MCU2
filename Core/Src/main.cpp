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

//  const char *msg = "What's up man.\n";
//  HAL_UART_Transmit(&gh_uart2, const_cast<uint8_t *>(reinterpret_cast<const uint8_t *>(msg)), strlen(msg), HAL_MAX_DELAY);

  Uart_echo echo{gh_uart2};
  interrupt::set_uart_handle(&gh_uart2, std::bind(&Uart_echo::byte_received_callback, echo));

  for (;;)
  {
    echo.work(Mechanism::interrupt);
  }

  return 0;
}

static void system_clock_config(void)
{
}
