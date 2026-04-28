/*
 * Copyright (c) Quectel Wireless Solution, Co., Ltd.All Rights Reserved.
 *  
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *  
 *     http://www.apache.org/licenses/LICENSE-2.0
 *  
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __HELIOS_RINGBUF_H__
#define __HELIOS_RINGBUF_H__

#ifdef __cplusplus
extern "C" {
#endif



typedef unsigned long long u64;

typedef struct helios_ring_buf_struct {
    unsigned int size;
    u64  rpos;
    u64  wpos;
    unsigned char *data;
}helios_ring_buf_t;



helios_ring_buf_t *helios_rb_create(unsigned int size);

void helios_rb_destroy(helios_ring_buf_t **rb);

unsigned int helios_rb_is_empty(helios_ring_buf_t *rb);

unsigned int helios_rb_is_full(helios_ring_buf_t *rb);

unsigned int helios_rb_data_len(helios_ring_buf_t *rb);

unsigned int helios_rb_free_space(helios_ring_buf_t *rb);

unsigned int helios_rb_write(helios_ring_buf_t *rb, unsigned char *data, unsigned int len);

unsigned int helios_rb_read(helios_ring_buf_t *rb, unsigned char *data, unsigned int len);

void helios_rb_clear(helios_ring_buf_t *rb);

#ifdef __cplusplus
} /*"C" */
#endif


#endif
