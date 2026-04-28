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
 @file	helios_datacall.h
 @brief	Data type definition for datacall.
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
2021/03/27  Jayceon.Fu	Create.
**************************************************************************/

#ifndef _HELIOS_DATACALL_H
#define _HELIOS_DATACALL_H

#ifdef __cplusplus
extern "C" {
#endif
/*-----------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#if defined(PLAT_Qualcomm)
#include "helios_socket.h"
#elif defined(PLAT_EIGEN) || defined(PLAT_EIGEN_718)
#include "lwip/inet.h"
#include "lwip/sockets.h"
#elif defined(PLAT_SONY_ALT1350)
#include "inet.h"
#include "sockets.h"
#else
#include "inet.h"
#include "sockets.h"
#endif
#include "helios_os.h"

#if defined(PLAT_RDA)
#define HELIOS_APN_LEN_MAX 36
#define HELIOS_USR_LEN_MAX 36
#define HELIOS_PWD_LEN_MAX 36
#else
#if defined(PLAT_Qualcomm)
#define HELIOS_APN_LEN_MAX 63
#else
#define HELIOS_APN_LEN_MAX 64
#endif
#define HELIOS_USR_LEN_MAX 64
#define HELIOS_PWD_LEN_MAX 64
#endif

#define HELIOS_PDP_TYPE_NUM 3 //0~2
#if defined(PLAT_Qualcomm)
#define HELIOS_AUTH_TYPE_NUM 4 //0~3
#else
#define HELIOS_AUTH_TYPE_NUM 3 //0~2
#endif

#define HELIOS_PROFILE_IDX_MIN    Helios_DataCall_GetProfileIdxMin()
#define HELIOS_PROFILE_IDX_MAX    Helios_DataCall_GetProfileIdxMax()

typedef void (*datacall_cb_t)(int32_t profile_idx, uint8_t sim_id, int32_t status);

typedef struct
{
	datacall_cb_t user_cb;
}Helios_DataCallInitStruct;

#if defined(PLAT_Qualcomm)
typedef enum
{
	HELIOS_PROFILE_PDP_IPV4 = 0,
	HELIOS_PROFILE_PDP_IPV6 = 1,
	HELIOS_PROFILE_PDP_IPV4V6 = 2,
	HELIOS_PROFILE_PDP_MAX
}HELIOS_PROFILE_PDP_TYPE_e;

typedef enum {
	HELIOS_PROFILE_AUTH_NONE = 0,
	HELIOS_PROFILE_AUTH_PAP = 1,
	HELIOS_PROFILE_AUTH_CHAP = 2,
	HELIOS_PROFILE_AUTH_PAP_CHAP = 3,
	HELIOS_PROFILE_AUTH_TYPE_MAX
}HELIOS_PROFILE_AUTH_TYPE_e;
#endif

typedef struct
{
	int32_t ip_type;
	int32_t auth;
	char apn[HELIOS_APN_LEN_MAX + 1];
	char user[HELIOS_USR_LEN_MAX + 1];
	char pwd[HELIOS_PWD_LEN_MAX + 1];
}Helios_DataCallStartStruct;

struct ipv4_address
{
	struct in_addr ip;
	struct in_addr pri_dns;
	struct in_addr sec_dns;
};

struct ipv4_info
{
	int32_t state;                 //dial status
	int32_t reconnect;
	struct ipv4_address addr;      //IPv4 address information
};

struct ipv6_address
{
	struct in6_addr ip;
	struct in6_addr pri_dns;
	struct in6_addr sec_dns;
};

struct ipv6_info
{
	int32_t state;                 //dial status
	int32_t reconnect;
	struct ipv6_address addr;      //IPv6 address information
};

typedef struct
{
	int32_t profile_idx;
	int32_t ip_version;
	struct ipv4_info v4;
	struct ipv6_info v6;
}Helios_DataCallInfoStruct;

typedef struct
{
	int32_t profile_idx;
	int32_t ip_type;
	int32_t auth_type;
	int32_t apn_type;  //0-default apn, 1-user apn
	char apn[HELIOS_APN_LEN_MAX + 1];
	char user[HELIOS_USR_LEN_MAX + 1];
	char pwd[HELIOS_PWD_LEN_MAX + 1];
}Helios_DataCallRecordAPNStruct;

typedef struct
{
	int32_t profile_id;
	int32_t ip_type;
	int32_t auth_type;
	
	char apn[HELIOS_APN_LEN_MAX + 1];
	char user[HELIOS_USR_LEN_MAX + 1];
	char pwd[HELIOS_PWD_LEN_MAX + 1];
	
	uint8_t is_poweron_datacall; //0:no   1:yes
	uint8_t sim_id;
	uint8_t sim_mnc; // SIM card mnc, 0xff -  invalid
	uint8_t apn_type; //0:default apn  1:user apn
	uint8_t auto_connect;
	uint8_t used;
	uint8_t datacall_status; //0-datacall failed, 1-datacall succeed
}Helios_DataCallAPNInfoStruct;

typedef struct 
{
	int32_t profile_id;
	int32_t ip_type;
	int32_t auth;
	char apn[HELIOS_APN_LEN_MAX + 1];
	char usr[HELIOS_USR_LEN_MAX + 1];
	char pwd[HELIOS_PWD_LEN_MAX + 1];
	uint8_t mnc;
}Helios_DataCallDefaultAPNInfoStruct;



/**
 * @brief: datacall module initialize
 * @sideeffect:
 * @param:
 *       \profile_id   - PDP index, range [1,HELIOS_PROFILE_IDX_MAX]
 *       \sim_id	   - SIM card index, range [0,1]
 *       \info         - a pointer to the DataCallInitStruct structure type
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_DataCall_Init(int32_t profile_idx, uint8_t sim_id, Helios_DataCallInitStruct *info);

int Helios_DataCall_Deinit(void);

/**
 * @brief: start dialing
 * @sideeffect:
 * @param:
 *       \profile_id   - PDP index, range [1,HELIOS_PROFILE_IDX_MAX]
 *       \sim_id	   - SIM card index, range [0,1]
 *       \info         - a pointer to the DataCallStartStruct structure type
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_DataCall_Start(int32_t profile_idx, uint8_t sim_id, Helios_DataCallStartStruct *info);

/**
 * @brief: stop dialing
 * @sideeffect:
 * @param:
 *       \profile_id   - PDP index, range [1,HELIOS_PROFILE_IDX_MAX]
 *       \sim_id	   - SIM card index, range [0,1]
 *       \ip_type      - 0:IPV4, 1:IPV6, 2:IPV4 and IPV6
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_DataCall_Stop(int32_t profile_idx, uint8_t sim_id, int32_t ip_type);

/**
 * @brief: set whether to enable automatic reconnection 
 * @sideeffect:
 * @param:
 *       \profile_id   - PDP index, range [1,HELIOS_PROFILE_IDX_MAX]
 *       \sim_id	   - SIM card index, range [0,1]
 *       \enable       - enable the function that automatic reconnection
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_DataCall_SetAutoConnect(int32_t profile_idx, uint8_t sim_id, bool enable);

/**
 * @brief: set whether to datacall in asynchronous mode
 * @sideeffect:
 * @param:
 *       \profile_id   - PDP index, range [1,HELIOS_PROFILE_IDX_MAX]
 *       \sim_id	   - SIM card index, range [0,1]
 *       \enable       - enable the function that datacall in asynchronous mode
 * @return:
 *         0 - successful
 *        -1 - failed
*/

int Helios_DataCall_SetAsynMode(int32_t profile_idx, uint8_t sim_id, bool enable);

/**
 * @brief: get information of datacall
 * @sideeffect:
 * @param:
 *       \profile_id   - PDP index, range [1,HELIOS_PROFILE_IDX_MAX]
 *       \sim_id	   - SIM card index, range [0,1]
 *       \info         - a pointer to the DataCallInfoStruct structure type
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_DataCall_GetInfo(int32_t profile_idx, uint8_t sim_id, Helios_DataCallInfoStruct *info);

/**
 * @brief: get pdp used on poweron datacall
 * @sideeffect:
 * @param:
 *
 * @return:
 *         return PDP on success
 *        -1 - failed
*/
int Helios_DataCall_GetCurrentPDP(void);

/**
 * @brief: record the APN information used on the poweron datacall
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 *       \info         - a pointer to the Helios_DataCallRecordAPNStruct structure type
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_DataCall_RecordApn(uint8_t sim_id, Helios_DataCallRecordAPNStruct *info);
uint32_t Helios_DataCall_GetProfileIdxMin(void);
uint32_t Helios_DataCall_GetProfileIdxMax(void);

#if defined(PLAT_ASR) || defined(PLAT_Unisoc) || defined(PLAT_ASR_1803s) || defined(PLAT_ASR_1803sc)|| defined(PLAT_ASR_1606) || defined(PLAT_ASR_1609) \
    || defined(PLAT_Unisoc_8910_R05) || defined(PLAT_ASR_1602) || defined(PLAT_Unisoc_8910_R06)
int Helios_DataCall_GetApn(int paracount, uint8_t sim_id, void *apn, ...);
#endif

#if defined(PLAT_ASR) || defined(PLAT_Unisoc) || defined(PLAT_ASR_1803s) || defined(PLAT_ASR_1803sc) || defined(PLAT_Unisoc_8910_R05) || defined(PLAT_Unisoc_8910_R06)
int Helios_DataCall_SetDnsServer(int32_t profile_idx, uint8_t sim_id, char *new_pri, char *new_sec);
#endif

#if MICROPY_QPY_MODULE_DSDS
int Helios_DataCall_SetPDPContext(uint8_t sim_id,uint8_t profile_idx, Helios_DataCallStartStruct *info);
int Helios_DataCall_GetPDPContext(uint8_t sim_id,uint8_t profile_idx, Helios_DataCallStartStruct *info);
#else
int Helios_DataCall_SetPDPContext(uint8_t profile_idx, Helios_DataCallStartStruct *info);
int Helios_DataCall_GetPDPContext(uint8_t profile_idx, Helios_DataCallStartStruct *info);
#endif

#if defined(PLAT_ASR_1803s) || defined(PLAT_ASR_1803sc)
void Helios_DataCall_GetDataSpeed(uint32_t *rx, uint32_t *tx);
#endif

#ifdef PLAT_ASR
int Helios_DataCall_SetIsUseAttachApn(int attach_flag);
int Helios_DataCall_GetIsUseAttachApn(void);
#endif

//#if MICROPY_QPY_MODULE_WANINFO
typedef struct
{
    int used_MBytes_sim;
    int used_Bytes_sim;
    int recv_MBytes_sim;
    int recv_Bytes_sim;
}Helios_DataCallSimUsed;

int Helios_DataCall_GetSimUsed(uint8_t sim_id, Helios_DataCallSimUsed *info);
//#endif

/*-----------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif

