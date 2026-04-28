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

#include "helios_fs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helios_debug.h"

#if defined(PLAT_ASR) \
   || defined(PLAT_Unisoc) \
   || defined(PLAT_ASR_1606) \
   || defined(PLAT_ASR_1609) \
   || defined(PLAT_EIGEN) \
   || defined(PLAT_EIGEN_718) \
   || defined(PLAT_Unisoc_8850) \
   || defined(PLAT_ASR_1803s) || defined(PLAT_ASR_1803sc) \
   || defined(PLAT_Unisoc_8910_R05) \
   || defined(PLAT_ASR_1602) \
   || defined(PLAT_Unisoc_8850_R02) \
   || defined(PLAT_Unisoc_8910_R06)


#define FS_MAP_MAX 8

#define HELIOS_FS_LOG(fmt, ...) custom_log(helios_python_fs, fmt, ##__VA_ARGS__)

FS_MAP_S fs_map[FS_MAP_MAX] = {0};

void Helios_lfs_Map_printf() {
	int index = 0;
	for(index = 0; index < FS_MAP_MAX; index++) { 
		if(fs_map[index].is_used == 1) {
			HELIOS_FS_LOG("index[%d] flashName[%s] Letter[%s] pythonPath[%s] self[%x]\n", index, 
				fs_map[index].FlashName, fs_map[index].Letter, fs_map[index].pythonPath, fs_map[index].vfs_self);
		}
	}

}


int Helios_lfs_register_map(const char *flashName, const char* Letter, const char *python_path, void* vfs_self) {
	int index = 0;
	
	for(index = 0; index < FS_MAP_MAX; index++) {
		if(fs_map[index].is_used == 1 && strcmp(fs_map[index].FlashName, flashName) == 0)
		{
		    fs_map[index].is_used = 0;
			memset(fs_map[index].Letter, 0, FS_PATH_MAX);
			memset(fs_map[index].pythonPath, 0, FS_PATH_MAX);
			//return 0;
		}
	}
	
	for(index = 0; index < FS_MAP_MAX; index++) {
		if(fs_map[index].is_used == 0){
			fs_map[index].is_used = 1;
			memset(fs_map[index].FlashName, 0, FS_PATH_MAX);
			strncpy(fs_map[index].FlashName, flashName, strlen(flashName));
			memset(fs_map[index].Letter, 0, FS_PATH_MAX);
			strncpy(fs_map[index].Letter, Letter, strlen(Letter));
			memset(fs_map[index].pythonPath, 0, FS_PATH_MAX);
			strncpy(fs_map[index].pythonPath, python_path, strlen(python_path));
			fs_map[index].vfs_self = vfs_self;
			Helios_lfs_Map_printf();
			return 0;
		}
	}
	return -1;
}




int Helios_lfs_unregister_map(const char *pythonPath) {
	int index = 0;
	for(index = 0; index < FS_MAP_MAX; index++) {
		if(fs_map[index].is_used == 1 && strcmp(fs_map[index].FlashName, pythonPath) == 0){
			fs_map[index].is_used = 0;
			memset(fs_map[index].FlashName, 0, FS_PATH_MAX);
			memset(fs_map[index].Letter, 0, FS_PATH_MAX);
			memset(fs_map[index].pythonPath, 0, FS_PATH_MAX);
			fs_map[index].vfs_self = NULL;
			return 0;
		}
	}
	return -1;
}


char* Helios_lfs_get_letter_by_PYPath(const char *python_path) {
	int index = 0;
	for(index = 0; index <= 4; index++) {
		if(fs_map[index].is_used == 1 && python_path != NULL && strcmp(fs_map[index].pythonPath, python_path) == 0) {
			return fs_map[index].Letter;
		}
	}
	return NULL;
}

void* Helios_vfs_get_vfsobj_by_PYPath(const char *python_path) {
	int index = 0;
	
	for(index = 0; index <= 4; index++) {
		if(fs_map[index].is_used == 1 && python_path != NULL && (strcmp(fs_map[index].pythonPath, python_path) == 0)) {
			return fs_map[index].vfs_self;
		}
	}
	return NULL;
}

#endif
