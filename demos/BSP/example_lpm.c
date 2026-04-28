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
#include "helios_lpm.h"
#include "helios_extint.h"


/*===========================================================================
 * Macro Definition
 ===========================================================================*/
#define lpm_debug(fmt, ...) custom_log(APP, fmt, ##__VA_ARGS__)
static int g_lpm_fd = -1;
static int g_cnt = 0;



/*===========================================================================
 * Variate
 ===========================================================================*/
static Helios_Thread_t thread_id;

/*===========================================================================
 * Functions
 ===========================================================================*/
extern int Helios_GPIO_GetLevel(Helios_GPIONUM gpio_num);
static void __lpm_irq_handler(void)
{
	int value;

	if (g_lpm_fd > 0) {
		g_cnt++;
		value = Helios_GPIO_GetLevel(HELIOS_GPIO1);
		if (value) {	//wake_up
			Helios_LPM_WakeLockAcquire(g_lpm_fd);
		}
		else {	//sleep
			Helios_LPM_WakeLockRelease(g_lpm_fd);
		}
	}	
}

static void quec_lpm_demo_test(	void)
{
	int ret = -1;
	int j = 0;
	lpm_debug("=================enter power reset!!================ \n");

	
	Helios_ExtIntStruct extint_struct1 = {0};
	extint_struct1.gpio_trigger = HELIOS_EDGE_TRIGGER;
	extint_struct1.gpio_edge = HELIOS_EDGE_BOTH;
	extint_struct1.gpio_debounce = HELIOS_DEBOUNCE_EN;
	extint_struct1.gpio_pull = HELIOS_PULL_DOWN;
	extint_struct1.eint_cb = __lpm_irq_handler;
	extint_struct1.wakeup_eint_cb = NULL;
	
	ret = Helios_ExtInt_Init(HELIOS_GPIO1,  &extint_struct1);

	if (ret) {
		lpm_debug("eint register failed, ret = %d\n", ret);
		return;
	}
	Helios_ExtInt_Enable(HELIOS_GPIO1);
	
	g_lpm_fd = Helios_LPM_WakeLockInit("lpm_test_lock", sizeof("lpm_test_lock"));
	if (g_lpm_fd <= 0) {
		lpm_debug("ql_lpm_wakelock_create, lpm_fd = %d\n", g_lpm_fd);
		return;
	}
	//ql_lpm_wakelock_lock(g_lpm_fd);
	Helios_LPM_AutoSleepEnable(1);

	while(1) {
		j++;
		lpm_debug("quec_lpm_test_task, id:%d, g_cnt=%d \n", j, g_cnt);
		Helios_sleep(3);
	}

}


static void lpm_test_func_entry(void * argv)
{
	
	Helios_sleep(3);
    lpm_debug("lpm demo thread enter, param 0x%x", argv);
	quec_lpm_demo_test();

	Helios_Thread_Delete(thread_id);

}

void quec_lpm_test(void *argv)
{
	lpm_debug(" quec_lpm_test start \n");
    (void)argv;
    Helios_ThreadAttr ThreadAttr = {
        .name = "lpm_test",
        .stack_size = 4096,
        .priority = 100,
        .entry = lpm_test_func_entry,
        .argv = NULL
    };

    thread_id = Helios_Thread_Create(&ThreadAttr);
}

//application_init(quec_lpm_test, "quec_lpm_test", 2, 0);
