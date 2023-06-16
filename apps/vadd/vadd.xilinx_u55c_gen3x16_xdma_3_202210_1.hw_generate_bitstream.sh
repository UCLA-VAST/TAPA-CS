#!/bin/bash
TARGET=hw
# TARGET=hw_emu
# DEBUG=-g

TOP=VecAdd
XO='/home/nehaprakriya/tapa/apps/vadd/vadd.xilinx_u55c_gen3x16_xdma_3_202210_1.hw.xo'
>&2 echo "Using the default clock target of the platform."
PLATFORM=xilinx_u55c_gen3x16_xdma_3_202210_1
OUTPUT_DIR="$(pwd)/vitis_run_${TARGET}"

MAX_SYNTH_JOBS=8
STRATEGY="Explore"
PLACEMENT_STRATEGY="EarlyBlockPlacement"

v++ ${DEBUG} \
  --link \
  --output "${OUTPUT_DIR}/${TOP}_${PLATFORM}.xclbin" \
  --kernel ${TOP} \
  --platform ${PLATFORM} \
  --target ${TARGET} \
  --report_level 2 \
  --temp_dir "${OUTPUT_DIR}/${TOP}_${PLATFORM}.temp" \
  --optimize 3 \
  --connectivity.nk ${TOP}:1:${TOP} \
  --save-temps \
  "${XO}" \
  --vivado.synth.jobs ${MAX_SYNTH_JOBS} \
  --vivado.prop=run.impl_1.STEPS.PHYS_OPT_DESIGN.IS_ENABLED=1 \
  --vivado.prop=run.impl_1.STEPS.OPT_DESIGN.ARGS.DIRECTIVE=$STRATEGY \
  --vivado.prop=run.impl_1.STEPS.PLACE_DESIGN.ARGS.DIRECTIVE=$PLACEMENT_STRATEGY \
  --vivado.prop=run.impl_1.STEPS.PHYS_OPT_DESIGN.ARGS.DIRECTIVE=$STRATEGY \
  --vivado.prop=run.impl_1.STEPS.ROUTE_DESIGN.ARGS.DIRECTIVE=$STRATEGY \
