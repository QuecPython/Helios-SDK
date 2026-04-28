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
#include "helios_wdt.h"


/*===========================================================================
 * Macro Definition
 ===========================================================================*/
#define wdt_debug(fmt, ...) custom_log(APP, fmt, ##__VA_ARGS__)
#define WDT_S	5

/*===========================================================================
 * Variate
 ===========================================================================*/
static Helios_Thread_t thread_id;
static Helios_Thread_t thread_feed_id;
static int wdt_feed_cnt = 10;


/*===========================================================================
 * Functions
 ===========================================================================*/
static void wdt_feed_thread() {
	wdt_debug("enter wdt_feed_thread \n");
	while(wdt_feed_cnt--) {
		Helios_WDT_Feed();
		wdt_debug("wdt feed cnt : %d \n",wdt_feed_cnt);
		Helios_sleep(3);
	}
	wdt_debug("Stop feeding the dog and get ready to restart\n");
	Helios_Thread_Delete(thread_feed_id);
}

int quec_wdt_demo_test(	void)
{
    wdt_debug("quec_wdt_demo_test enter");

	int ret = Helios_WDT_Init(WDT_S);
	if(ret != 0) {
		wdt_debug("wdt init fail\n");
		return -1;
	}

	
    Helios_ThreadAttr ThreadAttr_feed = {
        .name = "wdt_feed",
        .stack_size = 1024,
        .priority = 110,
        .entry = wdt_feed_thread,
        .argv = NULL
    };

    thread_feed_id = Helios_Thread_Create(&ThreadAttr_feed);

	while(1) {
		Helios_sleep(5);
	}
	

	return 0;
}


static void wdt_test_func_entry(void * argv)
{
	Helios_sleep(3);
    wdt_debug("wdt demo thread enter, param 0x%x", argv);
	quec_wdt_demo_test();

	Helios_Thread_Delete(thread_id);

}

void quec_wdt_test(void *argv)
{
	wdt_debug(" quec_wdt_test start \n");
    (void)argv;
    Helios_ThreadAttr ThreadAttr = {
        .name = "wdt_test",
        .stack_size = 4096,
        .priority = 100,
        .entry = wdt_test_func_entry,
        .argv = NULL
    };

    thread_id = Helios_Thread_Create(&ThreadAttr);
}

application_init(quec_wdt_test, "quec_wdt_test", 2, 0);
