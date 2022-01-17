#!/bin/bash

source /home/yshi10/workspace_pma/8155_repos/qnx.sdk/qnx_bins/prebuilt_QNX700/qnxsdp-env.sh

mkdir -p build

cd build

pwd

cmake -DCMAKE_TOOLCHAIN_FILE=/home/yshi10/yfv_osi/nets/QNX.cmake ../

# make clean

# make
