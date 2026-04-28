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
#ifndef _HELIOS_CAMERA_H
#define _HELIOS_CAMERA_H
 
#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
	int        result;
	uint8_t*   DataBuf;
} Helios_decode_para;


typedef void (*Callback_decode)(Helios_decode_para* outdata);
typedef void (*Decode_Method)(unsigned char* buf, int width, int height);
typedef void (*SaveImage_Method)(unsigned char* pYUVBuffer, int width, int height);



typedef struct {
	uint8_t 			model;
	uint16_t         	camwidth;     //
	uint16_t         	camheight;
	uint8_t          	decbufcnt;    //����buffer������
	uint8_t 		   	preview;      //�Ƿ���Ҫ����Ԥ��
	uint8_t          	prebufcnt;    //Ԥ����buffer����
	uint16_t         	lcdprewidth;  //Ԥ��ͼ��Ŀ��
	uint16_t         	lcdpreheight; //Ԥ��ͼ��ĸ߶�
	Decode_Method		decode_pro;
	SaveImage_Method	saveimg_pro;
	
}Helios_CAMConfig;
 
 int Helios_camera_open(Helios_CAMConfig * camconfig);
 
 int Helios_camera_close();

 int Helios_camera_scandecode_callback(Callback_decode callback);
 
 int Helios_camera_scandecode_start();
 int Helios_camera_scandecode_pause();
 
 int Helios_camera_scandecode_resume();
 
 int Helios_camera_scandecode_stop();
 
 int Helios_camera_capture();

#ifdef CONFIG_DECODE_QINGYA
#if defined(PLAT_ASR) || defined(PLAT_ASR_1606) || defined(PLAT_ASR_1609) || defined(PLAT_ASR_1602)

#define CAM_SUPPORT_MAX_DECODE_LEN 2500

typedef enum
{
   CAM_DECODE_SUCESS    = 0,
   CAM_DECODE_FAIL      = -1,
   CAM_DECODE_INIT_FAIL = -2,
   CAM_DECODE_NOT_OPEN  = -3,
} ENUM_CAM_DECODE_RESULT;

typedef struct
{
	unsigned char  Type;
	int            DecodeLen;
	int            result;
	unsigned char  DataBuf[CAM_SUPPORT_MAX_DECODE_LEN];
} CAL_IDENTITY_RESULT_STRUCT,*P_CAL_IDENTITY_RESULT_STRUCT;


int Helios_Camera_ScanCode(unsigned char *InBuf,P_CAL_IDENTITY_RESULT_STRUCT OutBuf, int width, int height);

#endif
#endif

#ifdef __cplusplus
 } /*"C" */
#endif
 
#endif


