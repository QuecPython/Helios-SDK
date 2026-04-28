#! /usr/bin/env python3

import subprocess
from common import (
    LFS1_IMAGE_NAME_DFT,
    LFS2_IMAGE_NAME_DFT,
    BLOCK_SIZE_DFT,
    BLOCK_COUNT_DFT,
    LFS_FORMAT_DFT,
    get_free_loop_dev,
    chmod_add_rw_permission,
    attach_loop_dev,
    set_config,
    get_mount_dir_name,
    mkdir,
    mount
)

def _create_image(image, block_size, block_count):
    if subprocess.run(['dd', 'if=/dev/zero', 'of=' + image, 'bs=' + str(block_size), 'count=' + str(block_count)], stdout=subprocess.PIPE, stderr=subprocess.DEVNULL, text=True).returncode == 0:
        return True
    return False

def _format_image(lfs_cmd, loop_dev, lfs_format):
    lfs_cmd = './lfs' + str(lfs_format)
    if subprocess.run([lfs_cmd, '--format', loop_dev], stdout=subprocess.PIPE, stderr=subprocess.DEVNULL, text=True).returncode == 0:
        return True
    return False

def make_image(image = None, block_size = None, block_count = None, lfs_format = None):
    if not lfs_format:
        lfs_format = LFS_FORMAT_DFT
    else:
        lfs_format = int(lfs_format)

    if lfs_format == 1:
        if not image:
            image = LFS1_IMAGE_NAME_DFT
    elif lfs_format == 2:
        if not image:
            image = LFS2_IMAGE_NAME_DFT
    else:
        raise Exception(f"Invalid lfs format: {lfs_format}!")

    if not block_size:
        block_size = BLOCK_SIZE_DFT
    if not block_count:
        block_count = BLOCK_COUNT_DFT

    print("Getting free loop device...")
    free_loop_dev = get_free_loop_dev()
    if not free_loop_dev:
        raise Exception("No free loop device found!")
    
    print(f"Changing mode to 'a+rw' for free loop device: {free_loop_dev}...")
    if not chmod_add_rw_permission(free_loop_dev):
        raise Exception(f"Failed to add rw permission for {free_loop_dev}!")
    
    print(f"Creating a image: {image}...")
    if not _create_image(image, block_size, block_count):
        raise Exception(f"Failed to create image: {image}!")
    
    print("Attaching loop device...")
    if not attach_loop_dev(free_loop_dev, image):
        raise Exception(f"Failed to attach loop device: {free_loop_dev}!")

    print("Formatting image...")
    lfs_cmd = 'lfs' + str(lfs_format)
    if not _format_image(lfs_cmd, free_loop_dev, lfs_format):
        raise Exception(f"Failed to format loop device: {free_loop_dev}!")
    
    print(f"Making mount dir: {get_mount_dir_name(image)}...")
    if not mkdir(image):
        raise Exception(f"Failed to make dir: {get_mount_dir_name(image)}!")
    
    print(f"Mouting {free_loop_dev} to {get_mount_dir_name(image)}...")
    if not mount(free_loop_dev, image, lfs_format):
        raise Exception(f"Failed to mount {free_loop_dev} to {get_mount_dir_name(image)}!")
    
    print("Saving config...")
    set_config(free_loop_dev, image, lfs_format)

    print(f"Successfully maked lfs{lfs_format} image, you should put user data to {get_mount_dir_name(image)}.")