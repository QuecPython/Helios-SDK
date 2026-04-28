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
#include "helios_pwm.h"


/*===========================================================================
 * Macro Definition
 ===========================================================================*/
#define pwm_debug(fmt, ...) custom_log(APP, fmt, ##__VA_ARGS__)
#define PWM_FREQ 		1000000
#define PWM_DUTY		0.4	

/*===========================================================================
 * Variate
 ===========================================================================*/
static Helios_Thread_t thread_id;

/*===========================================================================
 * Functions
 ===========================================================================*/
int quec_pwm_demo_test(	void)
{
	int ret = -1;
	int runtime = 10;

	ret = Helios_PWM_Init(HELIOS_PWM0);
	if(ret != 0) {
		pwm_debug("PWM init fail\n");
		return -1;
	}
	
	ret = Helios_PWM_Start(HELIOS_PWM0, PWM_FREQ, PWM_DUTY);
	if(ret != 0) {
		pwm_debug("PWM open fail\n");
		return -1;
	}
	
	while(runtime--) 
	{
		pwm_debug("pwm test is running!!!\n");
		Helios_sleep(1);
	}
	Helios_PWM_Stop(HELIOS_PWM0);
	ret = Helios_PWM_Deinit(HELIOS_PWM0);
	if(ret != 0) {
		pwm_debug("PWM deinit fail\n");
		return -1;
	}
	return 0;
}


static void pwm_test_func_entry(void * argv)
{
	Helios_sleep(3);
    pwm_debug("pwm demo thread enter, param 0x%x", argv);
	quec_pwm_demo_test();

	Helios_Thread_Delete(thread_id);

}

void quec_pwm_test(void *argv)
{
	pwm_debug(" quec_pwm_test start \n");
    (void)argv;
    Helios_ThreadAttr ThreadAttr = {
        .name = "pwm_test",
        .stack_size = 4096,
        .priority = 100,
        .entry = pwm_test_func_entry,
        .argv = NULL
    };

    thread_id = Helios_Thread_Create(&ThreadAttr);
}

//application_init(quec_pwm_test, "quec_pwm_test", 2, 0);
