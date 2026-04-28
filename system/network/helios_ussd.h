
/*============================================================================
  Copyright (c) 2020 Quectel Wireless Solution, Co., Ltd.  All Rights Reserved.
  Quectel Wireless Solution Proprietary and Confidential.
 =============================================================================*/
/*===========================================================================

                        EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


WHEN        WHO            WHAT, WHERE, WHY
----------  ------------   ----------------------------------------------------

=============================================================================*/

#ifndef USSD_DEMO_H
#define USSD_DEMO_H


#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>
#include <string.h>

/*========================================================================
 *  Marco Definition
 *========================================================================*/
#define QUEC_SS_USSD_STRING_SIZE_MAX 160
#define QUEC_SS_USSD_UCS2_SIZE_MAX   ((2 * QUEC_SS_USSD_STRING_SIZE_MAX) + 2)
/*========================================================================
 *  Enumeration Definition
 *========================================================================*/

typedef enum
{
	HELIOS_USSD_SESSION_INITIATE     = 1,
  HELIOS_USSD_SESSION_CANCEL       = 2,
}Helios_Ussd_option_e;

typedef enum
{
	HELIOS_USSD_RESP_SUCCESS         = 0,
  HELIOS_USSD_CANCEL_SUCCESS       = 1,
  HELIOS_USSD_SAT_SUCCESS          = 2,
  HELIOS_USSD_NO_STR_ERR           = 3,
  HELIOS_USSD_OTHER_ERR            = 4,
}Helios_Ussd_resp_e;

typedef enum
{
  HELIOS_SERVICE_NOT_IMPLEMENTED       = (0xFA << 16)|10,
  HELIOS_INVALID_OPERATION             = (0xFA << 16)|11,
  HELIOS_INVALID_SERVICE_CODE          = (0xFA << 16)|12,
  HELIOS_MEMORY_FAILURE                = (0xFA << 16)|14,
  HELIOS_MM_ESTABLISHMENT              = (0xFA << 16)|20,
  HELIOS_TRANSACTION_TIMEOUT           = (0xFA << 16)|21,
  HELIOS_MM_CONNECTION_RELEASED        = (0xFA << 16)|22,
  HELIOS_UNKNOWN_COMPONENT_RECEIVED    = (0xFA << 16)|23,
  HELIOS_OPERATION_NOT_SUPPORTED       = 4,
  HELIOS_UNKNOWN                       = 50,
}Helios_Ussd_exec_err_e;
/*========================================================================
*  Type Definition
*========================================================================*/
typedef struct
{
  uint8_t                 dcs;
  uint8_t                 *str;
  uint32_t                len;
  Helios_Ussd_resp_e       resp_type;
  Helios_Ussd_exec_err_e         err_code;
}Helios_Ussd_str_s;

typedef struct 
{
  Helios_Ussd_option_e option;
  char str[QUEC_SS_USSD_STRING_SIZE_MAX];                      //USSD code
}Helios_Ussd_send_s;


typedef void (*ussd_cb_t)(uint8_t sim_id, unsigned int ind_type,void *ctx);


typedef struct
{
	ussd_cb_t user_cb;
}Helios_UssdInitStruct;


/*========================================================================
 *	function Definition
 *========================================================================*/

/*****************************************************************
* Function: Helios_Ussd_GetDcs
*
* Description: Get user setting DCS
* 
* Parameters: 
*   nSim                [in]    SIM index,range: 0-1
*   dcs                 [out]   CBS Data Coding Scheme,see 3GPP TS 23.038
*                               The DCS decides in which format we send the USSD code.
* Return:
*   0           success
*   other       error code
* 
*****************************************************************/
int Helios_Ussd_GetDcs(uint8_t sim_id,uint8_t *dcs);



/*****************************************************************
* Function: Helios_Ussd_SetDcs
* 
* Description: Set user DCS
* 
* Parameters: 
*   nSim                [in]    SIM index,range: 0-1
*   dcs                 [in]    CBS Data Coding Scheme,see 3GPP TS 23.038
*                               The DCS decides in which format we send the USSD code.
* 
* Return:
*   0           success
*   other       error code
* 
*****************************************************************/
int Helios_Ussd_SetDcs(uint8_t sim_id,uint8_t dcs);


/*****************************************************************
* Function: Helios_Ussd_getSessionState
*
* Description: Get current USSD session state.
* 
* Parameters: 
*   nSim                [in]    SIM index,range: 0-1
*   state               [out]   The state of USSD session
*                               1:Session is ongoing
*                               0:Session is end
* 
* Return:
*   0           success
*   other       error code
* 
*****************************************************************/
int Helios_Ussd_GetSessionState(uint8_t sim_id,bool *state);


/*****************************************************************
* Function: Helios_Ussd_Send
*
* Description: Initiate ussd session.
* 
* Parameters: 
*   nSim                [in]    SIM index,range: 0-1
*   option              [in]    see Helios_Ussd_Send_s
* 
* Return:
*   0           success
*   other       error code
* 
*****************************************************************/
int Helios_Ussd_Send(uint8_t sim_id,uint8_t option, char *ussd_str);


int Helios_Ussd_Init(uint8_t sim_id, Helios_UssdInitStruct *info);


int Helios_Ussd_Deinit(void);


#ifdef __cplusplus
}/*"C" */
#endif

#endif   /*USBNET_DEMO_H*/