platform=xilinx_u55c_gen3x16_xdma_3_202210_1
tapac -o cnn_1_8.$platform.hw.xo kernel_1_8_prof.cpp \
  --platform $platform \
  --top kernel3 \
  --work-dir cnn_1_8.$platform.hw.xo.tapa \
  --connectivity link_config_1_8.ini \
  --enable-floorplan \
  --constraint constraint_1_8.tcl \
  --enable-synth-util \
  --floorplan-strategy QUICK_FLOORPLANNING \

