 /**
 @file	helios_ble.h
 @brief	Data type definition for BLE.
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
2021/04/22  Kingka.Wu	Create.
**************************************************************************/

#ifndef _HELIOS_BLE_H
#define _HELIOS_BLE_H

#ifdef __cplusplus
extern "C" {
#endif

#define HELIOS_BT_DEV_NAME_SIZE	41
#define HELIOS_BT_SPP_SEND_SIZE	128

#define HELIOS_BT_BLE_NAME_MAX_SIZE   22
#define HELIOS_BLE_ADV_SCAN_DATA_SIZE  31
#define HELIOS_BLE_LONG_UUID_SIZE    16

#define HELIOS_SMS_NEW_MSG_IND	1
#define HELIOS_BT_MAC_ADDRESS_SIZE 6

typedef void (*Helios_BT_Callback)(void *ind_msg_buf, void *ctx);


typedef enum{
//bt
    HELIOS_BT_START_STATUS_IND = 0,     //bt/ble start
    HELIOS_BT_STOP_STATUS_IND=1,                                    //bt/ble stop
    HELIOS_BT_VISIBILE_IND=2,                                       //
    HELIOS_BT_HIDDEN_IND=3,
    HELIOS_BT_SET_LOCALNAME_IND=4,
    HELIOS_BT_SET_LOCALADDR_IND=5,
    HELIOS_BT_INQURY_IND=6,
    HELIOS_BT_INQURY_END_IND=7,
    HELIOS_BT_CANCEL_INQURY_IND=8,
    HELIOS_BT_BOND_IND=9,
    HELIOS_BT_CANCELBOND_IND=10,
    HELIOS_BT_CONNECT_IND=11,
    HELIOS_BT_DISCONNECT_IND=12,
    HELIOS_BT_SPP_SEND_IND=13,
    HELIOS_BT_SPP_RECV_IND=14,

    HELIOS_BT_HFP_CONNECTION_IND=15,
//ble
    //all:server and client can recieve this event
    //server:only server can recieve this event
    //client:only client can recieve this event
    HELIOS_BLE_CONNECT_IND=16,       //all:ble connect
    HELIOS_BLE_DISCONNECT_IND=17,                                    //all:ble disconnect
    HELIOS_BLE_UPDATE_CONN_PARAM_IND=18,                             //all:ble update connection parameter
    
    HELIOS_BLE_SCAN_REPORT_IND=19,                                    //client:ble gatt cliet scan and report other devices

    HELIOS_BLE_GATT_MTU=20,                                          //all:ble connection mtu
    HELIOS_BLE_GATT_RECV_IND=21,                                     //server:when ble client write characteristic value or descriptor,server get the notice
    HELIOS_BLE_GATT_RECV_READ_IND=22,                                //server:when ble client read characteristic value or descriptor,server get the notice
    HELIOS_BLE_GATT_RECV_NOTIFICATION_IND=23,                        //client:client recieve notification   
    HELIOS_BLE_GATT_RECV_INDICATION_IND=24,                          //client:client recieve indication
    HELIOS_BLE_GATT_SEND_END=25,                                     //server send notification,and recieve send end notice

    HELIOS_BLE_GATT_START_DISCOVER_SERVICE_IND=26,                   //client:start discover service
    HELIOS_BLE_GATT_DISCOVER_SERVICE_IND=27,                         //client:discover service
    HELIOS_BLE_GATT_DISCOVER_CHARACTERISTIC_DATA_IND=28,             //client:discover characteristic
    HELIOS_BLE_GATT_DISCOVER_CHARA_DESC_IND=29,                      //client:discover characteristic descriptor
    HELIOS_BLE_GATT_CHARA_WRITE_WITH_RSP_IND=30,                     //client:write characterisctc value with response
    HELIOS_BLE_GATT_CHARA_WRITE_WITHOUT_RSP_IND=31,                  //client:write characteristic value without response
    HELIOS_BLE_GATT_CHARA_READ_IND=32,                               //client:read characteristic value by hanlde
    HELIOS_BLE_GATT_CHARA_READ_BY_UUID_IND=33,                       //client:read characteristic value by uuid
    HELIOS_BLE_GATT_CHARA_MULTI_READ_IND=34,                         //client:read miltiple characteristic value
    HELIOS_BLE_GATT_DESC_WRITE_WITH_RSP_IND=35,                      //client:wirte characteristic descriptor
    HELIOS_BLE_GATT_DESC_READ_IND=36,                                //client:read characteristic descriptor
    HELIOS_BLE_GATT_ATT_ERROR_IND=37,                                //client:attribute error
    HELIOS_BLE_GATT_STATE_CHANGE_IND=38,                             //server:通道改变
    HELIOS_BLE_GATT_SEND_NODIFY_IND=39,                              //server:通知server线程从缓存里读取数据发送，只在标准版本使用

    HELIOS_BT_HFP_CONNECT_IND=40,                                    //bt hfp connected
    HELIOS_BT_HFP_DISCONNECT_IND=41,                                 //bt hfp disconnected
    HELIOS_BT_HFP_CALL_IND=42,                                       //bt hfp call state callback
    HELIOS_BT_HFP_CALL_SETUP_IND=43,                                 //bt hfp call setup state callback
    HELIOS_BT_HFP_NETWORK_IND=44,                                    //bt hfp network state callback
    HELIOS_BT_HFP_NETWORK_SIGNAL_IND=45,                             //bt hfp network signal callback
    HELIOS_BT_HFP_BATTERY_IND=46,                                    //bt hfp battery level callback
    HELIOS_BT_HFP_CALLHELD_IND=47,                                   //bt hfp callheld state callback
    HELIOS_BT_HFP_AUDIO_IND=48,                                      //bt hfp audio state callback
    HELIOS_BT_HFP_VOLUME_IND=49,                                     //bt hfp volume type callback
    HELIOS_BT_HFP_NETWORK_TYPE_IND=50,                               //bt hfp network type callback
    HELIOS_BT_HFP_RING_IND=51,                                       //bt hfp ring indication callback
    HELIOS_BT_HFP_CODEC_IND=52,                                      //bt hfp codec type callback

    HELIOS_BT_A2DP_AUDIO_CONFIG_IND=53,  //bt a2dp audio config callback
    HELIOS_BT_A2DP_AUDIO_STATE_START_IND=54,							    //bt a2dp audio state start callback
    HELIOS_BT_A2DP_AUDIO_STATE_STOPPED_IND=55,						    //bt a2dp audio state stop callback
    HELIOS_BT_A2DP_CONNECTION_STATE_CONNECTED_IND=56,				    //bt a2dp connect callback
    HELIOS_BT_A2DP_CONNECTION_STATE_DISCONNECTED_IND=57,				    //bt a2dp disconnect callback
    
    HELIOS_BT_AVRCP_CONNECTION_STATE_CONNECTED_IND=58,		//bt avrcp connect callback
    HELIOS_BT_AVRCP_CONNECTION_STATE_DISCONNECTED_IND=59,			                        //bt avrcp disconnect callback
    HELIOS_BT_AVRCP_VOLUME_CHANGE_IND=60,
    HELIOS_BT_SPP_CONNECT_IND=61,
    HELIOS_BT_SPP_DISCONNECT_IND=62,	 
#if defined(PLAT_Unisoc_8910_R05)
    HELIOS_BLE_GATT_SMP_COMPLETE_IND=63,                    //all:BLE smp complete
    HELIOS_BLE_GATT_SMP_USER_CONFIRM_IND=64,                //all:BLE SMP confirm user passkey
#endif
}Helios_BtBleEventIdType;


typedef enum
{
	HELIOS_BLE_MODE_NOTRUN,
	HELIOS_BLE_MODE_SERVER,
	HELIOS_BLE_MODE_CLINET,
}Helios_BleMode;


typedef struct
{
    uint32_t id;     ///< event identifier
    uint32_t param1; ///< 1st parameter
    uint32_t param2; ///< 2nd parameter
    uint32_t param3; ///< 3rd parameter
}Helios_Event;

//bt/ble address
typedef struct
{
    uint8_t addr[HELIOS_BT_MAC_ADDRESS_SIZE];
}Helios_BtBleAddr;

typedef enum 
{
    HELIOS_BT_BLE_STOPED    = 0,            //bt/ble is stoped
    HELIOS_BT_BLE_STARTED   = 1,            //bt/ble is started
}Helios_BtBle_Status;

typedef enum
{
    HELIOS_BT_BLE_NAME_CODE_UTF8 = 0,                   //code utf8
    HELIOS_BT_BLE_NAME_CODE_GBK = 1 ,                       //code GBK
}Helios_BtBleNameCodeType;

//bt/ble local name
typedef struct
{                             
    uint8_t name[HELIOS_BT_BLE_NAME_MAX_SIZE+1];  //蓝牙名称实际长度，最大长度为29.end with \0
    Helios_BtBleNameCodeType code_type;
}Helios_BtBleLocalName;

typedef struct
{
	uint16_t len;
	uint8_t *data;
}Helios_BtSppData;

typedef enum 
{
    HELIOS_BT_NONE_ENABLE               = 0, //can't be discovered and connectable
    HELIOS_BT_INQUIRY_ENABLE			= 1, //can be discovered,but can't be connected
    HELIOS_BT_PAGE_ENABLE				= 2, //can't be discovered,but can be connected
    HELIOS_BT_PAGE_AND_INQUIRY_ENABLE	= 3, //can be discovered and connected
}Helios_BtVisibleMode;

typedef enum
{
    HELIOS_BT_SERVICE_NONE 				= 0,
    HELIOS_BT_SERVICE_HANDFREE			= 1,
    HELIOS_BT_SERVICE_HANDSET			= 2,
    HELIOS_BT_SERVICE_OPP				= 3,
    HELIOS_BT_SERVICE_FTP				= 4,
    HELIOS_BT_SERVICE_A2DP				= 5,
    HELIOS_BT_SERVICE_AVRCP				= 6,
    HELIOS_BT_SERVICE_SPP				= 7,
    HELIOS_BT_SERVICE_A2DP_SRC			= 8,
    HELIOS_BT_SERVICE_AVRCP_TG			= 9,
    HELIOS_BT_SERVICE_MAP_SERVER		= 10,
    HELIOS_BT_SERVICE_PBAP_SERVER		= 11,
    HELIOS_BT_SERVICE_HANDFREE_GATEWAY	= 12,
    HELIOS_BT_SERVICE_HEADSET_GATEWAY	= 13,
    HELIOS_BT_SERVICE_BLE_HID			= 14,
    HELIOS_BT_SERVICE_ALL				= 15,
}Helios_BtServiceType;


typedef struct
{
	uint16_t name[HELIOS_BT_DEV_NAME_SIZE];	//bt name
	Helios_BtBleAddr addr;					//bt address
	uint32_t class;							//clasee level
	uint32_t rssi;							//rssi
}Helios_BtDevInfo;


typedef struct
{
	Helios_BT_Callback bt_user_cb;
}Helios_BtInitStruct;

typedef struct
{
	uint8_t state;
	Helios_BtBleAddr addr;
}Helios_BtHfpEventInfo;

typedef struct
{
	uint8_t state;
	Helios_BtBleAddr addr;
}Helios_BtSppEventInfo;


typedef struct
{
    Helios_BtBleAddr addr;
    uint8_t rssi;
    uint8_t device_name[HELIOS_BT_BLE_NAME_MAX_SIZE+1];
    uint32_t  device_class;
    uint8_t status;
}Helios_BtInquiryInfo;

typedef enum 
{
    Helios_BLEADV_INV                               = 0,    //可连接的非定向广播，默认选择
    Helios_BLEADV_HDCDA                             = 1,    //可连接高占空比的定向广播    
    Helios_BLEADV_SCAN_IND                          = 2,    //可扫描的非定向广�?
    Helios_BLEADV_NONCONN_IND                       = 3,    //不可连接的非定向广播
    Helios_BLEADV_LDCDA                             = 4,    //可连接低占空比的定向广播
}Helios_BleAdvTypeInfo;

typedef enum 
{
    Helios_BLEADV_FILTER_0                          = 0,            //处理所有设备的扫描和连接请�?
    Helios_BLEADV_FILTER_1                          = 1,            //处理所有设备的连接请求和只处理白名单设备的扫描请求
    Helios_BLEADV_FILTER_2                          = 2,            //处理所有设备的扫描请求和只处理白名单设备的连接请求
    Helios_BLEADV_FILTER_3                          = 3,            //只处理白名单设备的连接和扫描请求
}Helios_BleAdvFliterInfo;

typedef struct
{
    uint32_t max_adv;                                       //广播最大间隔：范围0x0020-0x4000。gap 0.625ms, 20ms-10.24s
    uint32_t min_adv;                                       //广播最小间隔：范围0x0020-0x4000。gap 0.625ms, 20ms-10.24s
    Helios_BleAdvTypeInfo adv_type;                             //广播类型
    uint32_t own_addr_type;                                //本地地址类型�?-公共地址�?-随机地址
    uint32_t channel_map;                                  //广播通道。bit0-37，bit1-38，bit2-39。默�?个信道都选择
    Helios_BleAdvFliterInfo filter;                             //广播过滤策略
    uint32_t discov_mode;                                  //发现模式，GAP协议使用，默认为1(普通发现模�?
    uint32_t no_br_edr;                                    //不用BR/EDR，默认为1
    uint32_t enable_adv;                                   //使能广播，默认为1
}Helios_BleAdvParam;



typedef struct
{
    uint8_t date_len;                                     //广播数据长度，不超过31个字�?
    uint8_t data[HELIOS_BLE_ADV_SCAN_DATA_SIZE];              //广播数据             
}Helios_BleAdvSetData;

typedef enum 
{
    HELIOS_BLE_GATT_LONG_UUID = 0,                      //长UUID�?28bit
    HELIOS_BLE_GATT_SHORT_UUID = 1,                         //短UUID�?6bit
}Helios_BleGattUuidState;

typedef struct
{
    Helios_BleGattUuidState uuid_type;
    uint8_t uuid_l[HELIOS_BLE_LONG_UUID_SIZE];
    uint16_t uuid_s; 
}Helios_BleGattUuid;


typedef enum
{
    HELIOS_RESERVED_SERVICE_DEL = 0,                //删除系统默认的GAP和GATT服务
    HELIOS_RESERVED_SERVICE_KEEP = 1,                   //保留系统默认的GAP和GATT服务
}Helios_BleSysServiceMode;

typedef enum
{
    HELIOS_BLE_GATT_NOTIFY = 0,                     //通知
    HELIOS_BLE_GATT_INDICATION = 1,                     //指示
}Helios_BleGattNotInd;


//connection parameter
typedef struct
{
    uint16_t conn_id;                         //connection id
    uint16_t max_interval;                    //最大的间隔，间隔：1.25ms，取值范围：6-3200，时间范围：7.5ms~4s
    uint16_t min_interval;                    //最小的间隔，间隔：1.25ms，取值范围：6-3200，时间范围：7.5ms~4s
    uint16_t latency;                         //从机忽略连接状态事件的时间。需满足：（1+latecy)*max_interval*2*1.25<timeout*10
    uint16_t timeout;                         //没有交互，超时断开时间，间隔：10ms，取值范围：10-3200，时间范围：100ms~32s
}Helios_BleUpdateConnInfos;

typedef struct
{
    uint16_t len;                                         //max 244
    uint8_t data[250];
    uint16_t uuid_s;
    uint8_t uuid_l[HELIOS_BLE_LONG_UUID_SIZE];
    uint16_t att_handle;
}Helios_BleGattData;

typedef struct
{
    uint8_t uuid_l[HELIOS_BLE_LONG_UUID_SIZE];
    uint16_t major;
    uint16_t minor;
}Helios_BleIbeaconCfg;


/*========================================= BLE Clinet =========================================*/
typedef enum
{
	HELIOS_BLESCAN_PASSIVE   = 0,        //消极扫描
    HELIOS_BLESCAN_ACTIVE    = 1,        //积极扫描，广播端设置的扫描回复数据才会有意义
}Helios_BleScanMode;

typedef struct
{
	Helios_BleScanMode scan_mode;		 //默认为积极扫�?
	uint32_t interval;					 //扫描间隔。范围：0x0004-0x4000，gap 0.625ms, 2.5ms-10.24s
	uint32_t window;					 //扫描时间。范围：0x0004-0x4000，gap 0.625ms, 2.5ms-10.24s
	Helios_BleAdvFliterInfo filter; 	 //扫描过滤策略，默认为0
	uint32_t own_addr_type;				 //本地地址类型�?-公共地址�?-随机地址
}Helios_BleScanParam;

typedef struct
{
	uint16_t start_handle;
	uint16_t end_handle;
}Helios_BleHandle;

typedef struct
{
	uint16_t length;
	uint8_t *data;    //特征值或特征描述�?
}Helios_BleGeneralData;

typedef struct
{
	Helios_BleGeneralData chara;
	uint16_t offset;
	uint8_t islong;
}Helios_BleCharaData;

typedef enum 
{
    HELIOS_BLE_PUBLIC_ADDRESS  = 0,        //public address
    HELIOS_BLE_RANDOM_ADDRESS  = 1,        //random address
}Helios_BleAddressType;

typedef enum 
{
    HELIOS_BLE_CONN_DISCONNECTED = 0,      //ble is disconnected
    HELIOS_BLE_CONN_CONNECTED,             //ble is connected
}Helios_BleConnectionStatus;


#define HELIOS_BLE_MAX_REMOTE_NAME_LEN 32
#define HELIOS_BLE_ADV_SCAN_DATA_SIZE 31

typedef struct
{
    uint8_t name_length;                                  //scan name lenth
    uint8_t name[HELIOS_BLE_MAX_REMOTE_NAME_LEN];         //scan name data
    uint8_t addr_type;                                    //device address type
    Helios_BtBleAddr addr;                                //device address
    uint8_t event_type;                                   //event type
    uint8_t data_length;                                  //raw data length
    uint8_t rssi;                                         //rssi
    uint8_t raw_data[HELIOS_BLE_ADV_SCAN_DATA_SIZE];      //scan raw data
}Helios_BleScanReportInfo;

typedef struct
{
    uint16_t uuid;
    uint16_t handle;
    uint16_t length;
    uint8_t *value;
}Helios_BleGattCharaDesc;

typedef struct
{
    uint16_t handle;
    uint16_t uuid;
    uint16_t value_handle;
    uint8_t properties;
    uint32_t desc_num;
    uint8_t *value;
    Helios_BleGattCharaDesc *pdesc_list;
}Helios_BleGattChara;

typedef struct
{
    uint16_t start_handle;
    uint16_t end_handle;
    uint16_t uuid;
    uint16_t char_num;
    Helios_BleGattChara *chara_list;
}Helios_BleGattPrimeService;

typedef struct
{
    uint16_t length;
    uint8_t *pay_load;
}Helios_AttGeneralRsp;


typedef struct
{
	Helios_BT_Callback ble_user_cb;
}Helios_BleInitStruct;

#if defined(PLAT_Unisoc_8910_R05)
typedef enum
{
    HELIOS_BLE_SMP_DISPLAY_ONLY = 0,                    //只有显示能力，可以显示PIN码
    HELIOS_BLE_SMP_DISPLAY_YESNO,                       //只有显示能力，只能显示Yes/No，不能显示PIN码
    HELIOS_BLE_SMP_KEYBOARD_ONLY,                       //只有输入能力，可以输入PIN码
    HELIOS_BLE_SMP_NOINPUT_NOOUTPUT,                    //没有输入输出能力
    HELIOS_BLE_SMP_KEYBOARD_DISPLAY,                    //有输入输出能力，既可以显示PIN码，又可以输入PIN码
} Helios_BleSmpIoCapability;

/*
*认证请求参数auth_req
*bit0   绑定。0配对后不绑定，1配对后绑定。
*bit2   MITM。0，不启用MIM。1启用MITM。
*Bit3   SC标志。0使用legacy paring，1使用 Secure Connections pairing。
*/
typedef struct
{
    Helios_BleSmpIoCapability io_cap;                      //IO能力
    unsigned char auth_req;                                 //认证请求参数，一般取值为9，即绑定，以及使用Secure Connections pairing
    unsigned int passkey;                                   //配对显示的PIN码
    unsigned int timeout;                                   //配对超时时间
} Helios_BleSmpCfg;

typedef enum
{
    HELIOS_BLE_SMP_PAIR_FAIL = 0,                       //配对失败
    HELIOS_BLE_SMP_LEGACY_JUST_WORK,                    //legecy paring:使用just work，不需要输入PIN码
    HELIOS_BLE_SMP_LEGACY_PASSKEY_OUTPUT,               //legecy paring:使用passkey entry，显示PIN码，不需要输入PIN码
    HELIOS_BLE_SMP_LEGACY_PASSKEY_INPUT,                //legecy paring:使用passkey entry，需要输入PIN码
    HELIOS_BLE_SMP_LEGACY_OOB,                          //legecy paring:使用OOB。不支持
    HELIOS_BLE_SMP_SECURE_JUST_WORK,                    //secure connection paring:使用just work，不需要输入PIN码
    HELIOS_BLE_SMP_SECURE_NUMBER_COMPARISON,            //secure connection paring:使用number compairison，显示PIN码，不需要输入PIN码
    HELIOS_BLE_SMP_SECURE_PASSKEY_OUTPUT,               //secure connection paring:使用passkey entry，显示PIN码，不需要输入PIN码
    HELIOS_BLE_SMP_SECURE_PASSKEY_INPUT,                //secure connection paring:使用passkey。需要输入PIN码
    HELIOS_BLE_SMP_SECURE_OOB,                          //secure connection paring:使用OOB。不支持
} Helios_BleSmpPairMode;

typedef struct
{
    unsigned int cid;                           //建立连接得到的连接ID
    Helios_BleSmpPairMode pair_mode;           //配对模式
    unsigned int pin;                           //PIN码
} Helios_BleSmpUserInfo;

typedef enum
{
    HELIOS_BLE_SMP_PAIR_CANCELED = 0,                   //取消配对
    HELIOS_BLE_SMP_PAIR_CONFIRM_WHIHOUT_PIN,            //确认配对，不携带PIN码
    HELIOS_BLE_SMP_PAIR_CONFIRM_WHIH_PIN,               //确认配对，携带PIN码
} Helios_BleSmpPairOperate;

typedef struct
{
    Helios_BleSmpPairOperate pair_op;          //建立连接得到的连接ID
    unsigned int pin;                           //PIN码
} Helios_BleSmpUserConfirm;

#define HELIOS_BLE_MAX_PAIRED_DEVICE_COUNT                    10 //最大10个，不能修改。展锐NV就只保存了10个
#define HELIOS_BLE_SMP_IRK_LEN                                16
typedef struct
{
    Helios_BtBleAddr addr;
    unsigned char irk[HELIOS_BLE_SMP_IRK_LEN];
} Helios_BleSmpDevInfo;

typedef struct
{
	uint16_t start_handle;
	uint16_t end_handle;
	uint16_t uuid_s;
	uint8_t  uuid_l[HELIOS_BLE_LONG_UUID_SIZE];
}Helios_BleHandleUUIDInfo;

#endif
 
/********************************************************************/
//以下接口为BT和BLE公用API
/********************************************************************/
#if !defined(PLAT_aic8800m40)
//开启BT/BLE
int Helios_BTBLE_Start(void);
//停止BT/BLE
int Helios_BTBLE_Stop(void);
//获取BT/BLE状�?
int Helios_BTBLE_GetStatus(Helios_BtBle_Status *status);
//设置BT/BLE名称到NVM，最大名称长�?2字节
int Helios_BTBLE_SetLocalName(Helios_BtBleLocalName *local_name);
//获取BT/BLE  名字
int Helios_BTBLE_GetLocalName(Helios_BtBleLocalName *local_name);
//设置是否过滤设备广播数据，设置后，同一台从机的广播数据只会上报一�?
int Helios_BTBLE_SetScanReportFilter(uint8_t act);
//获取广播数据的过滤策�?
int Helios_BTBLE_GetScanReportFilter(uint8_t *act);
#else
 //开启BLE GATT
int Helios_BLE_GattStart(void);
 //关闭BLE GATT
int Helios_BLE_GattStop(void);
//获取BLE状态
int Helios_BLE_GetStatus(Helios_BtBle_Status *status);
 //设置BLE GATT 名字
int Helios_BLE_GattSetLocalName(Helios_BtBleLocalName *local_name);
#endif


/********************************************************************/
//以下接口为BLE特有的API
/********************************************************************/

//获取公共地址
int Helios_BLE_GetPublic_addr(Helios_BtBleAddr *ble_addr);
//获取随机地址
int Helios_BLE_GetRandom_addr(Helios_BtBleAddr *ble_addr);
//GATT server/client 获取指定地址的连接状�?
int Helios_BLE_GetConnectionStatus(Helios_BtBleAddr *paddr, Helios_BleConnectionStatus *status);
//GATT SERVER 初始�?
int Helios_BLE_GattServerInit(Helios_BleInitStruct *info);
//GATT SERVER 资源释放
int Helios_BLE_GattServerRelease(void);
//设置广播参数
int Helios_BLE_AdvSetParam(Helios_BleAdvParam *adv_param);
//设置广播数据内容
int Helios_BLE_AdvSetData(Helios_BleAdvSetData *adv_data);
//设置收到APP扫描回复的数�?
int Helios_BLE_AdvSetScanRspData(Helios_BleAdvSetData *adv_data);
//设置ibeacon数据
int Helios_BLE_SetIbeaconData(Helios_BleIbeaconCfg *cfg);
//设置ibeacon数据到NVM
int Helios_BLE_WriteIbeaconCfg(Helios_BleIbeaconCfg *cfg);
//将ibeacon数据从NVM读取出来
int Helios_BLE_ReadIbeaconCfg(Helios_BleIbeaconCfg *cfg);
//为GATT增加服务service
int Helios_BLE_GattAddService(uint16_t server_id,Helios_BleGattUuid *uuid,uint8_t primary);
//为GATT增加属�?
int Helios_BLE_GattAddChara(uint16_t server_id,uint16_t chara_id,uint8_t char_prop,Helios_BleGattUuid *uuid);
//为GATT增加属性�?
int Helios_BLE_GattAddCharaValue(uint16_t server_id,uint16_t chara_id,uint16_t permission,Helios_BleGattUuid *uuid,uint16_t value_len,uint8_t *value);
//为GATT增加属性描�?
int Helios_BLE_GattAddCharaDesc(uint16_t server_id, uint16_t chara_id, uint16_t permission, Helios_BleGattUuid *uuid, uint16_t value_len, uint8_t *value);
//change the charcteristic value
int Helios_BLE_GattChangeCharaValue(uint16_t server_id,uint16_t chara_id,uint16_t value_len,uint8_t *value);
//添加完成service
int Helios_BLE_GattAddOrClearServiceComplete(uint16_t type,Helios_BleSysServiceMode mode);
//开启广�?
int Helios_BLE_AdvStart();
//停止广播
int Helios_BLE_AdvStop();
//发送数�?
int Helios_BLE_SendData(uint16_t conn_id, uint16_t att_handle,Helios_BleGattNotInd type, uint16_t length, uint8_t *value);
int Helios_BLE_ExchangeMtu(uint16_t conn_id, uint16_t mtu);

/****************************************************************************************/
/******************************以下接口用于BLE主机(client)**********************************/
/****************************************************************************************/
//GATT Clinet 初始�?
int Helios_BLE_GattClientInit(Helios_BleInitStruct *info);
//GATT client 资源释放
int Helios_BLE_GattClientRelease(void);
//GATT client 设置扫描参数
int Helios_BLE_ScanSetParam(Helios_BleScanParam *scan_param);
//GATT client 开始扫�?
int Helios_BLE_ScanStart(void);
//GATT client 停止扫描
int Helios_BLE_ScanStop(void);
//GATT client 建立连接
int Helios_BLE_ConnectAddr(Helios_BleAddressType addr_type, Helios_BtBleAddr *paddr);
//GATT client 取消正在建立连接
int Helios_BLE_CancelConnect(Helios_BtBleAddr *paddr);
//GATT client 断开已建立的连接
int Helios_BLE_Disconnect(uint16_t conn_id);
//GATT client 发现所有的服务
int Helios_BLE_GattDiscoverAllService(uint16_t conn_id);
//GATT client 发现指定UUID的服�?
int Helios_BLE_GattDiscoverByUuid(uint16_t conn_id, Helios_BleGattUuid *uuid);
//GATT client 发现所有的引用
int Helios_BLE_GattDiscoverAllIncludes(uint16_t conn_id, Helios_BleHandle *handle);
//GATT client 发现所有的特征
int Helios_BLE_GattDiscoverAllChara(uint16_t conn_id, Helios_BleHandle *handle);
//GATT client 发现所有的特征描述
int Helios_BLE_GattDiscoverAllCharaDesc(uint16_t conn_id, Helios_BleHandle *handle);
//GATT client 读取指定UUID的特征�?
int Helios_BLE_GattReadCharaByUuid(uint16_t conn_id, Helios_BleHandle *handle, Helios_BleGattUuid *uuid);
//GATT client 使用句柄读取特征�?
int Helios_BLE_GattReadCharaByHandle(uint16_t conn_id, uint16_t handle, uint16_t offset, uint8_t islong);
//GATT client 读取多个特征�?
int Helios_BLE_GattReadMultiChara(uint16_t conn_id, uint8_t *phandle, uint16_t length);
//GATT client 读取特征描述�?
int Helios_BLE_GattReadCharaDesc(uint16_t conn_id, uint16_t handle, uint8_t islong);
//GATT client 写入特征描述�?
int Helios_BLE_GattWriteCharaDesc(uint16_t conn_id, uint16_t handle, Helios_BleGeneralData *info);
//GATT client 写入特征�?
int Helios_BLE_GattWriteChara(uint16_t conn_id, uint16_t handle, Helios_BleCharaData *info);
//GATT client 写入特征�?蓝牙链路层不需要确�?
int Helios_BLE_GattWriteCharaNoRsp(uint16_t conn_id, uint16_t handle, Helios_BleGeneralData *info);

#if defined(PLAT_Unisoc_8910_R05)
//Set the configuration parameters used in the BLE SMP pairing process
int Helios_BLE_SmpSetConfig(Helios_BleSmpCfg smp_cfg);
//Get the configuration parameters used in the BLE SMP pairing process
int Helios_BLE_SmpGetConfig(Helios_BleSmpCfg* smp_cfg);
//Start the BLE SMP pairing process
//SMP pairing is initiated by the client, and the server can notify the client to initiate the SMP pairing request
int Helios_BLE_SmpStartPair(uint16_t conn_id);
//The user performs the corresponding operation according to the value of smp pair mode
int Helios_BLE_SmpUserConfirm(Helios_BleSmpUserConfirm user_confirm, uint16_t conn_id);
//Obtain device information for BLE SMP pairing
int Helios_BLE_SmpGetPairedDevInfo(unsigned char paired_num, unsigned char *real_paired_num, Helios_BleSmpDevInfo *dev_list);
//Removes BLE SMP pairing information for the specified device
int Helios_BLE_SmpRemovePairedDev(Helios_BtBleAddr *dev);
//Remove BLE SMP pairing information for all devices
int Helios_BLE_SmpCleanPairedDev(void);

#endif

/****************************** Classic BT API**************************************/
int Helios_BT_Init(Helios_BtInitStruct *info);
int Helios_BT_Release(void);

//设置经典蓝牙可见模式
int Helios_BT_SetVisibleMode(Helios_BtVisibleMode scanmode);
//获取经典蓝牙可见模式
int Helios_BT_GetVisibleMode(Helios_BtVisibleMode *scanmode);
//获取经典蓝牙的地址
int Helios_BT_GetLocalAddr(Helios_BtBleAddr *bt_addr);
//开始经典蓝牙扫�?暂不支持)
int Helios_BT_StartInquiry(Helios_BtServiceType type);
//取消经典蓝牙扫描搜索(暂不支持)
int Helios_BT_CancelInquiry(void);
//开始经典蓝牙的配对(暂不支持)
//int Helios_BT_StartBond(Helios_BtBleAddr *bond_addr);
//取消经典蓝牙的配�?暂不支持)
//int Helios_BT_CancelBond(Helios_BtBleAddr *bond_addr);
//获取已配对设备的信息(暂不支持)
//int Helios_BT_GetBondInfo(uint32_t spec_num, uint32_t *real_num, Helios_BtDevInfo info[]);
//删除一个已经配对的设备(暂不支持)
//int Helios_BT_RemoveBondDev(Helios_BtBleAddr *bond_addr);
//删除所有已经配对的设备(暂不支持)
//int Helios_BT_RemoveAllBondDev(void);
//start reconnect device that connected last time
void Helios_BT_Reconnect(void);
//set reconnect information
void Helios_BT_Reconnect_Set(uint16_t max_times, uint8_t period);

/****************************** BT SPP API**************************************/

//建立SPP连接（R02不支持）
int Helios_BT_SPP_Connect(Helios_BtBleAddr *bt_addr);
//断开SPP连接（R02不支持）
int Helios_BT_SPP_Disconnect(void);
//获取指定设备的连接状�?暂不支持)
//int Helios_BT_GetConnectStatus(Helios_BtBleAddr *conn_addr, uint8_t *status);
//通过SPP发送数�?R02不支�?
int Helios_BT_SPP_Send(Helios_BtSppData *info);
//BT SPP初始�?
int Helios_BT_SPP_Init(void);
//BT SPP释放资源
int Helios_BT_SPP_Release(void);

/****************************** BT HFP API**************************************/
#if !defined(PLAT_aic8800m40)
//BT HFP初始�?
int Helios_BT_HFP_Init(void);
//BT HFP释放资源
int Helios_BT_HFP_Release(void);
//连接HFP
int Helios_BT_HFP_Connect(Helios_BtBleAddr *ag_addr);
//断开HFP连接
int Helios_BT_HFP_Disconnect(Helios_BtBleAddr *ag_addr);
//设置HFP通话音量
int Helios_BT_HFP_SetVolume(Helios_BtBleAddr *ag_addr, uint8_t vol);
//接通电话后挂机
int Helios_BT_HFP_RejectAfterAnswerCall(Helios_BtBleAddr *ag_addr);
//接通电�?
int Helios_BT_HFP_AnswerCall(Helios_BtBleAddr *ag_addr);
//拒接电话
int Helios_BT_HFP_RejectCall(Helios_BtBleAddr *ag_addr);
//拨打电话(暂不支持)
//int Helios_BT_HFP_dial(Helios_BtBleAddr *ag_addr, uint8_t *phone_num);
//重复拨号(暂不支持)
//int Helios_BT_HFP_Redial(Helios_BtBleAddr *ag_addr);
//开启AG语音助手
int Helios_BT_HFP_EnableVR(Helios_BtBleAddr *ag_addr);
//关闭AG语音助手
int Helios_BT_HFP_DisableVR(Helios_BtBleAddr *ag_addr);
//控制三方通话
int Helios_BT_HFP_CtrlThreeWayCall(Helios_BtBleAddr *ag_addr, uint8_t cmd);

/****************************** BT A2DP/AVRCP API**************************************/

//初始化BT A2DP和AVRCP
int Helios_BT_A2DP_AVRCP_Init(void);
//BT A2DP和AVRCP释放资源
int Helios_BT_A2DP_AVRCP_Release(void);
//断开A2DP连接
int Helios_BT_A2DP_Disconnect(Helios_BtBleAddr *bt_addr);
//获取A2DP主机蓝牙地址
int Helios_BT_A2DP_GetAddr(Helios_BtBleAddr *bt_addr);
//获取A2DP连接状�?
int Helios_BT_A2DP_GetConnectStatus(uint8_t *status);
//通过AVRCP协议控制主机开始播�?
int Helios_BT_AVRCP_Start(void);
//通过AVRCP协议控制主机停止播放
int Helios_BT_AVRCP_Pause(void);
//通过AVRCP协议控制主机播放上一�?
int Helios_BT_AVRCP_Prev(void);
//通过AVRCP协议控制主机播放下一�?
int Helios_BT_AVRCP_Next(void);
//通过AVRCP协议控制主机播放音量
int Helios_BT_AVRCP_SetVol(uint8_t vol);
//通过AVRCP协议获取主机播放音量
int Helios_BT_AVRCP_GetVol(uint8_t *vol);
//通过AVRCP协议获取主机播放状�?
int Helios_BT_AVRCP_GetPlayStatus(uint8_t *status);
//获取AVRCP协议获取主机连接状�?
int Helios_BT_AVRCP_GetConnectStatus(uint8_t *status);
#endif

#ifdef __cplusplus
} /*"C" */
#endif

#endif


