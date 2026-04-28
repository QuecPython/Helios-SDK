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
2022/12/16  Francis.Qin	    Create.
**************************************************************************/

#ifndef _HELIOS_ALIIOT_H
#define _HELIOS_ALIIOT_H

#if MICROPY_QPY_MODULE_ALIPAY

#define uint8_t unsigned char
#define int32_t long

typedef enum {
	HELIOS_PAY_LL_VERBOSE = 0,
	HELIOS_PAY_LL_DEBUG,
	HELIOS_PAY_LL_INFO,
	HELIOS_PAY_LL_WARN,
	HELIOS_PAY_LL_ERROR,
	HELIOS_PAY_LL_FATAL,
} helios_pay_log_level_t;

#define HELIOS_AOS_IMEI_LEN                 17U            /*IMEI 串号长度*/
#define HELIOS_AOS_ICCID_LEN                20U            /*SIM 卡卡号长度*/
#define HELIOS_AOS_IMSI_LEN                 15U            /*IMSI 号长度*/
#define HELIOS_VENDOR_NAME_LEN              20U
#define HELIOS_PRODUCT_NAME_LEN             20U
#define HELIOS_PRODUCT_MODEL_LEN            20U
#define HELIOS_ALIPAY_PK_LEN                20U
#define HELIOS_ALIYUN_PK_LEN                20U
#define HELIOS_ALIYUN_PS_LEN                64U
#define HELIOS_PRODUCT_SN_LEN               48U
#define HELIOS_PRODUCT_MAC_LEN              6U


typedef struct {
    char imei[HELIOS_AOS_IMEI_LEN + 1];            		/*国际移动识别码 IMEI号*/
    char iccid[HELIOS_AOS_ICCID_LEN + 1];          		/*集成电路卡识别码即SIM卡卡号*/
    char imsi[HELIOS_AOS_IMSI_LEN + 1];            		/*国际移动用户识别码 IMSI号*/
    char mac[HELIOS_PRODUCT_MAC_LEN + 1];            		/*国际移动用户识别码 IMSI号*/
    char sn[HELIOS_PRODUCT_SN_LEN + 1];            		/*国际移动用户识别码 IMSI号*/
    char vendor[HELIOS_VENDOR_NAME_LEN + 1]; 				/*厂家名称 */
    char product_name[HELIOS_PRODUCT_NAME_LEN + 1];	/*厂家产品型号 */
    char product_model[HELIOS_PRODUCT_MODEL_LEN + 1];	/*厂家产品型号 */
#if 1
    char pk_alipay[HELIOS_ALIPAY_PK_LEN + 1];	/*支付宝厂家产品型号 支付宝绑定使用*/
    char pk_aliyun[HELIOS_ALIYUN_PK_LEN + 1];	/*阿里云厂家产品型号 支付宝空发ID2等使用*/
    char ps_aliyun[HELIOS_ALIYUN_PS_LEN + 1];	/*阿里云厂家产品秘钥 支付宝空发ID2等使用*/
    int32_t prd_type;                   /*支付宝产品类型 详见prd_type_e*/
#else
    char pk[HELIOS_ALIPAY_PK_LEN + 1];
#endif    
}helios_aos_identify_info_t;


typedef enum {
	HELIOS_PAY_RC_OK = 0,
	HELIOS_PAY_RC_ERROR,
	HELIOS_PAY_RC_UNKNOWN,
	HELIOS_PAY_RC_NOT_INIT,
	HELIOS_PAY_RC_TRUE,
	HELIOS_PAY_RC_FALSE, //5
	HELIOS_PAY_RC_PROCESSING,
	HELIOS_PAY_RC_NOT_INPROCESSING,
	HELIOS_PAY_RC_WRONG_PARAM,
	HELIOS_PAY_RC_WRONG_TIMESTAMP,
	HELIOS_PAY_RC_MEM_ERROR, //10
	HELIOS_PAY_RC_IO_ERROR,
	HELIOS_PAY_RC_JS_ERROR,
	HELIOS_PAY_RC_READ_ERROR,
	HELIOS_PAY_RC_WRITE_ERROR,
	HELIOS_PAY_RC_DEL_ERROR, //15
	HELIOS_PAY_RC_SEMAPHORE_CREATE_ERROR,
	HELIOS_PAY_RC_SE_SAVE_ERROR,
	HELIOS_PAY_RC_SE_INFO_ERROR,
	HELIOS_PAY_RC_SE_RESET_ERROR,
	HELIOS_PAY_RC_SE_GET_STATUS_ERROR, //20
	HELIOS_PAY_RC_SE_GENCODE_ERROR,
	HELIOS_PAY_RC_ENCRYPT_ERROR,
	HELIOS_PAY_RC_DECRYPT_ERROR,
	HELIOS_PAY_RC_NO_USERDATA,
	HELIOS_PAY_RC_BUF_TOO_SHORT, //25
	HELIOS_PAY_RC_NETWORK_ERROR,
	HELIOS_PAY_RC_SERVER_ERROR,
	HELIOS_PAY_RC_SERVER_TIMEOUT,
	HELIOS_PAY_RC_PB_PACK_ERROR,
	HELIOS_PAY_RC_ECC_GENERATE_ERROR, //30
	HELIOS_PAY_RC_ECC_SHARE_ERROR,
	HELIOS_PAY_RC_PRODUCT_MODEL_ERROR,
	HELIOS_PAY_RC_BINDING_DATA_FORMAT_ERROR,
	HELIOS_PAY_RC_TIMESTAMP_ERROR,
	HELIOS_PAY_RC_FUNC_CLOSED,//35
	HELIOS_PAY_RC_NOT_SUPPORT,
} helios_pay_rc_t;

typedef enum
{
    HELIOS_IDENTIFY_SUCCESS = 0U,
    HELIOS_IDENTIFY_INV_PARAM,
    HELIOS_IDENTIFY_NULL_PTR,
    HELIOS_IDENTIFY_SAVE_PARAM_FAIL,
    HELIOS_IDENTIFY_INVALID_IMEI,
    HELIOS_IDENTIFY_IMEI_CHECKFAIL,
    HELIOS_IDENTIFY_INVALID_ALIPAY_PK,
    HELIOS_IDENTIFY_ALIPAY_PK_CHECKFAIL,    
    HELIOS_IDENTIFY_TASK_CREAT_FAIL,
    HELIOS_IDENTIFY_PROCESS_IS_RUNNING,
    HELIOS_IDENTIFY_MEMORY_LEAK,
    HELIOS_IDENTIFY_REPORT_TO_CLOUD_FAIL,
}helios_identify_state;

typedef enum{
    prd_type_watch=0, //成人手表
    prd_type_b6t,    //成人手环
    prd_type_card,   //成人卡片
    prd_type_qzwt,   //儿童手表
    prd_type_qzb6t,  //儿童手环
    prd_type_qzcrd,  //儿童卡片
    prd_type_general, //其他类型，比如功能机
    prd_type_invalid
}prd_type_e;


typedef enum {
    HELIOS_PAYMENT_STATUS_SUCCESS          = 0,
	HELIOS_PAYMENT_STATUS_FAIL             = 1,
	HELIOS_PAYMENT_STATUS_NOTHING          = 2,
	HELIOS_PAYMENT_STATUS_UNBIND_BY_USER   = 3,
	HELIOS_PAYMENT_STATUS_DISABLED_BY_USER = 4,
    HELIOS_PAYMENT_STATUS_UNKNOWN          = 5
} helios_payment_status_t;

typedef enum {
	HELIOS_PAY_FAIL_RES_AMOUNT_LIMIT       = 0,  //超出设置的支付额度
	HELIOS_PAY_FAIL_RES_BALANCE_NOT_ENOUGH = 1,  //零花钱不足，请存入
	HELIOS_PAY_FAIL_RES_COMMON_FAIL        = 2,  //支付失败
} helios_scan_payment_fail_res_t;

/*
 * 消息定义
 */
typedef enum {
	/* 功能:
	 *   获取绑定码，可通过该绑定码完成设备绑定，处理结果通过notifier_cb返回。
	 *
	 * 实现：
	 *   收到此消息，消息处理任务开始向服务端获取绑定码
	 *
	 * 响应：
	 *   HELIOS_PAY_RSP_BIND_CODE       - 获取成功，并通过result传递绑定码字符串
	 *   HELIOS_PAY_RSP_NETWORK_ERROR   - 网络错误，可以重试
	 *   HELIOS_PAY_RSP_SERVER_ERROR    - 服务端错误，可以重试
	 *   HELIOS_PAY_RSP_SE_INFO_ERROR   - 内部错误
	 *   HELIOS_PAY_RSP_JS_ERROR        - JSON操作错误
	 *   HELIOS_PAY_RSP_BUFF_TOO_SHORT  - 内部Buffer空间不足
	 *   HELIOS_PAY_RSP_UNKNOWN         - 未知错误
	 *   HELIOS_PAY_RSP_ERROR           - 其它错误
	 */
	HELIOS_PAY_MSG_GET_BIND_CODE = 1,

	/* 功能：
	 *   获取绑定结果。
	 *
	 * 实现：
	 *   收到此消息，消息处理任务开始向服务端查询绑定结果，处理结果通过notifier_cb返回。
	 *   当查询到绑定正在进行时会继续以轮询方式获取，轮询间隔可通过get_bindcode_interval配置，默认2秒。
	 *   轮询超时可通过query_bind_result_timeout指定，默认120秒
	 *   备足：在轮询过程中，如果发送了新的msg，则停止轮询
	 *
	 * 响应：
	 *   HELIOS_PAY_RSP_BIND_COMPLETE    - 绑定成功
	 *   HELIOS_PAY_RSP_PROCESSING       - 绑定正在进行，等待轮询间隔后，自动继续查询
	 *   HELIOS_PAY_RSP_BIND_PROGRESS    - 绑定进度，进度值保存在result中，进度值的百分比，暂时只有70一个进度便。收到该响应说明可以关闭绑定码展示，开始显示绑定进度
	 *   HELIOS_PAY_RSP_NETWORK_ERROR    - 网络错误，可以重试
	 *   HELIOS_PAY_RSP_SERVER_ERROR     - 服务端错误，可以重试
	 *   HELIOS_PAY_RSP_NOT_INPROCESSING - 未在绑定流程中(可能没有获取过绑定码)
	 *   HELIOS_PAY_RSP_TIMEOUT          - 查询超时，绑定失败
	 *   HELIOS_PAY_RSP_SE_SAVE_ERROR    - 内部错误
	 *   HELIOS_PAY_RSP_ERROR            - 其它错误
	 */
	HELIOS_PAY_MSG_GET_BINDING_RESULT,

	/* 功能：
	 *   获取付款码
	 *
	 * 实现：
	 *   收到此消息，消息处理任务开始从服务端获取付款码，处理结果通过notifier_cb返回
	 *
	 * 响应：
	 *   HELIOS_PAY_RSP_PAY_CODE           - 获取成功，付款码字符串保存在result中
	 *   HELIOS_PAY_RSP_WRONG_PARAM        - 内部参数不合法
	 *   HELIOS_PAY_RSP_NO_USERDATA        - 找不到用户数据，可能为数据损坏或尚未绑定
	 *   HELIOS_PAY_RSP_READ_ERROR         - 本地数据读取失败，可能是数据损坏或已解绑
	 *   HELIOS_PAY_RSP_SE_GENCODE_ERROR   - 内部错误
	 *   HELIOS_PAY_RSP_ERROR              - 其它错误
	 */
	HELIOS_PAY_MSG_GET_PAY_CODE,

	/* 功能:
	 *   获取支付结果
	 *
	 * 实现:
	 *   收到此消息，消息处理任务开始向服务端查询绑定结果，处理结果通过notifier_cb返回
	 *   在没有错误返回并且未查询到支付结果时会继续以轮询方式获取，轮询间隔可通过query_payment_result_interval配置，默认2秒。
	 *   轮询超时可通过query_payment_result_timeout指定，默认120秒
	 *   备足：在轮询过程中，如果发送了新的msg，则停止轮询
	 *
	 * 响应：
	 *   HELIOS_PAY_RSP_ORDER_RESULT        - 付款成功，付款金额信息（bitmap）保存在result中
	 *   HELIOS_PAY_RSP_PROCESSING          - 未查询到支付结果，可能付款还没完成，等待轮询间隔后，自动继续轮询
	 *   HELIOS_PAY_RSP_TIMEOUT             - 查询超时，未查询到支付结果
	 *   HELIOS_PAY_RSP_NETWORK_ERROR       - 网络错误，可以重试
	 *   HELIOS_PAY_RSP_WRONG_PARAM         - 内部参数不合法
	 *   HELIOS_PAY_RSP_IO_ERROR            - 获取设备本地信息失败
	 *   HELIOS_PAY_RSP_READ_ERROR          - 本地数据读取失败，可能是数据损坏或已解绑
	 *   HELIOS_PAY_RSP_NOT_INPROCESSING    - 当前没有获取支付码，无法查询支付结果
	 *   HELIOS_PAY_RSP_JS_ERROR            - JSON操作错误，可以重试
	 *   HELIOS_PAY_RSP_UNKNOWN             - 未知错误，可以重试
	 *   HELIOS_PAY_RSP_FUNCTION_OFF        - 付款码支付功能已经被用户关闭
	 *   HELIOS_PAY_RSP_UNBIND              - 用户已在手机端解绑本设备，无法付款
	 *   HELIOS_PAY_RSP_PAYMENT_FAIL        - 付款失败
	 *   HELIOS_PAY_RSP_ERROR               - 其它错误
	 */
	HELIOS_PAY_MSG_GET_PAYMENT_RESULT,

	/* 功能：
	 *   获取收款码
	 *
	 * 实现：
	 *   收到此消息，消息处理任务获取收款码，处理结果通过notifier_cb返回
	 *
	 * 响应：
	 *   HELIOS_PAY_RSP_PAY_CODE           - 获取成功，收款码字符串保存在result中
	 *   HELIOS_PAY_RSP_FUNCTION_OFF       - 收款功能未开启
	 *   HELIOS_PAY_RSP_WRONG_PARAM        - 内部参数不合法
	 *   HELIOS_PAY_RSP_NO_USERDATA        - 找不到用户数据，可能为数据损坏或尚未绑定
	 *   HELIOS_PAY_RSP_READ_ERROR         - 本地数据读取失败，可能是数据损坏或已解绑
	 *   HELIOS_PAY_RSP_SE_GENCODE_ERROR   - 内部错误
	 *   HELIOS_PAY_RSP_ERROR              - 其它错误
	 */
	HELIOS_PAY_MSG_GET_COLLECTION_CODE,

	/* 功能:
	 *   解析扫码，付款码字符串通过消息参数传入
	 *
	 * 实现：
	 *   收到此消息，消息处理任务解析扫码字串，处理结果通过notifier_cb返回
	 *
	 * 响应：
	 *   HELIOS_PAY_RSP_SCANCODE_INFO     - 解析扫码，解析结果（upay_scancode_info_t类型指针）保存在result中，解析结果包含收款方名称、金额（如果收钱码是预设有交易金额）
	 *   HELIOS_PAY_RSP_NETWORK_ERROR     - 网络异常 -->提示：网络异常，请重试
	 *   HELIOS_PAY_RSP_SERVER_ERROR      - 码值无法解析，停止解析 -->提示：二维码无法识别
	 *   HELIOS_PAY_RSP_WRONG_PARAM       - 内部参数不合法
	 *   HELIOS_PAY_RSP_IO_ERROR          - 获取设备本地信息失败
	 *   HELIOS_PAY_RSP_JS_ERROR          - JSON操作错误
	 *   HELIOS_PAY_RSP_UNKNOWN           - 未知错误
	 *   HELIOS_PAY_RSP_ERROR             - 其它错误
	 */
	HELIOS_PAY_MSG_PARSE_SCAN_CODE,

	/* 功能：
	 *   发起主扫支付
	 *
	 * 实现：
	 *   收到此消息，消息处理任务发起主扫码支付，处理结果通过notifier_cb返回
	 *
	 * 响应：
	 *   HELIOS_PAY_RSP_POST_SCAN_PAYMENT_COMPLETE   - 发起主扫支付成功
	 *   HELIOS_PAY_RSP_BALANCE_NOT_ENOUGH           - 余额不足 - 报错文案：零花钱不足，请存入
	 *   HELIOS_PAY_RSP_AMOUNT_OVER_LIMIT            - 超出设置的支付额度 - 报错文案：超出设置的支付额度
	 *   HELIOS_PAY_RSP_PAYMENT_UNKNOWN              - 支付结果未知，请用户与商家确认结果
	 *   HELIOS_PAY_RSP_NETWORK_ERROR                - 网络异常 -->提示：网络异常，请向商家确认交易结果
	 *   HELIOS_PAY_RSP_PAYMENT_FAIL                 - 通用的支付失败case - 报错文案：支付失败
	 *   HELIOS_PAY_RSP_IO_ERROR                     - 获取设备本地信息失败
	 *   HELIOS_PAY_RSP_WRONG_PARAM                  - 内部参数不合法
	 *   HELIOS_PAY_RSP_NO_USERDATA                  - 未发现绑定数据，设备还没有绑定，停止发起支付
	 *   HELIOS_PAY_RSP_SE_GENCODE_ERROR             - 内部错误
	 *   HELIOS_PAY_RSP_JS_ERROR                     - JSON操作错误
	 *   HELIOS_PAY_RSP_UNKNOWN                      - 未知错误
	 *   HELIOS_PAY_RSP_ERROR                        - 其它错误
	 */
	HELIOS_PAY_MSG_POST_SCAN_PAYMENT,


	/* 功能：
	 *   获取家长控制码
	 *
	 * 实现：
	 *   收到此消息，消息处理任务获取家长控制码，处理结果通过notifier_cb返回
	 *
	 * 响应：
	 *   HELIOS_PAY_RSP_PAY_CODE           - 获取成功，家长控制码字符串保存在result中
	 *   HELIOS_PAY_RSP_FUNCTION_OFF       - 家长控制功能未开启
	 *   HELIOS_PAY_RSP_WRONG_PARAM        - 内部参数不合法
	 *   HELIOS_PAY_RSP_NO_USERDATA        - 找不到用户数据，可能为数据损坏或尚未绑定
	 *   HELIOS_PAY_RSP_READ_ERROR         - 本地数据读取失败，可能是数据损坏或已解绑
	 *   HELIOS_PAY_RSP_SE_GENCODE_ERROR   - 内部错误
	 *   HELIOS_PAY_RSP_ERROR              - 其它错误
	 */
	HELIOS_PAY_MSG_GET_PARENTCTRL_CODE,

	/* 功能：
	 *   解除绑定，清空本地数据
	 * 实现：
	 *   收到此消息，消息处理任务执行解绑操作，处理结果通过notifier_cb返回
	 *
	 * 响应：
	 *   HELIOS_PAY_RSP_UNBIND_COMPLETE     - 解绑成功
	 *   HELIOS_PAY_RSP_ERROR               - 解绑失败
	 */
	HELIOS_PAY_MSG_UNBIND,

	/* 功能：
	 *   与服务端同步时间(同步结果可能因为网络原因失败，不需要处理)(可以不用或空闲时调用)
	 *
	 * 实现：
	 *   收到此消息，消息处理任务与服务端同步时间(，处理结果通过notifier_cb返回
	 *
	 * 响应：
	 *   HELIOS_PAY_RSP_NO_ERRORE           - 与服务端同步时间成功
	 *   HELIOS_PAY_RSP_ERROR               - 与服务端同步时间失败
	 */
	HELIOS_PAY_MSG_SYNC_NETWORK_TIME,

	/* 功能：应用界面切换，退出当前界面
	 * 实现：收到此消息，消息处理任务中停止正在进行的轮询操作
	 * 响应：无
	 */
	HELIOS_PAY_MSG_NOTIFY_APP_BACK,

	/* 功能：应用退出
	 * 实现：收到此消息，sdk停止正在进行的轮询操作,并删除所有未处理的msg
	 * 响应：无
	 */
	HELIOS_PAY_MSG_NOTIFY_APP_EXIT,
} helios_pay_msg_cmd_t;

/*
 * 消息处理结果
 */
typedef enum {
	HELIOS_PAY_RSP_PROCESSING = 1,
	HELIOS_PAY_RSP_BIND_PROGRESS, /* 当用户扫码后，ALIPAY SDK收到服务端下发的绑定进度后主动推送UPAY_RSP_BIND_PROGRESS，此时可以关闭绑定码显示，开始显示绑定进度 */
	HELIOS_PAY_RSP_BIND_COMPLETE,
	HELIOS_PAY_RSP_BIND_CODE,
	HELIOS_PAY_RSP_PAY_CODE, //5
	HELIOS_PAY_RSP_COLLECTION_CODE,
	HELIOS_PAY_RSP_PARENTCTRL_CODE,
	HELIOS_PAY_RSP_ORDER_RESULT,
	HELIOS_PAY_RSP_SCANCODE_INFO,
	HELIOS_PAY_RSP_POST_SCAN_PAYMENT_COMPLETE,
	HELIOS_PAY_RSP_UNBIND_COMPLETE, //11
	HELIOS_PAY_RSP_NO_ERROR,
	HELIOS_PAY_RSP_NOT_INPROCESSING,
	HELIOS_PAY_RSP_NOT_INIT,
	HELIOS_PAY_RSP_NOT_FOUND,
	HELIOS_PAY_RSP_NO_USERDATA, //16
	HELIOS_PAY_RSP_BUFF_TOO_SHORT,
	HELIOS_PAY_RSP_AMOUNT_OVER_LIMIT,
	HELIOS_PAY_RSP_BALANCE_NOT_ENOUGH,
	HELIOS_PAY_RSP_NETWORK_ERROR,
	HELIOS_PAY_RSP_SERVER_ERROR, //21
	HELIOS_PAY_RSP_SERVER_TIMEOUT,
	HELIOS_PAY_RSP_PB_PACK_ERROR,
	HELIOS_PAY_RSP_ECC_GENERATE_ERROR,
	HELIOS_PAY_RSP_ECC_SHARE_ERROR,
	HELIOS_PAYY_RSP_DEL_ERROR, //26
	HELIOS_PAY_RSP_READ_ERROR,
	HELIOS_PAY_RSP_WRITE_ERROR,
	HELIOS_PAY_RSP_SEMAPHORE_CREATE_ERROR,
	HELIOS_PAY_RSP_SE_SAVE_ERROR,
	HELIOS_PAY_RSP_SE_INFO_ERROR, //31
	HELIOS_PAY_RSP_SE_RESET_ERROR,
	HELIOS_PAY_RSP_SE_GET_STATUS_ERROR,
	HELIOS_PAY_RSP_SE_GENCODE_ERROR,
	HELIOS_PAY_RSP_ENCRYPT_ERROR,
	HELIOS_PAY_RSP_DECRYPT_ERROR, //36
	HELIOS_PAY_RSP_JS_ERROR,
	HELIOS_PAY_RSP_MEM_ERROR,
	HELIOS_PAY_RSP_PRODUCT_MODEL_ERROR,
	HELIOS_PAY_RSP_BINDING_DATA_FORMAT_ERROR,
	HELIOS_PAY_RSP_TIMEOUT, //41
	HELIOS_PAY_RSP_PAYMENT_FAIL,
	HELIOS_PAY_RSP_PAYMENT_UNKNOWN,
	HELIOS_PAY_RSP_UNBIND_BY_USER,
	HELIOS_PAY_RSP_FUNCTION_OFF,
	HELIOS_PAY_RSP_WRONG_PARAM, //46
	HELIOS_PAY_RSP_WRONG_TIMESTAMP,
	HELIOS_PAY_RSP_IO_ERROR,
	HELIOS_PAY_RSP_UNKNOWN,
	HELIOS_PAY_RSP_ERROR,
	HELIOS_PAY_RSP_TRANSIT_LIST,
	HELIOS_PAY_RSP_TRANSIT_CODE,
	HELIOS_PAY_RSP_TRANSIT_CARD_DATA_LIMITED,
	HELIOS_PAY_RSP_TRANSIT_COMMON_ERROR,
	HELIOS_PAY_RSP_TRANSIT_NOT_SUPPORT,
} helios_pay_rsp_code_t;




typedef void (*upay_notify_t)(helios_pay_msg_cmd_t cmd, helios_pay_rsp_code_t rsp_code, char *result, int result_len, void *userdata);


/*
 * 异步接口使用的消息结构
 */
typedef struct {
	/* 调用方传入的消息类型 */
	helios_pay_msg_cmd_t cmd;

	/* 如果需要传入参数，通过args指定；不需要传入参数设置NULL */
	char *args;

	/* 用户数据，通过notifier回传给用户，不需要传递用户数据设置NULL */
	void *userdata;
} helios_pay_msg_t;

/*
 * 返回给用户的扫码解析结果
 */
typedef struct {
	char seller_name[120];
	char amount[20];
} helios_pay_scancode_info_t;

typedef struct {
	/* 查询绑定结果超时（非必填），取值范围：(0,600000]，默认：120000，单位：毫秒 */
	long long query_bind_result_timeout;

	/* 查询支付结果超时（非必填），蓝牙版本此值无效，取值范围：(0,160000]，默认：120000，单位：毫秒 */
	long long query_payment_result_timeout;

	/* 绑定结果轮询间隔（非必填），取值范围：(0,5000]，默认：网络支付宝2000，蓝牙支付默认100，单位：毫秒 */
	unsigned int query_bind_result_interval;

	/* 支付结果轮询间隔（非必填），蓝牙版本此值无效 取值范围：(0,5000]，默认：2000，单位：毫秒 */
	unsigned int query_payment_result_interval;

	/* 异步消息处理任务的优先级（非必填），默认：200 */
	int msg_task_priority;

	/* 异步消息处理任务的站大小（非必填），默认：网络手表40KB；蓝牙手表8K，单位：byte */
	int msg_task_stacksize;

	/* 消息回调函数（必填），upay通过该回调函数返回消息处理结果、绑定进度等信息。*/
	upay_notify_t notifier_cb;

	/* upay接口模式选择（必填），1: 不会初始化异步接口，0：初始化异步接口 */
	int sync_mode;
} helios_pay_config_t;

typedef struct {
	unsigned char mac_addr[6]; /* 设备mac地址（必填）， 数组类型；要求唯一不变性 */
	const char *imei; /* 网络支付宝设备imei必填，蓝牙支付宝传NULL，字符串类型，需以'\0'结束；要求唯一不变性 */
	const char *sn; /* 设备SN(厂商印刷在设备上的设备序列号)（必填），字符串类型，需以'\0'结束；长度不超过49个字符，只能包含大小写字母、数字、下划线；要求唯一不变性 */
	const char *vendor_name; /* 厂商名称（必填），字符串类型，需以'\0'结束，要求不变性 */
	const char *device_name; /* 产品名称（必填），字符串类型，需以'\0'结束，要求不变性 */
	const char *device_model; /* 产品型号（必填），字符串类型，需以'\0'结束；长度会影响绑定码的长度，建议不超过20个字符;要求不变性 */
	const char *product_key; /* 产品秘钥（必填），字符串类型，需以'\0'结束；长度会影响绑定码的长度，网络手表建议不超过20个字符要求不变性 ，蓝牙支付宝此值传NULL*/
} helios_pay_devinfo_t;

typedef struct helios_pay_transit_Card
{
    char  cardNo[40];               //卡号
    char  cardType[40];             //卡类型
    char  title[40];                //卡标题
}helios_pay_transit_Card_t;



/*
 * @brief: 下发机卡管理IMEI,ICCID,IMSI信息到机卡管理服务
 * @param: pstidentify  包含IMEI,ICCID,IMSI信息的结构体指针，该部分内存由调用者负责释放
 * @return: HELIOS_IDENTIFY_NULL_PTR   非法输入， pstidentify 为空指针
            HELIOS_IDENTIFY_INV_PARAM  非法输入， IMEI,ICCID,IMSI 超长或者溢出
            HELIOS_IDENTIFY_SUCCESS    下发成功
*/
int32_t Helios_aos_set_identify_info(helios_aos_identify_info_t *pstidentify);


/*
 * @brief: 启动机卡管理认证，要求开机启动触发一次，每12小时触发一次。
           本接口为异步接口，本接口在被调用后会创建一个任务将相关机卡信息上报到云端。
           上报成功后，任务会自动推出。否则会每隔5S尝试一次
           本接口调用前最好保证网络已经连接成功。
 * @param: 无
 * @return: HELIOS_IDENTIFY_IMEI_CHECKFAIL    IMEI号校验失败
            HELIOS_IDENTIFY_TASK_CREAT_FAIL   机卡管理认证任务启动失败
            HELIOS_IDENTIFY_SUCCESS           机卡管理任务启动成功
 */
int32_t Helios_aos_start_simcard_identify(void);


/*
 * 获取本地保存的绑定状态，即判断当前设备是否已经有用户的绑定数据（无论服务端是否已解绑）
 * 类型：NONBLOCK
 * @return  HELIOS_PAY_RC_TRUE   - 已绑定
 *          HELIOS_PAY_RC_FALSE  - 未绑定
 *          HELIOS_PAY_RC_ERROR  - 获取绑定状态失败
 */
helios_pay_rc_t Helios_upay_check_bind_status(void);


/*
 * 获取服务端的绑定状态，即判断当前设备是否已经有用户的绑定数据
 * 类型：NONBLOCK
 * @return  HELIOS_PAY_RC_TRUE   - 已绑定
 *          HELIOS_PAY_RC_FALSE  - 未绑定
 *          HELIOS_PAY_RC_ERROR  - 获取绑定状态失败
 */
helios_pay_rc_t Helios_upay_check_bind_status_online(void);


/*
 * 获取绑定码
 * 类型：BLOCK
 * @param [out]bindcode       绑定码字符串
 * @param [out]bindcode_len   绑定码字符串的长度，传入值应当是bindcode buffer的长度
 * @return  HELIOS_PAY_RC_OK             - 获取绑定码成功，可以使用bindcode输出的绑定码进行绑定
 *          若返回值为其他，则说明绑定码获取失败，需要重新获取。可能的失败原因如下：
 *          ----------------------------------------------------------------------
 *          HELIOS_PAY_RC_SE_INFO_ERROR  - 内部错误
 *          HELIOS_PAY_RC_JS_ERROR       - JSON操作错误
 *          HELIOS_PAY_RC_WRONG_PARAM    - 输入参数不合法
 *          HELIOS_PAY_RC_SERVER_ERROR   - 服务端返回错误
 *          HELIOS_PAY_RC_NETWORK_ERROR  - 网络错误，建议重试
 *          HELIOS_PAY_RC_BUF_TOO_SHORT  - bindcode buffer长度不足
 *          HELIOS_PAY_RC_UNKNOWN        - 未知错误
 */
helios_pay_rc_t Helios_upay_get_bindcode(char *bindcode, int *bindcode_len);


/*
 * 查绑定结果
 * 类型：BLOCK
 * @return  HELIOS_PAY_RC_OK             - 绑定成功，数据已保存
 *          HELIOS_PAY_RC_PROCESSING     - 绑定过程进行中，请继续轮询绑定结果；建议的轮询间隔为2s，超时时间建议为60s；超时后仍然返回processing，即可认为绑定失败
 *          HELIOS_PAY_RC_NETWORK_ERROR  - 网络错误。建议重新查询
 *          若返回值为其他，则说明绑定失败，需要重新获取绑定码绑定。可能的失败原因如下：
 *          --------------------------------------------------------------------------
 *          HELIOS_PAY_RC_NOT_INPROCESSING          - 未在绑定流程中（还没有调用upay_get_bindcode获取绑定码）
 *			HELIOS_PAY_RC_SE_SAVE_ERROR             - 内部错误
 *          HELIOS_PAY_RC_JS_ERROR                  - JSON操作错误
 *          HELIOS_PAY_RC_BINDING_DATA_FORMAT_ERROR - 绑定数据格式错误
 *          HELIOS_PAY_RC_WRITE_ERROR               - 数据保存失败
 *          HELIOS_PAY_RC_SERVER_ERROR              - 服务端返回错误
 *          HELIOS_PAY_RC_UNKNOWN                   - 未知错误
 *          HELIOS_PAY_RC_ERROR                     - 其它错误
 */
helios_pay_rc_t Helios_upay_query_bind_result(void);


/*
 * 获取付款码
 * 类型：BLOCK
 * @param [out]paycode      付款码字符串(付款码为长度18或19的数字字符串，条形码编码和显示时应注意做好不同长度的兼容)
 * @param [out]paycode_len  付款码字符串的长度，传入值应当是paycode buffer的长度
 * @return  UPAY_RC_OK                - 获取支付码成功，可以使用paycode输出的付款码进行支付
 *          若返回值为其他，则说明付款码获取失败，需要重新获取。可能的失败原因如下：
 *          ----------------------------------------------------------------------
 *          HELIOS_PAY_RC_WRONG_PARAM       - 输入参数不合法
 *          HELIOS_PAY_RC_NO_USERDATA       - 找不到用户数据，可能为数据损坏或尚未绑定
 *          HELIOS_PAY_RC_READ_ERROR        - 数据读取失败
 *          HELIOS_PAY_RC_SE_GENCODE_ERROR  - 内部错误
 *          HELIOS_PAY_RC_BUF_TOO_SHORT     - paycode buffer长度不足
 */
helios_pay_rc_t Helios_upay_get_paycode(uint8_t *paycode, int *paycode_len);


/*
 * 获取支付码支付结果；蓝牙支付宝此接口不需要调用
 * 类型：BLOCK
 * @param [out]status         支付码支付结果，定义见upay_payment_status_t，可能的结果：
                              HELIOS_PAYMENT_STATUS_SUCCESS  支付成功，此时amount_bitmap有金额输出
                              HELIOS_PAYMENT_STATUS_NOTHING  没有查到交易，请继续使用本接口查询
                              --------------------------其它输出均表示支付已经失败---------------------------
                              HELIOS_PAYMENT_STATUS_DISABLED_BY_USER  付款码支付功能已经被用户关闭
                              HELIOS_PAYMENT_STATUS_UNBIND_BY_USER  用户已在手机端解绑本设备
 * @param [out]amount_bitmap  支付金额的bitmap，二维数组，直接从左至右逐bit点阵输出即可（黑色bit为1，白色为0）
 * @return  UPAY_RC_OK               - 查询接口调用成功，此时会输出status和amount_bitmap
 *          若返回值为其他，则说明查询接口调用失败。可能的失败原因如下：
 *          ---------------------------------------------------------------
 *          HELIOS_PAY_RC_IO_ERROR         - 获取设备本地信息失败
 *          HELIOS_PAY_RC_WRONG_PARAM      - 输入参数不合法
 *          HELIOS_PAY_RC_NOT_INPROCESSING - 当前没有获取支付码，无法查询支付结果
 *          HELIOS_PAY_RC_READ_ERROR       - 本地数据读取失败，可能是数据损坏或已解绑
 *          ----------- 以下错误建议重试 ------------
 *          HELIOS_PAY_RC_UNKNOWN          - 未知错误
 *          HELIOS_PAYRC_JS_ERROR         - JSON操作异常（可能是内存不足）
 *          HELIOS_PAY_RC_NETWORK_ERROR    - 网络异常
 */
helios_pay_rc_t Helios_upay_query_order_result(helios_payment_status_t *status, char amount_bitmap[32][14]);


/*
 * 获取收款码
 * 类型：BLOCK
 * @param [out]collectioncode      收款码字符串(收钱码为长度40或41的字符串，含有字母和数字)
 * @param [out]collectioncode_len  收款码字符串的长度，传入值应当是paycode buffer的长度
 * @return  HELIOS_PAY_RC_OK                - 获取收款码成功，可以使用paycode输出的收款码进行收钱
 *          HELIOS_PAY_RC_FUNC_CLOSED       - 收款功能未开启
 *          若返回值为其他，则说明收款码获取失败，需要重新获取。可能的失败原因如下：
 *          -------------------------------------------------------------------
 *          HELIOS_PAY_RC_WRONG_PARAM       - 输入参数不合法
 *          HELIOS_PAY_RC_NO_USERDATA       - 找不到用户数据，可能为数据损坏或尚未绑定
 *          HELIOS_PAY_RC_READ_ERROR        - 数据读取失败
 *          HELIOS_PAY_RC_SE_GENCODE_ERROR  - 内部错误
 *          HELIOS_PAY_RC_BUF_TOO_SHORT     - paycode buffer长度不足
 */
helios_pay_rc_t Helios_upay_get_collectioncode(uint8_t *collectioncode, int *collectioncode_len);


/*
 * 主扫时解析扫到的收钱码
 * 类型：BLOCK
 * @param [in]code             摄像头扫描到的商家收钱码
 * @param [out]seller_name     商家名字
 * @param [in]seller_name_len  seller_name buffer的长度，建议>=100字节
 * @param [out]amount          如果收钱码是预设有交易金额的，将会在此字段输出，后续直接展示本金额，无需用户输入。禁止改动本金额
 * @param [in]amount_len       amount buffer的长度，建议>=10字节
 * @return  HELIOS_PAY_RC_OK            - 解析接口调用成功，此时会输出seller_name和amount
 *          若返回值为其他，则说明接口调用失败。可能的失败原因如下：
 *          -----------------------------------------------------------------
 *          HELIOS_PAY_RC_IO_ERROR      - 获取设备本地信息失败
 *          HELIOS_PAY_RC_WRONG_PARAM   - 参数不合法
 *          HELIOS_PAY_RC_NETWORK_ERROR - 网络异常 -->提示：网络异常，请重试
 *          HELIOS_PAY_RC_SERVER_ERROR  - 码值无法解析 -->提示：二维码无法识别
 *          HELIOS_PAY_RC_JS_ERROR      - JSON操作异常-可能是内存不足
 *          HELIOS_PAY_RC_READ_ERROR    - 本地数据读取失败，可能是数据损坏或已解绑
 *          HELIOS_PAY_RC_UNKNOWN       - 未知错误
 */
helios_pay_rc_t Helios_upay_parse_scan_code(char *code, char *seller_name, int seller_name_len, char *amount, int amount_len);


/*
 * 发起主扫支付。注意：执行upay_parse_scan_code成功之后才可以调用
 * 类型：BLOCK
 * @param [in]amount           支付金额。字符串格式，从范围0.01-1000元，小数点后最多保留2位小数
 * @param [out]status          主扫支付结果，定义见upay_payment_status_t，可能的结果：
                               HELIOS_PAYMENT_STATUS_SUCCESS  支付成功
                               HELIOS_PAYMENT_STATUS_FAIL     支付失败，此时fail_res有失败原因输出，根据输出进行报错
                               HELIOS_PAYMENT_STATUS_UNKNOWN  结果未知，请用户与商家确认结果
 * @param [out]res_fail        主扫支付失败原因，定义见upay_scan_payment_fail_res_t，可能的结果：
                               HELIOS_FAIL_RES_AMOUNT_LIMIT       超出设置的支付额度 - 报错文案：超出设置的支付额度
                               HELIOS_FAIL_RES_BALANCE_NOT_ENOUGH 余额不足           - 报错文案：零花钱不足，请存入
                               HELIOS_FAIL_RES_COMMON_FAIL        其它通用的失败case - 报错文案：支付失败
 * @return  HELIOS_PAY_RC_OK               - 支付接口调用成功，此时会输出status和fail_res
 *          若返回值为其他，则说明接口调用失败。可能的失败原因如下：
 *          --------------------------------------------------------------------
 *          HELIOS_PAY_RC_IO_ERROR         - 获取设备本地信息失败
 *          HELIOS_PAY_RC_WRONG_PARAM      - 输入参数不合法
 *          HELIOS_PAY_RC_NO_USERDATA      - 未发现绑定数据，设备还没有绑定
 *          HELIOS_PAY_RC_SE_GENCODE_ERROR - 内部错误
 *          HELIOS_PAY_RC_NETWORK_ERROR    - 网络异常 -->提示：网络异常，请向商家确认交易结果
 *          HELIOS_PAY_RC_JS_ERROR         - JSON操作错误
 *          HELIOS_PAY_RC_UNKNOWN          - 未知错误
 */
helios_pay_rc_t Helios_upay_post_scan_payment(const char *amount, helios_payment_status_t *status, helios_scan_payment_fail_res_t *fail_res);


/*
 * 获取家长设置码
 * 类型：BLOCK
 * @param [out]ctrlcode       家长设置定码字符串
 * @param [out]ctrlcode_len   家长设置码字符串的长度，传入值应当是ctrlcode buffer的长度
 * @return  HELIOS_PAY_RC_OK             - 获取家长设置定码成功，可以使用bindcode输出的绑定码进行绑定
 *          若返回值为其他，则说明绑定码获取失败，需要重新获取。可能的失败原因如下：
 *          ----------------------------------------------------------------------
 *          HELIOS_PAY_RC_SE_INFO_ERROR  - 内部错误
 *          HELIOS_PAY_RC_JS_ERROR       - JSON操作错误
 *          HELIOS_PAY_RC_WRONG_PARAM    - 输入参数不合法
 *          HELIOS_PAY_RC_SERVER_ERROR   - 服务端返回错误
 *          HELIOS_PAY_RC_NETWORK_ERROR  - 网络错误，建议重试
 *          HELIOS_PAY_RC_BUF_TOO_SHORT  - bindcode buffer长度不足
 *          HELIOS_PAY_RC_UNKNOWN        - 未知错误
 */
helios_pay_rc_t Helios_upay_get_parentctrlcode(char *ctrlcode, int *ctrlcode_len);


/*
 * 获取本地保存的logon id，参数id为调用方分配的buffer地址，*id_len表示buffer长度(长度建议100bytes)
 * 类型：NONBLOCK
 * @return  HELIOS_PAY_RC_OK          - 获取成功
 *          HELIOS_PAY_RC_NOT_EXIST   - logon id不存在
 *          HELIOS_PAY_RC_ERROR       - 获取失败
 */
helios_pay_rc_t Helios_upay_get_logon_id(char *id, int *id_len);


/*
 * 获取本地保存的昵称，参数name为调用方分配的buffer地址，*name_len表示buffer长度(buffer长度建议100bytes)
 * 类型：NONBLOCK
 * @return  HELIOS_PAY_RC_OK          - 获取成功
 *          HELIOS_PAY_RC_NOT_EXIST   - 昵称不存在
 *          HELIOS_PAY_RC_ERROR       - 获取失败
 */
helios_pay_rc_t Helios_upay_get_nick_name(char *name, int *name_len);


/*
 * 获取当前正在处理的消息，并保存到参数msg指向的变量中；如果当前没有正在处理的消息，不处理。
 * 类型：NONBLOCK
 * @return  HELIOS_PAY_RC_OK       - 获取成功
 *          HELIOS_PAY_RC_ERROR    - 获取失败
 */
helios_pay_rc_t Helios_upay_get_curr_msg(helios_pay_msg_cmd_t *msg);


/*
 * 与服务端同步时间(同步结果可能因为网络原因失败，不需要处理)(可以不用或空闲时调用)
 * 类型：BLOCK
 * @return  HELIOS_PAY_RC_OK      - 同步时间完成
 *          HELIOS_PAY_RC_ERROR   - 同步时间失败
 */
helios_pay_rc_t Helios_upay_sync_network_time(void);


/*
 * 消息发送
 * 类型：NONBLOCK
 * 对BLOCK类型接口的异步实现
 * 通过消息机制实现，调用方在初始化阶段通过upay_register_notifier()注册消息回调函数，然后通过Helios_upay_msg_send发送msg到消息队列中。
 * upay内部任务从消息队列取出msg，进行相应处理后通过通过回调函数返回处理结果。
 * Helios_upay_msg_send为非阻塞接口，消息队列已满的情况下，返回HELIOS_PAY_RC_ERROR
 * @return  HELIOS_PAY_RC_OK     - 消息发送成功
 *          HELIOS_PAY_RC_ERROR  - 消息发送失败
 */
helios_pay_rc_t Helios_upay_msg_send(helios_pay_msg_t *msg);


/*
 * 解除绑定
 * 类型：NONBLOCK
 * @return HELIOS_PAY_RC_OK              - 解绑成功，同时清空本地数据、关闭收款功能
 *         HELIOS_PAY_RC_DEL_ERROR       - 删除失败。建议重试3次，如果还是失败，可能是存储器故障
 *         HELIOS_PAY_RC_SE_RESET_ERROR  - 内部错误。建议重试3次，如果还是失败，可能是存储器故障
 *         HELIOS_PAY_RC_ERROR           - 其它错误
 */
helios_pay_rc_t Helios_upay_unbind(void);


/*
 * 检查收款功能是否打开
 * 类型：NONBLOCK
 * @return  HELIOS_PAY_RC_TRUE      - 收款功能开启
 *          HELIOS_PAY_RC_FALSE     - 收款功能关闭
 *          HELIOS_PAY_RC_ERROR     - 内部错误
 */
helios_pay_rc_t Helios_upay_check_collection_status(void);


/*
 * 打开/关闭收款功能
 * 类型：NONBLOCK
 * @argment 1 打开收款功能，0 关闭收款功能
 * @return HELIOS_PAY_RC_OK        - 设置成功
 *         HELIOS_PAY_RC_ERROR     - 设置失败
 */
helios_pay_rc_t Helios_upay_enable_collectioncode(int enable);


/*
 * 设置sdk所需的产品相关信息，包括厂商名称、产品名称、产品型号、mac地址、IMEI、SN编号
 * 类型：NONBLOCK
 * @return HELIOS_PAY_RC_OK        - 设置成功
 *         HELIOS_PAY_RC_ERROR     - 设置失败
 */
helios_pay_rc_t Helios_upay_set_devinfo(helios_pay_devinfo_t *info);


/*
 * 注册日志打印函数（针对定制打印函数的情况），需要在调用Helios_upay其他接口之前注册。
 * 没有注册打印函数，则使用Helios_upay默认的打印函数。
 * 类型：NONBLOCK
 * @return HELIOS_PAY_RC_OK        - 注册成功
 *         HELIOS_PAY_RC_ERROR     - 注册失败
 */
helios_pay_rc_t Helios_upay_register_print(void (*print_func)(const char *fmt, ...));


/*
 * 注册任务创建函数（针对需要使用外部任务创建函数的情况），需要在Helios_upay_init之前注册。
 * 没有该函数，则使用Helios_upay默认的任务创建函数。
 * 类型：NONBLOCK
 * @return HELIOS_PAY_RC_OK        - 注册成功
 *         HELIOS_PAY_RC_ERROR     - 注册失败
 */
helios_pay_rc_t Helios_upay_register_task_create(void *(*task_create_func)(void (*entry)(void *arg),const char *taskname, int stacksize, int priority, void *arg));


/*
 * 设置SDK内部最低的日志打印等级。对于调试版本，建议level等于HELIOS_UPA_LL_DEBUG；正式版本上level设置HELIOS_PAY_LL_INFO
 * 类型：NONBLOCK
 * @return HELIOS_PAY_RC_OK        - 设置成功
 *         HELIOS_PAY_RC_ERROR     - 设置失败
 */
helios_pay_rc_t Helios_upay_set_log_limit(helios_pay_log_level_t level);


/*
 * SDK初始化，设备启动后只需要调用一次，需要确认初始化成功，初始化失败时Helios_upay接口均不可用。注意在调用该接口需要满足：
 *    1. 如果是未绑定状态，需要保证网络连通（建议查询到网络状态以后再进行初始化）
 *    2. imei、sn、device name、device model、vendor name设置完成
 * 类型：BLOCK
 * @args    config必填
 * @return  HELIOS_PAY_RC_OK             - 初始化成功
 *          HELIOS_PAY_RC_NETWORK_ERROR  - 网络错误，可能需要重试
 *          HELIOS_PAY_RC_UNKNOWN        - 未知错误
 *          HELIOS_PAY_RC_ERROR          - 其它错误
 */
helios_pay_rc_t Helios_upay_init(helios_pay_config_t *config);


/*
 * SDK释放，设备关机时调用
 * 类型：NONBLOCK
 * @return  HELIOS_PAY_RC_OK     - 成功
 *          HELIOS_PAY_RC_ERROR  - 失败
 */
helios_pay_rc_t Helios_upay_free(void);


/*
* 产线烧录安全数据时使用,获取是否已经烧录
* 类型 BLOCK
* @return HELIOS_PAY_RC_OK    -未被烧录
*		  HELIOS_PAY_RC_ERROR -已经烧录
*/
helios_pay_rc_t Helios_upay_production_line_get_sercurte(void);


/*
* 产线烧录安全数据时使用,写入安全数据
* 类型 BLOCK
* @args input_buff 写入安全数据内容
*		input_len  写入安全数据长度
* @return HELIOS_PAY_RC_OK    -写入成功
*		  HELIOS_PAY_RC_ERROR -写入失败
*/
helios_pay_rc_t Helios_upay_production_line_write_securte(unsigned char* input_buff, unsigned char input_len);


/*
* 产线烧录安全数据时使用,校验写入结果
* 类型 BLOCK
*
* @return HELIOS_PAY_RC_OK    -校验成功
*		  HELIOS_PAY_RC_ERROR -校验失败
*/
helios_pay_rc_t Helios_upay_production_line_check_write_securte(void);


/*
* 产线读取安全数据ID时使用
* 类型 NONBLOCK
* @args id_buff 读取ID内容
*		input_len  读取ID
* @return HELIOS_PAY_RC_OK    -读取成功
*		  HELIOS_PAY_RC_ERROR -读取失败
*/
helios_pay_rc_t Helios_upay_production_line_get_secure_id(unsigned char* id_buff, uint32_t *input_len);


/*
* 恢复出厂设置时试用，清除本地存入的支付宝使用相关数据
* 如果已绑定且有网，会从服务端解绑
* 类型 NONBLOCK
* 
* @return HELIOS_PAY_RC_OK    -设置成功
*		  HELIOS_PAY_RC_ERROR -设置失败
*/
helios_pay_rc_t Helios_upay_factory_reset(void);


/*
* 恢复出厂设置时试用，直接清除本地存入的支付宝使用相关数据
* 类型 BLOCK
*
* @return HELIOS_PAY_RC_OK    -设置成功
*		  HELIOS_PAY_RC_ERROR -设置失败
*/
helios_pay_rc_t Helios_upay_hw_factory_reset(void);


/*
* 空发ID2方案时使用，初始化ID2
* 类型 BLOCK
*
* @return HELIOS_PAY_RC_OK    -初始化成功
*		  HELIOS_PAY_RC_ERROR -初始化失败
*/
helios_pay_rc_t Helios_upay_id2_init(void);


/*
* 空发ID2方案时使用，检查本地id2状态
* 类型 BLOCK
* @args [output]id2_st  id2 状态 1 - 已存在
*					   		     0 - 不存在
* @return HELIOS_PAY_RC_OK    -检查成功
*		  HELIOS_PAY_RC_ERROR -检查失败
*/
helios_pay_rc_t Helios_upay_id2_check_status(uint8_t* id2_st);


/*
* 空发ID2方案时使用，生成空发认证码
* 类型 BLOCK
* @args [input]token  从服务端获取的token
* @args [input]token_len  从服务端获取的token长度
* @args [output]auth_code  生成的认证码
* @args [output]len  生成认证码长度
* @return HELIOS_PAY_RC_OK    -获取成功
*		  HELIOS_PAY_RC_ERROR -获取失败
*/
helios_pay_rc_t Helios_upay_id2_get_opt_auth_code(const uint8_t * token, uint32_t token_len, uint8_t * auth_code, uint32_t * len);


/*
* 空发ID2方案时使用，保存空发数据
* 类型 BLOCK
* @args [input]otp_data  从服务端获取的空发数据、服务端下发的烧录数据需要做base64解码
* @args [input]len       base64解码后的长度
* @return HELIOS_PAY_RC_OK    -写入成功
*		  HELIOS_PAY_RC_ERROR -写入失败
*/
helios_pay_rc_t Helios_upay_id2_load_opt_data(const uint8_t * otp_data, uint32_t len);

#ifdef BOARD_EG810MCN_GA_ALIPAY
int Helios_upay_id2_write_rsvd_part(int fd, uint32_t offset, void *data, uint32_t data_len);

int Helios_upay_factory_partition_write(int fd, uint32_t offset, void *buffer, uint32_t write_len);
#endif

/*
*以下八个接口库中暂无
*/
#if 0
char* Helios_aos_idetnfiy_version_get(void);


/*
* 乘车码使用，检查乘车码是否可用
* 类型 BLOCK
* @args 
* @return HELIOS_PAY_RC_OK    -可使用
*		  HELIOS_PAY_RC_ERROR -不可使用
*/
helios_pay_rc_t Helios_upay_transit_pre_check(void);


/*
* 乘车码使用，更新开通状态(成人设备默认开通，无需关心该接口)
* 类型 BLOCK
* @args 
* @return HELIOS_PAY_RC_OK    -可用
*		  HELIOS_PAY_RC_ERROR -不可使用
*/
helios_pay_rc_t Helios_upay_transit_update_activity_status(void);


/*
 * 获取卡列表
 * @param   [out]card_list          存放获取的卡列表
 *          [inout]len_card_list    输入时为允许获取的最大长度，输出时为实际获取的长度
 *          [out]card_num           获取的卡片数量
 * @return  RV_OK 更新成功
 *          RV_JS_ERROR             CJSON库或接口错误
 *          RV_NETWORK_ERROR        网络错误
 *          RV_UNKNOWN              未知错误
 *          RV_SERVER_FAIL_ERROR    服务端返回错误
 *          RV_WRITE_ERROR          KV写错误，检查KV写接口的实现
 *          RV_BUF_TOO_SHORT        允许的最大长度小于实际获取的长度
 */
helios_pay_rc_t Helios_upay_transit_get_card_list(helios_pay_transit_Card_t* card_list, uint32_t* len_card_list, uint32_t* card_num);


/*
 * 获取指定卡的乘车码码值
 * @param   [in]cardNo              卡序号
 *          [in]cardType            卡类型
 *          [out]transitcode        储存码值的缓存
 *          [inout]len_transitcode  输入时为允许获取的最大长度，输出时为实际获取的长度
 * @return  RV_OK 更新成功
 *          RV_CARD_DATA_LIMITED    由于风控原因生码受限
 *          RV_UNKNOWN              未知错误
 *          RV_BUF_TOO_SHORT        允许的最大长度小于实际获取的长度
 *          RV_CODE_GEN_ERROR       生码异常
 *          RV_NETWORK_ERROR        网络错误
 */
helios_pay_rc_t Helios_upay_transit_get_code(char* cardNo, char* cardType, char* transitcode, uint32_t* len_transitcode);


/*
 * 检查本地是否存在安全证书
 * @param  
 * @return  HELIOS_PAY_RC_TRUE 	 已经存在证书
 *          HELIOS_PAY_RC_FALSE    不存在证书
 */
helios_pay_rc_t Helios_upay_cert_check_status(void);


/*
 * 获取认证数据
 * @param   [inout]auth_data              认证数据
 *          [inout]len_auth_data          认证数据长度
 * @return  HELIOS_PAY_RC_OK 					  成功
 *          HELIOS_PAY_RC_WRONG_PARAM           参数错误
 *          HELIOS_PAY_RC_BUF_TOO_SHORT         允许的最大长度小于实际获取的长度
 */
helios_pay_rc_t Helios_upay_cert_auth_data_get(uint8_t *auth_data, uint32_t* len_auth_data);


/*
 * 导入证书数据到设备
 * @param   [in]auth_data             证书数据
 * @return  RV_OK 					  更新成功
 */
helios_pay_rc_t Helios_upay_cert_load(uint8_t *auth_data);
#endif
#endif
#endif

