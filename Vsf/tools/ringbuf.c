/*
 * ringbuf.c
 *
 *  Created on: 2018年7月27日
 *      Author: rongjiayu
 */
#include "ringbuf.h"

#include <string.h>

int ringbuf_init (ringbuf_t *p_obj, void *p_mem, uint16_t mem_size)
{
	if ((NULL == p_mem) || (0 == mem_size)) {
		return -1;
	}

	p_obj->p_buf    = p_mem;
	p_obj->buf_size = mem_size;
	p_obj->cur_head = 0;
	p_obj->cur_tail = 0;
	return 0;
}

int ringbuf_puts (ringbuf_t *p_obj, const uint8_t *p_data, int length)
{
    uint16_t size, mask, write_position;

    mask = p_obj->buf_size - 1;

    /* whether has enough space */
    size = p_obj->buf_size - (p_obj->cur_tail - p_obj->cur_head);
    if (size == 0)
        return 0;           /* no space */
    if (size < length)
    	length = size;   /* drop some data */

    write_position = (p_obj->cur_tail & mask);
    if (p_obj->buf_size - write_position> length) {
        /* read_index - write_index = empty space */
        memcpy(&p_obj->p_buf[write_position], p_data, length);
    }
    else {
        memcpy(&p_obj->p_buf[write_position], p_data,
        		p_obj->buf_size - write_position);
        memcpy(&p_obj->p_buf[0], &p_data[p_obj->buf_size - write_position],
        		length - (p_obj->buf_size - write_position));
    }
    p_obj->cur_tail += length;

	return length;
}

int ringbuf_gets (ringbuf_t *p_obj, uint8_t *p_data, int length)
{
	uint16_t size, mask, read_position;

	/* whether has enough data  */
	mask = p_obj->buf_size - 1;
	size = p_obj->cur_tail - p_obj->cur_head;

	if (size == 0)
		return 0;       /* no data */
	if (size < length)
		length = size;  /* less data */

	read_position = p_obj->cur_head & mask;
	if (p_obj->buf_size - read_position >= length)
	{
		/* copy all of data */
		memcpy(p_data, &p_obj->p_buf[read_position], length);
	}
	else
	{
		/* copy first and second */
		memcpy(p_data, &p_obj->p_buf[read_position],
				p_obj->buf_size - read_position);
		memcpy(&p_data[p_obj->buf_size - read_position], &p_obj->p_buf[0],
				length - p_obj->buf_size + read_position);
	}
	p_obj->cur_head += length;

	return length;
}

bool ringbuf_is_empty (ringbuf_t *p_obj)
{
	return (p_obj->cur_head == p_obj->cur_tail);
}

