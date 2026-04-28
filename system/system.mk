# Copyright (c) Quectel Wireless Solution, Co., Ltd.All Rights Reserved.
#  
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#  
#     http://www.apache.org/licenses/LICENSE-2.0
#  
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

NAME := SYSTEM

include config/$(KCONFIG_CONFIG)

GLOBAL_INCS = include

$(NAME)_COMPONENTS := 	system/platform \
						system/debug \
						system/dev \
						system/fs \
						system/hal \
						system/lwip \
						system/network \
						system/os \
						system/bt \
						system/startup \
						system/at \
						system/csd \
						system/esim \
						system/aliiot


ifneq ($(strip $(PLAT)),RDA)
ifeq ($(CONFIG_MBEDTLS),y)
$(NAME)_COMPONENTS += system/mbedtls
else
ifeq ($(strip $(PLAT)), SONY_ALT1350)
GLOBAL_INCS = \
	system/platform/$(strip $(PLAT))/include/MbedTLS \
	system/platform/$(strip $(PLAT))/include/MbedTLS/mbedtls \
	system/platform/$(strip $(PLAT))/include/MbedTLS/psa \
	system/mbedtls/port/helios/inc
endif
endif
endif

ifeq ($(strip $(PLAT)),$(filter $(PLAT),Unisoc Unisoc_8910_R05 Unisoc_8910_R06 Unisoc_8850 Unisoc_8850_R02 ASR_1606 ASR Qualcomm ASR_1609 ASR_1602))
$(NAME)_COMPONENTS += system/gnss \

endif

$(NAME)_COMPONENTS += system/fota
