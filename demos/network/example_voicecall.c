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
 /* DATA    2021.07.22                          */
 /* =========================================== */
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "helios.h"
#include "helios_debug.h"
#include "helios_os.h"
#include "helios_voicecall.h"

#define voicecall_debug(fmt, ...) custom_log(APP, fmt, ##__VA_ARGS__)

//当前不支持双卡，故用例中simid始终传0
#define SIM_ID 0
typedef struct {
    HELIOS_VC_EVENT_ID_E voicecall_state;
}VOICECALL_CMMsg;

Helios_MsgQ_t g_vc_msgQueue;

void user_voicecall_event_handle_callback(uint8_t sim_id, int32_t event_id, void *ctx)
{
    VOICECALL_CMMsg *vc_states_msg;
    vc_states_msg=(VOICECALL_CMMsg *)malloc(sizeof(VOICECALL_CMMsg));
	if (vc_states_msg == NULL)
        return;

    (void)sim_id;
    (void)ctx;
    
	switch(event_id)
	{
		case HELIOS_VC_RING_IND:
			{
				voicecall_debug(" HELIOS_VC_RING_IND \n");
                //解析ctx参数的结构体如下，不建议直接在回调中处理
                //建议发消息出去处理，回调栈的空间只有1K，使用不当会造成死机
                //以下同理
                //Helios_call_incoming *voicecall_info = (Helios_call_incoming *)ctx;
                memset(vc_states_msg, 0, sizeof(VOICECALL_CMMsg));
                vc_states_msg->voicecall_state = event_id;
                Helios_MsgQ_Put(g_vc_msgQueue, (void *)vc_states_msg, sizeof(VOICECALL_CMMsg), HELIOS_NO_WAIT);
			}
			break;

        case HELIOS_VC_CONNECT_IND:
			{
				voicecall_debug(" HELIOS_VC_CONNECT_IND \n");           
                //解析ctx参数的结构体如下
                //Helios_call_connect *voicecall_info = (Helios_call_connect *)ctx;
                memset(vc_states_msg, 0, sizeof(VOICECALL_CMMsg));
                vc_states_msg->voicecall_state = event_id;
                Helios_MsgQ_Put(g_vc_msgQueue, (void *)vc_states_msg, sizeof(VOICECALL_CMMsg), HELIOS_NO_WAIT);
			}
			break;
            
        case HELIOS_VC_NOCARRIER_IND:
			{
				voicecall_debug(" HELIOS_VC_NOCARRIER_IND \n");
                //解析ctx参数的结构体如下
                //Helios_call_disconnect *voicecall_info = (Helios_call_disconnect *)ctx;
                memset(vc_states_msg, 0, sizeof(VOICECALL_CMMsg));
                vc_states_msg->voicecall_state = event_id;
                Helios_MsgQ_Put(g_vc_msgQueue, (void *)vc_states_msg, sizeof(VOICECALL_CMMsg), HELIOS_NO_WAIT);
			}
			break;
            
        case HELIOS_VC_CCWA_IND:
			{
				voicecall_debug(" HELIOS_VC_CCWA_IND \n");
                //解析ctx参数的结构体如下
                //Helios_call_waiting *voicecall_info = (Helios_call_waiting *)ctx;
                memset(vc_states_msg, 0, sizeof(VOICECALL_CMMsg));
                vc_states_msg->voicecall_state = event_id;
                Helios_MsgQ_Put(g_vc_msgQueue, (void *)vc_states_msg, sizeof(VOICECALL_CMMsg), HELIOS_NO_WAIT);
			}
			break;

        case HELIOS_VC_RING_VOLTE_IND:
        case HELIOS_VC_CONNECT_VOLTE_IND:
        case HELIOS_VC_NOCARRIER_VOLTE_IND:
        case HELIOS_VC_CCWA_VOLTE_IND:
            {
                voicecall_debug(" HELIOS_VC_VOLTE \n");
                //解析ctx参数的结构体如下
                //Helios_call_volte *voicecall_info = (Helios_call_volte *)ctx;
                memset(vc_states_msg, 0, sizeof(VOICECALL_CMMsg));
                vc_states_msg->voicecall_state = event_id;
                Helios_MsgQ_Put(g_vc_msgQueue, (void *)vc_states_msg, sizeof(VOICECALL_CMMsg), HELIOS_NO_WAIT);
            }
        break;
        
		default:
			break;
	}
}

static void listen_voicecall_states_func_entry()
{
    int ret = 0;
    VOICECALL_CMMsg *vc_states_msg;

    g_vc_msgQueue = Helios_MsgQ_Create(256, sizeof(VOICECALL_CMMsg));

	vc_states_msg=(VOICECALL_CMMsg *)malloc(sizeof(VOICECALL_CMMsg));
	if (vc_states_msg == NULL)
        return;

    while(1)
    {
        memset(vc_states_msg, 0, sizeof(VOICECALL_CMMsg));
        ret = Helios_MsgQ_Get(g_vc_msgQueue, (void *)vc_states_msg, sizeof(VOICECALL_CMMsg), HELIOS_WAIT_FOREVER);
        if (ret != 0)
            goto exit;

        voicecall_debug("%s: rcv msg type is %d",__func__,vc_states_msg->voicecall_state);

        switch(vc_states_msg->voicecall_state)
        {
            case HELIOS_VC_RING_IND:
            case HELIOS_VC_RING_VOLTE_IND:
    			{
    			    Helios_VoiceCall_Answer(SIM_ID);
    			}
    			break;

            case HELIOS_VC_CONNECT_IND:
            case HELIOS_VC_CONNECT_VOLTE_IND:
    			{
    			    Helios_VoiceCall_Start_Dtmf(SIM_ID, "123A", 500);
                    Helios_sleep(10);
                    Helios_VoiceCall_End(SIM_ID);
    			}
    			break;
                
            case HELIOS_VC_NOCARRIER_IND:
            case HELIOS_VC_NOCARRIER_VOLTE_IND:
    			{
    			    
    			}
    			break;

    		default:
    			break;
        }
    } 

exit:
    if (vc_states_msg)
    {
        free(vc_states_msg);
        vc_states_msg = NULL;
    }
    return;
}

static void voicecall_test_func_entry(void * argv)
{
    (void)argv;
    Helios_VoiceCallInitStruct info = {0};
    info.user_cb = user_voicecall_event_handle_callback;
    
	Helios_sleep(10);

	Helios_VoiceCall_Register(&info);

    Helios_sleep(10);

     Helios_ThreadAttr ThreadAttr = {
        .name = "listen_vc_state",
        .stack_size = 1024,
        .priority = 100,
        .entry = listen_voicecall_states_func_entry,
        .argv = NULL
    };

    Helios_Thread_Create(&ThreadAttr);
    
    Helios_VoiceCall_start(SIM_ID, "13855169092");
}

void quec_voicecall_test(void *argv)
{
	voicecall_debug(" quec_voicecall_test start \n");
    (void)argv;
    Helios_ThreadAttr ThreadAttr = {
        .name = "voicecall_test",
        .stack_size = 4096,
        .priority = 100,
        .entry = voicecall_test_func_entry,
        .argv = NULL
    };

    Helios_Thread_Create(&ThreadAttr);
}

//application_init(quec_voicecall_test, "quec_voicecall_test", 2, 0);
