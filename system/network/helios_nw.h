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
 @file	helios_nw.h
 @brief	Data type definition for network.
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
2021/03/29  Jayceon.Fu	Create.
**************************************************************************/

#ifndef _HELIOS_NW_H
#define _HELIOS_NW_H

#ifdef __cplusplus
extern "C" {
#endif
/*-----------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define HELIOS_NW_MCC_MAX_LEN 3
#define HELIOS_NW_MNC_MAX_LEN 3
#define HELIOS_NW_CELL_INFO_MAX_NUM 7
#define HELIOS_NW_LONG_NAME_MAX_LEN	32
#define HELIOS_NW_SHORT_NAME_MAX_LEN 32

#define HELIOS_NW_MAX_BLACK_CELL_NUM 10
#define HELIOS_CELL_INFO_MAX 128

#define HELIOS_NW_DATA_REG_STATUS_IND	1	//Network registration status event
#define	HELIOS_NW_VOICE_REG_STATUS_IND	2
#define HELIOS_NW_NITZ_TIME_UPDATE_IND	3
#define HELIOS_NW_SIGNAL_QUALITY_IND	4
#define HELIOS_NW_JAMMING_DETECT_IND	5


typedef void (*network_cb_t)(uint8_t sim_id, int32_t event_id, void *ctx);

typedef struct
{
	network_cb_t user_cb;
}Helios_NwInitStruct;


typedef struct nw_list_head
{
	struct nw_list_head *next;
	struct nw_list_head *prev;
	network_cb_t user_cb;
}Helios_NwCBlistNode;

typedef struct
{
	int32_t flag;
	int32_t cid;
	int32_t mcc;
	int32_t mnc;
	int32_t lac;
	int32_t arfcn;
	int32_t rssi;
	int8_t  bsic;
}Helios_GSMInfoStruct;

typedef struct
{
	int32_t flag;
	int32_t cid;
	int32_t lcid;
	int32_t mcc;
	int32_t mnc;
	int32_t lac;
	int32_t uarfcn;
	int32_t rssi;
	int32_t psc;
}Helios_UMTSInfoStruct;

typedef struct
{
	int32_t flag;
	int32_t cid;
	int32_t mcc;
	int32_t mnc;
	int32_t tac;
	int32_t earfcn;
	int32_t rssi;
	int32_t pci;
    int32_t rsrq;
#if defined(PLAT_RDA) || defined(PLAT_ASR) || defined(PLAT_EIGEN) || defined(PLAT_EIGEN_718)|| defined(PLAT_SONY_ALT1350)
    int32_t sinr; //mia.zhong @20220209
#endif
}Helios_LTEInfoStruct;

typedef struct
{
 	int32_t gsm_info_valid;
 	int32_t gsm_info_num;
 	Helios_GSMInfoStruct gsm_info[HELIOS_NW_CELL_INFO_MAX_NUM];
 	int32_t umts_info_valid;
 	int32_t umts_info_num;
 	Helios_UMTSInfoStruct umts_info[HELIOS_NW_CELL_INFO_MAX_NUM];
 	int32_t lte_info_valid;
 	int32_t lte_info_num;
 	Helios_LTEInfoStruct lte_info[HELIOS_NW_CELL_INFO_MAX_NUM];
}Helios_NwCellInfoStruct;

typedef enum
{
	HELIOS_NW_ACCESS_TECH_GSM					= 0,
	HELIOS_NW_ACCESS_TECH_GSM_COMPACT			= 1,
	HELIOS_NW_ACCESS_TECH_UTRAN					= 2,
	HELIOS_NW_ACCESS_TECH_GSM_wEGPRS			= 3,
	HELIOS_NW_ACCESS_TECH_UTRAN_wHSDPA			= 4,
	HELIOS_NW_ACCESS_TECH_UTRAN_wHSUPA			= 5,
	HELIOS_NW_ACCESS_TECH_UTRAN_wHSDPA_HSUPA	= 6,
	HELIOS_NW_ACCESS_TECH_E_UTRAN				= 7,
	HELIOS_NW_ACCESS_TECH_UTRAN_HSPAP			= 8,
	HELIOS_NW_ACCESS_TECH_E_UTRAN_CA			= 9,
#if defined(PLAT_Qualcomm)
	HELIOS_NW_ACCESS_TECH_E_UTRAN_NBIOT,
	HELIOS_NW_ACCESS_TECH_E_UTRAN_EMTC,
#endif
	HELIOS_NW_ACCESS_TECH_NONE,
}Helios_NW_Access_Technology_e;

typedef struct
{
	int32_t nw_selection_mode;
	char mcc[HELIOS_NW_MCC_MAX_LEN+1];
	char mnc[HELIOS_NW_MNC_MAX_LEN+1];
	Helios_NW_Access_Technology_e act;
}Helios_NwSelectionInfoStruct;

typedef struct
{
	int32_t rssi;
	int32_t rscp;
	int32_t ecno;
	int32_t bit_error_rate;
}Helios_GWSignalStrengthStruct;

typedef struct
{
	int32_t rssi;
	int32_t rsrp;
	int32_t rsrq;
	int32_t cqi;
#if !defined (PLAT_RDA) //defined(PLAT_ASR_1803s) || defined(PLAT_ASR_1803sc) || defined(PLAT_Qualcomm) || defined(PLAT_Unisoc) || defined(PLAT_ASR_1606) || defined(PLAT_ASR_1609) || defined(PLAT_ASR)
    int32_t sinr;
#endif
}Helios_LTESignalStrengthStruct;

typedef struct
{
	Helios_GWSignalStrengthStruct gw_signal_strength;
	Helios_LTESignalStrengthStruct lte_signal_strength;
}Helios_NwSignalStrengthInfoStruct;

typedef struct
{
	char nitz_time[32];
	uint32_t abs_time;
	uint8_t leap_sec;
}Helios_NwNITZTimeInfoStruct;


typedef struct
{
	char long_name[HELIOS_NW_LONG_NAME_MAX_LEN+1];
	char short_name[HELIOS_NW_SHORT_NAME_MAX_LEN+1];
	char mcc[HELIOS_NW_MCC_MAX_LEN+1];
	char mnc[HELIOS_NW_MCC_MAX_LEN+1];
}Helios_NwOperatorInfoStruct;

typedef struct
{
	int32_t status;
	int32_t act;
	int32_t lac;
	int32_t cid;
	int32_t psc;
	int32_t reject_cause;
}Helios_NwRegisterInfoStruct;

typedef struct
{
	Helios_NwRegisterInfoStruct voice_reg;
	Helios_NwRegisterInfoStruct data_reg;
}Helios_NwRegisterStatusInfoStruct;

#if defined(PLAT_Qualcomm)
typedef enum
{
	HELIOS_BAND_NOCHANGE	= 0,
	HELIOS_BAND_GSM_EGSM900	= 0x01,
	HELIOS_BAND_GSM_DCS1800 = 0x02,
	HELIOS_BAND_GSM_GSM850  = 0x04,
	HELIOS_BAND_GSM_PCS1900 = 0x08,
	HELIOS_BAND_GSM_MAXVALUE = 0x0f,
	
	HELIOS_BAND_LTE_BAND1 	= 0x01,
	HELIOS_BAND_LTE_BAND2 	= 0x02,
	HELIOS_BAND_LTE_BAND3 	= 0x04,
	HELIOS_BAND_LTE_BAND4 	= 0x08,
	HELIOS_BAND_LTE_BAND5 	= 0x10,
	HELIOS_BAND_LTE_BAND8 	= 0x80,
	HELIOS_BAND_LTE_BAND12 	= 0x800,
	HELIOS_BAND_LTE_BAND13 	= 0x1000,
	HELIOS_BAND_LTE_BAND18 	= 0x20000,
	HELIOS_BAND_LTE_BAND19 	= 0x40000,
	HELIOS_BAND_LTE_BAND20 	= 0x80000,
	HELIOS_BAND_LTE_BAND26 	= 0x2000000,
	HELIOS_BAND_LTE_BAND28 	= 0x8000000,
	HELIOS_BAND_LTE_BAND39 	= 0x4000000000,

}Helios_NwBand_e;

typedef enum
{
	HELIOS_GSM_BAND  = 0,
	HELIOS_LTE_BAND  = 1,
	HELIOS_CATM_BAND = 2,
	HELIOS_NB_BAND   = 3,
	HELIOS_BAND_TYPE_MAX_NUM = 3,
}Helios_NwBandTpye_e;

typedef struct
{
	Helios_NwBandTpye_e band_type;
	uint8_t band_gsm;
	uint64_t band_low;
	uint64_t band_hign;
}Helios_NwBandStruct;

#elif defined(PLAT_ASR) || MICROPY_QPY_MODULE_NET_BAND
#define   HELIOS_BAND_GSM_MAXVALUE      0x0fff

#define   HELIOS_BAND_GSM_900           0x01 //B8
#define   HELIOS_BAND_GSM_1800          0x02        //B3
#define   HELIOS_BAND_GSM_850           0x04         //B5
#define   HELIOS_BAND_GSM_1900          0x08        //B2
#define   HELIOS_BAND_WCDMA_2100        0x10         //B1
#define   HELIOS_BAND_WCDMA_1900        0x20        //B2
#define   HELIOS_BAND_WCDMA_850         0x40         //B5
#define   HELIOS_BAND_WCDMA_900         0x80        //B8
#define   HELIOS_BAND_WCDMA_800         0x100         //B6
#define   HELIOS_BAND_WCDMA_1700        0x200        //B4
#define   HELIOS_BAND_LTE_BAND1         0x01         
#define   HELIOS_BAND_LTE_BAND2         0x02        
#define   HELIOS_BAND_LTE_BAND3         0x04         
#define   HELIOS_BAND_LTE_BAND4         0x08        
#define   HELIOS_BAND_LTE_BAND5         0x10         
#define   HELIOS_BAND_LTE_BAND7         0x40        
#define   HELIOS_BAND_LTE_BAND8         0x80        
#define   HELIOS_BAND_LTE_BAND17        0x10000          
#define   HELIOS_BAND_LTE_BAND20        0x80000         
#define   HELIOS_BAND_LTE_BAND28        0x8000000         	//add band 28
#define   HELIOS_BAND_LTE_BAND31        0x40000000         	//add band 31
#define   HELIOS_BAND_LTE_BAND33        0x100000000           //add band 33
#define   HELIOS_BAND_LTE_BAND34        0x200000000           //add band 34
#define   HELIOS_BAND_LTE_BAND38        0x2000000000          
#define   HELIOS_BAND_LTE_BAND39        0x4000000000         
#define   HELIOS_BAND_LTE_BAND40        0x8000000000          
#define   HELIOS_BAND_LTE_BAND41        0x10000000000        
#define   HELIOS_BAND_LTE_BAND65        0x1        
#define   HELIOS_BAND_LTE_BAND66        0x2        
#define   HELIOS_BAND_LTE_BAND72        0x80

typedef enum
{
	HELIOS_GSM_BAND  = 0,
	HELIOS_LTE_BAND  = 1,
	//HELIOS_CATM_BAND = 2,
	//HELIOS_NB_BAND   = 3,
	HELIOS_BAND_TYPE_MAX_NUM = 1,
}Helios_NwBandTpye_e;

typedef struct
{
	Helios_NwBandTpye_e band_type;
	uint16_t band_gsm;
	uint64_t band_low;
	uint64_t band_hign;
}Helios_NwBandStruct;
#endif

typedef enum {
	HELIOS_NW_PREF_NET_TYPE_GSM	= 0,			/**< GSM */	
	HELIOS_NW_PREF_NET_TYPE_UMTS,    			/**< UMTS . not supported in EC100Y and EC200S*/
	HELIOS_NW_PREF_NET_TYPE_GSM_UMTS,   		/**< GSM_UMTS, auto. not supported in EC100Y and EC200S */
	HELIOS_NW_PREF_NET_TYPE_GSM_UMTS_PREF_GSM,	/**< GSM_UMTS, GSM preferred. not supported in EC100Y and EC200S */
	HELIOS_NW_PREF_NET_TYPE_GSM_UMTS_PREF_UMTS,	/**< GSM_UMTS, UMTS preferred. not supported in EC100Y and EC200S */
	HELIOS_NW_PREF_NET_TYPE_LTE = 5,				/**< LTE */
	HELIOS_NW_PREF_NET_TYPE_GSM_LTE_AUTO,		/**< GSM_LTE, auto, single link */
	HELIOS_NW_PREF_NET_TYPE_GSM_LTE_PREF_GSM,	/**< GSM_LTE, GSM preferred, single link */
	HELIOS_NW_PREF_NET_TYPE_GSM_LTE_PREF_LTE,	/**< GSM_LTE, LTE preferred, single link */
	HELIOS_NW_PREF_NET_TYPE_UMTS_LTE_AUTO,		/**< UMTS_LTE, auto, single link. not supported in EC100Y and EC200S */
	HELIOS_NW_PREF_NET_TYPE_UMTS_LTE_PREF_UMTS = 10,	/**< UMTS_LTE, UMTS preferred, single link. not supported in EC100Y and EC200S */
	HELIOS_NW_PREF_NET_TYPE_UMTS_LTE_PREF_LTE,	/**< UMTS_LTE, LTE preferred, single link . not supported in EC100Y and EC200S*/ 
	HELIOS_NW_PREF_NET_TYPE_GSM_UMTS_LTE_AUTO,		/**< GSM_UMTS_LTE, auto, single link. not supported in EC100Y and EC200S */
	HELIOS_NW_PREF_NET_TYPE_GSM_UMTS_LTE_PREF_GSM,	/**< GSM_UMTS_LTE, GSM preferred, single link. not supported in EC100Y and EC200S */
	HELIOS_NW_PREF_NET_TYPE_GSM_UMTS_LTE_PREF_UMTS,	/**< GSM_UMTS_LTE, UMTS preferred, single link. not supported in EC100Y and EC200S */
	HELIOS_NW_PREF_NET_TYPE_GSM_UMTS_LTE_PREF_LTE = 15,	/**< GSM_UMTS_LTE, LTE preferred, single link. not supported in EC100Y and EC200S */
	HELIOS_NW_PREF_NET_TYPE_GSM_LTE_DUALLINK,	/**< GSM_LTE, dual link */
	HELIOS_NW_PREF_NET_TYPE_UMTS_LTE_DUALLINK,	/**< UMTS_LTE, dual link. not supported in EC100Y and EC200S */
	HELIOS_NW_PREF_NET_TYPE_GSM_UMTS_LTE_DUALLINK,		/**< GSM_UMTS_LTE, dual link. not supported in EC100Y and EC200S */

	HELIOS_NW_PREF_NET_TYPE_CATM,               /**< BG95 supported */	
	HELIOS_NW_PREF_NET_TYPE_GSM_CATM = 20,           /**< BG95 supported */	
	HELIOS_NW_PREF_NET_TYPE_CATNB,              /**< BG95 supported */	
	HELIOS_NW_PREF_NET_TYPE_GSM_CATNB,          /**< BG95 supported */	
	HELIOS_NW_PREF_NET_TYPE_CATM_CATNB,         /**< BG95 supported */	
	HELIOS_NW_PREF_NET_TYPE_GSM_CATM_CATNB,     /**< BG95 supported */
	HELIOS_NW_PREF_NET_TYPE_CATM_GSM = 25,           /**< BG95 supported */
	HELIOS_NW_PREF_NET_TYPE_CATNB_GSM,          /**< BG95 supported */
	HELIOS_NW_PREF_NET_TYPE_CATNB_CATM,         /**< BG95 supported */
	HELIOS_NW_PREF_NET_TYPE_GSM_CATNB_CATM,     /**< BG95 supported */
	HELIOS_NW_PREF_NET_TYPE_CATM_GSM_CATNB,     /**< BG95 supported */
	HELIOS_NW_PREF_NET_TYPE_CATM_CATNB_GSM = 30,     /**< BG95 supported */
	HELIOS_NW_PREF_NET_TYPE_CATNB_GSM_CATM,     /**< BG95 supported */
	HELIOS_NW_PREF_NET_TYPE_CATNB_CATM_GSM,     /**< BG95 supported */

	HELIOS_NW_PREF_NET_TYPE_MAX
}Helios_NW_Preferred_Network_Type_e;


#if defined(PLAT_ASR) || defined(PLAT_ASR_1606) || defined(PLAT_ASR_1609) || defined(PLAT_ASR_1602)
typedef enum
{
    HELIOS_NW_WORKMODE_NORMAL = 0,
    HELIOS_NW_WORKMODE_POC = 3,
}HELIOS_NW_WORKMODE;

typedef enum
{
    HELIOS_NW_TYPE_REDUCTION = 2,              	//decrease the transmitting power
    HELIOS_NW_TYPE_RAISE = 3,					//increase the transmitting power
}HELIOS_NW_TXPOWER_TYPE;

typedef enum
{
    HELIOS_NW_MODE_GSM = 0,     //GSM network 
    HELIOS_NW_MODE_LTE = 2,		//LTE network 
    HELIOS_NW_MODE_ALL = 6,		//ALL network 
}HELIOS_NW_TXPOWER_MODE;

/*
*
*	band
* 	GSM: 0-PGSM,1-DCS,2-PCS,3-EGSM,4-GSM450,5-GSM480,6-GSM850;
* 	LTE:1-BAND1,2-BAND2...
*/
typedef enum
{						//GSM band
	HELIOS_NW_GSM_PGSM,
  	HELIOS_NW_GSM_DCS,
    HELIOS_NW_GSM_PCS,
    HELIOS_NW_GSM_EGSM,
    HELIOS_NW_GSM_GSM450,
    HELIOS_NW_GSM_GSM480,
    HELIOS_NW_GSM_GSM850,
}HELIOS_NW_TXPOWER_GSM;

#endif

typedef struct
{
	Helios_NW_Preferred_Network_Type_e net_mode;
	int32_t roaming_switch;
}Helios_NwConfigInfoStruct;


typedef struct
{
	int32_t gsm_info_num;
	char gsm_cell_info[HELIOS_NW_MAX_BLACK_CELL_NUM][HELIOS_CELL_INFO_MAX];
	int32_t lte_info_num;
	char lte_cell_info[HELIOS_NW_MAX_BLACK_CELL_NUM][HELIOS_CELL_INFO_MAX];
}Helios_NwBackCellInfo;

typedef struct
{
	int32_t gsm_minch;
	int32_t gsm_sinr;
	int32_t gsm_rssi;
	int32_t lte_rsrp;
	int32_t lte_rsrq;
	int32_t lte_rssi;
	int32_t shake_period;
}Helios_NwJamDetConfigStruct;

/**
 * @brief: net module initialize
 * @sideeffect:
 * @param:
 *       \info         - a pointer to the NwInitStruct structure type
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_Nw_Init(Helios_NwInitStruct *info);

int Helios_Nw_Deinit(void);

/**
 * @brief: get CSQ signal strength, range [0-31], returns 99 as invalid value
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 * @return:
 *         csq - successful
 *        -1 - failed
*/
int Helios_Nw_GetCSQ(uint8_t sim_id);

/**
 * @brief: get cell information
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 *       \info         - a pointer to the NWCellInfoStruct structure type
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_Nw_GetCellInfo(uint8_t sim_id, Helios_NwCellInfoStruct *info);

/**
 * @brief: get operator information
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 *       \info         - a pointer to the NwSelectionInfoStruct structure type
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_Nw_GetSelection(uint8_t sim_id, Helios_NwSelectionInfoStruct *info);

/**
 * @brief: set operator information
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 *       \info         - a pointer to the NwSelectionInfoStruct structure type
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_Nw_SetSelection(uint8_t sim_id, Helios_NwSelectionInfoStruct *info);

/**
 * @brief: get detailed signal strength
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 *       \info         - a pointer to the NwSignalStrengthInfoStruct structure type
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_Nw_GetSignalStrength(uint8_t sim_id, Helios_NwSignalStrengthInfoStruct *info);

/**
 * @brief: get network identity and time zone
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 *       \info         - a pointer to the NwNITZTimeInfoStruct structure type
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_Nw_GetNITZTime(Helios_NwNITZTimeInfoStruct *info);

/**
 * @brief: get operator name
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 *       \info         - a pointer to the NwOperatorInfoStruct structure type
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_Nw_GetOperatorName(uint8_t sim_id, Helios_NwOperatorInfoStruct *info);

/**
 * @brief: get the status information of network registration
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 *       \info         - a pointer to the NwRegisterStatusInfoStruct structure type
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_Nw_GetRegisterStatus(uint8_t sim_id, Helios_NwRegisterStatusInfoStruct *info);

/**
 * @brief: configure network mode
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 *       \info         - a pointer to the NwConfigInfoStruct structure type
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_Nw_SetConfiguration(uint8_t sim_id, Helios_NwConfigInfoStruct *info);

/**
 * @brief: get configuration information of network mode
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 *       \info         - a pointer to the NwConfigInfoStruct structure type
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_Nw_GetConfiguration(uint8_t sim_id, Helios_NwConfigInfoStruct *info);

int Helios_Nw_SetBlackCell(uint8_t mode);
int Helios_Nw_DeleteBlackCell(int rat, char *info);
int Helios_Nw_AddBlackCell(int rat, char *info);
int Helios_Nw_GetBlackCell(Helios_NwBackCellInfo *info);
int Helios_Nw_GetBlackCellCfg(int* blackcellCfg,int* blackcellCfg_num);
int Helios_Nw_SetBlackCellCfg(int blackcellCfg,int blackcellCfg_num);
int Helios_Nw_DeleteAllBlackCell(void);

int Helios_Nw_SetDrxtm(uint8_t simid, uint16_t drx_timer_value_set);
int Helios_Nw_GetDrxtm(uint8_t simid, uint16_t *drx_timer_value_get);
int Helios_Nw_ImsIsRegister(uint8_t nSim);

#if defined(PLAT_ASR) || defined(PLAT_Unisoc) || defined(PLAT_ASR_1803s) || defined(PLAT_ASR_1803sc) || defined(PLAT_Qualcomm) \
    || defined(PLAT_ASR_1606) || defined(PLAT_ASR_1609) || defined(PLAT_Unisoc_8910_R05) || defined(PLAT_ASR_1602) || defined(PLAT_Unisoc_8910_R06)
int Helios_Nw_SetApn(char *apn, uint8_t simid);

int Helios_Nw_GetApn(char *apn, uint8_t simid);

#if defined(PLAT_ASR) || defined(PLAT_ASR_1606) || defined(PLAT_ASR_1609) || defined(PLAT_ASR_1602)
/*****************************************************************
* Function: Helios_Nw_SetWorkMode
*
* Description:
* 	Set the network working mode
* 
* Parameters:
* 	mode	  			[in] 	network mode
* Return:
* 	0			return success
*	-1 			return failure
*
*****************************************************************/
int Helios_Nw_SetWorkMode(HELIOS_NW_WORKMODE mode);


/*****************************************************************
* Function: Helios_Nw_SetTxPower
*
* Description:
* 	increase or decrease the transmitting power at a certain frequency band
* 
* Parameters:
* 	type	  			[in] 	network typr
*	value	  			[in] 	power value
*	mode	  			[in] 	network mode
*	band	  			[in] 	network band
* Return:
* 	0			return success
*	-1 			return failure
*
*****************************************************************/
int Helios_Nw_SetTxPower(HELIOS_NW_TXPOWER_TYPE type,int32_t value,HELIOS_NW_TXPOWER_MODE mode,int32_t band);
#endif

#endif


#if defined(PLAT_Qualcomm) || defined(PLAT_ASR) || MICROPY_QPY_MODULE_NET_BAND
/**
 * @brief: set configuration information of network band
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 *       \info         - a pointer to the Helios_NwBandStruct structure type
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_Nw_SetBand(uint8_t sim_id, Helios_NwBandStruct *info);

/**
 * @brief: get configuration information of network band
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 *       \info         - a pointer to the Helios_NwBandStruct structure type
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_Nw_GetBand(uint8_t sim_id, Helios_NwBandStruct *info);
#endif

#if defined(PLAT_ASR) || MICROPY_QPY_MODULE_NET_BAND
int Helios_Nw_Band_Restore(uint8_t sim_id);
#endif

#if MICROPY_QPY_MODULE_JAMDET
int Helios_Nw_SetJamdetSwitch(uint8_t simid, uint8_t opt);
int Helios_Nw_GetJamdetSwitch(uint8_t simid, uint8_t *opt);
int Helios_Nw_SetJamdetConfiguration(uint8_t simid, Helios_NwJamDetConfigStruct *pcfg);
int Helios_Nw_GetJamdetConfiguration(uint8_t simid, Helios_NwJamDetConfigStruct *pcfg);
int Helios_Nw_GetJamdetStatus(uint8_t simid, uint8_t *status);
#endif

/*-----------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif

