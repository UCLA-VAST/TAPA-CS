
tapac \
  --work-dir run \
  --top Sextans \
  --part-num xcu55c-fsvh2892-2L-e \
  --clock-period 3.33 \
  -o Sextans.xo \
  --floorplan-output Sextans_floorplan.tcl \
  --connectivity ../src/link_config.ini \
  ../src/spmm_2.cpp \
  --multi-fpga 2 \
   2>&1 | tee tapa.log
