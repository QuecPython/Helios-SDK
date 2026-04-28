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
#include "helios.h"
#include "helios_debug.h"
#include "helios_os.h"
#include "helios_wifiscan.h"

#define wifiscan_debug(fmt, ...) custom_log(APP, fmt, ##__VA_ARGS__)

//当前不支持双卡，故用例中simid始终传0
#define SIM_ID 0

void user_wifiscan_event_handle_callback(uint8_t msg_id, void *ctx)
{
    (void)msg_id;
    (void)ctx;
}

static void wifiscan_test_func_entry(void * argv)
{
	int  ret;
    (void)argv;
    Helios_WifiScanInitStruct info = {0};
    info.user_cb = user_wifiscan_event_handle_callback;
    
	Helios_sleep(10);

	Helios_WifiScan_Init(&info);

    Helios_sleep(10);

    ret = Helios_WifiScan_Support();
    if (ret != 1)
    {
        wifiscan_debug("wifiscan not support\n");
        return;
    }

    ret = Helios_WifiScan_Open();
    if (ret != 0)
    {
        wifiscan_debug("wifiscan open failed\n");
        return;
    }

    Helios_WifiScanConfigStruct conf_info = {0};
    conf_info.timeout = 20;
    conf_info.round = 3;
    conf_info.max_ap_nums = 20;
    conf_info.scan_time = 1;
    conf_info.priority = 0;
    ret = Helios_WifiScan_SetConfiguration(&conf_info);
    if (ret != 0)
    {
        wifiscan_debug("wifiscan set config failed\n");
    }

    memset(&conf_info, 0, sizeof(conf_info));
    ret = Helios_WifiScan_GetConfiguration(&conf_info);
    if (ret == 0) {
        wifiscan_debug("wifiscan_config[%d,%d,%d,%d,%d]\n",conf_info.timeout,conf_info.round,conf_info.max_ap_nums,conf_info.scan_time,conf_info.priority);
    }

    Helios_WifiScanAPInfoStruct ap_info = {0};
    ret = Helios_WifiScan_SyncStart(&ap_info);
    if (ret == 0)
    {
        wifiscan_debug("ap_num=%d\n", ap_info.ap_nums);
    }
}

void quec_wifiscan_test(void *argv)
{
	wifiscan_debug(" quec_wifiscan_test start \n");
    (void)argv;
    Helios_ThreadAttr ThreadAttr = {
        .name = "wifiscan_test",
        .stack_size = 4096,
        .priority = 100,
        .entry = wifiscan_test_func_entry,
        .argv = NULL
    };

    Helios_Thread_Create(&ThreadAttr);
}

//application_init(quec_wifiscan_test, "quec_wifiscan_test", 2, 0);
