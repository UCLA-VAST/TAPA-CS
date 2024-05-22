VPP := $(XILINX_VITIS)/bin/v++
TAPAC := $(HOME)/.local/bin/tapac
EMCONFIGUTIL := $(XILINX_VITIS)/bin/emconfigutil
MODE := hw
PLATFORM := xilinx_u55c_gen3x16_xdma_3_202210_1

# sources
KERNEL_SRC := src/kernel/hac.cpp
KERNEL_HEADER := src/kernel/hac.h
HOST_SRC := src/host/host.cpp
HOST_P2P_SRC := src/host_p2p/host.cpp src/host_p2p/xcl2/*.cpp
TAPA_KERNEL_SRC := src/kernel_tap/hac.cpp
TAPA_KERNEL_HEADER := src/kernel_tap/hac.h

# targets
HOST_EXE := host.exe
HOST_P2P_EXE := host_p2p.exe
WORK_DIR := run3

XOS_ENCODING := encoding_kernel.$(MODE).xo
XOS_CLUSTERING := clustering_kernel.$(MODE).xo
XOS_TAPA := $(WORK_DIR)/wrapper.$(MODE).xo
XOS_WRAPPER := wrapper.$(MODE).xo

XCLBIN_ENCODING := hac_encoding.$(MODE).xclbin
XCLBIN := hac.$(MODE).xclbin
EMCONFIG_FILE := emconfig_new.json

VPP_LINK_OPTS := --profile.data all:all:all --profile.memory all --profile.stall all:all --profile.exec all:all --profile_kernel data:all:all:all --config connectivity.cfg
VPP_COMMON_OPTS := -s -t $(MODE) --platform $(PLATFORM) --report_level 2 --kernel_frequency 300 --optimize 3
TAPA_OPTS := --platform $(PLATFORM) --connectivity connectivity.cfg --work-dir ${WORK_DIR} --floorplan-output "${WORK_DIR}/wrapper.tcl" 


CFLAGS := -g -O3 -std=c++17 -I$(XILINX_XRT)/include -I$(XILINX_HLS)/include
LFLAGS := -L$(XILINX_XRT)/lib -lxilinxopencl -lpthread -lrt
NUMDEVICES := 1

# run time args
EXE_OPT := hac.$(MODE).xclbin

# primary build targets
.PHONY: xclbin app all

# xclbin:  $(XCLBIN)
# xclbin_enc: $(XCLBIN_ENCODING)

app: $(HOST_EXE) $(HOST_P2P_EXE)

# xo: $(XOS_ENCODING) $(XOS_CLUSTERING)
# xo_enc: $(XOS_ENCODING)
# xo_clu: $(XOS_CLUSTERING)
xo_tapa: $(XOS_TAPA)
# all: xclbin app
xo_wrp: $(XOS_WRAPPER)

# clean:
# 	-$(RM) $(HOST_EXE) $(EXE_OPT) $(XOS_ENCODING) $(XOS_CLUSTERING) $(EMCONFIG_FILE)

# kernel rules for encoding
$(XOS_ENCODING): $(KERNEL_SRC) $(KERNEL_HEADER)
	$(RM) $@
	$(VPP) $(VPP_COMMON_OPTS) --hls.clock 200000000:encoding_kernel -c -k encoding_kernel -o $@ $+

# kernel rules for clustering
$(XOS_CLUSTERING): $(KERNEL_SRC) $(KERNEL_HEADER)
	$(RM) $@
	$(VPP) $(VPP_COMMON_OPTS) --hls.clock 150000000:clustering_kernel -c -k clustering_kernel -o $@ $+
$(XOS_WRAPPER): $(KERNEL_SRC) $(KERNEL_HEADER)
	$(RM) $@
	$(VPP) $(VPP_COMMON_OPTS) --hls.clock 300000000:top_wrapper -c -k top_wrapper -o $@ $+

$(XOS_TAPA): $(TAPA_KERNEL_SRC) 
	mkdir -p $(WORK_DIR)
	$(TAPAC) $(TAPA_OPTS) --top wrapper -o $@ $+ 
  

$(XCLBIN): $(XOS_WRAPPER)# $(XOS_ENCODING) $(XOS_CLUSTERING)
	$(VPP) $(VPP_COMMON_OPTS) -l -o $@ $^ $(VPP_LINK_OPTS)

# host rules
$(HOST_EXE): $(HOST_SRC)
	g++ $(CFLAGS) -o $@ $+ $(LFLAGS)
	@echo 'Compiled Host Executable: $(HOST_EXE)'

$(HOST_P2P_EXE): $(HOST_P2P_SRC)
	g++ $(CFLAGS) -o $@ $+ $(LFLAGS)
	@echo 'Compiled Host Executable: $(HOST_P2P_EXE)'

$(EMCONFIG_FILE):
	$(EMCONFIGUTIL) --nd $(NUMDEVICES) --od . --platform $(PLATFORM)

check: $(XCLBIN) $(HOST_EXE) $(EMCONFIG_FILE)
	XCL_EMULATION_MODE=${MODE} ./$(HOST_EXE) $(EXE_OPT)

