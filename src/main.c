/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f1xx.h"
#include <string.h>

int main(void)
{
	HAL_Init();

	// GPIO for buttons Init
	GPIO_InitTypeDef buttonGpio;
	buttonGpio.Mode = GPIO_MODE_OUTPUT_PP;
	buttonGpio.Pin = GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | \
					 GPIO_PIN_4 | GPIO_PIN_5;
	buttonGpio.Pull = GPIO_NOPULL;
	buttonGpio.Speed = GPIO_SPEED_HIGH;

	__HAL_RCC_GPIOA_CLK_ENABLE();
	HAL_GPIO_Init(GPIOA, &buttonGpio);

	// UART Port init
	GPIO_InitTypeDef txGpio;
	txGpio.Mode = GPIO_MODE_AF_PP;
	txGpio.Pin = GPIO_PIN_10;
	txGpio.Pull = GPIO_NOPULL;
	txGpio.Speed = GPIO_SPEED_HIGH;

	__HAL_RCC_GPIOB_CLK_ENABLE();
	HAL_GPIO_Init(GPIOB, &txGpio);

	GPIO_InitTypeDef rxGpio;
	rxGpio.Mode = GPIO_MODE_AF_INPUT;
	rxGpio.Pin = GPIO_PIN_11;
	rxGpio.Pull = GPIO_PULLUP;
	rxGpio.Speed = GPIO_SPEED_HIGH;

	HAL_GPIO_Init(GPIOB, &rxGpio);

	// UART init
	UART_HandleTypeDef huart1;
	huart1.Instance = USART3;
	huart1.Init.BaudRate 	 = 19200;
	huart1.Init.HwFlowCtl	 = UART_HWCONTROL_NONE;
	huart1.Init.Mode 		 = UART_MODE_TX_RX;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	huart1.Init.Parity 		 = UART_PARITY_NONE;
	huart1.Init.StopBits 	 = UART_STOPBITS_2;
	huart1.Init.WordLength	 = UART_WORDLENGTH_8B;

	__HAL_RCC_USART3_CLK_ENABLE();
	HAL_UART_MspInit(&huart1);
	HAL_UART_Init(&huart1);

	char message[32] = "Remember me!";
	HAL_UART_Transmit(&huart1, message, strlen(message), 1000);

	for(;;) {
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);
		HAL_Delay(70);
	}

}
