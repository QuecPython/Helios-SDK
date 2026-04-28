/* Copyright (c) Quectel Wireless Solution, Co., Ltd.All Rights Reserved.
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
 /* =========================================== */
 /* AUTHOR  felix.Ye                           */
 /* DATA    2021.08.19                          */
 /* =========================================== */


/*===========================================================================
 * include files
 ===========================================================================*/

#include "helios.h"
#include "helios_debug.h"
#include "helios_os.h"
#include "helios_rtc.h"


/*===========================================================================
 * Macro Definition
 ===========================================================================*/
const char * week_days[] = {"SUN","MON","TUS","WED","THU","FRI","SAT"};

#define rtc_debug(fmt, ...) custom_log(APP, fmt, ##__VA_ARGS__)
#define	weekday_to_string(a)	(week_days[(a)])

/*===========================================================================
 * Variate
 ===========================================================================*/
static Helios_Thread_t thread_id;

/*===========================================================================
 * Functions
 ===========================================================================*/
 
static int quec_rtc_print_time(Helios_RTCTime tm)
{   
    rtc_debug("%d-%0.2d-%0.2d %0.2d:%0.2d:%0.2d [%s]\r\n",
			tm.tm_year,
			tm.tm_mon,
			tm.tm_mday,
			tm.tm_hour,
			tm.tm_min,
			tm.tm_sec,
			weekday_to_string(tm.tm_wday));
    return 0;
}
void quec_rtc_test_callback(void)
{
    rtc_debug("ql rtc test callback come in!");
    
    Helios_RTCTime test_tm = {0}; 
    
    //disable RTC alarm
    //ql_rtc_enable_alarm(0);
    
    //get alarm time
    rtc_debug("=========callback print alarm time===========\r\n");
    Helios_RTC_GetTime(&test_tm);
    quec_rtc_print_time(test_tm);
}


int quec_rtc_demo_test(	void)
{
    rtc_debug("ql rtc demo enter start! \n");

    Helios_RTCTime tm;
	Helios_RTCTime local_tm;
	int64_t ticks = 0;
	int Zoneoffset = 0;

    //get current time
    Helios_RTC_GetTime(&tm);   
    quec_rtc_print_time(tm);

    //2020-12-22 16:50:30 [WED]
    tm.tm_year = 2020;
    tm.tm_mon  = 12;
    tm.tm_mday = 22;
    tm.tm_wday = 2;
    tm.tm_hour = 16;
    tm.tm_min  = 50;
    tm.tm_sec  = 30;
    quec_rtc_print_time(tm);

    //set time
    Helios_RTC_SetTime(&tm);

    Helios_RTC_GetTime(&tm);
    quec_rtc_print_time(tm);

    //set & enable alarm
 	tm.tm_sec += 100;
	Helios_RTC_Set_Alarm(&tm);
    Helios_RTC_Register_cb(quec_rtc_test_callback);
	
	Helios_RTC_Enable_Alarm(1);

	ticks = Helios_RTC_GetTicks();
	rtc_debug("current ticks = %lld\n",ticks);

	Zoneoffset = Helios_RTC_GetTimeZoneOffset();
	rtc_debug("current Zoneoffset = %d\n",Zoneoffset);

	Helios_RTC_SetTimeZoneOffset(Zoneoffset+1);
	Zoneoffset = Helios_RTC_GetTimeZoneOffset();
	rtc_debug("current Zoneoffset = %d\n",Zoneoffset);

	Helios_RTC_GetLocalTime(&local_tm);
	rtc_debug("=========print local_tm time===========\r\n");
    quec_rtc_print_time(local_tm);
	
    Helios_RTC_SetTimeZoneOffset(Zoneoffset);
	
	while (1) 
    { 
		Helios_RTC_GetTime(&tm);
		rtc_debug("=========print current time===========\r\n");
		quec_rtc_print_time(tm);
		Helios_sleep(5);
	}
	return 0;
}


static void rtc_test_func_entry(void * argv)
{
	Helios_sleep(3);
    rtc_debug("rtc demo thread enter, param 0x%x", argv);
	quec_rtc_demo_test();

	Helios_Thread_Delete(thread_id);

}

void quec_rtc_test(void *argv)
{
	rtc_debug(" quec_rtc_test start \n");
    (void)argv;
    Helios_ThreadAttr ThreadAttr = {
        .name = "rtc_test",
        .stack_size = 4096,
        .priority = 100,
        .entry = rtc_test_func_entry,
        .argv = NULL
    };

    thread_id = Helios_Thread_Create(&ThreadAttr);
}

//application_init(quec_rtc_test, "quec_rtc_test", 2, 0);
