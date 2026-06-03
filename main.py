# -*- coding: utf-8 -*-

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

import os, sys, json, shutil, filecmp

if os.name == 'nt':
    host_spec = ' HOST=win32'
else:
    host_spec = ' HOST=linux'

argv = sys.argv
argc = len(argv)
error_occurred = False

build_log_file = 'build.log'
platform_json = 'system/platform/platform.json'

# error process
def error_proc(msg, prompt='CommandError', errtype='EARGV'):
    global error_occurred
    if not error_occurred:
        print("! %s: [%s]: `%s'" % (prompt, errtype, msg))
        error_occurred = True

# help cmd process
def help_proc():
    print('Usage: helios <action> [<app>] [<at>] [<fw_name>]\n')
    print('These are common commands used in various situations:')
    print('   menuconfig <module>              - Do the project configuration')
    print('   make <app> [[<at>] [<fw_name>]]  - Do the compilation work')
    print('   private_clean                    - Clean the app private target')
    print('   clean                            - Clean the output directory')
    print('   help                             - Show this help page')

# menuconfig cmd process
def menuconfig_proc(board):
    abs_path = os.getcwd()
    plat = get_plat_by_board(board)
    if plat == '':
        print('Not supported {}'.format(board))
        return
    real_board = board.split('*')[0]

    if host_spec == ' HOST=win32':
        src_path = abs_path + '\\system\\platform\\' + plat + '\\boards\\' + real_board + '\\config'
        dst_path = abs_path + '\\config'

        shutil.copy(src_path + '\\config.in', dst_path)
        shutil.copy(src_path + '\\config.mk', dst_path)
        shutil.copy(src_path + '\\autoconf.h', dst_path)

        target_dir = dst_path + '\\include'
        src_path_inc = src_path + '\\include'
        if os.path.exists(target_dir):
            shutil.rmtree(target_dir, ignore_errors=True)
        if not os.path.exists(src_path_inc):
            os.makedirs(src_path_inc)
        if not os.path.exists(target_dir):
            shutil.copytree(src_path + '\\include', dst_path + '\\include')
    else:
        src_path = abs_path + '/system/platform/' + plat + '/boards/' + real_board + '/config'
        dst_path = abs_path + '/config'

        shutil.copy(src_path + '/config.in', dst_path)
        shutil.copy(src_path + '/config.mk', dst_path)
        shutil.copy(src_path + '/autoconf.h', dst_path)

        target_dir = dst_path + '/include'
        src_path_inc = src_path + '/include'
        if os.path.exists(target_dir):
            shutil.rmtree(target_dir, ignore_errors=True)
        if not os.path.exists(src_path_inc):
            os.makedirs(src_path_inc)
        if not os.path.exists(target_dir):
            shutil.copytree(src_path + '/include', dst_path + '/include')

    cmd_str = 'make menuconfig PY=' + argv[1] + host_spec
    os.system(cmd_str)

    if host_spec == ' HOST=win32':
        shutil.copy(dst_path + '\\config.in', src_path)
        shutil.copy(dst_path + '\\config.mk', src_path)
        shutil.copy(dst_path + '\\autoconf.h', src_path)
        target_dir = src_path + '\\include'
        if os.path.exists(target_dir):
            shutil.rmtree(target_dir, ignore_errors=True)
        if not os.path.exists(target_dir):
            shutil.copytree(dst_path + '\\include', src_path + '\\include')
    else:
        shutil.copy(dst_path + '/config.in', src_path)
        shutil.copy(dst_path + '/config.mk', src_path)
        shutil.copy(dst_path + '/autoconf.h', src_path)
        target_dir = src_path + '/include'
        if os.path.exists(target_dir):
            shutil.rmtree(target_dir, ignore_errors=True)
        if not os.path.exists(target_dir):
            shutil.copytree(dst_path + '/include', src_path + '/include')


# clean cmd process
def clean_proc():
    if os.path.exists("output\\tmp\\app_record.tmp"):
        with open("output\\tmp\\app_record.tmp", 'r', encoding='utf-8') as tmp_app_entry_file:
            old_app_entry_str = (tmp_app_entry_file.read()).strip()
            if old_app_entry_str == "services/microPython" or old_app_entry_str == "services/micropython":
                if not os.path.exists("services\\microPython\\microPython.mk"):
                    print("!!!Warning!!! Micropython makefile has been deleted, try to fix it !!!")
                    move_micropython_dependencies(old_app_entry_str)
    cmd_str = 'make clean PY=' + argv[1]
    os.system(cmd_str)

# clean cmd process
def private_clean_proc():
    cmd_str = 'make private_clean PY=' + argv[1]
    os.system(cmd_str)

# get plat by board
def get_plat_by_board(board):
    if not os.path.exists(platform_json):
        error_proc(platform_json, 'NotFoundError', 'ECONF')
        return ''
    with open(platform_json, 'r', encoding='utf-8') as f:
        platforms = json.load(f)
        for k,v in platforms.items():
            if board in v:
                return k
        return ''
def move_micropython_dependencies(app_entry):
    abs_path = os.getcwd()
    src_path = abs_path + '/tools/micropython/'
    dst_path = abs_path + '/../../'
    shutil.copy(src_path + '/gen.sh', dst_path)
    shutil.copy(src_path + '/micropython.mk', dst_path)
    shutil.copy(src_path + '/private.mk', dst_path)

def sdk_version_update(sdk_ver_update, abs_path, arg):
    version_x = "1"
    version_y = "0"
    version_z_str = "1"
    version_z = 0
    fw_version_cache = None
    fw_version = None

    with open(abs_path + '\\system\\include\\quectel_version.h', 'r') as file:
        for line in file:
            data = line.strip()
            if "VERSION_MAJOR" in data:
                version_x = data.split(' ')[-1]
            if "VERSION_MINOR" in data:
                version_y = data.split(' ')[-1]
            if "VERSION_MICRO" in data:
                version_z_str = data.split(' ')[-1]
            if "mob_sw_rev" in data:
                fw_version_cache = data
    version_z = int(version_z_str) + 1
    if sdk_ver_update:
        fw_version = '#define mob_sw_rev  \"' + arg + '\"\n' 
    else:
        fw_version = fw_version_cache + '\n'

    version_content='#ifndef __QUECTEL_VERSION_H__\n' + \
                    '#define __QUECTEL_VERSION_H__\n\n' + \
                    fw_version + '\n' + \
                    '#define VERSION_MAJOR  ' + version_x + '\n'\
                    '#define VERSION_MINOR  ' + version_y + '\n'\
                    '#define VERSION_MICRO  ' + str(version_z) + '\n'\
                    '\n\n#endif'
    with open(abs_path + '\\system\\include\\quectel_version.h', 'w+') as f:
        f.write(version_content)

# make cmd process
def make_proc():
    global argv
    global argc
    got_plat = False
    got_noos = False
    got_verbose = False
    got_seq_params = False
    got_fw_name = False
    got_qpyver = False
    sdk_ver_update = False
    app_entry = argv[3].replace('\\', '/')

    app_entry_chr_list = list(app_entry)

    for i in list(reversed(range(0, len(app_entry_chr_list)))):
        if app_entry_chr_list[i-len(app_entry_chr_list)] == '/':
            app_entry_chr_list[i-len(app_entry_chr_list)] = ''
        else:
            break

    app_entry = ''.join(app_entry_chr_list)

    if not len(app_entry) or not os.path.exists(os.path.abspath(app_entry)):
        error_proc(argv[3], 'NotFoundError', 'EARGV')
        return
    
    cmd_str = argv[2] + ' APP_ENTRY=' + app_entry
    
    if argc != 4:
        for arg in argv[4:]:
            if arg.find('@') >= 0: # sequential parameters process
                if got_seq_params:
                    error_proc(arg)
                    return
                else:
                    seq_params = arg.split('@')
                    for i in seq_params:
                        if i == '':
                            pass
                        elif get_plat_by_board(i):
                            if got_plat:
                                error_proc(i)
                                return
                            else:
                                abs_path = os.getcwd()
                                real_board = i.split('*')[0]
                                plat = get_plat_by_board(i)

                                if host_spec == ' HOST=win32':
                                    src_path = abs_path + '\\system\\platform\\' + plat + '\\boards\\' + real_board + '\\config'
                                    dst_path = abs_path + '\\config'
                                    if not filecmp.cmp(src_path + '\\config.in', dst_path + '\\config.in', shallow=False):
                                        shutil.copy(src_path + '\\config.in', dst_path)
                                    if not filecmp.cmp(src_path + '\\config.mk', dst_path + '\\config.mk', shallow=False):
                                        shutil.copy(src_path + '\\config.mk', dst_path)
                                    if not filecmp.cmp(src_path + '\\autoconf.h', dst_path + '\\autoconf.h', shallow=False):
                                        shutil.copy(src_path + '\\autoconf.h', dst_path)

                                    target_dir = dst_path + '\\include'
                                    src_path_inc = src_path + '\\include'
                                    if os.path.exists(target_dir):
                                        shutil.rmtree(target_dir, ignore_errors=True)
                                    if not os.path.exists(src_path_inc):
                                        os.makedirs(src_path_inc)
                                    if not os.path.exists(target_dir):
                                        shutil.copytree(src_path + '\\include', dst_path + '\\include')
                                else:
                                    src_path = abs_path + '/system/platform/' + plat + '/boards/' + real_board + '/config'
                                    dst_path = abs_path + '/config'
                                    if not filecmp.cmp(src_path + '/config.in', dst_path + '/config.in', shallow=False):
                                        shutil.copy(src_path + '/config.in', dst_path)
                                    if not filecmp.cmp(src_path + '/config.mk', dst_path + '/config.mk', shallow=False):
                                        shutil.copy(src_path + '/config.mk', dst_path)
                                    if not filecmp.cmp(src_path + '/autoconf.h', dst_path + '/autoconf.h', shallow=False):
                                        shutil.copy(src_path + '/autoconf.h', dst_path)

                                    target_dir = dst_path + '/include'
                                    src_path_inc = src_path + '/include'
                                    if os.path.exists(target_dir):
                                        shutil.rmtree(target_dir, ignore_errors=True)
                                    if not os.path.exists(src_path_inc):
                                        os.makedirs(src_path_inc)
                                    if not os.path.exists(target_dir):
                                        shutil.copytree(src_path + '/include', dst_path + '/include')

                                cmd_str = cmd_str + ' PLAT=' + plat + ' BOARD=' + real_board
                                got_plat = True
                        elif i == 'NOOS':
                            if got_noos:
                                error_proc(i)
                                return
                            else:
                                cmd_str = cmd_str + ' NOOS=y'
                                got_noos = True
                        elif i == 'verbose':
                            if got_verbose:
                                error_proc(i)
                                return
                            else:
                                cmd_str = cmd_str + ' V=1'
                                got_verbose = True
                        elif i.startswith('VER='):
                            if got_qpyver:
                                error_proc(i)
                                return
                            else:
                                cmd_str = cmd_str + ' ' + i
                                got_qpyver = True
                        elif i.startswith('UPD'):
                            sdk_ver_update = True
                        else:
                            error_proc(i)
                            return
                    got_seq_params = True
            else:
                if got_fw_name:
                    error_proc(arg)
                    return
                else:
                    cmd_str = cmd_str + ' FW_NAME=' + arg
                    got_fw_name = True
                    
    # if got_fw_name:
    #     sdk_version_update(sdk_ver_update, abs_path, arg)
    cmd_str = cmd_str + host_spec
    cmd_str = cmd_str + ' PY=' + argv[1]
    cmd_str = cmd_str + ' 2>&1 | tee ' + app_entry + build_log_dir + arg + '/' + build_log_file

    move_micropython_dependencies(app_entry)
    os.system(cmd_str)

# flash cmd process
def flash_proc():
    global argv
    global argc
    
    if argc != 4:
        error_proc('arguments count error')
        return
    else:
        app_entry = argv[3].replace('\\', '/')

        app_entry_chr_list = list(app_entry)

        for i in list(reversed(range(0, len(app_entry_chr_list)))):
            if app_entry_chr_list[i-len(app_entry_chr_list)] == '/':
                app_entry_chr_list[i-len(app_entry_chr_list)] = ''
            else:
                break

        app_entry = ''.join(app_entry_chr_list)

        if not len(app_entry) or not os.path.exists(os.path.abspath(app_entry)):
            error_proc(argv[3], 'NotFoundError', 'EARGV')
            return
        
        cmd_str = 'make flash APP_ENTRY=' + app_entry + ' PY=' + argv[1]
        os.system(cmd_str)

# main entry:
if __name__ == '__main__':
    if argc > 6:
        error_proc(argv[6:], 'EARGC')
        exit()

    if argc == 2:
        help_proc()
    elif argc == 3:
        if argv[2] == 'help':
            help_proc()
        elif argv[2] == 'clean':
            clean_proc()
        elif argv[2] == 'private_clean':
            private_clean_proc()
        else:
            error_proc(argv[2])
    elif argc == 4:
        if argv[2] == 'menuconfig':
            menuconfig_proc(argv[3])
        elif argv[2] == 'flash':
            flash_proc()
        else:
            error_proc(argv[2])
    else:
        if argv[2] == 'make':
            make_proc()
        else:
            error_proc(argv[2])
