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
 @file	helios_voicecall.h
 @brief	Data type definition for voicecall.
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
2021/07/13  Mia.zhong	Create.
**************************************************************************/

#ifndef _HELIOS_VOICECALL_H
#define _HELIOS_VOICECALL_H

#ifdef __cplusplus
extern "C" {
#endif
/*-----------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef void (*voicecall_cb_t)(uint8_t sim_id, int32_t event_id, void *ctx);

//mia.zhong @20220322 DTMF识别
#if defined(PLAT_ASR) && defined(CONFIG_VIOCE_CALL)
typedef void(*helios_cb_on_tone_detect)(char tone);
#endif

//mia.zhong @20210831
/*
typedef enum
{
	AUD_RECORD_ERROR = -1,
	AUD_RECORD_START = 0,
	AUD_RECORD_DATA,
	AUD_RECORD_PAUSE,
	AUD_RECORD_FINISHED,
	AUD_RECORD_DISK_FULL,
}HELIOS_VOICECALL_AUD_REC_STATE;
*/

typedef enum 
{
	HELIOS_VC_SUCCESS = 0,
	HELIOS_VC_FAILURE,

    HELIOS_VC_NOT_SUPPORT
}HELIOS_VC_ERROR_CODE;

typedef enum
{
	HELIOS_VC_AUD_REC_ERROR = -1,
	HELIOS_VC_AUD_REC_START = 0,
	HELIOS_VC_AUD_REC_DATA,
	HELIOS_VC_AUD_REC_PAUSE,
	HELIOS_VC_AUD_REC_FINISHED,
	HELIOS_VC_AUD_REC_DISK_FULL,
}HELIOS_VC_AUD_REC_STATE;

typedef int(*helios_vc_cb_on_record)(char *filename, int datalen, HELIOS_VC_AUD_REC_STATE state);

typedef enum
{
    HELIOS_VC_AUD_REC_TYPE_AMR = 0,
    HELIOS_VC_AUD_REC_TYPE_WAV
}HELIOS_VC_REC_TYPE;

typedef enum
{
    HELIOS_VC_AUD_REC_MODE_RX = 0,
    HELIOS_VC_AUD_REC_MODE_TX,
    HELIOS_VC_AUD_REC_MODE_MIX
}HELIOS_VC_REC_MODE;

typedef enum
{
	HELIOS_VC_INIT_OK_IND = 1,
	HELIOS_VC_RING_IND,
	HELIOS_VC_CONNECT_IND,
	HELIOS_VC_NOCARRIER_IND,
	HELIOS_VC_ERROR_IND,
	HELIOS_VC_CCWA_IND,
	HELIOS_VC_DIALING_IND,
	HELIOS_VC_MO_FAILED_IND,
	HELIOS_VC_HOLDING_IND,
	
	HELIOS_VC_RING_VOLTE_IND,
	HELIOS_VC_CONNECT_VOLTE_IND,
	HELIOS_VC_NOCARRIER_VOLTE_IND,
	HELIOS_VC_CCWA_VOLTE_IND,
	HELIOS_VC_DIALING_VOLTE_IND,
	HELIOS_VC_ALERTING_VOLTE_IND,
	HELIOS_VC_HOLDING_VOLTE_IND
}HELIOS_VC_EVENT_ID_E;

typedef enum{
    HELIOS_CAUSE_UNKNOWN = 0,               			/**< Unknown cause (includes "None")  */
    HELIOS_CAUSE_UNASSIGNED_NUMBER,         		/**< Unassigned (unallocated) number  */
    HELIOS_CAUSE_NO_ROUTE_TO_DEST,          		/**< No route to destination  */
    HELIOS_CAUSE_CHAN_UNACCEPTABLE,         		/**< Channel unacceptable */
    HELIOS_CAUSE_OPERATOR_BARRING,          		/**< Operator determined barring  */
    HELIOS_CAUSE_NORMAL_CLEARING,           		/**< Normal call clearing */
    HELIOS_CAUSE_USER_BUSY,                 			/**< User busy  */
    HELIOS_CAUSE_NO_USER_RESPONSE,          		/**< No user responding */
    HELIOS_CAUSE_ALERT_NO_ANSWER,           		/**< User alerting, no answer */
    HELIOS_CAUSE_CALL_REJECTED,             			/**< Call rejected  */
    HELIOS_CAUSE_NUMBER_CHANGED = 10,            		/**< Number changed */
    HELIOS_CAUSE_PREEMPTION,                			/**< Pre-emption  */
    HELIOS_CAUSE_NONSELECTED_USER_CLEAR,    	/**< Non selected user clearing */
    HELIOS_CAUSE_DEST_OUT_OF_ORDER,         		/**< Destination out of order */
    HELIOS_CAUSE_INVALID_NUMFORMAT,         		/**< Invalid number format (incomplete) */
    HELIOS_CAUSE_FACILITY_REJECT,           			/**< Facility rejected  */
    HELIOS_CAUSE_STATUSENQ_RESPONSE,       	       /**< Response to STATUS ENQUIRY */
    HELIOS_CAUSE_NORMAL_UNSPECIFIED,        		/**< Normal, unspecified  */
    HELIOS_CAUSE_NO_CCT_AVAILABLE,          		/**< No circuit/channel available */
    HELIOS_CAUSE_NETWORK_OUT_OF_ORDER,      	/**< Network out of order */
    HELIOS_CAUSE_TEMP_FAILURE = 20,              			/**< Temporary failure  */
    /*21-30*/
    HELIOS_CAUSE_CONGESTION,                			/**< Switching equipment congestion */
    HELIOS_CAUSE_ACCESSINFO_DISCARDED,     		 /**< Access information discarded */
    HELIOS_CAUSE_CIRCUIT_UNAVAILABLE,       		/**< Requested circuit/channel unavailable  */
    HELIOS_CAUSE_RESOURCES_UNAVAILABLE,     		/**< Resources unavailable, unspecified */
    HELIOS_CAUSE_QOS_UNAVAIL,               			/**< Quality of service (QoS) unavailable */
    HELIOS_CAUSE_FACILITY_NOTSUBSCRIBED,    		/**< Requested facility not subscribed  */
    HELIOS_CAUSE_MT_CALLBARRING_IN_CUG,     		/**< Incoming (MT) calls barred within CUG  */
    HELIOS_CAUSE_BEARERCAP_NOTAUTHORIZED,  	 /**< Bearer capability not authorized */
    HELIOS_CAUSE_BEARERCAP_UNAVAILABLE,     		/**< Bearer capability not available  */
    HELIOS_CAUSE_SVC_UNAVAILABLE = 30,          			/**< Service or option not available  */
    /*31-40*/
    HELIOS_CAUSE_BEARERSVC_NOT_IMPLEMENTED, 	/**< Bearer service not implemented */
    HELIOS_CAUSE_ACMMAX_REACHED,           			 /**< ACM equal to, or greater than, ACMmax  */
    HELIOS_CAUSE_FACILITY_NOT_IMPLEMENTED,  	/**< Requested facility not implemented */
    HELIOS_CAUSE_BEARERCAP_RDI_ONLY,        		/**< Only RDI bearer capability is available  */
    HELIOS_CAUSE_SVC_NOT_IMPLEMENTED,       		/**< Service or option not implemented  */
    HELIOS_CAUSE_INVALID_TRANSACTID,        		/**< Invalid transaction ID value */
    HELIOS_CAUSE_NOT_CUG_MEMBER,            		/**< User not member of CUG */
    HELIOS_CAUSE_DEST_INCOMPATIBLE,         		/**< Incompatible destination */
    HELIOS_CAUSE_INCORRECT_MESSAGE,         		/**< Semantically incorrect message */
    HELIOS_CAUSE_TRANSIT_NETWORK_INVALID = 40,   	/**< Invalid transit network selection  */
    /*41-50*/
    HELIOS_CAUSE_NO_SUCH_MSGTYPE,          		 /**< Message type non-existent or not implemented */
    HELIOS_CAUSE_MSGTYPE_WRONG_STATE,       		/**< Message type incompatible with current protocol state */
    HELIOS_CAUSE_NO_SUCH_IE,               		/**< Information element non-existent or not implemented */
    HELIOS_CAUSE_CONDITIONAL_IE_ERROR,     		 /**< Conditional IE error */
    HELIOS_CAUSE_MSG_WRONG_STATE,           		/**< Message incompatible with current protocol state */
    HELIOS_CAUSE_RECOVERY_AFTER_TIMEOUT,    	/**< Recovery after timer expiry  */
    HELIOS_CAUSE_PROTOCOL_ERROR,            		/**< Protocol error, unspecified  */
    HELIOS_CAUSE_INTERWORKING,              			/**< Interworking, unspecified  */

	/* Error codes originated locally */
    HELIOS_CAUSE_ABNORMAL,              			/**< Abnormal release  */
    HELIOS_CAUSE_ERROR_REESTABLISHMENT_BARRED = 50,       /**< Reestablishment barred  */
    /*51-60*/
    HELIOS_CAUSE_CELL_SELECTION_IN_PROGRESS,         /**< Cell seection in progress  */
    HELIOS_CAUSE_LOWER_LAYER_FAILURE,                /**< Lower layer failure  */
    HELIOS_CAUSE_RACH_FAIL,                          /**< Rach fail  */
    
    HELIOS_CAUSE_FDN_BLOCKED,                        /**< FDN Mismatch  */

    HELIOS_CAUSE_ACCESS_CLASS_BARRED,                /**< Cell barred  */

    HELIOS_CAUSE_MAND_IE_ERROR,                      /**< Invalid mandatory information */

    HELIOS_CAUSE_EMERGENCY_ONLY,              /**< Only Emergency calls allowed */
    HELIOS_CAUSE_NO_CS_SERVICE,
    HELIOS_CAUSE_DMM_DEDICATE,                       /**< other sim in dedicate mode */
    HELIOS_CAUSE_UNALLOCATED_TMSI = 60,                      /**< unallocated TMSI */
    /*61-70*/
    HELIOS_CAUSE_ILLEGAL_MS,                      /**< Illegal MS */
    HELIOS_CAUSE_ILLEGAL_ME,                      /**< Illegal ME */
    HELIOS_CAUSE_NETWORK_FAILURE,                      /**< Network failure */
    HELIOS_CAUSE_SYNCH_FAILURE,                      /**< Synch failure */
    HELIOS_CAUSE_CALL_CANNOT_BE_IDENTIFIED,                      /**< Call cannot be identified */
    HELIOS_CAUSE_AUTH_FAILURE,                    /**< Authentication failure */

    // 67

    /*Added by cherryli@09.02.2014 for CQ69642 begin.*/
    HELIOS_RRC_REL_CAUSE_NORMAL = 68,
    HELIOS_RRC_REL_CAUSE_UNSPEC,
    HELIOS_RRC_REL_CAUSE_PRE_EMPTIVE = 70,

    /*71-80*/
    HELIOS_RRC_REL_CAUSE_CONGESTION,
    HELIOS_RRC_REL_CAUSE_RE_ESTABLISH_REJECT,
    HELIOS_RRC_REL_CAUSE_DIRECTED_SIGNALLING_REESTABLISHMENT,
    HELIOS_RRC_REL_CAUSE_USER_INACTIVITY,
    /*Added by cherryli@09.02.2014 for CQ69642 end.*/

    /*Added by cherryli@06.28.2020 CQ00121837 begin.*/
	HELIOS_CAUSE_IN_REGISTER = 75,
    /*Added by cherryli@06.28.2020 CQ00121837 end.*/

    HELIOS_VC_REASON_NOANSWER,
    HELIOS_VC_REASON_NOCARRIER,
    HELIOS_VC_REASON_BUSY,
    HELIOS_VC_REASON_PWROFF,
    HELIOS_VC_REASON_ERROR,
    /* This one must always be last in the list! */
    HELIOS_NUM_CAUSES                       				/**< Number of cause codes defined  */
} HELIOS_VC_DISCONNECT_TYPE_E;

//mia.zhong @20210831
typedef struct
{
#if	defined(PLAT_Unisoc_8850_R02)
	char filename[64];
#else
    char filename[32];
#endif
    HELIOS_VC_REC_TYPE record_type;
    HELIOS_VC_REC_MODE record_mode;
}Helios_Voicecall_Record_Process_t;

typedef struct
{
	voicecall_cb_t user_cb;
}Helios_VoiceCallInitStruct;

typedef struct {
    uint8_t id;
    uint8_t dir;
    int status; //for DSCI stat
    uint8_t type;
	uint8_t mpty;
    //UINT16 Digits[ CI_MAX_ADDRESS_LENGTH + ATCI_NULL_TERMINATOR_LENGTH ];
    char phone_num[40];
    uint8_t num_type;
    uint8_t release_direction;
}Helios_call_volte;

typedef struct 
{
     uint16_t CallId;
     char phone_num[40];
}Helios_call_incoming;

typedef struct 
{
     uint16_t CallId;
     char phone_num[40];
     int num_type;
	 uint8_t  CliValidity;
}Helios_call_waiting;

typedef struct 
{
     uint16_t CallId;
     uint8_t Cause;
     uint8_t InBandTones;
}Helios_call_mo_failed;

typedef Helios_call_incoming Helios_call_connect;
typedef Helios_call_incoming Helios_call_holding;


typedef struct 
{
     uint16_t CallId;
	 uint8_t  cause;
}Helios_call_disconnect;

typedef enum
{
	HELIOS_AUD_RING_NONE  =  0,    //no ring tone
	HELIOS_AUD_RING_NOKIA,		   //invalid now
	HELIOS_AUD_RING_DIAL_TONE,
	HELIOS_AUD_RING_CUSTOMER_DEF,
		
	HELIOS_AUD_RING_MAX,
}HELIOS_AUD_RING_TYPE_E;


int Helios_VoiceCall_Register(Helios_VoiceCallInitStruct *info);

int Helios_VoiceCall_Auto_Answer(uint8_t nSim, uint8_t times);

int Helios_VoiceCall_start(uint8_t nSim, char* dial_num);

int Helios_VoiceCall_Answer(uint8_t nSim);

int Helios_VoiceCall_End(uint8_t nSim);

int Helios_VoiceCall_Start_Dtmf(uint8_t nSim, char *dtmf, uint16_t duration);

int Helios_VoiceCall_Set_Fw(uint8_t nSim, int reason, int fwmode, char* phone_num);

int Helios_VoiceCall_Set_CallWait(uint8_t nSim, int enable);

int Helios_VoiceCall_Get_CallWait(uint8_t nSim);

int Helios_VoiceCall_CallHold(uint8_t nSim, int n);
//mia.zhong @20220322 DTMF识别
#if defined(PLAT_ASR) && defined(CONFIG_VIOCE_CALL)
int Helios_VoiceCall_Tone_Detect(uint8_t enable);
int Helios_VoiceCall_Tone_Detect_Set_Cb(helios_cb_on_tone_detect cb);
#endif

//mia.zhong @20210831
//int Helios_Voicecall_Set_Record_Callback(helios_vc_cb_on_record record_cb);
// #if defined(PLAT_ASR) || defined(PLAT_Unisoc)
HELIOS_VC_ERROR_CODE Helios_Voicecall_Set_Auto_Record(uint8_t enable, Helios_Voicecall_Record_Process_t *param);

HELIOS_VC_ERROR_CODE Helios_VoiceCall_Start_Record(Helios_Voicecall_Record_Process_t *param);

HELIOS_VC_ERROR_CODE Helios_VoiceCall_Stop_Record(void);
// #endif

// #if defined(PLAT_ASR)// || defined(PLAT_Unisoc)
HELIOS_VC_ERROR_CODE Helios_VoiceCall_Start_Record_Stream(Helios_Voicecall_Record_Process_t *param, helios_vc_cb_on_record record_cb);
// #endif

#if defined(PLAT_Unisoc) || defined(PLAT_Unisoc_8910_R05)
#if defined(CONFIG_VIOCE_CALL)
HELIOS_VC_ERROR_CODE Helios_VoiceCall_Set_Ringtone_type(HELIOS_AUD_RING_TYPE_E type);
#endif
#endif

#if defined(PLAT_ASR_1803s) || defined(PLAT_ASR_1803sc) || MICROPY_QPY_MODULE_AUTOCANCEL
int Helios_VoiceCall_Set_Autocancel_Flag(uint8_t enable);

uint8_t Helios_VoiceCall_Get_Autocancel_Flag(void);

#endif

#if defined(PLAT_ASR_1606)
HELIOS_VC_ERROR_CODE Helios_VoiceCall_Set_Record_Check_Flag(unsigned char set);

unsigned char Helios_VoiceCall_Get_Record_Check_Flag(void);
#endif
/*-----------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif

