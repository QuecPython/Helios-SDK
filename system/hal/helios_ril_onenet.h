/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of Quectel Co., Ltd. 2020
*
*****************************************************************************/
/*****************************************************************************
 *
 * Filename:
 * ---------
 *   ril_onenet.h 
 *
 * Project:
 * --------
 *   QuecOpen
 *
 * Description:
 * ------------
 *   The file declares some API functions, which are related to onenet
 *
 * Author:
 * -------
 * -------
 *
 *============================================================================
 *             HISTORY
 *----------------------------------------------------------------------------
 * 
 ****************************************************************************/
#ifndef __HELIOS_RIL_OneNet_H__
#define __HELIOS_RIL_OneNet_H__

typedef uint32_t u32;
typedef int s32;
typedef uint8_t u8;

typedef enum
{
    HELIOS_ONENET_BS_MODE_DISABLE = 0,   //Disable boostrap.
    HELIOS_ONENET_BS_MODE_ENABLE         //Enable boostrap.default mode
}Helios_Enum_ONENET_Bs_Mode;

typedef enum
{
    HELIOS_ONENET_CFG_SERVER = 0,   
    HELIOS_ONENET_CFG_RSPTIMEOUT = 2,
    HELIOS_ONENET_CFG_OBAUTOACK,
    HELIOS_ONENET_CFG_SAVE,
}Helios_Enum_ONENET_Conf_Flag;


typedef enum
{
    HELIOS_ONENET_OBJ_FLAG_DISABLE= 0,     //Update without objects list.
    HELIOS_ONENET_OBJ_FLAG_ENABLE          //Update with objects list. 
}Helios_Enum_ONENET_Obj_Flag;


typedef enum
{
	HELIOS_ONENET_OBSERVE_RESULT_1= 1,     //2.05 Content, indicate the correct result.
    HELIOS_ONENET_OBSERVE_RESULT_2,        //2.04 Content, indicate the correct result.
    HELIOS_ONENET_OBSERVE_RESULT_11 = 11,  //4.00 Bad Request. 
    HELIOS_ONENET_OBSERVE_RESULT_12 ,      //4.01 Unauthorized.
    HELIOS_ONENET_OBSERVE_RESULT_13,       //4.04 Not Found.
    HELIOS_ONENET_OBSERVE_RESULT_14,       //4.05 Method Not Allowed.
    HELIOS_ONENET_OBSERVE_RESULT_15        //4.06 Not Acceptable.
}Helios_Enum_ONENET_Observe_Result;


typedef enum
{
    HELIOS_ONENET_VALUE_TYPE_STRING= 1,     
    HELIOS_ONENET_VALUE_TYPE_OPAQUE,        
    HELIOS_ONENET_VALUE_TYPE_INTEGER,      
    HELIOS_ONENET_VALUE_TYPE_FLOAT,       
    HELIOS_ONENET_VALUE_TYPE_BOOLEAN      
}Helios_Enum_ONENET_Value_Type;

typedef enum
{
    HELIOS_RAI_MODE_NOT_IND = 0,     
    HELIOS_RAI_MODE_REL_AFTER_SEND_IND,        
    HELIOS_RAI_MODE_REL_AFTER_RECV_IND      
}Helios_Enum_ONENET_Rai_Mode;

typedef enum
{
    HELIOS_EVENT_BOOTSTRAP_START= 1,     
    HELIOS_EVENT_BOOTSTRAP_SUCCESS,        
    HELIOS_EVENT_BOOTSTRAP_FAILED,      
    HELIOS_EVENT_CONNECT_SUCCESS,       
    HELIOS_EVENT_CONNECT_FAILED,
    HELIOS_EVENT_REG_SUCCESS,  
    HELIOS_EVENT_REG_FAILED,  
    HELIOS_EVENT_REG_TIMEOUT,  
    HELIOS_EVENT_LIFETIME_TIMEOUT,  
    HELIOS_EVENT_STATUS_HALT,  
    HELIOS_EVENT_UPDATE_SUCCESS,  
    HELIOS_EVENT_UPDATE_FAILED,  
    HELIOS_EVENT_UPDATE_TIMEOUT, 
    HELIOS_EVENT_UPDATE_NEED, 
    HELIOS_EVENT_DEREG_DONE,//15
    HELIOS_EVENT_RESPONSE_FAILED = 20,
    HELIOS_EVENT_RESPONSE_SUCCESS,
    HELIOS_EVENT_NOTIFY_FAILED =25, 
    HELIOS_EVENT_NOTIFY_SUCCESS,//26
    HELIOS_EVENT_END 
}Helios_Enum_ONENET_Event_Evtid;


typedef struct{
	u32 ref;		  // Instance ID of OneNET communication suite..
	u32 ins_id;	   // Object identifier. If the object ID is not existed, the module will return error..
	u32 obj_id;		//Instance count.			
	u32 ins_count;   //Length of data sent.
	u8* insbitmap;   //Instance bitmap. A string which should be marked with double quotation marks  For example,
				   //if <insCount>=4, and the <insBitmap>="1101", it means the instance ID 0, 1, 3 will be registered, and the instance ID 2 will not be registered.
	u32 attrcount;   //Attribute count, which indicate the count of readable and/or writeable resources.
	u32 actcount;    //Action count, which indicate the count of executable resources.
}Helios_ONENET_Obj_Param_t;

typedef struct{
u32 ref;    //Instance ID of OneNET communication suite.
u32 msgid;  //The message identifier, which comes from the URC "+ MIPLOBSERVE:".
Helios_Enum_ONENET_Observe_Result  obderve_result;// The result of observe.
u8  raimode;
}Helios_ONENET_Observe_Param_t;


typedef struct{
 Helios_Enum_ONENET_Bs_Mode      onenet_bs_mode;      
 u8* ip;   
 u32 port; 
 u8 ack_timeout;
 bool obs_autoack;
 bool auto_update;
 bool save_state;
}Helios_ONENET_Config_Param_t;


typedef struct{
 u32 ref;		 // Instance ID of OneNET communication suite..
 u32 msgid;      //The message identifier, which comes from the URC "+ MIPLDISCOVER:"
 u32 result;     //The result of discover operate,
 u32 length;     //The length of <valuestring>.
 u8* value_string; //A string which includes the attributes of the object and should be marked with double quotation marks. 
 Helios_Enum_ONENET_Rai_Mode  raimode;
}Helios_ONENET_Discover_Rsp_Param_t;

typedef struct{
 u32 ref;		 // Instance ID of OneNET communication suite..
 u32 msgid;      //The message identifier, which comes from the URC "+MIPLREAD:"
 Helios_Enum_ONENET_Observe_Result  result;// The result of response.
 u32 objid;      //Object identifier.
 u32 insid;      //The instance identifier, which comes from the URC "+MIPLOBSERVE :"
 u32 resid;      //The resource identifier, which comes from the URC "+MIPLOBSERVE :".
 Helios_Enum_ONENET_Value_Type value_type; //The value type.
 u32 len;         //The value length.
 u8* value;
 u32 index;      //The index number of the data.
 u32 flag;       //The message indication. The range is 0-2. 
 Helios_Enum_ONENET_Rai_Mode raimode;     //Integer type. Just for raimode 
}Helios_ONENET_Read_Rsp_Param_t;

typedef struct{
u32 ref;	//Instance ID of OneNET communication suite.
u32 msgid;	//The message identifier, which comes from the URC "+MIPLWRITE:".
Helios_Enum_ONENET_Observe_Result	result;// The result of response.
Helios_Enum_ONENET_Rai_Mode	raimode;
}Helios_ONENET_Write_Rsp_Param_t;


typedef struct{
 u32 ref;		 // Instance ID of OneNET communication suite..
 u32 msgid;      //The message identifier, which comes from the URC "+MIPLDISCOVER:"
 u32 objid;      //Object identifier.
 u32 insid;      //The instance identifier, which comes from the URC "+MIPLOBSERVE :"
 u32 resid;      //The resource identifier, which comes from the URC "+MIPLOBSERVE :".
 Helios_Enum_ONENET_Value_Type value_type; //The value type.
 u32 len;         //The value length.
 u8* value;
 u32 index;      //The index number of the data.
 u32 flag;       //The message indication. The range is 0-2. 
 u32 ackid;      //Integer type, range: 0-65535
 u32 result;     //Integer type. Just for Read Response
 Helios_Enum_ONENET_Rai_Mode raimode;     //Integer type. Just for raimode 
}Helios_ONENET_Notify_Param_t;


typedef struct{
u32 actual_length;
u32 remain_length;
u8* buffer;
u8* prefix;
u8  errno;
}Helios_Onenet_Param;


/******************************************************************************
* Function:     Helios_ONENET_Create
*  
* Description:
*               Create a OneNET Communication Suite Instance
*
* Parameters:    
*               void.
* Return:  
*                RIL_AT_SUCCESS,send AT successfully.
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
******************************************************************************/
s32 Helios_ONENET_Create(void);



/******************************************************************************
* Function:     Helios_ONENET_Addobj
*  
* Description:
*               Delete a OneNET Communication Suite Instance
*
* Parameters:    
*                 onenet_obj_param_t
*                 [in] 
*                  object param,please refer to ST_ONENET_Obj_Param_t.
* Return:  
*                RIL_AT_SUCCESS,send AT successfully.
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
******************************************************************************/
s32 Helios_ONENET_Addobj(Helios_ONENET_Obj_Param_t *onenet_obj_param_t);



/******************************************************************************
* Function:     Helios_ONENET_Delobj
*  
* Description:
*                   Delete a LWM2M Object
*
* Parameters: 
*                ref:
*                  [in]
*                  Instance ID of OneNET communication suite.
*               obj_id:
*                   [in] 
*                   Object identifier. If the object ID is not existed, the module will return error.
* Return:  
*                RIL_AT_SUCCESS,send AT successfully.
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
******************************************************************************/
s32 Helios_ONENET_Delobj(u32 ref,u32 obj_id);



/******************************************************************************
* Function:     Helios_ONENET_Open
*  
* Description:
*                  Send Register Request
*
* Parameters: 
*                ref:
*                  [in]
*                  Instance ID of OneNET communication suite.
*               lifetime:
*                   [in] 
*                   Lifetime, unit is second. Range is 0 or 15~268435455; "0" means that lifetime is 3600 seconds.
* Return:  
*                RIL_AT_SUCCESS,send AT successfully.
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
******************************************************************************/
s32 Helios_ONENET_Open(u32 ref, u32 lifetime, void (*callback_onenet_req)(u8* buffer,u32 length) );


/******************************************************************************
* Function:     Helios_ONENET_Observer_Rsp
*  
* Description:
*                   Respond the Discover Request
*
* Parameters:    
*                onenet_observe_param_t:
*                  [in]
*                lwm2m send param,please refer to ST_ONENET_Observe_Param_t.
*
*                RIL_AT_SUCCESS,send AT successfully. 
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
******************************************************************************/
s32 Helios_ONENET_Observer_Rsp(Helios_ONENET_Observe_Param_t* onenet_observe_param_t);




/******************************************************************************
* Function:     Helios_ONENET_Config
*  
* Description:
*               Configure Optional Parameters
*
* Parameters:    
*                 onenet_config_param_t
*                 [in] 
*                 config param,please refer to ST_ONENET_Config_Param_t.
*
*                 server_config_flag
*                 [in] 
*                 TRUE:  the user need to config ip and port 
*                 FALSE: ignore ip and port
*
* Return:  
*                RIL_AT_SUCCESS,send AT successfully. 
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
******************************************************************************/
s32 Helios_ONENET_Config(Helios_ONENET_Config_Param_t* onenet_config_param_t,Helios_Enum_ONENET_Conf_Flag config_flag);



/******************************************************************************
* Function:     Helios_ONENET_Discover_Rsp
*  
* Description:
*                   Respond the Discover Request
*
* Parameters:    
*                   onenet_discover_rsp_param_t:
*                   [in] 
*                   lwm2m send param,please refer to ST_Socket_Param_t.
*
*                RIL_AT_SUCCESS,send AT successfully.
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
******************************************************************************/
s32 Helios_ONENET_Discover_Rsp(Helios_ONENET_Discover_Rsp_Param_t *onenet_discover_rsp_param_t);


/******************************************************************************
* Function:     Helios_ONENET_Write_Rsp
*  
* Description:
*                   Respond the Write Request
*
* Parameters:    
*                  onenet_write_rsp_param_t:
*                  [in]
*                lwm2m write request param,please refer to ST_ONENET_Write_Rsp_Param_t.
*
*
*                RIL_AT_SUCCESS,send AT successfully. 
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
******************************************************************************/
s32 Helios_ONENET_Write_Rsp(Helios_ONENET_Write_Rsp_Param_t* onenet_write_rsp_param_t);


/******************************************************************************
* Function:     Helios_ONENET_Read_Rsp
*  
* Description:
*                   Respond the Read Request
*
* Parameters:    
*                  onenet_read_param_t:
*                  [in]
*                lwm2m read request param,please refer to ST_ONENET_Notify_Param_t.
*
*                RIL_AT_SUCCESS,send AT successfully.
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
******************************************************************************/
s32 Helios_ONENET_Read_Rsp(Helios_ONENET_Read_Rsp_Param_t* onenet_read_param_t);


/******************************************************************************
* Function:     Helios_ONENET_Execute_Rsp
*  
* Description:
*                   Respond the execute Request
*
* Parameters:    
*                ref:
*                  [in]
*                  Instance ID of OneNET communication suite.
*               msgid:
*                   [in] 
*                  The message identifier, which comes from the URC ?бу+MIPLEXECUTE:.
*               result:
*                    [in]            
*                 The results of execute operation and the result codes are as follows:
*                 Result code CoAP response code Description
*                 2 2.04 Changed, indicates the correct result.
*                 11 4.00 Bad Request
*                 12 4.01 Unauthorized
*                 13 4.04 Not Found
*                 14 4.05 Method Not Allowed
*
*                RIL_AT_SUCCESS,send AT successfully.
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
******************************************************************************/
s32 Helios_ONENET_Execute_Rsp(Helios_ONENET_Write_Rsp_Param_t* onenet_write_rsp_param_t);


/******************************************************************************
* Function:     Helios_ONENET_Notify
*  
* Description:
*                   Notify the Data to OneNET platform or Application Server
*
* Parameters:    
*                  ST_ONENET_Notify_Param_t:
*                   [in] 
*                   onenet notify param,please refer to ST_ONENET_Notify_Param_t.
**                 ack_flag:
*                   [in] 
*                   FALSE     disable ack id .
*                   TRUE      enalbe ack id .
*                 .
*                RIL_AT_SUCCESS,send AT successfully. 
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
******************************************************************************/
s32 Helios_ONENET_Notify(Helios_ONENET_Notify_Param_t* onenet_notify_param_t,bool ack_flag);



/******************************************************************************
* Function:     Helios_ONENET_Update
*  
* Description:
*                  Send Update Request
*
*                ref:
*                  [in]
*                  Instance ID of OneNET communication suite.
*               lifetime:
*                   [in] 
*                  Updated lifetime value. The range is 0 or 15-268435455 Unit: second. "0" means that lifetime is 3600 seconds.
*               onenet_obj_flag:
*                    [in]            
*                  Whether to update with objects list.
* Return:  
*                RIL_AT_SUCCESS,send AT successfully.
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
******************************************************************************/
s32 Helios_ONENET_Update(u32 ref,u32 lifetime,Helios_Enum_ONENET_Obj_Flag obj_flag,Helios_Enum_ONENET_Rai_Mode raimode);

/******************************************************************************
* Function:     Helios_ONENET_CLOSE
*  
* Description:
*               Send Deregister Request 
*
*                ref:
*                  [in]
*                  Instance ID of OneNET communication suite.
*
* Return:  
*                RIL_AT_SUCCESS,send AT successfully.
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
******************************************************************************/
s32 Helios_ONENET_CLOSE(u32 ref);


/******************************************************************************
* Function:     Helios_ONENET_DELETE
*  
* Description:
*               Delete a OneNET Communication Suite Instance
*
*                ref:
*                  [in]
*                  Instance ID of OneNET communication suite.
*
* Return:  
*                RIL_AT_SUCCESS,send AT successfully.
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
******************************************************************************/
s32 Helios_ONENET_DELETE(u32 ref);
#endif // __RIL_NETWORK_H__
