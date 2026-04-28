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
2021/03/29  Felix.Ye	Create.
**************************************************************************/

#ifndef _HELIOS_WDT_H
#define _HELIOS_WDT_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief:
 *      wdt init
 *
 * @sideeffect:
 *
 * @param:
 *      \period_s   [in]         - set soft dog detection time (s)
 * @return:
 *      init wdt Result, 0 for success,-1 for failure
 */
int Helios_WDT_Init(uint64_t period_s);


/**
 * @brief:
 *      feed wdt
 *
 * @sideeffect:
 *
 * @param:
 *      \NULL
 *
 * @return:
 *      feed wdt Result, 0 for success,-1 for failure
 */
int Helios_WDT_Feed(void);


/**
 * @brief:
 *      stop wdt
 *
 * @sideeffect:
 *
 * @param:
 *      NULL
 * @return:
 *      stop wdt Result, 0 for success,-1 for failure
 */
int Helios_WDT_Deinit(void);


#ifdef __cplusplus
} /*"C" */
#endif

#endif

