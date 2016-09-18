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
			

int main(void)
{
	HAL_Init();
	GPIO_InitTypeDef buttonGpio;
	buttonGpio.Mode = GPIO_MODE_OUTPUT_PP;
	buttonGpio.Pin = GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | \
					 GPIO_PIN_4 | GPIO_PIN_5;
	buttonGpio.Pull = GPIO_NOPULL;
	buttonGpio.Speed = GPIO_SPEED_HIGH;

	__HAL_RCC_GPIOA_CLK_ENABLE();
	HAL_GPIO_Init(GPIOA, &buttonGpio);

	for(;;) {
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);
		HAL_Delay(70);
	}

}
