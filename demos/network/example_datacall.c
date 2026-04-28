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
 /* DATA    2021.07.23                          */
 /* =========================================== */
#include "helios.h"
#include "helios_debug.h"
#include "helios_os.h"
#include "helios_datacall.h"

#define datacall_debug(fmt, ...) custom_log(APP, fmt, ##__VA_ARGS__)

//当前不支持双卡，故用例中simid始终传0
#define SIM_ID 0
int data_call_state=-1;

void user_datacall_event_handle_callback(int32_t pid, uint8_t sim_id, int32_t status)
{
    (void)sim_id;
    datacall_debug("[datacall] pid = %d, datacall_status = %d\r\n", pid, status);
    data_call_state=status;
}

static void datacall_test_func_entry(void * argv)
{
	int  ret;
    char ip4_addr_str[16] = {0};
    (void)argv;
	Helios_sleep(10);
    
    Helios_DataCallInitStruct DataCallInitStruct = {user_datacall_event_handle_callback};
    Helios_DataCall_Init(1, 0, &DataCallInitStruct);

    Helios_sleep(10);

    Helios_DataCall_SetAutoConnect(1, 0, 1);
    
    Helios_DataCall_SetAsynMode(1, 0, 0);

    Helios_DataCallStartStruct start_info = {0};

    ret = Helios_DataCall_Start(1, 0, &start_info);
    while(data_call_state==-1)
	{
		Helios_msleep(100);
	}
	datacall_debug("data_call_state=%d\n\n", data_call_state);

    Helios_DataCallInfoStruct datacall_info = {0};
    ret = Helios_DataCall_GetInfo(1, 0, &datacall_info);

    datacall_debug("info.profile_idx: %d\r\n", datacall_info.profile_idx);
	datacall_debug("info.ip_version: %d\r\n", datacall_info.ip_version);
	datacall_debug("info.v4.state: %d\r\n", datacall_info.v4.state);
	datacall_debug("info.v4.reconnect: %d\r\n", datacall_info.v4.reconnect);

	inet_ntop(AF_INET, &datacall_info.v4.addr.ip, ip4_addr_str, sizeof(ip4_addr_str));
	datacall_debug("info.v4.addr.ip: %s\r\n", ip4_addr_str);

	inet_ntop(AF_INET, &datacall_info.v4.addr.pri_dns, ip4_addr_str, sizeof(ip4_addr_str));
	datacall_debug("info.v4.addr.pri_dns: %s\r\n", ip4_addr_str);

	inet_ntop(AF_INET, &datacall_info.v4.addr.sec_dns, ip4_addr_str, sizeof(ip4_addr_str));
	datacall_debug("info.v4.addr.sec_dns: %s\r\n", ip4_addr_str);

	ret=Helios_DataCall_Stop(1, 0, 0);
	datacall_debug("helios stop datacall  ret=%d\r\n", ret);
}

void quec_datacall_test(void *argv)
{
	datacall_debug(" quec_datacall_test start \n");
    (void)argv;
    Helios_ThreadAttr ThreadAttr = {
        .name = "datacall_test",
        .stack_size = 4096,
        .priority = 100,
        .entry = datacall_test_func_entry,
        .argv = NULL
    };

    Helios_Thread_Create(&ThreadAttr);
}

//application_init(quec_datacall_test, "quec_datacall_test", 2, 0);
