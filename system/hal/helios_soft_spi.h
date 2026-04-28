#ifndef __HELIOS_SOFT_SPI__
#define __HELIOS_SOFT_SPI__
#include "helios_gpio.h"
#include "helios_pin.h"
#include "helios_spi.h"
typedef enum
{
    SPI_3WIRE,
    SPI_4WIRE
}SPI_WIRE_CNT_T;

typedef struct
{
	SPI_WIRE_CNT_T wire_cnt;
	Helios_GPIONum gpio_cs;
	Helios_GPIONum gpio_clk;
	Helios_GPIONum gpio_mosi;
	Helios_GPIONum gpio_miso;
	uint32_t delay;
	Helios_LvlMode lvl_cs_active;
	Helios_SPIMode mode;
}cfg_data;


extern void helios_spi_write_read_bytes(cfg_data* data,uint8_t *write_data,uint8_t *read_data,uint32_t len);
extern int helios_soft_spi_init(cfg_data* data);
extern int spi_write_bytes_3wire
(
	cfg_data *data,
	uint8_t* writedata,
	uint32_t writelen
);
extern int spi_read_bytes_3wire
(
	cfg_data *data,
	uint8_t* readdata,
	uint32_t readlen
);
extern int spi_write_read_bytes_3wire
(
	cfg_data *data,
	uint8_t* writedata,
	uint32_t writelen,
	uint8_t* readdata,
	uint32_t readlen
);

#endif

