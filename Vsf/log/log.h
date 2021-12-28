/*
 * log.h
 *
 *  Created on: 2014-3-5
 *      Author: Ming180
 */

#ifndef LOG_H_
#define LOG_H_

#include "app_type.h"

#define LOG_EN              1
#define ASSERT_EN           0

#if LOG_EN
    #define LOG(fmt, ...)    log_printf(fmt, ##__VA_ARGS__)
#else
    #define LOG(fmt, ...)    ((void)0)
#endif

#if ASSERT_EN
    #define STRIPPATH(s)\
        (sizeof(s) > 2 && (s)[sizeof(s)-2] == '/' ? (s) + sizeof(s) - 1 : \
        sizeof(s) > 3 && (s)[sizeof(s)-3] == '/' ? (s) + sizeof(s) - 2 : \
        sizeof(s) > 4 && (s)[sizeof(s)-4] == '/' ? (s) + sizeof(s) - 3 : \
        sizeof(s) > 5 && (s)[sizeof(s)-5] == '/' ? (s) + sizeof(s) - 4 : \
        sizeof(s) > 6 && (s)[sizeof(s)-6] == '/' ? (s) + sizeof(s) - 5 : \
        sizeof(s) > 7 && (s)[sizeof(s)-7] == '/' ? (s) + sizeof(s) - 6 : \
        sizeof(s) > 8 && (s)[sizeof(s)-8] == '/' ? (s) + sizeof(s) - 7 : \
        sizeof(s) > 9 && (s)[sizeof(s)-9] == '/' ? (s) + sizeof(s) - 8 : \
        sizeof(s) > 10 && (s)[sizeof(s)-10] == '/' ? (s) + sizeof(s) - 9 : \
        sizeof(s) > 11 && (s)[sizeof(s)-11] == '/' ? (s) + sizeof(s) - 10 : (s))

    #define __JUSTFILE__ STRIPPATH(__FILE__)

    #define ASSERT(e)       ((e) ? (void)0 : log_assert(__JUSTFILE__, __LINE__))
#else
    #define ASSERT(e)       ((void)0)
#endif

int log_init(bool (*_puts)(uint8_t *str, uint16_t n));
// int log_puts(char *s, int len);
int log_printf(char *fmt, ...);
int log_stream_channel(int16_t *channel, int16_t len);
void log_hexdump(uint8_t *data, uint32_t size);

void log_assert(const char *p_file, int line);

#endif /* LOG_H_ */
