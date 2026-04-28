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
 /* AUTHOR  Felix.Ye                           */
 /* DATA    2021.07.22                          */
 /* =========================================== */
#include "helios.h"
#include "helios_debug.h"
#include "helios_os.h"
#include "helios_atcmd_async.h"

#define at_debug(fmt, ...) custom_log(APP, fmt, ##__VA_ARGS__)

#define ATCMD_RESP_LEN_MAX 1024

char resp_buff[ATCMD_RESP_LEN_MAX] = {0};

void user_atcmd_cb(int sta)
{
    at_debug("atcmd sta = %d\r\n",sta);
    if(0 == sta){
        at_debug("resp: %s\r\n",resp_buff);
    }
}

void quec_atcmd_async_test(void *argv)
{
    int ret = 0;
	at_debug(" quec_atcmd_async_test start \n");
    (void)argv;

    //Initialize and register the callback function
    ret = Helios_Atcmd_Thread_Init(user_atcmd_cb);  
    if(ret != 0){
        at_debug("faile to init atcmd\r\n");
    }

    //"AT+QHEAPS?\r\n" is is the instruction  for the ASR to query the heap, as a demonstration
    Helios_Atcmd_Send_by_Thread(0, "AT+QHEAPS?\r\n", resp_buff, ATCMD_RESP_LEN_MAX, " ", 20);

    while(1){
        Helios_sleep(1);
    }
}

//application_init(quec_atcmd_async_test, "quec_atcmd_async_test", 2, 0);
