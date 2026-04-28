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
#include "helios_extint.h"


/*===========================================================================
 * Macro Definition
 ===========================================================================*/
#define extint_debug(fmt, ...) custom_log(APP, fmt, ##__VA_ARGS__)

/*===========================================================================
 * Enum
 ===========================================================================*/
typedef enum
{
    INT_CB01,
    INT_CB02
} quec_IntSel;



/*===========================================================================
 * Variate
 ===========================================================================*/
static Helios_Thread_t thread_id;
static quec_IntSel quec_intsel_flg = INT_CB01;

/*===========================================================================
 * Functions
 ===========================================================================*/
extern int Helios_GPIO_GetLevel(Helios_GPIONUM gpio_num);

static void _gpioint_callback01()
{
    extint_debug("gpio[%d] int lvl:[%d]", HELIOS_GPIO1, Helios_GPIO_GetLevel(HELIOS_GPIO1));

    extint_debug("Welcome to Quectel!");
}

static void _gpioint_callback02()
{
    extint_debug("gpio[%d] int lvl:[%d]", HELIOS_GPIO2, Helios_GPIO_GetLevel(HELIOS_GPIO2));

    extint_debug("Quectel is No.1!");
}
static void quec_extint_demo_test(	void)
{
	Helios_ExtInt_Deinit(HELIOS_GPIO1);
	Helios_ExtInt_Deinit(HELIOS_GPIO2);

	
	Helios_ExtIntStruct extint_struct1 = {0};
	extint_struct1.gpio_trigger = HELIOS_EDGE_TRIGGER;
	extint_struct1.gpio_edge = HELIOS_EDGE_RISING;
	extint_struct1.gpio_debounce = HELIOS_DEBOUNCE_EN;
	extint_struct1.gpio_pull = HELIOS_PULL_DOWN;
	extint_struct1.eint_cb = _gpioint_callback01;
	extint_struct1.wakeup_eint_cb = NULL;

	Helios_ExtIntStruct extint_struct2 = {0};
	extint_struct2.gpio_trigger = HELIOS_EDGE_TRIGGER;
	extint_struct2.gpio_edge = HELIOS_EDGE_FALLING;
	extint_struct2.gpio_debounce = HELIOS_DEBOUNCE_EN;
	extint_struct2.gpio_pull = HELIOS_PULL_UP;
	extint_struct2.eint_cb = _gpioint_callback02;
	extint_struct2.wakeup_eint_cb = NULL;
	
	Helios_ExtInt_Init(HELIOS_GPIO1,  &extint_struct1);
	Helios_ExtInt_Init(HELIOS_GPIO2,  &extint_struct2);
		

    Helios_sleep(20);

    while(1)
    {

        if( quec_intsel_flg == INT_CB01 )
        {
            if( Helios_ExtInt_Disable(HELIOS_GPIO1) == 0 )
            {
                extint_debug("gpio[%d] int disable, enable gpio[%d] int", HELIOS_GPIO1, HELIOS_GPIO2);
                Helios_ExtInt_Enable(HELIOS_GPIO2);
                quec_intsel_flg = INT_CB02;
            }
        }
        else/* ql_intsel_flg == INT_CB02 */
        {
            if( Helios_ExtInt_Disable(HELIOS_GPIO2) == 0 )
            {
                extint_debug("gpio[%d] int disable, enable gpio[%d] int", HELIOS_GPIO2, HELIOS_GPIO1);
                Helios_ExtInt_Enable(HELIOS_GPIO1);
                quec_intsel_flg = INT_CB01;
            }
        }

        Helios_sleep(20);
    }
}


static void extint_test_func_entry(void * argv)
{
	Helios_sleep(3);
    extint_debug("adc demo thread enter, param 0x%x", argv);
	quec_extint_demo_test();

	Helios_Thread_Delete(thread_id);

}

void quec_extint_test(void *argv)
{
	extint_debug(" quec_extint_test start \n");
    (void)argv;
    Helios_ThreadAttr ThreadAttr = {
        .name = "extint_test",
        .stack_size = 4096,
        .priority = 100,
        .entry = extint_test_func_entry,
        .argv = NULL
    };

    thread_id = Helios_Thread_Create(&ThreadAttr);
}

//application_init(quec_extint_test, "quec_extint_test", 2, 0);
