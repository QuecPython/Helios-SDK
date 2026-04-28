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

make_mk_fnc = $(1)/$(notdir $(1)).mk
make_obj_fnc = $(OUTPUT_OBJ_PATH)/$(strip $(1)).o
make_dep_fnc = $(OUTPUT_OBJ_PATH)/$(strip $(1)).d

COMP_MK = $(call make_mk_fnc,$(COMP_PATH))
include $(COMP_MK)

OBJECTS_1 := $(foreach n, $(addprefix $(COMP_PATH)/,$(strip $($(NAME)_SRCS))), $(call make_obj_fnc, $(n)))
DEPENDS   := $(foreach n, $(addprefix $(COMP_PATH)/,$(strip $($(NAME)_SRCS))), $(call make_dep_fnc, $(n)))
OBJECTS_2 := $(foreach n, $(addprefix $(COMP_PATH)/,$(strip $($(NAME)_SRCS_2))), $(call make_obj_fnc, $(n)))
DEPENDS   += $(foreach n, $(addprefix $(COMP_PATH)/,$(strip $($(NAME)_SRCS_2))), $(call make_dep_fnc, $(n)))
OBJECTS_3 := $(foreach n, $(addprefix $(COMP_PATH)/,$(strip $($(NAME)_SRCS_3))), $(call make_obj_fnc, $(n)))
DEPENDS   += $(foreach n, $(addprefix $(COMP_PATH)/,$(strip $($(NAME)_SRCS_3))), $(call make_dep_fnc, $(n)))
ARCHIVE   := $(OUTPUT_OBJ_PATH)/$(COMP_PATH)/lib$(notdir $(COMP_PATH)).a

$(ARCHIVE): $(OBJECTS_1) $(OBJECTS_2) $(OBJECTS_3)
	@echo ----- archiving $@
	@-rm -f $@
ifneq ($(strip $(OBJECTS_1)),)
	$(Q)$(AR) -rc $@ $(OBJECTS_1)
endif
ifneq ($(strip $(OBJECTS_2)),)
	$(Q)$(AR) -rc $@ $(OBJECTS_2)
endif
ifneq ($(strip $(OBJECTS_3)),)
	$(Q)$(AR) -rc $@ $(OBJECTS_3)
endif

$(OBJECTS_1) $(OBJECTS_2) $(OBJECTS_3):$(OUTPUT_OBJ_PATH)/%.o:%
	@echo ----- compiling $<
	@mkdir -p $(OUTPUT_OBJ_PATH)/$(dir $<)
	$(Q)$(cc) $($(NAME)_CFLAGS) -c $< $(foreach i, $(COMP_IFLAGS) $(IFLAGS), -I$(i)) $(foreach d, $(DFLAGS) $(COMP_DFLAGS), -D$(d)) -o $@ -MMD -MF $(OUTPUT_OBJ_PATH)/$<.d.tmp -MP || (rm -f $(ARCHIVE); exit 1)
	$(Q)sed -i '/\\:\\/s/\\:\\/:\\/g' $(OUTPUT_OBJ_PATH)/$<.d.tmp
	$(Q)mv $(OUTPUT_OBJ_PATH)/$<.d.tmp $(OUTPUT_OBJ_PATH)/$<.d

%.c.o: cc=$(CC) $(CFLAGS)
%.S.o: cc=$(CC) $(CFLAGS)
%.cpp.o: cc=$(CXX) $(CPPFLAGS)

$(foreach d, $(DEPENDS), $(eval -include $(d)))
