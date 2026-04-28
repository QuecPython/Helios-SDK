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


#ifndef _HELIOS_FOTA_H_
#define _HELIOS_FOTA_H_

#include <stddef.h>

#if defined (PLAT_Unisoc) || defined(PLAT_Unisoc_8910_R05) || defined(PLAT_Unisoc_8910_R06)//forrest.liu@20220611 add for http header set by python
struct header
{
	char *key;
	char *value;
};
#endif

int Helios_Fota_Init(void);
int Helios_Fota_PackageWrite(int hdl, void *data, size_t len, size_t file_size);
int Helios_Fota_PackageFlush(int hdl);
int Helios_Fota_PackageVerify(int hdl);
int Helios_Fota_firmware_download(char * address1, char * address2, void(*cb)(int sta, int progress));
void Helios_Fota_Deinit(int hdl);
int Helios_Fota_Set_PublicKey(unsigned char* key, int key_len);

#endif
