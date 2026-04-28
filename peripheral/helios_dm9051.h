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

#ifndef _HELIOS_DM9051_H_
#define _HELIOS_DM9051_H_

#include <stdint.h>
#include "ip4_addr.h"

typedef struct
{
    uint8_t *mac;
    char *hostname;
    struct
    {
        int iptype;
        ip_addr_t ipaddr;
        ip_addr_t netmask;
        ip_addr_t gw;
        ip_addr_t dns_server[2];
    } ipv4_info;
} dm_ethnetif_ipconfig_t;

typedef enum  {
    DM_ETHNETIF_NODE = 0,  // 网卡终端模式(默认模式)
    DM_ETHNETIF_GATEWAY,   // 网卡网关模式
} dm_ethnetif_work_mode;

void Helios_DM9051_NICSetSPI(int port, int cs);

void Helios_DM9051_NICSetEINTPin(int eint_pin);

void Helios_DM9051_NICSetResetPin(int reset_pin);

int Helios_DM9051_NICRegister(uint8_t mac[6], char *ip_str, char *mask_str, char *gw_str, dm_ethnetif_work_mode mode);

int Helios_DM9051_NICSetAddr(char *ip_str, char *mask_str, char *gw_str);

int Helios_DM9051_NICSetDNS(char *pri_str, char *sec_str);

int Helios_DM9051_NICSetUp(void);

int Helios_DM9051_NICSetDown(void);

int Helios_DM9051_NICDHCP(void);

void Helios_DM9051_IPConfig(dm_ethnetif_ipconfig_t *ipconfig);

void Helios_DM9051_Destroy(void);

int Helios_DM9051_NICSetDefaultNetworkCard(char *ip);


#endif

