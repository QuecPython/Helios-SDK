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
 @file	helios_acctimer.h
 @brief	Data type definition for acctimer.
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
2022/09/15  Stephen.Gao	Create.
**************************************************************************/

#ifndef _HELIOS_APBTIMER_H
#define _HELIOS_APBTIMER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void(*APBTIMER_CALLBACK)(unsigned int);	/* Function pointer */

typedef int APBTimer_ID;

typedef	struct _APBTimerConfig_s					/* timer configuration */
{
    unsigned int flag;						// 0: one shot  1: preiodic
    unsigned int period;					// interruption cycle, unit:us
    APBTIMER_CALLBACK timerCallbackFunc;	// callback
    unsigned int timerParams;				// callback parameter, reserved unused
}APBTimerConfig_S;

/**
 * @brief:
 *      timer create
 *
 * @sideeffect:
 *
 * @param:
 *      \para   [in]   - timer configuration
 *
 * @return:
 *      Timer handle,-1 for failure
 */

APBTimer_ID Helios_Acctimer_Create(APBTimerConfig_S* para);



/**
 * @brief:
 *      timer delete
 *
 * @sideeffect:
 *
 * @param:
 *      \Timer_handle   [in]   - Timer handle
 *
 * @return:
 *      \deint timer result, 0 for success,-1 for failure
 */
int Helios_Acctimer_Delete(APBTimer_ID acc_timer_id);



int Helios_Acctimer_Start(APBTimer_ID acc_timer_id, APBTimerConfig_S* timer_cfg);

int Helios_Acctimer_Stop(APBTimer_ID acc_timer_id);



#ifdef __cplusplus
} /*"C" */
#endif

#endif



