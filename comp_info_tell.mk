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

include $(COMP_MK)

all:
	@echo "NAME: $(NAME)"
	@echo "GLOBAL_INCS: $(GLOBAL_INCS)"
	@echo "GLOBAL_DEFINE: $(GLOBAL_DEFINE)"
	@echo "LOCAL_CFLAGS: $($(NAME)_CFLAGS)"
	@echo "LOCAL_ARCHIVES: $($(NAME)_ARCHIVES)"
	@echo "LOCAL_SRCS: $($(NAME)_SRCS)"
	@echo "LOCAL_SRCS_2: $($(NAME)_SRCS_2)"
	@echo "LOCAL_SRCS_3: $($(NAME)_SRCS_3)"
	@echo "LOCAL_INCS: $($(NAME)_INCS)"
	@echo "LOCAL_DEFINE: $($(NAME)_DEFINE)"
	@echo "COMP_DEPS: $($(NAME)_COMPONENTS)"
