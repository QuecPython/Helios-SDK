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
 @file	helios_wifiscan.h
 @brief	Data type definition for wifiscan.
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
2021/04/20  Jayceon.Fu	Create.
**************************************************************************/
#ifndef _HELIOS_ESIM_H
#define _HELIOS_ESIM_H

#include "mphalport.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ESIM_LPA_PROFILE_LIST_MAX_NUM 10
#if MICROPY_QPY_MODULE_ESIM_IPA

typedef void (*Helios_esim_cb_t)(uint8_t sim_id, unsigned int ind_flag,int result , void *contextPtr);

#define  ESIM_LPA_DATA_MAX                      128

typedef enum {
    HELIOS_ESIM_MODE_LPA = 0X00,
    HELIOS_ESIM_MODE_IPA = 0X01,
    HELIOS_ESIM_MODE_INVALID = 0XFF
}Helios_Esim_Mode;

typedef enum
{
    HELIOS_ESIM_NOTIFICATION_TYPE_ALL = 0,
    HELIOS_ESIM_NOTIFICATION_TYPE_ENABLE,
    HELIOS_ESIM_NOTIFICATION_TYPE_DISABLE,
    HELIOS_ESIM_NOTIFICATION_TYPE_DELETE,
    HELIOS_ESIM_NOTIFICATION_TYPE_INSTALL
} Helios_Esim_Notification_Type;

typedef enum {
    HELIOS_ESIM_GET_PROFILE_INFO = 0, 
    HELIOS_ESIM_LIST_PROFILE_INFO    
}Helios_esim_profile_list_opt;

typedef enum {
    HELIOS_ESIM_ENABLE_PROFILE = 0,
    HELIOS_ESIM_DISABLE_PROFILE,
    HELIOS_ESIM_DELETE_PROFILE,

    HELIOS_ESIM_PROFILE_TAG_MAX_NUM
} HELIOS_ESIM_PROFILE_TAG;
typedef enum
{
    HELIOS_ESIM_LPA_OTA_DOWN_PROFILE = 0,
    HELIOS_ESIM_LPA_UART_DOWN_PROFILE
} Helios_esim_lpa_profile_down_opt;

typedef enum
{
    HELIOS_ESIM_LPA_AT_INVALID_RSP = 0,
    HELIOS_ESIM_LPA_AT_PROFILE_RSP,
    HELIOS_ESIM_LPA_AT_PROFILE_LIST_RSP,
    HELIOS_ESIM_LPA_AT_NICKNAME_RSP,
    HELIOS_ESIM_LPA_AT_GET_EID_RSP,
    HELIOS_ESIM_LPA_AT_SET_APN_RSP,
    HELIOS_ESIM_LPA_AT_NOTIFICATION_LIST_RSP,
    HELIOS_ESIM_LPA_AT_NOTIFICATION_OPT_RSP,
    HELIOS_ESIM_LPA_AT_DOWN_OPT_RSP,
    HELIOS_ESIM_LPA_PROFILE_TRANS_RSP,
    HELIOS_ESIM_LPA_PROFILE_INSTALL_RSP,
    HELIOS_ESIM_LPA_VERSION_RSP,
    HELIOS_ESIM_SDK_COMPILE_RSP,
    HELIOS_ESIM_IPA_VERSION_RSP,
    HELIOS_ESIM_IPA_POLL_SET_RSP,
    HELIOS_ESIM_IPA_EIM_LIST_RSP,
    HELIOS_ESIM_IPA_EIM_ADD_RSP,
    HELIOS_ESIM_IPA_EIM_OPT_RSP,
    HELIOS_ESIM_IPA_TIMER_CFG_GET_RSP,
    HELIOS_ESIM_IPA_FALLBACK_RSP,
    HELIOS_ESIM_IPA_FALLBACK_RETURN_RSP,
    HELIOS_ESIM_LPA_AT_GET_APN_RSP,
} Helios_esim_cmd;

typedef enum
{
    HELIOS_ESIM_AT_NOTIFICATION_GET_OPT = 0,
    HELIOS_ESIM_AT_NOTIFICATION_DELETE_OPT,
    HELIOS_ESIM_AT_NOTIFICATION_REPORT_OPT
}Helios_esim_notification_opt;

typedef enum
{
    HELIOS_ESIM_EIM_UPDATE = 0,
    HELIOS_ESIM_EIM_DELETE,
    HELIOS_ESIM_EIM_ADD
} Helios_esim_eim_opt;

typedef struct {
	char iccid[ESIM_LPA_DATA_MAX+1];
	uint8_t status;
	char nickname[ESIM_LPA_DATA_MAX+1];
	char provider[ESIM_LPA_DATA_MAX+1];
} ESIM_Profile_List;

typedef struct {
    int32_t profile_num;
    ESIM_Profile_List profile_list[ESIM_LPA_PROFILE_LIST_MAX_NUM];
} Helios_Esim_Profilelistinfo_Struct;



typedef struct {
	uint32_t type;
    uint32_t seq_num;
	char iccid[ESIM_LPA_DATA_MAX+1];
} Esim_LPA_Notification_list;

typedef struct{
    uint8_t list_num;
    Esim_LPA_Notification_list notyfication_list[ESIM_LPA_PROFILE_LIST_MAX_NUM];
}Helios_Esim_LPA_Notification_list;

typedef struct {
    Helios_esim_lpa_profile_down_opt down_type;
    uint32_t   playload_len;
    uint8_t    *playload_info;
    uint32_t    data_len;
    uint8_t     data[ESIM_LPA_DATA_MAX+1];
}Helios_Esim_uart_download_resp;


typedef enum {
    HELIOS_EIMIDTYPEOID = 1,
    HELIOS_EIMIDTYPEFQDN,
    HELIOS_EIMIDTYPEPROPRIETARY
}Helios_eim_id_type;

typedef struct {
	bool        status;
    Helios_eim_id_type eim_type;
	char eim_id_info[ESIM_LPA_DATA_MAX+1];
    char eim_fqdn_info[ESIM_LPA_DATA_MAX+1];
} Esim_IPA_Eim_list;

typedef struct{
    int32_t element_num;
    Esim_IPA_Eim_list notyfication_list[ESIM_LPA_PROFILE_LIST_MAX_NUM];
}Helios_Esim_Eim_list;

typedef struct {
    uint32_t    ipa_poll_interval;
    uint32_t    rollback_interval;
    #if 0
    bool        auto_sync_flag;
    bool        regular_sync_flag;
    uint32_t    regular_interval;
    #endif
}Helios_esim_ipa_cfg_resp;


typedef struct {
    uint32_t data_len;
    char *data;
}Helios_data_array;

typedef struct {
    Helios_esim_notification_opt opt;              
    uint32_t                apdu_result_code; 
    uint32_t                result;           
    Helios_data_array      rsp_info;           
}Helios_esim_notification_resp;

int Helios_Esim_init(Helios_Esim_Mode mode);
int Helios_Esim_deinit();
int Helios_Esim_Get_Eid(void);
int Helios_Esim_Add_Event_Handler(Helios_esim_cb_t handlerPtr);
int Helios_Esim_Get_Profiles_Info(Helios_esim_profile_list_opt listmode);
int Helios_Esim_LPA_Profile_Handle(HELIOS_ESIM_PROFILE_TAG profile_tag, uint8_t *iccid);
int Helios_Esim_LPA_Set_Nickname(uint8_t *iccid,uint8_t *nickname);
int Helios_Esim_LPA_Get_Version(void);
int Helios_Esim_LPA_Get_CompileTime(void);
int Helios_Esim_LPA_Profile_Ota(Helios_esim_lpa_profile_down_opt download_mode,uint8_t *activationCode, uint8_t *confirmationCode);
int Helios_Esim_LPA_Profile_Trans(uint32_t total_len,bool state,uint8_t seq,uint32_t data_len,uint8_t *data);
int Helios_Esim_LPA_Get_Notification_List(Helios_Esim_Notification_Type type);
int Helios_Esim_LPA_Notification_hdlr(Helios_esim_notification_opt opt_mode,uint32_t seq_num);
int Helios_Esim_IPA_Poll_Interval_Set(int sec);
int Helios_Esim_IPA_Eim_List(void);
int Helios_Esim_IPA_Eim_Info_Opt(uint8_t *eim_id,uint8_t *eim_domain,Helios_esim_eim_opt mode);
int Helios_Esim_IPA_Timer_Cfg_Get(void);
int Helios_Esim_IPA_Fallback(void);
int Helios_Esim_IPA_Fallback_Return(void);
int Helios_Esim_LPA_Get_Apn(void);
int Helios_Esim_LPA_Set_Apn(uint8_t *apn);
#else
/*-----------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#if MICROPY_QPY_MODULE_ESIM

#define HELIOS_ESIM_LPA_OTA_SUCCESS 0
#define HELIOS_ESIM_LPA_OTA_FAILED  1

typedef void (*Helios_esim_cb_t)(uint8_t sim_id, unsigned int ind_flag, void *contextPtr);

#define ESIM_LPA_EUICCID_MAX_LEN      32
#define ESIM_ICCID_MAX_LEN            20
#define ESIM_NICKNAME_MAX_LEN         64
#define ESIM_PROVIDER_NAME_MAX_LEN    64

typedef struct {
	char iccid[ESIM_ICCID_MAX_LEN+1];
	uint8_t status;
	char nickname[ESIM_NICKNAME_MAX_LEN+1];
	char provider[ESIM_PROVIDER_NAME_MAX_LEN+1];
} ESIM_Profile_List;

typedef enum {
    ESIM_ENABLE_PROFILE = 0,
    ESIM_DISABLE_PROFILE,
    ESIM_DELETE_PROFILE,

    ESIM_PROFILE_TAG_MAX_NUM
} ESIM_PROFILE_TAG;

/* ========================================= *
 *                HELIOS                     *
 * ========================================= */
typedef enum {
    HELIOS_ESIM_ENABLE_PROFILE = 0,
    HELIOS_ESIM_DISABLE_PROFILE,
    HELIOS_ESIM_DELETE_PROFILE,

    HELIOS_ESIM_PROFILE_TAG_MAX_NUM
} HELIOS_ESIM_PROFILE_TAG;

typedef struct {
    uint8_t profile_num;
    ESIM_Profile_List profile_list[ESIM_LPA_PROFILE_LIST_MAX_NUM];
} Helios_Esim_Profilelistinfo_Struct;

typedef struct {
    uint32_t seqnum;
    char iccid[ESIM_ICCID_MAX_LEN+1];
}Helios_Esim_Notifications_Info;


typedef struct {
    int info_num;
    Helios_Esim_Notifications_Info info_list[ESIM_LPA_PROFILE_LIST_MAX_NUM];
}Helios_Esim_Notifications_Info_List;


int Helios_Esim_LPA_Get_Eid(char *eid);

int Helios_Esim_LPA_Get_Profiles_Info(uint8_t listmode, Helios_Esim_Profilelistinfo_Struct *prolist_info);

int Helios_Esim_LPA_Profile_Handle(HELIOS_ESIM_PROFILE_TAG profile_tag, char *iccid);

int Helios_Esim_LPA_Profile_Ota(char *activationCode, char *confirmationCode);

int Helios_Esim_LPA_Add_Event_Handler(Helios_esim_cb_t handlerPtr);

int Helios_Esim_LPA_Report_Notifications(char *iccid);

int Helios_Esim_LPA_Remove_Notifications(uint32_t seqnum);

int Helios_Esim_LPA_Get_Notifications(Helios_Esim_Notifications_Info_List *info);

#if MICROPY_QPY_MODULE_ESIM_LPA_SET_TIMEOUT
int Helios_Esim_LPA_Set_Cmd_Timeout(int timeout);
#endif

#endif
#endif
/*-----------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif

