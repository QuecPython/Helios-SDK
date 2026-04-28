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

/**
 @file	helios_i2c.h
 @brief	Data type definition for I2C.
*/
/**************************************************************************
===========================================================================
Copyright (c) 2018 Quectel Wireless Solution, Co., Ltd.All Rights Reserved.
Quectel Wireless Solution Proprietary and Confidential.
===========================================================================

						EDIT HISTORY FOR FILE
This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

WHEN		WHO			WHAT,WHERE,WHY
----------  ---------   ---------------------------------------------------
2021/03/29  Felix.Ye	Create.
**************************************************************************/

#ifndef _HELIOS_I2C_H
#define _HELIOS_I2C_H


#ifdef __cplusplus
extern "C" {
#endif

/**
 * Uniform I2C channel interface to the PY layer
 */
typedef enum {
	HELIOS_I2C0 = 0,
	HELIOS_I2C1,
	HELIOS_I2C2,
	HELIOS_I2C3,
}Helios_I2CEnum;


/**
 * The PY layer and the Adapter layer interface transform 
 */
typedef struct {
	Helios_I2CEnum export_i2c_no;
	uint32_t internal_i2c_no;
}Helios_I2CMap;


/**
 * I2C MODE
 */
typedef enum
{
    HELIOS_STANDARD_MODE = 0,  //Standard mode (100K)
    HELIOS_FAST_MODE = 1,      //Fast mode (400K)
    HELIOS_ENHANCED_FAST_MODE = 2,      //Enhanced Fast mode (1M)
} Helios_I2CMode;


/**
 * @brief:
 *      i2c init
 *
 * @param:
 *      \i2c_no   [in]      - i2c channel number
 *      \fastMode [in]      - i2c mode (0-standard mode or 1-fastmode)
 * @return:
 *      i2c init Result, 0 for success,-1 for failure
 */
#if defined(PLAT_aic8800m40)
int Helios_I2C_Init(Helios_I2CEnum i2c_no, Helios_I2CMode Mode,unsigned char group);
#else
int Helios_I2C_Init(Helios_I2CEnum i2c_no, Helios_I2CMode Mode);
#endif
/**
 * @brief:
 *      i2c deinit
 *
 * @param:
 *      \i2c_no   [in]      - i2c channel number
 * @return:
 *      i2c deinit Result, 0 for success,-1 for failure
 */
int Helios_I2C_Deinit(Helios_I2CEnum i2c_no);



/**
 * @brief:
 *      read data from i2c
 *
 * @param:
 *      \i2c_no        [in]    - i2c channel number
 *      \slaveaddress  [in]    - the slave address
 *      \regaddr       [in]    - the address of register
 *      \addrlen       [in]    - the length of regaddr 
 *      \data          [out]   - the read data
 *      \datalen       [in]    - the length of the data read
 *      \wait_times    [in]    - the data conversion time
 *                    
 *
 * @return:
 *      read i2c data result, 0 for success,-1 for failure
 */
int HELIOS_I2C_Read(Helios_I2CEnum i2c_no, uint8_t slaveaddress, uint8_t *regaddr, size_t addrlen, void *data, size_t datalen,uint32_t wait_times);


/**
 * @brief:
 *      write data to i2c
 *
 * @param:
 *      \i2c_no [in]         - i2c channel number
 *      \slaveaddress [in]   - the slave address
 *      \regaddr  [in]       - the address of register
 *      \addrlen  [in]       - the length of regaddr 
 *      \data     [in]       - the data write to i2c bus
 *      \datalen  [in]       - the length of the data write
 *    
 * @return:
 *      i2c write Result, 0 for success,-1 for failure
 */
int HELIOS_I2C_Write(Helios_I2CEnum i2c_no, uint8_t slaveaddress, uint8_t *regaddr,size_t addrlen,void *data, size_t datalen);


#ifdef __cplusplus
} /*"C" */
#endif

#endif




