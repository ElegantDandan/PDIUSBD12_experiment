/*
 * dbuffer.c
 *
 *  Created on: 2016-5-4
 *      Author: Ming180
 */

#include "dbuffer.h"

void dbuffer_init(dbuffer_t *obj, uint8_t *buffer1, uint8_t *buffer2, uint16_t size)
{
	obj->size      = size;
	obj->index     = 0;
	obj->buffer[0] = buffer1;
	obj->buffer[1] = buffer2;
}

void dbuffer_clear(dbuffer_t *obj)
{
	obj->index = 0;
}

void dbuffer_switch_buffer(dbuffer_t *obj)
{
	obj->index = (obj->index + 1) & 0x01;
}

uint8_t *dbuffer_get_current(dbuffer_t *obj)
{
	return obj->buffer[obj->index];
}

uint8_t *dbuffer_get_next(dbuffer_t *obj)
{
	return obj->buffer[(obj->index + 1) & 0x01];
}
