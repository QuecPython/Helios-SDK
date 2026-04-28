#! /usr/bin/env python3

import subprocess
from common import (
    IMAGE_NAME_DFT,
    get_free_loop_dev,
    chmod_add_rw_permission,
    attach_loop_dev,
    get_config,
    set_config,
    get_mount_dir_name,
    mkdir,
    mount
)

def mount_image(image = None):
    if not image:
        raise Exception("Must specify an image!")

    print("Getting free loop device...")
    free_loop_dev = get_free_loop_dev()
    if not free_loop_dev:
        raise Exception("No free loop device found!")
    
    print(f"Changing mode to 'a+rw' for free loop device: {free_loop_dev}...")
    if not chmod_add_rw_permission(free_loop_dev):
        raise Exception(f"Failed to add rw permission for {free_loop_dev}!")
    
    print("Attaching loop device...")
    if not attach_loop_dev(free_loop_dev, image):
        raise Exception(f"Failed to attach loop device: {free_loop_dev}!")

    print(f"Making mount dir: {get_mount_dir_name(image)}...")
    if not mkdir(image):
        raise Exception(f"Failed to make dir: {get_mount_dir_name(image)}!")
    
    print(f"Mouting {free_loop_dev} to {get_mount_dir_name(image)}...")
    config = get_config(image)
    lfs_format = int(config['format'][-1])
    if not mount(free_loop_dev, image, lfs_format):
        raise Exception(f"Failed to mount {free_loop_dev} to {get_mount_dir_name(image)}!")
    
    print("Saving config...")
    set_config(free_loop_dev, image, lfs_format)

    print(f"Successfully mounted lfs{lfs_format} image, you should put user data to {get_mount_dir_name(image)}.")