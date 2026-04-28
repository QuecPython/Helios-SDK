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
202/07/20  Francis.Qin	    Create.
**************************************************************************/

#ifndef _HELIOS_ALIPAY_H
#define _HELIOS_ALIPAY_H


#ifdef __cplusplus
extern "C" {
#endif

#define HELIOS_ALIPAY_QUEUE_L1_SIZE  (6)  //10
#define HELIOS_ALIPAY_QUEUE_L2_SIZE  (6)  //20  /*FLASH空间大小 (6+6)*4 =48K*/
#define HELIOS_ALIPAY_EVN_VALUE_MAX  (5)

#define MAX_DEMO_TIMER_NO        (20)
#define LOCAL_MSG_SDK_START      (999)
#define LOCAL_MSG_TIMER_EXPIRED  (998)
#define ANT_MSG_ID_IDX_BASE 0
#define HELIOS_SDK_CLOSE_TIMER_ID   (5)
#define HELIOS_SDK_OPEN_TIMER_ID    (9)

#define kNoErr 0
#define kGeneralErr -1
#define TRUE 1
#define FRLSE 0

typedef void (*callback_on_timer)(void *param);
typedef void * Helios_ant_timer;
typedef int Helios_ant_task_t;
typedef void (* Helios_ant_task_function_t)(void *);
typedef unsigned int Helios_ant_u32;
typedef void* Helios_ant_ptr;
typedef int Helios_ant_s32;
typedef char Helios_ant_char;
typedef signed long long    Helios_ant_s64;


typedef enum{
    ALIPAY_IOT_TRANCTION_ERR_UNKNOWN           =-1,//交易结果无法获取
    ALIPAY_IOT_TRANCTION_ERR_NONE              = 0,//交易成功时设置
    ALIPAY_IOT_TRANCTION_ERR_TIMEOUT           = 1,//交易超时
    ALIPAY_IOT_TRANCTION_ERR_TRADE_FAIL        = 2,//交易返回失败
    ALIPAY_IOT_TRANCTION_ERR_PROCESSING        = 3,//支付处理中
    ALIPAY_IOT_TRANCTION_ERR_NETWORK_EXCEPTION = 4,//网络异常
    ALIPAY_IOT_TRANCTION_ERR_UNKNOW_EXCEPTION  = 5,//未知异常
    ALIPAY_IOT_TRANCTION_ERR_NOT_SUPPORT       = 6,//不支持的交易
}HELIOS_ALIPAY_IOT_TRANCTION_ERR_ENUM;


typedef enum {
    ALIPAY_IOT_SIGN_RV_OK = 0,             //操作成功
    ALIPAY_IOT_SIGN_RV_PARAM_ERROR,        //参数错误
    ALIPAY_IOT_SIGN_RV_BUF_NOT_ENOUGHT,    //传入的内存不足
    ALIPAY_IOT_SIGN_RV_IO_ERROR,           //IO错误
    ALIPAY_IOT_SIGN_RV_SEC_INTERNAL_ERROR, //安全库内部错误
    ALIPAY_IOT_SIGN_RV_SIGN_ERROR,         //签名接口调用错误
    ALIPAY_IOT_SIGN_RV_UNKNOWN = 99        //未知错误
}HELIOS_ALIPAY_IOT_SIGN_RET;

typedef enum{
    alipay_iot_biz_result_succ          = 0,/**成功*/
    alipay_iot_biz_result_para_err      = 1,/**参数有误*/
    alipay_iot_biz_result_not_init      = 2,/**还没初始化*/
    alipay_iot_biz_result_buff_err      = 3,/**缓存队列访问错误*/
    alipay_iot_biz_result_mem_err       = 4,/**内存分配失败*/
    alipay_iot_biz_result_busy_err      = 5,/**mdap繁忙*/
    alipay_iot_biz_result_buff_full     = 6,/**缓存队列已满*/
    alipay_iot_biz_result_backup_fail   = 7,/**数据备份失败，但不影响L1缓存中数据的使用*/
} Helios_alipay_iot_biz_result_code_t;

typedef struct
{
    //provided by ant platform, 每个数组需要以数字0结尾
    char item_id[64 + 1];                        //item id provided by ant platform ,蚂蚁集团提供的产品身份识别号
    char module_supplier_no[64 + 1];         //hardware supplier NO. 硬件供应商编号
    char device_supplier_no[32 + 1];  //device supplier NO.  设备供应商编号
    char merchant_user_id[32 + 1];      //device operator ID.  设备运营商编号
    char product_key[64 + 1];                //product key  区分设备名称,蚂蚁集团提供的设备行业和设备形态的精简描述
    int32_t env;                                                  //env PROFILE对应的运行环境，0为正式运行环境
}Helios_alipay_sdk_profile_info_struct;

typedef struct
{
    char account_flow[64+1];       //流量账户信息，默认和传入SIM卡的ICCID保持一致; 第一个字节为数字0表示不传
    char iccid[21+1];              //SIM卡的ICCID; 第一个字节为数字0表示不传
    uint32_t human_verify;         //身份核实方式，值为ALIPAY_IOT_HUMAN_VERIFY的按bit组合; 为0表示不传
}Helios_alipay_iot_production_info_struct;

typedef struct{
    char business_no[64+1];                     //交易成功返回的流水号, 必须以'\0'结尾; 第一个字节为数字0表示不传
    char qr_code[64+1];                         //付款码, 必须以'\0'结尾; 第一个字节为数字0表示不传
    int32_t amount;                             //交易金额,单位为分; 为负数表示不传
    int32_t time_consuming;                     //交易耗时毫秒数; 为负数表示不传
    HELIOS_ALIPAY_IOT_TRANCTION_ERR_ENUM fail_reason;//交易结果
    uint32_t timestamp;                         //UTC时间戳, 仅仅为参考用。以SDK内部时间为准
}Helios_alipay_iot_transaction_data_struct;

typedef struct{
    uint32_t brocast_count;                     //语音播报增量次数
    uint32_t scan_count;                        //扫码次数增量
}Helios_alipay_iot_action_data_struct;

typedef struct
{
    int     							    rsv1;
    Helios_alipay_sdk_profile_info_struct   profile_info_st;
	char 								    terminal_id[64+1]; //SN 设备的序列号sn
}Helios_aliapy_iot_save,*Helios_aliapy_iot_save_ptr;

typedef struct
{
	char					account_iccid[64+1]; //accout info or sim iccid
	char					imei[64+1];          //IMEI
	char					sn[64+1];            //SN
	char					clear_sdk_cache;     //clear cache flag
	int 					running;             //sdk run flag
	int 					state;               //cust app state
	int 					iot_sdk_tid;         //alipay sdk task id record
	int						iot_app_tid;         //ql alipay app task id record
	Helios_aliapy_iot_save	aliapy_iot_save;     //iot ctx need save parms
	int						rsv;                 //reserve
}Helios_aliapy_iot_ctx, *Helios_aliapy_iot_ctx_ptr;

typedef enum {
	HELIOS_ALIPAY_DEVICE_SN = 0,  		//0 设备SN，	device sn是AT 传入的terminal id 
	HELIOS_ALIPAY_DEVICE_MODULE_SN,		//1 module_sn是模块自身的序列号
	HELIOS_ALIPAY_DEVICE_IMEI,			//2 设备的IMEI
	HELIOS_ALIPAY_DEVICE_ICCID,			//3 设备通讯卡的ICCID
	HELIOS_ALIPAY_DEVICE_MAX
} Helios_alipay_device_info_e;

/*****************************************************************
* Function: Helios_alipay_iot_snyc_ctx_info
*
* Description:
*	同步配置context info
* 
* Parameters:
*	Helios_aliapy_iot_ctx_ptr		[in]	机具扫描到的消费者付款码长度=19位的数字字符串）
*
* Return:
*	kNoErr       (0)            设置成功
*	kGeneralErr  (-1)           设置失败
*	
*****************************************************************/

int Helios_alipay_iot_snyc_ctx_info(Helios_aliapy_iot_ctx_ptr iot_ctx);


/*#* 交易加签 *#*/

/*****************************************************************
* Function: alipay_iot_sign_qrcode
*
* Description:
*	反扫（用户支付二维码）支付模式交易加签。
* 
* Parameters:
*	code						[in]	机具扫描到的消费者付款码长度=19位的数字字符串）
*	amount						[in]	金额，单位为元，可以带小数点。不签金额时amount传入NULL
*	result						[out]	创建结果（json字符串）
*	len_result					[out]	创建结果（json字符串）的长度，传入时值应当是result buffer的长度,执行成功或返回RV_BUF_NOT_ENOUGHT后，会被更新为实际产生的签名数据（所需要的）的长度
* Return:
*	HELIOS_ALIPAY_IOT_SIGN_RET 		详见枚举值
*
* Lowlevel: 
*	HELIOS_ALIPAY_IOT_SIGN_RET alipay_iot_sign_qrcode(const char * code, const char * amount, char * result, int * len_result);
*	
*****************************************************************/
HELIOS_ALIPAY_IOT_SIGN_RET Helios_alipay_iot_sign_qrcode(const char * code, const char * amount, char * result, int * len_result);

/*****************************************************************
* Function: alipay_iot_sign_qrcode
*
* Description:
*	主扫（商家收款二维码）支付模式交易加签
* 
* Parameters:
*	tid 						[in]	交易单号，可以是支付宝交易单号，也可以是外部订单号
*	amount						[in]	金额，单位为元，可以带小数点。不签金额时amount传入NULL
*	result						[out]	创建结果（json字符串）
*	len_result					[out]	创建结果（json字符串）的长度，传入时值应当是result buffer的长度
*										执行成功或返回RV_BUF_NOT_ENOUGHT后，会被更新为实际产生的签名数据（所需要的）的长度
* Return:
*	HELIOS_ALIPAY_IOT_SIGN_RET 		详见枚举值
*
* Lowlevel:
*	HELIOS_ALIPAY_IOT_SIGN_RET alipay_iot_sign_recv_qrcode(const char * tid,const char * amount, char * result, int * len_result);
*	
*****************************************************************/
HELIOS_ALIPAY_IOT_SIGN_RET Helios_alipay_iot_sign_recv_qrcode(const char * tid,const char * amount, char * result, int * len_result);


/*****************************************************************
* Function: alipay_iot_sign_face_token
*
* Description:
*	刷脸（用户人脸token）支付模式交易加签
* 
* Parameters:
*	faceToken					[in]	人脸token(长度36的字符串)
*	amount						[in]	金额，单位为元，可以带小数点。不签金额时amount传入NULL
*	result						[out]	创建结果（json字符串）
*	len_result					[out]	创建结果（json字符串）的长度，传入时值应当是result buffer的长度
*										执行成功或返回RV_BUF_NOT_ENOUGHT后，会被更新为实际产生的签名数据（所需要的）的长度
* Return:
*	HELIOS_ALIPAY_IOT_SIGN_RET 		详见枚举值
*
* Lowlevel:
*	HELIOS_ALIPAY_IOT_SIGN_RET alipay_iot_sign_face_token(const char * faceToken, const char * amount, char * result, int * len_result);
*	
*****************************************************************/
HELIOS_ALIPAY_IOT_SIGN_RET Helios_alipay_iot_sign_face_token(const char * faceToken, const char * amount, char * result, int * len_result);


/*****************************************************************
* Function: alipay_iot_sign_delegated
*
* Description:
*	代扣（交易标识）支付模式交易加签
* 
* Parameters:
*	tid 						[in]	代扣协议号
*	amount						[in]	金额，单位为元，可以带小数点。不签金额时amount传入NULL
*	result						[out]	创建结果（json字符串）
*	len_result					[out]	创建结果（json字符串）的长度，传入时值应当是result buffer的长度
*										执行成功或返回RV_BUF_NOT_ENOUGHT后，会被更新为实际产生的签名数据（所需要的）的长度
* Return:
*	HELIOS_ALIPAY_IOT_SIGN_RET 		详见枚举值
*
* Lowlevel:
*	HELIOS_ALIPAY_IOT_SIGN_RET  alipay_iot_sign_delegated(const char * tid, const char * amount, char * result, int * len_result);
*	
*****************************************************************/
HELIOS_ALIPAY_IOT_SIGN_RET Helios_alipay_iot_sign_delegated(const char * tid, const char * amount, char * result, int * len_result);

/*#* 交易上报 *#*/

/**
* send production info data to alipay
* call this api each time the sdk startup. (that means the device power on)
* @param production data
* @return return alipay_iot_result_code_t
* @lowlevel 
*/

/*****************************************************************
* Function: alipay_iot_coll_production_info_send
*
* Description:
*	send production info data to alipay
*	产品信息上报
* Parameters:
*	pd_info 					[in]	production data
*
* Return:
*	alipay_iot_result_code_t		详见枚举值
*
* Lowlevel:
*	Helios_alipay_iot_biz_result_code_t alipay_iot_coll_production_info_send(const alipay_iot_production_info_struct* pd_info);
*	
*****************************************************************/
Helios_alipay_iot_biz_result_code_t Helios_alipay_iot_coll_production_info_send(const Helios_alipay_iot_production_info_struct* pd_info);


/*****************************************************************
* Function: Helios_alipay_iot_coll_transaction_data_send
*
* Description:
*	send transaction data to alipay, the api will send to network immediately
*	call this api each time you got a qrcode or business_no.
*	交易信息上报
* Parameters:
*	transaction 					[in]	transaction data
*
* Return:
*	alipay_iot_result_code_t		详见枚举值
*
* Lowlevel:
*	Helios_alipay_iot_biz_result_code_t alipay_iot_coll_transaction_data_send_rt(const alipay_iot_transaction_data_struct* transaction);
*	
*****************************************************************/

Helios_alipay_iot_biz_result_code_t Helios_alipay_iot_coll_transaction_data_send(const Helios_alipay_iot_transaction_data_struct* transaction);


/*****************************************************************
* Function: alipay_iot_coll_action_data_send
*
* Description:
*	send action data to alipay,call this api each time you scan qrcode or broadcast a voice.
*	行为信息上报:扫码次数、广播次数
* Parameters:
*	action						[in]	action data
*
* Return:
*	alipay_iot_result_code_t		详见枚举值
*
* Lowlevel:
*	Helios_alipay_iot_biz_result_code_t alipay_iot_coll_action_data_send(const alipay_iot_action_data_struct* action);
*	
*****************************************************************/
Helios_alipay_iot_biz_result_code_t Helios_alipay_iot_coll_action_data_send(const Helios_alipay_iot_action_data_struct* action);

int Helios_alipay_iot_set_save(Helios_aliapy_iot_save* aliapy_save);

Helios_aliapy_iot_ctx_ptr Helios_alipay_iot_get_ctx(void);

int Helios_alipay_iot_init(void);

int Helios_alipay_iot_get_version_info(char *version, char* build_time, int size);

int Helios_alipay_iot_get_utc(unsigned int *seconds);

int Helios_alipay_get_biztid(char *biztid_res ,int len);

int Helios_alipay_get_iotdid(char *iotdid_res ,int len);

int Helios_alipay_iot_get_type_info(int type, char *buf, int size);

typedef void (*Helios_alipay_event_callback)(int msgID, int data);

int Helios_alipay_set_callback(Helios_alipay_event_callback cb);

#ifdef __cplusplus
}
#endif


#endif


