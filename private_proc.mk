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

ifneq ($(APP_ENTRY),)

make_mk_fnc = $(1)/$(notdir $(1)).mk

APP_MK = $(call make_mk_fnc, $(APP_ENTRY))
include $(APP_MK)

APP_PRIVATE_MK = $($(NAME)_PRIVATE_SCRIPT)

define RULES
$(1):
	@make -C $(APP_ENTRY) --no-print-directory -f $(APP_PRIVATE_MK) $(1)
endef

$(foreach target, $($(NAME)_PRIVATE_SCRIPT_TARGETS), $(eval $(call RULES, $(target))))

ifneq ($(findstring clean,$($(NAME)_PRIVATE_SCRIPT_TARGETS)),)
APP_PRIVATE_CLEAN = clean
endif

endif

.PHONY : private_main private_clean $(APP_PRIVATE_CLEAN) $($(NAME)_PRIVATE_SCRIPT_TARGETS)

prompt:
ifneq ($($(NAME)_PRIVATE_SCRIPT_TARGETS),)
	@echo ----- doing preaction for $(APP_ENTRY)
else
	@echo ----- ! No preaction for $(APP_ENTRY)
endif

private_main: prompt $($(NAME)_PRIVATE_SCRIPT_TARGETS)

private_clean: $(APP_PRIVATE_CLEAN)