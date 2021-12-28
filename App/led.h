/*
 * led.h
 *
 *  Created on: 2016-12-21
 *      Author: Ming180
 */

#ifndef LED_H_
#define LED_H_

#include "app_type.h"

#define LED_MODE_OFF			0
#define LED_MODE_ON				1
#define LED_MODE_FLASH_SLOW		2
#define LED_MODE_FLASH_FAST		3
#define LED_MODE_FLASH_1		4
#define LED_MODE_FLASH_2		5
#define LED_MODE_FLASH_3		6
#define LED_MODE_FLASH_4		7
#define LED_MODE_FLASH_5		8
#define LED_MODE_FLASH_6		9
#define LED_MODE_POWER_0		10
#define LED_MODE_POWER_1		11
#define LED_MODE_POWER_2		12
#define LED_MODE_POWER_3		13
#define LED_MODE_POWER_4		14
#define LED_MODE_FLASH_FAST2	15

#define LED_MODE_FLASH_ERR		LED_MODE_FLASH_4

#define LED_TYPE_STATUS			0

#define LED_Y					0
#define LED_B					1
#define LED_R					2

void led_works(void);
void led_set_flash_mode(uint8_t index, uint8_t mode);
void led_event_loop(void);

#endif // LED_H_
