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

#include "helios.h"
#include "helios_debug.h"
#include "helios_os.h"

#define app_debug(fmt, ...) custom_log(APP, fmt, ##__VA_ARGS__)

static void AppSample(void *argv)
{
    UNUSED(argv);

    while (1)
    {
        app_debug("app sample running ...\r\n");
        Helios_sleep(1);
    }
}

application_init(AppSample, "AppSample", 2, 0);
