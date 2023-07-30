g++ -w -o knn-host knn-host-new.cpp kernel_1.cpp genColHost.hpp popl.hpp \
/home/ubuntu/AlveoLink/common/sw/src/xNativeFPGA.cpp /home/ubuntu/AlveoLink/network/roce_v2/sw/src/HiveNet.cpp /home/ubuntu/AlveoLink/network/roce_v2/sw/src/cmac.cpp \
-fmessage-length=0 \
-I /home/ubuntu/tapa_m/includes/ \
-I/home/ubuntu/tapa_m/apps/multi-fpga-vadd/src/ \
-I/opt/xilinx/xrt/include \
-I/tools/Xilinx/Vitis_HLS/2022.1/include \
-I/tools/Xilinx/Vitis/2022.1/include \
-std=c++17 -Wall -Wno-unknown-pragmas -Wno-unused-label  -g -O0  \
-ltapa -lfrt -lglog -lgflags -lOpenCL \
-I/home/ubuntu/tapa_m/apps/multi-fpga-vadd/host/ \
-I /home/ubuntu/AlveoLink/common/sw/include \
-I /home/ubuntu/AlveoLink/network/roce_v2/sw/include \
-I /home/ubuntu/tapa_m/build/ \
-pthread -L/opt/xilinx/xrt/lib -L/tools/Xilinx/Vitis_HLS/2022.1/lnx64/tools/fpo_v7_0  -Wl,--as-needed -lxrt_core -lrt -lstdc++ -luuid -lxrt_coreutil
