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
#include "helios_adc.h"


/*===========================================================================
 * Macro Definition
 ===========================================================================*/
#define adc_debug(fmt, ...) custom_log(APP, fmt, ##__VA_ARGS__)


/*===========================================================================
 * Variate
 ===========================================================================*/
static Helios_Thread_t thread_id;

/*===========================================================================
 * Functions
 ===========================================================================*/
int quec_adc_demo_test(	void)
{
	int adc_value = 0;
	Helios_ADC_Init();

	while(1) {
		adc_value = Helios_ADC_Read(HELIOS_ADC0);
		adc_debug("ADC[0]: adc_value=[%d]", adc_value );
		
		adc_value = Helios_ADC_Read(HELIOS_ADC1);
		adc_debug("ADC[1]: adc_value=[%d]", adc_value );
		
		adc_value = Helios_ADC_Read(HELIOS_ADC2);
		adc_debug("ADC[2]: adc_value=[%d]", adc_value );
#ifndef QL_APP_PROJECT_DEF_EC200U
		adc_value = Helios_ADC_Read(HELIOS_ADC3);
		adc_debug("ADC[3]: adc_value=[%d]", adc_value );
#endif
		Helios_sleep(2);
	}
	
	Helios_ADC_Deinit();
	return 0;
}


static void adc_test_func_entry(void * argv)
{
	Helios_sleep(3);
    adc_debug("adc demo thread enter, param 0x%x", argv);
	quec_adc_demo_test();

	Helios_Thread_Delete(thread_id);

}

void quec_adc_test(void *argv)
{
	adc_debug(" quec_adc_test start \n");
    (void)argv;
    Helios_ThreadAttr ThreadAttr = {
        .name = "adc_test",
        .stack_size = 4096,
        .priority = 100,
        .entry = adc_test_func_entry,
        .argv = NULL
    };

    thread_id = Helios_Thread_Create(&ThreadAttr);
}

//application_init(quec_adc_test, "quec_adc_test", 2, 0);
