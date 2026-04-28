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

#ifndef _HELIOS_SECUREDATA_H
#define _HELIOS_SECUREDATA_H

#ifdef __cplusplus
extern "C" {
#endif
/*-----------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define HELIOS_MAX_SECUREDATA_COUNT (16)

typedef struct
{
	uint8_t index;
    uint8_t* pBuffer;
    uint32_t len;
}Helios_SecureData_t;

int Helios_Securedata_Read(Helios_SecureData_t *sec_data);

int Helios_Securedata_Store(Helios_SecureData_t *sec_data);

/*-----------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif


