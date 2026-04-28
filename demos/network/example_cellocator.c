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
 /* DATA    2021.07.26                          */
 /* =========================================== */
#include "helios.h"
#include "helios_debug.h"
#include "helios_os.h"
#include "helios_celllocator.h"

#define celllocator_debug(fmt, ...) custom_log(APP, fmt, ##__VA_ARGS__)

//当前不支持双卡，故用例中simid始终传0
#define SIM_ID 0
static void celllocator_test_func_entry(void * argv)
{
    (void)argv;
    Helios_LBSConfigStruct lbs_config = {0};
    Helios_LBS_SetConfiguration(SIM_ID, &lbs_config);

    Helios_LBSInfoStruct lbs_info = {0};
    Helios_LBS_GetPosition(&lbs_info);
}

void quec_celllocator_test(void *argv)
{
	celllocator_debug(" quec_celllocator_test start \n");
    (void)argv;
    Helios_ThreadAttr ThreadAttr = {
        .name = "celllocator_test",
        .stack_size = 4096,
        .priority = 100,
        .entry = celllocator_test_func_entry,
        .argv = NULL
    };

    Helios_Thread_Create(&ThreadAttr);
}

//application_init(quec_celllocator_test, "quec_celllocator_test", 2, 0);
