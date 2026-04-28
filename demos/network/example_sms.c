/* Copyright (c) Quectel Wireless Solution, Co., Ltd.All Rights Reserved.
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
 /* =========================================== */
 /* AUTHOR  Mia.Zhong                           */
 /* DATA    2021.07.20                          */
 /* =========================================== */
#include "helios.h"
#include "helios_debug.h"
#include "helios_os.h"
#include "helios_sms.h"

#define sms_debug(fmt, ...) custom_log(APP, fmt, ##__VA_ARGS__)

void user_sms_event_handle_callback(uint8_t sim_id, int32_t event_id, void *ctx)
{
    (void)sim_id;
    (void)ctx;
	switch(event_id)
	{
		case HELIOS_SMS_NEW_MSG_IND:
			{
				sms_debug(" HELIOS_SMS_NEW_MSG_IND \n");
                //解析ctx参数的结构体如下，不建议直接在回调中处理
                //建议发消息出去处理，回调栈的空间只有1K，使用不当会造成死机
                //Helios_SMSNewMsgInfoStruct *msg_info = (Helios_SMSNewMsgInfoStruct *)ctx;
			}
			break;
		default:
			break;
	}
}

//当前不支持双卡，故用例中simid始终传0
#define SIM_ID 0
static void sms_test_func_entry(void * argv)
{
	int  ret;

    (void)argv;

    Helios_SMSInitStruct info = {0};
    info.user_cb = user_sms_event_handle_callback;
    
	Helios_sleep(10);

	Helios_SMS_Init(&info);

	Helios_sleep(10);

    //mode:0-PDU,1-TEXT
    ret = Helios_SMS_SetMsgMode(SIM_ID, 0);//PDU
    if (ret != 0)
        sms_debug("set msg mode failed!\n");

    //mode:0-GSM,1-UCS2
    ret = Helios_SMS_SetCodeMode(SIM_ID, 0);
    if (ret != 0)
        sms_debug("set code mode failed!\n");

    Helios_SMSSendMsgInfoStruct sendmsg_info = {HELIOS_GSM, "hello,mia", "13855169092"};
    /*sendmsg_info.code = HELIOS_GSM;
    strncpy(sendmsg_info.msg, "hello,mia", strlen("hello,mia"));
    strncpy(sendmsg_info.msg, "13855169092", strlen("13855169092"));*/
    ret = Helios_SMS_SendTextMsg(SIM_ID, &sendmsg_info);
    if (ret != 0)
        sms_debug("send text msg failed\n");
    Helios_sleep(10);

    Helios_SMSSendMsgInfoStruct sendmsg_info_1 = {HELIOS_UCS2, "hello,mia[你好]", "13855169092"};
    /*sendmsg_info.code = HELIOS_UCS2;
    strncpy(sendmsg_info.msg, "hello,mia[你好]", strlen("hello,mia[你好]"));
    strncpy(sendmsg_info.msg, "13855169092", strlen("13855169092"));*/
    ret = Helios_SMS_SendPDUMsg(SIM_ID, &sendmsg_info_1);
    if (ret != 0)
        sms_debug("send PDU msg failed\n");
    Helios_sleep(10);
    
    //Helios_SMS_DeleteMsg(SIM_ID, 0);

    char center_addr[21] = {0};
    ret = Helios_SMS_GetCenterAddress(SIM_ID, center_addr, 14);
    if (ret != 0)
        sms_debug("get center address failed\n");

    ret = Helios_SMS_SetCenterAddress(SIM_ID, center_addr);
    if (ret != 0)
        sms_debug("set center address failed\n");

    Helios_SMSMemGetInfoStruct mem_info = {0};
    ret = Helios_SMS_GetSavingLocation(SIM_ID, &mem_info);
    if (ret != 0)
        sms_debug("get saving location failed\n");
    else 
        sms_debug("mem=%s,current_nums=%d,max_nums=%d\n",mem_info.mem1.mem,mem_info.mem1.current_nums,mem_info.mem1.max_nums);

    Helios_SMSMemSetInfoStruct mem_info_set = {0};
    strncpy(mem_info_set.mem1,"SM",strlen("SM")+1);
    strncpy(mem_info_set.mem2,"SM",strlen("SM")+1);
    strncpy(mem_info_set.mem2,"SM",strlen("SM")+1);
    ret = Helios_SMS_SetSavingLocation(SIM_ID, &mem_info_set);
    if (ret != 0)
        sms_debug("set saving location failed\n");

    //ret = Helios_SMS_SetReceiveDealMode(SIM_ID, 1);//该接口废弃

    //假设index=1是有短信的
    Helios_SMSRecvMsgInfoStruct text_msg = {0};
    ret = Helios_SMS_ReadTextMsg(SIM_ID, 1, &text_msg);
    if (ret != 0)
        sms_debug("read text msg failed\n");
    else 
        sms_debug("phone_num=%s,msg_buf=%s,buf_len=%d\n",text_msg.phone_num,text_msg.msg_buf,text_msg.buf_len);

    Helios_SMSRecvMsgInfoStruct pdu_msg = {0};
    ret = Helios_SMS_ReadPDUMsg(SIM_ID, 1, &pdu_msg);
    if (ret != 0)
        sms_debug("read pdu msg failed\n");
    else 
        sms_debug("msg_buf=%s\n",pdu_msg.msg_buf);
    
    ret = Helios_SMS_GetPDUMsgLength(pdu_msg.msg_buf);
    sms_debug("pdu_length=%d\n",ret);

    ret = Helios_SMS_GetMsgIndex(SIM_ID);
    sms_debug("msg_count=%d\n",ret);
}

void quec_sms_test(void *argv)
{
	sms_debug(" quec_sms_test start \n");
    (void)argv;
    Helios_ThreadAttr ThreadAttr = {
        .name = "sms_test",
        .stack_size = 4096,
        .priority = 100,
        .entry = sms_test_func_entry,
        .argv = NULL
    };

    Helios_Thread_Create(&ThreadAttr);
}

//application_init(quec_sms_test, "quec_sms_test", 2, 0);
