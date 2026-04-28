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
 @file	helios_wdt.h
 @brief	Data type definition for WDT.
*/
/**************************************************************************
===========================================================================
Copyright (c) 2018 Quectel Wireless Solution, Co., Ltd.All Rights Reserved.
Quectel Wireless Solution Proprietary and Confidential.
===========================================================================

						EDIT HISTORY FOR FILE
This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

WHEN		WHO			WHAT,WHERE,WHY
----------  ---------   ---------------------------------------------------
2021/05/25  Jayceon.Fu	Create.
**************************************************************************/

#ifndef _HELIOS_USB_H
#define _HELIOS_USB_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef enum
{
	HELIOS_USBNET_TYPE_ECM	    = 1,
	HELIOS_USBNET_TYPE_RNDIS	= 3,
}Helios_USBNET_Type_e;


/**
 * @brief:
 *      usbnet type set
 *
 * @sideeffect:
 *
 * @param:
 *      \info   [in]         - usbnet type
 * @return:
 *      0 for success,-1 for failure
 */
int Helios_USBNET_SetType(Helios_USBNET_Type_e type);

int Helios_USBNET_GetType(Helios_USBNET_Type_e *type);

int Helios_USBNET_GetStatus(uint8_t *status);

#if defined(PLAT_Unisoc) || defined(PLAT_Unisoc_8910_R05) || defined(PLAT_Unisoc_8850) || defined(PLAT_Unisoc_8850_R02) || defined(PLAT_Unisoc_8910_R06)
	int Helios_USBNET_GetNat(uint8_t sim_id, uint8_t profile_id);

	int Helios_USBNET_SetNat(uint8_t sim_id, uint8_t profile_id, uint8_t nat);
#endif

/**
 * @brief:
 *      open usbnet
 *
 * @sideeffect:
 *
 * @param:
 *      \
 * @return:
 *      0 for out,1 for in
 */
int Helios_USBNET_Open(void);

int Helios_USBNET_Close(void);

int Helios_USBNET_SetMAC(unsigned char *mac);

int Helios_USBNET_SetProduct(char *product);

#ifdef __cplusplus
} /*"C" */
#endif

#endif

