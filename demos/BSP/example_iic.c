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
#include "helios_iic.h"


/*===========================================================================
 * Macro Definition
 ===========================================================================*/
#define iic_debug(fmt, ...) custom_log(APP, fmt, ##__VA_ARGS__)
#define I2C_SLAVE_ADDR  0x1B	//codec 5616
static unsigned char who_am_i = 0x02;
#define WHO_AM_I_VALUE  0x12
#define IIC_NO			HELIOS_I2C1
#define IIC_MODE		HELIOS_STANDARD_MODE



/*===========================================================================
 * Variate
 ===========================================================================*/
static Helios_Thread_t thread_id;

/*===========================================================================
 * Functions
 ===========================================================================*/
int quec_iic_demo_test(	void)
{
	iic_debug("quec_iic_demo_test enter\n");
	int iRet;
	unsigned char wrtBuff[2] = {WHO_AM_I_VALUE, 0};
	unsigned char rdBuff[2] = {0, 0};	
#if defined(PLAT_aic8800m40)
	iRet = Helios_I2C_Init(IIC_NO, IIC_MODE, 0);
#else
	iRet = Helios_I2C_Init(IIC_NO, IIC_MODE);
#endif
	if(iRet != 0) {
		iic_debug("i2c init fail\n");
		return -1;
	}
	
	
	
	iRet = HELIOS_I2C_Write(IIC_NO, I2C_SLAVE_ADDR, &who_am_i, 1, wrtBuff, 2);
	iic_debug("< write i2c value=0x%x, iRet=%d >\n", WHO_AM_I_VALUE, iRet);
	iRet = HELIOS_I2C_Read(IIC_NO, I2C_SLAVE_ADDR, &who_am_i, 1, rdBuff, 2, 0);
	iic_debug("< read i2c iRet=%d, value=0x%x%x >\n", iRet, rdBuff[1], rdBuff[0]);//Little endian
	
	return 0;
}


static void iic_test_func_entry(void * argv)
{
	Helios_sleep(3);
    iic_debug("iic demo thread enter, param 0x%x", argv);
	quec_iic_demo_test();

	Helios_Thread_Delete(thread_id);

}

void quec_iic_test(void *argv)
{
	iic_debug(" quec_iic_test start \n");
    (void)argv;
    Helios_ThreadAttr ThreadAttr = {
        .name = "iic_test",
        .stack_size = 4096,
        .priority = 100,
        .entry = iic_test_func_entry,
        .argv = NULL
    };

    thread_id = Helios_Thread_Create(&ThreadAttr);
}

//application_init(quec_iic_test, "quec_iic_test", 2, 0);
