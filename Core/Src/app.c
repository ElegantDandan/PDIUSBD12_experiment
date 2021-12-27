/*
 * app.c
 *
 *  Created on: 2021-12-26
 *      Author: dandan
 */

#include "stm32f1xx_hal.h"
#include "app_type.h"
#include "log.h"

void _sbrk(void)
{

}

void app_main(void)
{
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
	HAL_Delay(500);
	LOG("hello world\n");
}
