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
 @file	helios_sms.h
 @brief	Data type definition for SIM.
*/
/**************************************************************************
===========================================================================
Copyright (c) 2021 Quectel Wireless Solution, Co., Ltd.All Rights Reserved.
Quectel Wireless Solution Proprietary and Confidential.
===========================================================================

						EDIT HISTORY FOR FILE
This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

WHEN		WHO			WHAT,WHERE,WHY
----------  ---------   ---------------------------------------------------
2021/03/30  Jayceon.Fu	Create.
**************************************************************************/

#ifndef _HELIOS_SIM_H
#define _HELIOS_SIM_H

#ifdef __cplusplus
extern "C" {
#endif
/*-----------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define HELIOS_SIM_ICCID_LEN      20
#define HELIOS_SIM_IMSI_LEN       16
#define HELIOS_SIM_PHONENUM_LEN   24

#if defined(PLAT_EIGEN) || defined(PLAT_EIGEN_718) || defined(PLAT_SONY_ALT1350)
#define HELIOS_SIM_PIN_LEN_MAX	  8
#else
#define HELIOS_SIM_PIN_LEN_MAX	  15
#endif

typedef enum
{
	HELIOS_SIM_0,
	HELIOS_SIM_1,
	NUM_OF_HELIOS_SIM
}HELIOS_SimID_ex;

typedef enum 
{
    HELIOS_SIM_SUCCESS = 0,
    HELIOS_SIM_GENERIC_FAILURE,

    HELIOS_SIM_NOT_SUPPORT
}HELIOS_SIM_ERRORCODE;

typedef enum
{
	HELIOS_SIM_SWITCH_INIT,
	HELIOS_SIM_SWITCH_START,
	HELIOS_SIM_SWITCH_PRESIM_PDP_DOWN,
	HELIOS_SIM_SWITCH_PRESIM_IMS_DOWN,
	HELIOS_SIM_SWITCH_PRESIM_PSDC_DOWN,
	HELIOS_SIM_SWITCH_CURRSIM_PDP_UP,
//#ifdef CRANE_DSS
	//HELIOS_SIM_SWITCH_CURRSIM_CFUN0,
//#endif
    HELIOS_SIM_SWITCH_PRESIM_IMS_UP,
	HELIOS_SIM_SWITCH_CURRSIM_PSDC_UP,
	HELIOS_SIM_SWITCH_ERROR
}HELIOS_SIM_SWITCH_STATE;

#define PB_USERNAME_LEN_MAX      32
#define PB_PHONENUM_LEN_MAX      24
#define PB_RECORDS_COUNT_MAX     20

typedef struct
{
	int32_t index;
	char user_name[PB_USERNAME_LEN_MAX];
	char phone_num[PB_PHONENUM_LEN_MAX];
}Helios_SIMPhoneInfoStruct;

typedef struct
{
	uint8_t count;
	Helios_SIMPhoneInfoStruct records[PB_RECORDS_COUNT_MAX];
}Helios_SIMPhoneRecordsInfoStruct;


typedef struct
{
	int32_t start_index;
	int32_t end_index;
	char *user_name;
	Helios_SIMPhoneRecordsInfoStruct phonebook;
}Helios_SIMReadPhoneBookInfoStruct;

typedef struct
{
	char pin[HELIOS_SIM_PIN_LEN_MAX+1];
}Helios_SIMPinInfoStruct;

typedef struct
{
	char puk[HELIOS_SIM_PIN_LEN_MAX+1];
	char new_pin[HELIOS_SIM_PIN_LEN_MAX+1];
}Helios_SIMUnlockPinInfoStruct;

typedef struct
{
	char old_pin[HELIOS_SIM_PIN_LEN_MAX+1];
	char new_pin[HELIOS_SIM_PIN_LEN_MAX+1];
}Helios_SIMChangePinInfoStruct;

typedef struct
{
	uint8_t pin_remain_attempts;
	uint8_t puk_remain_attempts;
	uint8_t pin2_remain_attempts;
	uint8_t puk2_remain_attempts;
}Helios_SIMRemainPinAttempts;

//mia.zhong @20211008
#if defined (PLAT_ASR)
typedef struct
{
	int len;
	char cmd[256];
    char resp[256];
}Helios_SIMGenericAccesStruct;
#endif

typedef enum 
{
   HELIOS_SIM_STATUS_NOT_INSERTED = 0,
   HELIOS_SIM_STATUS_READY,
   HELIOS_SIM_STATUS_SIM_PIN,
   HELIOS_SIM_STATUS_SIM_PUK,
   HELIOS_SIM_STATUS_PH_SIM_LOCK_PIN,
   HELIOS_SIM_STATUS_PH_SIM_LOCK_PUK,
   HELIOS_SIM_STATUS_PH_FSIM_PIN,
   HELIOS_SIM_STATUS_PH_FSIM_PUK,
   HELIOS_SIM_STATUS_SIM_PIN2,
   HELIOS_SIM_STATUS_SIM_PUK2,
   HELIOS_SIM_STATUS_PH_NET_PIN,
   HELIOS_SIM_STATUS_PH_NET_PUK,
   HELIOS_SIM_STATUS_PH_NET_SUB_PIN,
   HELIOS_SIM_STATUS_PH_NET_SUB_PUK,
   HELIOS_SIM_STATUS_PH_SP_PIN,
   HELIOS_SIM_STATUS_PH_SP_PUK,
   HELIOS_SIM_STATUS_PH_CORP_PIN,
   HELIOS_SIM_STATUS_PH_CORP_PUK,
   HELIOS_SIM_STATUS_BUSY,
   HELIOS_SIM_STATUS_BLOCKED,
   HELIOS_SIM_STATUS_UNUSEFUL,
   HELIOS_SIM_STATUS_UNKNOWN
}Helios_SIM_Status_e;    /**< Card state. */

typedef enum
{
	HELIOS_SIM1_INSERT = 1,
	HELIOS_SIM1_POLLOUT,
	HELIOS_SIM2_INSERT,
	HELIOS_SIM2_POLLOUT
} Helios_SIM_hotplug_state_e;

typedef enum
{
    HELIOS_SIM_PHONE_BOOK_STORAGE_DC,
    HELIOS_SIM_PHONE_BOOK_STORAGE_EN,
    HELIOS_SIM_PHONE_BOOK_STORAGE_FD,
    HELIOS_SIM_PHONE_BOOK_STORAGE_LD,
    HELIOS_SIM_PHONE_BOOK_STORAGE_MC,
    HELIOS_SIM_PHONE_BOOK_STORAGE_ME,
    HELIOS_SIM_PHONE_BOOK_STORAGE_MT,
    HELIOS_SIM_PHONE_BOOK_STORAGE_ON,
    HELIOS_SIM_PHONE_BOOK_STORAGE_RC,
    HELIOS_SIM_PHONE_BOOK_STORAGE_SM,
    HELIOS_SIM_PHONE_BOOK_STORAGE_AP,
    HELIOS_SIM_PHONE_BOOK_STORAGE_MBDN,
    HELIOS_SIM_PHONE_BOOK_STORAGE_MN,
    HELIOS_SIM_PHONE_BOOK_STORAGE_SDN,
    HELIOS_SIM_PHONE_BOOK_STORAGE_ICI,
    HELIOS_SIM_PHONE_BOOK_STORAGE_OCI,
}HELIOS_SIM_PHONE_BOOK_STORAGE;

typedef void (*Helios_sim_cb_t)(uint8_t sim_id, unsigned int ind_flag, void *contextPtr);

int Helios_SIM_Add_Event_Handler(Helios_sim_cb_t handlerPtr);

int Helios_SIM_SetSimDet(uint8_t sim_id, int simdet, int level);
int Helios_SIM_GetSimDet(uint8_t sim_id, int *simdet, int *level);

/**
 * @brief: get IMSI of SIM card
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 *       \imsi         - a pointer to the buffer
 *       \len          - size of buffer 
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_SIM_GetIMSI(uint8_t sim_id, void *imsi, size_t len);

/**
 * @brief: get ICCID of SIM card
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 *       \imsi         - a pointer to the buffer
 *       \len          - size of buffer 
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_SIM_GetICCID(uint8_t sim_id, void *iccid, size_t len);

/**
 * @brief: get phone number of SIM card
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 *       \imsi         - a pointer to the buffer
 *       \len          - size of buffer 
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_SIM_GetPhoneNumber(uint8_t sim_id, void *phone_num, size_t len);

/**
 * @brief: get status of SIM card
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 *       \status       - a pointer to variable for SIM card status
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_SIM_GetCardStatus(uint8_t sim_id, Helios_SIM_Status_e *status);

#if defined(PLAT_ASR_1803s) || defined(PLAT_ASR_1803sc) || defined(PLAT_ASR) || (( defined(PLAT_Unisoc_8850_R02) ||defined (PLAT_ASR_1606) || defined (PLAT_ASR_1609) || defined(PLAT_ASR_1602)) && MICROPY_QPY_MODULE_PHB)
/**
 * @brief: check phonebook is ready or not
 * @sideeffect:
 * @param:
 *       \pbready	   - [out] pb status, 0:not ready  1:ready
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_SIM_GetPbReady(uint8_t *pbready);

/**
 * @brief: write a phone number information to the phone book
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 *       \info         - a pointer to the SIMPhoneInfoStruct structure type
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_SIM_WritePhonebookRecord(uint8_t sim_id, int32_t storage, Helios_SIMPhoneInfoStruct *info);

/**
 * @brief: read the phone number records from the phone book 
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 *       \info         - a pointer to the SIMReadPhoneBookInfoStruct structure type
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_SIM_ReadPhonebookRecord(uint8_t sim_id, int32_t storage, Helios_SIMReadPhoneBookInfoStruct *info);
#endif

/**
 * @brief: enable SIM card PIN code verification, and restart will take effect
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 *       \info         - a pointer to the SIMPinInfoStruct structure type
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_SIM_PINEnable(uint8_t sim_id, Helios_SIMPinInfoStruct *info);

/**
 * @brief: disable SIM card PIN code verification
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 *       \info         - a pointer to the SIMPinInfoStruct structure type
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_SIM_PINDisable(uint8_t sim_id, Helios_SIMPinInfoStruct *info);

/**
 * @brief: when the SIM state is requested PIN/PIN2, enter the PIN/PIN2 code to verify
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 *       \info         - a pointer to the SIMPinInfoStruct structure type
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_SIM_PINVerify(uint8_t sim_id, Helios_SIMPinInfoStruct *info);

/**
 * @brief: When the SIM card status is requested PUK/PUK2 after multiple incorrect input 
 *         of PIN/PIN2 code, input PUK/PUK2 code and a new PIN/PIN2 code to unlock
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 *       \info         - a pointer to the SIMUnlockPinInfoStruct structure type
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_SIM_PINUnlock(uint8_t sim_id, Helios_SIMUnlockPinInfoStruct *info);

/**
 * @brief: After enabling SIM card PIN verification, change the SIM card PIN
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 *       \info         - a pointer to the SIMChangePinInfoStruct structure type
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_SIM_PINChange(uint8_t sim_id, Helios_SIMChangePinInfoStruct *info);

#if MICROPY_QPY_MODULE_PIN_REMATTEMPTS
int Helios_SIM_PINRemainAttempts(uint8_t sim_id, Helios_SIMRemainPinAttempts *info);
#endif

//mia.zhong @20211008
#if defined(PLAT_ASR)
int Helios_SIM_GenericAccess(uint8_t sim_id, Helios_SIMGenericAccesStruct *info);
#endif

int Helios_SIM_SwitchCard(uint8_t sim_id, void *cb);
int Helios_SIM_GetCurrentSimid(uint8_t *sim_id);
#if defined(BOARD_EC800MCN_LE_VOLVGL) || defined(BOARD_EC800MCN_LE_CPE) || defined(BOARD_EG810MEU_LA_VOLVGL)
int Helios_SIM_GetInsertStatus(uint8_t sim_id, uint8_t *status);
#endif

#if defined (PLAT_EIGEN_718)
int Helios_SIM_GetCurrentSimid(uint8_t *sim_id);
#endif

/*-----------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif

