#!/usr/bin/env python3
import subprocess
import os
import json

LFS1_IMAGE_NAME_DFT = 'lfs1.img'
LFS2_IMAGE_NAME_DFT = 'lfs2.img'
IMAGE_NAME_DFT = LFS2_IMAGE_NAME_DFT
BLOCK_SIZE_DFT = 4096
BLOCK_COUNT_DFT = 128

LFS_FORMAT_DFT = 2

CONFIG_FILE = 'lfs.json'

class MountStatus():
    MOUNTED = 'mounted'
    UMOUNTED = 'umounted'

def _get_config():
    if os.path.exists(CONFIG_FILE):
        with open(CONFIG_FILE, 'r') as f:
            return json.load(f)
    else:
        return []

def get_config(image = IMAGE_NAME_DFT):
    config_list = _get_config()

    for i, c in enumerate(config_list):
        if c['image'] == image:
            return config_list[i]
    return {}

def set_config(loop_dev, image = IMAGE_NAME_DFT, lfs_format = LFS_FORMAT_DFT, del_item = False):
    config_list = _get_config()

    for i, c in enumerate(config_list):
        if c['image'] == image:
            del config_list[i]
            break

    if not del_item:
        config = {}
        config.update({'image': image, 'format': 'lfs' + str(lfs_format), 'loop_dev': loop_dev})
        config_list.append(config)
    with open(CONFIG_FILE, 'w') as f:
        json.dump(config_list, f, indent = 4)

def get_free_loop_dev():
    result = subprocess.run(['losetup', '-f'], stdout=subprocess.PIPE, stderr=subprocess.DEVNULL, text=True)
    if result.returncode == 0:
        return result.stdout.strip()
    else:
        return ''

def chmod_add_rw_permission(loop_dev):
    if subprocess.run(['sudo', 'chmod', 'a+rw', loop_dev], stdout=subprocess.PIPE, stderr=subprocess.DEVNULL, text=True).returncode == 0:
        return True
    return False

def attach_loop_dev(loop_dev, image):
    if subprocess.run(['losetup', loop_dev, image], stdout=subprocess.PIPE, stderr=subprocess.DEVNULL, text=True).returncode == 0:
        return True
    return False

def get_mount_dir_name(image = IMAGE_NAME_DFT):
    return image + '.mount'

def mkdir(image):
    mount_dir_name = get_mount_dir_name(image)
    if not os.path.exists(mount_dir_name):
        if subprocess.run(['mkdir', mount_dir_name], stdout=subprocess.PIPE, stderr=subprocess.DEVNULL, text=True).returncode == 0:
            return True
        return False
    return True

def mount(loop_dev, image, lfs_format = LFS_FORMAT_DFT):
    mount_dir_name = get_mount_dir_name(image)
    lfs_cmd = './lfs' + str(lfs_format)
    if subprocess.run([lfs_cmd, loop_dev, mount_dir_name], stdout=subprocess.PIPE, stderr=subprocess.DEVNULL, text=True).returncode == 0:
        return True
    return False

def get_mount_status(image = IMAGE_NAME_DFT):
    image_abspath = os.path.abspath(image)
    result = subprocess.run(['losetup', '-a', '|', 'grep', image], stdout=subprocess.PIPE, stderr=subprocess.DEVNULL, text=True)
    if result.returncode == 0:
        mount_result = result.stdout.strip()
        if f'({image_abspath})' in mount_result:
            return MountStatus.MOUNTED
        else:
            return MountStatus.UMOUNTED
    else:
        raise Exception('Failed to get mount status of image: ' + image)