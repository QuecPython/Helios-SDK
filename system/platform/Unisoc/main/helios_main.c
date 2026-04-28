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


#include "helios_debug.h"
#include "helios_os.h"
#include "osi_log.h"
#include "osi_api.h"
#include "helios_voicecall.h"


#define OSI_LOG_TAG OSI_MAKE_LOG_TAG('H', 'L', 'O', 'S')

static void prvInvokeGlobalCtors(void)
{
    extern void (*__init_array_start[])();
    extern void (*__init_array_end[])();

    size_t count = __init_array_end - __init_array_start;
    for (size_t i = 0; i < count; ++i)
        __init_array_start[i]();
}

extern void application_start(void);


static void prvThreadEntry(void *param)
{
    OSI_LOGI(0, "application thread enter, param 0x%x", param);
    #if defined(PLAT_Unisoc) && defined(CONFIG_VIOCE_CALL)
    Helios_VoiceCall_Set_Ringtone_type(HELIOS_AUD_RING_CUSTOMER_DEF);
    #endif

    application_start();
    Helios_Thread_Exit();
    
}

int appimg_enter(void *param)
{
    OSI_LOGI(0, "application image enter, param 0x%x", param);

    prvInvokeGlobalCtors();

    Helios_ThreadAttr ThreadAttr = {
        .name = "application",
        .stack_size = 4096,
        .priority = 100,
        .entry = prvThreadEntry,
        .argv = NULL
    };

    Helios_Thread_Create(&ThreadAttr);

    return 0;
}

void appimg_exit(void)
{
    helios_debug("application image exit");
}
