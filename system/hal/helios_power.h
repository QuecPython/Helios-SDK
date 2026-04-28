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
 @file	helios_power.h
 @brief	Data type definition for POWER.
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

#ifndef _HELIOS_POWER_H
#define _HELIOS_POWER_H


#ifdef __cplusplus
extern "C" {
#endif

typedef void (*powerkey_cb_t)(uint8_t status);

typedef struct
{
	powerkey_cb_t user_cb;
}Helios_PowerInitStruct;


typedef enum
{
	HELIOS_CAM_VDD_CLOSED = -2,
    HELIOS_CAM_VDD_UNUSED = -1,
	HELIOS_CAM_VDD_1V20 = 0x0,
    HELIOS_CAM_VDD_1V25,
    HELIOS_CAM_VDD_1V30,
    HELIOS_CAM_VDD_1V50,
    HELIOS_CAM_VDD_1V70, 
    HELIOS_CAM_VDD_1V80, 
    HELIOS_CAM_VDD_1V85,
    HELIOS_CAM_VDD_1V90, 
    HELIOS_CAM_VDD_2V50, 
    HELIOS_CAM_VDD_2V60,
    HELIOS_CAM_VDD_2V70,
    HELIOS_CAM_VDD_2V75,
    HELIOS_CAM_VDD_2V80, 
    HELIOS_CAM_VDD_2V85,
    HELIOS_CAM_VDD_2V90, 
    HELIOS_CAM_VDD_3V00,
    HELIOS_CAM_VDD_3V10, 
    HELIOS_CAM_VDD_3V30, 
    HELIOS_CAM_VDD_MAX = HELIOS_CAM_VDD_3V30  
} Helios_cameraVDD_t;

//for unisoc 8910s
typedef enum
{
    POWER_LEVEL_3200MV = 3200,
    POWER_LEVEL_3100MV = 3100,
    POWER_LEVEL_3000MV = 3000,
    POWER_LEVEL_2900MV = 2900,
    POWER_LEVEL_2800MV = 2800,
    POWER_LEVEL_2700MV = 2700,
    POWER_LEVEL_2600MV = 2600,
    POWER_LEVEL_2500MV = 2500,
    POWER_LEVEL_2400MV = 2400,
    POWER_LEVEL_2300MV = 2300,
    POWER_LEVEL_2200MV = 2200,
    POWER_LEVEL_2100MV = 2100,
    POWER_LEVEL_2000MV = 2000,
    POWER_LEVEL_1900MV = 1900,
    POWER_LEVEL_1800MV = 1800,
    POWER_LEVEL_1700MV = 1700,
    POWER_LEVEL_1600MV = 1600,
    POWER_LEVEL_1500MV = 1500,
    POWER_LEVEL_1400MV = 1400,
    POWER_LEVEL_1300MV = 1300,
    POWER_LEVEL_1200MV = 1200,
    POWER_LEVEL_1100MV = 1100,
    POWER_LEVEL_UNUSED
} Helios_powerLevel_t;

/**
 * @brief:
 *      register power on/off callback
 *
 * @param:
 *      NULL
 * @return:
 *      0 - succeed, -1 - failed
 */
int Helios_Power_Init(Helios_PowerInitStruct *info);

int Helios_Power_DeInit();

#if defined(PLAT_Unisoc) || defined(PLAT_Unisoc_8910_R05) || defined(PLAT_Unisoc_8910_R06)
int Helios_Power_Init_ex(Helios_PowerInitStruct *info, uint8_t mode);
#endif

/**
 * @brief:
 *      power reset
 *
 * @param:
 *      \reset_mode        [in]    - 0 quick reset
 *                                 - 1 normal reset
 * @return:
 *      power reset result, 0 for success,-1 for failure
 */
int Helios_Power_Reset(uint32_t reset_mode);


/**
 * @brief:
 *      power down
 *
 * @param:
 *      \powd_mode        [in]    - 0 quick powerdown
 *                                - 1 normal powerdown
 * @return:
 *      power down result, 0 for success,-1 for failure
 */
int Helios_Power_Down(uint32_t powd_mode);





/**
 * @brief:
 *      get power up reason
 *
 * @param:
 *      NULL
 * @return:
 *      get power up reason value
 */
int Helios_Power_GetUpReason(void);


/**
 * @brief:
 *      get power down reason
 *
 * @param:
 *      NULL
 * @return:
 *      get power down reason value
 */
int Helios_Power_GetDownReason(void);


/**
 * @brief:
 *      get battery value
 *
 * @param:
 *      NULL
 * @return:
 *      get battery voltage value
 */
int Helios_Power_GetBatteryVol(void);


#if defined(PLAT_Unisoc) || defined(PLAT_Unisoc_8910_R05) || defined(PLAT_Unisoc_8910_R06) || defined(PLAT_ASR_1606) \
	 || defined(PLAT_ASR_1609) || defined(PLAT_ASR_1602) || defined(PLAT_ASR) 
int Helios_Power_CAM_VDD_output(uint8_t on_off, Helios_cameraVDD_t level,unsigned char lp_enabled);
#else
void Helios_Power_CAM_VDD_output(uint8_t on_off);
#endif

#if defined(PLAT_EIGEN)
/**
 * @brief:
 *      set powerkey poweron debounce time
 *
 * @param:
 *      uint32 time_ms, this value will be writen into nv
 * @return:
 *      powerkey poweron debounce time NV write return val
 */
int Helios_Pwrkey_poweron_debounce_time_set(uint32_t time_ms);
#endif

void Helios_camera_poweron(void);
void Helios_camera_poweroff(void);
unsigned char Helios_Get_Pwrkey_Status(void);
int Helios_Set_Power_Level(unsigned char id,Helios_powerLevel_t level);

#ifdef __cplusplus
} /*"C" */
#endif

#endif

