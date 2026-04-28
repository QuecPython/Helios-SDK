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
 @file	helios_keypad.h
 @brief	Data type definition for keypad Record.
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
2021/10/26  Burols.wang	Create.
**************************************************************************/
#if defined(PLAT_ASR)  || defined(PLAT_Unisoc) || defined(PLAT_ASR_1606) || defined(PLAT_ASR_1609) || defined(PLAT_Unisoc_8910_R05) || defined(PLAT_ASR_1602) || defined(PLAT_Unisoc_8910_R06) \
	|| defined(PLAT_Unisoc_8850_R02)
#ifndef __HELIOS_KEYPAD_H__
#define __HELIOS_KEYPAD_H__


typedef enum
{
	Helios_KeyPad_Light_Level_0 = 0,
	Helios_KeyPad_Light_Level_1,
	Helios_KeyPad_Light_Level_2,
	Helios_KeyPad_Light_Level_3,
	Helios_KeyPad_Light_Level_4,
	Helios_KeyPad_Light_Level_5,
	Helios_KeyPad_Light_Level_6,
	Helios_KeyPad_Light_Level_7,
	Helios_KeyPad_Light_Level_8,
	Helios_KeyPad_Light_Level_9,
	Helios_KeyPad_Light_Level_10,
	Helios_KeyPad_Light_Level_MAX,
}Helios_KeyPad_Light_Level_E;
	
//note:if  update ql_event_data_t ,here shuld update too. because this type is same as ql_event_data_t
typedef struct __Helios_KeyPad_Event{
	int32_t event_id; // UP/DOWN
	int32_t param_01; // row index
	int32_t param_02; // col index
	int32_t param_03; //
	int32_t key_v;
}Helios_KeyPad_Event;

//note:control keypad's light is on or off
typedef enum __HELIOS_KEYPAD_LIGHT_CTRL{
	HELIOS_KEYPAD_LIGHT_OFF=0,
	HELIOS_KEYPAD_LIGHT_ON,
}Helios_KeyPad_Light_Ctl_E;

typedef uint32_t (*Helios_KeyPad_CallBack_t)(Helios_KeyPad_Event event);

int32_t Helios_KeyPad_Init(int row_num,int col_num);

int32_t Helios_KeyPad_Deinit();

void 	Helios_KeyPad_SetCb(Helios_KeyPad_CallBack_t cb);

#endif
#endif