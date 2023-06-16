TARGET=hw
TOP=VecAdd_1
OUTPUT_DIR="$(pwd)/vitis_run_${TARGET}"
# v++ -c -D KERNEL_NAME=VecAdd --hls.clock 300000000:VecAdd -t hw --platform /opt/xilinx/platforms/xilinx_u55c_gen3x16_xdma_3_202210_1/xilinx_u55c_gen3x16_xdma_3_202210_1.xpfm --save-temps -D AL_mtuBytes=1472 -D AL_maxConnections=16 -D AL_netDataBits=512 -D AL_destBits=16 -I/home/nehaprakriya/AlveoLink/common/hw/include -I/home/nehaprakriya/AlveoLink/kernel/hw/include -I/home/nehaprakriya/AlveoLink/adapter/roce_v2/hw/include -I/home/ubuntu/tapa_m/apps/2-multi-fpga/ -k VecAdd --temp_dir _x_temp.hw.xilinx_u55c_gen3x16_xdma_3_202210_1 --report_dir /home/ubuntu/tapa_m/apps/2-multi-fpga/reports/_x.hw.xilinx_u55c_gen3x16_xdma_3_202210_1 -o x_temp.hw.xilinx_u55c_gen3x16_xdma_3_202210_1/vadd_1.xo /home/ubuntu/tapa_m/apps/2-multi-fpga/vadd_1.cpp
v++ ${DEBUG} \
    --advanced.param compiler.userPostSysLinkOverlayTcl=/home/ubuntu/tapa_m/apps/2-multi-fpga/post_sys_link.tcl\
    --platform /opt/xilinx/platforms/xilinx_u55c_gen3x16_xdma_3_202210_1/xilinx_u55c_gen3x16_xdma_3_202210_1.xpfm \
    --output "${OUTPUT_DIR}/${TOP}_${PLATFORM}.xclbin" \
    --config /home/ubuntu/tapa_m/apps/2-multi-fpga/conn_u55c_if2.tmp.cfg \
    --define AL_mtuBytes=1472 \
    --define AL_maxConnections=16 \
    --define AL_netDataBits=512 \
    --define AL_destBits=16 \
    --include /home/nehaprakriya/AlveoLink/common/hw/include \
    --include /home/nehaprakriya/AlveoLink/kernel/hw/include \
    --include /home/nehaprakriya/AlveoLink/adapter/roce_v2/hw/include \
    --input_files /home/ubuntu/tapa_m/apps/2-multi-fpga/vadd_1.xilinx_u55c_gen3x16_xdma_3_202210_1.hw.xo \
    --input_files /home/nehaprakriya/AlveoLink//../xup_vitis_network_example/Ethernet/_x.xilinx_u55c_gen3x16_xdma_3_202210_1/cmac_0.xo \
    --input_files /home/nehaprakriya/AlveoLink//../xup_vitis_network_example/Ethernet/_x.xilinx_u55c_gen3x16_xdma_3_202210_1/cmac_1.xo \
    --input_files /home/nehaprakriya/AlveoLink//network/roce_v2/hw/HiveNet/build/HiveNet_kernel_0.xo \
    --input_files /home/nehaprakriya/AlveoLink//network/roce_v2/hw/HiveNet/build/HiveNet_kernel_1.xo \
    --link \
    --kernel_frequency 150 \
    --optimize 2 \
    --report_level 2 \
    --temp_dir "${OUTPUT_DIR}/${TOP}_${PLATFORM}.temp" \
    --save-temps \