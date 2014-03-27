#!/bin/zsh

set -e

./configure --enable-debug --enable-developer \
            --with-samba-source=/home/vortec/workspace/samba/source3
