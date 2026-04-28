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

#ifndef _HELIOS_ATCMD_H
#define _HELIOS_ATCMD_H

#ifdef __cplusplus
extern "C" {
#endif
/*-----------------------------------------------------------------------*/
#define HELIOS_MAX_OSA_MSG_BUF_LEN 2048
#define HELIOS_MAX_AT_TIME_OUT 600

typedef enum HELIOS_AT_RESP_STATUS_ENUM{
	HELIOS_AT_RESP_OK = 0,   //成功
	HELIOS_AT_RESP_ERROR,    //AT指令未识别
	HELIOS_AT_RESP_CME_ERROR,   //
	HELIOS_AT_RESP_CMS_ERROR,   //短信错误
	HELIOS_AT_RESP_INVALID_PARAM,  //参数错误
	HELIOS_AT_RESP_TIME_OUT,   //超时
	HELIOS_AT_RESP_SYS_ERROR,  //系统错误
}HELIOS_AT_RESP_STATUS_E;

int Helios_Atcmd_Get_Para_Value_Str(char *result,int line_index,int para_index, char *para_value,int para_value_len);


/**
 * @brief:
 *      发送AT指令
 *
 * @param:
 *      sim_id       [in]    - SIM卡ID，0或1，无双卡功能的模组填0
 *      cmd          [in]    - 需要发送的AT指令，字符串类型，结尾必须包含'\r\n'
 * 		resp		 [out]   - AT指令返回结果会保存在该数组，字符串类型
 * 		resp_len     [in]    - 接收AT指令返回结果的数组最大长度
 * 		include_str  [in]    - 期望指令返回的结果中所包含的字符串，字符串类型，具体如下：
 * 							   空字符串 - 获取AT指令返回的所有数据(不包含‘OK’等结果性的字符数据)放入resp参数中
 * 							   非空字符串 - 筛选包含该字符串的数据放入resp参数中
 * 		time_out     [in]    - 超时时间，单位/秒
 * @return:
 *      成功返回0，失败返回非0值
 */
HELIOS_AT_RESP_STATUS_E Helios_Atcmd_Send_Sync(uint8_t sim_id,char *cmd,char *resp,int resp_len,char *include_str,int time_out);

/*-----------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif

