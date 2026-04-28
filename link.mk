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

$(TARGET_BIN): $(TARGET_ELF)

ifneq ($(strip $(PLAT)),FCM360W)
	$(Q)$(OBJCOPY) $^ $@ -Obinary
endif
	@echo ----- $@ updated

$(TARGET_HEX): $(TARGET_ELF)
	$(Q)$(OBJCOPY) $^ $@ -Oihex
	@echo ----- $@ updated

-include $(OUTPUT_LD_FILE).d

$(OUTPUT_LD_FILE): $(LD_FILE)
	@echo
	$(Q)$(CC) $(foreach inc, $(OUTPUT_SCRIPTS_INCS), -I$(inc)) $(CFLAGS) $(foreach d, $(DFLAGS) $(COMP_DFLAGS), -D$(d)) -E -P -x c -MD -MT $@ -MF $@.d -o $@ -c $<
	@echo ----- $@ updated

$(TARGET_ELF): $(OUTPUT_LD_FILE) $(COMP_ARCHIVES) $(USER_ARCHIVES) $(STD_LIBS)
	@echo
	$(Q)$(LD) --whole-archive \
	$(COMP_ARCHIVES) $(USER_ARCHIVES) --no-whole-archive $(STD_LIBS) \
	-o $@ $(LDFLAGS)
	@echo ----- $@ updated
