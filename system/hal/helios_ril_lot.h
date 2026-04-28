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
/*****************************************************************************
 *
 * Filename:
 * ---------
 *   helios_ril_lot.c
 *
 * Project:
 * --------
 *   QuecOpen
 *
 * Description:
 * ------------
 *   The module implements lot related APIs.
 *
 * Author:burols.wang
 * -------
 * -------
 *
 *============================================================================
 *             HISTORY
 *----------------------------------------------------------------------------
 *version 0.1
 ****************************************************************************/
#ifndef __RIL_LOT_H__
#define __RIL_LOT_H__
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define MAX_IP_LEN      16
#define MAX_PSK_LEN     64
#define MAX_PORT_LEN    5

typedef struct __ST_OC_INFO{
    uint8_t     ip[MAX_IP_LEN];
    uint8_t     psk[MAX_PSK_LEN];
    uint8_t     port[MAX_PORT_LEN];
}Helios_NB_OC_Info;

/*note :user this struct must malloc memery from Helios_NB_OC_databuffer.buffer
* when don't use this struct must free the memery Helios_NB_OC_databuffer.buffer
*/
typedef struct __ST_OC_BUF{
    uint32_t    len;
    uint32_t    capacity;
    uint8_t     *buffer;
}Helios_NB_OC_databuffer;
/*****************************************************************************
 * function name :Helios_OC_Set_Defalut
 * paragram:
 *          str_ip      [in]        [char *]       [MAX_LEN 16]      [not null]
 *          str_port    [in]        [char *]       [MAX_LEN 5]       [not null]
 *          str_psk     [in]        [char *]       [MAX_LEN 256]     [not NULL]
 * description：
 *          str_ip  :   Internet of things platform ip address.
 *          str_port:   Internet of things platform port.
 *          str_psk :   PSK code of IOT platform equipment
 * This function sets the default IP address and port and PSK code required for OC connection
 * return:
 *          int :  -1-failed
 *                  0-success
 * ***************************************************************************/
int Helios_OC_Set_Defalut(uint8_t *str_ip,uint8_t *str_port,uint8_t *str_psk);

/*****************************************************************************
 * function name :Helios_OC_Connect
 * paragram:
 *          str_ip      [in]        [char *]       [MAX_LEN 16]      [not null]
 *          str_port    [in]        [char *]       [MAX_LEN 5]       [not null]
 *          str_psk     [in]        [char *]       [MAX_LEN 256]     [not null]
 *          st_oc_info  [in]        [ST_OC_INFO *] []                [null]
 * description：
 *          str_ip  :   Internet of things platform ip address.
 *          str_port:   Internet of things platform port.
 *          str_psk :   PSK code of IOT platform equipment
 * This function initiates an OC connection and returns 0 on success or an error code on failure
 * return:
 *          0 - success
 *          other - failed
 * ***************************************************************************/
int Helios_OC_Connect(uint8_t *str_ip,uint8_t *str_port,uint8_t *str_psk,Helios_NB_OC_Info * st_oc_info);

/*****************************************************************************
 * function name :Helios_OC_DisConnect
 * paragram:
 *          void
 * description：disconnect the OC connection 
 * return:
 *          0 - success
 *          other - failed
 * ***************************************************************************/
int Helios_OC_DisConnect(void);

/*****************************************************************************
 * function name :Helios_OC_SendData
 * paragram:
 *          len      [in]        [u8]       [MAX_LEN 16]      [not null]
 *          data     [in]        [u8 *]     [MAX_LEN 512]     [not null]
 *          type     [in]        [u8]       [MAX_LEN 102]     [not null]
 * description：Send data to the Internet of Things
 * return:
 *          0 - success
 *          other - failed
 * ***************************************************************************/
int Helios_OC_SendData(uint32_t len,uint8_t *data,uint8_t type);

/*****************************************************************************
 * function name :Helios_OC_RecvData
 * paragram:
 *          data     [out]        [u8 *]     [MAX_LEN 512]     [not null]
 * description：When the received data mode is changed to buffer mode, the data
 * distributed by the platform will be cached in the local buffer for reading 
 * with this function.
 * return:
 *          0 - success
 *          other - failed
 * ***************************************************************************/
int Helios_OC_RecvData(Helios_NB_OC_databuffer *data);

#endif