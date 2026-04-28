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

##########################################
# flags and libs on Unisoc & Unisoc_8850 #
##########################################
ifeq ($(strip $(PLAT)), $(filter $(PLAT),Unisoc Unisoc_8850 Unisoc_8910_R05 Unisoc_8850_R02 Unisoc_8910_R06))
CFLAGS_PLAT = 	-mcpu=cortex-a5 -mtune=generic-armv7-a -mthumb \
				-mfpu=neon-vfpv4 -mfloat-abi=hard -mno-unaligned-access
CPPFLAGS_PLAT = -mcpu=cortex-a5 -mtune=generic-armv7-a -mthumb \
				-mfpu=neon-vfpv4 -mfloat-abi=hard -mno-unaligned-access
include config/config.mk

# ifeq ($(CONFIG_CAMERA_DECODE), y)
ifeq ($(CONFIG_CAMERA), y)
# $(info USE nano lib)
USE_NANO_LIB = y
endif

ifeq ($(strip $(BOARD)),$(filter $(strip $(BOARD)),EC800GCN_LD EC600UCN_LB EC800GCN_TT EG800GLA_LD))
# $(info USE nano lib)
USE_NANO_LIB = y
endif

ifeq ($(USE_NANO_LIB), y) # use nano lib
STD_LIBS += $(COMPILER_PATH)/$(CROSS)/lib/thumb/v7-a+fp/hard/libc_nano.a
else
STD_LIBS += $(COMPILER_PATH)/$(CROSS)/lib/thumb/v7-a+fp/hard/libc.a
endif

ifneq ($(USE_NOSYS_LIB), n) # use nosys lib
STD_LIBS += $(COMPILER_PATH)/$(CROSS)/lib/thumb/v7-a+fp/hard/libnosys.a
endif

STD_LIBS += $(COMPILER_PATH)/$(CROSS)/lib/thumb/v7-a+fp/hard/libm.a \
			$(COMPILER_PATH)/lib/gcc/$(CROSS)/10.2.1/thumb/v7-a+fp/hard/libgcc.a
            
ifeq ($(strip $(PLAT)),$(filter $(PLAT),Unisoc_8850 Unisoc_8850_R02 Unisoc_8910_R06))
DFLAGS_PLAT = _SYS__TIMEVAL_H_
endif
endif

##########################
#  export for STD_LIBS   #
##########################
export STD_LIBS