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


#ifndef _Helios_STK_H_
#define _Helios_STK_H_
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PROFILEBUF_LEN                      (34)
#define HELIOS_STK_MAX_MENU_ITEMS           (50)
#define HELIOS_STK_STRING_LENGTH_MAX        (512)
#define HELIOS_COMPONENT_STK                (0x9000)

#define HELIOS_SIM_ENVELOPE_MENU_SELECTION  (253)
#define HELIOS_TERMINATE_STK_SESSION        (254)

typedef void (*Helios_stk_callback_t)(uint8_t nSim, uint32_t ind_type, void *ctx);
typedef enum
{
    HELIOS_STK_BIP_CONFIG_MODE_DISABLE, /* will disable BIP function */
    HELIOS_STK_BIP_CONFIG_MODE_AUTO, /* When the specified cid is not available, find the available cid automatically, default value */
    HELIOS_STK_BIP_CONFIG_MODE_FIXED, /* When the specified cid is not available, BIP function is not useable */
}helios_stk_bip_config_mode_e;

typedef struct
{
    bool status_report;
    helios_stk_bip_config_mode_e mode; /* BIP cid mode */
    uint8_t cid; /* the cid used by BIP, start from 1, max is PROFILE_IDX_VOLTE_MAX or PROFILE_IDX_MAX */
} helios_stk_bip_config_s;


typedef enum
{
    HELIOS_STK_MODE_DISABLE, /**< disable STK functionality */
    HELIOS_STK_MODE_ENABLE   /**< enable STK functionality */
} helios_stk_mode_e;

typedef enum
{
    HELIOS_STK_ALPHABET_SET_GSM, /**< gsm */
    HELIOS_STK_ALPHABET_SET_UCS2 /**< ucs2 */
} helios_stk_alphabet_set_e;

typedef struct
{
    uint8_t profile_len;
    uint8_t profile_buf[PROFILEBUF_LEN+1];
} helios_stk_profile_s;
typedef struct
{
    uint16_t length; /**< Length of the text. */
    uint8_t *text;   /**< Text string. */
} helios_stk_string_s;

typedef struct
{
    uint8_t qualifier;                      /**< Qualifiers specific to the command */
    uint8_t num_items;                      /**< Number of items. */
    uint8_t item_id[HELIOS_STK_MAX_MENU_ITEMS+1]; /**< array list for items. */
    helios_stk_string_s title;                  /**< Title string. */
} helios_stk_setup_menu_s;

typedef struct
{
    uint8_t item_id;           /**< array list for items. */
    helios_stk_string_s item_text; /**< Title string. */
} helios_stk_item_s;


typedef struct
{
    uint8_t qualifier;                      /**< Qualifiers specific to the command */
    uint8_t num_items;                      /**< Number of items. */
    uint8_t item_id[HELIOS_STK_MAX_MENU_ITEMS+1]; /**< array list for items. */
    helios_stk_string_s title;                  /**< Title. */
} helios_stk_select_item_s;

typedef struct
{
    uint8_t qualifier;           /**< Qualifiers specific to the command */
    helios_stk_string_s text_string; /**< Title string. */
} helios_stk_setup_idle_mode_text_s;

typedef struct
{
    uint8_t qualifier;            /**< Qualifiers specific to the command */
    helios_stk_string_s text_string;  /**< Title string. */
} helios_stk_display_text_s;

typedef struct
{
    uint8_t qualifier;            /**< Qualifiers specific to the command */
    uint8_t minimum_user_input;   /**< Minimum number of user input. */
    uint8_t maximum_user_input;   /**< Maximum number of user input. */
    helios_stk_string_s text_string;  /**< Title string. */
    helios_stk_string_s default_text; /**< Default text. */
} helios_stk_get_input_s;

typedef struct
{
    uint8_t qualifier;            /**< Qualifiers specific to the command */
    helios_stk_string_s text_string;  /**< Title string. */
} helios_stk_get_inkey_s;


typedef struct
{
    uint8_t alpha2[2];
} helios_stk_iso6391_s;
typedef struct
{
    uint8_t qualifier;         /**< Qualifiers specific to the command */
    helios_stk_iso6391_s language; /**< language, each language code is a pair of alpha-numeric characters, defined in ISO 639 [29].  */
} helios_stk_language_notification_s;

typedef enum
{
    HELIOS_STK_TONE_DIAL_TONE                    = 0x01,
    HELIOS_STK_TONE_CALLED_SUBSCRIBER_BUSY       = 0x02,
    HELIOS_STK_TONE_CONGESTION                   = 0x03,
    HELIOS_STK_TONE_RADIO_PATH_ACKNOWLEDGE       = 0x04,
    HELIOS_STK_TONE_RADIO_PATH_NOT_AVAILABLE     = 0x05,
    HELIOS_STK_TONE_ERROR_OR_SPECIAL_INFORMATION = 0x06,
    HELIOS_STK_TONE_CALL_WAITING_TONE            = 0x07,
    HELIOS_STK_TONE_RINGING_TONE                 = 0x08,

    HELIOS_STK_TONE_GENERAL_BEEP                           = 0x10,
    HELIOS_STK_TONE_POSITIVE_ACKNOWLEDGEMENT_TONE          = 0x11,
    HELIOS_STK_TONE_NEGATIVE_ACKNOWLEDGEMENT_OR_ERROR_TONE = 0x12
} helios_stk_tone_e;

typedef struct
{
    uint8_t qualifier;     /**< Qualifiers specific to the command */
    helios_stk_tone_e tone;    /**< Standard supervisory tones */
    uint8_t duration_unit; /**< duration unit */
    uint8_t duration;      /**< the length of time for which the ME shall generate the tone, if the tone is continuous or repeatable. */
    helios_stk_string_s title; /**< Title string. */
} helios_stk_play_tone_s;

typedef enum
{
    HELIOS_STK_PROACTIVE_CMD_NONE                  = 0x00,
    HELIOS_STK_PROACTIVE_CMD_PLAY_TONE             = 0x20,
    HELIOS_STK_PROACTIVE_CMD_DISPLAY_TEXT          = 0x21,
    HELIOS_STK_PROACTIVE_CMD_GET_INKEY             = 0x22,
    HELIOS_STK_PROACTIVE_CMD_GET_INPUT             = 0x23,
    HELIOS_STK_PROACTIVE_CMD_SELECT_ITEM           = 0x24,
    HELIOS_STK_PROACTIVE_CMD_SETUP_MENU            = 0x25,
    HELIOS_STK_PROACTIVE_CMD_SETUP_IDLE_MODE_TEXT  = 0x28,
    HELIOS_STK_PROACTIVE_CMD_LANGUAGE_NOTIFICATION = 0x35,
} helios_stk_proactive_cmd_e;

typedef enum
{
    HELIOS_STK_PROACTIVE_CMD_AUTO_RSP_STATE     = 0x00, /* qstk is disabled, will reply proactive command automaticaly */
    HELIOS_STK_PROACTIVE_CMD_TERMINAL_RSP_STATE = 0x01, /* qstk is enabled, a proactive command needs to be handled or a SETUP MENU item can be selected */
    HELIOS_STK_PROACTIVE_CMD_WAIT_STATE         = 0x02  /* qstk is enabled, and a terminal response message has been sent to SIM, waiting for response */
} helios_stk_state_e;

typedef enum {
    HELIOS_STK_STK_PROACTIVE_CMD_IND    = 1 | (HELIOS_COMPONENT_STK<<16),
    HELIOS_STK_STK_NO_PROACTIVE_CMD_IND = 2 | (HELIOS_COMPONENT_STK<<16),
    HELIOS_STK_STK_TIMEOUT_IND          = 3 | (HELIOS_COMPONENT_STK<<16),
    HELIOS_STK_STK_SIM_LOST_IND         = 4 | (HELIOS_COMPONENT_STK<<16),
}helios_event_id_e;

int Helios_Stk_Get_Bip_Config(helios_stk_bip_config_s *config);
int Helios_Stk_Set_Bip_Config(const helios_stk_bip_config_s config);
int Helios_Stk_Register_Cb(Helios_stk_callback_t stk_cb);
int Helios_Stk_Cfg_Get(helios_stk_mode_e *stk_mode,helios_stk_alphabet_set_e *alphabet_type,uint16_t *auto_response_timeout);
int Helios_Stk_Cfg_Set(helios_stk_mode_e stk_mode,helios_stk_alphabet_set_e alphabet_type,uint16_t auto_response_timeout);
int Helios_Stk_Get_Terminal_Profile(uint8_t nSim, helios_stk_profile_s *profile_config);
int Helios_Stk_Acquire_Setup_Menu_Info(uint8_t nSim, helios_stk_setup_menu_s *menu_info,helios_stk_alphabet_set_e alphabet);
int Helios_Stk_Acquire_Setup_Menu_Item_List(uint8_t nSim,uint8_t item_identifler,helios_stk_item_s *info,helios_stk_alphabet_set_e alphabet);
int Helios_Stk_Acquire_Sub_Menu_Info(uint8_t nSim,helios_stk_select_item_s *sub_menu_info,helios_stk_alphabet_set_e alphabet);
int Helios_Stk_Acquire_Sub_Menu_Item_List(uint8_t nSim,uint8_t item_identifler,helios_stk_item_s *info,helios_stk_alphabet_set_e alphabet);
int Helios_Stk_Acquire_Display_Text_Info(uint8_t nSim,helios_stk_display_text_s *display_text,helios_stk_alphabet_set_e alphabet);
int Helios_Stk_Acquire_Get_Input_Info(uint8_t nSim,helios_stk_get_input_s *input_info,helios_stk_alphabet_set_e alphabet);
int Helios_Stk_Acquire_Get_Inkey_Info(uint8_t nSim,helios_stk_get_inkey_s *inkey_info,helios_stk_alphabet_set_e alphabet);
int Helios_Stk_Acquire_Setup_Idle_Mode_Text_Info(uint8_t nSim,helios_stk_setup_idle_mode_text_s * inkey_info,helios_stk_alphabet_set_e alphabet);
int Helios_Stk_Acquire_Language_Notification_Info(uint8_t nSim,helios_stk_language_notification_s * notification_info);
int Helios_Stk_Acquire_Play_Tone_Info(uint8_t nSim,helios_stk_play_tone_s *tone_info,helios_stk_alphabet_set_e alphabet);
int Helios_Stk_Send_Command_Result(uint8_t nSim,uint8_t stk_cmd_id,uint8_t result,uint8_t item_id,helios_stk_string_s *res_string);
int Helios_Stk_Get_Stk_Proactive_Cmd(uint8_t nSim,helios_stk_proactive_cmd_e *ret_cmd,helios_stk_state_e *ret_state);


#endif