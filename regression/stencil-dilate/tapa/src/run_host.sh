gcc -w -o stencil main.cpp kernel_1.cpp genColHost.hpp popl.hpp \
/home/nehaprakriya/AlveoLink/common/sw/src/xNativeFPGA.cpp /home/nehaprakriya/AlveoLink/network/roce_v2/sw/src/HiveNet.cpp /home/nehaprakriya/AlveoLink/network/roce_v2/sw/src/cmac.cpp \
-fmessage-length=0 \
-I /home/nehaprakriya/TAPA-CS/includes/ \
-I/home/nehaprakriya/TAPA-CS/apps/multi-fpga-vadd/src/ \
-I/opt/xilinx/xrt/include \
-I/tools/Xilinx/Vitis_HLS/2022.1/include \
-I/tools/Xilinx/Vitis/2022.1/include \
-std=c++17 -Wall -Wno-unknown-pragmas -Wno-unused-label  -g -O0  \
-ltapa -lfrt -lglog -lgflags -lOpenCL \
-I/home/nehaprakriya/TAPA-CS/apps/multi-fpga-vadd/host/ \
-I /home/nehaprakriya/AlveoLink/common/sw/include \
-I /home/nehaprakriya/AlveoLink/network/roce_v2/sw/include \
-I /home/nehaprakriya/TAPA-CS/build/ \
-pthread -L/opt/xilinx/xrt/lib -L/tools/Xilinx/Vitis_HLS/2022.1/lnx64/tools/fpo_v7_0  -Wl,--as-needed -lxrt_core -lrt -lstdc++ -luuid -lxrt_coreutil

# g++ -O2 kernel_1.cpp main.cpp genColHost.hpp popl.hpp DILATE.h \
# /home/nehaprakriya/AlveoLink/common/sw/src/xNativeFPGA.cpp /home/nehaprakriya/AlveoLink/network/roce_v2/sw/src/HiveNet.cpp \
# /home/nehaprakriya/AlveoLink/network/roce_v2/sw/src/cmac.cpp -o stencil  \
# -fmessage-length=0 -ltapa -lfrt -lglog -lgflags -lOpenCL \
# -std=c++17
# -I/tools/Xilinx/Vitis_HLS/2022.1/include -I/opt/xilinx/xrt/include -I /home/nehaprakriya/tapa/includes/ \
# -I/home/nehaprakriya/tapa/apps/multi-fpga-vadd/src/ -I /home/nehaprakriya/AlveoLink/common/sw/include \
#  -I /home/nehaprakriya/AlveoLink/network/roce_v2/sw/include -pthread -L/opt/xilinx/xrt/lib -L/tools/Xilinx/Vitis_HLS/2022.1/lnx64/tools/fpo_v7_0  \
#  -Wl,--as-needed -lxrt_core -lrt -lstdc++ -luuid -lxrt_coreutil