//  Add SPI LCD processing (felix 2022/07/19)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#if CONFIG_LCD

#include "helios_debug.h"
#include "helios_lcd.h"
#include "helios_spi.h"
#include "helios_pin.h"
#include "helios_gpio.h"
#include "qpy_lcd.h"
#include "helios_os.h"
#include "helios_fs.h"

Helios_Mutex_t spi_lcd_write_mutex = 0;
static uint16_t *lcd_write_buff = NULL;

static uint8_t fstn_invalid_type = 1;

#define QPY_LCD_LOG(msg, ...) custom_log("QPYlcd", msg, ##__VA_ARGS__)

#define XSTART_H 0xf0
#define XSTART_L 0xf1
#define YSTART_H 0xf2
#define YSTART_L 0xf3
#define XEND_H 0xE0
#define XEND_L 0xE1
#define YEND_H 0xE2
#define YEND_L 0xE3
#define LIGHT_VALUE 0xFE
#define XSTART 0xD0
#define XEND 0xD1
#define YSTART 0xD2
#define YEND 0xD3

extern int QPY_SPILCD_Clear(uint32_t color);
extern void Helios_msleep(uint32_t ms);

enum
{
    DATA_FORMAT_CHAR,
    DATA_FORMAT_SHORT,
};


int data_format = DATA_FORMAT_CHAR;


static QPY_LCDStruct_t QPY_LCDStruct = {0};

static LCD_INTERFACE LCD_Interface = INTERFACE_LCD;
static int QPY_SPILCD_Write_Cmd(void *buf, size_t len);
static int QPY_SPILCD_Write_Data(void *buf, size_t len);
static int QPY_SPILCD_Write_Data_Fstn(void *buf, size_t len);
static int QPY_SPILCD_Write_init_data(void *buf, size_t len);

#define CS_SET(x)                                                         \
    do                                                                    \
    {                                                                     \
        if (0 != Helios_GPIO_SetLevel(QPY_LCDStruct.spiInfo.CSPin, x)) \
        {                                                                 \
            QPY_LCD_LOG("gpio set fail\n");                            \
            return -1;                                                    \
        }                                                                 \
    } while (0)

#define WRITE_FUNCTION(x, y)                                                       \
    do                                                                             \
    {                                                                              \
        if (0 != QPY_LCDWriteFunction(x, y))                                    \
        {                                                                          \
            Helios_GPIO_SetLevel(QPY_LCDStruct.spiInfo.CSPin, HELIOS_LVL_HIGH); \
            QPY_LCD_LOG("lcd write func fail\n");                               \
            return -1;                                                             \
        }                                                                          \
    } while (0)

#define CHECK_INIT()                                      \
    do                                                    \
    {                                                     \
        if (QPY_LCDStruct.state != QPY_LCD_IS_INIT) \
        {                                                 \
            QPY_LCD_LOG("lcd is not init\n");          \
            return -1;                                    \
        }                                                 \
    } while (0)

static int QPY_LCD_InitDataHand(char *init_data, size_t length)
{
    uint32_t i = 0;

    if (init_data == NULL)
    {
        return -1;
    }
    char *data_temp = init_data;

    if (QPY_LCDStruct.recv_data.lcd_init_recv != NULL)
    {
        free(QPY_LCDStruct.recv_data.lcd_init_recv);
    }
    QPY_LCDStruct.recv_data.lcd_init_recv = calloc(1, sizeof(Helios_LCDWriteStruct) * length / 3);
    if (QPY_LCDStruct.recv_data.lcd_init_recv == NULL)
        return -1;

    Helios_LCDWriteStruct *lcd_data_recv = QPY_LCDStruct.recv_data.lcd_init_recv;

    int cur_temp = 0;
    for (i = 0; i < length;)
    {
        lcd_data_recv[cur_temp].type = data_temp[i++];
        lcd_data_recv[cur_temp].data_length = data_temp[i++];
        if (lcd_data_recv[cur_temp].data_length == 2 && lcd_data_recv[cur_temp].type == 1)
        {
            lcd_data_recv[cur_temp].value = data_temp[i++] << 8;
            lcd_data_recv[cur_temp].value |= data_temp[i++];
        }
        else
        {
            lcd_data_recv[cur_temp].value = data_temp[i++];
        }
        cur_temp++;
    }
    QPY_LCDStruct.recv_data.lcd_init_recv_cnt = cur_temp;
    return 0;
}

static int QPY_LCDInvalidDataHand(char *inavlid_data, size_t length)
{

    if (inavlid_data == NULL)
    {
        return -1;
    }

    char *invalid_data_temp = inavlid_data;

    if (QPY_LCDStruct.recv_data.lcd_invaild_recv != NULL)
    {
        free(QPY_LCDStruct.recv_data.lcd_invaild_recv);
    }
    QPY_LCDStruct.recv_data.lcd_invaild_recv = calloc(1, sizeof(Helios_LCDWriteStruct) * length / 3);
    if (QPY_LCDStruct.recv_data.lcd_invaild_recv == NULL)
        return -1;

    Helios_LCDWriteStruct *lcd_invaild_recv = QPY_LCDStruct.recv_data.lcd_invaild_recv;

    int invaid_cur_temp = 0;
    int j = 0;
    unsigned int i = 0;
    for (i = 0; i < length;)
    {
        lcd_invaild_recv[invaid_cur_temp].type = invalid_data_temp[i++];
        lcd_invaild_recv[invaid_cur_temp].data_length = invalid_data_temp[i++];
        if (lcd_invaild_recv[invaid_cur_temp].data_length == 2 && lcd_invaild_recv[invaid_cur_temp].type == 1)
        {
            switch (invalid_data_temp[i])
            {
            case XSTART:
                for (j = 0; j < 3; j++)
                {
                    if (QPY_LCDStruct.index.x_start_index[j] == 0)
                    {
                        QPY_LCDStruct.index.x_start_index[j] = invaid_cur_temp;
                        break;
                    }
                }
                break;
            case XEND:
                for (j = 0; j < 3; j++)
                {
                    if (QPY_LCDStruct.index.x_end_index[j] == 0)
                    {
                        QPY_LCDStruct.index.x_end_index[j] = invaid_cur_temp;
                        break;
                    }
                }

                break;
            case YSTART:
                for (j = 0; j < 3; j++)
                {
                    if (QPY_LCDStruct.index.y_start_index[j] == 0)
                    {
                        QPY_LCDStruct.index.y_start_index[j] = invaid_cur_temp;
                        break;
                    }
                }
                break;
            case YEND:
                for (j = 0; j < 3; j++)
                {
                    if (QPY_LCDStruct.index.y_end_index[j] == 0)
                    {
                        QPY_LCDStruct.index.y_end_index[j] = invaid_cur_temp;
                        break;
                    }
                }
                break;
            }
            i++;
            data_format = DATA_FORMAT_SHORT;
        }
        else if (lcd_invaild_recv[invaid_cur_temp].data_length == 1 && lcd_invaild_recv[invaid_cur_temp].type == 1)
        {
            data_format = DATA_FORMAT_CHAR;

            switch (invalid_data_temp[i])
            {
            case XSTART_H:
                QPY_LCDStruct.index.x_h_start_index = invaid_cur_temp;
                break;
            case XSTART_L:
                QPY_LCDStruct.index.x_l_start_index = invaid_cur_temp;
                break;
            case YSTART_H:
                QPY_LCDStruct.index.y_h_start_index = invaid_cur_temp;
                break;
            case YSTART_L:
                QPY_LCDStruct.index.y_l_start_index = invaid_cur_temp;
                break;
            case XEND_H:
                QPY_LCDStruct.index.x_h_end_index = invaid_cur_temp;
                break;
            case XEND_L:
                QPY_LCDStruct.index.x_l_end_index = invaid_cur_temp;
                break;
            case YEND_H:
                QPY_LCDStruct.index.y_h_end_index = invaid_cur_temp;
                break;
            case YEND_L:
                QPY_LCDStruct.index.y_l_end_index = invaid_cur_temp;
                break;
            }
            i++;
        }
        else
        {
            lcd_invaild_recv[invaid_cur_temp].value = invalid_data_temp[i++];
            if (HELIOS_LCD_TYPE_FSTN == QPY_LCDStruct.type && lcd_invaild_recv[invaid_cur_temp].value == 0xB4)
            {
                fstn_invalid_type = 2;
            }
        }
        invaid_cur_temp++;
    }

    QPY_LCDStruct.recv_data.lcd_invaild_recv_cnt = invaid_cur_temp;

    // QPY_LCD_LOG("data_format = %d\n", data_format);
    // QPY_LCD_LOG("%d %d %d %d %d %d %d %d\n", QPY_LCDStruct.index.x_h_start_index, QPY_LCDStruct.index.x_l_start_index,
    //                QPY_LCDStruct.index.y_h_start_index, QPY_LCDStruct.index.y_l_start_index, QPY_LCDStruct.index.x_h_end_index,
    //                QPY_LCDStruct.index.x_l_end_index, QPY_LCDStruct.index.y_h_end_index, QPY_LCDStruct.index.y_l_end_index);
    // QPY_LCD_LOG("%d %d %d %d %d %d\n", QPY_LCDStruct.index.x_start_index[0], QPY_LCDStruct.index.y_start_index[0],
    //                QPY_LCDStruct.index.x_end_index[0], QPY_LCDStruct.index.y_end_index[0], QPY_LCDStruct.index.x_start_index[1], QPY_LCDStruct.index.y_start_index[1]);
    // QPY_LCD_LOG("invaid_cur_temp = %d\n", invaid_cur_temp);
    return 0;
}

Helios_LCDWriteStruct *lcd_invaild_handle(unsigned int x_start, unsigned int y_start, unsigned int x_end, unsigned int y_end)
{
    int i = 0;
    Helios_LCDWriteStruct *lcd_invaild_recv = QPY_LCDStruct.recv_data.lcd_invaild_recv;
    uint8_t x_h_start_index = QPY_LCDStruct.index.x_h_start_index;
    uint8_t x_l_start_index = QPY_LCDStruct.index.x_l_start_index;
    uint8_t y_h_start_index = QPY_LCDStruct.index.y_h_start_index;
    uint8_t y_l_start_index = QPY_LCDStruct.index.y_l_start_index;

    uint8_t x_h_end_index = QPY_LCDStruct.index.x_h_end_index;
    uint8_t x_l_end_index = QPY_LCDStruct.index.x_l_end_index;
    uint8_t y_h_end_index = QPY_LCDStruct.index.y_h_end_index;
    uint8_t y_l_end_index = QPY_LCDStruct.index.y_l_end_index;

    uint32_t *x_start_index = QPY_LCDStruct.index.x_start_index;
    uint32_t *y_start_index = QPY_LCDStruct.index.y_start_index;
    uint32_t *x_end_index = QPY_LCDStruct.index.x_end_index;
    uint32_t *y_end_index = QPY_LCDStruct.index.y_end_index;

    if (lcd_invaild_recv == NULL)
    {
        return NULL;
    }
    if (data_format == DATA_FORMAT_CHAR)
    {
        if (x_h_start_index != 0)
            lcd_invaild_recv[x_h_start_index].value = (x_start >> 8) & 0xFF;
        if (x_l_start_index != 0)
            lcd_invaild_recv[x_l_start_index].value = x_start & 0xFF;

        if (y_h_start_index != 0)
            lcd_invaild_recv[y_h_start_index].value = (y_start >> 8) & 0xFF;
        if (y_l_start_index != 0)
            lcd_invaild_recv[y_l_start_index].value = y_start & 0xFF;

        if (x_h_end_index != 0)
            lcd_invaild_recv[x_h_end_index].value = (x_end >> 8) & 0xFF;
        if (x_l_end_index != 0)
            lcd_invaild_recv[x_l_end_index].value = x_end & 0xFF;

        if (y_h_end_index != 0)
            lcd_invaild_recv[y_h_end_index].value = (y_end >> 8) & 0xFF;
        if (y_l_end_index != 0)
            lcd_invaild_recv[y_l_end_index].value = y_end & 0xFF;
    }
    else if (data_format == DATA_FORMAT_SHORT)
    {

        for (i = 0; i < 3; i++)
        {
            if (x_start_index[i] != 0)
            {
                lcd_invaild_recv[x_start_index[i]].value = x_start;
            }
            else
            {
                break;
            }
        }
        for (i = 0; i < 3; i++)
        {
            if (y_start_index[i] != 0)
            {
                lcd_invaild_recv[y_start_index[i]].value = y_start;
            }
            else
            {
                break;
            }
        }
        for (i = 0; i < 3; i++)
        {
            if (x_end_index[i] != 0)
            {
                lcd_invaild_recv[x_end_index[i]].value = x_end;
            }
            else
            {
                break;
            }
        }
        for (i = 0; i < 3; i++)
        {
            if (y_end_index[i] != 0)
            {
                lcd_invaild_recv[y_end_index[i]].value = y_end;
            }
            else
            {
                break;
            }
        }
    }

    return lcd_invaild_recv;
}

static int QPY_LCDDisplayOnDataHand(char *displayon_data, size_t length)
{

    char *data_display_on_temp = displayon_data;
    if (QPY_LCDStruct.recv_data.lcd_display_on_recv != NULL)
    {
        free(QPY_LCDStruct.recv_data.lcd_display_on_recv);
        QPY_LCDStruct.recv_data.lcd_display_on_recv = NULL;
    }
    QPY_LCDStruct.recv_data.lcd_display_on_recv = calloc(1, sizeof(Helios_LCDWriteStruct) * (length / 3));
    if (QPY_LCDStruct.recv_data.lcd_display_on_recv == NULL)
    {
        return -3;
    }

    data_display_on_temp = displayon_data;
    Helios_LCDWriteStruct *lcd_display_on_recv = QPY_LCDStruct.recv_data.lcd_display_on_recv;
    int on_cur_temp = 0;
    unsigned int i = 0;
    for (i = 0; i < length;)
    {
        lcd_display_on_recv[on_cur_temp].type = data_display_on_temp[i++];
        lcd_display_on_recv[on_cur_temp].data_length = data_display_on_temp[i++];
        if (lcd_display_on_recv[on_cur_temp].data_length == 2 && lcd_display_on_recv[on_cur_temp].type == 1)
        {
            lcd_display_on_recv[on_cur_temp].value = data_display_on_temp[i++] << 8;
            lcd_display_on_recv[on_cur_temp].value |= data_display_on_temp[i++];
        }
        else
        {
            lcd_display_on_recv[on_cur_temp].value = data_display_on_temp[i++];
        }
        on_cur_temp++;
    }
    QPY_LCDStruct.recv_data.lcd_display_on_recv_cnt = on_cur_temp;
    return 0;
}

static int QPY_LCDDisplayOffDataHand(char *dispoff_data, size_t length)
{

    char *data_display_off_temp = dispoff_data;
    if (QPY_LCDStruct.recv_data.lcd_display_off_recv != NULL)
    {
        free(QPY_LCDStruct.recv_data.lcd_display_off_recv);
        QPY_LCDStruct.recv_data.lcd_display_off_recv = NULL;
    }
    QPY_LCDStruct.recv_data.lcd_display_off_recv = calloc(1, sizeof(Helios_LCDWriteStruct) * (length / 3));
    if (QPY_LCDStruct.recv_data.lcd_display_off_recv == NULL)
    {
        return -3;
    }

    data_display_off_temp = dispoff_data;

    Helios_LCDWriteStruct *lcd_display_off_recv = QPY_LCDStruct.recv_data.lcd_display_off_recv;
    int off_cur_temp = 0;
    unsigned int i = 0;
    for (i = 0; i < length;)
    {
        lcd_display_off_recv[off_cur_temp].type = data_display_off_temp[i++];
        lcd_display_off_recv[off_cur_temp].data_length = data_display_off_temp[i++];
        if (lcd_display_off_recv[off_cur_temp].data_length == 2 && lcd_display_off_recv[off_cur_temp].type == 1)
        {
            lcd_display_off_recv[off_cur_temp].value = data_display_off_temp[i++] << 8;
            lcd_display_off_recv[off_cur_temp].value |= data_display_off_temp[i++];
        }
        else
        {
            lcd_display_off_recv[off_cur_temp].value = data_display_off_temp[i++];
        }
        off_cur_temp++;
    }
    QPY_LCDStruct.recv_data.lcd_display_off_recv_cnt = off_cur_temp;
    return 0;
}

static int QPY_LCDLightDataHand(char *light_data, size_t length)
{

    char *data_display_light_temp = light_data;
    if (QPY_LCDStruct.recv_data.lcd_display_light_recv != NULL)
    {
        free(QPY_LCDStruct.recv_data.lcd_display_light_recv);
        QPY_LCDStruct.recv_data.lcd_display_light_recv = NULL;
    }
    QPY_LCDStruct.recv_data.lcd_display_light_recv = calloc(1, sizeof(Helios_LCDWriteStruct) * (length / 3));
    if (QPY_LCDStruct.recv_data.lcd_display_light_recv == NULL)
    {
        return -3;
    }

    data_display_light_temp = light_data;

    Helios_LCDWriteStruct *lcd_display_light_recv = QPY_LCDStruct.recv_data.lcd_display_light_recv;
    int light_cur_temp = 0;
    unsigned int i = 0;
    for (i = 0; i < length;)
    {
        lcd_display_light_recv[light_cur_temp].type = data_display_light_temp[i++];
        lcd_display_light_recv[light_cur_temp].data_length = data_display_light_temp[i++];
        if (data_display_light_temp[i] == LIGHT_VALUE)
        {
            QPY_LCDStruct.index.light_index = light_cur_temp;
        }
        if (lcd_display_light_recv[light_cur_temp].data_length == 2 && lcd_display_light_recv[light_cur_temp].type == 1)
        {
            lcd_display_light_recv[light_cur_temp].value = data_display_light_temp[i++] << 8;
            lcd_display_light_recv[light_cur_temp].value |= data_display_light_temp[i++];
        }
        else
        {
            lcd_display_light_recv[light_cur_temp].value = data_display_light_temp[i++];
        }
        light_cur_temp++;
    }
    QPY_LCDStruct.recv_data.lcd_display_light_cnt = light_cur_temp;
    return 0;
}

static int QPY_LCDWriteFunction(Helios_LCDWriteStruct *init_data, unsigned int length)
{
    unsigned int i = 0;
    unsigned char data_idx = 0;
    unsigned char data_length = 0;
    Helios_LCDWriteStruct *pdata = init_data;

    if (pdata == NULL || length == 0)
    {
        QPY_LCD_LOG("%s: %d: param is error!! \n", __FUNCTION__, __LINE__);
        return -1;
    }

    for (i = 0; i < length;)
    {
        i++;
        if (pdata->type == HELIOS_LCD_CMD)
        {
            QPY_SPILCD_Write_Cmd(&(pdata->value), 1);
            if (pdata->data_length > 0)
            {
                data_length = pdata->data_length;
                pdata++;
                for (data_idx = 0; (data_idx < data_length) && (i < length); data_idx++, i++)
                {
                    if (pdata->type != HELIOS_LCD_DATA)
                    {
                        QPY_LCD_LOG("%s: %d: SPI data is error[%u, %u], please check!!!!!!!! \n",
                                       __FUNCTION__, __LINE__, i, data_idx);
                        return -1;
                    }
                    else
                    {
                        QPY_SPILCD_Write_init_data(&(pdata->value), 1);
                        pdata++;
                    }
                }
            }
            else
            {
                pdata++;
            }
        }
        else if (pdata->type == HELIOS_LCD_DELAY)
        {
            // Helios_msleep(pdata->value);
            Helios_msleep(pdata->value);
            pdata++;
        }
        else
        {
            QPY_LCD_LOG("%s: %d: SPI data is error[%u, %u], please check!!!!!!!! \n",
                           __FUNCTION__, __LINE__, i, pdata->type);
            return -1;
        }
    }

    return 0;
}

static void Memory_release(void **Pointer)
{
    if (*Pointer != NULL)
    {
        free(*Pointer);
        *Pointer = NULL;
    }
}

static void QPY_LCDStruct_Free(QPY_LCDStruct_t *lcd_struct)
{
    Helios_SPI_Deinit(QPY_LCDStruct.spiInfo.spi_port);
    Helios_GPIO_Deinit(QPY_LCDStruct.spiInfo.CSPin);
    Helios_GPIO_Deinit(QPY_LCDStruct.spiInfo.DCPin);

    Memory_release((void *)&(lcd_struct->recv_data.lcd_init_recv));
    Memory_release((void *)&(lcd_struct->recv_data.lcd_invaild_recv));
    Memory_release((void *)&(lcd_struct->recv_data.lcd_display_on_recv));
    Memory_release((void *)&(lcd_struct->recv_data.lcd_display_off_recv));
    Memory_release((void *)&(lcd_struct->recv_data.lcd_display_light_recv));
    Memory_release((void *)&(lcd_struct->fstn_buff));

    memset((void *)lcd_struct, 0, sizeof(QPY_LCDStruct_t));
}

static int QPY_SPILCD_Write_Cmd(void *buf, size_t len)
{
    if (NULL == buf || len == 0)
        return -1;

    Helios_GPIO_SetLevel(QPY_LCDStruct.spiInfo.DCPin, HELIOS_LVL_LOW);

    if (0 != Helios_SPI_Write(QPY_LCDStruct.spiInfo.spi_port, buf, len))
    {
        QPY_LCD_LOG("write cmd fail\n");
        return -1;
    }

    Helios_GPIO_SetLevel(QPY_LCDStruct.spiInfo.DCPin, HELIOS_LVL_HIGH);
    return 0;
}

uint16_t Htons(uint16_t sHost)
{
	uint8_t* p = (uint8_t *)&sHost;
	uint8_t c = *p;
	*p = *(p + 1);
	*(p + 1) = c;
	return sHost;
}

static int QPY_SPILCD_Write_init_data(void *buf, size_t len)
{
    if (NULL == buf || len == 0)
        return -1;

    Helios_GPIO_SetLevel(QPY_LCDStruct.spiInfo.DCPin, HELIOS_LVL_HIGH);

    if (0 != Helios_SPI_Write(QPY_LCDStruct.spiInfo.spi_port, buf, len))
    {
        QPY_LCD_LOG("write data fail\n");
        return -1;
    }
    return 0;
}

static int QPY_SPILCD_Write_Data(void *buf, size_t len)
{
    if (NULL == buf || len == 0)
        return -1;

    Helios_GPIO_SetLevel(QPY_LCDStruct.spiInfo.DCPin, HELIOS_LVL_HIGH);
#if defined (PLAT_Unisoc) || defined(PLAT_Unisoc_8850) || defined(PLAT_Unisoc_8910_R05) || defined(PLAT_Unisoc_8850_R02) || defined(PLAT_Unisoc_8910_R06)
    if (0 != Helios_SPI_Write(QPY_LCDStruct.spiInfo.spi_port, buf, len))
    {
        QPY_LCD_LOG("write data fail\n");
        return -1;
    }
    return 0;
#else
    if(lcd_write_buff != NULL) {
		free(lcd_write_buff);
		lcd_write_buff = NULL;
	}
    uint16_t *ori_buf = (uint16_t *)buf;
    lcd_write_buff = calloc(1, len);

    unsigned int i;
    for(i = 0;i<(len/2);i++)
    {
        lcd_write_buff[i] = Htons(ori_buf[i]);
    }
    // QPY_LCD_LOG("%s: %d: len is %d-------------- \n",
                        //    __FUNCTION__, __LINE__, len);
    if (0 != Helios_SPI_Write(QPY_LCDStruct.spiInfo.spi_port, (void *)lcd_write_buff, len))
    {
        QPY_LCD_LOG("write data fail\n");
        return -1;
    }
    return 0;
#endif
}

static int QPY_SPILCD_Write_Data_Fstn(void *buf, size_t len)
{   
    if (NULL == buf || len == 0)
        return -1;
    // if(0 == spi_lcd_write_mutex) {
    //     spi_lcd_write_mutex = Helios_Mutex_Create();
    // }
    // Helios_Mutex_Lock(spi_lcd_write_mutex, HELIOS_WAIT_FOREVER);
    uint8_t reg1[] = {0x40};
    uint8_t reg2[8] = {0};
    uint8_t reg3[2] = {0};

    if (fstn_invalid_type == 1) 
    {
        uint8_t reg2_tmp[] = {0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7};
        uint8_t reg3_tmp[] = {0x10, 0x00};
        memcpy(reg2, reg2_tmp, sizeof(reg2_tmp));
        memcpy(reg3, reg3_tmp, sizeof(reg3_tmp));
    }
    //ka'er customer fstn
    else 
    {
        uint8_t reg2_tmp[] = {0xB4, 0xB5, 0xB6, 0xB7, 0xB0, 0xB1, 0xB2, 0xB3};
        uint8_t reg3_tmp[] = {0x10, 0x01};
        memcpy(reg2, reg2_tmp, sizeof(reg2_tmp));
        memcpy(reg3, reg3_tmp, sizeof(reg3_tmp));
    }
    uint8_t reg4[] = {0xAF};

    uint8_t i;
	for(i=0;i<8;i++)//每页地址�???bit，也就是控制纵坐标，8*8=64//8->4
	{
        Helios_GPIO_SetLevel(QPY_LCDStruct.spiInfo.DCPin, HELIOS_LVL_LOW);
        if (0 != Helios_SPI_Write(QPY_LCDStruct.spiInfo.spi_port, reg1, 1))
        {
            QPY_LCD_LOG("write data fail\n");
            // Helios_Mutex_Unlock(spi_lcd_write_mutex);
            return -1;
        }
        if (0 != Helios_SPI_Write(QPY_LCDStruct.spiInfo.spi_port, reg2+i, 1))   //页坐�???
        {
            QPY_LCD_LOG("write data fail\n");
            // Helios_Mutex_Unlock(spi_lcd_write_mutex);
            return -1;
        }
        if (0 != Helios_SPI_Write(QPY_LCDStruct.spiInfo.spi_port, reg3, 2))     //横坐�???
        {
            QPY_LCD_LOG("write data fail\n");
            // Helios_Mutex_Unlock(spi_lcd_write_mutex);
            return -1;
        }
        Helios_GPIO_SetLevel(QPY_LCDStruct.spiInfo.DCPin, HELIOS_LVL_HIGH);
        if (0 != Helios_SPI_Write(QPY_LCDStruct.spiInfo.spi_port, buf, QPY_LCDStruct.lcdInfo.width))
        {
            QPY_LCD_LOG("write data fail\n");
            // Helios_Mutex_Unlock(spi_lcd_write_mutex);
            return -1;
        }
        // QPY_LCD_LOG("%s: %d: i=%d,lcd width is %d-------------- \n",
                        //    __FUNCTION__, __LINE__, i, QPY_LCDStruct.lcdInfo.width);
        buf += QPY_LCDStruct.lcdInfo.width;
		
        // if (0 != Helios_SPI_Write(QPY_LCDStruct.spiInfo.spi_port, reg4, 1))     //Display ON
        // {
        //     QPY_LCD_LOG("write data fail\n");
        //     return -1;
        // }
	}
    // Helios_Mutex_Unlock(spi_lcd_write_mutex);
    return 0;
}

int QPY_SPILCD_Init(Helios_LCDInitStruct *init_data, QPY_LCDSPI_INFO spi_info)
{
    if (NULL == init_data)
    {
        QPY_LCD_LOG("init data is NULL\n");
        return -1;
    }

    if (QPY_LCDStruct.state == QPY_LCD_IS_INIT)
    {
        QPY_LCDStruct_Free(&QPY_LCDStruct);
    }

#if defined(BOARD_EC600UCN_LC) || defined(BOARD_EC600UCN_LC_EXTFS8M) || defined(BOARD_EC600UCN_LC_ZS)
    Helios_LCD_VDD_switch_on();
#endif

    memcpy(&QPY_LCDStruct.spiInfo, &spi_info, sizeof(QPY_LCDSPI_INFO));

    QPY_LCD_LOG("spi lcd init: spi[%d], clk[%d], mode[%d], CS[%d], dc[%d] rst[%d]\n", QPY_LCDStruct.spiInfo.spi_port,
                   QPY_LCDStruct.spiInfo.spiclk, QPY_LCDStruct.spiInfo.spimode, QPY_LCDStruct.spiInfo.CSPin, QPY_LCDStruct.spiInfo.DCPin, QPY_LCDStruct.spiInfo.RSTPin);

    QPY_LCDStruct.state = QPY_LCD_IS_INIT;
#if defined(PLAT_ASR_1606) || defined(PLAT_ASR_1609) || defined(PLAT_ASR_1602)
	if (0 != Helios_SPI_Init(QPY_LCDStruct.spiInfo.spi_port, QPY_LCDStruct.spiInfo.spimode, QPY_LCDStruct.spiInfo.spiclk, 0))
#else
    if (0 != Helios_SPI_Init(QPY_LCDStruct.spiInfo.spi_port, QPY_LCDStruct.spiInfo.spimode, QPY_LCDStruct.spiInfo.spiclk))
#endif
    {
        QPY_LCD_LOG("spi init fail\n");
        goto err;
    }

    Helios_GPIOInitStruct gpio_s = {0};
    gpio_s.dir = HELIOS_GPIO_OUTPUT;
    gpio_s.pull = HELIOS_PULL_UP;
    gpio_s.value = HELIOS_LVL_HIGH;

#if !defined(BOARD_EC600GCN_LA_CDD)
    if (0 != Helios_GPIO_Init(QPY_LCDStruct.spiInfo.CSPin, &gpio_s))
    {
        QPY_LCD_LOG("cs gpio init fail\n");
        goto err;
    }
#endif

    if (0 != Helios_GPIO_Init(QPY_LCDStruct.spiInfo.DCPin, &gpio_s))
    {
        QPY_LCD_LOG("cs gpio init fail\n");
        goto err;
    }

    if (0 != Helios_GPIO_Init(QPY_LCDStruct.spiInfo.RSTPin, &gpio_s))
    {
        QPY_LCD_LOG("cs gpio init fail\n");
        goto err;
    }

    QPY_LCDStruct.lcdInfo.width = init_data->width;
    QPY_LCDStruct.lcdInfo.hight = init_data->hight;
    QPY_LCDStruct.type = init_data->lcdtype;
    QPY_LCD_LOG("width[%d],hight[%d]\n", QPY_LCDStruct.lcdInfo.width, QPY_LCDStruct.lcdInfo.hight);

    if (HELIOS_LCD_TYPE_FSTN == QPY_LCDStruct.type)
    {
        QPY_LCDStruct.fstn_buff = calloc(1, QPY_LCDStruct.lcdInfo.width * QPY_LCDStruct.lcdInfo.hight / 8);
        if (NULL == QPY_LCDStruct.fstn_buff)
        {
            QPY_LCD_LOG("malloc[%d] fail\n", QPY_LCDStruct.lcdInfo.width * QPY_LCDStruct.lcdInfo.hight / 8);
            goto err;
        }
    }

    if (0 != QPY_LCD_InitDataHand(init_data->init_data, init_data->init_data_len))
    {
        goto err;
    }

    if (0 != QPY_LCDInvalidDataHand(init_data->invaild_data, init_data->invaild_data_len))
    {
        goto err;
    }

    if (0 != QPY_LCDDisplayOnDataHand(init_data->displayon_data, init_data->displayon_data_len))
    {
        QPY_LCD_LOG("displayon data is None\n");
    }

    if (0 != QPY_LCDDisplayOffDataHand(init_data->displayoff_data, init_data->displayoff_data_len))
    {
        QPY_LCD_LOG("displayoff data is None\n");
    }

    if (0 != QPY_LCDLightDataHand(init_data->light_level_data, init_data->light_level_data_len))
    {
        QPY_LCD_LOG("light data is None\n");
    }


    HeliosFILE *fp_e = Helios_fopen("E:/logo.bin","r");
	HeliosFILE *fp = Helios_fopen("U:/logo.bin","r");

 	if((fp_e == NULL && fp == NULL) || init_data->init_flag) //增加是否强制初始化的判断

	{  
        Helios_msleep(5);
        Helios_GPIO_SetLevel(QPY_LCDStruct.spiInfo.RSTPin, HELIOS_LVL_LOW);
        Helios_msleep(5);
        Helios_GPIO_SetLevel(QPY_LCDStruct.spiInfo.RSTPin, HELIOS_LVL_HIGH);
        Helios_msleep(5);

        Helios_GPIO_SetLevel(QPY_LCDStruct.spiInfo.CSPin, HELIOS_LVL_LOW);
        QPY_LCD_LOG("init data write begin\n");

        if (0 != QPY_LCDWriteFunction(QPY_LCDStruct.recv_data.lcd_init_recv, QPY_LCDStruct.recv_data.lcd_init_recv_cnt))
        {
            QPY_LCD_LOG("init data write error\n");
            Helios_GPIO_SetLevel(QPY_LCDStruct.spiInfo.CSPin, HELIOS_LVL_HIGH);
            goto err;
        }

    #if !CONFIG_POC
        if( QPY_SPILCD_Clear(0xffff) == -1 )
        {
            QPY_LCD_LOG("init clear error\n");
            Helios_GPIO_SetLevel(QPY_LCDStruct.spiInfo.CSPin, HELIOS_LVL_HIGH);
            goto err;
        }
    #endif
        Helios_GPIO_SetLevel(QPY_LCDStruct.spiInfo.CSPin, HELIOS_LVL_HIGH);
		
	} else {
        QPY_LCD_LOG("have logo.bin or don't enforce init LCD\n");
		if(fp_e) {
			Helios_fclose(fp_e);
		}
		if(fp) {
			Helios_fclose(fp);
		}
    }

    return 0;

err:
#if defined(BOARD_EC600UCN_LC) || defined(BOARD_EC600UCN_LC_EXTFS8M) 
    Helios_LCD_VDD_switch_off();
#endif
    QPY_LCDStruct_Free(&QPY_LCDStruct);
    QPY_LCDStruct.state = QPY_LCD_IS_UNINIT;
    return -1;
}

#if defined (PLAT_Unisoc) || defined(PLAT_Unisoc_8910_R05) || defined(PLAT_Unisoc_8850_R02) || defined(PLAT_Unisoc_8910_R06)
int QPY_SPILCD_Brightness(uint32_t light_level)
{
    return Helios_SPI_LCD_Brightness(light_level);
}
#else
int QPY_SPILCD_Brightness(uint32_t light_level)
{
    return 0;
}
#endif
static unsigned char *color_buf_fstn = NULL;
void RGB2fstn(void *buffer, uint32_t start_x, uint32_t start_y, uint32_t end_x, uint32_t end_y)
{
    uint32_t x = 0, y = 0;
    uint16_t *tmp = buffer;
    // unsigned char fstn = 0;
    unsigned char result;
    unsigned short r, g, b;

    if (QPY_LCDStruct.fstn_buff == NULL)
        return;

    color_buf_fstn = QPY_LCDStruct.fstn_buff;

    for (y = start_y; y <= end_y && y < QPY_LCDStruct.lcdInfo.hight; y++)
    {
        for (x = start_x; x <= end_x; x++)
        {
            // printf("%x,",tmp->full);
            r = (*tmp >> 11) & 0x1F;
            g = (*tmp >> 5) & 0x3F;
            b = *tmp & 0x1F;
            r = r * 0xFF / 0X1F;
            g = g * 0xFF / 0x3F;
            b = b * 0xFF / 0x3F;
            result = (unsigned char)((77 * r + 150 * g + 29 * b) >> 8);
            if (result > 128)
            {
                color_buf_fstn[x + (y / 8) * QPY_LCDStruct.lcdInfo.width] |= (1 << (y % 8));
            }
            else
            {
                color_buf_fstn[x + (y / 8) * QPY_LCDStruct.lcdInfo.width] &= ~(1 << (y % 8));
            }
            tmp++;
        }
    }
}

int QPY_SPILCD_Write(void *buffer, uint32_t start_x, uint32_t start_y, uint32_t end_x, uint32_t end_y)
{
    if(0 == spi_lcd_write_mutex) {
        spi_lcd_write_mutex = Helios_Mutex_Create();
    }
    Helios_Mutex_Lock(spi_lcd_write_mutex, HELIOS_WAIT_FOREVER);
    CHECK_INIT();
    int ret = 0;
    uint8_t end_tran = 0xAF;

    Helios_LCDWriteStruct *lcd_invaild_data = lcd_invaild_handle(start_x, start_y, end_x, end_y);
    if (lcd_invaild_data == NULL)
    {
        Helios_Mutex_Unlock(spi_lcd_write_mutex);
        return -1;
    }

    int count = QPY_LCDStruct.recv_data.lcd_invaild_recv_cnt;

#if !defined(BOARD_EC600GCN_LA_CDD)
    CS_SET(HELIOS_LVL_LOW);
#endif

    WRITE_FUNCTION(lcd_invaild_data, count);
    // QPY_LCD_LOG("%s: %d: lcd type is %d-------------- \n",__FUNCTION__, __LINE__, QPY_LCDStruct.type);
    if (HELIOS_LCD_TYPE_FSTN == QPY_LCDStruct.type)
    {
        // QPY_LCD_LOG("rgb2fstn start\n");
        RGB2fstn(buffer, start_x, start_y, end_x, end_y);
        // QPY_LCD_LOG("rgb2fstn end\n");
        ret = QPY_SPILCD_Write_Data_Fstn(QPY_LCDStruct.fstn_buff, QPY_LCDStruct.lcdInfo.width * QPY_LCDStruct.lcdInfo.hight / 8);
        QPY_SPILCD_Write_Cmd(&end_tran, 1);
    }
    else if ( HELIOS_LCD_TYPE_RGB666 == QPY_LCDStruct.type)
    {
        ret = QPY_SPILCD_Write_Data(buffer, (end_x - start_x + 1) * (end_y - start_y + 1) * 3);
    }
    else
    {
        ret = QPY_SPILCD_Write_Data(buffer, (end_x - start_x + 1) * (end_y - start_y + 1) * 2);
    }

    if (0 != ret)
    {
#if !defined(BOARD_EC600GCN_LA_CDD)
        CS_SET(HELIOS_LVL_HIGH);
#endif
        QPY_LCD_LOG("lcd write data fail\n");
        Helios_Mutex_Unlock(spi_lcd_write_mutex);
        return -1;
    }
#if !defined(BOARD_EC600GCN_LA_CDD)
    CS_SET(HELIOS_LVL_HIGH);
#endif
    Helios_Mutex_Unlock(spi_lcd_write_mutex);
    return 0;
}

int QPY_SPILCD_Display_on()
{
    CHECK_INIT();
#if !defined(BOARD_EC600GCN_LA_CDD)
    CS_SET(0);
#endif
    WRITE_FUNCTION(QPY_LCDStruct.recv_data.lcd_display_on_recv, QPY_LCDStruct.recv_data.lcd_display_on_recv_cnt);
#if !defined(BOARD_EC600GCN_LA_CDD)
    CS_SET(1);
#endif
    return 0;
}

int QPY_SPILCD_Display_off()
{
    CHECK_INIT();
#if !defined(BOARD_EC600GCN_LA_CDD)
    CS_SET(0);
#endif
    WRITE_FUNCTION(QPY_LCDStruct.recv_data.lcd_display_off_recv, QPY_LCDStruct.recv_data.lcd_display_off_recv_cnt);
#if !defined(BOARD_EC600GCN_LA_CDD)
    CS_SET(1);
#endif
    return 0;
}

int QPY_SPILCD_WriteCmd(uint64_t cmd, uint32_t data_len)
{
    CHECK_INIT();
    CS_SET(0);
    if (0 != QPY_SPILCD_Write_Cmd(&cmd, data_len))
    {
        CS_SET(1);
        return -1;
    }
    CS_SET(1);
    return 0;
}

int QPY_SPILCD_WriteData(uint64_t data, uint32_t data_len)
{
    CHECK_INIT();
    CS_SET(0);
    if (0 != QPY_SPILCD_Write_Data(&data, data_len))
    {
        CS_SET(1);
        return -1;
    }
    CS_SET(1);
    return 0;
}

int QPY_SPILCD_Clear(uint32_t color)
{

    if ( HELIOS_LCD_TYPE_RGB666 == QPY_LCDStruct.type)
    {
        uint8_t cRed = ((color >> 16) & 0xff);
        uint8_t cGreen = ((color  >> 8) & 0xff);
        uint8_t cBlue = (color & 0xff);

        // QPY_LCD_LOG("clearRed[0x%x]\n", cRed);
        // QPY_LCD_LOG("clearGreen[0x%x]\n", cGreen);
        // QPY_LCD_LOG("clearBlue[0x%x]\n", cBlue);
        uint8_t *buf = (uint8_t *)calloc(1, QPY_LCDStruct.lcdInfo.width * QPY_LCDStruct.lcdInfo.hight * 3);
        if (NULL == buf)
        {
            QPY_LCD_LOG("malloc[%d] fail\n", QPY_LCDStruct.lcdInfo.width * QPY_LCDStruct.lcdInfo.hight * 3);
            return -1;
        }
        uint32_t i = 0;
        for (i = 0; i < QPY_LCDStruct.lcdInfo.width * QPY_LCDStruct.lcdInfo.hight * 3; i += 3)
        {
            buf[i] = cRed;
            buf[i+1] = cGreen;
            buf[i+2] = cBlue;
        }
        QPY_SPILCD_Write(buf, 0, 0, QPY_LCDStruct.lcdInfo.width - 1, QPY_LCDStruct.lcdInfo.hight - 1);

        if (buf)
        {
            free(buf);
            buf = NULL;
        }
        return 0;
    }
    else
    {
    uint16_t color_tmp = color << 8;
    color_tmp |= (color >> 8);
    // QPY_LCD_LOG("clear[0x%x]\n", color_tmp);
    uint16_t *buf = (uint16_t *)calloc(1, QPY_LCDStruct.lcdInfo.width * QPY_LCDStruct.lcdInfo.hight * 2);
    if (NULL == buf)
    {
        QPY_LCD_LOG("malloc[%d] fail\n", QPY_LCDStruct.lcdInfo.width * QPY_LCDStruct.lcdInfo.hight * 2);
        return -1;
    }
    uint32_t i = 0;
    for (i = 0; i < QPY_LCDStruct.lcdInfo.width * QPY_LCDStruct.lcdInfo.hight; i++)
    {
        buf[i] = color_tmp;
    }

    QPY_SPILCD_Write(buf, 0, 0, QPY_LCDStruct.lcdInfo.width - 1, QPY_LCDStruct.lcdInfo.hight - 1);

    if (buf)
    {
        free(buf);
        buf = NULL;
    }
    return 0;
    }
}

int QPY_LCD_Set_Interface(LCD_INTERFACE type)
{
    LCD_Interface = type;
    return 0;
}

int QPY_LCD_Init(Helios_LCDInitStruct *init_data, QPY_LCDSPI_INFO spi_info)
{
    if (LCD_Interface == INTERFACE_SPI)
    {
        return QPY_SPILCD_Init(init_data, spi_info);
    }
    else
    {
        return Helios_LCD_Init(init_data);
    }
}
int QPY_LCD_Write(void *buffer, uint32_t start_x, uint32_t start_y, uint32_t end_x, uint32_t end_y)
{
    if (LCD_Interface == INTERFACE_SPI)
    {
        return QPY_SPILCD_Write(buffer, start_x, start_y, end_x, end_y);
    }
    else
    {
        return Helios_LCD_Write(buffer, start_x, start_y, end_x, end_y);
    }
}

int QPY_LCD_Display_on()
{
    if (LCD_Interface == INTERFACE_SPI)
    {
        return QPY_SPILCD_Display_on();
    }
    else
    {
        return Helios_LCD_Display_on();
    }
}

int QPY_LCD_Display_off()
{
    if (LCD_Interface == INTERFACE_SPI)
    {
        return QPY_SPILCD_Display_off();
    }
    else
    {
        return Helios_LCD_Display_off();
    }
}

int QPY_LCD_WriteCmd(uint64_t cmd, uint32_t data_len)
{
    if (LCD_Interface == INTERFACE_SPI)
    {
        return QPY_SPILCD_WriteCmd(cmd, data_len);
    }
    else
    {
        return Helios_LCD_WriteCmd(cmd, data_len);
    }
}

int QPY_LCD_WriteData(uint64_t data, uint32_t data_len)
{
    if (LCD_Interface == INTERFACE_SPI)
    {
        return QPY_SPILCD_WriteData(data, data_len);
    }
    else
    {
        return Helios_LCD_WriteData(data, data_len);
    }
}

int QPY_LCD_Clear(uint32_t color)
{
    if (LCD_Interface == INTERFACE_SPI)
    {
        return QPY_SPILCD_Clear(color);
    }
    else
    {
        return Helios_LCD_Clear((uint16_t) color);
    }
}

int QPY_LCD_Brightness(uint32_t light_level)
{
    if (LCD_Interface == INTERFACE_SPI)
    {
        return QPY_SPILCD_Brightness(light_level);
    }
    else
    {
        return Helios_LCD_Brightness(light_level);
    }
}

#endif