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
 /* DATA    2021.08.18                          */
 /* =========================================== */


/*===========================================================================
 * include files
 ===========================================================================*/

#include "helios.h"
#include "helios_debug.h"
#include "helios_os.h"
#include "helios_timer.h"

#if defined(PLAT_ASR_1606) || defined(PLAT_ASR_1609) || defined(PLAT_ASR_1602)
#include "helios_gpio.h"
#include "helios_apbtimer.h"
#endif


/*===========================================================================
 * Macro Definition
 ===========================================================================*/
#define timer_debug(fmt, ...) custom_log(APP, fmt, ##__VA_ARGS__)
#define TIMER_TIME_MS	2000 //2S
#define IS_CYCLICAL 1


/*===========================================================================
 * Variate
 ===========================================================================*/
static Helios_Thread_t thread_id;
static unsigned int g_timer_cnt = 0;


/*===========================================================================
 * Functions
 ===========================================================================*/
static void timer_isr(void) {
	g_timer_cnt++;
	
	timer_debug("g_timer_cnt = %d\n",g_timer_cnt);
}


int quec_timer_demo_test(	void)
{
	timer_debug("quec_timer_demo_test start\n");
	int timer = 0;
	int ret = -1;
	timer = Helios_Timer_init( (void* )timer_isr, NULL);

	ret = Helios_Timer_Start(timer, TIMER_TIME_MS, IS_CYCLICAL);
	if(ret != 0) {
		return -1;
	}
	

	while(1) {
		Helios_sleep(2);
	}
	
	Helios_Timer_Deinit(timer);
	return 0;
}


static void timer_test_func_entry(void * argv)
{
	Helios_sleep(3);
    timer_debug("timer demo thread enter, param 0x%x", argv);
	int ret = quec_timer_demo_test();
	if(ret != 0) {
		timer_debug("quec_timer_demo_test fail\n ");
	}

	Helios_Thread_Delete(thread_id);

}

void quec_timer_test(void *argv)
{
	timer_debug(" quec_timer_test start \n");
    (void)argv;
    Helios_ThreadAttr ThreadAttr = {
        .name = "timer_test",
        .stack_size = 4096,
        .priority = 100,
        .entry = timer_test_func_entry,
        .argv = NULL
    };

    thread_id = Helios_Thread_Create(&ThreadAttr);
}


#if defined(PLAT_ASR_1606) || defined(PLAT_ASR_1609) || defined(PLAT_ASR_1602)

#define PIN_TEST 35

static char is_conver = 0;
static void __apbtimer_cb(unsigned int data)
{
	(void)data;

	if(is_conver == 0) {
		is_conver = 1;
		Helios_GPIO_SetLevel(PIN_TEST, 0);
	} else {
		is_conver = 0;
		Helios_GPIO_SetLevel(PIN_TEST, 1);
	}
	
}



void quec_apbtimer_test(void* argv)
{
	(void)argv;
	APBTimerConfig_S timer_p = {0};

	timer_p.flag = 1;
	timer_p.period = 20;
	timer_p.timerCallbackFunc = __apbtimer_cb;
	timer_p.timerParams = 0;


	int id = Helios_Apbtimer_Create(&timer_p);

	
	Helios_GPIOInitStruct pin_para = {0};
	pin_para.dir = HELIOS_GPIO_OUTPUT;
	pin_para.pull = HELIOS_PULL_NONE;
	pin_para.value = HELIOS_LVL_HIGH;

	
	Helios_GPIO_Init(PIN_TEST, &pin_para);

	
	while (1)
	{
		Helios_Apbtimer_Start(id, &timer_p);
		while(1) {
			Helios_sleep(2);
			timer_debug("app apbtimer test running ...\r\n");
		}
	}
}
//application_init(quec_apbtimer_test, "quec_timer_test", 2, 0);


#endif


//application_init(quec_timer_test, "quec_timer_test", 2, 0);
