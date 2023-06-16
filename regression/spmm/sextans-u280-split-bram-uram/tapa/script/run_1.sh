
tapac \
  --work-dir run \
  --top Sextans_1 \
  --part-num xcu55c-fsvh2892-2L-e \
  --clock-period 3.33 \
  -o Sextans.xo \
  --floorplan-output Sextans_floorplan.tcl \
  --connectivity ../src/link_config.ini \
  ../src/kernel_1.cpp \
   2>&1 | tee tapa.log
