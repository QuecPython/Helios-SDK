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


#if !defined(PLAT_ASR) && !defined(PLAT_EIGEN) && !defined(PLAT_ECR6600) && !defined(PLAT_EIGEN_718)

#include "helios_debug.h"
#include "helios_os.h"
#include "helios_startup.h"
#if !defined(PLAT_RDA)
#if CONFIG_MBEDTLS
#include "mbedtls_init.h"
#endif
#endif


extern void * __appRegTable_start__;
extern void * __appRegTable_end__;

static void appRegTableSplitArray(appRegItem_t* arr, int low, int high, int *p ) 
{ 
    int i, j;
    int item;
    appRegItem_t t;

    item = arr[low].startup_prio;
    i = low;
    j = high;

    while( i < j )
    {
        /*  move from R to L in search of element < item */
        while ( arr[j].startup_prio> item )
            j = j - 1;

        /*  move from L to R in search of element > item */
        while ( arr[i].startup_prio<= item  &&  i < j )
            i = i + 1;

        if ( i < j )
        {
            t = arr[i];
            arr[i] = arr[j];
            arr[j] = t;
        }
    }
    *p = j;
    t = arr[low];
    arr[low] = arr[*p];
    arr[*p] = t;
}

static void appRegTableQuickSort(appRegItem_t* arr, int low, int high )
{
    int pos;

    if( low < high )
    {
        appRegTableSplitArray( arr, low, high, &pos );
        appRegTableQuickSort( arr, low, pos - 1 );
        appRegTableQuickSort( arr, pos + 1, high );
    }
}

static void AppStartupTask(void *argv)
{
	helios_debug("app(0x%p) started\r\n", argv);
	
	((app_entry_t)argv)(NULL);

	Helios_Thread_Exit();
}

static void AppStartup(void)
{
	uint32_t appRegItemNum = (appRegItem_t *)&__appRegTable_end__ - (appRegItem_t *)&__appRegTable_start__;
	appRegItem_t * appRegTable = (appRegItem_t *)&__appRegTable_start__;
	uint32_t itemIdx = 0;

	helios_debug("appRegTable start addr: 0x%p\r\n", &__appRegTable_start__);
	helios_debug("appRegTable end addr:   0x%p\r\n", &__appRegTable_end__);
	helios_debug("size of per appRegItem: 0x%p\r\n", sizeof(appRegItem_t));
	helios_debug("appRegItemNum: %d\r\n", appRegItemNum);

	if(appRegItemNum)
		appRegTableQuickSort(appRegTable, 0, appRegItemNum - 1);

	for(; itemIdx < appRegItemNum; itemIdx++)
	{
        Helios_ThreadAttr ThreadAttr = {
            .name = appRegTable[itemIdx].name,
            .stack_size = appRegTable[itemIdx].stack_size,
            .priority = 100,
            .entry = AppStartupTask,
            .argv = appRegTable[itemIdx].entry
        };
        
		helios_debug("app[%d] (0x%p) starting ...\r\n", itemIdx, appRegTable[itemIdx].entry);
        Helios_Thread_Create(&ThreadAttr);
	}
}

void application_start(void)
{
    Helios_Debug_Enable();
    helios_debug("application_start\r\n");

    AppStartup();
}

#endif
