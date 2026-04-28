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
#include "helios_nw.h"

#define nw_debug(fmt, ...) custom_log(APP, fmt, ##__VA_ARGS__)

//当前不支持双卡，故用例中simid始终传0
#define SIM_ID 0

void user_nw_event_handle_callback(uint8_t sim_id, int32_t event_id, void *ctx)
{
    (void)sim_id;
    (void)ctx;
    switch (event_id)
	{
		case HELIOS_NW_DATA_REG_STATUS_IND:
			/* ... */
			nw_debug("[net] ind_flag = %x\r\n", event_id);
			break;
		case HELIOS_NW_VOICE_REG_STATUS_IND:
			/* ... */
			nw_debug("[net] ind_flag = %x\r\n", event_id);
			break;
		case HELIOS_NW_NITZ_TIME_UPDATE_IND:
			/* ... */
			nw_debug("[net] ind_flag = %x\r\n", event_id);
			break;
		case HELIOS_NW_SIGNAL_QUALITY_IND:
			/* ... */
			nw_debug("[net] ind_flag = %x\r\n", event_id);
			break;
		default:
			nw_debug("[net] event handler, ind=%x\r\n", event_id);
			break;
	}
}

static void nw_test_func_entry(void * argv)
{
	int  ret;

    (void)argv;
    Helios_NwInitStruct info = {0};
    info.user_cb = user_nw_event_handle_callback;
    
	Helios_sleep(10);

	Helios_Nw_Init(&info);

	Helios_sleep(10);

    ret = Helios_Nw_GetCSQ(SIM_ID);
    if (ret >= 0)
        nw_debug("CSQ[%d]\n",ret);

    Helios_NwCellInfoStruct cellinfo = {0};
    ret = Helios_Nw_GetCellInfo(SIM_ID, &cellinfo);
    if (ret != 0)
        nw_debug("nw get cellinfo failed\n");
    else 
        nw_debug("gsm_info_num[%d],lte_info_num[%d],umts_info_num[%d]\n",cellinfo.gsm_info_num,cellinfo.lte_info_num,cellinfo.umts_info_num);

    Helios_NwSelectionInfoStruct selectioninfo = {0};
    ret = Helios_Nw_GetSelection(SIM_ID, &selectioninfo);
    if (ret != 0)
        nw_debug("nw get selectioninfo failed\n");
    else 
        nw_debug("selectionmode[%d],mcc[%s],mnc[%s],act[%d]\n",selectioninfo.nw_selection_mode,selectioninfo.mcc,selectioninfo.mnc,selectioninfo.act);

    Helios_NwSignalStrengthInfoStruct signalinfo = {0};
    ret = Helios_Nw_GetSignalStrength(SIM_ID, &signalinfo);
    if (ret != 0)
        nw_debug("nw get signalstrength failed\n");

    Helios_NwNITZTimeInfoStruct timeinfo = {0};
    ret = Helios_Nw_GetNITZTime(&timeinfo);
    if (ret != 0)
        nw_debug("nw get NITZtime failed\n");
    else 
        nw_debug("nitztime[%s],abstime[%d],leaptime[%d]\n",timeinfo.nitz_time,timeinfo.abs_time,timeinfo.leap_sec);

    Helios_NwOperatorInfoStruct operatorinfo = {0};
    ret = Helios_Nw_GetOperatorName(SIM_ID, &operatorinfo);
    if (ret != 0)
        nw_debug("nw get operatorname failed\n");
    else 
        nw_debug("longname[%s],shortname[%s],mnc[%s],mcc[%s]\n",operatorinfo.long_name,operatorinfo.short_name,operatorinfo.mnc,operatorinfo.mcc);

    Helios_NwRegisterStatusInfoStruct registerinfo = {0};
    ret = Helios_Nw_GetRegisterStatus(SIM_ID, &registerinfo);
    if (ret != 0)
        nw_debug("nw get operatorname failed\n");
}

void quec_nw_test(void *argv)
{
	nw_debug(" quec_nw_test start \n");
    (void)argv;
    Helios_ThreadAttr ThreadAttr = {
        .name = "nw_test",
        .stack_size = 4096,
        .priority = 100,
        .entry = nw_test_func_entry,
        .argv = NULL
    };

    Helios_Thread_Create(&ThreadAttr);
}

//application_init(quec_nw_test, "quec_nw_test", 2, 0);
