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
#include "helios_power.h"


/*===========================================================================
 * Macro Definition
 ===========================================================================*/
#define power_debug(fmt, ...) custom_log(APP, fmt, ##__VA_ARGS__)


/*===========================================================================
 * Variate
 ===========================================================================*/
static Helios_Thread_t thread_id;

/*===========================================================================
 * Functions
 ===========================================================================*/
int quec_power_demo_test(	void)
{
	int powerup_reason = 0;
	int powerdown_reason = 0;
	int battery_vol = 0;
	
	power_debug("enter power api test!! \n");
	Helios_sleep(5);
	battery_vol = Helios_Power_GetBatteryVol();
	power_debug("get battery_vol = %d \n", battery_vol);

	powerup_reason = Helios_Power_GetUpReason();
	power_debug("power up reason: 0x%x\n", powerup_reason);

	powerdown_reason = Helios_Power_GetDownReason();
	power_debug("power down reason: 0x%x\n", powerdown_reason);
	
	Helios_sleep(60);
	//ql_power_down(1);
	power_debug("enter power reset!! \n");
	Helios_Power_Reset(0);
	return 0;
}


static void power_test_func_entry(void * argv)
{
	Helios_sleep(3);
    power_debug("power demo thread enter, param 0x%x", argv);
	quec_power_demo_test();

	Helios_Thread_Delete(thread_id);

}

void quec_power_test(void *argv)
{
	power_debug(" quec_power_test start \n");
    (void)argv;
    Helios_ThreadAttr ThreadAttr = {
        .name = "power_test",
        .stack_size = 4096,
        .priority = 100,
        .entry = power_test_func_entry,
        .argv = NULL
    };

    thread_id = Helios_Thread_Create(&ThreadAttr);
}

application_init(quec_power_test, "quec_power_test", 2, 0);
