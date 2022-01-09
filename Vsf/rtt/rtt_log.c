/*
 * rtt_log.c
 *
 *  Created on: 2018-5-14
 *      Author: rongjiayu
 */

#include "rtt_log.h"
#include "SEGGER_RTT.h"
#include <string.h>

void _sbrk(void)
{

}

void rtt_log_puts(uint8_t *data, uint32_t length)
{
    SEGGER_RTT_Write(0, data, length);
}

#define RTT_JS_CHANNEL         1
#define RTT_JS_CHANNEL_MAX     4

static int  rtt_log_scope_channel[4];
static char JS_RTT_UpBuffer[128];    // J-Scope RTT Buffer

void rtt_log_scope_init(void)
{
	SEGGER_RTT_ConfigUpBuffer(0, "RTTUP", NULL, 0, SEGGER_RTT_MODE_NO_BLOCK_SKIP);
	SEGGER_RTT_ConfigDownBuffer(0, "RTTDOWN", NULL, 0, SEGGER_RTT_MODE_NO_BLOCK_SKIP);
}

void rtt_log_scope_channel_set(int channel, int value)
{
	if (channel < dimof(rtt_log_scope_channel))
		rtt_log_scope_channel[channel] = value;
}

void rtt_log_scope_event_loop(void)
{
	SEGGER_RTT_Write(RTT_JS_CHANNEL, rtt_log_scope_channel, sizeof(rtt_log_scope_channel));
}
