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

#ifndef _QPY_LCD_H
#define _QPY_LCD_H
 
#ifdef __cplusplus
 extern "C" {
#endif

//  Add SPI LCD processing (felix 2022/07/19)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "helios_debug.h"
#include "helios_lcd.h"
#include "helios_spi.h"
#include "helios_pin.h"
#include "helios_gpio.h"

typedef enum
{
    QPY_LCD_IS_UNINIT = 0,
    QPY_LCD_IS_INIT = 1,
} QPY_LCDState;

typedef struct
{
    uint32_t totol_count;
    uint32_t on_total_count;
    uint32_t off_total_count;
    uint32_t light_total_count;

    uint32_t light_index;

    uint32_t lcd_brightness_index;

    uint32_t x_start_index[3];
    uint32_t y_start_index[3];
    uint32_t x_end_index[3];
    uint32_t y_end_index[3];

    uint8_t x_h_start_index;
    uint8_t y_h_start_index;
    uint8_t x_h_end_index;
    uint8_t y_h_end_index;
    uint8_t x_l_start_index;
    uint8_t y_l_start_index;
    uint8_t x_l_end_index;
    uint8_t y_l_end_index;
} QPY_LCDIndexStruct;

typedef struct
{
    Helios_LCDWriteStruct *lcd_init_recv;
    uint32_t lcd_init_recv_cnt;
    Helios_LCDWriteStruct *lcd_invaild_recv;
    uint32_t lcd_invaild_recv_cnt;
    Helios_LCDWriteStruct *lcd_display_on_recv;
    uint32_t lcd_display_on_recv_cnt;
    Helios_LCDWriteStruct *lcd_display_off_recv;
    uint32_t lcd_display_off_recv_cnt;
    Helios_LCDWriteStruct *lcd_display_light_recv;
    uint32_t lcd_display_light_cnt;
} QPY_LCDDataRecvStruct;

typedef struct
{
    uint32_t width;
    uint32_t hight;

} QPY_LCDInfoStruct;

typedef struct
{
    QPY_LCDState state;
    QPY_LCDIndexStruct index;
    QPY_LCDDataRecvStruct recv_data;
    Helios_LCDType type;
    QPY_LCDSPI_INFO spiInfo;
    QPY_LCDInfoStruct lcdInfo;
    void *fstn_buff;
} QPY_LCDStruct_t;

int QPY_LCD_Set_Interface(LCD_INTERFACE type);
int QPY_LCD_Init(Helios_LCDInitStruct *init_data, QPY_LCDSPI_INFO spi_info);
int QPY_LCD_Write(void *buffer, uint32_t start_x, uint32_t start_y, uint32_t end_x, uint32_t end_y);
int QPY_LCD_Display_on();
int QPY_LCD_Display_off();
int QPY_LCD_WriteCmd(uint64_t cmd, uint32_t data_len);
int QPY_LCD_WriteData(uint64_t data, uint32_t data_len);
int QPY_LCD_Clear(uint32_t color);
int QPY_LCD_Brightness(uint32_t light_level);

#ifdef __cplusplus
 } /*"C" */
#endif
 
#endif