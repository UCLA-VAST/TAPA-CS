# 2020.2 results in smaller LUT usage
source /opt/tools/xilinx/Vitis_HLS/2022.1/settings64.sh

tapac \
  --work-dir run \
  --top Knn \
  --part-num xcu55c-fsvh2892-2L-e \
  --max-parallel-synth-jobs 8 \
  --clock-period 3.33 \
  -o knn.xo \
  --enable-synth-util \
  --floorplan-output knn_floorplan.tcl \
  --connectivity ../src/knn.ini \
<<<<<<< HEAD
  --floorplan-strategy QUICK_FLOORPLANNING \
  --multi-fpga 2\
=======
  --run-floorplan-dse \
  --max-parallel-synth-jobs 32 \
>>>>>>> 7107e487dade8a32d831151f03e44facb01a21e7
  ../src/knn.cpp
