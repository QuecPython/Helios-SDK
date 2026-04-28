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

#include <stdio.h>
#include <assert.h>
#include "stdlib.h"
#include "string.h"	

#include "helios_ringbuf.h"

helios_ring_buf_t *helios_rb_create(unsigned int size)
{
	helios_ring_buf_t *rb = NULL;
	
	if (size <= 0) {
		return NULL;
	}

	assert(!(size&(size - 1))); // 此ringbuffer长度必须为2的n次方

	rb = malloc(sizeof(helios_ring_buf_t));
	if (NULL == rb) {
		return NULL;
	}
	memset(rb, 0, sizeof(helios_ring_buf_t));
	
	rb->data = malloc(size);
	memset(rb->data, 0, size);
	if (NULL == rb->data) {
		free(rb);
		return NULL;
	}

	rb->size = size;

	return rb;
}

void helios_rb_destroy(helios_ring_buf_t **rb)
{
	if (*rb) {
		if ((*rb)->data) {
			free((*rb)->data);
			(*rb)->data = NULL;
		}
		free(*rb);
		*rb = NULL;
	}
}

unsigned int helios_rb_is_empty(helios_ring_buf_t *rb)
{
	return (rb->wpos == rb->rpos);
}

unsigned int helios_rb_is_full(helios_ring_buf_t *rb)
{
	return (rb->size == (unsigned int)(rb->wpos-rb->rpos));
}

unsigned int helios_rb_data_len(helios_ring_buf_t *rb)
{
	return (rb->wpos - rb->rpos);
}

unsigned int helios_rb_free_space(helios_ring_buf_t *rb)
{
	return (rb->size - (rb->wpos - rb->rpos));
}

void helios_rb_clear(helios_ring_buf_t *rb)
{
	rb->wpos = rb->rpos = 0;
	memset(rb->data, 0, rb->size);
	return;
}

unsigned int helios_rb_write(helios_ring_buf_t *rb, unsigned char *data, unsigned int len)
{
	unsigned int w_size = 0, w_free_size = 0;
	unsigned int r_free_size = 0;

	if (!rb || !data || (len <= 0)) {
        //quec_log("%s,rb=%#x,data=%#x,len=%d",__func__,rb,data,len);
		return 0;
	}
	//shaohua.li@20200922
	//��ֹ���̲߳������»�ȡ��r_free_size��׼
	//��Ŀ�����ǰ�����ε���helios_rb_free_space(rb)����ֵ��һ�£�(��һ�ε��ú������̴߳�ϣ������̴߳�rb�������ݵ��µڶ��η���ֵ��ȡ��??
	//����w_size��ֵС��lenֵ������ʹ���潫dataָ���������copy��rb
	//w_size = len < helios_rb_free_space(rb) ? len : helios_rb_free_space(rb);
	r_free_size = helios_rb_free_space(rb);
	w_size = len < r_free_size ? len : r_free_size;
	
	/* first put the data starting from write_pos to buffer end */ 
	w_free_size = w_size < (rb->size-(rb->wpos&(rb->size-1))) ? w_size : (rb->size-(rb->wpos&(rb->size-1)));

	memcpy(rb->data+(rb->wpos&(rb->size-1)), data, w_free_size);
	/* then put the rest (if any) at the beginning of the buffer */ 
	memcpy(rb->data, data+w_free_size, w_size-w_free_size);

	rb->wpos += w_size;

	return w_size;
}

unsigned int helios_rb_read(helios_ring_buf_t *rb, unsigned char *data, unsigned int len)
{
	unsigned int r_size = 0, r_free_size = 0;
	unsigned int r_data_len = 0;
	
	if (!rb || !data || (len <= 0)) {
        //quec_log("%s,rb=%#x,data=%#x,len=%d",__func__,rb,data,len);
		return 0;
	}
    
	//shaohua.li@20200922
	//��ֹ���̲߳������»�ȡ��datalen��׼
	//��Ŀ�����ǰ�����ε���helios_rb_data_len(rb)����ֵ��һ�£�(��һ�ε��ú������̴߳�ϣ�������rbд�����ݵ��µڶ��λ�ȡ��??
	//����r_size��ֵ����lenֵ������ʹ�������dataָ��Խ��
	//r_size = len < helios_rb_data_len(rb)	? len : helios_rb_data_len(rb);
	r_data_len = helios_rb_data_len(rb);
	r_size = len < r_data_len ? len : r_data_len;
	
	/* first get the data from ring_buf->read_pos until the end of the buffer */
	r_free_size = r_size < (rb->size-(rb->rpos&(rb->size-1))) ? r_size : (rb->size-(rb->rpos&(rb->size-1)));
	
	memcpy(data, rb->data+(rb->rpos&(rb->size-1)), r_free_size);
	/* then get the rest (if any) from the beginning of the buffer */
	memcpy(data+r_free_size, rb->data, r_size-r_free_size);

	rb->rpos += r_size;

	return r_size;
}


