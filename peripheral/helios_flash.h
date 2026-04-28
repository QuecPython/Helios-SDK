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


#ifndef _HELIOS_FLASH_H_
#define _HELIOS_FLASH_H_

#include <stdint.h>

typedef struct
{
    char *name;
    uint32_t addr;
    size_t size;
#if defined(PLAT_ASR) || defined(PLAT_ASR_1606) || defined(PLAT_ASR_1609) || defined(PLAT_ASR_1602)//forrest.liu@20220309 add for ASR1601 platform pythonSDK use same lfs handle as kernel
	void *lfs_kernel;
#endif	
} HeliosFlashPartiCtx;





HeliosFlashPartiCtx *Helios_Flash_GetPartiCtx(const char *parti_name);
int Helios_Flash_Write(uint32_t addr, const void *buffer, size_t size);
int Helios_Flash_Read(uint32_t addr, void *buffer, size_t size);
int Helios_Flash_Erase(uint32_t addr, size_t size);
#if defined(PLAT_ASR_1606) || defined(PLAT_ASR_1609) || defined(PLAT_ASR_1602)
int Helios_External_Flash_Read(int port, uint32_t addr, void *buffer, size_t size);
void *Helios_lfs_mutexlock_get(char *patition_name);
#endif

#if defined(BOARD_EC600MCN_CC_EXT) || defined(BOARD_EC600MCN_CC_EXT_TTS) || defined(BOARD_EC800MCN_CC_TTS) \
    || defined(BOARD_EC800KCN_CC_TTS) || defined(BOARD_EC600KCN_CC_TTS)

int Helios_Flash_Fs_Format(char *parti_name);
#endif

#ifdef CONFIG_SPINAND

typedef unsigned int FILE_ID;

typedef struct tag_nandfile_info
{
   /* filename plus end of string character */
   char file_name[128 + 1];
   int       time;          /* updated time stamp when modified */
   int       date;          /* updated date stamp when modified */
   unsigned int      size;          /* size of file data in bytes */
   unsigned short      owner_id;
   unsigned short      group_id;
   unsigned short      permissions;
   FILE_ID   data_id;       /* FDI identifier for file data */

   /* the following fields are needed for power loss recovery */

   FILE_ID   plr_id;        /* used for power loss recovery */
   int       plr_time;      /* used for power loss recovery */
   int       plr_date;      /* used for power loss recovery */
   unsigned int     plr_size;      /* used for power loss recovery */
} NANDFILE_INFO;

int Helios_NandFlash_Init();
FILE_ID Helios_NandFlash_fopen(const char *filename_ptr, const char *mode);
int Helios_NandFlash_fclose(FILE_ID stream);
int Helios_NandFlash_fread(void *buff, size_t element_size, size_t count, FILE_ID stream);
int Helios_NandFlash_fwrite(const void *buff, size_t element_size, size_t count, FILE_ID stream);
int Helios_NandFlash_fseek(FILE_ID stream, int32_t offset, int wherefrom);
int Helios_NandFlash_fremove(const char *filename_ptr);
int Helios_NandFlash_frename(char *name, char *new_name);
int Helios_NandFlash_fsize(char *file_name);
int Helios_NandFlash_fmkdir(char *dir_name);
int Helios_NandFlash_faccess(char *name);
int Helios_NandFlash_FreeSize();

int Helios_NandFlash_FindFirst(const char *filename_ptr, NANDFILE_INFO* fileinfo_ptr);
int Helios_NandFlash_FindNext(NANDFILE_INFO* fileinfo_ptr);
int Helios_NandFlash_frmdir(char *dir_name);
int Helios_NandFlash_SetCurrentDir(const char* dir_mane);
char *Helios_NandFlash_GetCurrentDir(char *Buffer, unsigned int MaxLen);
int Helios_NandFlash_Fromat();
int Helios_NandFlash_ListDir(const char *dir_ptr, char* fileinfo_ptr);


#endif

#endif
