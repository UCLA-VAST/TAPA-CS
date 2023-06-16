TARGET=hw
TOP=unikernel
OUTPUT_DIR="$(pwd)/vitis_run_1_128_${TARGET}"
v++ ${DEBUG} \
    --platform /opt/xilinx/platforms/xilinx_u55c_gen3x16_xdma_3_202210_1/xilinx_u55c_gen3x16_xdma_3_202210_1.xpfm \
    --output "${OUTPUT_DIR}/${TOP}_${PLATFORM}.xclbin" \
    --config /home/ubuntu/tapa_m/regression/stencil-dilate/tapa/src/kernel_1.ini \
    --define AL_mtuBytes=1472 \
    --define AL_maxConnections=16 \
    --define AL_netDataBits=512 \
    --define AL_destBits=16 \
    --include /home/ubuntu/AlveoLink/common/hw/include \
    --include /home/ubuntu/AlveoLink/kernel/hw/include \
    --include /home/ubuntu/AlveoLink/adapter/roce_v2/hw/include \
    --input_files /home/ubuntu/tapa_m/regression/stencil-dilate/tapa/src/unikernel_1_28.xilinx_u55c_gen3x16_xdma_3_202210_1.hw.xo \
    --input_files /home/ubuntu/AlveoLink//../xup_vitis_network_example/Ethernet/_x.xilinx_u55c_gen3x16_xdma_3_202210_1/cmac_0.xo \
    --input_files /home/ubuntu/AlveoLink//network/roce_v2/hw/HiveNet/build/HiveNet_kernel_0.xo \
    --link \
    --optimize 2 \
    --report_level 2 \
    --temp_dir "${OUTPUT_DIR}/${TOP}_${PLATFORM}.temp" \
    --advanced.param compiler.userPostSysLinkOverlayTcl=/home/ubuntu/tapa_m/regression/stencil-dilate/tapa/src/post_sys_link.tcl\
    --save-temps \