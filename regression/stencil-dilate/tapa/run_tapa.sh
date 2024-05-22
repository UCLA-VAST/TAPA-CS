#! /bin/bash

# originall tested on 2020.2
# source /opt/tools/xilinx/Vitis_HLS/2020.2/settings64.sh

WORK_DIR=run_128_2048_2048_dwidth_512
mkdir -p ${WORK_DIR}

tapac \
  --work-dir ${WORK_DIR} \
  --platform xilinx_u55c_gen3x16_xdma_3_202210_1 \
  --clock-period 3.33 \
  --other-hls-configs "config_compile -unsafe_math_optimizations" \
  \
  --top unikernel \
  -o "${WORK_DIR}/unikernel.xo" \
   --floorplan-output "${WORK_DIR}/unikernel_floorplan.tcl" \
  \
  \
  --connectivity ./src/unikernel.ini \
  ./src/unikernel.cpp
