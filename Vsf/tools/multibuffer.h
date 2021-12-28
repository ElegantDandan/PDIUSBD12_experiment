/*
 * multibuffer.h
 *
 *  Created on: 2016-5-4
 *      Author: Ming180
 */

#ifndef MULTIBUFFER_H_
#define MULTIBUFFER_H_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
	uint32_t num_items;	// 有效缓冲数量
	uint32_t head;
	uint32_t depth;		// 多缓冲深度
	uint32_t size;		// 单缓冲区长度
	uint8_t *buffer;
} multibuffer_t;

bool  multibuffer_init(multibuffer_t *obj, void *buffer, uint32_t depth, uint32_t size);
bool  multibuffer_clear(multibuffer_t *obj);
void *multibuffer_front(multibuffer_t *obj);
void *multibuffer_tail(multibuffer_t *obj);
bool  multibuffer_append(multibuffer_t *obj);
bool  multibuffer_release(multibuffer_t *obj);
bool  multibuffer_is_empty(multibuffer_t *obj);

bool multibuffer_push(multibuffer_t *obj, void *item);
bool multibuffer_pop (multibuffer_t *obj, void *item);

#endif // MULTIBUFFER_H_
