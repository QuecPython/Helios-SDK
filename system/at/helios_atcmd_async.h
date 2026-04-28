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
 @file	helios_nw.h
 @brief	Data type definition for network.
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
2021/03/29  xjin.gao	Create.
**************************************************************************/

#ifndef _HELIOS_ATCMD_ASYNC_H
#define _HELIOS_ATCMD_ASYNC_H

#ifdef __cplusplus
extern "C" {
#endif
/*-----------------------------------------------------------------------*/
typedef void(*helios_atcmd_send_callback_t)(int sta);

/**
 * @brief:
 *      Initialize the AT thread
 *
 * @param:
 *      \cb [in]         - callback function pointer, type is helios_atcmd_send_callback_t
 * @return:
 *      0 - sucsses , -1 - faile
 */
int Helios_Atcmd_Thread_Init(void *cb);

/**
 * @brief:
 *      Delete the AT thread
 *
 * @param:
 *      void
 * @return:
 *      no return
 */
void Helios_Atcmd_Thread_Deinit(void);

/**
 * @brief:
 *      Send AT Cmd
 *
 * @param:
 *      \sim_id [in]         - SIM card ID, default is 0
 *		\cmd [in]          	 - AT command must include "\r\n"
 *		\resp [out]          - Array for receiving reply characters
 *		\resp_len [in]       - Maximum received byte length
 *		\include_str [in]    - Index string, only reply to result information containing the string
*		\time_out [in]       - Timeout return, unit is seconds
 * @return:
 *      0 - sucsses , -1 - faile
 */
int Helios_Atcmd_Send_by_Thread(uint8_t sim_id,char *cmd,char *resp,int resp_len,char *include_str,int time_out);

/*-----------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif

