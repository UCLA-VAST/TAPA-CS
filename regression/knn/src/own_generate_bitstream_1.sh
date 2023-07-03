TARGET=hw
TOP=Knn_1
CONSTRAINT='/home/nehaprakriya/tapa/regression/knn/src/tapacs_knn1/run-1/knn_1_floorplan.tcl'

MAX_SYNTH_JOBS=8
STRATEGY="Explore"
PLACEMENT_STRATEGY="EarlyBlockPlacement"
OUTPUT_DIR="$(pwd)/tapacs_knn_1_${TARGET}"
v++ ${DEBUG} \
    --platform /opt/xilinx/platforms/xilinx_u55c_gen3x16_xdma_3_202210_1/xilinx_u55c_gen3x16_xdma_3_202210_1.xpfm \
    --output "${OUTPUT_DIR}/${TOP}_${PLATFORM}.xclbin" \
    --config /home/nehaprakriya/tapa/regression/knn/src/kernel_1.ini \
    --define AL_mtuBytes=1472 \
    --define AL_maxConnections=16 \
    --define AL_netDataBits=512 \
    --define AL_destBits=16 \
    --include /home/nehaprakriya/AlveoLink/common/hw/include \
    --include /home/nehaprakriya/AlveoLink/kernel/hw/include \
    --include /home/nehaprakriya/AlveoLink/adapter/roce_v2/hw/include \
    --input_files /home/nehaprakriya/tapa/regression/knn/src/tapacs_knn1/run-1/knn_1.xo \
    --input_files /home/nehaprakriya/cmac_0.xo \
    --input_files /home/nehaprakriya/HiveNet_kernel_0.xo \
    --input_files /home/nehaprakriya/cmac_1.xo \
    --input_files /home/nehaprakriya/HiveNet_kernel_1.xo \
    --link \
    --optimize 2 \
    --report_level 2 \
    --temp_dir "${OUTPUT_DIR}/${TOP}_${PLATFORM}.temp" \
    --advanced.param compiler.userPostSysLinkOverlayTcl=/home/nehaprakriya/tapa/regression/knn/src/post_sys_link.tcl\
    --vivado.prop=run.impl_1.STEPS.PHYS_OPT_DESIGN.IS_ENABLED=true \
    --vivado.prop=run.impl_1.STEPS.OPT_DESIGN.ARGS.DIRECTIVE=$STRATEGY \
    --vivado.prop=run.impl_1.STEPS.PLACE_DESIGN.ARGS.DIRECTIVE=$PLACEMENT_STRATEGY \
    --vivado.prop=run.impl_1.STEPS.PHYS_OPT_DESIGN.ARGS.DIRECTIVE=$STRATEGY \
    --vivado.prop=run.impl_1.STEPS.PHYS_OPT_DESIGN.IS_ENABLED=true\
    --vivado.prop=run.impl_1.STEPS.PHYS_OPT_DESIGN.ARGS.DIRECTIVE=Explore\
    --vivado.prop=run.impl_1.STEPS.ROUTE_DESIGN.ARGS.DIRECTIVE=$STRATEGY \
    --vivado.prop=run.impl_1.STEPS.POST_ROUTE_PHYS_OPT_DESIGN.IS_ENABLED=true\
    --vivado.prop=run.impl_1.STEPS.POST_ROUTE_PHYS_OPT_DESIGN.ARGS.DIRECTIVE=AggressiveExplore\
    --vivado.prop=run.impl_1.STEPS.OPT_DESIGN.TCL.PRE=$CONSTRAINT \
    --save-temps \
