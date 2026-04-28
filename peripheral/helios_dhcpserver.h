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

#ifndef _HELIOS_DHCPSERVER_H_
#define _HELIOS_DHCPSERVER_H_

#include <stdint.h>

#define DHCPS_BASE_IP (16)
#define DHCPS_MAX_IP (8)
#define CLIENT_USER_NAME_MAX_LEN 64

typedef struct {
    char mac[18];
    char ip[16];
    char cname[CLIENT_USER_NAME_MAX_LEN+1]; // client host name
} dhcp_server_client_helios_info_t;

typedef struct {
    u8_t count;
    dhcp_server_client_helios_info_t info[DHCPS_MAX_IP];
} dhcp_server_client_helios_t;

void Helios_DhcpServer_Init(char *ip_str, char *mask_str);

void Helios_DhcpServer_Deinit();

int Helios_DhcpServer_Start(void);

int Helios_DhcpServer_Get_Client_Info(dhcp_server_client_helios_t *client_info);

int Helios_DhcpServer_Set_Addrpool(char *start_addr, char *end_addr);

#endif


