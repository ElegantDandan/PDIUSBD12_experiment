/*
 * app.c
 *
 *  Created on: 2021-12-26
 *      Author: dandan
 */

#include "stm32f1xx_hal.h"
#include "app_type.h"
#include "log.h"
#include "led.h"

extern volatile uint32_t sys_tickclk;

// event loop 100Hz
void app_event_loop_slow(void)
{
	extern volatile bool sys_startup;
	static uint32_t div2 = 0;

	if (++div2 & 0x01) {
		led_event_loop();
	}

	if (sys_startup) {
	}
}

void app_main(void)
{
	static uint32_t tick;

	if (sys_tickclk - tick >= 1000) {
		tick = sys_tickclk;
		// LOG("hello world, sys_tickclk = %d\n", sys_tickclk);
	}
}
