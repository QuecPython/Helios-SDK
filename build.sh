#!/bin/sh

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

py_ver=$(python --version 2> /dev/null | sed -n '/Python 3/p')
py3_ver=$(python3 --version 2> /dev/null | sed -n '/Python 3/p')

if [ ! -n "$py_ver" ]; then
    if [ ! -n "$py3_ver" ]; then
        echo "! No Python3.x found in system environment."
    else
        python3 main.py python3 $*
    fi
else
    python main.py python $*
fi


