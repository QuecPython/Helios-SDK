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

/**
 @file	helios_celllocator.h
 @brief	Data type definition for cell locator.
*/
/**************************************************************************
===========================================================================
Copyright (c) 2021 Quectel Wireless Solution, Co., Ltd.All Rights Reserved.
Quectel Wireless Solution Proprietary and Confidential.
===========================================================================

						EDIT HISTORY FOR FILE
This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

WHEN		WHO			WHAT,WHERE,WHY
----------  ---------   ---------------------------------------------------
2021/03/30  Jayceon.Fu	Create.
**************************************************************************/

#ifndef _HELIOS_CELLLOCATOR_H
#define _HELIOS_CELLLOCATOR_H

#ifdef __cplusplus
extern "C" {
#endif
/*-----------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct
{
	char *server_addr;
	char *token;
	int32_t port;
	int32_t profile_idx;
	int32_t timeout;
}Helios_LBSConfigStruct;

typedef struct 
{
    float longitude;
    float latitude;
    uint16_t accuracy;
	uint8_t	flag; //0 - 正常基站,     1 – 无效基站
}Helios_LBSInfoStruct;



/**
 * @brief: configure Parameter for cell locator
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 *       \info         - a pointer to the Helios_LBSConfigStruct structure type
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_LBS_SetConfiguration(uint8_t sim_id, Helios_LBSConfigStruct *info);


/**
 * @brief: get cell coordinates
 * @sideeffect:
 * @param:
 *       \postion_info         - a pointer to the Helios_LBSConfigStruct structure type
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_LBS_GetPosition(Helios_LBSInfoStruct *postion_info);


/*-----------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif

