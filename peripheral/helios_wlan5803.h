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
 @file	helios_wlan.h
 @brief	Data type definition for wlan.
*/
/**************************************************************************
===========================================================================
Copyright (c) 2021 Quectel Wireless Solution, Co., Ltd.All Rights Reserved.
Quectel Wireless Solution Proprietary and Confidential.
===========================================================================

						EDIT HISTORY FOR FILE
This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

WHEN		WHO			WHAT,WHERE,WHY
----------  ---------   ---------------------------------------------------
2023/03/28  Francis.qin	Create.
**************************************************************************/

#ifndef _HELIOS_WLAN5803_H
#define _HELIOS_WLAN5803_H


#define HELIOS_WLAN_AP_MODE  0
#define HELIOS_WLAN_STA_MODE 1

#define HELIOS_WLAN_SHUT_DOWN 0
#define HELIOS_WLAN_TURN_ON   1

#define HELIOS_MAX_SSID     32
#define HELIOS_MAX_PASSWORD 64
#define HELIOS_MIN_PASSWORD 8
#define HELIOS_MAC_LEN      6

#define MAX_DEVICES 10

/* Definitions for error constants. */
#define HELIOS_WLAN_5803W_OK          	 0     /*!< HELIOS 5803W value indicating success (no error) */
#define HELIOS_WLAN_5803W_FAIL        	 -1    /*!< Generic 5803 err code indicating failure */

#define HELIOS_5803W_INVALID_ARG         101   /*!< Invalid argument */
#define HELIOS_5803W_NOT_SUPPORTED       102   /*!< Operation or feature not supported */


typedef enum 
{
	HELIOS_5803W_AUTH_OPEN_SHA = 0,
	HELIOS_5803W_AUTH_OPEN,
	HELIOS_5803W_AUTH_SHA,  //NOT SUPPORT
	HELIOS_5803W_AUTH_WPA,
	HELIOS_5803W_AUTH_WPA2,
	HELIOS_5803W_AUTH_WPA_WPA2
}Helios_WLAN_5803W_AUTH_TYPE;

typedef enum 
{
	HELIOS_5803W_ENC_NONE = 0,
	HELIOS_5803W_ENC_WEP,  //NOT SUPPORT 
	HELIOS_5803W_ENC_TKIP,
	HELIOS_5803W_ENC_AES,
	HELIOS_5803W_ENC_TKIP_AES,
}Helios_WLAN_5803W_ENCMODE_TYPE;

typedef enum 
{
	HELIOS_5803W_5G = 1, //NOT SUPPORT
	HELIOS_5803W_2_4G_B,
	HELIOS_5803W_2_4G_B_G,  
	HELIOS_5803W_2_4G_B_G_N,
}Helios_WLAN_5803W_CHANNEL_MODE_TYPE;

typedef struct 
{
	bool     enable;                 //EN (0-1)
	uint8_t  mode;                   //M  (0:AP 1:STA)
	uint8_t  secmode;                //AP (0:OPEN 1 2  3:WPA 4:WPA2 5:WPA/WPA2)
	uint8_t  encmode;                //AP (0:None 1:WEP 2:TKIP 3:AES 4:TKIP-AES)
	uint8_t  chan_mode;              //AP (0:5G 1:2.4G b 2:2.4G b/g 3:2.4G b/g/n)
	uint8_t  channel;	               //AP (2.4G(1-13) 5G(NOT SUPPORT))
	uint8_t  b40acs;                 //AP (2.4G B40 ACS)
	char   ssid[HELIOS_MAX_SSID+1];    //AP 
	char   pass[HELIOS_MAX_PASSWORD+1]; //AP
	char   mac[HELIOS_MAC_LEN+1];
}Helios_WLAN_5803W_CFG   ;


typedef struct {
    uint64_t  tick;
	uint64_t  cum_time;
    char 	device_mac[18];
    char 	device_ip[16];
} Helios_WLAN_5803W_DeviceInfo_t;


int Helios_WLAN_5803W_ENABLE(int enable);

int Helios_WLAN_5803W_GetStatus(int *enable);

/*
 *	@param:
 *		ssid len <= 32
 */
int Helios_WLAN_5803W_AP_SetSSID(char *ssid);

int Helios_WLAN_5803W_AP_GetSSID(char ssid[HELIOS_MAX_SSID+1]);

/*
 *	@param:
 *		OPEN/SHA  = 0,
 *		OPEN	  = 1,
 *		SHA		  = 2,
 *		WPA		  = 3,
 *		WPA2	  = 4;
 *		WPA/WPA2  = 5,
 */
int Helios_WLAN_5803W_AP_GetAuth(uint8_t *auth);

/*
 *	@param:
 *		UNENCRYPTED = 0,
 *		WEP	  		= 1, //SET NOT SUPPORT
 *		TKIP	    = 2,
 *		AES	  		= 3;
 *		TKIP/AES    = 4,
 */
int Helios_WLAN_5803W_AP_GetSecurity(uint8_t *security);

/*
 *	@param:
 *		8 < wifikey len < 64
 */
int Helios_WLAN_5803W_AP_GetPassword(char *wifikey);

/*
 *	@param:
 *		802.11 5G	  	   = 1, //NOT SUPPORT ASR5803
 *		802.11 2.4G b	   = 2,
 *		802.11 2.4G b/g	   = 3,
 *		802.11 2.4G b/g/n  = 4,
 */
int Helios_WLAN_5803W_AP_GetChannelMode(uint8_t *chanmode);

/*
 *	@param:
 *		Automatic	  	   = 0,
 *		Specify a channel  = (1~13),
 */
int Helios_WLAN_5803W_AP_GetChannel(uint8_t *channel);

/*
 *	@param:
 *		Close adaptive  = 0,
 *		Open adaptive   = 1,
 */
int Helios_WLAN_5803W_AP_Getb40acsStatus(uint8_t *enable);

int Helios_WLAN_5803W_AP_GetMAC(char *mac);

void Helios_WLAN_5803W_IsConnected(uint8_t *type);

int Helios_WLAN_5803W_AP_SetAuthConfig(uint8_t auth, uint8_t security, char* wifikey);

int Helios_WLAN_5803W_AP_SetChannelConfig(uint8_t mode, uint8_t channel, uint8_t b40acs);

void Helios_WLAN_5803W_Set_LDO_EN_Pin(int ldo_en_pin);

void Helios_WLAN_5803W_Set_ResetPin(int reset_pin);

void Helios_WLAN_5803W_Set_HostWakeWlanPin(int H_wake_W_pin);

void Helios_WLAN_5803W_Set_WlanWakeHostPin(int W_wake_H_pin);

void Helios_WLAN_5803W_InitDriver(void);

void Helios_WLAN_5803W_Get_DataSpeed(uint32_t *rx, uint32_t *tx);

void Helios_WLAN_5803W_Get_ConnectionList(int *output_num, Helios_WLAN_5803W_DeviceInfo_t **output_list);

int Helios_WLAN_5803W_SetMAC(char *mac);

int Helios_WLAN_5803W_AP_SetAllCfg(Helios_WLAN_5803W_CFG *wifi_cfg);

int Helios_WLAN_5803W_SetDefaultNetworkCard(char *ip);

#if 0

int Helios_WLAN_5803W_AP_SetAuth(uint8_t auth);

int Helios_WLAN_5803W_AP_SetSecurity(uint8_t security);

int Helios_WLAN_5803W_AP_SetPassword(char *wifikey);

int Helios_WLAN_5803W_AP_SetChannelMode(uint8_t chanmode);

int Helios_WLAN_5803W_AP_SetChannel(uint8_t channel);

int Helios_WLAN_5803W_AP_b40acs_enable(uint8_t enable);

int Helios_WLAN_5803W_AP_GetAuthConfig(uint8_t* auth, uint8_t* security, char* wifikey);

int Helios_WLAN_5803W_AP_GetChannelConfig(uint8_t* mode, uint8_t* channel, uint8_t* b40acs);

#endif



#endif
