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
 /* AUTHOR  felix.Ye                           */
 /* DATA    2021.08.18                          */
 /* =========================================== */


/*===========================================================================
 * include files
 ===========================================================================*/
#include <stdlib.h>
#include <string.h>
#include "helios.h"
#include "helios_debug.h"
#include "helios_os.h"
#include "helios_uart.h"


/*===========================================================================
 * Macro Definition
 ===========================================================================*/
#define uart_debug(fmt, ...) custom_log(APP, fmt, ##__VA_ARGS__)
#define UART_RX_BUFF_SIZE   2048
#define TEST_UART			HELIOS_UART2
#ifndef MIN
#define MIN(n, m)   (((n) < (m)) ? (n) : (m))
#endif


/*===========================================================================
 * Variate
 ===========================================================================*/
static Helios_Thread_t thread_id;

/*===========================================================================
 * Functions
 ===========================================================================*/
 
void uart_callback(uint64_t ind_type, Helios_UARTNum port, uint64_t size)
{
    unsigned char *recv_buff = calloc(1, UART_RX_BUFF_SIZE+1);
    unsigned int real_size = 0;
    int read_len = 0;
    
    if(0 == ind_type)
    {
        while(size > 0)
        {
            memset(recv_buff, 0, UART_RX_BUFF_SIZE+1);
            real_size= MIN(size, UART_RX_BUFF_SIZE);
            
            read_len = Helios_UART_Read(port, recv_buff, real_size);
            uart_debug("read_len=%d, recv_data=%s", read_len, recv_buff);
            if((read_len > 0) && ((int)size >= read_len))
            {
                size -= read_len;
            }
            else
            {
                break;
            }
        }
    }
    free(recv_buff);
    recv_buff = NULL;
}
static void quec_uart_demo_test(	void)
{
    int write_len = 0;
	unsigned char data[] = "hello uart demo\r\n";
	
	Helios_UARTInitStruct uart_para = {0};
	Helios_UARTConfig uart_config = {0};
	uart_para.uart_config = &uart_config;
	uart_config.baudrate = HELIOS_UART_BAUD_115200;
	uart_config.data_bit = HELIOS_UART_DATABIT_8;
	uart_config.flow_ctrl = HELIOS_UART_FC_NONE;
	uart_config.parity_bit = HELIOS_UART_PARITY_EVEN;
	uart_config.stop_bit = HELIOS_UART_STOP_1;
	
	if(Helios_UART_Init(TEST_UART, &uart_para) != 0) {
		uart_debug("Serial port initialization failed\n");
		return;
	}

	if(0 != Helios_UART_SetCallback(TEST_UART, uart_callback)) {
		uart_debug("Serial port callback setting failed\n");
		return;
	}

	while(1)
	{	
		write_len = Helios_UART_Write(TEST_UART, data, strlen((char *)data));
		uart_debug("write_len:%d", write_len);
	
		Helios_sleep(2);
	}

	Helios_UART_Deinit(TEST_UART);
}


static void uart_test_func_entry(void * argv)
{
	Helios_sleep(3);
    uart_debug("adc demo thread enter, param 0x%x", argv);
	quec_uart_demo_test();

	Helios_Thread_Delete(thread_id);

}

void quec_uart_test(void *argv)
{
	uart_debug(" quec_uart_test start \n");
    (void)argv;
    Helios_ThreadAttr ThreadAttr = {
        .name = "uart_test",
        .stack_size = 4096,
        .priority = 100,
        .entry = uart_test_func_entry,
        .argv = NULL
    };

    thread_id = Helios_Thread_Create(&ThreadAttr);
}

//application_init(quec_uart_test, "quec_uart_test", 2, 0);
