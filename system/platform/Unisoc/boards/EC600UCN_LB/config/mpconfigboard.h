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
 
#ifndef __MPCONFIGBOARD_H__
#define __MPCONFIGBOARD_H__

#define MICROPY_QPY_MODULE_ATCMD            (1)
#define MICROPY_QPY_MODULE_UOS              (1)
#define MICROPY_QPY_MODULE_MACHINE          (1)
#define MICROPY_QPY_MODULE_USOCKET          (1)
#define MICROPY_QPY_MODULE_MISC             (1)
#define MICROPY_QPY_MODULE_OSTIMER          (1)
#define MICROPY_QPY_MODULE_EXAMPLE          (1)
#define MICROPY_QPY_MODULE_DATACALL         (1)
#define MICROPY_QPY_MODULE_MODEM            (1)
#define MICROPY_QPY_MODULE_UTIME            (1)
#define MICROPY_QPY_MODULE_UTILS            (1)
#define MICROPY_QPY_MODULE_HMACSHA1         (1)
#define MICROPY_QPY_MODULE_SMS              (1)
#define MICROPY_QPY_MODULE_SIM              (1)
#define MICROPY_QPY_MODULE_SIMDET           (1)
#define MICROPY_QPY_MODULE_LPM              (1)
#define MICROPY_QPY_MODULE_NET              (1)
#define MICROPY_QPY_MODULE_CELLLOCATOR      (1)
#define MICROPY_QPY_MODULE_AUDIO            (1)
#define MICROPY_QPY_MODULE_FOTA             (1)
#define MICROPY_QPY_MODULE_WIFISCAN         (1)
#define MICROPY_QPY_MODULE_QUECGNSS         (1)
#define MICROPY_QPY_MODULE_WIFILOCATOR      (1)
#define MICROPY_QPY_MODULE_ETHERNET         (1)
#define MICROPY_QPY_MODULE_SENSOR           (1)
#define MICROPY_QPY_MODULE_SECUREDATA       (1)
#define MICROPY_QPY_MODULE_SLIP             (1)
#define MICROPY_QPY_MODULE_TP               (0)
#define MICROPY_QPY_MODULE_AUDIOCODEC       (0)
#define MICROPY_QPY_MODULE_CSD              (0)
#define MICROPY_QPY_MODULE_LWM2M            (0)
#define MICROPY_QPY_MODULE_NB               (0)
#define MICROPY_QPY_MODULE_UHASHLIB         (1)
#define MICROPY_QPY_MODULE_UCRYPTOLIB       (1)
#define MICROPY_QPY_MODULE_URSA             (1)
#define MICROPY_QPY_MODULE_IPSEC            (1)

#if CONFIG_MBEDTLS
    #define MICROPY_QPY_MODULE_USSL         (1)
    #define MICROPY_QPY_SSL_MBEDTLS         (1)
#endif

#if CONFIG_QUECTHING
    #define MICROPY_QPY_MODULE_QUECIOT          (1)
#else
    #define MICROPY_QPY_MODULE_QUECIOT          (0)
#endif

#if CONFIG_LVGL
    #define MICROPY_QPY_MODULE_LVGL             (1)
#else
    #define MICROPY_QPY_MODULE_LVGL             (0)
#endif

#if CONFIG_CAMERA
    #define MICROPY_QPY_MODULE_CAMERA           (1)
#else
    #define MICROPY_QPY_MODULE_CAMERA           (0)
#endif

#if CONFIG_RTMP
    #define MICROPY_QPY_MODULE_RTMP             (1)
#else
    #define MICROPY_QPY_MODULE_RTMP             (0)
#endif

#if CONFIG_VIOCE_CALL
    #define MICROPY_QPY_MODULE_VIOCE_CALL       (1)
#else
    #define MICROPY_QPY_MODULE_VIOCE_CALL       (0)
#endif

#if CONFIG_POC
    #define MICROPY_QPY_MODULE_POC              (1)
#else
    #define MICROPY_QPY_MODULE_POC              (0)
#endif

#if CONFIG_QRCODE
    #define MICROPY_QPY_MODULE_QRCODE           (1)
#else
    #define MICROPY_QPY_MODULE_QRCODE           (0)
#endif

#ifdef CONFIG_QUEC_PROJECT_FEATURE_BLE_GATT
    #define MICROPY_QPY_MODULE_BLE              (1)
#else
    #define MICROPY_QPY_MODULE_BLE              (0)
#endif

#ifdef CONFIG_QUEC_PROJECT_FEATURE_CLASSIC_BT
    #define MICROPY_QPY_MODULE_BT               (1)
#else
    #define MICROPY_QPY_MODULE_BT               (0)
#endif


#if MICROPY_QPY_MODULE_MACHINE
    #define MICROPY_QPY_MACHINE_TIMER           (1)
    #define MICROPY_QPY_MACHINE_RTC             (1)
    #define MICROPY_QPY_MACHINE_WDT             (1)
    #define MICROPY_QPY_MACHINE_PIN             (1)
    #define MICROPY_QPY_MACHINE_EXTINT          (1)
    #define MICROPY_QPY_MACHINE_UART            (1)
    #define MICROPY_QPY_MACHINE_SPI             (1)
    #define MICROPY_QPY_MACHINE_I2C             (1)
    #define MICROPY_QPY_MACHINE_I2C_SOFT        (1)
	#define MICROPY_QPY_MACHINE_KEY             (1)
	#define MICROPY_QPY_MACHINE_ONE_WIRE           (1)
    #ifdef CONFIG_LCD
        #define MICROPY_QPY_MACHINE_LCD             (1)
#else
        #define MICROPY_QPY_MACHINE_LCD             (0)
#endif
    #define MICROPY_QPY_MACHINE_KEYPAD          (1)
    #ifdef CONFIG_SPINAND
        #define MICROPY_QPY_MACHINE_NANDFLASH       (1)
    #else
        #define MICROPY_QPY_MACHINE_NANDFLASH       (0)
    #endif
#endif

#if MICROPY_QPY_MODULE_MISC
    #define MICROPY_QPY_MISC_POWER              (1)
    #define MICROPY_QPY_MISC_ADC                (1)
    #define MICROPY_QPY_MISC_POWERKEY           (1)
    #define MICROPY_QPY_MISC_TEMPERATURE        (0)
    #define MICROPY_QPY_MISC_PWM                (1)
    #define MICROPY_QPY_MISC_USB                (1)
    #define MICROPY_QPY_MISC_USBNET             (1)
    #define MICROPY_QPY_MISC_CFG_NETLIGHT       (1)
#endif

#if MICROPY_QPY_MODULE_AUDIO
    #define MICROPY_QPY_AUDIO_AUDIO             (1)
    #if CONFIG_TTS
        #define MICROPY_QPY_AUDIO_TTS               (1)
    #else
        #define MICROPY_QPY_AUDIO_TTS               (0)
    #endif
    #define MICROPY_QPY_AUDIO_RECORD            (1)
#endif

#if MICROPY_QPY_MODULE_ETHERNET
    #define MICROPY_QPY_ETHERNET_DM9051         (0)
    #define MICROPY_QPY_ETHERNET_W5500          (1)
    #define MICROPY_QPY_ETHERNET_CH395          (1)
#endif

#if MICROPY_QPY_MODULE_TP
    #define MICROPY_QPY_TP_XPT2046              (1)
    #define MICROPY_QPY_TP_GT9XX                (1)
#endif

#if MICROPY_QPY_MODULE_AUDIOCODEC
    #define MICROPY_QPY_AUDIOCODEC_RT5616       (0)
#endif

#if MICROPY_QPY_MODULE_SENSOR
    #define MICROPY_QPY_SENSOR_SN95500          (0)
	#define MICROPY_QPY_SENSOR_ICC_KEY			(0)
	#define MICROPY_QPY_SENSOR_GNSS				(1)
#endif

#if MICROPY_QPY_MODULE_CAMERA
    #define MICROPY_QPY_CAMERA_CAMPREVIEW       (1)
    #if CONFIG_CAMERA_SAVEPHOTOS
        #define MICROPY_QPY_CAMERA_CAMCAPTURE       (1)
    #else
        #define MICROPY_QPY_CAMERA_CAMCAPTURE       (0)
    #endif
    #ifdef CONFIG_CAMERA_DECODE
        #define MICROPY_QPY_CAMERA_CAMSCANDECODE    (1)
    #else
        #define MICROPY_QPY_CAMERA_CAMSCANDECODE    (0)
    #endif
#endif

#if MICROPY_QPY_MODULE_UCRYPTOLIB
    #define MICROPY_PY_UCRYPTOLIB_DES           (0)
    #ifdef CONFIG_GMSSL
        #define MICROPY_PY_UCRYPTOLIB_SM2           (1)
        #define MICROPY_PY_UBINASCII_SM3			(1)
        #define MICROPY_PY_UCRYPTOLIB_SM4           (1)
    #endif
#endif

#define MICROPY_QPY_GC_HEAP_SIZE            (832 * 1024)
#define MICROPY_QPY_DEVICE_REPORT           (0)

/***********************micropython opts*******************************/
#define MICROPY_QPY_DEBUG_PRINTERS      		(1)  //flash 4160 Byte
#define MICROPY_QPY_PY_MATH             		(1)  //flash 14880 Byte
#define MICROPY_QPY_PY_CMATH            		(1)  //flash 3136 Byte
#define MICROPY_QPY_PY_USELECT   		        (1)  //flash 1792 Byte
#define MICROPY_QPY_PY_UCTYPES          		(1)  //flash 2816 Byte
#define MICROPY_QPY_PY_UZLIB            		(1)  //flash 3072 Byte
#define MICROPY_QPY_PY_UASYNCIO   		        (1)  //flash 2048 Byte
#define MICROPY_QPY_PY_ENABLE_WEBSERVER			(1)  //flash 3424 Byte
#define MICROPY_QPY_PERSISTENT_CODE_LOAD        (1)  //flash 2048 Byte
#define MICROPY_QPY_EMIT_XTENSAWIN              (0)  //flash 19776 Byte


#endif
