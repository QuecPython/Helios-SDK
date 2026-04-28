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

export HOST
export PY

export PLAT = Unisoc
export BOARD = EC200UEU_AA



#################################################################
#                                                               #
#                 compilation toolchain setup                   #
#                                                               #
#################################################################


# helios-toolchain on win32 has updated to v1.3.0 to support Qualcomm platform,
# Add a new environment variable `LLVM_COMPILER_PATH' to specify compiler path of
# Qualcomm platform.
#
# Lower version of helios-toolchain both on win32 and linux is compatible.

# if Unisoc platform
ifeq ($(strip $(PLAT)), $(filter $(PLAT),Unisoc Unisoc_8910_R05 Unisoc_8910_R06))
ifeq ($(HOST),win32)
ifneq ($(strip $(ARM_GCC_COMPILER_PATH)),)
export COMPILER_PATH = $(strip $(ARM_GCC_COMPILER_PATH))
endif
endif
CROSS = arm-none-eabi
endif

export COMPILER_BIN_PATH = $(COMPILER_PATH)/bin/

ifneq ($(PLAT),Qualcomm)
export AS = $(COMPILER_BIN_PATH)$(CROSS)-as
export CC = $(COMPILER_BIN_PATH)$(CROSS)-gcc
export CXX = $(COMPILER_BIN_PATH)$(CROSS)-g++
export AR = $(COMPILER_BIN_PATH)$(CROSS)-ar
export LD = $(COMPILER_BIN_PATH)$(CROSS)-ld
export OBJCOPY = $(COMPILER_BIN_PATH)$(CROSS)-objcopy
export SIZE = $(COMPILER_BIN_PATH)$(CROSS)-size
export STRIP = $(COMPILER_BIN_PATH)$(CROSS)-strip
export GDB = $(COMPILER_BIN_PATH)$(CROSS)-gdb
export OBJDUMP = $(COMPILER_BIN_PATH)$(CROSS)-objdump
endif



#################################################################
#                                                               #
#                    command verbose setup                      #
#                                                               #
#################################################################

V = 0
ifeq ($(V),1)
export Q :=
else
ifeq ($(V),0)
export Q := @
endif
endif



#################################################################
#                                                               #
#              output files and directories setup               #
#                                                               #
#################################################################

export APP_ENTRY := 

export ROOT_PATH := ../

export OUTPUT_DIR := output
export OUTPUT_TMP_DIR := tmp
export OUTPUT_OBJ_DIR := obj
export OUTPUT_BIN_DIR := bin
export OUTPUT_REL_DIR := release
export OUTPUT_SCRIPTS_DIR := scripts

export OUTPUT_TMP_PATH := $(OUTPUT_DIR)/$(OUTPUT_TMP_DIR)
export OUTPUT_OBJ_PATH := $(OUTPUT_DIR)/$(OUTPUT_OBJ_DIR)
export OUTPUT_BIN_PATH := $(OUTPUT_DIR)/$(OUTPUT_BIN_DIR)
export OUTPUT_REL_PATH := $(OUTPUT_DIR)/$(OUTPUT_REL_DIR)
export OUTPUT_SCRIPTS_PATH := $(OUTPUT_DIR)/$(OUTPUT_SCRIPTS_DIR)

APP_RECORD_TMP_FILE := app_record.tmp
FW_NAME_RECORD_TMP_FILE := fw_name_record.tmp
BOARD_RECORD_TMP_FILE := board_record.tmp
DFLAGS_TMP_FILE := dflags.tmp
BUILD_SUCESS_FILE := build_sucess.tmp

ifeq ($(PLAT),RDA)
export LD_FILE = system/platform/$(strip $(PLAT))/boards/$(strip $(BOARD))/scripts/linkscript.ld
else
export LD_FILE = system/platform/$(strip $(PLAT))/scripts/linkscript.ld
endif
export OUTPUT_LD_FILE := $(OUTPUT_SCRIPTS_PATH)/$(notdir $(LD_FILE))

export PLAT_PRIVATE_MK_FILE = system/platform/$(strip $(PLAT))/scripts/private.mk
export PLAT_PRIVATE_CFG_FILE = system/platform/$(strip $(PLAT))/scripts/private.cfg
ifneq ($(shell ls $(PLAT_PRIVATE_CFG_FILE) 2> /dev/null),)
export OUTPUT_PLAT_PRIVATE_CFG_FILE := $(OUTPUT_SCRIPTS_PATH)/$(notdir $(PLAT_PRIVATE_CFG_FILE))
else
export OUTPUT_PLAT_PRIVATE_CFG_FILE :=
endif

define READ_APP_RECORD_TMP_FILE
$(shell cat $(OUTPUT_TMP_PATH)/$(APP_RECORD_TMP_FILE) 2> /dev/null)
endef

define READ_FW_NAME_RECORD_TMP_FILE
$(shell cat $(OUTPUT_TMP_PATH)/$(FW_NAME_RECORD_TMP_FILE) 2> /dev/null)
endef

define READ_BOARD_RECORD_TMP_FILE
$(shell cat $(OUTPUT_TMP_PATH)/$(BOARD_RECORD_TMP_FILE) 2> /dev/null)
endef

define READ_DFLAGS_TMP_FILE
$(shell sed -n '/\"/p' $(OUTPUT_TMP_PATH)/$(DFLAGS_TMP_FILE)  | sed 's/\"/\\\"/g' 2> /dev/null)
endef

NAME := TOP

export FW_NAME = $(notdir $(APP_ENTRY))

export TARGET_BIN = $(OUTPUT_BIN_PATH)/$(FW_NAME).bin
export TARGET_HEX = $(OUTPUT_BIN_PATH)/$(FW_NAME).hex
export TARGET_ELF = $(OUTPUT_BIN_PATH)/$(FW_NAME).elf
export TARGET_MAP = $(OUTPUT_BIN_PATH)/$(FW_NAME).map
export TARGET_SIZE = $(OUTPUT_BIN_PATH)/$(FW_NAME).size



#################################################################
#                                                               #
#               compilation common options setup                #
#                                                               #
#################################################################

include plat.mk
-include $(APP_ENTRY)/user_cfg.mk

export GLOBAL_INCS :=
export GLOBAL_DEFINE :=

ifeq ($(CFLAGS_USER),)
ifeq ($(PLAT),aic8800m40)
	CFLAGS_USER = -W -Wall -fno-strict-aliasing -ffunction-sections -fdata-sections -g -Os
else
	CFLAGS_USER = -W -Wall -Werror -fno-strict-aliasing -ffunction-sections -fdata-sections -g -Os
endif
endif

LDFLAGS_O = -Os

ifeq ($(PLAT),Qualcomm)
export IFLAGS := $(COMPILER_PATH)/armv7m-none-eabi/libc/include
LDFLAGS_O =
endif

ifeq ($(VER),)
VER_EXTERN=
else
VER_EXTERN=V
endif

export CFLAGS := $(CFLAGS_USER) $(CFLAGS_PLAT) --include=config/autoconf.h -std=gnu11
export QUEC_CFLAGS := $(CFLAGS_USER) $(CFLAGS_PLAT)
export CPPFLAGS := $(CFLAGS_USER) $(CPPFLAGS_PLAT) --include=config/autoconf.h -std=c++11
export DFLAGS := $(DFLAGS_USER) $(DFLAGS_PLAT) PLAT_$(strip $(PLAT)) BOARD_$(strip $(BOARD)) BOARD=$(strip $(BOARD)) FW_NAME=\"$(strip $(FW_NAME))\" QPYVER=$(VER_EXTERN)$(VER)
ifeq ($(strip $(PLAT)),ECR6600)
export LDFLAGS := $(LDFLAGS_PLAT) -nostdlib $(LDFLAGS_O) -T$(OUTPUT_LD_FILE) \
				  $(LDFLAGS_USE_NANO_LIB) $(LDFLAGS_USE_NOSYS_LIB) -static \
				  -Wl,-Map=$(TARGET_MAP) -Wl,-gc-sections
else
export LDFLAGS := $(LDFLAGS_PLAT) -nostdlib $(LDFLAGS_O) -T$(OUTPUT_LD_FILE) \
				  $(LDFLAGS_USE_NANO_LIB) $(LDFLAGS_USE_NOSYS_LIB) -static \
				  -Map=$(TARGET_MAP) -gc-sections
endif

OUTPUT_SCRIPTS_INCS = \
	system/platform/$(strip $(PLAT))/include \
	system/platform/$(strip $(PLAT))/scripts \
	system/platform/$(strip $(PLAT))/boards/$(strip $(BOARD))/include
export OUTPUT_SCRIPTS_INCS



#################################################################
#                                                               #
#                   targets' generation rules                   #
#                                                               #
#################################################################

.PHONY : preaction target construct prepare update_tmp_file exec beforeend end clean common_clean private_clean menuconfig

target: preaction construct end

preaction:
	@mkdir -p $(OUTPUT_TMP_PATH)
	@echo $(APP_ENTRY) > $(OUTPUT_TMP_PATH)/$(APP_RECORD_TMP_FILE)
ifneq ($(READ_BOARD_RECORD_TMP_FILE), $(BOARD))
ifneq ($(shell ls $(OUTPUT_TMP_PATH)/$(BOARD_RECORD_TMP_FILE) 2> /dev/null),)
	@make --no-print-directory private_clean
endif
endif
	@make --no-print-directory -f private_proc.mk APP_ENTRY=$(APP_ENTRY)

construct: prepare update_tmp_file exec

prepare:
ifeq ($(APP_ENTRY),)
	$(error Please specify an application directory !!!)
endif
ifneq ($(READ_BOARD_RECORD_TMP_FILE), $(BOARD))
ifneq ($(shell ls $(OUTPUT_TMP_PATH)/$(BOARD_RECORD_TMP_FILE) 2> /dev/null),)
	@make --no-print-directory common_clean
endif
else
ifneq ($(strip $(sort $(READ_DFLAGS_TMP_FILE))), $(strip $(sort $(DFLAGS))))
	@-rm -rf $(OUTPUT_OBJ_PATH)/*
endif
ifneq ($(READ_APP_RECORD_TMP_FILE), $(APP_ENTRY))
	@-rm -rf $(OUTPUT_OBJ_PATH)/$(READ_APP_RECORD_TMP_FILE)
	@-rm -rf $(OUTPUT_BIN_PATH)/*
	@-rm -rf $(OUTPUT_REL_PATH)/*
endif
ifneq ($(READ_FW_NAME_RECORD_TMP_FILE), $(FW_NAME))
	@-rm -rf $(OUTPUT_BIN_PATH)/*
	@-rm -rf $(OUTPUT_REL_PATH)/*
endif
endif
	@mkdir -p $(OUTPUT_TMP_PATH) $(OUTPUT_OBJ_PATH) $(OUTPUT_BIN_PATH) $(OUTPUT_REL_PATH) $(OUTPUT_SCRIPTS_PATH)
	@-rm -rf $(OUTPUT_TMP_PATH)/$(BUILD_SUCESS_FILE)

update_tmp_file:
	@echo $(APP_ENTRY) > $(OUTPUT_TMP_PATH)/$(APP_RECORD_TMP_FILE)
	@echo $(FW_NAME) > $(OUTPUT_TMP_PATH)/$(FW_NAME_RECORD_TMP_FILE)
	@echo $(BOARD) > $(OUTPUT_TMP_PATH)/$(BOARD_RECORD_TMP_FILE)
	@echo $(DFLAGS) > $(OUTPUT_TMP_PATH)/$(DFLAGS_TMP_FILE)

exec:
	@$(PY) compile.py $(APP_ENTRY)
	@echo

-include $(OUTPUT_PLAT_PRIVATE_CFG_FILE).d

$(OUTPUT_PLAT_PRIVATE_CFG_FILE): $(PLAT_PRIVATE_CFG_FILE)
	@echo
	$(Q)$(CC) $(foreach inc, $(OUTPUT_SCRIPTS_INCS), -I$(inc)) $(CFLAGS) $(addprefix -D,$(DFLAGS)) -E -P -x c -MD -MT $@ -MF $@.d -o $@ -c $<
	@echo ----- $@ updated

end: $(OUTPUT_PLAT_PRIVATE_CFG_FILE)
ifneq ($(strip $(PLAT)),$(filter $(strip $(PLAT)),aic8800m40 SONY_ALT1350))
	@make --no-print-directory -f $(PLAT_PRIVATE_MK_FILE)
endif

	@echo we have building done.>$(OUTPUT_TMP_PATH)/$(BUILD_SUCESS_FILE)
	@echo
	@echo ====================================================
	@echo ============ Project construct finished ============
	@echo ====================================================



#################################################################
#                                                               #
#                          clean rules                          #
#                                                               #
#################################################################

private_clean:
	@make --no-print-directory -f private_proc.mk private_clean APP_ENTRY=$(strip $(READ_APP_RECORD_TMP_FILE))

common_clean:
	@echo ----- cleaning project target
	@-rm -rf $(OUTPUT_DIR)
	@echo ----- done.

clean: private_clean common_clean



#################################################################
#                                                               #
#                       menuconfig rules                        #
#                                                               #
#################################################################

# If in CMD environment
ifeq ($(findstring cmd.exe,$(COMSPEC)),cmd.exe)
# Get helios version
HELIOS_VERSION := $(shell cmd /c get_helios_version.bat)
# Define a macro to check if a string represents a number
define is_number
$(shell cmd /c check_number.bat $1)
endef

# Else, in BASH environment
else

# Get helios version
ifeq ($(shell type -P helios),)
    HELIOS_VERSION :=
else
    HELIOS_VERSION := $(shell helios --version | grep -Po 'Helios \(released by Quectel\) \K[^\s]+')
endif
# Define a macro to check if a string represents a number
define is_number
$(shell echo "$1" | grep -q '^[0-9]\+$' && echo "true" || echo "false")
endef

endif

# Check if HELIOS_VERSION is empty or not
ifeq ($(HELIOS_VERSION),)
    IS_NEWER_THAN_1_4_1 := false
else ifeq ($(HELIOS_VERSION),1.4.1)
    IS_NEWER_THAN_1_4_1 := true
else
    # Split the version into parts
    HELIOS_VERSION_PARTS := $(subst ., ,$(HELIOS_VERSION))
    # Check if major, minor, and patch are numbers
    IS_MAJOR_NUMBER := $(call is_number,$(word 1,$(HELIOS_VERSION_PARTS)))
    IS_MINOR_NUMBER := $(call is_number,$(word 2,$(HELIOS_VERSION_PARTS)))
    IS_PATCH_NUMBER := $(call is_number,$(word 3,$(HELIOS_VERSION_PARTS)))

    # If any part is not a number, report an error
    ifneq ($(IS_MAJOR_NUMBER)$(IS_MINOR_NUMBER)$(IS_PATCH_NUMBER),truetruetrue)
        $(error "Unexpected version format: $(HELIOS_VERSION)")
    else
        # Compare the version with 1.4.1
        IS_NEWER_THAN_1_4_1 := $(shell echo "$(HELIOS_VERSION)" | awk -F. '{if ($$1 > 1 || ($$1 == 1 && $$2 >= 4 && $$3 >= 1)) print "true"; else print "false"}')
    endif
endif

export KCONFIG_CONFIG = config.mk
export KCONFIG_AUTOHEADER = autoconf.h

# If the version number of helios is >= 1.4.1.
ifeq ($(IS_NEWER_THAN_1_4_1),true)
export KCONFIG_ENTRY = config.in
# Else
else
export KCONFIG_INCLUDE_DIR = include/config
export MENUCONFIG_CMD_PATH = ../tools/common/$(strip $(HOST))/menuconfig/bin/
ifeq ($(strip $(HOST)),win32)
WIN32_CLEANUP = && make --no-print-directory -f cleanup.mk
WIN32_BASH = git-bash
endif

endif

menuconfig:
	@if [ "$(IS_NEWER_THAN_1_4_1)" = "true" ]; then \
		cd config/ && $(PY) -c "from kconfiglib import Kconfig;from menuconfig import menuconfig;kconf=Kconfig(filename=\"$(KCONFIG_ENTRY)\");menuconfig(kconf);kconf.write_autoconf();"; \
	else \
		cd config/ && mkdir -p $(KCONFIG_INCLUDE_DIR) && $(WIN32_BASH) ./menuconfig.sh $(WIN32_CLEANUP); \
	fi
