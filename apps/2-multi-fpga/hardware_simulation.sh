#! /bin/bash

platform=xilinx_u55c_gen3x16_xdma_3_202210_1
v++ -o vadd.$platform.hw_emu.xclbin --link --target hw_emu --kernel VecAdd --platform $platform vadd.$platform.hw.xo