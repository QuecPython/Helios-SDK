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
 @file	helios_timer.h
 @brief	Data type definition for timer.
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

#ifndef _HELIOS_TIMER_H
#define _HELIOS_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief:
 *      timer init
 *
 * @sideeffect:
 *
 * @param:
 *      \timerCallbackFunc   [in]   - timer call-back routine
 *      \timerArgc    		 [in]   - argument to be passed to call-back on expiration
 *
 * @return:
 *      Timer handle,-1 for failure
 */
int Helios_Timer_init( void* timerCallbackFunc, void* timerParams);

/**
 * @brief:
 *      timer deinit
 *
 * @sideeffect:
 *
 * @param:
 *      \Timer_handle   [in]   - Timer handle
 *
 * @return:
 *      \deint timer result, 0 for success,-1 for failure
 */
int Helios_Timer_Deinit( int Timer_handle);

/**
 * @brief:
 *      timer start
 *
 * @sideeffect:
 *
 * @param:
 *      \Timer_handle   [in]   - Timer handle
 *		\set_Time		[in]   - timer set value
 *		\cyclicalEn		[in]   - wether to enable the cyclical mode or not
 *
 * @return:
 *      start timer result, 0 for success,-1 for failure
 */
int Helios_Timer_Start( int Timer_handle, uint32_t set_Time, uint8_t cyclicalEn);




/**
 * @brief:
 *      timer stop
 *
 * @sideeffect:
 *
 * @param:
 *      \Timer_handle   [in]   - Timer handle
 *
 * @return:
 *      stop timer result, 0 for success,-1 for failure
 */
int Helios_Timer_Stop( int Timer_handle);


#ifdef __cplusplus
} /*"C" */
#endif

#endif



