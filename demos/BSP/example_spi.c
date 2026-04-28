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

#include "helios.h"
#include "helios_debug.h"
#include "helios_os.h"
#include "helios_spi.h"
#include "string.h"


/*===========================================================================
 * Macro Definition
 ===========================================================================*/
#define spi_debug(fmt, ...) custom_log(APP, fmt, ##__VA_ARGS__)


/*===========================================================================
 * Variate
 ===========================================================================*/
static Helios_Thread_t thread_id;
#define SPI_NO 		HELIOS_SPI1
#define SPI_MODE	HELIOS_SPIMODE0
#define SPI_CLK		4

/*===========================================================================
 * Functions
 ===========================================================================*/
int quec_spi_demo_test(	void)
{
	spi_debug("quec_spi_demo_test enter");
	int ret = -1;
	
	char buf_in[256] = {0};
	char buf_out[128] ="=========This is the spi test !!===========\r\n";
#if defined(PLAT_ASR_1606) || defined(PLAT_ASR_1609) || defined(PLAT_ASR_1602)
	Helios_SPI_Init(SPI_NO, SPI_MODE,SPI_CLK,0);
#else
	Helios_SPI_Init(SPI_NO, SPI_MODE,SPI_CLK);
#endif

	while(1)
	{	

		spi_debug("ql_spi_buf_out:  %s \r\n ",buf_out);
	
		ret= Helios_SPI_WriteRead(SPI_NO, buf_in, strlen(buf_out), buf_out, strlen(buf_out));
		if(ret != 0)
			spi_debug("ql_spi_read error, ret = %d \r\n",ret);
		
		
		spi_debug("ql_spi_buf_in:  %s \r\n",buf_in);

		Helios_sleep(3);
		
	}
	Helios_SPI_Deinit(SPI_NO);
}


static void spi_test_func_entry(void * argv)
{
	Helios_sleep(3);
    spi_debug("spi demo thread enter, param 0x%x", argv);
	quec_spi_demo_test();

	Helios_Thread_Delete(thread_id);

}

void quec_spi_test(void *argv)
{
	spi_debug(" quec_spi_test start \n");
    (void)argv;
    Helios_ThreadAttr ThreadAttr = {
        .name = "spi_test",
        .stack_size = 4096,
        .priority = 100,
        .entry = spi_test_func_entry,
        .argv = NULL
    };

    thread_id = Helios_Thread_Create(&ThreadAttr);
}

//application_init(quec_spi_test, "quec_spi_test", 2, 0);
