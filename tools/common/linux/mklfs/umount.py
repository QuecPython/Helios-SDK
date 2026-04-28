#! /usr/bin/env python3

import subprocess
from common import (
    IMAGE_NAME_DFT,
    MountStatus,
    get_config,
    set_config,
    get_mount_dir_name,
    get_mount_status
)

def _umount(dir):
    if subprocess.run(['umount', dir], stdout=subprocess.PIPE, stderr=subprocess.DEVNULL, text=True).returncode == 0:
        return True
    return False

def _detach_loop_dev(loop_dev):
    if subprocess.run(['sudo', 'losetup', '-d', loop_dev], stdout=subprocess.PIPE, stderr=subprocess.DEVNULL, text=True).returncode == 0:
        return True
    return False

def umount_image(image = None):
    if not image:
        raise Exception("Must specify an image!")

    mount_dir_name = get_mount_dir_name(image)
    print(f"Umounting dir: {mount_dir_name}...")
    if not _umount(mount_dir_name):
        raise Exception(f"Failed to umount dir: {mount_dir_name}!")

    config = get_config(image)
    status = get_mount_status(image)
    if status == MountStatus.MOUNTED:
        loop_dev = config['loop_dev']
        print(f"Detaching loop device:{loop_dev}...")
        if not _detach_loop_dev(loop_dev):
            raise Exception("Failed to detach loop device!")

        print("Saving config...")
        set_config(loop_dev, image, int(config['format'][-1]))

        print(f"Successfully umounted lfs{int(config['format'][-1])} image.")
    else:
        print("Image is already been umounted.")