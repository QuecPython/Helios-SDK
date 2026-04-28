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
	HELIOS_USB_HOTPLUG_OUT	= 0,
	HELIOS_USB_HOTPLUG_IN	= 1,
}Helios_USB_Status_e;


typedef void(*usb_hotplug_cb_t)(Helios_USB_Status_e status); 


typedef struct
{
	usb_hotplug_cb_t usb_hotplug_cb;
}Helios_USBInitStruct;


/**
 * @brief:
 *      usb init
 *
 * @sideeffect:
 *
 * @param:
 *      \info   [in]         - a pointer to the Helios_USBInitStruct structure type
 * @return:
 *      0 for success,-1 for failure
 */
int Helios_USB_Init(Helios_USBInitStruct *info);

int Helios_USB_DeInit();



/**
 * @brief:
 *      get usb hotplug status
 *
 * @sideeffect:
 *
 * @param:
 *      \
 * @return:
 *      0 for out,1 for in
 */
int Helios_USB_GetStatus(void);

#if MICROPY_QPY_USB_DOUBLE_CDC
extern int Helios_USB_nv_set_double_cdc(unsigned char cfg);
#endif

#if defined(PLAT_ASR) || defined(PLAT_Unisoc)
/**
 * @brief:
 *      Write NV to Disable USB Discription for SANX
 *
 * @sideeffect:
 *
 * @param:
 *      \flag  [in]     -the flag which will be written in usb_dis_flag.nv(support 0 or 1)
 * @return:
 *      0 for failed,1 for succeed
 */
int Helios_USB_function_disable(int flag);

/**
 * @brief:
 *      Read NV to Disable USB Discription for SANX
 *
 * @sideeffect:
 *
 * @param:
 *      \
 * @return:
 *      0 for not set,1 for usb disable
 */
int Helios_USB_function_state(void);

#endif

#ifdef __cplusplus
} /*"C" */
#endif

#endif

