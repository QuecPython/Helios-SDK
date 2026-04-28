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
#include "helios_sim.h"

#define sim_debug(fmt, ...) custom_log(APP, fmt, ##__VA_ARGS__)

//当前不支持双卡，故用例中simid始终传0
#define SIM_ID 0

static void user_sim_event_handle_callback(uint8_t sim_id, unsigned int event_id, void *ctx)
{
    (void)sim_id;
    (void)ctx;
	switch(event_id)
	{
		case HELIOS_SIM1_INSERT:
			{
				sim_debug(" HELIOS_SIM1_INSERT \n");
			}
			break;

        case HELIOS_SIM1_POLLOUT:
			{
				sim_debug(" HELIOS_SIM1_POLLOUT \n");           
			}
			break;
            
        case HELIOS_SIM2_INSERT:
			{
				sim_debug(" HELIOS_SIM2_INSERT \n");
			}
			break;
            
        case HELIOS_SIM2_POLLOUT:
			{
				sim_debug(" HELIOS_SIM2_POLLOUT \n");
			}
			break;
        
		default:
			break;
	}
}

static void sim_test_func_entry(void * argv)
{
	int  ret;

    (void)argv;
	Helios_sleep(10);
	Helios_SIM_Add_Event_Handler(user_sim_event_handle_callback);
    Helios_sleep(10);
    
    char data[64] = {0};
	size_t data_len = 32;
    ret = Helios_SIM_GetIMSI(SIM_ID, data, data_len);
    if (ret == 0)
        sim_debug("imsi=%s\n",data);

    memset(data,0,sizeof(data));
    ret = Helios_SIM_GetICCID(SIM_ID, data, data_len);
    if (ret == 0)
        sim_debug("iccid=%s\n",data);

    ret = Helios_SIM_GetPhoneNumber(SIM_ID, data, data_len);
    if (ret == 0)
        sim_debug("phonenum=%s\n",data);

    Helios_SIM_Status_e status = 0;
    ret = Helios_SIM_GetCardStatus(SIM_ID,&status);
    if (ret == 0)
        sim_debug("status=%d\n",status);

    Helios_SIMPhoneInfoStruct phone_info = {0};
    memcpy(phone_info.phone_num,"12345678901",strlen("12345678901"));
    memcpy(phone_info.user_name,"quectel-01",strlen("quectel-01"));
    phone_info.index = 1;
    ret = Helios_SIM_WritePhonebookRecord(SIM_ID, HELIOS_SIM_PHONE_BOOK_STORAGE_DC, &phone_info);
    if (ret == 0)
    {
        Helios_SIMReadPhoneBookInfoStruct read_phone_info = {0};
        read_phone_info.start_index = 0;
        read_phone_info.end_index = 5;
        //read_phone_info.user_name = NULL;
        ret = Helios_SIM_ReadPhonebookRecord(SIM_ID, HELIOS_SIM_PHONE_BOOK_STORAGE_DC, &read_phone_info);
        if (ret == 0) {
            //用户可使用for循环自行打印
        }
    }

    Helios_SIMPinInfoStruct pin_info = {0};
    memcpy(pin_info.pin,"1234",strlen("1234"));
    Helios_SIM_PINEnable(SIM_ID, &pin_info);

    Helios_SIM_PINVerify(SIM_ID, &pin_info);

    Helios_SIM_PINDisable(SIM_ID, &pin_info);
}

void quec_sim_test(void *argv)
{
	sim_debug(" quec_sim_test start \n");
    (void)argv;
    Helios_ThreadAttr ThreadAttr = {
        .name = "sim_test",
        .stack_size = 4096,
        .priority = 100,
        .entry = sim_test_func_entry,
        .argv = NULL
    };

    Helios_Thread_Create(&ThreadAttr);
}

//application_init(quec_sim_test, "quec_sim_test", 2, 0);
