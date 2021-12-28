/*
 * dbuffer.h
 *
 *  Created on: 2016-5-4
 *      Author: Ming180
 */

#ifndef DBUFFER_H_
#define DBUFFER_H_

#include <stdint.h>

typedef struct {
	uint16_t size;
	uint8_t  index;
	uint8_t *buffer[2];
} dbuffer_t;

void dbuffer_init(dbuffer_t *obj, uint8_t *buffer1, uint8_t *buffer2, uint16_t size);
void dbuffer_clear(dbuffer_t *obj);
void dbuffer_switch_buffer(dbuffer_t *obj);
uint8_t *dbuffer_get_current(dbuffer_t *obj);
uint8_t *dbuffer_get_next(dbuffer_t *obj);

#endif // DBUFFER_H_
