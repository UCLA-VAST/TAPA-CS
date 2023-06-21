platform=xilinx_u55c_gen3x16_xdma_3_202210_1
tapac -o cnn_1_8.$platform.hw.xo kernel_1_8.cpp \
  --platform $platform \
  --top kernel3_1 \
  --work-dir cnn_1_8.$platform.hw.xo.tapa 