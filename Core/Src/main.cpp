#include <cstring>
#include <cstdint>

#include "stm32f4xx_hal.h"
#include "uartecho.h"

static void system_clock_config(void);
static void init_uart(UART_HandleTypeDef *ph);
static void handle_error(void);

static UART_HandleTypeDef gh_uart2 = {0};

int main(void)
{
  HAL_Init();
  system_clock_config();
  init_uart(&gh_uart2);

  Uart_echo echo{gh_uart2};

  for (;;)
  {
    echo.receive();
    echo.transmit();
  }

  return 0;
}

static void system_clock_config(void)
{
}

static void init_uart(UART_HandleTypeDef *ph)
{
  ph->Instance = USART2;
  ph->Init.BaudRate = 115200u;
  ph->Init.WordLength = UART_WORDLENGTH_8B;
  ph->Init.StopBits = UART_STOPBITS_1;
  ph->Init.Parity = UART_PARITY_NONE;
  ph->Init.HwFlowCtl = UART_HWCONTROL_NONE;
  ph->Init.Mode = UART_MODE_TX_RX;

  if (HAL_OK != HAL_UART_Init(ph))
  {
    handle_error();
  }
}

static void handle_error(void)
{
  for (;;)
  {
  }
}
