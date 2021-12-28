/*
 * ringbuf.h
 *
 *  Created on: 2018年7月27日
 *      Author: rongjiayu
 */

#ifndef RINGBUF_H_
#define RINGBUF_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct {
	uint8_t *p_buf;
	uint16_t buf_size;
	uint16_t cur_head;
	uint16_t cur_tail;
} ringbuf_t;

#define RINGBUF_DEFINE(_name, _buf_size) \
			uint8_t    __##_name##_mem[_buf_size]; \
			ringbuf_t  _name = { .p_buf = __##_name##_mem, .buf_size = _buf_size, .cur_head = 0, .cur_tail = 0 };


#define RINGBUF_DEFINE_STATIC(_name, _buf_size) \
			static uint8_t    __##_name##_mem[_buf_size]; \
			static ringbuf_t  _name = { .p_buf = __##_name##_mem, .buf_size = _buf_size, .cur_head = 0, .cur_tail = 0 };

int ringbuf_init (ringbuf_t *p_obj, void *p_mem, uint16_t mem_size);

/*
 * 返回实际写入数据长度
 */
int ringbuf_puts (ringbuf_t *p_obj, const uint8_t *p_data, int data_size);

/*
 * p_outbuf    取出数据存放内存
 * outbuf_size 取出数据最大长度
 * 返回实际取出数据长度
 */
int ringbuf_gets (ringbuf_t *p_obj, uint8_t *p_data, int length);

bool ringbuf_is_empty (ringbuf_t *p_obj);

#endif /* RINGBUF_H_ */
