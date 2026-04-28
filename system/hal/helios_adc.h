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
 @file	helios_adc.h
 @brief	Data type definition for ADC.
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
2021/03/29  Felix.Ye	Create.
**************************************************************************/

#ifndef _HELIOS_ADC_H
#define _HELIOS_ADC_H

#ifdef __cplusplus
extern "C" {
#endif



/**
 * Uniform channel interface to the PY layer
 */
typedef enum {
	HELIOS_ADC0 = 0,
	HELIOS_ADC1,
	HELIOS_ADC2,
	HELIOS_ADC3,
}Helios_ADCNum;

/**
 * The PY layer and the Adapter layer interface transform 
 */
typedef struct {
	Helios_ADCNum export_adc_no;
	uint32_t internal_adc_no;
}Helios_ADCMap;


/**
 * @brief:
 *      ADC OPEN INIT
 *
 * @param:
 *      NULL
 * @return:
 *      open adc result, 0 for success,-1 for failure
 */
int Helios_ADC_Init(void);


/**
 * @brief:
 *      GET ADC VALUE
 *
 * @param:
 *      \adc_port [in]         - adc channel number
 *      \value    [out]        - adc get value
 * @return:
 *      get adc value result,-1 for failure
 */
int Helios_ADC_Read(Helios_ADCNum adc_port);


/**
 * @brief:
 *      ADC CLOSE
 *
 * @param:
 *      NULL
 * @return:
 *      close adc result, 0 for success,-1 for failure
 */
int Helios_ADC_Deinit(void);

/**
 * @brief:
 *      Get  BC25PA termperature api
 *
 * @param:
 *      NULL
 * @return:
 *      termperature value
 */
#if defined(PLAT_RDA)
int Helios_Get_Temperature();
#endif
#ifdef __cplusplus
} /*"C" */
#endif

#endif

