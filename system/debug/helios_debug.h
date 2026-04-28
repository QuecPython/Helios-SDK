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


#ifndef _HELIOS_DEBUG_H_
#define _HELIOS_DEBUG_H_

#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>

void Helios_Debug_Enable(void);
void Helios_Debug_Disable(void);
int Helios_Debug_Output(const char *fmt, ...);
void Helios_Assert(const char      *cond, const char *file, int line, const char* fmt, ...);
#if defined(PLAT_RDA)
int Helios_Debug_Trace(char * data,unsigned int len);
#endif

#if CONFIG_POC_SLPOC
void Helios_USB_Log_Enable(void);
#endif

#if defined(PLAT_Unisoc_8850_R02)
int Helios_Debug_PCM_Data_Dump_Log_Set(uint8_t enable);
#endif

#if defined(BOARD_EC600MCN_CC_EXT) || defined(BOARD_EC600MCN_LF_SLPOC) || defined(BOARD_EC600MCN_CC_EXT_TTS) \
    || defined(BOARD_EC800MCN_CC_TTS) || defined(BOARD_EC800KCN_CC_TTS) || defined(BOARD_EC600KCN_CC_TTS)
#define helios_debug(fmt, ...)
#define custom_log(tag, fmt, ...)
#else
#if !defined(PLAT_RDA)
#define helios_debug(fmt, ...) Helios_Debug_Output("[%s, L%d]" fmt "", __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define custom_log(tag, fmt, ...) Helios_Debug_Output("["#tag"][%s, L%d]" fmt "", __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
// burols.wang add because RDA platform no more app rom. 2023/01/29
#define helios_debug(fmt, ...) Helios_Debug_Output(fmt"",##__VA_ARGS__)
#define custom_log(tag, fmt, ...) Helios_Debug_Output(fmt"", ##__VA_ARGS__)
#endif
#endif
#endif
