#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

// #include "quec_ftm.h"

int helios_ftm_mode_switch(uint8_t mode);
int helios_ftm_mode_get(void);
int helios_ftm_test_start(uint16_t band, uint32_t tx_channel,uint8_t tx_power);
int helios_ftm_test_stop(void);