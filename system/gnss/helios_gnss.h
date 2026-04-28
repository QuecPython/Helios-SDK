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


#ifndef _HELIOS_GNSS_H
#define _HELIOS_GNSS_H
 
#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef enum
{
	HELIOS_UART_RX_RECV_DATA_IND = 0,
}Helios_GnssEvent;

typedef void (*gnss_cb_t)(Helios_GnssEvent ind_type, uint32_t size);


typedef struct
{
	gnss_cb_t gnss_cb;
}Helios_GNSSInitStruct;


typedef enum
{
    HELIOS_GNSS_DISABLE,
    HELIOS_GNSS_ENABLE,
    HELIOS_GNSS_RESET
}Helios_GnssSW;

#if defined(PLAT_Qualcomm)
typedef enum
{
   HELIOS_GNSS_PRIORITY_GROUP_0 = 0,     //0:GNSS service has a higher priority.
   HELIOS_GNSS_PRIORITY_GROUP_1,         //1:WWAN service has a higher priority.
   HELIOS_GNSS_PRIORITY_GROUP_MAX
}Helios_GNSS_LTE_Priority;
#else
typedef enum
{
   HELIOS_GNSS_PRIORITY_GROUP_0 = 0,     //0:gnss cold > lte signal > gnss hot > lte data
   HELIOS_GNSS_PRIORITY_GROUP_1,         //1:gnss cold > lte signal > lte data > gnss hot
   HELIOS_GNSS_PRIORITY_GROUP_2,         //2:gnss cold > gnss hot > lte signal > lte data
   HELIOS_GNSS_PRIORITY_GROUP_3,         //3:lte signal > lte data > gnss cold > gnss hot
   HELIOS_GNSS_PRIORITY_GROUP_MAX
}Helios_GNSS_LTE_Priority;
#endif

int Helios_GNSS_Init(Helios_GNSSInitStruct *info);
int Helios_GNSS_Switch(Helios_GnssSW gnss_sw);
int Helios_GNSS_GetState(uint8_t *state);
int Helios_GNSS_GetNmea(unsigned char *pbuff, uint32_t len);
#if defined(PLAT_Unisoc) || defined(PLAT_Unisoc_8910_R05) || defined(PLAT_Unisoc_8910_R06)
//int Helios_GNSS_SetSysType(uint32_t systype);
//int Helios_GNSS_GetSysType(uint32_t *systype);
int Helios_GNSS_enableGST(uint8_t opt);
#endif

/*henry.fang 2025.11.13 Quecpython add BG95M3 gnss init flag*/
#if defined(BOARD_BG95M3)
   static bool gnss_init_flag = false;
   #define	 CHECK_GNSS_ALREADY_ENABLED1(X)	          if(gnss_init_flag==X) return mp_obj_new_int(-1)
   #define   CHECK_GNSS_ALREADY_ENABLED2(X)            if(gnss_init_flag!=X) return mp_obj_new_int(-1)
   #define   TOGGLE_GNSS_INIT_FLAG_ON_SUCCESS(X)       if(X==0) gnss_init_flag=!gnss_init_flag
#else
   #define	 CHECK_GNSS_ALREADY_ENABLED1(X)
   #define   CHECK_GNSS_ALREADY_ENABLED2(X)
   #define   TOGGLE_GNSS_INIT_FLAG_ON_SUCCESS(X)
#endif

#if defined(PLAT_Unisoc_8850) || defined(PLAT_Qualcomm) || defined(PLAT_Unisoc_8850_R02)
int Helios_GNSS_SetGnssLtePriority(Helios_GNSS_LTE_Priority priority);
int Helios_GNSS_GetGnssLtePriority(Helios_GNSS_LTE_Priority *priority);
#endif

#if defined(PLAT_ASR_1606) || defined(PLAT_ASR_1609) || defined(PLAT_ASR_1602) || defined(PLAT_Unisoc) \
 || defined(PLAT_Unisoc_8910_R05) || defined(PLAT_Unisoc_8910_R06) || defined(PLAT_ASR)
int Helios_GNSS_Configuration_Set(uint8_t config_type, uint8_t config_value);
int Helios_GNSS_Configuration_Get(uint8_t config_type);
#endif

#endif
