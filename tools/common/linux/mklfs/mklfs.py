#! /usr/bin/env python

import argparse
import sys
from make import make_image
from mount import mount_image
from umount import umount_image
from clean import clean_image

class VersionSuffix():
    BASE_VERSION = 'base'
    ALPHA_VERSION = 'alpha'
    BETA_VERSION = 'beta'
    RC_VERSION = 'rc'
    RELEASE_VERSION = 'release'

MAJOR_VERSION = '1'
MINOR_VERSION = '0'
PATCH_VERSION = '0'
VERSION_SUFFIX = VersionSuffix.BETA_VERSION
VERSION_SUFFIX_NUM = '2'

formal_version = True

VERSION = 'mklfs ' + MAJOR_VERSION + '.' + MINOR_VERSION + '.' + PATCH_VERSION + ('' if formal_version else '_' + VERSION_SUFFIX + VERSION_SUFFIX_NUM)

# Create a parser
parser = argparse.ArgumentParser(description='Make littlefs image', prog='mklfs')
subparsers = parser.add_subparsers(dest='command', help='help for commands')

# Add a version argument
parser.add_argument('-v', '--version', action='version', version=VERSION)

# Add a parser for the 'make' command.
make_parser = subparsers.add_parser('make', help='make littlefs image')
make_parser.add_argument('-i', '--image', default='', dest='image', metavar='image', help='littlefs image')
make_parser.add_argument('-s', '--block-size', default='', dest='block_size', metavar='block_size', help='block size of littlefs image')
make_parser.add_argument('-c', '--block-count', default='', dest='block_count', metavar='block_count', help='block count of littlefs image')
make_parser.add_argument('-f', '--lfs-format', default='', dest='lfs_format', metavar='lfs_format', help='littlefs image format')

# Add a parser for the 'mount' command.
mount_parser = subparsers.add_parser('mount', help='mount littlefs image')
mount_parser.add_argument('-i', '--image', default='', dest='image', metavar='image', help='littlefs image')

# Add a parser for the 'umount' command.
umount_parser = subparsers.add_parser('umount', help='umount littlefs image')
umount_parser.add_argument('-i', '--image', default='', dest='image', metavar='image', help='littlefs image')

# Add a parser for the 'clean' command.
clean_parser = subparsers.add_parser('clean', help='clean littlefs image')
clean_parser.add_argument('-i', '--image', default='', dest='image', metavar='image', help='clean littlefs image')

# Add a parser for the 'help' command.
subparsers.add_parser('help', help='show this help page and exit')

args = parser.parse_args()
if args.command == 'make':
    make_image(args.image, args.block_size, args.block_count, args.lfs_format)
elif args.command == 'mount':
    mount_image(args.image)
elif args.command == 'umount':
    umount_image(args.image)
elif args.command == 'clean':
    clean_image(args.image)
else:
    parser.print_help()
