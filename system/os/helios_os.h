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


#ifndef _HELIOS_OS_H_
#define _HELIOS_OS_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct
{
    char *name;
    size_t stack_size;
    uint32_t priority;
    void(*entry)(void *);
    void *argv;
} Helios_ThreadAttr;

typedef struct
{
    uint32_t ms;
    bool cycle_enable;
    void(*cb)(void *);
    void *argv;
} Helios_OSTimerAttr;

#define HELIOS_WAIT_FOREVER 0xFFFFFFFF
#define HELIOS_NO_WAIT      0x0

typedef int Helios_Thread_t;
typedef int Helios_Sem_t;
typedef int Helios_Mutex_t;
typedef int Helios_ReMutex_t;
typedef int Helios_MsgQ_t;
typedef int Helios_OSTimer_t;

Helios_Thread_t Helios_Thread_Create(Helios_ThreadAttr *attr);
void Helios_Thread_Delete(Helios_Thread_t thread);
void Helios_Thread_Exit(void);
void *Helios_Thread_GetStaskPtr(Helios_Thread_t thread);
char *Helios_Thread_GetName(void);
Helios_Thread_t Helios_Thread_GetID(void);
void Helios_Thread_SetSpecific(void *spec);
void *Helios_Thread_GetSpecific(void);
Helios_Sem_t Helios_Semaphore_Create(uint32_t max_count, uint32_t init_count);
int Helios_Semaphore_Acquire(Helios_Sem_t sem, uint32_t wait);
void Helios_Semaphore_Poll(Helios_Sem_t sem, uint32_t *count);

void Helios_Semaphore_Release(Helios_Sem_t sem);
void Helios_Semaphore_Delete(Helios_Sem_t sem);
Helios_Mutex_t Helios_Mutex_Create(void);
int Helios_Mutex_Lock(Helios_Mutex_t mutex, uint32_t wait);
void Helios_Mutex_Unlock(Helios_Mutex_t mutex);
void Helios_Mutex_Delete(Helios_Mutex_t mutex);
Helios_ReMutex_t Helios_ReMutex_Create(void);
int Helios_ReMutex_Lock(Helios_ReMutex_t mutex_r, uint32_t wait);
void Helios_ReMutex_Unlock(Helios_ReMutex_t mutex_r);
void Helios_ReMutex_Delete(Helios_ReMutex_t mutex_r);
Helios_MsgQ_t Helios_MsgQ_Create(uint32_t msg_count, size_t msg_size);
int Helios_MsgQ_Put(Helios_MsgQ_t mq, const void *msg, size_t msg_size, uint32_t wait);
int Helios_MsgQ_Get(Helios_MsgQ_t mq, void *msg, size_t msg_size, uint32_t wait);
int Helios_MsgQ_Get_Cnt(Helios_MsgQ_t mq, uint32_t *count);
void Helios_MsgQ_Delete(Helios_MsgQ_t mq);
Helios_OSTimer_t Helios_OSTimer_Create(void);
int Helios_OSTimer_Start(Helios_OSTimer_t timer, Helios_OSTimerAttr *attr);
int Helios_OSTimer_Stop(Helios_OSTimer_t timer);
void Helios_OSTimer_Delete(Helios_OSTimer_t timer);
void Helios_sleep(uint32_t s);
void Helios_msleep(uint32_t ms);
uint32_t Helios_GetAvailableMemorySize(void);
uint32_t Helios_Critical_Enter(void);
void Helios_Critical_Exit(uint32_t critical);

typedef int Helios_OSFlag_t;

typedef enum
{
	Helios_FLAG_AND 		= 5,	///< Wait for all bits in the input event to be set. Do not clear the event flag after the event is processed.
	Helios_FLAG_AND_CLEAR 	= 6,	///< Wait for all bits in the input event to be set. Clear the event flag after the event is processed.
	Helios_FLAG_OR 			= 7,	///< Wait for any bit in the input event to be set. Do not clear the event flag after the task is finished processing the event.
	Helios_FLAG_OR_CLEAR	= 8		///< Wait for any bit in the input event to be set. After the task is finished processing the event, clear the event flag.
} Helios_flag_op_e;


Helios_OSFlag_t Helios_Flag_Create();
int Helios_Flag_Wait(Helios_OSFlag_t flagRef, uint32_t mask, Helios_flag_op_e operation, uint32_t *flag, uint32_t timeout);
int Helios_Flag_Release(Helios_OSFlag_t flagRef, uint32_t mask,  Helios_flag_op_e operation);
int Helios_Flag_Clear(Helios_OSFlag_t flagRef, uint32_t flag);
int Helios_Flag_delete( Helios_OSFlag_t flagRef);

#if defined(PLAT_ASR_1606) || defined(PLAT_Unisoc) || defined(PLAT_ASR_1602) || defined(PLAT_Unisoc_8910_R06)
void Helios_delay_us(unsigned long uSec);
#endif
#endif

