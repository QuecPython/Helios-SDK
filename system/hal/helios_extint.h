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
 @file	helios_extint.h
 @brief	Data type definition for Extint.
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

#ifndef _HELIOS_EXTINT_H
#define _HELIOS_EXTINT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "helios_pin.h"

/**
 * GPIO interrupt debounce
 */
typedef enum
{
    HELIOS_DEBOUNCE_DIS = 0,
    HELIOS_DEBOUNCE_EN
}Helios_DebounceMode;


/**
 * GPIO interrupt trigger
 */
typedef enum
{
    HELIOS_EDGE_TRIGGER = 0,
    HELIOS_LEVEL_TRIGGER
}Helios_TriggerMode;


/**
 * GPIO edge-trigger mode
 */
typedef enum
{
    HELIOS_EDGE_RISING = 0,
    HELIOS_EDGE_FALLING,
    HELIOS_EDGE_BOTH
}Helios_EdgeMode;


/**
 * GPIO input pull mode
 */
#ifndef HELIOS_PULL_MODE
#define HELIOS_PULL_MODE 1
typedef enum
{
    HELIOS_PULL_NONE = 0,
    HELIOS_PULL_UP,
    HELIOS_PULL_DOWN
}Helios_PullMode;
#endif


#define HANDLER_FUN_0_N(N)	HANDLER_FUN_0_n(N)
#define HANDLER_FUN_0_n(n)	HANDLER_FUN_0_##n
#define HANDLER_FUN_0_0							HANDLER_FUN(0)
#define HANDLER_FUN_0_1		HANDLER_FUN_0_0		HANDLER_FUN(1)
#define HANDLER_FUN_0_2		HANDLER_FUN_0_1		HANDLER_FUN(2)
#define HANDLER_FUN_0_3		HANDLER_FUN_0_2		HANDLER_FUN(3)
#define HANDLER_FUN_0_4		HANDLER_FUN_0_3		HANDLER_FUN(4)
#define HANDLER_FUN_0_5		HANDLER_FUN_0_4		HANDLER_FUN(5)
#define HANDLER_FUN_0_6		HANDLER_FUN_0_5		HANDLER_FUN(6)
#define HANDLER_FUN_0_7		HANDLER_FUN_0_6		HANDLER_FUN(7)
#define HANDLER_FUN_0_8		HANDLER_FUN_0_7		HANDLER_FUN(8)
#define HANDLER_FUN_0_9		HANDLER_FUN_0_8		HANDLER_FUN(9)
#define HANDLER_FUN_0_10	HANDLER_FUN_0_9		HANDLER_FUN(10)
#define HANDLER_FUN_0_11	HANDLER_FUN_0_10	HANDLER_FUN(11)
#define HANDLER_FUN_0_12	HANDLER_FUN_0_11	HANDLER_FUN(12)
#define HANDLER_FUN_0_13	HANDLER_FUN_0_12	HANDLER_FUN(13)
#define HANDLER_FUN_0_14	HANDLER_FUN_0_13	HANDLER_FUN(14)
#define HANDLER_FUN_0_15	HANDLER_FUN_0_14	HANDLER_FUN(15)
#define HANDLER_FUN_0_16	HANDLER_FUN_0_15	HANDLER_FUN(16)
#define HANDLER_FUN_0_17	HANDLER_FUN_0_16	HANDLER_FUN(17)
#define HANDLER_FUN_0_18	HANDLER_FUN_0_17	HANDLER_FUN(18)
#define HANDLER_FUN_0_19	HANDLER_FUN_0_18	HANDLER_FUN(19)
#define HANDLER_FUN_0_20	HANDLER_FUN_0_19	HANDLER_FUN(20)
#define HANDLER_FUN_0_21	HANDLER_FUN_0_20	HANDLER_FUN(21)
#define HANDLER_FUN_0_22	HANDLER_FUN_0_21	HANDLER_FUN(22)
#define HANDLER_FUN_0_23	HANDLER_FUN_0_22	HANDLER_FUN(23)
#define HANDLER_FUN_0_24	HANDLER_FUN_0_23	HANDLER_FUN(24)
#define HANDLER_FUN_0_25	HANDLER_FUN_0_24	HANDLER_FUN(25)
#define HANDLER_FUN_0_26	HANDLER_FUN_0_25	HANDLER_FUN(26)
#define HANDLER_FUN_0_27	HANDLER_FUN_0_26	HANDLER_FUN(27)
#define HANDLER_FUN_0_28	HANDLER_FUN_0_27	HANDLER_FUN(28)
#define HANDLER_FUN_0_29	HANDLER_FUN_0_28	HANDLER_FUN(29)
#define HANDLER_FUN_0_30	HANDLER_FUN_0_29	HANDLER_FUN(30)
#define HANDLER_FUN_0_31	HANDLER_FUN_0_30	HANDLER_FUN(31)
#define HANDLER_FUN_0_32	HANDLER_FUN_0_31	HANDLER_FUN(32)
#define HANDLER_FUN_0_33	HANDLER_FUN_0_32	HANDLER_FUN(33)
#define HANDLER_FUN_0_34	HANDLER_FUN_0_33	HANDLER_FUN(34)
#define HANDLER_FUN_0_35	HANDLER_FUN_0_34	HANDLER_FUN(35)
#define HANDLER_FUN_0_36	HANDLER_FUN_0_35	HANDLER_FUN(36)
#define HANDLER_FUN_0_37	HANDLER_FUN_0_36	HANDLER_FUN(37)
#define HANDLER_FUN_0_38	HANDLER_FUN_0_37	HANDLER_FUN(38)
#define HANDLER_FUN_0_39	HANDLER_FUN_0_38	HANDLER_FUN(39)
#define HANDLER_FUN_0_40	HANDLER_FUN_0_39	HANDLER_FUN(40)
#define HANDLER_FUN_0_41	HANDLER_FUN_0_40	HANDLER_FUN(41)
#define HANDLER_FUN_0_42	HANDLER_FUN_0_41	HANDLER_FUN(42)
#define HANDLER_FUN_0_43	HANDLER_FUN_0_42	HANDLER_FUN(43)
#define HANDLER_FUN_0_44	HANDLER_FUN_0_43	HANDLER_FUN(44)
#define HANDLER_FUN_0_45	HANDLER_FUN_0_44	HANDLER_FUN(45)
#define HANDLER_FUN_0_46	HANDLER_FUN_0_45	HANDLER_FUN(46)
#define HANDLER_FUN_0_47	HANDLER_FUN_0_46	HANDLER_FUN(47)
#define HANDLER_FUN_0_48	HANDLER_FUN_0_47	HANDLER_FUN(48)
#define HANDLER_FUN_0_49	HANDLER_FUN_0_48	HANDLER_FUN(49)
#define HANDLER_FUN_0_50	HANDLER_FUN_0_49	HANDLER_FUN(50)


/**
 * The PY layer and the Adapter layer interface transform 
 */
typedef struct {
	Helios_GPIONum export_pin;      //Adapter layer interface for GPIO
	uint32_t internal_pin;    //Platform layer interface for GPIO
}HELIOS_GPIOPinMap;


typedef struct {
	Helios_TriggerMode gpio_trigger;	//GPIO interrupt trigger mode  (0-EDGE_TRIGGER  1-LEVEL_TRIGGER)
	Helios_DebounceMode gpio_debounce;	//GPIO interrupt trigger debounce enable/disable  (0-disable  1-enable)
	Helios_EdgeMode gpio_edge;			//GPIO interrupt edge/level trigger configure  (0-EDGE_RISING 1-EDGE_FALLING 2-EDGE_BOTH)
	Helios_PullMode gpio_pull;			//GPIO get input pull (0-PULL_NONE 1-PULL_UP 2-PULL_DOWN)
	void *eint_cb;						//GPIO interrupt cb
	void *wakeup_eint_cb;				//GPIO interrupt cb_ctx
}Helios_ExtIntStruct;


/**
 * @brief:
 *      GPIO interrupt init
 *
 * @param:
 *      \gpio_num         [in]   GPIO number
 *      \extint_struct    [in]   extint struct
 *    
 * @return:
 *      GPIO interrupt register Result, 0 for success,-1 for failure
 */
int Helios_ExtInt_Init
			(
				Helios_GPIONum gpio_num,
				Helios_ExtIntStruct *extint_struct
			);


/**
 * @brief:
 *      GPIO interrupt enable
 *
 * @param:
 *      \gpio_num     [in]    GPIO number
 * @return:
 *      GPIO interrupt enable result, 0 for success,-1 for failure
 */
int Helios_ExtInt_Enable(Helios_GPIONum gpio_num);


/**
 * @brief:
 *      GPIO interrupt disable
 *
 * @param:
 *      \gpio_num    [in]    GPIO number
 *
 * @return:
 *      GPIO interrupt disable result, 0 for success,-1 for failure
 */
int Helios_ExtInt_Disable(Helios_GPIONum gpio_num);

/**
 * @brief:
 *      GPIO interrupt close
 *
 * @param:
 *      \gpio_num    [in]    GPIO number
 *
 * @return:
 *      GPIO interrupt close result, 0 for success,-1 for failure
 */
int Helios_ExtInt_Deinit(Helios_GPIONum gpio_num);

void Helios_ExtInt_FastSetGpio(Helios_GPIONum gpio_num);
int Helios_ExtInt_FastGetCnt();


#ifdef __cplusplus
} /*"C" */
#endif

#endif




