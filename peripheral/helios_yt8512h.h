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
} yt8512h_ethnetif_ipconfig_t;



int Helios_YT8512H_NICRegister(uint8_t mac[6], char *ip_str, char *mask_str, char *gw_str);

int Helios_YT8512H_NICSetAddr(char *ip_str, char *mask_str, char *gw_str);

int Helios_YT8512H_NICSetDNS(char *pri_str, char *sec_str);

int Helios_YT8512H_NICSetUp(void);

int Helios_YT8512H_NICSetDown(void);

int Helios_YT8512H_NICDHCP(void);

void Helios_YT8512H_IPConfig(yt8512h_ethnetif_ipconfig_t *ipconfig);

int Helios_YT8512H_SetDefaultNetworkCard(char *ip);

void Helios_YT8512H_Destroy(void);

void Helios_YT8512H_Status(int *status);

void Helios_YT8512H_TX_RX_Speed(u32_t *tx, u32_t *rx);

int Helios_YT8512H_Node_List(int *num, u32_t *ip, u8_t mac[][6], u32_t *ticks);

int Helios_YT8512H_Pool_Config(int pool_start, int pool_end, int lease_time);

void Helios_YT8512H_AutoSleep(int enable);

uint16_t Helios_YT8512H_RGMII_DeInit(void);

#endif


