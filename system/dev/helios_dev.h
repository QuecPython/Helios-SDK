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


#ifndef _HELIOS_DEV_H_
#define _HELIOS_DEV_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef enum
{
    HELIOS_DEV_MODEM_FUN_MIN = 0,
    HELIOS_DEV_MODEM_FUN_FULL,
    HELIOS_DEV_MODEM_FUN_DISABLE_RX_RF_CIRCUITS = 3,
    HELIOS_DEV_MODEM_FUN_DISABLE_TX_RX_RF_CIRCUITS,
    HELIOS_DEV_MODEM_FUN_DISABLE_SIM, 
    HELIOS_DEV_MODEM_FUN_TURN_OFF_FULL_SECONDARY_RX
} Helios_DevModemFunction;

int Helios_Dev_GetQpyVersion(char *buffer, size_t len);
int Helios_Dev_GetModel(void *buffer, size_t len);
int Helios_Dev_GetProductName(void *buffer, size_t len);
int Helios_Dev_GetPID(void *buffer, size_t len);
int Helios_Dev_GetFwVersion(void *buffer, size_t len);
int Helios_Dev_GetIMEI(void *buffer, size_t len, uint8_t sim_id);
int Helios_Dev_GetSN(void *buffer, size_t len, uint8_t sim_id);
int Helios_Dev_SetModemFunction(Helios_DevModemFunction modem_fun, bool reset, uint8_t sim_id);
int Helios_Dev_GetModemFunction(Helios_DevModemFunction *modem_fun_ptr, uint8_t sim_id);

#if defined(PLAT_ECR6600) || defined(PLAT_aic8800m40)
int Helios_Dev_GetMAC(void *buffer, size_t len);
#endif

#if defined (PLAT_ASR) || defined(PLAT_ASR_1606) || defined(PLAT_ASR_1609) || defined(PLAT_ASR_1602)
int Helios_Dev_IncreaseCoreVoltage(void);
#endif

#if defined (PLAT_Qualcomm)
typedef struct
{
	int32_t backup_valid;
	int32_t backup_cnt;
	int32_t restore_cnt;
}Helios_DevBackupStatusStruct;

int Helios_Dev_Backup();
int Helios_Dev_Backup_Status(Helios_DevBackupStatusStruct *backupStatus);
#endif

#endif
