#! /bin/bash

WORK_DIR=run
mkdir -p "${WORK_DIR}"

tapac \
  --work-dir "${WORK_DIR}" \
  --top VecAdd \
  --platform xilinx_u55c_gen3x16_xdma_3_202210_1 \
  --clock-period 3.33 \
  -o "${WORK_DIR}/VecAdd.xo" \
  --floorplan-output "${WORK_DIR}/VecAdd_floorplan.tcl" \
  --connectivity link_config.ini \
  --multi-fpga 2 \
  vadd.cpp