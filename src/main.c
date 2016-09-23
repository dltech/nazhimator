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

#define START_PHRASE "Remember me!"
#define MESSAGE_SIZE  16


void pusher(uint8_t *message)
{
/* This function reads the message and pushes the buttons according to the
 * active bits.
 */
	int i;

	for( i=1 ; i<MESSAGE_SIZE ; ++i) {
		if( message[i] & 0x01 )
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
		if( message[i] & 0x02 )
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
		if( message[i] & 0x04 )
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
		if( message[i] & 0x08 )
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);

		HAL_Delay(message[0]); 							 	// delay before = delay in message
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2 | GPIO_PIN_3 \
				          | GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_RESET);
		HAL_Delay( message[0] / 2 ); 						// delay after = delay / 2 due to economy of time
	}
}


int main(void)
{
	HAL_Init();
	HAL_Delay(300);

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
	huart1.Init.BaudRate 	 = 57600;
	huart1.Init.HwFlowCtl	 = UART_HWCONTROL_NONE;
	huart1.Init.Mode 		 = UART_MODE_TX_RX;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	huart1.Init.Parity 		 = UART_PARITY_NONE;
	huart1.Init.StopBits 	 = UART_STOPBITS_2;
	huart1.Init.WordLength	 = UART_WORDLENGTH_8B;
	__HAL_RCC_USART3_CLK_ENABLE();
	HAL_UART_MspInit(&huart1);
	HAL_UART_Init(&huart1);

	// Transmit start phrase (device works)
	char msg[32] = START_PHRASE;
	HAL_UART_Transmit(&huart1, msg, strlen(msg), 1000);

	uint8_t message[MESSAGE_SIZE];
	int status = 0xff;

	for(;;) {
		status = HAL_UART_Receive(&huart1, message, MESSAGE_SIZE, 300); // read the message throw UART
		if (status == HAL_OK) pusher(message);							// push the buttons according to the message (if any)
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);							// blinking led just for fun
	}

}
