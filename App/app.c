/*
 * app.c
 *
 *  Created on: 2021-12-26
 *      Author: dandan
 */

#include <stdio.h>

#include "stm32f1xx_hal.h"
#include "app_type.h"
#include "log.h"
#include "led.h"
#include "SEGGER_RTT.h"

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
	static uint32_t tick, tick2, tick3;
	static float basic_tick = 0.0f;
	char buf[128];

	if (sys_tickclk - tick >= 1) {
		tick = sys_tickclk;
		// LOG("hello world, 中文测试 sys_tickclk = %d\n", sys_tickclk);

		tick2++;
		tick3 += 2;

		if (tick2 > 1000)
			tick2 = 0;

		if (tick3 > 500)
			tick3 = 0;

		basic_tick += 0.000001f;

		sprintf(buf, "X, %f, %d, %d\r\n",  basic_tick, tick2, tick3);

		SEGGER_RTT_SetTerminal(0);
		SEGGER_RTT_WriteString(0, buf);
	}
}
