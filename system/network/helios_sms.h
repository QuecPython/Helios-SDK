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
 @brief	Data type definition for SMS.
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

#ifndef _HELIOS_SMS_H
#define _HELIOS_SMS_H

#ifdef __cplusplus
extern "C" {
#endif
/*-----------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#if defined(PLAT_ASR) || defined(PLAT_ASR_1803s) || defined(PLAT_ASR_1803sc)
#define HELIOS_MAX_SMS_DATA_LEN   140 * 6 //支持6条正常短信长度
#elif defined(PLAT_Unisoc) || defined(PLAT_Qualcomm) || defined(PLAT_Unisoc_8910_R05) || defined(PLAT_Unisoc_8910_R06)
#define HELIOS_MAX_SMS_DATA_LEN   140 * 4 //支持4条正常短信长度
#else
#define HELIOS_MAX_SMS_DATA_LEN   140
#endif

#define HELIOS_SMS_NEW_MSG_IND	1

typedef void (*sms_cb_t)(uint8_t sim_id, int32_t event_id, void *ctx);

typedef struct
{
    uint8_t index;
	char mem[5];
}Helios_SMSNewMsgInfoStruct;

typedef struct
{
	sms_cb_t user_cb;
}Helios_SMSInitStruct;

typedef enum
{
	HELIOS_GSM  = 0,
	HELIOS_UCS2 = 1,
}Helios_SMS_Code_e;

typedef struct
{
	Helios_SMS_Code_e code;
	char *phone_num;
	char *msg;
}Helios_SMSSendMsgInfoStruct;

typedef struct
{
	char mem[5];
	uint16_t current_nums;
	uint16_t max_nums;
}Helios_SMSMemInfoStruct;

typedef struct
{
	Helios_SMSMemInfoStruct mem1;
	Helios_SMSMemInfoStruct mem2;
	Helios_SMSMemInfoStruct mem3;
}Helios_SMSMemGetInfoStruct;

typedef struct
{
	char mem1[5];
	char mem2[5];
	char mem3[5];
}Helios_SMSMemSetInfoStruct;

typedef struct
{
	char phone_num[32];
	char *msg_buf;
	size_t buf_len;
}Helios_SMSRecvMsgInfoStruct;

typedef struct
{
    char number[32];
    char body[280]; // 每条收到的短信长度最大为280
    char time[32];
    int  body_len;
}Helios_SMSStatusInfo;

//#if defined(PLAT_ASR_1803s) || defined(PLAT_ASR_1803sc) || (defined(PLAT_Unisoc) && !defined(BOARD_EG915UEU_AB)) || defined(PLAT_Qualcomm) || defined(PLAT_ASR_1606) || defined(PLAT_ASR_1609) || defined(PLAT_ASR) || defined(PLAT_EIGEN)
#if !defined(PLAT_Unisoc_8850) && !defined(PLAT_RDA) && !defined(PLAT_Unisoc_8850_R02)
typedef enum {
  HELIOS_SMS_DEL_MODE_DEFAULT = 0,
  HELIOS_SMS_DEL_INDEX = 0,       /* Delete only one message indicated by the index */
  HELIOS_SMS_DEL_RECV_READ,       /* Delete all received read messages */
  HELIOS_SMS_DEL_RECV_READ_SENT,  /* Delete all received read messages as well as sent MO messages */
  HELIOS_SMS_DEL_RECV_READ_MO,    /* Delete received read messages and all MO messages - sent and unsent */
  HELIOS_SMS_DEL_ALL,
  
  HELIOS_SMS_NUM_DEL_MODES
} HELIOS_SMS_DEL_MODE;

int Helios_SMS_DeleteMsg_Ex(uint8_t sim_id, uint8_t index, HELIOS_SMS_DEL_MODE del_mode);
#endif

int Helios_SMS_DecodePdu(Helios_SMSStatusInfo *info, char *data);

/**
 * @brief: SMS module initialize
 * @sideeffect:
 * @param:
 *       \info         - a pointer to the NwInitStruct structure type
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_SMS_Init(Helios_SMSInitStruct *info);

/**
 * @brief: set mode of msg
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 *       \mode         - 0:PDU, 1:TEXT
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_SMS_SetMsgMode(uint8_t sim_id, uint8_t mode);

/**
 * @brief: set code mode of msg
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 *       \mode         - 0:GSM, 1:UCS2
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_SMS_SetCodeMode(uint8_t sim_id, uint8_t mode);

/**
 * @brief: send a short message in text format
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 *       \info         - a pointer to the SMSSendMsgInfoStruct structure type
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_SMS_SendTextMsg(uint8_t sim_id, Helios_SMSSendMsgInfoStruct *info);

/**
 * @brief: send a short message in PDU format
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 *       \info         - a pointer to the SMSSendMsgInfoStruct structure type
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_SMS_SendPDUMsg(uint8_t sim_id, Helios_SMSSendMsgInfoStruct *info);

/**
 * @brief: deletes a message by index number
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 *       \index        - index number for message
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_SMS_DeleteMsg(uint8_t sim_id, uint8_t index);

/**
 * @brief: get the SMS center address
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 *       \center_addr  - a pointer for the SMS center address
 *       \len		   - buffer length
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_SMS_GetCenterAddress(uint8_t sim_id, void *center_addr, size_t len);

/**
 * @brief: set the SMS center address
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 *       \center_addr  - a pointer for the SMS center address
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_SMS_SetCenterAddress(uint8_t sim_id, void *center_addr);

/**
 * @brief: get the storage information of SM and ME
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 *       \center_addr  - a pointer to the SMSMemGetInfoStruct structure type
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_SMS_GetSavingLocation(uint8_t sim_id, Helios_SMSMemGetInfoStruct *info);

/**
 * @brief: set the location of SMS storage
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 *       \info		   - a pointer to the SMSMemSetInfoStruct structure type
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_SMS_SetSavingLocation(uint8_t sim_id, Helios_SMSMemSetInfoStruct *info);

/**
 * @brief: set the processing mode when a message is received
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 *       \mode		   - 
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_SMS_SetReceiveDealMode(uint8_t sim_id, int32_t mode);

/**
 * @brief: read a single short message by text format
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 *       \index		   - index number for message
 *       \text_msg	   - a pointer to the SMSRecvMsgInfoStruct structure type
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_SMS_ReadTextMsg(uint8_t sim_id, uint8_t index, Helios_SMSRecvMsgInfoStruct *text_msg);

/**
 * @brief: read a single short message by PDU format
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 *       \index		   - index number for message
 *       \pdu_msg	   - a pointer to the SMSRecvMsgInfoStruct structure type
 * @return:
 *         0 - successful
 *        -1 - failed
*/
int Helios_SMS_ReadPDUMsg(uint8_t sim_id, uint8_t index, Helios_SMSRecvMsgInfoStruct *pdu_msg);

/**
 * @brief: get length of PDU message
 * @sideeffect:
 * @param:
 *       \pdu_msg	   - a pointer to the message buffer
 * @return:
 *         the length of PDU msg - successful
 *        -1 - failed
*/
int Helios_SMS_GetPDUMsgLength(void *pdu_msg);

/**
 * @brief: get message numbers
 * @sideeffect:
 * @param:
 *       \sim_id	   - SIM card index, range [0,1]
 * @return:
 *         message numbers - successful
 *        -1 - failed
*/
int Helios_SMS_GetMsgIndex(uint8_t sim_id);


#if defined(PLAT_ASR_1803s) || defined(PLAT_ASR_1803sc) || defined(PLAT_ASR) || defined(PLAT_ASR_1606) || defined(PLAT_ASR_1609) || defined(PLAT_ASR_1602)
int Helios_SMS_GetMsgStatus(uint8_t *smsready);
#endif


/*-----------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif

