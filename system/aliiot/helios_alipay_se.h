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

#ifndef _HELIOS_ALIPAY_SE_H
#define _HELIOS_ALIPAY_SE_H



/**
 * 绑定状态相关
 */
typedef int binding_status_e;
#define ALIPAY_STATUS_BINDING_FAIL  0    // 绑定失败
#define ALIPAY_STATUS_UNBINDED      1    // 解绑
#define ALIPAY_STATUS_START_BINDING 2    // 开始绑定
#define ALIPAY_STATUS_BINDING_OK    0xa5 // 绑定成功(已绑定)
#define ALIPAY_STATUS_UNKNOWN       0xff // 未知状态

typedef enum {
    ALIPAY_PAYMENT_STATUS_SUCCESS          = 0,
	ALIPAY_PAYMENT_STATUS_FAIL             = 1,
	ALIPAY_PAYMENT_STATUS_NOTHING          = 2,
	ALIPAY_PAYMENT_STATUS_UNBIND_BY_USER   = 3,
	ALIPAY_PAYMENT_STATUS_DISABLED_BY_USER = 4,
    ALIPAY_PAYMENT_STATUS_UNKNOWN          = 5,
    ALIPAY_PAYMENT_STATUS_PROCESSING       = 6,
} alipay_payment_status_e;

typedef enum {
    PRODUCT_TYPE_ADULT_WATCH          =  0,		//成人手表
    PRODUCT_TYPE_ADULT_BRACELET       =  1,		//成人手环
    PRODUCT_TYPE_ADULT_CARD        	  =  2,		//成人卡片
    PRODUCT_TYPE_CHILD_WATCH     	  =  3,		//儿童手表
    PRODUCT_TYPE_CHILD_BRACELET		  =  4,		//儿童手环
    PRODUCT_TYPE_STUDENT_CARD		  =  5		//学生卡
} alipay_product_type;

typedef struct {
    bool is_success;              //是否成功收款(readonly)
    // char amount[32];           //收款金额(readonly)
    char bitmap_amount[32][14];   //收款金额(readonly)
    char message[256];            //收款说明(readonly)
} alipay_income_detail_info_t;


/**
 * 获取帮助码
 * @param [out] aid_code 存放数据的指针，建议buffer大小为256
 * @param [inout] len_aid_code 帮助码大小，输入时为最大允许读取长度，输出时为实际长度
 * @return  RV_OK：获取成功
 *          RV_WRONG_PARAM：参数错误
 *          RV_UNKNOWN：不应该出现
 *          RV_JS_ERROR：不应该出现
 *          RV_BUF_TOO_SHORT：缓存太小
 */
int Helios_alipay_get_aid_code(char aid_code[256], uint32_t* len_aid_code);

/**
 * 初始化该功能，启动设备或者进入支付宝前调用一次即可，若失败则表示功能不可用，不允许打开支付宝
 * @return  0：    初始化成功
 *          其他value：失败
 */
int Helios_alipay_pre_init(void);

/**
 * 获取绑定码
 * @param [out] result     存放绑定码的指针,建议buffer大小为256
 * @param [inout] len_result 绑定码数据大小，传入时为允许的最大长度，传出时为实际的长度
 * @return  RV_OK：    获取成功
 *          RV_WRONG_PARAM：入惨错误，result为空，或者*len_result为0
 *          RV_BUF_TOO_SHORT：缓存太小
 *          RV_NETWORK_ERROR：网络错误，可尝试重新调用此接口
 *          其他错误：不应该出现
 */
int Helios_alipay_get_binding_code(char* result, int *len_result);

/***
 * 轮询绑定结果
 * @param [out] status     当前的绑定状态
 * @return  RV_OK  绑定成功，数据已保存
 *          RV_PROCESSING  绑定过程进行中，请继续轮询绑定结果;
 *                         建议的轮询间隔为2s，超时时间建议为60s;超时后仍然返回processing，即可认为绑定失败
 *          RV_UNKNOWN   绑定失败，需要重新获取绑定码绑定。
 */
int Helios_alipay_query_binding_result(binding_status_e* status);

/**
 * 获取支付码，支付码为18或19位纯数字字符串，条形码编码和显示时应注意
 * @param [out] paycode     存放支付码的指针，建议缓存大小为20
 * @param [inout] len_paycode 支付码数据大小，传入时为paycode buff大小，传出时为实际获取的大小
 * @return  RV_OK：    获取成功
 *          其他value：获取失败
 */
int Helios_alipay_get_paycode(uint8_t *paycode, uint32_t *len_paycode);

/***
 * 获取收钱码，仅儿童设备可用，用法及返回值状态同alipay_get_paycode()
 * 收钱码为长度40或41的字符串，含有字母和数字
 * @param [out] paycode     存放支付码的指针，建议缓存大小为64
 * @param [inout] len_paycode 支付码数据大小，传入时为允许的最大大小，传出时为实际获取的大小
 * @return  RV_OK：    获取成功
 *          其他value：获取失败
 */
int Helios_alipay_get_collectioncode(uint8_t *code, uint32_t *len_code);

/***
 * 获取支付码支付结果
 * @param   [in]pay_code    用于查询的付款码码串，来自「alipay_get_paycode」接口
 *          [out]status      支付码支付结果，定义见alipay_payment_status_e，可能的结果：
                           ALIPAY_PAYMENT_STATUS_SUCCESS  支付成功，此时bitmap_amount有金额输出
                           ALIPAY_PAYMENT_STATUS_NOTHING  没有查到交易，请继续使用本接口查询
                           --------------------------其它输出均表示支付已经失败---------------------------
                           ALIPAY_PAYMENT_STATUS_DISABLED_BY_USER  付款码支付功能已经被用户关闭
                           ALIPAY_PAYMENT_STATUS_UNBIND_BY_USER  用户已在手机端解绑本设备
 * @param [out]bitmap_amount  支付金额的bitmap，二维数组，直接从左至右逐bit点阵输出即可（黑色bit为1，白色为0）
 * @return  RV_OK  查询接口调用成功，此时会输出status和bitmap_amount
 *          若返回值为其他，则说明查询接口调用失败。可能的失败原因如下：
 * -------------------------------------------------------------------
 *          RV_IO_ERROR 获取设备本地信息失败
 *          RV_WRONG_PARAM  输入参数不合法
 *          RV_NOT_INPROCESSING 当前没有获取支付码，无法查询支付结果
 *          RV_READ_ERROR  本地数据读取失败，可能是数据损坏或已解绑
            -----------以下错误建议重试------------
 *          RV_UNKNOWN  未知错误
 *          RV_JS_ERROR  json操作异常-可能是内存不足
 *          RV_NETWORK_ERROR  网络异常
 */
int Helios_alipay_query_order_result(char* pay_code, alipay_payment_status_e *status, char bitmap_amount[32][14]);

/**
 * @brief 同alipay_query_order_result, 区别为额外返回字符串形式的额度信息；
 * @param status 
 * @param pay_amount 
 * @param ext_data 
 * @param ext_data_len 
 * @return  RV_OK  查询接口调用成功，此时会输出status和bitmap_amount
 *          若返回值为其他，则说明查询接口调用失败。可能的失败原因如下：
 * -------------------------------------------------------------------
 *          RV_IO_ERROR 获取设备本地信息失败
 *          RV_WRONG_PARAM  输入参数不合法
 *          RV_NOT_INPROCESSING 当前没有获取支付码，无法查询支付结果
 *          RV_READ_ERROR  本地数据读取失败，可能是数据损坏或已解绑
            -----------以下错误建议重试------------
 *          RV_UNKNOWN  未知错误
 *          RV_JS_ERROR  json操作异常-可能是内存不足
 *          RV_NETWORK_ERROR  网络异常
 */
int Helios_alipay_query_order_result_string(char* pay_code, alipay_payment_status_e *status, char pay_amount[32], char *ext_data, uint32_t *ext_data_len);

/***
 * 获取支付码支付结果
 * @param   [in]collection_code    用于查询的收款码码串，来自「alipay_get_collectioncode」接口
 * @param   [out]alipay_income_detail_info_t  用法同「alipay_query_order_result」
 * @return  RV_OK  查询接口调用成功，此时会输出status和bitmap_amount
 *          若返回值为其他，则说明查询接口调用失败。可能的失败原因如下：
 * -------------------------------------------------------------------
 *          RV_IO_ERROR 获取设备本地信息失败
 *          RV_WRONG_PARAM  输入参数不合法
 *          RV_NOT_INPROCESSING 当前没有获取支付码，无法查询支付结果
 *          RV_READ_ERROR  本地数据读取失败，可能是数据损坏或已解绑
            -----------以下错误建议重试------------
 *          RV_UNKNOWN  未知错误
 *          RV_JS_ERROR  json操作异常-可能是内存不足
 *          RV_NETWORK_ERROR  网络异常
 */
int Helios_alipay_query_income_details(char* collection_code, alipay_income_detail_info_t *income_detail);

/***
 * 打断付款码支付结果query接口的执行，让接口立即返回
 * 注意：只允许用来打断alipay_query_order_result接口，请勿在其它接口执行时调用
 */
void Helios_alipay_query_flow_break(void);

/**
 * @brief 检查设备授权状态
 * @return 是否授权
 */
bool Helios_alipay_check_active_status(void);

/**
 * @brief 获取设备端授权请求信息
 * @param buf_output 授权请求内容
 * @param len_output 授权请求长度
 * @return 错误码
 */
int Helios_alipay_get_active_request(uint8_t* buf_output, uint32_t *len_output);

/**
 * @brief 获取设备端授权请求信息(阿里云专用)
 * @param buf_output 授权请求内容
 * @param len_output 授权请求长度
 * @return 错误码
 */
int Helios_alipay_get_active_request_campt(const char* model, uint8_t* buf_output, uint32_t *len_output);

/**
 * @brief 同步蚂蚁链激活接口
 * @param buf_input 激活请求输入
 * @param len_input 激活请求输入长度
 * @param buf_output 激活请求
 * @param len_output 激活请求长度
 * @return EXTERNC 
 */
int Helios_alipay_get_active_request_with_antchain(uint8_t* buf_output, uint32_t *len_output);

/**
 * @brief 保存授权信息
 * @param buf_input 授权信息内容
 * @param len_input 授权信息长度
 * @return 错误码
 */
int Helios_alipay_save_active_response(uint8_t* buf_input, uint32_t len_input);

/**
 * 用于测试安全环境通用ecc算法
*/
int Helios_alipay_check_ecc_alg(void);

/***
 * 在证书空发流程中需要用到，若采用产线烧录则忽略该接口，
 * 获取用于去云端兑换证书的数据
 * @param [out]auth_data        去兑换证书的数据，建议大小为2k
 * @param [inout]len_auth_data  输入的时候为允许获取的最大长度，输出的时候为实际获取的长度
 * @return  RV_OK               成功
 *          RV_JS_ERROR         Json操作错误
 *          RV_BUF_TOO_SHORT    允许获取的最大长度过短
 *          RV_UNKNOWN          未知错误
 */
int Helios_alipay_secure_get_auth_data(char* auth_data, uint32_t* len_auth_data);

/***
 * 在证书空发流程中需要用到，若采用产线烧录则忽略该接口，
 * 解析接收到的数据
 * @param [in]auth_data        接收到的数据
 * @return  RV_OK              解析成功
 *          RV_IO_ERROR             文件系统操作错误
 *          RV_UNKNOWN              未知错误
 */
int Helios_alipay_secure_rcv_dev_cert(char* data);

/**
 * 判断是否需要获取证书
 * @return  1：    本地没有找到证书，需要获取证书
 *          0：    本地有证书
 */
int Helios_alipay_is_need_to_request_cert(void);

/**
 * 获取缓存的绑定状态
 * @param [in] void
 * @return 返回绑定状态(是否已经绑定)
 */
bool Helios_alipay_get_binding_status(void);

/**
 * 获取缓存的的logon_ID
 * @param [out] id 存放数据的指针，建议buffer大小为128
 * @param [inout] len_id数据大小，输入时为最大允许读取长度，输出时为实际长度
 * @return  RV_OK：读取成功
 *          RV_NOT_FOUND：未发现该存储项
 */
int Helios_alipay_get_logon_ID(uint8_t *id, uint32_t *len_id);

/**
 * 读取存储的nick_name
 * @param [out] nick_name 存放数据的指针，，建议buffer大小为128
 * @param [out] len_nick_name数据大小，输入时为最大允许读取长度，输出时为实际长度
 * @return  RV_OK：读取成功
 *          RV_NOT_FOUND：未发现该存储项
 */
int Helios_alipay_get_nick_name(uint8_t *nick_name, uint32_t *len_nick_name);

/**
 * 支付功能解绑，清除绑定数据
 * @return  RV_OK：    成功
 *          其他value：失败  频繁失败说明芯片可能出错，建议禁止支付功能
 */
int Helios_alipay_unbinding(void);

/**
 * @brief 清除所有数据，包括安全环境(含加密芯片中的账户维度 + 设备维护的所有数据) 耗时较多
 * @return 
 *          RV_OK：    成功
 *          其他value：失败  频繁失败说明芯片可能出错，建议禁止支付功能
 */
int Helios_alipay_reset_all(void);

void Helios_alipay_set_i2c_port(int se_i2c_no, int se_i2c_reset);

void Helios_alipay_se_i2c_init(void);

void Helios_alipay_se_enter_lpm(void);

void Helios_alipay_se_exit_lpm(void);

void Helios_alipay_set_vendor_info(char name[20U+1], char model[20U+1]);

void Helios_alipay_set_product_type(alipay_product_type type);

#endif


