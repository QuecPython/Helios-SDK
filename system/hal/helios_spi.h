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

/**
 @file	Helios_spi.h
 @brief	Data type definition for SPI.
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
2021/03/29  Felix.Ye	Create.
**************************************************************************/

#ifndef _HELIOS_SPI_H
#define _HELIOS_SPI_H

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Uniform SPI channel interface to the PY layer
 */
typedef enum {
	HELIOS_SPI0 = 0,
	HELIOS_SPI1,
	HELIOS_SPI2,
	HELIOS_SPI3,
}Helios_SPINum;

/**
 * spi mode
 * 0 : CPOL=0, CPHA=0
 * 1 : CPOL=0, CPHA=1
 * 2 : CPOL=1, CPHA=0
 * 3 : CPOL=1, CPHA=1
 */
typedef enum {
	HELIOS_SPIMODE0 = 0,
	HELIOS_SPIMODE1,
	HELIOS_SPIMODE2,
	HELIOS_SPIMODE3,
}Helios_SPIMode;


/**
 * The PY layer and the Adapter layer interface transform 
 */
typedef struct {
	Helios_SPINum export_spi_no;
	uint32_t internal_spi_no;
}Helios_SPIMap;


/**
 * @brief:
 *      spi init
 *
 * @param:
 *      \port    [in]      - spi channel number
 *      \spimode [in]      - spi mode   (0:CPOL=0,CPHA=0 1:CPOL=0,CPHA=1 2:CPOL=1,CPHA=0 3:CPOL=1,CPHA=1)
 *      \spiclk  [in]      - spi clock  (-1:invalid 0:812.5kHz 1:1.625MHz 2:3.25MHz 3:6.5MHz 4:13MHz 5:26MHz 6:52MHz)							
 * @return:
 *      spi init Result, 0 for success,-1 for failure
 */
#if defined(PLAT_ASR_1606) || defined(PLAT_ASR_1609) ||defined(PLAT_ASR_1602)
int Helios_SPI_Init(Helios_SPINum spi_port, Helios_SPIMode spimode, uint32_t spiclk,unsigned char group);
#else
int Helios_SPI_Init(Helios_SPINum spi_port, Helios_SPIMode spimode, uint32_t spiclk);
#endif
/**
 * @brief:
 *      spi deinit
 *
 * @param:
 *      \port    [in]      - spi channel number
 * @return:
 *      spi deinit Result, 0 for success,-1 for failure
 */
int Helios_SPI_Deinit(Helios_SPINum spi_port);



/**
 * @brief:
 *      write and read spi
 *
 * @param:
 *      \port    [in]    - spi channel number
 *      \inbuf   [in]    - data write to the spi bus
 *      \inlen   [in]    - the length of data write to the spi bus
 *      \outbuf  [out]   - data read from the spi bus
 *      \outlen  [in]    - the length of the data read                 
 *
 * @return:
 *      spi write and read result,0 for success,-1 for failure
 */
int Helios_SPI_WriteRead(Helios_SPINum spi_port,void *inbuf,size_t inlen,void *outbuf, size_t outlen);


/**
 * @brief:
 *      write data to spi
 *
 * @param:
 *      \port [in]      - spi channel number
 *      \buf  [in]      - data write to the spi bus
 *      \len  [in]      - the length of data write to the spi bus
 *                   
 * @return:
 *      spi write result,0 for success,-1 for failure
 */
int Helios_SPI_Write(Helios_SPINum spi_port, void *buf, size_t len);


/**
 * @brief:
 *      read data from spi
 *
 * @param:
 *      \port [in]       - spi channel number
 *      \buf  [out]      - data read from the spi bus
 *      \len  [in]       - the length of the data read
 *                    
 *
 * @return:
 *      read spi data result, 0 for success,-1 for failure
 */
int Helios_SPI_Read(Helios_SPINum spi_port, void *buf, size_t len);


#if defined (PLAT_Unisoc) || defined(PLAT_Unisoc_8910_R05) || defined(PLAT_Unisoc_8910_R06)

typedef void (*helios_spi_callback_t)( Helios_SPINum port,unsigned int dma_done_event);

int Helios_SPI_Set_Callback(Helios_SPINum spi_port, helios_spi_callback_t cb);

int Helios_SPI_Init_Dma(Helios_SPINum spi_port, Helios_SPIMode spimode, uint32_t spiclk);

#endif

#if defined(PLAT_ASR_1606) || defined(PLAT_ASR_1609) || defined(PLAT_ASR_1602)

typedef void (*helios_spi_callback_t)( Helios_SPINum port,unsigned int dma_done_event);

int Helios_SPI_Set_Callback(Helios_SPINum spi_port, helios_spi_callback_t cb);

int Helios_SPI_Init_Dma(Helios_SPINum spi_port, Helios_SPIMode spimode, uint32_t spiclk);

#endif

#if defined (PLAT_ASR) || defined(PLAT_ASR_1606) || defined(PLAT_ASR_1609) || defined(PLAT_ASR_1602)//add  1603spi  fifo  20230228;1606spi  fifo  20230511
int Helios_SPI_Transfer_Pio(Helios_SPINum spi_port,void *inbuf,size_t inlen,void *outbuf, size_t outlen);
int Helios_SPI_Read_Fifo(Helios_SPINum spi_port, void *buf, size_t len); 
int Helios_SPI_Write_Fifo(Helios_SPINum spi_port, void *buf, size_t len); 
#endif

#ifdef __cplusplus
} /*"C" */
#endif

#endif



