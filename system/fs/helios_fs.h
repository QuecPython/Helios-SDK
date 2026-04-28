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


#ifndef _HELIOS_FS_H_
#define _HELIOS_FS_H_

#include <stdint.h>
#include <stddef.h>

typedef enum
{
    SD_DET_LEVEL_INSERT_LOW  = 0,
	SD_DET_LEVEL_INSERT_HIGH   = 1 
} Helios_sd_det_mode;

typedef void HeliosFILE;

typedef void (*Helios_SD_Callback)(uint8_t ind_type);

#define FS_PATH_MAX 64
 
 typedef struct {
 	 char is_used;
	 char Letter[FS_PATH_MAX];
	 char pythonPath[FS_PATH_MAX];
	 char FlashName[FS_PATH_MAX];
	 void* vfs_self;
 }FS_MAP_S;

#if defined(PLAT_SONY_ALT1350)
typedef void HeliosDIR;

typedef struct {
    uint8_t    d_type;
    char       d_name[128];
} HeliosDIR_Iter;

typedef struct {
    uint32_t      f_size;
    uint32_t      f_isdir;
    uint32_t      reserved[8];//预留，预备后续对接到其他平台时扩展
} Helios_fstat_t;

typedef struct {
    uint32_t      f_bsize;
    uint32_t      f_blocks;
    uint32_t      f_bfree;
    uint32_t      f_bavail;
    uint32_t      reserved[8];//预留，预备后续对接到其他平台时扩展
} Helios_fs_info_t;

int Helios_rename(const char *old_path, const char *new_path);
int Helios_rmdir(const char *path);
int Helios_mkdir(const char *path, uint16_t mode);
int Helios_fstat(const char *path, Helios_fstat_t *fstat);
int helios_fs_info_get(const char disk, Helios_fs_info_t* fs_info);
HeliosDIR* Helios_opendir(const char *path);
int Helios_closedir(HeliosDIR *dir);
int Helios_readdir(HeliosDIR *dir, HeliosDIR_Iter* dir_iter);
#endif

HeliosFILE *Helios_fopen(const char *fname, const char *mode);
int Helios_remove(const char *fname);
int Helios_fwrite(void *buffer, size_t size, size_t num, HeliosFILE *file);
int Helios_fread(void *buffer, size_t size, size_t num, HeliosFILE *file);
int Helios_fclose(HeliosFILE *file);
int Helios_fsize(HeliosFILE *file);
int Helios_fs_free_size(char disk_sym);
int Helios_fseek(HeliosFILE *file, long offset, int origin);
int Helios_ftell(HeliosFILE *file);
int Helios_frewind(HeliosFILE *file);
int Helios_fputc(int chr, HeliosFILE *file);
int Helios_fputs(const char *str, HeliosFILE *file);
int Helios_fprintf(HeliosFILE *file, const char *format, ...);
int Helios_fgetc(HeliosFILE *file);
char *Helios_fgets(char *str, int n, HeliosFILE *file);
int Helios_fscanf(HeliosFILE *file, const char *format, ...);
void Helios_lfs_register(void *p);
#if defined(PLAT_Unisoc) || defined(PLAT_Unisoc_8850) || defined(PLAT_Unisoc_8910_R05) || defined(PLAT_Unisoc_8850_R02) || defined(PLAT_Unisoc_8910_R06)
int Helios_lfs_mount(const char *base_path, void *p, const char* flashName);
int Helios_lfs_mount_threadsafe(const char *base_path, void* p, const char* flashName, void* vfs_lfs_mutex);
#else
int Helios_lfs_mount(const char *base_path, void *p);
#endif
int Helios_sd_mount(void);
int Helios_sd_set_det(size_t gpio_num,Helios_sd_det_mode mode);
int Helios_sd_set_callback(Helios_SD_Callback sd_callback_fnc);
#if defined (PLAT_Unisoc) || defined(PLAT_Unisoc_8910_R05) || defined(BOARD_BG95M6) || defined(PLAT_Unisoc_8850_R02) || defined(PLAT_Unisoc_8910_R06)
void Helios_set_nor_flash_spi(unsigned char port_number,unsigned char clk);
#endif

int Helios_lfs_register_map(const char *flashName, const char* Letter, const char *python_path, void* vfs_self);
int Helios_lfs_unregister_map(const char *pythonPath);
char* Helios_Flash_DiskSym_get(char *patition_name);
void get_vfs_path(const char* base_path, char* dsc_path);
char* Helios_lfs_get_letter_by_PYPath(const char *python_path);
int Helios_EXTFS_Init(int port, int clk);
void* Helios_vfs_get_vfsobj_by_PYPath(const char *python_path);

// add by elian.wang
#if defined(PLAT_ASR_1803s) || defined(PLAT_ASR_1803sc)

#define ASR_SDIO_SD_VOLUME 			"C:"
HeliosFILE *Helios_fat_fopen(const char *fname, const char *mode);
int Helios_fat_fclose(HeliosFILE *file);
int Helios_fat_remove(const char *fname);
int Helios_fat_fwrite(void *buffer, size_t size, size_t num, HeliosFILE *file);
int Helios_fat_fread(void *buffer, size_t size, size_t num, HeliosFILE *file);
int Helios_fat_fseek(HeliosFILE *file, long offset, int origin);
int Helios_fat_rename(const char *oldpath, const char *newpath);
int Helios_fat_makedir(char *dir_name, unsigned int mode);
int Helios_fat_removedir(char *dir_name);
int Helios_fat_fsync(unsigned int stream);
int Helios_fat_is_file_exist(char *path);
unsigned char Helios_fat_getstat(char *path, unsigned int *size, unsigned char *isdir);
unsigned int Helios_fat_getfree(char *path);
unsigned int Helios_fat_gettotal(char *path);
int Helios_fat_diropen(void* f_dir, const char* dir_path);
int Helios_fat_dirread(void* f_dir, void* f_fileinfo);
int Helios_fat_format(const char* fs_path);
int Helios_fat_dirclose(void* f_dir);

typedef enum Helios_sdio_device_type
{
    HELIOS_SDIO_SDCARD,
    HELIOS_SDIO_EMMC
} Helios_sdio_device_type_e;

int Helios_fat_device_type_switch(Helios_sdio_device_type_e sdio_device_type);
#endif

#if defined(PLAT_RDA) || defined(PLAT_ASR_1606)
extern int Helios_NV_File_Exist(const char *file_name);
extern int Helios_NV_File_Write(const char   *file_name,      void *write_buf,int write_size);
extern int Helios_NV_File_Read(const char   *file_name,      void *read_buf,int read_size);
extern int Helios_NV_File_Delete(const char   *file_name);

#define PYLOG_PORT_CFG_FILE "pylog_cfg"
#endif

#endif
