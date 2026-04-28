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

#ifndef _HELIOS_WLAN_H
#define _HELIOS_WLAN_H

 /*-----------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define HELIOS_WIFI_SSID_MAX_LEN    (32)
#define HELIOS_WIFI_PWD_MAX_LEN     (63)
#define HELIOS_WIFI_MAX_CHANNEL     (13)
#if defined(PLAT_ECR6600)
#define HELIOS_WIFI_MAX_CLIENTS     (4)
void Helios_Active_Status(void);
#elif defined(PLAT_aic8800m40)
#define HELIOS_WIFI_MAX_CLIENTS     (10)
#else
#define HELIOS_WIFI_MAX_CLIENTS     (0)
#endif

typedef enum {
    HELIOS_WLAN_EVENT_RF_WAKEUP = 3001,
    HELIOS_WLAN_EVENT_RF_SLEEP,

    HELIOS_WLAN_EVENT_SCAN_DONE = 3101,
    HELIOS_WLAN_EVENT_SCAN_FAILED,

    HELIOS_WLAN_EVENT_AP_START_SUCCEED = 3201,
    HELIOS_WLAN_EVENT_AP_START_FAILED,
    HELIOS_WLAN_EVENT_STA_CONNECTED,
    HELIOS_WLAN_EVENT_STA_DISCONNECTED,
    HELIOS_WLAN_EVENT_STA_IP_ASSIGNED,
    HELIOS_WLAN_EVENT_AP_STOP,

    HELIOS_WLAN_EVENT_STA_START_CONN = 3301,
    HELIOS_WLAN_EVENT_CONN_SUCCEED,
    HELIOS_WLAN_EVENT_CONN_FAILED,
    HELIOS_WLAN_EVENT_CONN_LOST,
    HELIOS_WLAN_EVENT_GOT_IP,
    HELIOS_WLAN_EVENT_LOST_IP,

    HELIOS_WLAN_EVENT_NETCFG_START_SUCCEED = 3401,
    HELIOS_WLAN_EVENT_NETCFG_START_FAILED,
    HELIOS_WLAN_EVENT_NETCFG_STOP_SUCCEED,
    HELIOS_WLAN_EVENT_NETCFG_STOP_FAILED,
    HELIOS_WLAN_EVENT_NETCFG_STAT_CLIENT_CONNECT,
    HELIOS_WLAN_EVENT_NETCFG_GOT_KEY,
    HELIOS_WLAN_EVENT_NETCFG_TIMEOUT,
    HELIOS_WLAN_EVENT_MAX
} Helios_Wlan_Event_e;

typedef enum {
    HELIOS_WLAN_ERROR_OK = 2000,
    HELIOS_WLAN_ERROR_NO_MEM,
    HELIOS_WLAN_ERROR_PARAM_INVALID,
    HELIOS_WLAN_ERROR_WIFI_BUSY,
    HELIOS_WLAN_ERROR_NOT_SUPPORT,
    HELIOS_WLAN_ERROR_WIFI_ALREADY_CUR_IF,
    HELIOS_WLAN_ERROR_INTERNAL,
    HELIOS_WLAN_ERROR_WOULDCONNECT,
    HELIOS_WLAN_ERROR_NO_AP_FOUND,
    HELIOS_WLAN_ERROR_PWD_WRONG,
    HELIOS_WLAN_ERROR_AUTHMODE_WRONG,
    HELIOS_WLAN_ERROR_CHANNEL_INVALID,
    HELIOS_WLAN_ERROR_NONAUTH,
    HELIOS_WLAN_ERROR_NONASSOC,
    HELIOS_WLAN_ERROR_HANDSHAKE_TIMEOUT,
    HELIOS_WLAN_ERROR_WOULDBLOCK,
    HELIOS_WLAN_ERROR_NOT_ACTIVE,
    HELIOS_WLAN_ERROR_NO_STA_IF,
    HELIOS_WLAN_ERROR_UNCONNECTED_AP,
    HELIOS_WLAN_ERROR_AP_UNSTART,
    HELIOS_WLAN_ERROR_NO_AP_IF,
    HELIOS_WLAN_ERROR_NO_SCAN_MODE,
    HELIOS_WLAN_ERROR_NO_AP_STA_IF,
    HELIOS_WLAN_ERROR_TIMEOUT,
    HELIOS_WLAN_ERROR_NETCFG_BUSY,
    HELIOS_WLAN_ERROR_NETCFG_SOFTAP_START,
    HELIOS_WLAN_ERROR_NETCFG_SOCKET_CREATE,
    HELIOS_WLAN_ERROR_NETCFG_HTTP_SERVER_CREATE,
    HELIOS_WLAN_ERROR_NETCFG_BLE_SERVER_CREATE,
    HELIOS_WLAN_ERROR_NETCFG_GATT_SERVER_CREATE,
    HELIOS_WLAN_ERROR_NETCFG_NOT_IN_NETCFG,
    HELIOS_WLAN_ERROR_NETCFG_HTTP_SERVER_CLOSE,
    HELIOS_WLAN_ERROR_NETCFG_SOCKET_CLOSE,
    HELIOS_WLAN_ERROR_NETCFG_SOFTAP_CLOSE,
    HELIOS_WLAN_ERROR_NETCFG_BLE_SERVER_CLOSE,
    HELIOS_WLAN_ERROR_STA_KICKED_OFFLINE_BY_AP,
    HELIOS_WLAN_ERROR_SER_DISCONNECT,
    HELIOS_WLAN_ERROR_AUTHMODE_CHANGED,
    HELIOS_WLAN_ERROR_IFMODE_CHANGED,
    HELIOS_WLAN_ERROR_DHCP_LEASE_EXPIRED,
    HELIOS_WLAN_ERROR_INACTIVE_TIMEOUT,
    HELIOS_WLAN_ERROR_IP_DEL_ARTIFICIALLY,
    HELIOS_WLAN_ERROR_MAX
}Helios_Wlan_Error_e;

typedef enum {
    HELIOS_WLAN_STATUS_RF_NOT_ACTIVATED = 1000,
    HELIOS_WLAN_STATUS_RF_ACTIVATED,
    HELIOS_WLAN_STATUS_RF_SLEEP,
    HELIOS_WLAN_STATUS_RF_WAKEUP,
    HELIOS_WLAN_STATUS_AP_IDLE,
    HELIOS_WLAN_STATUS_AP_START,
    HELIOS_WLAN_STATUS_AP_STACONNECTED,
    HELIOS_WLAN_STATUS_STA_IDLE,
    HELIOS_WLAN_STATUS_STA_SCANNING,
    HELIOS_WLAN_STATUS_STA_CONNECTING,
    HELIOS_WLAN_STATUS_STA_CONNECTED,
    HELIOS_WLAN_STATUS_STA_GOT_IP,
    HELIOS_WLAN_STATUS_STA_LOST_IP,
    HELIOS_WLAN_STATUS_NETCFG_NOT_INTO,
    HELIOS_WLAN_STATUS_NETCFG_INTO,
    HELIOS_WLAN_STATUS_NETCFG_GOT_KEY,
    HELIOS_WLAN_STATUS_MAX,
}Helios_Wlan_Status_e;

typedef enum {
    HELIOS_WLAN_MODE_NONE = 0,
    HELIOS_WLAN_MODE_AP,
    HELIOS_WLAN_MODE_STA,
    HELIOS_WLAN_MODE_AP_STA,
    HELIOS_WLAN_MODE_MAX,
}Helios_Wlan_Mode_e;

typedef enum {
    HELIOS_WLAN_SOFTAP_IF,
    HELIOS_WLAN_STATION_IF,
    HELIOS_WLAN_MAX_IF,
}Helios_Wlan_Interface_e;

typedef struct {
    char    ip[16];
    char    netmask[16];
    char    gateway[16];
    char    dns_server[2][16];
} Helios_Wlan_Ipconfig_t;

typedef struct {
    uint32_t status;          /**< status of scanning APs */
    uint8_t  number;
    uint8_t  scan_id;
} Helios_Wlan_Event_STA_Scan_Done_t;

typedef struct {
    int8_t rssi;                /**< Signal strength of the current connected AP */
    uint8_t ssid[HELIOS_WIFI_SSID_MAX_LEN + 1]; /**< SSID of the current connected wlan */
    uint8_t pwd[HELIOS_WIFI_PWD_MAX_LEN + 1];
    uint8_t bssid[6];                /**< BSSID of the current connected wlan */
    uint8_t channel;                 /**< Channel of the current connected wlan */
    uint8_t auth;
    uint8_t cipher;
} Helios_Wlan_Event_STA_Connected_t;

typedef struct {
    uint8_t ssid[HELIOS_WIFI_SSID_MAX_LEN + 1];         /**< SSID of disconnected AP */
    uint8_t ssid_len;                        /**< SSID length of disconnected AP */
    uint8_t bssid[6];                        /**< BSSID of disconnected AP */
    uint8_t reason;                          /**< reason of disconnection */
} Helios_Wlan_Event_STA_Disconnected_t;

typedef struct {
    Helios_Wlan_Mode_e old_mode;         /**< the old auth mode of AP */
    Helios_Wlan_Mode_e new_mode;         /**< the new auth mode of AP */
} Helios_Wlan_Event_STA_Authmode_Change_t;

typedef struct {
    Helios_Wlan_Ipconfig_t ip_info;
    uint8_t ip_changed;
} Helios_Wlan_Event_STA_Got_IP_t;

typedef struct {
    uint8_t mac[6];           /**< MAC address of the station connected to soft-AP */
    uint8_t aid;              /**< the aid that soft-AP gives to the station connected to  */
} Helios_Wlan_Event_AP_StationConnected_t;

typedef struct {
    char ip[16];
    uint8_t mac[6];
    uint8_t aid;
}Helios_Wlan_Event_AP_StationIPAssigned_t;

typedef struct {
    char ip[16];
    uint8_t mac[6];
    uint8_t aid;
} Helios_Wlan_Event_AP_StationDisconnected_t;

typedef struct {
    uint8_t in_out;           /**< sta enter(1)/exit(0) gtk rekey */
}Helios_Wlan_Event_STA_Gtk_Rekey_t;

typedef struct {
    uint8_t ssid[HELIOS_WIFI_SSID_MAX_LEN + 1]; /**< SSID of the current connected wlan */
    uint8_t password[HELIOS_WIFI_PWD_MAX_LEN + 1];
}Helios_Wlan_Event_Netcfg_Got_Key_t;

typedef union {
    Helios_Wlan_Event_STA_Connected_t               connected;          /**< station connected to AP */
    Helios_Wlan_Event_STA_Disconnected_t            disconnected;       /**< station disconnected to AP */
    Helios_Wlan_Event_STA_Scan_Done_t               scan_done;          /**< station scan (APs) done */
    Helios_Wlan_Event_STA_Authmode_Change_t         auth_change;        /**< the auth mode of AP station connected to changed */
    Helios_Wlan_Event_STA_Got_IP_t                  got_ip;             /**< station got IP, first time got IP or when IP is changed */
    Helios_Wlan_Event_AP_StationConnected_t         sta_connected;      /**< a station connected to soft-AP */
    Helios_Wlan_Event_AP_StationIPAssigned_t        sta_ipassigned;
    Helios_Wlan_Event_AP_StationDisconnected_t      sta_disconnected;   /**< a station disconnected to soft-AP */
    Helios_Wlan_Event_STA_Gtk_Rekey_t               in_out_rekey;       /**< station enter/exit gtk rekey */
    Helios_Wlan_Event_Netcfg_Got_Key_t              netcfg_got_key;
} Helios_Wlan_Event_Info_t;

typedef struct {
    uint32_t                    type;
    Helios_Wlan_Event_e         id;      /**< event ID */
    Helios_Wlan_Event_Info_t    info;    /**< event information */
} Helios_Wlan_Event_t;

typedef int (*Helios_WlanEventCallback)(Helios_Wlan_Event_t* event);

typedef struct {
    uint8_t ssid[HELIOS_WIFI_SSID_MAX_LEN + 1];
    uint8_t ssid_len;
    uint8_t bssid[6];
    uint8_t channel;
    int8_t rssi;
    uint8_t auth;
    uint8_t hidden;
} Helios_Wlan_Scan_Result_t;

typedef enum {
    HELIOS_WLAN_AUTH_OPEN = 0,      /**< authenticate mode : open */
    HELIOS_WLAN_AUTH_WEP,           /**< authenticate mode : WEP */
    HELIOS_WLAN_AUTH_WPA_PSK,       /**< authenticate mode : WPA_PSK */
    HELIOS_WLAN_AUTH_WPA2_PSK,      /**< authenticate mode : WPA2_PSK */
    HELIOS_WLAN_AUTH_WPA_WPA2_PSK,  /**< authenticate mode : WPA_WPA2_PSK */
    HELIOS_WLAN_AUTH_MAX
} Helios_Wlan_Auth_Mode_e;

typedef enum {
    HELIOS_WLAN_CIPHER_NONE = 0,
    HELIOS_WLAN_CIPHER_WEP40,
    HELIOS_WLAN_CIPHER_WEP104,
    HELIOS_WLAN_CIPHER_TKIP,
    HELIOS_WLAN_CIPHER_CCMP,
} Helios_Wlan_Cipher_Mode_e;

typedef struct {
    unsigned char    ssid[HELIOS_WIFI_SSID_MAX_LEN + 1];
    char             password[HELIOS_WIFI_PWD_MAX_LEN + 1];
    uint8_t          channel;  //in concurrent mode(softap+sta), if sta is connected, will ignore this configure here, to take sta's channel.
    Helios_Wlan_Auth_Mode_e authmode;
    uint8_t 		 max_connect;
    uint8_t			 hidden_ssid;
} Helios_Wlan_Softap_Config_t;

typedef struct {
    unsigned char   ssid[HELIOS_WIFI_SSID_MAX_LEN + 1]; /**< SSID of target AP*/
    char     password[HELIOS_WIFI_PWD_MAX_LEN + 1];    /**< password of target AP*/
    uint8_t  channel;
    uint8_t  bssid[6];
} Helios_Wlan_Station_Config_t;

typedef struct {
    Helios_Wlan_Mode_e wifi_mode; /**< DHCP mode: @ref wlanInterfaceTypedef.*/
    uint8_t block;
    uint32_t timeout;                   /* timeout time */
    Helios_Wlan_Softap_Config_t ap;              /* configuration of AP */
    Helios_Wlan_Station_Config_t sta;            /* configuration of STA */
} Helios_Wlan_Init_config_t;

typedef struct {
    uint8_t state;              /**< The link to wlan is established or not, 0: disconnected, 1: connected. */
    int8_t rssi;                /**< Signal strength of the current connected AP */
    uint8_t ssid[HELIOS_WIFI_SSID_MAX_LEN + 1]; /**< SSID of the current connected wlan */
    uint8_t pwd[HELIOS_WIFI_PWD_MAX_LEN + 1];
    uint8_t bssid[6];                /**< BSSID of the current connected wlan */
    uint8_t channel;                 /**< Channel of the current connected wlan */
    uint8_t auth;
    uint8_t cipher;
} Helios_Wlan_Station_Status_t;

typedef struct {
    uint8_t* ssid;               /* SSID of AP */
    uint8_t* bssid;              /* MAC address of AP */
    uint8_t  channel;            /* channel, scan the specific channel */
    uint8_t  passive;            /* passive slave or not */
    uint8_t  max_item;           /* max scan item */
    int32_t scan_time;          /* scan time per channel, units: millisecond */
} Helios_Wlan_Scan_Config_t;

typedef struct {
    uint8_t mac[6];
} Helios_Wlan_Softap_Station_List_t;

typedef enum {
    HELIOS_WLAN_NETCFG_TYPE_SMARTCONFIG = 0,
    HELIOS_WLAN_NETCFG_TYPE_WEBCONFIG,
    HELIOS_WLAN_NETCFG_TYPE_BLECONFIG,
    HELIOS_WLAN_NETCFG_TYPE_MAX
}Helios_Wlan_Netcfg_Type_e;

typedef struct {
    uint8_t enable;
    uint8_t block;
    Helios_Wlan_Netcfg_Type_e type;
    uint32_t timeout;
}Helios_Wlan_Netcfg_Config_t;

typedef struct {
    uint8_t ssid[HELIOS_WIFI_SSID_MAX_LEN + 1]; /**< SSID of the current connected wlan */
    uint8_t pwd[HELIOS_WIFI_PWD_MAX_LEN + 1];
}Helios_Wlan_Netcfg_Result_t;

typedef struct {
    uint8_t ssid[HELIOS_WIFI_SSID_MAX_LEN + 1]; /**< SSID of the current connected wlan */
    uint8_t pwd[HELIOS_WIFI_PWD_MAX_LEN + 1];
    Helios_Wlan_Error_e error_code;
}Helios_Wlan_Netcfg_Event_Msg_t;

typedef struct {
    Helios_Wlan_Netcfg_Type_e type;
    Helios_Wlan_Event_e id;
    Helios_Wlan_Netcfg_Event_Msg_t msg;
}Helios_Wlan_Netcfg_Event_Info_t;

int Helios_Wlan_isActive(Helios_Wlan_Interface_e vif);

int Helios_Wlan_Start(Helios_Wlan_Init_config_t* wlan_config);

int Helios_Wlan_Stop(Helios_Wlan_Mode_e mode);

int Helios_Wlan_Station_Get_AP_Info(Helios_Wlan_Station_Status_t* station_status);

Helios_Wlan_Status_e Helios_Wlan_Get_Status(Helios_Wlan_Interface_e vif);

Helios_Wlan_Status_e Helios_Wlan_Get_Netcfg_Status(void);

int Helios_Wlan_Softap_Get_Station_List(Helios_Wlan_Softap_Station_List_t* sta_list, uint32_t* num);

/**
 * [0] Non blocking
 * [1] block
*/
int Helios_Wlan_Scan_Start(uint8_t block, Helios_Wlan_Scan_Config_t* config);

int Helios_Wlan_Scan_Num(void);

int Helios_Wlan_Scan_AP_Result(uint8_t index, Helios_Wlan_Scan_Result_t* ap_info);

int Helios_Wlan_Set_IPConfig(Helios_Wlan_Interface_e vif, Helios_Wlan_Ipconfig_t* ipconfig);

int Helios_Wlan_Get_IPConfig(Helios_Wlan_Interface_e vif, Helios_Wlan_Ipconfig_t* ipconfig);

int Helios_Wlan_Get_Channel(Helios_Wlan_Interface_e vif);

int Helios_Wlan_AP_Add_Station_to_Blacklist(uint8_t* sta_mac);

int Helios_Wlan_AP_Remove_Station_from_Blacklist(uint8_t* sta_mac);

int Helios_Wlan_AP_Get_Station_MAC(uint32_t ip, uint8_t* sta_mac);

int Helios_Wlan_AP_Get_Station_IP(uint32_t* ip, uint8_t* sta_mac);

int Helios_Wlan_AP_Get_Station_AID(uint8_t* aid, uint8_t* sta_mac);

int Helios_Wlan_Set_MAC_Addr(Helios_Wlan_Interface_e vif, uint8_t* mac);

int Helios_Wlan_Get_MAC_Addr(Helios_Wlan_Interface_e vif, uint8_t* mac);

int Helios_Wlan_Set_Country_Code(const char* country_code);

int Helios_Wlan_Get_Country_Code(char* country_code);

int Helios_Wlan_Set_Event_Callback(Helios_WlanEventCallback cb);

int Helios_Wlan_Del_Event_Callback(Helios_WlanEventCallback cb);

int Helios_Wlan_Netcfg_Start(Helios_Wlan_Netcfg_Config_t config, Helios_Wlan_Netcfg_Result_t* result);

int Helios_Wlan_Netcfg_Stop(Helios_Wlan_Netcfg_Config_t config);

#endif
