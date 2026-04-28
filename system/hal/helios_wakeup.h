
#ifndef _HELIOS_WAKEUP_H
#define _HELIOS_WAKEUP_H

#include <stdint.h>
#include <stddef.h>
#include "helios_extint.h"
#include "helios_gpio.h"

typedef void (*ql_isr_callback)(void *arvg);
typedef void (*Helios_WakeupPad_Callback)(uint8_t level);


/**
 * GPIO interrupt debounce
 */


typedef enum
{
    HELIOS_WAKE_PULL_NONE = 0,
    HELIOS_WAKE_PULL_UP,
    HELIOS_WAKE_PULL_DOWN
}Helios_WAKE_PullMode;

typedef enum
{
    HELIOS_WAKEUP_1 = 1,
    HELIOS_WAKEUP_2,
    HELIOS_WAKEUP_3,
    HELIOS_WAKEUP_4,
    HELIOS_WAKEUP_5,
    HELIOS_WAKEUP_6,
    HELIOS_WAKEUP_7,
    HELIOS_WAKEUP_8,
    HELIOS_WAKEUP_9,
    HELIOS_WAKEUP_10,
    HELIOS_WAKEUP_11,
    HELIOS_WAKEUP_12,
    HELIOS_WAKEUP_13,
    HELIOS_WAKEUP_14,
    HELIOS_WAKEUP_15,
    HELIOS_WAKEUP_16,
    HELIOS_WAKEUP_17,
    HELIOS_WAKEUP_18,
    HELIOS_WAKEUP_19,
    HELIOS_WAKEUP_20,
    HELIOS_WAKEUP_21,
    HELIOS_WAKEUP_22,
    HELIOS_WAKEUP_23,
    HELIOS_WAKEUP_24,
    HELIOS_WAKEUP_25,
    HELIOS_WAKEUP_26,
    HELIOS_WAKEUP_27,
    HELIOS_WAKEUP_28,
    HELIOS_WAKEUP_29,
    HELIOS_WAKEUP_MAX,
}Helios_Wakeup_ID;


typedef struct 
{	
	Helios_WAKE_PullMode pull_mode;
	Helios_EdgeMode edge_mode;
}Helios_Wakeup_cfg_t;

typedef struct 
{	
	Helios_Wakeup_ID id;
	ql_isr_callback internal_cb;
	Helios_WakeupPad_Callback helios_cb;
}Helios_Wakeup_cb_t;



int Helios_Wakeup_Config(Helios_Wakeup_ID wakeup_id,Helios_Wakeup_cfg_t *cfg);
int Helios_Wakeup_Get_Pin_Value(Helios_Wakeup_ID wakeup_id);
int Helios_Wakeup_Disable(Helios_Wakeup_ID wakeup_id);
int Helios_Wakeup_Enable(Helios_Wakeup_ID wakeup_id);
int Helios_Wakeup_Deinit(Helios_Wakeup_ID wakeup_id);
int Helios_Wakeup_ReadWakePinvalue(Helios_Wakeup_ID wakeup_id);
int Helios_Wakeup_WakeTrip(Helios_Wakeup_ID wakeup_id);
int Helios_Wakeup_set_callback(Helios_Wakeup_ID wakeup_id, Helios_WakeupPad_Callback cb);

#endif

