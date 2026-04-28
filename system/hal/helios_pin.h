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
 @file	helios_gpio.h
 @brief	Data type definition for GPIO.
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

#ifndef _HELIOS_PIN_H
#define _HELIOS_PIN_H

#ifdef __cplusplus
extern "C" {
#endif

#define BOOST_PP_REPEAT_1(c, m) BOOST_PP_REPEAT_1_I(c, m)
#define BOOST_PP_REPEAT_1_I(c, m) BOOST_PP_REPEAT_1_ ## c(m)
//#define BOOST_PP_REPEAT_1_0(m)
#define BOOST_PP_REPEAT_1_1(m) m(1)
#define BOOST_PP_REPEAT_1_2(m) BOOST_PP_REPEAT_1_1(m), m(2)
#define BOOST_PP_REPEAT_1_3(m) BOOST_PP_REPEAT_1_2(m), m(3)
#define BOOST_PP_REPEAT_1_4(m) BOOST_PP_REPEAT_1_3(m), m(4)
#define BOOST_PP_REPEAT_1_5(m) BOOST_PP_REPEAT_1_4(m), m(5)
#define BOOST_PP_REPEAT_1_6(m) BOOST_PP_REPEAT_1_5(m), m(6)
#define BOOST_PP_REPEAT_1_7(m) BOOST_PP_REPEAT_1_6(m), m(7)
#define BOOST_PP_REPEAT_1_8(m) BOOST_PP_REPEAT_1_7(m), m(8)
#define BOOST_PP_REPEAT_1_9(m) BOOST_PP_REPEAT_1_8(m), m(9)
#define BOOST_PP_REPEAT_1_10(m) BOOST_PP_REPEAT_1_9(m), m(10)
#define BOOST_PP_REPEAT_1_11(m) BOOST_PP_REPEAT_1_10(m), m(11)
#define BOOST_PP_REPEAT_1_12(m) BOOST_PP_REPEAT_1_11(m), m(12)
#define BOOST_PP_REPEAT_1_13(m) BOOST_PP_REPEAT_1_12(m), m(13)
#define BOOST_PP_REPEAT_1_14(m) BOOST_PP_REPEAT_1_13(m), m(14)
#define BOOST_PP_REPEAT_1_15(m) BOOST_PP_REPEAT_1_14(m), m(15)
#define BOOST_PP_REPEAT_1_16(m) BOOST_PP_REPEAT_1_15(m), m(16)
#define BOOST_PP_REPEAT_1_17(m) BOOST_PP_REPEAT_1_16(m), m(17)
#define BOOST_PP_REPEAT_1_18(m) BOOST_PP_REPEAT_1_17(m), m(18)
#define BOOST_PP_REPEAT_1_19(m) BOOST_PP_REPEAT_1_18(m), m(19)
#define BOOST_PP_REPEAT_1_20(m) BOOST_PP_REPEAT_1_19(m), m(20)
#define BOOST_PP_REPEAT_1_21(m) BOOST_PP_REPEAT_1_20(m), m(21)
#define BOOST_PP_REPEAT_1_22(m) BOOST_PP_REPEAT_1_21(m), m(22)
#define BOOST_PP_REPEAT_1_23(m) BOOST_PP_REPEAT_1_22(m), m(23)
#define BOOST_PP_REPEAT_1_24(m) BOOST_PP_REPEAT_1_23(m), m(24)
#define BOOST_PP_REPEAT_1_25(m) BOOST_PP_REPEAT_1_24(m), m(25)
#define BOOST_PP_REPEAT_1_26(m) BOOST_PP_REPEAT_1_25(m), m(26)
#define BOOST_PP_REPEAT_1_27(m) BOOST_PP_REPEAT_1_26(m), m(27)
#define BOOST_PP_REPEAT_1_28(m) BOOST_PP_REPEAT_1_27(m), m(28)
#define BOOST_PP_REPEAT_1_29(m) BOOST_PP_REPEAT_1_28(m), m(29)
#define BOOST_PP_REPEAT_1_30(m) BOOST_PP_REPEAT_1_29(m), m(30)
#define BOOST_PP_REPEAT_1_31(m) BOOST_PP_REPEAT_1_30(m), m(31)
#define BOOST_PP_REPEAT_1_32(m) BOOST_PP_REPEAT_1_31(m), m(32)
#define BOOST_PP_REPEAT_1_33(m) BOOST_PP_REPEAT_1_32(m), m(33)
#define BOOST_PP_REPEAT_1_34(m) BOOST_PP_REPEAT_1_33(m), m(34)
#define BOOST_PP_REPEAT_1_35(m) BOOST_PP_REPEAT_1_34(m), m(35)
#define BOOST_PP_REPEAT_1_36(m) BOOST_PP_REPEAT_1_35(m), m(36)
#define BOOST_PP_REPEAT_1_37(m) BOOST_PP_REPEAT_1_36(m), m(37)
#define BOOST_PP_REPEAT_1_38(m) BOOST_PP_REPEAT_1_37(m), m(38)
#define BOOST_PP_REPEAT_1_39(m) BOOST_PP_REPEAT_1_38(m), m(39)
#define BOOST_PP_REPEAT_1_40(m) BOOST_PP_REPEAT_1_39(m), m(40)
#define BOOST_PP_REPEAT_1_41(m) BOOST_PP_REPEAT_1_40(m), m(41)
#define BOOST_PP_REPEAT_1_42(m) BOOST_PP_REPEAT_1_41(m), m(42)
#define BOOST_PP_REPEAT_1_43(m) BOOST_PP_REPEAT_1_42(m), m(43)
#define BOOST_PP_REPEAT_1_44(m) BOOST_PP_REPEAT_1_43(m), m(44)
#define BOOST_PP_REPEAT_1_45(m) BOOST_PP_REPEAT_1_44(m), m(45)
#define BOOST_PP_REPEAT_1_46(m) BOOST_PP_REPEAT_1_45(m), m(46)
#define BOOST_PP_REPEAT_1_47(m) BOOST_PP_REPEAT_1_46(m), m(47)
#define BOOST_PP_REPEAT_1_48(m) BOOST_PP_REPEAT_1_47(m), m(48)
#define BOOST_PP_REPEAT_1_49(m) BOOST_PP_REPEAT_1_48(m), m(49)
#define BOOST_PP_REPEAT_1_50(m) BOOST_PP_REPEAT_1_49(m), m(50)




#define GPIO_MAP_DEF(n) { MP_ROM_QSTR(MP_QSTR_GPIO##n), MP_ROM_INT(HELIOS_GPIO##n) }
#define PLAT_GPIO_DEF(n) BOOST_PP_REPEAT_1(n,GPIO_MAP_DEF)



#define GPIO_HELIOS_DEF(n) HELIOS_GPIO##n
#define PLAT_GPIO_HELIOS_DEF(n) BOOST_PP_REPEAT_1(n,GPIO_HELIOS_DEF)

#define EXTERNAL_GPIO_DEF(n) GPIO##n
#define EXTERNAL_PLAT_GPIO_DEF(n) BOOST_PP_REPEAT_1(n,EXTERNAL_GPIO_DEF)



#if defined(PLAT_Qualcomm)
#if defined(BOARD_BG95M1) || defined(BOARD_BG95M2) || defined(BOARD_BG95M3) || defined(BOARD_BG95M6) \
 || defined(BOARD_BG95M8) || defined(BOARD_BG95M9) || defined(BOARD_BG95M3_LX) || defined(BOARD_BG95M8_SANX)
#define PLAT_GPIO_NUM 30
#elif defined(BOARD_BG77)
#define PLAT_GPIO_NUM 43
#elif defined(BOARD_BG600LM3)
#define PLAT_GPIO_NUM 25
#else
#error "Please confirm the Qualcomm platform"
#endif
#elif defined(PLAT_ASR)
#if defined(BOARD_EC800NCN_LA)
#define PLAT_GPIO_NUM 37
#elif defined(BOARD_EG915NEU_AC) || defined(BOARD_EG915NEU_AG) || defined(BOARD_EG915NEA_AC) || defined(BOARD_EG915NEA_AC_SANX)\
   || defined(BOARD_EG915NEU_AP)
#define PLAT_GPIO_NUM 41
#elif defined(BOARD_EC100YCN_AA)
#define PLAT_GPIO_NUM 20
#elif defined(BOARD_EG912NEN_AA) || defined(BOARD_EG912NEN_AA_SANX)
#define PLAT_GPIO_NUM 40
#elif defined(BOARD_EC200NCN_AA) || defined(BOARD_EC200NCN_AC) || defined(BOARD_EC200NCN_LA)
#define PLAT_GPIO_NUM 46
#else
#define PLAT_GPIO_NUM 41
#endif

#elif defined(PLAT_RDA)
#if defined(BOARD_BC32RA) || defined(BOARD_BC92RB)
#define PLAT_GPIO_NUM 11
#else
#define PLAT_GPIO_NUM 18
#endif


#elif defined(PLAT_Unisoc) || defined(PLAT_Unisoc_8910_R05) || defined(PLAT_Unisoc_8910_R06)
#if (defined(BOARD_EC600UCN_LB_TTS)	\
	|| defined(BOARD_EC600UCN_LB)	\
	|| defined(BOARD_EC600UCN_LC)	\
	|| defined(BOARD_EC600UCN_LC_ZS)	\
	|| defined(BOARD_EC600UCN_LC_EXTFS8M)	\
	|| defined(BOARD_EC600UEU_AB)	\
	|| defined(BOARD_EC600UEU_AB_POC)	\
	|| defined(BOARD_EC600UCN_LB_VOLTE)	\
	|| defined(BOARD_EC600UEU_AB_VOLTE)	\
	|| defined(BOARD_EC600UCN_LB_AP)	\
	|| defined(BOARD_EC600UCN_LB_ICC)	\
	|| defined(BOARD_EC600UCN_LB_EXTFS4M)	\
	|| defined(BOARD_EC600UCN_LB_EXTFS8M)	\
	|| defined(BOARD_EC600UCN_LB_QIOT)	\
	|| defined(BOARD_EC600UCN_LB_BT) \
	|| defined(BOARD_EC600UCN_LB_YDWL) \
	|| defined(BOARD_EC600UEC_AC) \
	|| defined(BOARD_EC600UEC_DC) \
	|| defined(BOARD_EC600UEC_AD) \
	|| defined(BOARD_EC600UEC_AC_WS) \
	|| defined(BOARD_EC600UEC_AD_WS) \
	|| defined(BOARD_EC600UEC_AC_VOLTE)) \
	|| defined(BOARD_EC600ULA_AC) \
	|| defined(BOARD_EC600ULA_AC_WS) \
	|| defined(BOARD_EC600UEU_AC_VOLTE) \
	|| defined(BOARD_EC600UEU_AC_WS) \
	|| defined(BOARD_EC600UEC_DC_WS) \
	|| defined(BOARD_EC600UEU_DC)
#define PLAT_GPIO_NUM 47
#elif (defined(BOARD_EC200UCN_AA) \
	|| defined(BOARD_EC200UCN_LA) \
	|| defined(BOARD_EC200UCN_LA_BT) \
	|| defined(BOARD_EC200UCN_LA_EXTFS8M) \
	|| defined(BOARD_EC200UCN_LB) \
	|| defined(BOARD_EC200UCN_LB_BT) \
	|| defined(BOARD_EC200UCN_LB_EXTFS8M) \
	|| defined(BOARD_EC200UEU_AB) \
	|| defined(BOARD_EC200UEU_AB_VOLTE) \
	|| defined(BOARD_EC200UEU_AB_SANX) \
	|| defined(BOARD_EC200UEU_AA) \
	|| defined(BOARD_EC200UEU_AA_CAM) \
	|| defined(BOARD_EC200UEU_AA_BTLVGL) \
	|| defined(BOARD_EC200UEU_AA_QIOT) \
	|| defined(BOARD_EC200UEU_AA_EXTFS) \
	|| defined(BOARD_EC200UEU_AA_MSDL) \
	|| defined(BOARD_EC200UCN_AA_QIOT) \
	|| defined(BOARD_EC200UCN_AA_VOBT) \
	|| defined(BOARD_EC200UCN_AA_BT) \
	|| defined(BOARD_EC200UCN_AA_EXTFS8M) \
	|| defined(BOARD_EC200UAU_AB) \
	|| defined(BOARD_EC200UAU_AB_VOLTE) \
	|| defined(BOARD_EC200UAU_AA)) \
	|| defined(BOARD_EC200UCN_AB) \
	|| defined(BOARD_EC200UCN_AB_VOBT) \
	|| defined(BOARD_EC200UCN_AD)
#define PLAT_GPIO_NUM 47
#elif defined(BOARD_EG915UEU_AB) \
	|| defined(BOARD_EG915UEU_AB_HYT) \
	|| defined(BOARD_EG915ULA_AB) \
	|| defined(BOARD_EG915ULA_AC) \
	|| defined(BOARD_EG915ULA_AD) \
	|| defined(BOARD_EG915UCN_AC) \
	|| defined(BOARD_EG915UEC_AC) \
	|| defined(BOARD_EG915UEU_AC) \
	|| defined(BOARD_EG915ULA_AC_USBUP) \
	|| defined(BOARD_EG915UCN_AC_USBUP) \
	|| defined(BOARD_EG915UEU_AC_USBUP) \
	|| defined(BOARD_EG915UEC_AC_USBUP)
#define PLAT_GPIO_NUM 41
#elif defined(BOARD_EG912UGL_AA) || defined(BOARD_EG912UGL_AC_CFF) || defined(BOARD_EG912UGL_AC)
#define PLAT_GPIO_NUM 41
#elif defined(BOARD_EC200UEU_DC)
#define PLAT_GPIO_NUM 47
#elif defined(BOARD_EG915ULA_DC) || defined(BOARD_EG915ULA_DC_CUG)
#define PLAT_GPIO_NUM 41
#else
#error "Please confirm the unisoc platform"
#endif

#elif defined(PLAT_Unisoc_8850) || defined(PLAT_Unisoc_8850_R02)
#if defined(BOARD_EC800GCN_GA) \
	|| defined(BOARD_EC800GCN_GA_MS) \
	|| defined(BOARD_EC800GCN_LD) \
	|| defined(BOARD_EC800GCN_LD_XBND) \
	|| defined(BOARD_EC800GCN_LD_HRXM) \
	|| defined(BOARD_EC800GCN_LB) \
	|| defined(BOARD_EC800GCN_TT)\
	|| defined(BOARD_EC800GCN_GA_VOLTE) \
	|| defined(BOARD_EG800GLA_LD)
#define PLAT_GPIO_NUM 50
#elif defined(BOARD_EC600GCN_LD) \
	|| defined(BOARD_EC600GCN_LA) \
	|| defined(BOARD_EC600GCN_LA_CDD) \
	|| defined(BOARD_EC600GCN_LD_YM) \
	|| defined(BOARD_EC600GCN_MD_HK)
#define PLAT_GPIO_NUM 48
#elif defined(BOARD_EG700GCN_LC)
#define PLAT_GPIO_NUM 46
#else
#error "Please confirm the unisoc_8850 platform"
#endif

#elif defined(PLAT_ASR_1803s) || defined(PLAT_ASR_1803sc)
#define PLAT_GPIO_NUM 47
#elif defined(PLAT_ASR_1606)
#if defined(BOARD_EC600MCN_LA) || defined(BOARD_EC600MCN_LA_POC_XBND)|| defined(BOARD_EC600MCN_LA_POC_QS) \
    || defined(BOARD_EC600MCN_LA_VOLTE) || defined(BOARD_EC600MCN_LA_HJT) || defined(BOARD_EC600MCN_LC) \
    || defined(BOARD_EC600MCN_LE) || defined(BOARD_EC600MCN_LF) || defined(BOARD_EC600MCN_LE_POC_XBND) \
	|| defined(BOARD_EC600MCN_LA_POC_ZZD) || defined(BOARD_EC600MCN_LE_POC_ZZD) || defined(BOARD_EC600MCN_LF_SPISD)\
	|| defined(BOARD_EC600MCN_LE_POC_QS) || defined(BOARD_EC600MCN_CC) || defined(BOARD_EC600MCN_LE_VOLTE) \
	|| defined(BOARD_EC600MCN_CC_EXT) ||  defined(BOARD_EC600MCN_LF_SLPOC) || defined(BOARD_EC600MCN_CC_EXT_TTS) \
	|| defined(BOARD_EC600MCN_LE_ALIPAY) || defined(BOARD_EC600MCN_LE_BTZ) || defined(BOARD_EC600MEU_LA) \
	|| defined(BOARD_EC600MEU_LA_POC_XBND) || defined(BOARD_EC600MCN_LF_QS) || defined(BOARD_EC600MLA_LA_POC_XBND) \
	|| defined(BOARD_EC600MEU_LA_POC_QS) || defined(BOARD_EC600MLA_LA_POC_QS)
#define PLAT_GPIO_NUM 45
#elif defined(BOARD_EC800MCN_LA) || defined(BOARD_EC800MCN_GA)  || defined(BOARD_EC800MCN_LE) \
    || defined(BOARD_EC800MCN_LA_VOLTE) || defined(BOARD_EC800MCN_GC) || defined(BOARD_EC800MCN_LC) \
    || defined(BOARD_EC800MCN_LF) || defined(BOARD_EC800MCN_GD)\
    || defined(BOARD_EC800MCN_GA_MS) || defined(BOARD_EC800MCN_GA_VOLTE) || defined(BOARD_EC800MCN_LA_POC_XBND) \
    || defined(BOARD_EC800MCN_LE_POC_XBND) || defined(BOARD_EC800MCN_GA_ALIPAY) || defined(BOARD_EG810MCN_GA) \
    || defined(BOARD_EC800MCN_CC) || defined(BOARD_EC800MCN_LE_VOLTE) || defined(BOARD_EC800MCN_GA_SPISD) \
    || defined(BOARD_EG810MCN_GA_ALIPAY) || defined(BOARD_EC800MCN_GA_VOEXT) || defined(BOARD_EG810MCN_GA_VOEXT) \
    || defined(BOARD_EC800MCN_LE_VOLVGL) || defined(BOARD_EG810MCN_GA_VOLTE) || defined(BOARD_EC800MCN_CC_TTS) \
	|| defined(BOARD_EC800MCN_GB) || defined(BOARD_EG810MCN_GB) || defined(BOARD_EG810MCN_GB_VOEXT) \
	|| defined(BOARD_EC800MCN_LF_CCG) || defined(BOARD_EG810MCN_LA) || defined(BOARD_EG810MEU_LA) \
	|| defined(BOARD_EG810MCN_LA_VOLTE) || defined(BOARD_EG810MEU_LA_VOEXT) || defined(BOARD_EG810MCN_LA_VOEXT)\
	|| defined(BOARD_EC800MCN_LE_CPE) || defined(BOARD_EC800MCN_GB_VOEXT) || defined(BOARD_EG810MEU_LA_VOLVGL) \
	||defined(BOARD_EG810MCN_GB_ALIPAY) || defined(BOARD_EC800MCN_LE_VOEXT)
#define PLAT_GPIO_NUM 47
#else
#error "Please confirm the board"
#endif
#elif defined(PLAT_ASR_1602)
#if defined(BOARD_EC600KCN_CC_TTS) || defined(BOARD_EC600KCN_LC)
#define PLAT_GPIO_NUM 39
#elif defined(BOARD_EC800KCN_CC_TTS) || defined(BOARD_EC800KCN_LC) || defined(BOARD_EC800KCN_CC) || defined(BOARD_EG800KCN_GC) || defined(BOARD_EG800KEU_CC)\
|| defined(BOARD_EC800KCN_LC_SMS)
#define PLAT_GPIO_NUM 47
#else
#error "Please confirm the board"
#endif
#elif defined(PLAT_ASR_1609)
#if defined(BOARD_EG800PCN_LA) || defined(BOARD_EG800PCN_LA_ALIPAY)
#define PLAT_GPIO_NUM 50
#else
#error "Please confirm the board"
#endif
#elif defined(PLAT_EIGEN)
#if defined(BOARD_EC600ECN_LC) || defined(BOARD_EC600ECN_LC_AEF) || defined(BOARD_EC600ECN_LC_AUD)
#define PLAT_GPIO_NUM 41
#elif defined(BOARD_EC800ECN_LC) || defined(BOARD_EC800ECN_LC_WDF) || defined(BOARD_EC800ECN_LC_AEF) || defined(BOARD_EC800ECN_LC_AUD)
#define PLAT_GPIO_NUM 40
#else
#error "Please confirm the eigen platform"
#endif
#elif defined(PLAT_ECR6600)
#if defined(BOARD_FCM360W)
#define PLAT_GPIO_NUM 29
#else
#error "Please confirm the ecr6600 platform"

#endif

#elif defined(PLAT_EIGEN_718)
#if defined(BOARD_EC800ZCN_LD)
#define PLAT_GPIO_NUM 41
#else
#error "Please confirm the eigen 718 platform"
#endif

#elif defined(PLAT_aic8800m40)
#define PLAT_GPIO_NUM 38 //TODO

#elif defined(PLAT_SONY_ALT1350)
#if defined(BOARD_BG950SGL_AA)
#define PLAT_GPIO_NUM 28 //TODO
#elif defined(BOARD_BG770SGL_AA)
#define PLAT_GPIO_NUM 37 //TODO
#else 
#error "Please confirm the Sony 1350 platform"
#endif

#else
#error "Please confirm the platform"
#endif



/**
 * Uniform GPIO number to the PY layer
 */
typedef enum {
	HELIOS_GPIO0 = 0,
	PLAT_GPIO_HELIOS_DEF(PLAT_GPIO_NUM),
	HELIOS_GPIOMAX,
}Helios_GPIONum;

typedef enum {
	GPIO0 = 0,
	EXTERNAL_PLAT_GPIO_DEF(PLAT_GPIO_NUM),
	GPIOMAX,
}GPIONum;



#ifdef __cplusplus
} /*"C" */
#endif

#endif



