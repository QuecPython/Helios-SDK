
#if defined(MICROPY_QPY_MODULE_LWM2M)

#ifndef __HELIOS_LWM2M_H
#define __HELIOS_LWM2M_H
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
 @file	helios_lwm2m.h
 @brief	Data type definition for lwm2m.
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
2022/02/14 burols.Wang	Create.
**************************************************************************/


#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef enum {
	Helios_Lwm2m_Config_Case_unknown 			= -1,
	Helios_Lwm2m_Config_Case_pdpcid 			= 0,
	Helios_Lwm2m_Config_Case_security 			= 1,
	Helios_Lwm2m_Config_Case_server 			= 2,
	Helios_Lwm2m_Config_Case_local_port 		= 3,
	Helios_Lwm2m_Config_Case_epnamemode 		= 4,
	Helios_Lwm2m_Config_Case_urc 				= 5,
	Helios_Lwm2m_Config_Case_startup 			= 6,
	Helios_Lwm2m_Config_Case_fota 				= 7,
	Helios_Lwm2m_Config_Case_hostdevice 		= 8,
	Helios_Lwm2m_Config_Case_reset 				= 9,
	Helios_Lwm2m_Config_Case_nettype 			= 10,
	Helios_Lwm2m_Config_Case_appaccount 		= 11,
	Helios_Lwm2m_Config_Case_apnretry 			= 12,
	Helios_Lwm2m_Config_Case_dataformat 		= 13,
	Helios_Lwm2m_Config_Case_waitafterbs 		= 14,

	#if MICROPY_QPY_MODULE_LWM2M_SUPPORT_EPNAME
	Helios_Lwm2m_Config_Case_epname 			= 15,	
	#endif	
	
	Helios_Lwm2m_Config_Case_Max				,
	
}Helios_Config_Type;

typedef enum {
	Helios_Lwm2m_ErrorCode_Success = 0,
	Helios_Lwm2m_ErrorCode_Config_Security_Error 	= -1,
	Helios_Lwm2m_ErrorCode_Config_Server_Error 		= -2,
	Helios_Lwm2m_ErrorCode_Config_EpMode_Error 		= -3,
	Helios_Lwm2m_ErrorCode_Config_Urc_Error 		= -4,
	Helios_Lwm2m_ErrorCode_Config_Startup_Error 	= -5,
	Helios_Lwm2m_ErrorCode_Config_HostDevice_Error 	= -6,
	Helios_Lwm2m_ErrorCode_Config_Reset_Error 		= -7,
	Helios_Lwm2m_ErrorCode_Config_Nettype_Error 	= -8,
	Helios_Lwm2m_ErrorCode_Config_ApnRetry_Error 	= -9,
	Helios_Lwm2m_ErrorCode_Config_AppAccount_Error 	= -10,
	Helios_Lwm2m_ErrorCode_AT_Failed 				= -11,
	Helios_Lwm2m_ErrorCode_Config_Type_Error 		= -12,
	Helios_Lwm2m_ErrorCode_Config_NO_FUNC_Error 	= -13,
	Helios_Lwm2m_ErrorCode_Config_Get_AtStr_Error   = -14,
	Helios_Lwm2m_ErrorCode_Config_Not_Support   	= -15,
}Helios_Lwm2m_Error_Code;

typedef enum {
	Helios_Lwm2m_Bootstrap_server 	= 0,
	Helios_Lwm2m_DM_server 			= 1,
	Helios_Lwm2m_Diagnostics_server = 2,
	Helios_Lwm2m_Repository_server 	= 3,
}Helios_Lwm2m_ServerType;

typedef  struct {
	Helios_Lwm2m_ServerType 		iServie_id;	// must have value
	int32_t			iSid;
	char			strServer_addr[256];
	int8_t			iBootstrap;
	int32_t			iSecrity_mode;
	char			strPsk_id[64];
	char			strPsk_key[128];
}Helios_Config_Security_t;

typedef struct {
	int32_t 		iServie_id;		// must have value
	int32_t			iLifetime;
	int32_t			iPeriod_min;
	int32_t			iPeriod_max;
	int32_t			iDisable_timeout;
	int8_t			sStoring;
	char			strBind_mode[4];
}Helios_Config_Server_t;

typedef  struct {
	int32_t			iEpmode;
	#if MICROPY_QPY_MODULE_LWM2M_SUPPORT_EPNAME
	char			strEpname[64];
	#endif
}Helios_Config_EpMode_t;

typedef  struct {
	int32_t			iUrc_on;
}Helios_Config_Urc_t;

typedef  struct {
	int32_t			iStart_up;
}Helios_Config_Startup_t;

typedef  struct {
	char   			strUnique_id[128];
	char   			strManufacture[128];
	char   			strModel[128];
	char   			strSw_version[128];
	char       		strFw_version[128];
	char       		strHw_version[128];
	int64_t   	 	lUpgrade_time;
	int8_t			iHost_id;
}Helios_Config_HostDevice_t;

typedef  struct {
	int32_t			iRset ;
}Helios_Config_Reset_t;

typedef  struct {
	int32_t			iNettype;
}Helios_Config_NetType_t;

typedef  struct {
	int32_t			iId;
	int32_t			iRetries;
	int32_t			iOff_period;
}Helios_Config_ApnRetry_t;

typedef  struct {
	char			strKey[64];
	char			strPwd[64];
}Helios_Config_AppAccount_t;

typedef  struct {
	int8_t		i8AutoDownload;
	int8_t		i8AutoUpdate;
}Helios_Config_Fota_t;

// A member of the Helios_Config_t structure, if not used, the value must be NULL
typedef  struct {
	Helios_Config_Type			config_type;
	Helios_Config_Security_t  	*config_security;
	Helios_Config_Server_t		*config_server;
	Helios_Config_EpMode_t		*config_epmode;
	Helios_Config_Urc_t			*config_urc;
	Helios_Config_Startup_t		*config_startup;
	Helios_Config_HostDevice_t	*config_hostdevice;
	Helios_Config_Reset_t		*config_reset;
	Helios_Config_NetType_t		*config_nettype;
	Helios_Config_ApnRetry_t	*config_apnretry;
	Helios_Config_AppAccount_t	*config_appaccount;
	Helios_Config_Fota_t		*config_fota;
}Helios_Config_t;

typedef int (*config_func)(Helios_Config_t *config,char 	*strAt);

typedef struct {
	Helios_Config_Type	type;
	config_func			func;
}Helios_config_list;

typedef struct __Helios_Lwm2m_Event{
	int32_t event_id; 
	int32_t event_code; 
	void 	* param; 
}Helios_Lwm2m_Event;

/*++  maybe have  application interface   --start*/
typedef  void (*lwm2m_call_cb_t)(Helios_Lwm2m_Event event);
Helios_Lwm2m_Error_Code helios_lwm2m_config(Helios_Config_t *config);

/*---lwm2m client need interface  */
Helios_Lwm2m_Error_Code helios_lwm2m_create();
Helios_Lwm2m_Error_Code helios_lwm2m_update(uint32_t ssid);
Helios_Lwm2m_Error_Code helios_lwm2m_register();
Helios_Lwm2m_Error_Code helios_lwm2m_unregister();
Helios_Lwm2m_Error_Code helios_lwm2m_free();
Helios_Lwm2m_Error_Code helios_lwm2m_get_stat(int *lwstat);
Helios_Lwm2m_Error_Code helios_lwm2m_register_callcb(lwm2m_call_cb_t callcb);
#if MICROPY_QPY_MODULE_LWM2M_ACK
Helios_Lwm2m_Error_Code helios_lwm2m_enable_ack_support(uint32_t is_eable);
Helios_Lwm2m_Error_Code helios_lwm2m_ack_messageid(uint32_t messageid,uint32_t type);
#endif
#if MICROPY_QPY_MODULE_LWM2M_SUPPORT_CHANGE
Helios_Lwm2m_Error_Code Helios_lwm2m_change_value (const char * uri,int uri_len,const char *value,int value_len);
#endif
/* >>>>must have application interface  --end */


#endif //__HELIOS_LWM2M_H

#endif //MICROPY_QPY_MODULE_LWM2M
