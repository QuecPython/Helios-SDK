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
 @file	helios_wifiscan.h
 @brief	Data type definition for wifiscan.
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
2021/04/20  Jayceon.Fu	Create.
**************************************************************************/

#ifndef _HELIOS_WIFISCAN_H
#define _HELIOS_WIFISCAN_H

#ifdef __cplusplus
extern "C" {
#endif
/*-----------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MAX_AP_NUMS	30

typedef enum
{
    HELIOS_WIFISCAN_EVENT_DO_IND = 0,
	HELIOS_WIFISCAN_EVENT_ASYNC_IND,
}Helios_WifiScan_Event_Id_e;


typedef void (*wifiscan_cb_t)(uint8_t msg_id, void *ctx);

typedef struct
{
	wifiscan_cb_t user_cb;
}Helios_WifiScanInitStruct;

typedef struct
{
	uint8_t round;
	uint8_t priority;
	uint16_t max_ap_nums;
	uint32_t timeout;
	uint32_t scan_time;
}Helios_WifiScanConfigStruct;

typedef struct
{
	uint8_t channel;
	uint8_t bssid[6];
	int16_t rssi;
}Helios_WifiScanAPStruct;

typedef struct
{
	uint8_t ap_nums;
	Helios_WifiScanAPStruct ap[MAX_AP_NUMS];
}Helios_WifiScanAPInfoStruct;


/**
 * @brief: WifiScan module initialize
 * @sideeffect:
 * @param:
 *       \info         - a pointer to the Helios_WifiScanInitStruct structure type
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_WifiScan_Init(Helios_WifiScanInitStruct *info);

int Helios_WifiScan_Deinit(void);

/**
 * @brief: Determine whether the current platform supports Wifiscan
 * @sideeffect:
 * @param:
 *       \
 * @return:
 *         0 - not support
 *         1 - support
*/
int Helios_WifiScan_Support(void);

/**
 * @brief: open wifiscan function
 * @sideeffect:
 * @param:
 *       \
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_WifiScan_Open(void);

/**
 * @brief: close wifiscan function
 * @sideeffect:
 * @param:
 *       \
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_WifiScan_Close(void);

/**
 * @brief: get wifiscan status
 * @sideeffect:
 * @param:
 *       \
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_WifiScan_GetStatus(uint8_t *status);

/**
 * @brief: wifiscan parameter setting
 * @sideeffect:
 * @param:
 *       \info         - a pointer to the Helios_WifiScanConfigStruct structure type
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_WifiScan_SetConfiguration(Helios_WifiScanConfigStruct *info);
int Helios_WifiScan_SetConfiguration_v2(Helios_WifiScanConfigStruct *info);

/**
 * @brief: wifiscan parameter getting
 * @sideeffect:
 * @param:
 *       \info         - a pointer to the Helios_WifiScanConfigStruct structure type
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_WifiScan_GetConfiguration(Helios_WifiScanConfigStruct *info);
int Helios_WifiScan_GetConfiguration_v2(Helios_WifiScanConfigStruct *info);

/**
 * @brief: Synchronize mode for scanning
 * @sideeffect:
 * @param:
 *		 \info		   - a pointer to the Helios_WifiScanAPInfoStruct structure type
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_WifiScan_SyncStart(Helios_WifiScanAPInfoStruct *info);

/**
 * @brief: Asynchronous mode for scanning
 * @sideeffect:
 * @param:
 *       \
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_WifiScan_AsyncStart(void);


/*-----------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif

