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
#include "helios_gpio.h"


/*===========================================================================
 * Macro Definition
 ===========================================================================*/
#define gpio_debug(fmt, ...) custom_log(APP, fmt, ##__VA_ARGS__)


/*===========================================================================
 * Variate
 ===========================================================================*/
typedef struct {
	Helios_GPIONum 			gpio_num;
	Helios_GPIOInitStruct 	gpio_struct;
}GPIOP_CFG;

static GPIOP_CFG _gpio_cfg[] = 
{	/* gpio_num   		gpio_dir     			gpio_pull    			gpio_lvl    */
    {  HELIOS_GPIO1,   	{HELIOS_GPIO_INPUT,   	HELIOS_PULL_DOWN,   	0xff     }},   // set input pull-down
    {  HELIOS_GPIO2,  	{HELIOS_GPIO_OUTPUT,  	HELIOS_PULL_NONE,       HELIOS_LVL_HIGH }}    // set output high-level
};

/*===========================================================================
 * Functions
 ===========================================================================*/
static void _quec_gpio_demo_init(void)
{
	uint16_t num = 0;
    for( num = 0; num < sizeof(_gpio_cfg)/sizeof(_gpio_cfg[0]); num++ )
    {
        Helios_GPIO_Deinit(_gpio_cfg[num].gpio_num);
        Helios_GPIO_Init(_gpio_cfg[num].gpio_num, &(_gpio_cfg[num].gpio_struct));
    }
}


static void gpio_test_func_entry(void * argv)
{
	Helios_sleep(3);
    gpio_debug("gpio demo thread enter, param 0x%x", argv);
	
    uint16_t num;
    Helios_GPIODir  gpio_dir;
    Helios_LvlMode  gpio_lvl;

	_quec_gpio_demo_init();


    /* get init info */
    for( num = 0; num < sizeof(_gpio_cfg)/sizeof(_gpio_cfg[0]); num++ )
    {
        gpio_dir = Helios_GPIO_GetDirection(_gpio_cfg[num].gpio_num);
        gpio_lvl = Helios_GPIO_GetLevel(_gpio_cfg[num].gpio_num);

        gpio_debug("gpio[%d] init", _gpio_cfg[num].gpio_num);
        gpio_debug("gpio[%d] get dir:[%d], lvl:[%d]", _gpio_cfg[num].gpio_num, gpio_dir, gpio_lvl);
    }
	Helios_sleep(3);

	
    while(1)
    {

        /* output low test */
        gpio_dir  = HELIOS_GPIO_OUTPUT;
        gpio_lvl  = HELIOS_LVL_LOW;
        for( num = 0; num < sizeof(_gpio_cfg)/sizeof(_gpio_cfg[0]); num++ )
        {
            /* set output low */
            Helios_GPIO_SetDirection(_gpio_cfg[num].gpio_num, gpio_dir);
            Helios_GPIO_SetLevel(_gpio_cfg[num].gpio_num, gpio_lvl);

            gpio_debug("gpio[%d] output low-level", _gpio_cfg[num].gpio_num);
            gpio_debug("gpio[%d] set dir:[%d], lvl:[%d]", _gpio_cfg[num].gpio_num, gpio_dir, gpio_lvl);

            /* get output low */
            gpio_dir = Helios_GPIO_GetDirection(_gpio_cfg[num].gpio_num);
            gpio_lvl = Helios_GPIO_GetLevel(_gpio_cfg[num].gpio_num);

            gpio_debug("gpio[%d] output low-level", _gpio_cfg[num].gpio_num);
            gpio_debug("gpio[%d] get dir:[%d], lvl:[%d]", _gpio_cfg[num].gpio_num, gpio_dir, gpio_lvl);
        }
        Helios_sleep(3);

        /* output high test */
        gpio_dir  = HELIOS_GPIO_OUTPUT;
        gpio_lvl  = HELIOS_LVL_HIGH;
        for( num = 0; num < sizeof(_gpio_cfg)/sizeof(_gpio_cfg[0]); num++ )
        {
            /* set output high */
            Helios_GPIO_SetDirection(_gpio_cfg[num].gpio_num, gpio_dir);
            Helios_GPIO_SetLevel(_gpio_cfg[num].gpio_num, gpio_lvl);

            gpio_debug("gpio[%d] output high-level", _gpio_cfg[num].gpio_num);
            gpio_debug("gpio[%d] set dir:[%d], lvl:[%d]", _gpio_cfg[num].gpio_num, gpio_dir, gpio_lvl);

            /* get output high */
            gpio_dir = Helios_GPIO_GetDirection(_gpio_cfg[num].gpio_num);
            gpio_lvl = Helios_GPIO_GetLevel(_gpio_cfg[num].gpio_num);

            gpio_debug("gpio[%d] output high-level", _gpio_cfg[num].gpio_num);
            gpio_debug("gpio[%d] get dir:[%d], lvl:[%d]", _gpio_cfg[num].gpio_num, gpio_dir, gpio_lvl);
        }
        Helios_sleep(3);

        /* input test */
        gpio_dir  = HELIOS_GPIO_INPUT;
        for( num = 0; num < sizeof(_gpio_cfg)/sizeof(_gpio_cfg[0]); num++ )
        {
            /* set input */
            Helios_GPIO_SetDirection(_gpio_cfg[num].gpio_num, gpio_dir);

            gpio_debug("gpio[%d] input", _gpio_cfg[num].gpio_num);
            gpio_debug("gpio[%d] set dir:[%d]", _gpio_cfg[num].gpio_num, gpio_dir);

            /* get input */
            gpio_dir = Helios_GPIO_GetDirection(_gpio_cfg[num].gpio_num);
            gpio_lvl = Helios_GPIO_GetLevel(_gpio_cfg[num].gpio_num);

            gpio_debug("gpio[%d] input", _gpio_cfg[num].gpio_num);
            gpio_debug("gpio[%d] get dir:[%d], lvl:[%d]", _gpio_cfg[num].gpio_num, gpio_dir, gpio_lvl);
        }
        Helios_sleep(3);

    }

	
}

void quec_gpio_test(void *argv)
{
	gpio_debug(" quec_gpio_test start \n");
    (void)argv;
    Helios_ThreadAttr ThreadAttr = {
        .name = "gpio_test",
        .stack_size = 4096,
        .priority = 100,
        .entry = gpio_test_func_entry,
        .argv = NULL
    };

    Helios_Thread_Create(&ThreadAttr);
}

//application_init(quec_gpio_test, "quec_gpio_test", 2, 0);
