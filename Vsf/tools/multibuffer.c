/*
 * multibuffer.c
 *
 *  Created on: 2016-5-4
 *      Author: Ming180
 */

#include "multibuffer.h"

bool multibuffer_init(multibuffer_t *obj, void *buffer, uint32_t depth, uint32_t size)
{
	if (buffer == NULL)
		return false;

	obj->num_items = 0;
	obj->head      = 0;
	obj->depth     = depth;		// 多缓冲深度
	obj->size      = size;		// 单缓冲区长度
	obj->buffer    = buffer;

	return true;
}

// clear - removes all points from the curve
bool multibuffer_clear(multibuffer_t *obj)
{
	obj->num_items = 0;
	obj->head = 0;

	return true;
}

void *multibuffer_tail(multibuffer_t *obj)
{
	// determine position of new item
	uint32_t tail = obj->head + obj->num_items;

	if (tail >= obj->depth) {
		tail -= obj->depth;
	}

	// no room and return false
	if (obj->num_items == obj->depth) {
		return NULL;
	}

	tail *= obj->size;

	return &obj->buffer[tail];
}

// add - adds an item to the buffer.  returns TRUE if successfully added
bool multibuffer_append(multibuffer_t *obj)
{
	// no room and return false
	if (obj->num_items == obj->depth) {
		return false;
	}

	// increment number of items
	obj->num_items++;

    return true;
}

// get - returns the next value in the buffer
void *multibuffer_front(multibuffer_t *obj)
{
	void *result;

	// return zero if buffer is empty
	if (obj->num_items == 0)
		return NULL;

	// get next value in buffer
	result = &obj->buffer[obj->head * obj->size];

	// return item
	return result;
}

bool multibuffer_release(multibuffer_t *obj)
{
	// return zero if buffer is empty
	if (obj->num_items == 0) {
		return false;
	}

	// increment to next point
	obj->head++;
	if (obj->head >= obj->depth) {
		obj->head = 0;
	}

	// reduce number of items
	obj->num_items--;

	return true;
}

bool multibuffer_is_empty(multibuffer_t *obj)
{
	// return zero if buffer is empty
	if (obj->num_items == 0) {
		return true;
	}

	return false;
}

bool multibuffer_push(multibuffer_t *obj, void *item)
{
	// determine position of new item
	uint32_t tail = obj->head + obj->num_items;

	if (tail >= obj->depth) {
		tail -= obj->depth;
	}

	// no room and return false
	if (obj->num_items == obj->depth) {
		return false;
	}

	tail *= obj->size;
	memcpy(&obj->buffer[tail], item, obj->size);

	// increment number of items
	obj->num_items++;

	return true;
}

bool multibuffer_pop(multibuffer_t *obj, void *item)
{
	void *buff;

	// return zero if buffer is empty
	if (obj->num_items == 0)
		return false;

	// get next value in buffer
	buff = &obj->buffer[obj->head * obj->size];

	memcpy(item, buff, obj->size);

	// increment to next point
	obj->head++;
	if (obj->head >= obj->depth) {
		obj->head = 0;
	}

	// reduce number of items
	obj->num_items--;

	return true;
}
