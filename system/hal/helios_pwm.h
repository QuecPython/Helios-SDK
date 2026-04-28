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
 @file	helios_pwm.h
 @brief	Data type definition for PWM.
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
2021/3/29  Felix.Ye	Create.
**************************************************************************/

#ifndef _HELIOS_PWM_H
#define _HELIOS_PWM_H


#ifdef __cplusplus
extern "C" {
#endif

#include "helios_pin.h"
/**
 * Uniform channel interface to the PY layer
 */
#define PWM_MAP_DEF(n) { MP_ROM_QSTR(MP_QSTR_PWM##n), MP_ROM_INT(PWM##n) }
#define PLAT_PWM_DEF(n) BOOST_PP_REPEAT_1(n,PWM_MAP_DEF)

#define PWM_HELIOS_DEF(n) HELIOS_PWM##n
#define PLAT_PWM_HELIOS_DEF(n) BOOST_PP_REPEAT_1(n,PWM_HELIOS_DEF)

#define PWM_DEF(n) PWM##n
#define PLAT_PWMn_DEF(n) BOOST_PP_REPEAT_1(n,PWM_DEF)

//PLAT_PWM_NUMMAX = PLAT_PWM_NUM - 1
#if defined(PLAT_ASR) || defined(PLAT_ASR_1606) || defined(PLAT_ASR_1609) || defined(PLAT_ASR_1602)
#define PLAT_PWM_NUMMAX 3
#elif defined(PLAT_ASR_1803s) || defined(PLAT_ASR_1803sc)
#define PLAT_PWM_NUMMAX 2
#elif defined(PLAT_Unisoc_8850) || defined(PLAT_Unisoc_8850_R02)
#if defined(BOARD_EC800GCN_GA) \
	|| defined(BOARD_EC800GCN_GA_MS) \
	|| defined(BOARD_EC800GCN_LD) \
    || defined(BOARD_EC800GCN_LD_XBND) \
	|| defined(BOARD_EC800GCN_LD_HRXM) \
	|| defined(BOARD_EC800GCN_LB) \
    || defined(BOARD_EC800GCN_TT) \
	|| defined(BOARD_EC800GCN_GA_VOLTE) \
    || defined(BOARD_EG800GLA_LD)
#define PLAT_PWM_NUMMAX 28
#elif defined(BOARD_EC600GCN_LD) \
	|| defined(BOARD_EC600GCN_LA) \
	|| defined(BOARD_EC600GCN_LA_CDD) \
	|| defined(BOARD_EC600GCN_LD_YM) \
	|| defined(BOARD_EG700GCN_LC)
#define PLAT_PWM_NUMMAX 3
#else
#error "Please confirm the unisoc_8850 platform"
#endif
#elif defined(PLAT_EIGEN)
#define PLAT_PWM_NUMMAX 16
#elif defined(PLAT_Qualcomm)
#define PLAT_PWM_NUMMAX 2
#elif defined(PLAT_ECR6600)
#define PLAT_PWM_NUMMAX 5

#elif defined(PLAT_ASR_1602)
#if defined(BOARD_EC600KCN_CC_TTS) || defined(BOARD_EC600KCN_LC)
#define PLAT_GPIO_NUM 3
#elif defined(BOARD_EC800KCN_CC_TTS) || defined(BOARD_EC800KCN_LC) || defined(BOARD_EG800KCN_GC) || defined(BOARD_EC800KCN_LC_SMS)
#define PLAT_GPIO_NUM 1
#endif

#else
#define PLAT_PWM_NUMMAX 3
// #error "Please confirm the platform"
#endif


typedef enum {
	HELIOS_PWM0 = 0,
	PLAT_PWM_HELIOS_DEF(PLAT_PWM_NUMMAX),
	HELIOS_PWMMAX
}Helios_PwnNum;

typedef enum
{
	PWM0 = 0,
	PLAT_PWMn_DEF(PLAT_PWM_NUMMAX),
	PWMMAX
}PWMn;

typedef struct
{
    int cycle;
    float duty;
}Helios_PWMInitStruct;

typedef struct {
	Helios_PwnNum export_pwm;      //Adapter layer interface for UART
	uint32_t internal_pwm;    //Platform layer interface for UART
}Helios_PWMMap;

typedef enum
{
    HELIOS_LPG_PER_125MS,
    HELIOS_LPG_PER_250MS,
    HELIOS_LPG_PER_500MS,
    HELIOS_LPG_PER_1000MS,
    HELIOS_LPG_PER_1500MS,
    HELIOS_LPG_PER_2000MS,
    HELIOS_LPG_PER_2500MS,
    HELIOS_LPG_PER_3000MS
}Helios_LpgPer;

typedef enum
{
    HELIOS_LPG_ONTIME_UNDEFINE,
    HELIOS_LPG_ONTIME_15_6MS,
    HELIOS_LPG_ONTIME_31_2MS,
    HELIOS_LPG_ONTIME_46_8MS,
    HELIOS_LPG_ONTIME_62MS,
    HELIOS_LPG_ONTIME_78MS,
    HELIOS_LPG_ONTIME_94MS,
    HELIOS_LPG_ONTIME_110MS,
    HELIOS_LPG_ONTIME_125MS,
    HELIOS_LPG_ONTIME_140MS,
    HELIOS_LPG_ONTIME_156MS,
    HELIOS_LPG_ONTIME_172MS,
    HELIOS_LPG_ONTIME_188MS,
    HELIOS_LPG_ONTIME_200MS,
    HELIOS_LPG_ONTIME_218MS,
    HELIOS_LPG_ONTIME_234MS
}Helios_LpgOntime;


/**
 * @brief:
 *      pwm init
 *
 * @param:
 *		\pwm_num           [in] pwn port
 *      \pwn_para          [in] pwm initialization structure
 *
 * @return:
 *     pwm init result, 0 for success,-1 for failure
 */
int Helios_PWM_Init(Helios_PwnNum pwm_num);

/**
 * @brief:
 *      pwm deinit
 *
 * @param:
 *		\pwm_num           [in] pwn port
 *
 * @return:
 *     pwm init result, 0 for success,-1 for failure
 */

int Helios_PWM_Deinit(Helios_PwnNum pwm_num);

/**
 * @brief:
 *      pwm start
 *
 * @param:
 *		\pwm_num           [in] pwn port
 *
 * @return:
 *     pwm init result, 0 for success,-1 for failure
 */

int Helios_PWM_Start(Helios_PwnNum pwm_num, double frequency, float duty);

/**
 * @brief:
 *      pwm stop
 *
 * @param:
 *		\pwm_num           [in] pwn port
 *
 * @return:
 *     pwm init result, 0 for success,-1 for failure
 */

int Helios_PWM_Stop(Helios_PwnNum pwm_num);


#if defined(PLAT_ASR_1803s) || defined(PLAT_ASR_1803sc)
int Helios_PWM_En_Sleep(Helios_PwnNum pwm_num,int pwm_en_sleep);
#endif

#ifdef __cplusplus
} /*"C" */
#endif

#endif

