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


-include $(OUTPUT_PLAT_PRIVATE_CFG_FILE)

DTOOLS = tools/$(strip $(PLAT))/$(HOST)/dtools
PACGEN_PY = $(PY) tools/$(strip $(PLAT))/pacgen.py

IMAGES_PATH = system/platform/$(strip $(PLAT))/boards/$(strip $(BOARD))/images
FDL1_IMG = $(IMAGES_PATH)/fdl1.img
FDL2_IMG = $(IMAGES_PATH)/fdl2.img
KERNEL_PAC = $(IMAGES_PATH)/kernel.pac
KERNEL_ELF = $(IMAGES_PATH)/kernel.elf
KERNEL_MAP = $(IMAGES_PATH)/kernel.map

FW_NAME_FAC = $(FW_NAME)_factory

TARGET_IMG = $(OUTPUT_BIN_PATH)/$(FW_NAME).img
TARGET_PAC = $(OUTPUT_BIN_PATH)/$(FW_NAME).pac
TARGET_FS_ERASE_PAC = $(OUTPUT_BIN_PATH)/$(FW_NAME)_pyfs_erase.pac
TARGET_FLASH_DELETE_PAC = $(OUTPUT_BIN_PATH)/$(FW_NAME)_flash_delete.pac

FIRMWARE_PREFIX = 8915DM_cat1_open
FIRMWARE_REL_PAC = $(OUTPUT_REL_PATH)/$(FW_NAME)/$(FIRMWARE_PREFIX)_$(FW_NAME)_merge.pac
FIRMWARE_FAC_PAC = $(OUTPUT_REL_PATH)/$(FW_NAME_FAC)/$(FIRMWARE_PREFIX)_$(FW_NAME)_merge.pac

$(FIRMWARE_REL_PAC): $(KERNEL_PAC) $(TARGET_PAC) $(TARGET_FLASH_DELETE_PAC) $(TARGET_FS_ERASE_PAC)
	$(Q)mkdir -p $(OUTPUT_REL_PATH)/$(FW_NAME)/app $(OUTPUT_REL_PATH)/$(FW_NAME_FAC)/app
	$(Q)$(DTOOLS) pacmerge --id APPIMG,PS $(KERNEL_PAC) $(TARGET_PAC) $@.tmp
	$(Q)$(DTOOLS) pacmerge --id ERASE_PY_FS_U,PS --id ERASE_PY_FS_B,PS --id ERASE_PY_FS_C,PS $@.tmp $(TARGET_FS_ERASE_PAC) $@.tmp
	$(Q)cp $(OUTPUT_BIN_PATH)/*.elf $(OUTPUT_BIN_PATH)/*.map $(OUTPUT_BIN_PATH)/*.img $(OUTPUT_BIN_PATH)/*.pac $(OUTPUT_REL_PATH)/$(FW_NAME)/app
	$(Q)cp $(OUTPUT_REL_PATH)/$(FW_NAME)/app/$(FW_NAME).elf $(OUTPUT_REL_PATH)/$(FW_NAME)/app/customer_app.elf
	$(Q)cp -rf $(OUTPUT_REL_PATH)/$(FW_NAME)/* $(OUTPUT_REL_PATH)/$(FW_NAME_FAC)
	$(Q)mv $(FIRMWARE_FAC_PAC).tmp $(FIRMWARE_FAC_PAC)
	$(Q)mv $@.tmp $@
	@echo ----- $@ updated
	@echo ----- $(FIRMWARE_FAC_PAC) updated

$(TARGET_FLASH_DELETE_PAC): $(FDL1_IMG) $(FDL2_IMG)
	$(Q)$(PACGEN_PY) cfg-init --pname UIX8910_MODEM --palias APPIMG --pversion "8910 MODULE" \
	--version BP_R1.0.0 --flashtype 1 cfg-host-fdl -a $(MK_CONFIG_FDL1_IMAGE_START) -s $(MK_CONFIG_FDL1_IMAGE_SIZE) \
	-p $(FDL1_IMG) cfg-fdl2 -a $(MK_CONFIG_FDL2_IMAGE_START) -s $(MK_CONFIG_FDL2_IMAGE_SIZE) \
	-p $(FDL2_IMG) cfg-erase-flash -i ERASE_APPIMG -a $(MK_CONFIG_APPIMG_FLASH_ADDRESS) -s $(MK_CONFIG_APPIMG_FLASH_SIZE) \
	pac-gen $@
	@echo ----- $@ updated

$(TARGET_PAC): $(FDL1_IMG) $(FDL2_IMG) $(TARGET_IMG)
	$(Q)$(PACGEN_PY) cfg-init --pname UIX8910_MODEM --palias APPIMG --pversion "8910 MODULE" \
	--version BP_R1.0.0 --flashtype 1 cfg-host-fdl -a $(MK_CONFIG_FDL1_IMAGE_START) -s $(MK_CONFIG_FDL1_IMAGE_SIZE) \
	-p $(FDL1_IMG) cfg-fdl2 -a $(MK_CONFIG_FDL2_IMAGE_START) -s $(MK_CONFIG_FDL2_IMAGE_SIZE) \
	-p $(FDL2_IMG) cfg-image -i APPIMG -a $(MK_CONFIG_APPIMG_FLASH_ADDRESS) -s $(MK_CONFIG_APPIMG_FLASH_SIZE) \
	-p $(TARGET_IMG) \
	pac-gen $@
	@echo ----- $@ updated

$(TARGET_FS_ERASE_PAC): $(FDL1_IMG) $(FDL2_IMG)
	$(Q)$(PACGEN_PY) cfg-init --pname UIX8910_MODEM --palias APPIMG --pversion "8910 MODULE" \
	--version BP_R1.0.0 --flashtype 1 cfg-host-fdl -a $(MK_CONFIG_FDL1_IMAGE_START) -s $(MK_CONFIG_FDL1_IMAGE_SIZE) \
	-p $(FDL1_IMG) cfg-fdl2 -a $(MK_CONFIG_FDL2_IMAGE_START) -s $(MK_CONFIG_FDL2_IMAGE_SIZE) \
	-p $(FDL2_IMG) \
	cfg-erase-flash -i ERASE_PY_FS_U -a $(MK_CONFIG_FS_PY_U_FLASH_ADDRESS) -s $(MK_CONFIG_FS_PY_U_FLASH_SIZE) \
	cfg-erase-flash -i ERASE_PY_FS_B -a $(MK_CONFIG_FS_PY_B_FLASH_ADDRESS) -s $(MK_CONFIG_FS_PY_B_FLASH_SIZE) \
	cfg-erase-flash -i ERASE_PY_FS_C -a $(MK_CONFIG_FS_PY_C_FLASH_ADDRESS) -s $(MK_CONFIG_FS_PY_C_FLASH_SIZE) \
	pac-gen $@

$(TARGET_IMG): $(TARGET_ELF)
	$(Q)$(DTOOLS) mkappimg $^ $@
	@echo ----- $@ updated
