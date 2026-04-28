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

import json, os, re, sys

dep_dict = {}

def not_empty(s):
    if not s == '':
        return True
    return False

def path_optimizer(comp_path):
    app_path_split = comp_path.replace('\\', '/').split('/')
    return '/'.join(list(filter(not_empty, app_path_split)))

animation_idx = 0
def wait_animation():
    global animation_idx
    animation = "|/-\\"
    if(animation_idx >= 4):
        animation_idx = 0
    print('\b\b' + animation[animation_idx] + ' ', end='', flush=True)
    animation_idx += 1

def search_for_deps(comp_path):
    wait_animation()
    global dep_dict
    comp_path = path_optimizer(comp_path)
    if comp_path in dep_dict:
        return
    
    comp_mk = comp_path + '/' + comp_path.split('/')[-1] + '.mk'
    cmd = 'make --no-print-directory -f comp_info_tell.mk' + ' COMP_MK=' + comp_mk
    res = os.popen(cmd)
    ret = res.buffer.read().decode(encoding='utf-8')
    res.close()
    if not ret:
        raise RuntimeError('cmd [%s] execution error' % cmd)
    regex = re.compile(r'NAME: (.*)\nGLOBAL_INCS: (.*)\nGLOBAL_DEFINE: (.*)\nLOCAL_CFLAGS: (.*)\nLOCAL_ARCHIVES: (.*)\nLOCAL_SRCS: (.*)\nLOCAL_SRCS_2: (.*)\nLOCAL_SRCS_3: (.*)\nLOCAL_INCS: (.*)\nLOCAL_DEFINE: (.*)\nCOMP_DEPS: (.*)\n')
    mo = regex.findall(ret)
    
    name_list = mo[0][0].split(' ')
    global_incs = mo[0][1].split(' ')
    global_define = mo[0][2].split(' ')
    local_cflags = mo[0][3].split(' ')
    local_archives = mo[0][4].split(' ')
    local_srcs = mo[0][5].split(' ')
    local_srcs_2 = mo[0][6].split(' ')
    local_srcs_3 = mo[0][7].split(' ')
    local_incs = mo[0][8].split(' ')
    local_define = mo[0][9].split(' ')
    comp_deps = mo[0][10].split(' ')

    '''
    print('', flush=True)
    print('===================================', flush=True)
    print('name_list:', name_list, flush=True)
    print('global_incs:', global_incs, flush=True)
    print('global_define:', global_define, flush=True)
    print('local_cflags:', local_cflags, flush=True)
    print('local_archives:', local_archives, flush=True)
    print('local_srcs:', local_srcs, flush=True)
    print('local_incs:', local_incs, flush=True)
    print('local_define:', local_define, flush=True)
    print('comp_deps:', comp_deps, flush=True)
    print('===================================', flush=True)
    '''

    comp_info = {}

    if list(filter(not_empty, name_list)):
        comp_info['NAME'] = name_list
    if list(filter(not_empty, global_incs)):
        comp_info['GLOBAL_INCS'] = global_incs
    if list(filter(not_empty, global_define)):
        comp_info['GLOBAL_DEFINE'] = global_define
    if list(filter(not_empty, local_cflags)):
        comp_info['LOCAL_CFLAGS'] = local_cflags
    if list(filter(not_empty, local_archives)):
        comp_info['LOCAL_ARCHIVES'] = local_archives
    if list(filter(not_empty, local_srcs)):
        comp_info['LOCAL_SRCS'] = local_srcs
    if list(filter(not_empty, local_srcs_2)):
        comp_info['LOCAL_SRCS'] += local_srcs_2
    if list(filter(not_empty, local_srcs_3)):
        comp_info['LOCAL_SRCS'] += local_srcs_3
    if list(filter(not_empty, local_incs)):
        comp_info['LOCAL_INCS'] = local_incs
    if list(filter(not_empty, local_define)):
        comp_info['LOCAL_DEFINE'] = local_define
    if list(filter(not_empty, comp_deps)):
        comp_info['COMP_DEPS'] = comp_deps
    
    if comp_mk != 'system/system.mk' and not comp_mk.startswith("system/"):
        if 'COMP_DEPS' in comp_info:
            if 'system' not in comp_info['COMP_DEPS']:
                comp_info['COMP_DEPS'].append('system')
        else:
            comp_info['COMP_DEPS'] = ['system']
    
    for i in comp_info:
        comp_info[i] = list(filter(not_empty, comp_info[i]))

    dep_dict[comp_path] = comp_info

    if 'COMP_DEPS' in dep_dict[comp_path]:
        for comp in dep_dict[comp_path]['COMP_DEPS']:
            search_for_deps(comp)

def dependency_proc(component, last = None):
    global dep_dict
    wait_animation()
    if 'COMP_DEPS' in dep_dict[component]:
        if last:
            last_dep = dep_dict[last]['COMP_DEPS']
            for dep in dep_dict[component]['COMP_DEPS']:
                if dep not in last_dep:
                    last_dep.append(dep)
        for comp in dep_dict[component]['COMP_DEPS']:
            dependency_proc(comp, component)

def compile_option_proc(component, last = []):
    wait_animation()
    global dep_dict
    if 'LOCAL_INCS' in dep_dict[component]:
        for inc in dep_dict[component]['LOCAL_INCS']:
            if 'INC_COLLECT' not in dep_dict[component]:
                dep_dict[component]['INC_COLLECT'] = []
            inc = component + '/' + inc
            if inc not in dep_dict[component]['INC_COLLECT']:
                dep_dict[component]['INC_COLLECT'].append(inc)
    if 'GLOBAL_INCS' in dep_dict[component]:
        for inc in dep_dict[component]['GLOBAL_INCS']:
            if 'INC_COLLECT' not in dep_dict[component]:
                dep_dict[component]['INC_COLLECT'] = []
            inc = component + '/' + inc
            if inc not in dep_dict[component]['INC_COLLECT']:
                dep_dict[component]['INC_COLLECT'].append(inc)
            for lst in last:
                if 'INC_COLLECT' not in dep_dict[lst]:
                    dep_dict[lst]['INC_COLLECT'] = []
                if 'INC_COLLECT' in dep_dict[lst] and inc not in dep_dict[lst]['INC_COLLECT']:
                    if 'COMP_DEPS' in dep_dict[lst] and component in dep_dict[lst]['COMP_DEPS']:
                        dep_dict[lst]['INC_COLLECT'].append(inc)
    if 'GLOBAL_DEFINE' in dep_dict[component]:
        for define in dep_dict[component]['GLOBAL_DEFINE']:
            if 'DEF_COLLECT' not in dep_dict[component]:
                dep_dict[component]['DEF_COLLECT'] = []
            if define not in dep_dict[component]['DEF_COLLECT']:
                dep_dict[component]['DEF_COLLECT'].append(define)
            for lst in last:
                if 'DEF_COLLECT' not in dep_dict[lst]:
                    dep_dict[lst]['DEF_COLLECT'] = []
                if 'DEF_COLLECT' in dep_dict[lst] and define not in dep_dict[lst]['DEF_COLLECT']:
                    if 'COMP_DEPS' in dep_dict[lst] and component in dep_dict[lst]['COMP_DEPS']:
                        dep_dict[lst]['DEF_COLLECT'].append(define)
    if 'LOCAL_DEFINE' in dep_dict[component]:
        for define in dep_dict[component]['LOCAL_DEFINE']:
            if 'DEF_COLLECT' not in dep_dict[component]:
                dep_dict[component]['DEF_COLLECT'] = []
            if define not in dep_dict[component]['DEF_COLLECT']:
                dep_dict[component]['DEF_COLLECT'].append(define)
    if 'COMP_DEPS' in dep_dict[component]:
        last.append(component)
        for comp in dep_dict[component]['COMP_DEPS']:
            compile_option_proc(comp, last)
        last = []

def compile_proc():
    comp_archive_list = []
    user_archive_list = []
    for k,v in dep_dict.items():
        if 'LOCAL_SRCS' in v and v['LOCAL_SRCS']:
            archive = os.environ['OUTPUT_OBJ_PATH'] + '/' + k + '/lib' + k.split('/')[-1] + '.a'
            comp_archive_list.append(archive)
            cmd = 'make --no-print-directory -j12 -f compilerules.mk'
            os.environ['COMP_PATH'] = k
            if 'INC_COLLECT' in v and v['INC_COLLECT']:
                comp_iflags = ' '.join(v['INC_COLLECT'])
                os.environ['COMP_IFLAGS'] = comp_iflags
            if 'DEF_COLLECT' in v and v['DEF_COLLECT']:
                comp_dflags = ' '.join(v['DEF_COLLECT'])
                os.environ['COMP_DFLAGS'] = comp_dflags
            if os.system(cmd):
                raise RuntimeError('cmd [%s] execution error' % cmd)
        if 'LOCAL_ARCHIVES' in v and v['LOCAL_ARCHIVES']:
            user_archive_list.extend(list(map(lambda x : k + '/' + x, v['LOCAL_ARCHIVES'])))      
    
    target_bin = os.environ['TARGET_BIN']
    cmd = 'make --no-print-directory -f link.mk ' + target_bin + ' COMP_ARCHIVES="' + ' '.join(comp_archive_list) + '"' + ' USER_ARCHIVES="' + ' '.join(user_archive_list) + '"'
    if os.system(cmd):
        raise RuntimeError('cmd [%s] execution error' % cmd)
    if os.environ['PLAT'] != 'RDA' and os.environ['PLAT'] != 'Qualcomm':
        target_hex = os.environ['TARGET_HEX']
        cmd = 'make --no-print-directory -f link.mk ' + target_hex + ' COMP_ARCHIVES="' + ' '.join(comp_archive_list) + '"' + ' USER_ARCHIVES="' + ' '.join(user_archive_list) + '"'
        if os.system(cmd):
            raise RuntimeError('cmd [%s] execution error' % cmd)

def build_proc(app):
    print('\n[searching for all components ...]   ', end = '', flush=True)
    search_for_deps(app)
    print('')
    for k in dep_dict:
        print('-', k, flush=True)
    print('\n[finding dependency among components ...]   ', end = '', flush=True)
    dependency_proc(app)
    print('')
    print('\n[generating compile options for per component ...]   ', end = '', flush=True)
    compile_option_proc(app)
    print('')
    dependency_json = os.environ['OUTPUT_TMP_PATH'] + '/' + 'dependency.json'
    with open(dependency_json, 'w') as f:
        json.dump(dep_dict, f, indent = 3)
    print('\n[starting compiling ...]\n', flush=True)
    compile_proc()

build_proc(path_optimizer(sys.argv[1]))
