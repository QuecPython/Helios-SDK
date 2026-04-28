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


#ifndef _HELIOS_STARTUP_H_
#define _HELIOS_STARTUP_H_

#include <stdint.h>

typedef void (*app_entry_t)(void *argv);


#if defined(PLAT_EIGEN) || defined(PLAT_EIGEN_718)

typedef struct
{
	app_entry_t  app_entry;
	char     *app_name;
	uint32_t  stack_size_byte;
	uint8_t   startup_prio;
	uint32_t  *arvg;
} appRegItem_t;

#define _appRegTable_attr_ const __attribute__((__section__(".LOAD_APP_TABLE")))

#define application_init(app_entry, app_name, stack_size_kib, startup_prio) _appRegTable_attr_  appRegItem_t _regAppItem_##app_entry  = {app_entry, app_name, stack_size_kib*1024, startup_prio, NULL}

#else

typedef struct
{
	app_entry_t entry;
	char *name;
	uint32_t stack_size;
	uint8_t startup_prio;
} appRegItem_t;

#define _appInit_ __attribute__((unused, section(".appRegTable")))

#define application_init(entry, name, stack_size_kib, startup_prio) \
	appRegItem_t _regAppItem_##entry _appInit_ = {entry, name, stack_size_kib*1024, startup_prio}

#endif

#endif /* _STARTUP_H_ */
