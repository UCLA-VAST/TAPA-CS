#! /bin/bash

platform=xilinx_u55c_gen3x16_xdma_3_202210_1
tapac -o vadd.$platform.hw.xo vadd.cpp --platform $platform --top VecAdd --work-dir vadd.$platform.hw.xo.tapa