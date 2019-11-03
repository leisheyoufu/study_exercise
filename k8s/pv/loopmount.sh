#!/bin/bash

# Usage: sudo loopmount file size mount-point
#./loopmount.sh vol1 6G /mnt/dynamic/vol1

touch $1
truncate -s $2 $1
mke2fs -t ext4 -F $1 1> /dev/null 2> /dev/null
if [[ ! -d $3 ]]; then
        echo $3 " not exist, creating..."
        mkdir $3
fi
mount $1 $3
df -h |grep $3
~
