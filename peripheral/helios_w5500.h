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

#ifndef _HELIOS_W5500_H_
#define _HELIOS_W5500_H_

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
} wz_ethnetif_ipconfig_t;

typedef enum  {
	WZ_ETHNETIF_NODE = 0,  // 网卡终端模式
	WZ_ETHNETIF_GATEWAY,   // 网卡网关模式
} wz_ethnetif_work_mode;


#if defined(PLAT_ASR_1606)
    void Helios_W5500_NICSetSPI(int port, int cs,int group);
#else 
    void Helios_W5500_NICSetSPI(int port, int cs);
#endif
void Helios_W5500_NICSetEINTPin(int eint_pin);

void Helios_W5500_NICSetResetPin(int reset_pin);

int Helios_W5500_NICRegister(uint8_t mac[6], char *ip_str, char *mask_str, char *gw_str, wz_ethnetif_work_mode mode);

int Helios_W5500_NICSetAddr(char *ip_str, char *mask_str, char *gw_str);

int Helios_W5500_NICSetDNS(char *pri_str, char *sec_str);

int Helios_W5500_NICSetUp(void);

int Helios_W5500_NICSetDown(void);

int Helios_W5500_NICDHCP(void);

void Helios_W5500_IPConfig(wz_ethnetif_ipconfig_t *ipconfig);

int Helios_W5500_SetDefaultNetworkCard(char *ip);

void Helios_W5500_Destroy(void);

void Helios_W5500_Status(int *status);

#endif


