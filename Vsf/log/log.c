/*
 * log.c
 *
 *  Created on: 2014-3-5
 *      Author: Ming180
 */

#include "app_type.h"
#include "log.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

volatile bool log_stream_lock = false;

static char log_buffer[128];
bool (*log_puts)(uint8_t *str, uint16_t n);

int log_init(bool (*_puts)(uint8_t *str, uint16_t n))
{
	if (_puts == NULL)
		return 1;

	log_puts = _puts;
	return 0;
}

// int log_puts(char *s, int len)
// {
// 	if (log_putc == NULL)
// 		return 1;

// 	while (len--) {
// 		log_putc(*s++);
// 	}

// 	return 0;
// }

int log_printf(char *fmt, ...)
{
	int len;
	va_list ap;

	if (log_puts == NULL)
		return 1;

	va_start(ap, fmt);
	len = vsprintf(log_buffer, fmt, ap);
	log_puts((uint8_t *)log_buffer, (uint16_t)len);
	va_end(ap);

	return 0;
}

int log_stream_channel(int16_t *channel, int16_t len)
{
	uint32_t i;
	uint32_t bytes = len * 2;
	uint8_t  *txbuffer, checksum = 0;

	if (log_puts == NULL)
		return 1;

	if (bytes > (sizeof(log_buffer) - 3))
		return 1;

	txbuffer = (uint8_t *)log_buffer;

	txbuffer[0] = 0xA5;
	txbuffer[1] = 0x5A;

	memcpy(txbuffer + 2, channel, bytes);
	bytes += 2;

	for (i = 2; i < bytes; i++) {
		checksum += txbuffer[i];
	}

	txbuffer[bytes] = checksum;

	log_puts(txbuffer, bytes + 1);

	return 0;
}

void log_hexdump(uint8_t *data, uint32_t size)
{
	uint32_t i;

	for (i = 0; i < size; i++) {
//		if (i && (i % 16 == 0))
//			LOG("\r\n");

		LOG("%02X ", data[i]);
	}

	LOG("\r\n");
}

void log_assert(const char *p_file, int line)
{
    LOG("assert failed in <%s>, line %d\r\n", p_file, line);
    while(1);
}
