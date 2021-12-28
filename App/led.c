/*
 * led.c
 *
 *  Created on: 2016-12-21
 *      Author: Ming180
 */

#include "led.h"
#include "gpio.h"

struct led_seq_t {
	uint8_t const *bytes;
	uint8_t len;
};

// LED Control Block
struct led_cb_t {
	const struct  led_seq_t *seq;
	uint8_t bit_index;
	uint8_t byte_index;
	uint8_t mode;
};

static const uint8_t led_seq_off[]    = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static const uint8_t led_seq_on[]     = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
static const uint8_t led_seq_slow[]   = {0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF};
static const uint8_t led_seq_fast[]   = {0x00, 0xFF};
static const uint8_t led_seq_flash1[] = {0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static const uint8_t led_seq_flash2[] = {0xF0, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static const uint8_t led_seq_flash3[] = {0xF0, 0x00, 0xF0, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static const uint8_t led_seq_flash4[] = {0xF0, 0x00, 0xF0, 0x00, 0xF0, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static const uint8_t led_seq_flash5[] = {0xF0, 0x00, 0xF0, 0x00, 0xF0, 0x00, 0xF0, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static const uint8_t led_seq_flash6[] = {0xF0, 0x00, 0xF0, 0x00, 0xF0, 0x00, 0xF0, 0x00, 0xF0, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static const uint8_t led_seq_power0[] = {0x00, 0xFF};
static const uint8_t led_seq_power1[] = {0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static const uint8_t led_seq_power2[] = {0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static const uint8_t led_seq_power3[] = {0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static const uint8_t led_seq_power4[] = {0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static const uint8_t led_seq_fast2[]  = {0x0F};

static const struct led_seq_t led_seq_list[] = {
	{led_seq_off,    dimof(led_seq_off)   }, 	// LED_MODE_OFF
	{led_seq_on,     dimof(led_seq_on)    },	// LED_MODE_ON
	{led_seq_slow,   dimof(led_seq_slow)  },	// LED_MODE_FLASH_SLOW
	{led_seq_fast,   dimof(led_seq_fast)  },	// LED_MODE_FLASH_FAST
	{led_seq_flash1, dimof(led_seq_flash1)},	// LED_MODE_FLASH_1
	{led_seq_flash2, dimof(led_seq_flash2)},	// LED_MODE_FLASH_2
	{led_seq_flash3, dimof(led_seq_flash3)},	// LED_MODE_FLASH_3
	{led_seq_flash4, dimof(led_seq_flash4)},	// LED_MODE_FLASH_4
	{led_seq_flash5, dimof(led_seq_flash5)},	// LED_MODE_FLASH_5
	{led_seq_flash6, dimof(led_seq_flash6)},	// LED_MODE_FLASH_6
	{led_seq_power0, dimof(led_seq_power0)},	// LED_MODE_POWER_0
	{led_seq_power1, dimof(led_seq_power2)},	// LED_MODE_POWER_1
	{led_seq_power2, dimof(led_seq_power3)},	// LED_MODE_POWER_2
	{led_seq_power3, dimof(led_seq_power3)},	// LED_MODE_POWER_3
	{led_seq_power4, dimof(led_seq_power4)},	// LED_MODE_POWER_4
	{led_seq_fast2,  dimof(led_seq_fast2) },	// LED_MODE_FLASH_FAST2
};

static struct led_cb_t led_cb_list[] = {
	{led_seq_list, 0, 0, LED_MODE_OFF},
	{led_seq_list, 0, 0, LED_MODE_OFF},
	{led_seq_list, 0, 0, LED_MODE_OFF},
};

uint8_t led_enable_flag = 1;

static void led_output(uint8_t index, uint8_t state)
{
	switch (index) {
		case 0:
			led_on(index, state);
			break;
		case 1:
		case 2:
			break;

		default:
			break;
	}
}

void led_work(uint8_t index, struct led_cb_t *cb)
{
	led_output(index, (uint8_t)(cb->seq->bytes[cb->byte_index] << cb->bit_index) & ((uint8_t)0x80));
	cb->bit_index++;

	if (cb->bit_index > 7) {
		cb->bit_index = 0;
		cb->byte_index++;
	}

	if (cb->byte_index >= cb->seq->len) {
		cb->byte_index = 0;
	}
}

void led_set_flash_mode(uint8_t index, uint8_t mode)
{
	if (index < dimof(led_cb_list)) {
		led_cb_list[index].mode = mode;
	}
}

void led_event_loop(void)
{
	uint16_t i;

	for (i = 0; i < dimof(led_cb_list); ++i) {
		led_cb_list[i].seq = &led_seq_list[led_cb_list[i].mode];
		led_work(i, &led_cb_list[i]);
	}
}
