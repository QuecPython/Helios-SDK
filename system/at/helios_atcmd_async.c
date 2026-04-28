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
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "helios_debug.h"
#include "helios_os.h"
#include "helios_atcmd.h"
#include "helios_atcmd_async.h"

#define atcmd_debug(fmt, ...) custom_log(APP, fmt, ##__VA_ARGS__)

Helios_Thread_t helios_AT_cmd_async_thread_handle = 0;
Helios_MsgQ_t   helios_AT_cmd_async_msq = 0;

helios_atcmd_send_callback_t helios_atcmd_send_user_cb = NULL;

typedef struct
{
    uint8_t sim_id;
    char *cmd;
    char *resp;
    int resp_len;
    char *include_str;
    int time_out;
} Helios_ATCmdAttr;

void helios_AT_cmd_async_thread(void *argv)
{
    (void)argv;
    int ret = 0;
    int att_p = 0;
    Helios_ATCmdAttr *atcmd = NULL;
    while(1){
        ret = Helios_MsgQ_Get(helios_AT_cmd_async_msq, &att_p, sizeof(int), HELIOS_WAIT_FOREVER);
        if(ret != 0){
            atcmd_debug("faile to get queue,ret=%d\r\n",ret);
            continue;
        }
        atcmd = (Helios_ATCmdAttr *)att_p;
        ret = Helios_Atcmd_Send_Sync(atcmd->sim_id, atcmd->cmd, atcmd->resp, atcmd->resp_len, atcmd->include_str, atcmd->time_out);
        if(helios_atcmd_send_user_cb){
            helios_atcmd_send_user_cb(ret);
        }
        if(atcmd){
            free(atcmd);
        }
    }
    Helios_Thread_Delete(helios_AT_cmd_async_thread_handle);
}

int Helios_Atcmd_Thread_Init(void *cb)
{
    Helios_ThreadAttr ThreadAttr = {
        .name = "helios_AT_cmd_async_thread",
        .stack_size = 1024,
        .priority = 100,
        .entry = helios_AT_cmd_async_thread,
        .argv = NULL
    };
    if(cb){
        helios_atcmd_send_user_cb = (helios_atcmd_send_callback_t)cb;
    }

    if(0 == helios_AT_cmd_async_msq){
        helios_AT_cmd_async_msq = Helios_MsgQ_Create(1, sizeof(int));
        if(0 == helios_AT_cmd_async_msq){
            atcmd_debug("msg queue creat faile!!!\r\n");
            goto error_exit;
        }
    }

    if(0 == helios_AT_cmd_async_thread_handle){
        helios_AT_cmd_async_thread_handle = Helios_Thread_Create(&ThreadAttr);
        if(0 == helios_AT_cmd_async_thread_handle){
            atcmd_debug("helios_AT_cmd_async_thread creat faile!!!\r\n");
            goto error_exit;
        }
    }
    return 0;

error_exit:
    if(helios_AT_cmd_async_thread_handle){
        Helios_Thread_Delete(helios_AT_cmd_async_thread_handle);
        helios_AT_cmd_async_thread_handle = 0;
    }
    if(helios_AT_cmd_async_msq){
        Helios_MsgQ_Delete(helios_AT_cmd_async_msq);
        helios_AT_cmd_async_msq = 0;
    }
    return -1;
}

void Helios_Atcmd_Thread_Deinit(void)
{
    if(helios_AT_cmd_async_thread_handle){
        Helios_Thread_Delete(helios_AT_cmd_async_thread_handle);
        helios_AT_cmd_async_thread_handle = 0;
    }
    if(helios_AT_cmd_async_msq){
        Helios_MsgQ_Delete(helios_AT_cmd_async_msq);
        helios_AT_cmd_async_msq = 0;
    }    
}

int Helios_Atcmd_Send_by_Thread(uint8_t sim_id,char *cmd,char *resp,int resp_len,char *include_str,int time_out)
{
    if(0 == helios_AT_cmd_async_thread_handle || 0 == helios_AT_cmd_async_msq){
        return -1;
    }

    Helios_ATCmdAttr *att = malloc(sizeof(Helios_ATCmdAttr));
    if(NULL == att){
        return -1;
    }
    att->sim_id      = sim_id;
    att->cmd         = cmd;
    att->resp        = resp;
    att->resp_len    = resp_len;
    att->include_str = include_str;
    att->time_out    = time_out;

    Helios_MsgQ_Put(helios_AT_cmd_async_msq, (void *)&att, sizeof(int), HELIOS_NO_WAIT);

    return 0;
}