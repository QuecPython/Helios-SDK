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

def _rm_image(image, dir):
    if subprocess.run(['rm', '-rf', image, dir], stdout=subprocess.PIPE, stderr=subprocess.DEVNULL, text=True).returncode == 0:
        return True
    return False

def clean_image(image = None):
    if not image:
        raise Exception("Must specify an image!")

    mount_dir_name = get_mount_dir_name(image)

    config = get_config(image)
    status = get_mount_status(image)
    if status == MountStatus.UMOUNTED:
        print(f"Removing {image} and {mount_dir_name}...")
        if not _rm_image(image, mount_dir_name):
            raise Exception(f"Failed to remove {image} and {mount_dir_name}!")

        print("Updating config...")
        set_config(None, image, None, del_item = True)

        print(f"Successfully umounted lfs{int(config['format'][-1])} image.")
    else:
        raise Exception("Failed to clean image, must umount image firstly!")