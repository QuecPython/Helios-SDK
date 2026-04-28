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
 @file	helios_lpm.h
 @brief	Data type definition for Low power dependent API.
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

#ifndef _HELIOS_LPM_H
#define _HELIOS_LPM_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined (PLAT_ECR6600)
typedef enum {
  HELIOS_LPM_MODE_MODEM_SLEEP,  /*close rf and clock partly*/
  HELIOS_LPM_MODE_LIGHT_SLEEP,  /*close cpu rf and clock,when weaked up system can quickly resume*/
  HELIOS_LPM_MODE_DEEP_SLEEP,   /*close cpu rf and clock,when weaked up system will reset*/
  HELIOS_LPM_MODE_SLEEP_MAX,    /*max status,should't in this status */
}Helios_LPM_Mode;

/**
 * @brief:
 *      config lpm
 * @sideeffect:
 *
 * @param:
 *      \sleep_mode    		[in]    - sleep mode
 *      \listen_interval 	[in]    - the psm listen interval
 * @return:
 *       config lpm result, 0 for success,-1 for failure
 */
int Helios_LPM_Config(Helios_LPM_Mode sleep_mode, unsigned char listen_interval);
#endif

#if defined (PLAT_aic8800m40)
typedef enum {
  HELIOS_LPM_MODE_ACTICVE, 
  HELIOS_LPM_MODE_LIGHT_SLEEP, 
  HELIOS_LPM_MODE_DEEP_SLEEP,  
  HELIOS_LPM_MODE_HIBERNATE,
  HELIOS_LPM_MODE_SLEEP_MAX,
}Helios_LPM_Mode;

/**
 * @brief:
 *      config lpm
 * @sideeffect:
 *
 * @param:
 *      \sleep_mode    		[in]    - sleep mode
 *      \listen_interval 	[in]    - the psm listen interval
 * @return:
 *       config lpm result, 0 for success,-1 for failure
 */
int Helios_LPM_Config(Helios_LPM_Mode sleep_mode, unsigned char listen_interval);
#endif


/**
 * @brief:
 *      create wakelock
 * @sideeffect:
 *
 * @param:
 *      \lock_name        [in]    - customize the Lock name
 *      \name_size        [in]    - the length for lock name
 * @return:
 *       create wakelock result, wakelock_id for success,-1 for failure
 */
int Helios_LPM_WakeLockInit(char *lock_name, size_t name_size);


/**
 * @brief:
 *       delete wakelock
 *
 * @sideeffect:
 *
 * @param:
 *      \wakelock_fd        [in]    - the ID of the deleted lock identity
 * @return:
 *      delete wakelock result, 0 for success,-1 for failure
 */
int Helios_LPM_WakeLockDeInit(int wakelock_fd);


/**
 * @brief:
 *      lock wakelock
 *
 * @sideeffect:
 *
 * @param:
 *      \wakelock_fd        [in]    - The Wakelock identity ID that needs to be locked
 * @return:
 *      lock wakelock result, 0 for success,-1 for failure
 */
int Helios_LPM_WakeLockAcquire(int wakelock_fd);

int Helios_LPM_WakeLock_GetLockActiveNum();


/**
 * @brief:
 *      unlock wakelock
 *
 * @sideeffect:
 *
 * @param:
 *      \wakelock_fd        [in]    - The Wakelock identity ID that needs to be used to release the lock
 * @return:
 *      unlock wakelock result, 0 for success,-1 for failure
 */
int Helios_LPM_WakeLockRelease(int wakelock_fd);


/**
 * @brief:
 *      Automatic sleep mode control
 *
 * @sideeffect:
 *
 * @param:
 *      \sleep_flag        [in]    - auto sleep mode control flag 0-disable auto sleep,1-enable auto sleep
 * @return:
 *      Automatic sleep mode control result, 0 for success,-1 for failure
 */
int Helios_LPM_AutoSleepEnable(uint32_t sleep_flag);

/**
 * @brief:
 *		Get wakelock num
 *
 * @sideeffect:
 *
 * @param:
 *		\NULL
 * @return:
 *		Get wakelock num result, -1 for failure 
*/
int Helios_LPM_GetWakeLockNum(void);

/**
 * @brief:
 *      set power ex
 * @sideeffect:
 *
 * @param:
 *      mode - 0:disable sleep, 1:enable sleep
 *		no_data_time - The time when the module into sleep after sending data
 *		punish_time - When an abnormal situation occurs, the time of using the enhanced dormancy mode is prohibited
 * @return:
 *      0 success
 *      else fail
 */
int Helios_LPM_EXSet(uint8_t mode, uint8_t no_data_time, uint16_t punish_time);

#if defined(PLAT_RDA)
/**
 * @brief:
 *      when into sleep modem ,will call this  register function
 *
 * @param:
 *      void *cb ,
 * @return:
 *      0     - success 
 *      other - failed
 */
int Helios_LPM_Sleep_Register_cb(void * cb);

#endif

#if defined(PLAT_RDA) \
|| defined(PLAT_Unisoc_8850) \
|| defined(PLAT_Unisoc_8850_R02) \
|| defined(PLAT_Unisoc) \
|| defined(PLAT_EIGEN) \
|| defined(PLAT_Unisoc_8910_R05)\
|| defined(PLAT_Unisoc_8910_R06)\
|| defined(PLAT_Qualcomm)\
|| defined(PLAT_EIGEN_718)
typedef struct {
  int8_t  mode;
  int8_t  tau_uint;
  int8_t  tau_time;
  int8_t  act_uint;
  int8_t  act_time;
}Helios_psm_info;
#if defined(PLAT_RDA)
typedef struct {
  /*
  i8_mode:
  0 Disables eDRX
  1 Enable eDRX
  2 Enable eDRX and enable URC +CEDRXP: <AcT-type>[,<Requeste d_eDRX_value>[,<NW-provided_eDRX_value>[,<Paging_ti me_window>]]] escalation
  3 Disable eDRX and clear all eDRX parameter configurations (reset to default if there is a default value)
  */
  int8_t i8_mode;
  int8_t i8_ActType;
  /*
  str5_Requested_eDRX:
  4 3 2 1 E-UTRAN eDRX cycle length duration
  0 0 1 0 20.48 seconds
  0 0 1 1 40.96 seconds
  0 1 0 1 81.92 seconds
  1 0 0 1 163.84 seconds
  1 0 1 0 327.68 seconds
  1 0 1 1 655.36 seconds
  1 1 0 0 1310.72 seconds
  1 1 0 1 2621.44 seconds
  1 1 1 0 5242.88 seconds
  1 1 1 1 10485.76 seconds
  */
  int8_t str5_Requested_eDRX[5];
  /* str5_Nwprovided_eDRX : The meaning of the parameter is the same as str5_Requested_eDRX */
  int8_t str5_Nwprovided_eDRX[5];
  /*  str5_Paging_time_window:
  4 3 2 1 Paging window length
  0 0 0 0 2.56 seconds
  0 0 0 1 5.12 seconds
  0 0 1 0 7.68 seconds
  0 0 1 1 10.24 seconds
  0 1 0 0 12.8 seconds
  0 1 0 1 15.36 seconds
  0 1 1 0 17.92 seconds
  0 1 1 1 20.48 seconds
  1 0 0 0 23.04 seconds
  1 0 0 1 25.6 seconds
  1 0 1 0 28.16 seconds
  1 0 1 1 30.72 seconds
  1 1 0 0 33.28 seconds
  1 1 0 1 35.84 seconds
  1 1 1 0 38.4 seconds
  1 1 1 1 40.96 seconds
 */
  int8_t str5_Paging_time_window[5];
}Helios_edrx_info;
#endif

int Helios_LPM_Set_PsmTime(uint32_t mode,uint32_t tau_uint,uint32_t tau_time,uint32_t act_uint,uint32_t act_time);

int Helios_LPM_get_PsmTime(Helios_psm_info *psm_info);
#if defined(PLAT_RDA)

int Helios_LPM_get_eDrx(Helios_edrx_info *edrx_info);

int Helios_LPM_set_eDrx(Helios_edrx_info edrx_info);
#endif
#endif

#if defined(PLAT_ASR_1606) || defined(PLAT_ASR_1609) || defined(PLAT_ASR_1602) || defined(PLAT_ASR_1803s) || defined(PLAT_ASR_1803sc)
void Helios_LPM_fast_extint(unsigned char value);
#endif

#if defined(PLAT_EIGEN) || defined(BOARD_BC32RA) || defined(PLAT_EIGEN_718)
/**
 * @brief:
 *      Force into hibernate sleep instead of be controled by T3412
 * @sideeffect:
 *
 * @param:
 *      
 * @return:
 *      0 success
 *      else fail
 */
int Helios_LPM_forcehib(void);
#endif

#ifdef __cplusplus
} /*"C" */
#endif

#endif

