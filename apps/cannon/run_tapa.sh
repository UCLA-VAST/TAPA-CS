#! /bin/bash

WORK_DIR=run
mkdir -p "${WORK_DIR}"

tapac \
  --work-dir "${WORK_DIR}" \
  --top Cannon \
  --part-num xcu55c-fsvh2892-2L-e \
  --clock-period 3.33 \
  -o "${WORK_DIR}/Cannon.xo" \
  --floorplan-output "${WORK_DIR}/Cannon_floorplan.tcl" \
  --connectivity link_config.ini \
  --multi-fpga 2 \
  cannon.cpp
