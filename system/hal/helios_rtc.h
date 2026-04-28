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
 @file	helios_rtc.h
 @brief	Data type definition for RTC.
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
2021/03/27  Felix.Ye	Create.
**************************************************************************/

#ifndef _HELIOS_RTC_H
#define _HELIOS_RTC_H

#ifdef __cplusplus
extern "C" {
#endif


//time[2000-01-01 00:00:00-----2100-01-01 00:00:00]
typedef struct {
	int tm_sec;	 // seconds [0,59]
	int tm_min;	 // minutes [0,59]
	int tm_hour; // hour [0,23]
	int tm_mday; // day of month [1,31]
	int tm_mon;	 // month of year [1,12]
	int tm_year; // year [2000-2100] 
	int tm_wday; // wday [0-6],sunday = 0
}Helios_RTCTime;

#if defined(PLAT_RDA)
typedef enum{
	Helios_Rtc_Call_NoCalled =0,
	Helios_Rtc_Call_Called   
}Helios_Rtc_Call_E;
#endif

/**
 * @brief:
 *      set rtc time
 *
 * @sideeffect:
 *
 * @param:
 *      \tm [in]         - HELIOS_RTC_time struct
 *    
 * @return:
 *      set rtc result, 0 for success,-1 for failure
 */
int Helios_RTC_SetTime(Helios_RTCTime *tm);


/**
 * @brief:
 *      get rtc time
 *
 * @sideeffect:
 *
 * @param:
 *      \tm [out]         - HELIOS_rtc_time struct
 * @return:
 *      get rtc time result, 0 for success,-1 for failure
 */
int Helios_RTC_GetTime(Helios_RTCTime *tm);

/**
 * @brief:
 *      get ticks
 *
 * @sideeffect:
 *
 * @param:
 *      \tm [out]        
 * @return:
 *      get rtc ticks result, other for success,-1 for failure
 */
int64_t Helios_RTC_GetTicks(void);

int64_t Helios_RTC_GetSecond(void);
uint64_t Helios_Get_CurrentDateTime_Second(void);


int64_t Helios_RTC_TicksToMs(void);
int64_t Helios_RTC_TicksToUs(void);

#if defined(PLAT_ASR_1803s) || defined(PLAT_ASR_1803sc) || defined(PLAT_EIGEN) || defined(PLAT_ASR_1606) \
|| defined(PLAT_ASR_1609) || defined(PLAT_ASR_1602)
void Helios_RTC_SetTimeZoneOffset(float offset);
float Helios_RTC_GetTimeZoneOffset(void);
#else
void Helios_RTC_SetTimeZoneOffset(int offset);
int Helios_RTC_GetTimeZoneOffset(void);
#endif

#if defined(PLAT_ASR_1803s) || defined(PLAT_ASR_1803sc) || defined(PLAT_Unisoc) || defined(PLAT_EIGEN) \
|| defined(PLAT_Unisoc_8910_R05) || defined(PLAT_Unisoc_8910_R06)
int Helios_NITZ_Switch(bool isEnable);
int Helios_NITZ_Setval_get(void);
#endif

int Helios_RTC_NtpSetTime(Helios_RTCTime *tm, int flag);
int Helios_RTC_GetLocalTime(Helios_RTCTime *tm);

/**
 * @brief:
 *		set rtc alarm
 *
 * @sideeffect:
 *
 * @param:
 *		\tm [in]		 - HELIOS_RTC_time struct
 *	  
 * @return:
 *		set rtc alarm result, 0 for success,-1 for failure
 */
int Helios_RTC_Set_Alarm(Helios_RTCTime *tm);

/**
 * @brief:
 *		enable rtc alarm
 *
 * @sideeffect:
 *
 * @param:
 *		\on_off [in]		 - enable/disable
 *	  
 * @return:
 *		enable rtc alarm result, 0 for success,-1 for failure
 */
int Helios_RTC_Enable_Alarm(unsigned char on_off);

/**
 * @brief:
 *		register rtc alarm callback
 *
 * @sideeffect:
 *
 * @param:
 *		\on_off [in]		 - enable/disable
 *	  
 * @return:
 *		register callback result, 0 for success,-1 for failure
 */
int Helios_RTC_Register_cb(void (*cb)(void));

#if defined(PLAT_RDA)
/**
 * @brief:
 *		when wakeup from deepsleep or soft powerdown,this function get flag
 *
 * @sideeffect:
 *
 * @param:
 *		no
 *	  
 * @return:
 *		Helios_Rtc_Call_E : register RTC callback and RTC timer callback
 *      be called then will return Helios_Rtc_Call_Called
 */
Helios_Rtc_Call_E Helios_Rtc_Get_Called();
/**
 * @brief:
 *		set RTC callback flag
 *
 * @sideeffect:
 *
 * @param:
 *	Helios_Rtc_Call_E
 *	  
 * @return:
 *		0
 */
int Helios_Rtc_Set_Called( Helios_Rtc_Call_E iscalled );
#endif

#ifdef __cplusplus
} /*"C" */
#endif

#endif

