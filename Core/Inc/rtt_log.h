/*
 * rtt_log.h
 *
 *  Created on: 2018-5-14
 *      Author: rongjiayu
 */

#ifndef RTT_H_
#define RTT_H_

#include "app_type.h"

void rtt_log_puts(uint8_t *data, uint32_t length);
void rtt_log_scope_init(void);
void rtt_log_scope_channel_set(int channel, int value);
void rtt_log_scope_event_loop(void);

#endif /* RTT_LOG_H_ */
