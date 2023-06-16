`timescale 1 ns / 1 ps 

(* CORE_GENERATION_INFO = "Jacobi_Jacobi,hls_ip_2022_1,{HLS_INPUT_TYPE=cxx,HLS_INPUT_FLOAT=0,HLS_INPUT_FIXED=0,HLS_INPUT_PART=xcu55c-fsvh2892-2L-e,HLS_INPUT_CLOCK=3.333000,HLS_INPUT_ARCH=others,HLS_SYN_CLOCK=1.000000,HLS_SYN_LAT=0,HLS_SYN_TPT=none,HLS_SYN_MEM=0,HLS_SYN_DSP=0,HLS_SYN_FF=246,HLS_SYN_LUT=424,HLS_VERSION=2022_1}" *)


module Jacobi_inner
(
  s_axi_control_AWVALID,
  s_axi_control_AWREADY,
  s_axi_control_AWADDR,
  s_axi_control_WVALID,
  s_axi_control_WREADY,
  s_axi_control_WDATA,
  s_axi_control_WSTRB,
  s_axi_control_ARVALID,
  s_axi_control_ARREADY,
  s_axi_control_ARADDR,
  s_axi_control_RVALID,
  s_axi_control_RREADY,
  s_axi_control_RDATA,
  s_axi_control_RRESP,
  s_axi_control_BVALID,
  s_axi_control_BREADY,
  s_axi_control_BRESP,
  ap_clk,
  ap_rst_n,
  interrupt,
  m_axi_bank_0_t1_ARADDR,
  m_axi_bank_0_t1_ARBURST,
  m_axi_bank_0_t1_ARCACHE,
  m_axi_bank_0_t1_ARID,
  m_axi_bank_0_t1_ARLEN,
  m_axi_bank_0_t1_ARLOCK,
  m_axi_bank_0_t1_ARPROT,
  m_axi_bank_0_t1_ARQOS,
  m_axi_bank_0_t1_ARREADY,
  m_axi_bank_0_t1_ARSIZE,
  m_axi_bank_0_t1_ARVALID,
  m_axi_bank_0_t1_AWADDR,
  m_axi_bank_0_t1_AWBURST,
  m_axi_bank_0_t1_AWCACHE,
  m_axi_bank_0_t1_AWID,
  m_axi_bank_0_t1_AWLEN,
  m_axi_bank_0_t1_AWLOCK,
  m_axi_bank_0_t1_AWPROT,
  m_axi_bank_0_t1_AWQOS,
  m_axi_bank_0_t1_AWREADY,
  m_axi_bank_0_t1_AWSIZE,
  m_axi_bank_0_t1_AWVALID,
  m_axi_bank_0_t1_BID,
  m_axi_bank_0_t1_BREADY,
  m_axi_bank_0_t1_BRESP,
  m_axi_bank_0_t1_BVALID,
  m_axi_bank_0_t1_RDATA,
  m_axi_bank_0_t1_RID,
  m_axi_bank_0_t1_RLAST,
  m_axi_bank_0_t1_RREADY,
  m_axi_bank_0_t1_RRESP,
  m_axi_bank_0_t1_RVALID,
  m_axi_bank_0_t1_WDATA,
  m_axi_bank_0_t1_WLAST,
  m_axi_bank_0_t1_WREADY,
  m_axi_bank_0_t1_WSTRB,
  m_axi_bank_0_t1_WVALID,
  m_axi_bank_0_t0_ARADDR,
  m_axi_bank_0_t0_ARBURST,
  m_axi_bank_0_t0_ARCACHE,
  m_axi_bank_0_t0_ARID,
  m_axi_bank_0_t0_ARLEN,
  m_axi_bank_0_t0_ARLOCK,
  m_axi_bank_0_t0_ARPROT,
  m_axi_bank_0_t0_ARQOS,
  m_axi_bank_0_t0_ARREADY,
  m_axi_bank_0_t0_ARSIZE,
  m_axi_bank_0_t0_ARVALID,
  m_axi_bank_0_t0_AWADDR,
  m_axi_bank_0_t0_AWBURST,
  m_axi_bank_0_t0_AWCACHE,
  m_axi_bank_0_t0_AWID,
  m_axi_bank_0_t0_AWLEN,
  m_axi_bank_0_t0_AWLOCK,
  m_axi_bank_0_t0_AWPROT,
  m_axi_bank_0_t0_AWQOS,
  m_axi_bank_0_t0_AWREADY,
  m_axi_bank_0_t0_AWSIZE,
  m_axi_bank_0_t0_AWVALID,
  m_axi_bank_0_t0_BID,
  m_axi_bank_0_t0_BREADY,
  m_axi_bank_0_t0_BRESP,
  m_axi_bank_0_t0_BVALID,
  m_axi_bank_0_t0_RDATA,
  m_axi_bank_0_t0_RID,
  m_axi_bank_0_t0_RLAST,
  m_axi_bank_0_t0_RREADY,
  m_axi_bank_0_t0_RRESP,
  m_axi_bank_0_t0_RVALID,
  m_axi_bank_0_t0_WDATA,
  m_axi_bank_0_t0_WLAST,
  m_axi_bank_0_t0_WREADY,
  m_axi_bank_0_t0_WSTRB,
  m_axi_bank_0_t0_WVALID
);

  parameter C_S_AXI_CONTROL_DATA_WIDTH = 32;
  parameter C_S_AXI_CONTROL_ADDR_WIDTH = 6;
  parameter C_S_AXI_DATA_WIDTH = 32;
  parameter C_S_AXI_CONTROL_WSTRB_WIDTH = 32 / 8;
  parameter C_S_AXI_WSTRB_WIDTH = 32 / 8;
  input s_axi_control_AWVALID;
  output s_axi_control_AWREADY;
  input [C_S_AXI_CONTROL_ADDR_WIDTH-1:0] s_axi_control_AWADDR;
  input s_axi_control_WVALID;
  output s_axi_control_WREADY;
  input [C_S_AXI_CONTROL_DATA_WIDTH-1:0] s_axi_control_WDATA;
  input [C_S_AXI_CONTROL_WSTRB_WIDTH-1:0] s_axi_control_WSTRB;
  input s_axi_control_ARVALID;
  output s_axi_control_ARREADY;
  input [C_S_AXI_CONTROL_ADDR_WIDTH-1:0] s_axi_control_ARADDR;
  output s_axi_control_RVALID;
  input s_axi_control_RREADY;
  output [C_S_AXI_CONTROL_DATA_WIDTH-1:0] s_axi_control_RDATA;
  output [1:0] s_axi_control_RRESP;
  output s_axi_control_BVALID;
  input s_axi_control_BREADY;
  output [1:0] s_axi_control_BRESP;
  input ap_clk;
  input ap_rst_n;
  output interrupt;
  output [63:0] m_axi_bank_0_t1_ARADDR;
  output [1:0] m_axi_bank_0_t1_ARBURST;
  output [3:0] m_axi_bank_0_t1_ARCACHE;
  output [0:0] m_axi_bank_0_t1_ARID;
  output [7:0] m_axi_bank_0_t1_ARLEN;
  output m_axi_bank_0_t1_ARLOCK;
  output [2:0] m_axi_bank_0_t1_ARPROT;
  output [3:0] m_axi_bank_0_t1_ARQOS;
  input m_axi_bank_0_t1_ARREADY;
  output [2:0] m_axi_bank_0_t1_ARSIZE;
  output m_axi_bank_0_t1_ARVALID;
  output [63:0] m_axi_bank_0_t1_AWADDR;
  output [1:0] m_axi_bank_0_t1_AWBURST;
  output [3:0] m_axi_bank_0_t1_AWCACHE;
  output [0:0] m_axi_bank_0_t1_AWID;
  output [7:0] m_axi_bank_0_t1_AWLEN;
  output m_axi_bank_0_t1_AWLOCK;
  output [2:0] m_axi_bank_0_t1_AWPROT;
  output [3:0] m_axi_bank_0_t1_AWQOS;
  input m_axi_bank_0_t1_AWREADY;
  output [2:0] m_axi_bank_0_t1_AWSIZE;
  output m_axi_bank_0_t1_AWVALID;
  input [0:0] m_axi_bank_0_t1_BID;
  output m_axi_bank_0_t1_BREADY;
  input [1:0] m_axi_bank_0_t1_BRESP;
  input m_axi_bank_0_t1_BVALID;
  input [31:0] m_axi_bank_0_t1_RDATA;
  input [0:0] m_axi_bank_0_t1_RID;
  input m_axi_bank_0_t1_RLAST;
  output m_axi_bank_0_t1_RREADY;
  input [1:0] m_axi_bank_0_t1_RRESP;
  input m_axi_bank_0_t1_RVALID;
  output [31:0] m_axi_bank_0_t1_WDATA;
  output m_axi_bank_0_t1_WLAST;
  input m_axi_bank_0_t1_WREADY;
  output [3:0] m_axi_bank_0_t1_WSTRB;
  output m_axi_bank_0_t1_WVALID;
  output [63:0] m_axi_bank_0_t0_ARADDR;
  output [1:0] m_axi_bank_0_t0_ARBURST;
  output [3:0] m_axi_bank_0_t0_ARCACHE;
  output [0:0] m_axi_bank_0_t0_ARID;
  output [7:0] m_axi_bank_0_t0_ARLEN;
  output m_axi_bank_0_t0_ARLOCK;
  output [2:0] m_axi_bank_0_t0_ARPROT;
  output [3:0] m_axi_bank_0_t0_ARQOS;
  input m_axi_bank_0_t0_ARREADY;
  output [2:0] m_axi_bank_0_t0_ARSIZE;
  output m_axi_bank_0_t0_ARVALID;
  output [63:0] m_axi_bank_0_t0_AWADDR;
  output [1:0] m_axi_bank_0_t0_AWBURST;
  output [3:0] m_axi_bank_0_t0_AWCACHE;
  output [0:0] m_axi_bank_0_t0_AWID;
  output [7:0] m_axi_bank_0_t0_AWLEN;
  output m_axi_bank_0_t0_AWLOCK;
  output [2:0] m_axi_bank_0_t0_AWPROT;
  output [3:0] m_axi_bank_0_t0_AWQOS;
  input m_axi_bank_0_t0_AWREADY;
  output [2:0] m_axi_bank_0_t0_AWSIZE;
  output m_axi_bank_0_t0_AWVALID;
  input [0:0] m_axi_bank_0_t0_BID;
  output m_axi_bank_0_t0_BREADY;
  input [1:0] m_axi_bank_0_t0_BRESP;
  input m_axi_bank_0_t0_BVALID;
  input [31:0] m_axi_bank_0_t0_RDATA;
  input [0:0] m_axi_bank_0_t0_RID;
  input m_axi_bank_0_t0_RLAST;
  output m_axi_bank_0_t0_RREADY;
  input [1:0] m_axi_bank_0_t0_RRESP;
  input m_axi_bank_0_t0_RVALID;
  output [31:0] m_axi_bank_0_t0_WDATA;
  output m_axi_bank_0_t0_WLAST;
  input m_axi_bank_0_t0_WREADY;
  output [3:0] m_axi_bank_0_t0_WSTRB;
  output m_axi_bank_0_t0_WVALID;
  wire ap_start;
  wire s_axi_control_AWVALID_slr_0;
  wire s_axi_control_AWREADY_slr_0;
  wire [C_S_AXI_CONTROL_ADDR_WIDTH-1:0] s_axi_control_AWADDR_slr_0;
  wire s_axi_control_WVALID_slr_0;
  wire s_axi_control_WREADY_slr_0;
  wire [C_S_AXI_CONTROL_DATA_WIDTH-1:0] s_axi_control_WDATA_slr_0;
  wire [C_S_AXI_CONTROL_WSTRB_WIDTH-1:0] s_axi_control_WSTRB_slr_0;
  wire [63:0] bank_0_t0_slr_0;
  wire [63:0] bank_0_t1_slr_0;
  wire [63:0] coalesced_data_num_slr_0;
  wire s_axi_control_AWVALID_slr_1;
  wire s_axi_control_AWREADY_slr_1;
  wire [C_S_AXI_CONTROL_ADDR_WIDTH-1:0] s_axi_control_AWADDR_slr_1;
  wire s_axi_control_WVALID_slr_1;
  wire s_axi_control_WREADY_slr_1;
  wire [C_S_AXI_CONTROL_DATA_WIDTH-1:0] s_axi_control_WDATA_slr_1;
  wire [C_S_AXI_CONTROL_WSTRB_WIDTH-1:0] s_axi_control_WSTRB_slr_1;
  wire [63:0] bank_0_t0_slr_1;
  wire [63:0] bank_0_t1_slr_1;
  wire [63:0] coalesced_data_num_slr_1;
  wire s_axi_control_AWVALID_slr_2;
  wire s_axi_control_AWREADY_slr_2;
  wire [C_S_AXI_CONTROL_ADDR_WIDTH-1:0] s_axi_control_AWADDR_slr_2;
  wire s_axi_control_WVALID_slr_2;
  wire s_axi_control_WREADY_slr_2;
  wire [C_S_AXI_CONTROL_DATA_WIDTH-1:0] s_axi_control_WDATA_slr_2;
  wire [C_S_AXI_CONTROL_WSTRB_WIDTH-1:0] s_axi_control_WSTRB_slr_2;
  wire [63:0] bank_0_t0_slr_2;
  wire [63:0] bank_0_t1_slr_2;
  wire [63:0] coalesced_data_num_slr_2;
  wire bank_0_t0_buf__rst__q0;
  (* keep = "true" *)
  reg bank_0_t0_buf__rst__q1;
  (* keep = "true" *)
  reg bank_0_t0_buf__rst__q2;
  (* keep = "true" *)
  reg bank_0_t0_buf__rst__q3;
  wire bank_0_t1_buf__rst__q0;
  (* keep = "true" *)
  reg bank_0_t1_buf__rst__q1;
  (* keep = "true" *)
  reg bank_0_t1_buf__rst__q2;
  (* keep = "true" *)
  reg bank_0_t1_buf__rst__q3;
  wire from_super_source_to_t1_offset_0__rst__q0;
  (* keep = "true" *)
  reg from_super_source_to_t1_offset_0__rst__q1;
  (* keep = "true" *)
  reg from_super_source_to_t1_offset_0__rst__q2;
  (* keep = "true" *)
  reg from_super_source_to_t1_offset_0__rst__q3;
  wire from_super_source_to_t1_offset_1__rst__q0;
  (* keep = "true" *)
  reg from_super_source_to_t1_offset_1__rst__q1;
  (* keep = "true" *)
  reg from_super_source_to_t1_offset_1__rst__q2;
  (* keep = "true" *)
  reg from_super_source_to_t1_offset_1__rst__q3;
  wire from_t0_pe_0_to_super_sink__rst__q0;
  (* keep = "true" *)
  reg from_t0_pe_0_to_super_sink__rst__q1;
  (* keep = "true" *)
  reg from_t0_pe_0_to_super_sink__rst__q2;
  (* keep = "true" *)
  reg from_t0_pe_0_to_super_sink__rst__q3;
  wire from_t0_pe_1_to_super_sink__rst__q0;
  (* keep = "true" *)
  reg from_t0_pe_1_to_super_sink__rst__q1;
  (* keep = "true" *)
  reg from_t0_pe_1_to_super_sink__rst__q2;
  (* keep = "true" *)
  reg from_t0_pe_1_to_super_sink__rst__q3;
  wire from_t1_offset_0_to_t1_offset_2000__rst__q0;
  (* keep = "true" *)
  reg from_t1_offset_0_to_t1_offset_2000__rst__q1;
  (* keep = "true" *)
  reg from_t1_offset_0_to_t1_offset_2000__rst__q2;
  (* keep = "true" *)
  reg from_t1_offset_0_to_t1_offset_2000__rst__q3;
  wire from_t1_offset_0_to_tcse_var_0_pe_1__rst__q0;
  (* keep = "true" *)
  reg from_t1_offset_0_to_tcse_var_0_pe_1__rst__q1;
  (* keep = "true" *)
  reg from_t1_offset_0_to_tcse_var_0_pe_1__rst__q2;
  (* keep = "true" *)
  reg from_t1_offset_0_to_tcse_var_0_pe_1__rst__q3;
  wire from_t1_offset_1_to_t1_offset_2001__rst__q0;
  (* keep = "true" *)
  reg from_t1_offset_1_to_t1_offset_2001__rst__q1;
  (* keep = "true" *)
  reg from_t1_offset_1_to_t1_offset_2001__rst__q2;
  (* keep = "true" *)
  reg from_t1_offset_1_to_t1_offset_2001__rst__q3;
  wire from_t1_offset_1_to_tcse_var_0_pe_0__rst__q0;
  (* keep = "true" *)
  reg from_t1_offset_1_to_tcse_var_0_pe_0__rst__q1;
  (* keep = "true" *)
  reg from_t1_offset_1_to_tcse_var_0_pe_0__rst__q2;
  (* keep = "true" *)
  reg from_t1_offset_1_to_tcse_var_0_pe_0__rst__q3;
  wire from_t1_offset_2000_to_t0_pe_1__rst__q0;
  (* keep = "true" *)
  reg from_t1_offset_2000_to_t0_pe_1__rst__q1;
  (* keep = "true" *)
  reg from_t1_offset_2000_to_t0_pe_1__rst__q2;
  (* keep = "true" *)
  reg from_t1_offset_2000_to_t0_pe_1__rst__q3;
  wire from_t1_offset_2000_to_tcse_var_0_pe_0__rst__q0;
  (* keep = "true" *)
  reg from_t1_offset_2000_to_tcse_var_0_pe_0__rst__q1;
  (* keep = "true" *)
  reg from_t1_offset_2000_to_tcse_var_0_pe_0__rst__q2;
  (* keep = "true" *)
  reg from_t1_offset_2000_to_tcse_var_0_pe_0__rst__q3;
  wire from_t1_offset_2001_to_t0_pe_0__rst__q0;
  (* keep = "true" *)
  reg from_t1_offset_2001_to_t0_pe_0__rst__q1;
  (* keep = "true" *)
  reg from_t1_offset_2001_to_t0_pe_0__rst__q2;
  (* keep = "true" *)
  reg from_t1_offset_2001_to_t0_pe_0__rst__q3;
  wire from_t1_offset_2001_to_tcse_var_0_pe_1__rst__q0;
  (* keep = "true" *)
  reg from_t1_offset_2001_to_tcse_var_0_pe_1__rst__q1;
  (* keep = "true" *)
  reg from_t1_offset_2001_to_tcse_var_0_pe_1__rst__q2;
  (* keep = "true" *)
  reg from_t1_offset_2001_to_tcse_var_0_pe_1__rst__q3;
  wire from_tcse_var_0_offset_0_to_t0_pe_0__rst__q0;
  (* keep = "true" *)
  reg from_tcse_var_0_offset_0_to_t0_pe_0__rst__q1;
  (* keep = "true" *)
  reg from_tcse_var_0_offset_0_to_t0_pe_0__rst__q2;
  (* keep = "true" *)
  reg from_tcse_var_0_offset_0_to_t0_pe_0__rst__q3;
  wire from_tcse_var_0_offset_0_to_t0_pe_1__rst__q0;
  (* keep = "true" *)
  reg from_tcse_var_0_offset_0_to_t0_pe_1__rst__q1;
  (* keep = "true" *)
  reg from_tcse_var_0_offset_0_to_t0_pe_1__rst__q2;
  (* keep = "true" *)
  reg from_tcse_var_0_offset_0_to_t0_pe_1__rst__q3;
  wire from_tcse_var_0_offset_1_to_t0_pe_0__rst__q0;
  (* keep = "true" *)
  reg from_tcse_var_0_offset_1_to_t0_pe_0__rst__q1;
  (* keep = "true" *)
  reg from_tcse_var_0_offset_1_to_t0_pe_0__rst__q2;
  (* keep = "true" *)
  reg from_tcse_var_0_offset_1_to_t0_pe_0__rst__q3;
  wire from_tcse_var_0_offset_1_to_t0_pe_1__rst__q0;
  (* keep = "true" *)
  reg from_tcse_var_0_offset_1_to_t0_pe_1__rst__q1;
  (* keep = "true" *)
  reg from_tcse_var_0_offset_1_to_t0_pe_1__rst__q2;
  (* keep = "true" *)
  reg from_tcse_var_0_offset_1_to_t0_pe_1__rst__q3;
  wire from_tcse_var_0_pe_0_to_tcse_var_0_offset_1__rst__q0;
  (* keep = "true" *)
  reg from_tcse_var_0_pe_0_to_tcse_var_0_offset_1__rst__q1;
  (* keep = "true" *)
  reg from_tcse_var_0_pe_0_to_tcse_var_0_offset_1__rst__q2;
  (* keep = "true" *)
  reg from_tcse_var_0_pe_0_to_tcse_var_0_offset_1__rst__q3;
  wire from_tcse_var_0_pe_1_to_tcse_var_0_offset_0__rst__q0;
  (* keep = "true" *)
  reg from_tcse_var_0_pe_1_to_tcse_var_0_offset_0__rst__q1;
  (* keep = "true" *)
  reg from_tcse_var_0_pe_1_to_tcse_var_0_offset_0__rst__q2;
  (* keep = "true" *)
  reg from_tcse_var_0_pe_1_to_tcse_var_0_offset_0__rst__q3;
  wire [64:0] bank_0_t0_buf__dout;
  wire bank_0_t0_buf__empty_n;
  wire bank_0_t0_buf__read;
  wire [64:0] bank_0_t0_buf__din;
  wire bank_0_t0_buf__full_n;
  wire bank_0_t0_buf__write;
  wire [64:0] bank_0_t1_buf__dout;
  wire bank_0_t1_buf__empty_n;
  wire bank_0_t1_buf__read;
  wire [64:0] bank_0_t1_buf__din;
  wire bank_0_t1_buf__full_n;
  wire bank_0_t1_buf__write;
  wire [32:0] from_super_source_to_t1_offset_0__dout;
  wire from_super_source_to_t1_offset_0__empty_n;
  wire from_super_source_to_t1_offset_0__read;
  wire [32:0] from_super_source_to_t1_offset_0__din;
  wire from_super_source_to_t1_offset_0__full_n;
  wire from_super_source_to_t1_offset_0__write;
  wire [32:0] from_super_source_to_t1_offset_1__dout;
  wire from_super_source_to_t1_offset_1__empty_n;
  wire from_super_source_to_t1_offset_1__read;
  wire [32:0] from_super_source_to_t1_offset_1__din;
  wire from_super_source_to_t1_offset_1__full_n;
  wire from_super_source_to_t1_offset_1__write;
  wire [32:0] from_t0_pe_0_to_super_sink__dout;
  wire from_t0_pe_0_to_super_sink__empty_n;
  wire from_t0_pe_0_to_super_sink__read;
  wire [32:0] from_t0_pe_0_to_super_sink__din;
  wire from_t0_pe_0_to_super_sink__full_n;
  wire from_t0_pe_0_to_super_sink__write;
  wire [32:0] from_t0_pe_1_to_super_sink__dout;
  wire from_t0_pe_1_to_super_sink__empty_n;
  wire from_t0_pe_1_to_super_sink__read;
  wire [32:0] from_t0_pe_1_to_super_sink__din;
  wire from_t0_pe_1_to_super_sink__full_n;
  wire from_t0_pe_1_to_super_sink__write;
  wire [32:0] from_t1_offset_0_to_t1_offset_2000__dout;
  wire from_t1_offset_0_to_t1_offset_2000__empty_n;
  wire from_t1_offset_0_to_t1_offset_2000__read;
  wire [32:0] from_t1_offset_0_to_t1_offset_2000__din;
  wire from_t1_offset_0_to_t1_offset_2000__full_n;
  wire from_t1_offset_0_to_t1_offset_2000__write;
  wire [32:0] from_t1_offset_0_to_tcse_var_0_pe_1__dout;
  wire from_t1_offset_0_to_tcse_var_0_pe_1__empty_n;
  wire from_t1_offset_0_to_tcse_var_0_pe_1__read;
  wire [32:0] from_t1_offset_0_to_tcse_var_0_pe_1__din;
  wire from_t1_offset_0_to_tcse_var_0_pe_1__full_n;
  wire from_t1_offset_0_to_tcse_var_0_pe_1__write;
  wire [32:0] from_t1_offset_1_to_t1_offset_2001__dout;
  wire from_t1_offset_1_to_t1_offset_2001__empty_n;
  wire from_t1_offset_1_to_t1_offset_2001__read;
  wire [32:0] from_t1_offset_1_to_t1_offset_2001__din;
  wire from_t1_offset_1_to_t1_offset_2001__full_n;
  wire from_t1_offset_1_to_t1_offset_2001__write;
  wire [32:0] from_t1_offset_1_to_tcse_var_0_pe_0__dout;
  wire from_t1_offset_1_to_tcse_var_0_pe_0__empty_n;
  wire from_t1_offset_1_to_tcse_var_0_pe_0__read;
  wire [32:0] from_t1_offset_1_to_tcse_var_0_pe_0__din;
  wire from_t1_offset_1_to_tcse_var_0_pe_0__full_n;
  wire from_t1_offset_1_to_tcse_var_0_pe_0__write;
  wire [32:0] from_t1_offset_2000_to_t0_pe_1__dout;
  wire from_t1_offset_2000_to_t0_pe_1__empty_n;
  wire from_t1_offset_2000_to_t0_pe_1__read;
  wire [32:0] from_t1_offset_2000_to_t0_pe_1__din;
  wire from_t1_offset_2000_to_t0_pe_1__full_n;
  wire from_t1_offset_2000_to_t0_pe_1__write;
  wire [32:0] from_t1_offset_2000_to_tcse_var_0_pe_0__dout;
  wire from_t1_offset_2000_to_tcse_var_0_pe_0__empty_n;
  wire from_t1_offset_2000_to_tcse_var_0_pe_0__read;
  wire [32:0] from_t1_offset_2000_to_tcse_var_0_pe_0__din;
  wire from_t1_offset_2000_to_tcse_var_0_pe_0__full_n;
  wire from_t1_offset_2000_to_tcse_var_0_pe_0__write;
  wire [32:0] from_t1_offset_2001_to_t0_pe_0__dout;
  wire from_t1_offset_2001_to_t0_pe_0__empty_n;
  wire from_t1_offset_2001_to_t0_pe_0__read;
  wire [32:0] from_t1_offset_2001_to_t0_pe_0__din;
  wire from_t1_offset_2001_to_t0_pe_0__full_n;
  wire from_t1_offset_2001_to_t0_pe_0__write;
  wire [32:0] from_t1_offset_2001_to_tcse_var_0_pe_1__dout;
  wire from_t1_offset_2001_to_tcse_var_0_pe_1__empty_n;
  wire from_t1_offset_2001_to_tcse_var_0_pe_1__read;
  wire [32:0] from_t1_offset_2001_to_tcse_var_0_pe_1__din;
  wire from_t1_offset_2001_to_tcse_var_0_pe_1__full_n;
  wire from_t1_offset_2001_to_tcse_var_0_pe_1__write;
  wire [32:0] from_tcse_var_0_offset_0_to_t0_pe_0__dout;
  wire from_tcse_var_0_offset_0_to_t0_pe_0__empty_n;
  wire from_tcse_var_0_offset_0_to_t0_pe_0__read;
  wire [32:0] from_tcse_var_0_offset_0_to_t0_pe_0__din;
  wire from_tcse_var_0_offset_0_to_t0_pe_0__full_n;
  wire from_tcse_var_0_offset_0_to_t0_pe_0__write;
  wire [32:0] from_tcse_var_0_offset_0_to_t0_pe_1__dout;
  wire from_tcse_var_0_offset_0_to_t0_pe_1__empty_n;
  wire from_tcse_var_0_offset_0_to_t0_pe_1__read;
  wire [32:0] from_tcse_var_0_offset_0_to_t0_pe_1__din;
  wire from_tcse_var_0_offset_0_to_t0_pe_1__full_n;
  wire from_tcse_var_0_offset_0_to_t0_pe_1__write;
  wire [32:0] from_tcse_var_0_offset_1_to_t0_pe_0__dout;
  wire from_tcse_var_0_offset_1_to_t0_pe_0__empty_n;
  wire from_tcse_var_0_offset_1_to_t0_pe_0__read;
  wire [32:0] from_tcse_var_0_offset_1_to_t0_pe_0__din;
  wire from_tcse_var_0_offset_1_to_t0_pe_0__full_n;
  wire from_tcse_var_0_offset_1_to_t0_pe_0__write;
  wire [32:0] from_tcse_var_0_offset_1_to_t0_pe_1__dout;
  wire from_tcse_var_0_offset_1_to_t0_pe_1__empty_n;
  wire from_tcse_var_0_offset_1_to_t0_pe_1__read;
  wire [32:0] from_tcse_var_0_offset_1_to_t0_pe_1__din;
  wire from_tcse_var_0_offset_1_to_t0_pe_1__full_n;
  wire from_tcse_var_0_offset_1_to_t0_pe_1__write;
  wire [32:0] from_tcse_var_0_pe_0_to_tcse_var_0_offset_1__dout;
  wire from_tcse_var_0_pe_0_to_tcse_var_0_offset_1__empty_n;
  wire from_tcse_var_0_pe_0_to_tcse_var_0_offset_1__read;
  wire [32:0] from_tcse_var_0_pe_0_to_tcse_var_0_offset_1__din;
  wire from_tcse_var_0_pe_0_to_tcse_var_0_offset_1__full_n;
  wire from_tcse_var_0_pe_0_to_tcse_var_0_offset_1__write;
  wire [32:0] from_tcse_var_0_pe_1_to_tcse_var_0_offset_0__dout;
  wire from_tcse_var_0_pe_1_to_tcse_var_0_offset_0__empty_n;
  wire from_tcse_var_0_pe_1_to_tcse_var_0_offset_0__read;
  wire [32:0] from_tcse_var_0_pe_1_to_tcse_var_0_offset_0__din;
  wire from_tcse_var_0_pe_1_to_tcse_var_0_offset_0__full_n;
  wire from_tcse_var_0_pe_1_to_tcse_var_0_offset_0__write;
  wire [63:0] Mmap2Stream_0___bank_0_t1__q0;
  (* keep = "true" *)
  reg [63:0] Mmap2Stream_0___bank_0_t1__q1;
  (* keep = "true" *)
  reg [63:0] Mmap2Stream_0___bank_0_t1__q2;
  wire [63:0] Mmap2Stream_0___coalesced_data_num__q0;
  (* keep = "true" *)
  reg [63:0] Mmap2Stream_0___coalesced_data_num__q1;
  (* keep = "true" *)
  reg [63:0] Mmap2Stream_0___coalesced_data_num__q2;
  wire Mmap2Stream_0__ap_rst_n__q0;
  (* keep = "true" *)
  reg Mmap2Stream_0__ap_rst_n__q1;
  (* keep = "true" *)
  reg Mmap2Stream_0__ap_rst_n__q2;
  (* keep = "true" *)
  reg Mmap2Stream_0__ap_rst_n__q3;
  wire Mmap2Stream_0__ap_start_global__q0;
  (* keep = "true" *)
  reg Mmap2Stream_0__ap_start_global__q1;
  (* keep = "true" *)
  reg Mmap2Stream_0__ap_start_global__q2;
  (* keep = "true" *)
  reg Mmap2Stream_0__ap_start_global__q3;
  wire Mmap2Stream_0__is_done__q0;
  (* keep = "true" *)
  reg Mmap2Stream_0__is_done__q1;
  (* keep = "true" *)
  reg Mmap2Stream_0__is_done__q2;
  (* keep = "true" *)
  reg Mmap2Stream_0__is_done__q3;
  wire Mmap2Stream_0__ap_done_global__q0;
  (* keep = "true" *)
  reg Mmap2Stream_0__ap_done_global__q1;
  (* keep = "true" *)
  reg Mmap2Stream_0__ap_done_global__q2;
  (* keep = "true" *)
  reg Mmap2Stream_0__ap_done_global__q3;
  wire Mmap2Stream_0__ap_start;
  reg [1:0] Mmap2Stream_0__state;
  wire Mmap2Stream_0__ap_done;
  wire Mmap2Stream_0__ap_idle;
  wire Mmap2Stream_0__ap_ready;
  wire Module0Func_0__ap_rst_n__q0;
  (* keep = "true" *)
  reg Module0Func_0__ap_rst_n__q1;
  (* keep = "true" *)
  reg Module0Func_0__ap_rst_n__q2;
  (* keep = "true" *)
  reg Module0Func_0__ap_rst_n__q3;
  wire Module0Func_0__ap_start_global__q0;
  (* keep = "true" *)
  reg Module0Func_0__ap_start_global__q1;
  (* keep = "true" *)
  reg Module0Func_0__ap_start_global__q2;
  (* keep = "true" *)
  reg Module0Func_0__ap_start_global__q3;
  wire Module0Func_0__is_done__q0;
  (* keep = "true" *)
  reg Module0Func_0__is_done__q1;
  (* keep = "true" *)
  reg Module0Func_0__is_done__q2;
  (* keep = "true" *)
  reg Module0Func_0__is_done__q3;
  wire Module0Func_0__ap_done_global__q0;
  (* keep = "true" *)
  reg Module0Func_0__ap_done_global__q1;
  (* keep = "true" *)
  reg Module0Func_0__ap_done_global__q2;
  (* keep = "true" *)
  reg Module0Func_0__ap_done_global__q3;
  wire Module0Func_0__ap_start;
  reg [1:0] Module0Func_0__state;
  wire Module0Func_0__ap_done;
  wire Module0Func_0__ap_idle;
  wire Module0Func_0__ap_ready;
  wire Module1Func_0__ap_rst_n__q0;
  (* keep = "true" *)
  reg Module1Func_0__ap_rst_n__q1;
  (* keep = "true" *)
  reg Module1Func_0__ap_rst_n__q2;
  (* keep = "true" *)
  reg Module1Func_0__ap_rst_n__q3;
  wire Module1Func_0__ap_start_global__q0;
  (* keep = "true" *)
  reg Module1Func_0__ap_start_global__q1;
  (* keep = "true" *)
  reg Module1Func_0__ap_start_global__q2;
  (* keep = "true" *)
  reg Module1Func_0__ap_start_global__q3;
  wire Module1Func_0__is_done__q0;
  (* keep = "true" *)
  reg Module1Func_0__is_done__q1;
  (* keep = "true" *)
  reg Module1Func_0__is_done__q2;
  (* keep = "true" *)
  reg Module1Func_0__is_done__q3;
  wire Module1Func_0__ap_done_global__q0;
  (* keep = "true" *)
  reg Module1Func_0__ap_done_global__q1;
  (* keep = "true" *)
  reg Module1Func_0__ap_done_global__q2;
  (* keep = "true" *)
  reg Module1Func_0__ap_done_global__q3;
  wire Module1Func_0__ap_start;
  reg [1:0] Module1Func_0__state;
  wire Module1Func_0__ap_done;
  wire Module1Func_0__ap_idle;
  wire Module1Func_0__ap_ready;
  wire Module1Func_1__ap_rst_n__q0;
  (* keep = "true" *)
  reg Module1Func_1__ap_rst_n__q1;
  (* keep = "true" *)
  reg Module1Func_1__ap_rst_n__q2;
  (* keep = "true" *)
  reg Module1Func_1__ap_rst_n__q3;
  wire Module1Func_1__ap_start_global__q0;
  (* keep = "true" *)
  reg Module1Func_1__ap_start_global__q1;
  (* keep = "true" *)
  reg Module1Func_1__ap_start_global__q2;
  (* keep = "true" *)
  reg Module1Func_1__ap_start_global__q3;
  wire Module1Func_1__is_done__q0;
  (* keep = "true" *)
  reg Module1Func_1__is_done__q1;
  (* keep = "true" *)
  reg Module1Func_1__is_done__q2;
  (* keep = "true" *)
  reg Module1Func_1__is_done__q3;
  wire Module1Func_1__ap_done_global__q0;
  (* keep = "true" *)
  reg Module1Func_1__ap_done_global__q1;
  (* keep = "true" *)
  reg Module1Func_1__ap_done_global__q2;
  (* keep = "true" *)
  reg Module1Func_1__ap_done_global__q3;
  wire Module1Func_1__ap_start;
  reg [1:0] Module1Func_1__state;
  wire Module1Func_1__ap_done;
  wire Module1Func_1__ap_idle;
  wire Module1Func_1__ap_ready;
  wire Module1Func_2__ap_rst_n__q0;
  (* keep = "true" *)
  reg Module1Func_2__ap_rst_n__q1;
  (* keep = "true" *)
  reg Module1Func_2__ap_rst_n__q2;
  (* keep = "true" *)
  reg Module1Func_2__ap_rst_n__q3;
  wire Module1Func_2__ap_start_global__q0;
  (* keep = "true" *)
  reg Module1Func_2__ap_start_global__q1;
  (* keep = "true" *)
  reg Module1Func_2__ap_start_global__q2;
  (* keep = "true" *)
  reg Module1Func_2__ap_start_global__q3;
  wire Module1Func_2__is_done__q0;
  (* keep = "true" *)
  reg Module1Func_2__is_done__q1;
  (* keep = "true" *)
  reg Module1Func_2__is_done__q2;
  (* keep = "true" *)
  reg Module1Func_2__is_done__q3;
  wire Module1Func_2__ap_done_global__q0;
  (* keep = "true" *)
  reg Module1Func_2__ap_done_global__q1;
  (* keep = "true" *)
  reg Module1Func_2__ap_done_global__q2;
  (* keep = "true" *)
  reg Module1Func_2__ap_done_global__q3;
  wire Module1Func_2__ap_start;
  reg [1:0] Module1Func_2__state;
  wire Module1Func_2__ap_done;
  wire Module1Func_2__ap_idle;
  wire Module1Func_2__ap_ready;
  wire Module1Func_3__ap_rst_n__q0;
  (* keep = "true" *)
  reg Module1Func_3__ap_rst_n__q1;
  (* keep = "true" *)
  reg Module1Func_3__ap_rst_n__q2;
  (* keep = "true" *)
  reg Module1Func_3__ap_rst_n__q3;
  wire Module1Func_3__ap_start_global__q0;
  (* keep = "true" *)
  reg Module1Func_3__ap_start_global__q1;
  (* keep = "true" *)
  reg Module1Func_3__ap_start_global__q2;
  (* keep = "true" *)
  reg Module1Func_3__ap_start_global__q3;
  wire Module1Func_3__is_done__q0;
  (* keep = "true" *)
  reg Module1Func_3__is_done__q1;
  (* keep = "true" *)
  reg Module1Func_3__is_done__q2;
  (* keep = "true" *)
  reg Module1Func_3__is_done__q3;
  wire Module1Func_3__ap_done_global__q0;
  (* keep = "true" *)
  reg Module1Func_3__ap_done_global__q1;
  (* keep = "true" *)
  reg Module1Func_3__ap_done_global__q2;
  (* keep = "true" *)
  reg Module1Func_3__ap_done_global__q3;
  wire Module1Func_3__ap_start;
  reg [1:0] Module1Func_3__state;
  wire Module1Func_3__ap_done;
  wire Module1Func_3__ap_idle;
  wire Module1Func_3__ap_ready;
  wire Module1Func_4__ap_rst_n__q0;
  (* keep = "true" *)
  reg Module1Func_4__ap_rst_n__q1;
  (* keep = "true" *)
  reg Module1Func_4__ap_rst_n__q2;
  (* keep = "true" *)
  reg Module1Func_4__ap_rst_n__q3;
  wire Module1Func_4__ap_start_global__q0;
  (* keep = "true" *)
  reg Module1Func_4__ap_start_global__q1;
  (* keep = "true" *)
  reg Module1Func_4__ap_start_global__q2;
  (* keep = "true" *)
  reg Module1Func_4__ap_start_global__q3;
  wire Module1Func_4__is_done__q0;
  (* keep = "true" *)
  reg Module1Func_4__is_done__q1;
  (* keep = "true" *)
  reg Module1Func_4__is_done__q2;
  (* keep = "true" *)
  reg Module1Func_4__is_done__q3;
  wire Module1Func_4__ap_done_global__q0;
  (* keep = "true" *)
  reg Module1Func_4__ap_done_global__q1;
  (* keep = "true" *)
  reg Module1Func_4__ap_done_global__q2;
  (* keep = "true" *)
  reg Module1Func_4__ap_done_global__q3;
  wire Module1Func_4__ap_start;
  reg [1:0] Module1Func_4__state;
  wire Module1Func_4__ap_done;
  wire Module1Func_4__ap_idle;
  wire Module1Func_4__ap_ready;
  wire Module1Func_5__ap_rst_n__q0;
  (* keep = "true" *)
  reg Module1Func_5__ap_rst_n__q1;
  (* keep = "true" *)
  reg Module1Func_5__ap_rst_n__q2;
  (* keep = "true" *)
  reg Module1Func_5__ap_rst_n__q3;
  wire Module1Func_5__ap_start_global__q0;
  (* keep = "true" *)
  reg Module1Func_5__ap_start_global__q1;
  (* keep = "true" *)
  reg Module1Func_5__ap_start_global__q2;
  (* keep = "true" *)
  reg Module1Func_5__ap_start_global__q3;
  wire Module1Func_5__is_done__q0;
  (* keep = "true" *)
  reg Module1Func_5__is_done__q1;
  (* keep = "true" *)
  reg Module1Func_5__is_done__q2;
  (* keep = "true" *)
  reg Module1Func_5__is_done__q3;
  wire Module1Func_5__ap_done_global__q0;
  (* keep = "true" *)
  reg Module1Func_5__ap_done_global__q1;
  (* keep = "true" *)
  reg Module1Func_5__ap_done_global__q2;
  (* keep = "true" *)
  reg Module1Func_5__ap_done_global__q3;
  wire Module1Func_5__ap_start;
  reg [1:0] Module1Func_5__state;
  wire Module1Func_5__ap_done;
  wire Module1Func_5__ap_idle;
  wire Module1Func_5__ap_ready;
  wire Module3Func1_0__ap_rst_n__q0;
  (* keep = "true" *)
  reg Module3Func1_0__ap_rst_n__q1;
  (* keep = "true" *)
  reg Module3Func1_0__ap_rst_n__q2;
  (* keep = "true" *)
  reg Module3Func1_0__ap_rst_n__q3;
  wire Module3Func1_0__ap_start_global__q0;
  (* keep = "true" *)
  reg Module3Func1_0__ap_start_global__q1;
  (* keep = "true" *)
  reg Module3Func1_0__ap_start_global__q2;
  (* keep = "true" *)
  reg Module3Func1_0__ap_start_global__q3;
  wire Module3Func1_0__is_done__q0;
  (* keep = "true" *)
  reg Module3Func1_0__is_done__q1;
  (* keep = "true" *)
  reg Module3Func1_0__is_done__q2;
  (* keep = "true" *)
  reg Module3Func1_0__is_done__q3;
  wire Module3Func1_0__ap_done_global__q0;
  (* keep = "true" *)
  reg Module3Func1_0__ap_done_global__q1;
  (* keep = "true" *)
  reg Module3Func1_0__ap_done_global__q2;
  (* keep = "true" *)
  reg Module3Func1_0__ap_done_global__q3;
  wire Module3Func1_0__ap_start;
  reg [1:0] Module3Func1_0__state;
  wire Module3Func1_0__ap_done;
  wire Module3Func1_0__ap_idle;
  wire Module3Func1_0__ap_ready;
  wire Module3Func2_0__ap_rst_n__q0;
  (* keep = "true" *)
  reg Module3Func2_0__ap_rst_n__q1;
  (* keep = "true" *)
  reg Module3Func2_0__ap_rst_n__q2;
  (* keep = "true" *)
  reg Module3Func2_0__ap_rst_n__q3;
  wire Module3Func2_0__ap_start_global__q0;
  (* keep = "true" *)
  reg Module3Func2_0__ap_start_global__q1;
  (* keep = "true" *)
  reg Module3Func2_0__ap_start_global__q2;
  (* keep = "true" *)
  reg Module3Func2_0__ap_start_global__q3;
  wire Module3Func2_0__is_done__q0;
  (* keep = "true" *)
  reg Module3Func2_0__is_done__q1;
  (* keep = "true" *)
  reg Module3Func2_0__is_done__q2;
  (* keep = "true" *)
  reg Module3Func2_0__is_done__q3;
  wire Module3Func2_0__ap_done_global__q0;
  (* keep = "true" *)
  reg Module3Func2_0__ap_done_global__q1;
  (* keep = "true" *)
  reg Module3Func2_0__ap_done_global__q2;
  (* keep = "true" *)
  reg Module3Func2_0__ap_done_global__q3;
  wire Module3Func2_0__ap_start;
  reg [1:0] Module3Func2_0__state;
  wire Module3Func2_0__ap_done;
  wire Module3Func2_0__ap_idle;
  wire Module3Func2_0__ap_ready;
  wire Module6Func1_0__ap_rst_n__q0;
  (* keep = "true" *)
  reg Module6Func1_0__ap_rst_n__q1;
  (* keep = "true" *)
  reg Module6Func1_0__ap_rst_n__q2;
  (* keep = "true" *)
  reg Module6Func1_0__ap_rst_n__q3;
  wire Module6Func1_0__ap_start_global__q0;
  (* keep = "true" *)
  reg Module6Func1_0__ap_start_global__q1;
  (* keep = "true" *)
  reg Module6Func1_0__ap_start_global__q2;
  (* keep = "true" *)
  reg Module6Func1_0__ap_start_global__q3;
  wire Module6Func1_0__is_done__q0;
  (* keep = "true" *)
  reg Module6Func1_0__is_done__q1;
  (* keep = "true" *)
  reg Module6Func1_0__is_done__q2;
  (* keep = "true" *)
  reg Module6Func1_0__is_done__q3;
  wire Module6Func1_0__ap_done_global__q0;
  (* keep = "true" *)
  reg Module6Func1_0__ap_done_global__q1;
  (* keep = "true" *)
  reg Module6Func1_0__ap_done_global__q2;
  (* keep = "true" *)
  reg Module6Func1_0__ap_done_global__q3;
  wire Module6Func1_0__ap_start;
  reg [1:0] Module6Func1_0__state;
  wire Module6Func1_0__ap_done;
  wire Module6Func1_0__ap_idle;
  wire Module6Func1_0__ap_ready;
  wire Module6Func2_0__ap_rst_n__q0;
  (* keep = "true" *)
  reg Module6Func2_0__ap_rst_n__q1;
  (* keep = "true" *)
  reg Module6Func2_0__ap_rst_n__q2;
  (* keep = "true" *)
  reg Module6Func2_0__ap_rst_n__q3;
  wire Module6Func2_0__ap_start_global__q0;
  (* keep = "true" *)
  reg Module6Func2_0__ap_start_global__q1;
  (* keep = "true" *)
  reg Module6Func2_0__ap_start_global__q2;
  (* keep = "true" *)
  reg Module6Func2_0__ap_start_global__q3;
  wire Module6Func2_0__is_done__q0;
  (* keep = "true" *)
  reg Module6Func2_0__is_done__q1;
  (* keep = "true" *)
  reg Module6Func2_0__is_done__q2;
  (* keep = "true" *)
  reg Module6Func2_0__is_done__q3;
  wire Module6Func2_0__ap_done_global__q0;
  (* keep = "true" *)
  reg Module6Func2_0__ap_done_global__q1;
  (* keep = "true" *)
  reg Module6Func2_0__ap_done_global__q2;
  (* keep = "true" *)
  reg Module6Func2_0__ap_done_global__q3;
  wire Module6Func2_0__ap_start;
  reg [1:0] Module6Func2_0__state;
  wire Module6Func2_0__ap_done;
  wire Module6Func2_0__ap_idle;
  wire Module6Func2_0__ap_ready;
  wire Module8Func_0__ap_rst_n__q0;
  (* keep = "true" *)
  reg Module8Func_0__ap_rst_n__q1;
  (* keep = "true" *)
  reg Module8Func_0__ap_rst_n__q2;
  (* keep = "true" *)
  reg Module8Func_0__ap_rst_n__q3;
  wire Module8Func_0__ap_start_global__q0;
  (* keep = "true" *)
  reg Module8Func_0__ap_start_global__q1;
  (* keep = "true" *)
  reg Module8Func_0__ap_start_global__q2;
  (* keep = "true" *)
  reg Module8Func_0__ap_start_global__q3;
  wire Module8Func_0__is_done__q0;
  (* keep = "true" *)
  reg Module8Func_0__is_done__q1;
  (* keep = "true" *)
  reg Module8Func_0__is_done__q2;
  (* keep = "true" *)
  reg Module8Func_0__is_done__q3;
  wire Module8Func_0__ap_done_global__q0;
  (* keep = "true" *)
  reg Module8Func_0__ap_done_global__q1;
  (* keep = "true" *)
  reg Module8Func_0__ap_done_global__q2;
  (* keep = "true" *)
  reg Module8Func_0__ap_done_global__q3;
  wire Module8Func_0__ap_start;
  reg [1:0] Module8Func_0__state;
  wire Module8Func_0__ap_done;
  wire Module8Func_0__ap_idle;
  wire Module8Func_0__ap_ready;
  wire [63:0] Stream2Mmap_0___bank_0_t0__q0;
  (* keep = "true" *)
  reg [63:0] Stream2Mmap_0___bank_0_t0__q1;
  (* keep = "true" *)
  reg [63:0] Stream2Mmap_0___bank_0_t0__q2;
  wire Stream2Mmap_0__ap_rst_n__q0;
  (* keep = "true" *)
  reg Stream2Mmap_0__ap_rst_n__q1;
  (* keep = "true" *)
  reg Stream2Mmap_0__ap_rst_n__q2;
  (* keep = "true" *)
  reg Stream2Mmap_0__ap_rst_n__q3;
  wire Stream2Mmap_0__ap_start_global__q0;
  (* keep = "true" *)
  reg Stream2Mmap_0__ap_start_global__q1;
  (* keep = "true" *)
  reg Stream2Mmap_0__ap_start_global__q2;
  (* keep = "true" *)
  reg Stream2Mmap_0__ap_start_global__q3;
  wire Stream2Mmap_0__is_done__q0;
  (* keep = "true" *)
  reg Stream2Mmap_0__is_done__q1;
  (* keep = "true" *)
  reg Stream2Mmap_0__is_done__q2;
  (* keep = "true" *)
  reg Stream2Mmap_0__is_done__q3;
  wire Stream2Mmap_0__ap_done_global__q0;
  (* keep = "true" *)
  reg Stream2Mmap_0__ap_done_global__q1;
  (* keep = "true" *)
  reg Stream2Mmap_0__ap_done_global__q2;
  (* keep = "true" *)
  reg Stream2Mmap_0__ap_done_global__q3;
  wire Stream2Mmap_0__ap_start;
  reg [1:0] Stream2Mmap_0__state;
  wire Stream2Mmap_0__ap_done;
  wire Stream2Mmap_0__ap_idle;
  wire Stream2Mmap_0__ap_ready;
  reg [1:0] tapa_state;
  reg [1:0] countdown;
  wire ap_start__q0;
  (* keep = "true" *)
  reg ap_start__q1;
  (* keep = "true" *)
  reg ap_start__q2;
  (* keep = "true" *)
  reg ap_start__q3;
  wire ap_done__q0;
  (* keep = "true" *)
  reg ap_done__q1;
  (* keep = "true" *)
  reg ap_done__q2;
  (* keep = "true" *)
  reg ap_done__q3;
  wire ap_rst_n_inv;
  wire ap_done;
  wire ap_idle;
  wire ap_ready;
  wire ap_rst_n__q0;
  (* keep = "true" *)
  reg ap_rst_n__q1;
  (* keep = "true" *)
  reg ap_rst_n__q2;
  (* keep = "true" *)
  reg ap_rst_n__q3;

  always @(posedge ap_clk) begin
    ap_rst_n__q1 <= ap_rst_n__q0;
    ap_rst_n__q2 <= ap_rst_n__q1;
    ap_rst_n__q3 <= ap_rst_n__q2;
  end


  Jacobi_control_s_axi
  #(
    .C_S_AXI_ADDR_WIDTH(C_S_AXI_CONTROL_ADDR_WIDTH),
    .C_S_AXI_DATA_WIDTH(C_S_AXI_CONTROL_DATA_WIDTH)
  )
  control_s_axi_U_slr_0
  (
    .AWVALID(s_axi_control_AWVALID_slr_0),
    .AWREADY(s_axi_control_AWREADY_slr_0),
    .AWADDR(s_axi_control_AWADDR_slr_0),
    .WVALID(s_axi_control_WVALID_slr_0),
    .WREADY(s_axi_control_WREADY_slr_0),
    .WDATA(s_axi_control_WDATA_slr_0),
    .WSTRB(s_axi_control_WSTRB_slr_0),
    .ARVALID(s_axi_control_ARVALID),
    .ARREADY(s_axi_control_ARREADY),
    .ARADDR(s_axi_control_ARADDR),
    .RVALID(s_axi_control_RVALID),
    .RREADY(s_axi_control_RREADY),
    .RDATA(s_axi_control_RDATA),
    .RRESP(s_axi_control_RRESP),
    .BVALID(s_axi_control_BVALID),
    .BREADY(s_axi_control_BREADY),
    .BRESP(s_axi_control_BRESP),
    .ACLK(ap_clk),
    .ARESET(ap_rst_n_inv),
    .ACLK_EN(1'b1),
    .bank_0_t0(bank_0_t0_slr_0),
    .bank_0_t1(bank_0_t1_slr_0),
    .coalesced_data_num(coalesced_data_num_slr_0),
    .ap_start(ap_start),
    .interrupt(interrupt),
    .ap_ready(ap_ready),
    .ap_done(ap_done),
    .ap_idle(ap_idle)
  );


  Jacobi_control_s_axi
  #(
    .C_S_AXI_ADDR_WIDTH(C_S_AXI_CONTROL_ADDR_WIDTH),
    .C_S_AXI_DATA_WIDTH(C_S_AXI_CONTROL_DATA_WIDTH)
  )
  control_s_axi_U_slr_1
  (
    .AWVALID(s_axi_control_AWVALID_slr_1),
    .AWREADY(s_axi_control_AWREADY_slr_1),
    .AWADDR(s_axi_control_AWADDR_slr_1),
    .WVALID(s_axi_control_WVALID_slr_1),
    .WREADY(s_axi_control_WREADY_slr_1),
    .WDATA(s_axi_control_WDATA_slr_1),
    .WSTRB(s_axi_control_WSTRB_slr_1),
    .ARVALID(1'b0),
    .ARREADY(),
    .ARADDR(),
    .RVALID(),
    .RREADY(),
    .RDATA(),
    .RRESP(),
    .BVALID(),
    .BREADY(1'b1),
    .BRESP(),
    .ACLK(ap_clk),
    .ARESET(ap_rst_n_inv),
    .ACLK_EN(1'b1),
    .bank_0_t0(bank_0_t0_slr_1),
    .bank_0_t1(bank_0_t1_slr_1),
    .coalesced_data_num(coalesced_data_num_slr_1),
    .ap_start(),
    .interrupt(),
    .ap_ready(),
    .ap_done(),
    .ap_idle()
  );


  Jacobi_control_s_axi
  #(
    .C_S_AXI_ADDR_WIDTH(C_S_AXI_CONTROL_ADDR_WIDTH),
    .C_S_AXI_DATA_WIDTH(C_S_AXI_CONTROL_DATA_WIDTH)
  )
  control_s_axi_U_slr_2
  (
    .AWVALID(s_axi_control_AWVALID_slr_2),
    .AWREADY(s_axi_control_AWREADY_slr_2),
    .AWADDR(s_axi_control_AWADDR_slr_2),
    .WVALID(s_axi_control_WVALID_slr_2),
    .WREADY(s_axi_control_WREADY_slr_2),
    .WDATA(s_axi_control_WDATA_slr_2),
    .WSTRB(s_axi_control_WSTRB_slr_2),
    .ARVALID(1'b0),
    .ARREADY(),
    .ARADDR(),
    .RVALID(),
    .RREADY(),
    .RDATA(),
    .RRESP(),
    .BVALID(),
    .BREADY(1'b1),
    .BRESP(),
    .ACLK(ap_clk),
    .ARESET(ap_rst_n_inv),
    .ACLK_EN(1'b1),
    .bank_0_t0(bank_0_t0_slr_2),
    .bank_0_t1(bank_0_t1_slr_2),
    .coalesced_data_num(coalesced_data_num_slr_2),
    .ap_start(),
    .interrupt(),
    .ap_ready(),
    .ap_done(),
    .ap_idle()
  );


  a_axi_write_broadcastor_1_to_3
  #(
    .C_S_AXI_CONTROL_DATA_WIDTH(C_S_AXI_CONTROL_DATA_WIDTH),
    .C_S_AXI_CONTROL_ADDR_WIDTH(C_S_AXI_CONTROL_ADDR_WIDTH),
    .C_S_AXI_DATA_WIDTH(C_S_AXI_DATA_WIDTH),
    .C_S_AXI_CONTROL_WSTRB_WIDTH(C_S_AXI_CONTROL_WSTRB_WIDTH),
    .C_S_AXI_WSTRB_WIDTH(C_S_AXI_WSTRB_WIDTH)
  )
  s_axi_write_broadcastor
  (
    .ap_clk(ap_clk),
    .s_axi_control_AWVALID_slr_0(s_axi_control_AWVALID_slr_0),
    .s_axi_control_AWREADY_slr_0(s_axi_control_AWREADY_slr_0),
    .s_axi_control_AWADDR_slr_0(s_axi_control_AWADDR_slr_0),
    .s_axi_control_WVALID_slr_0(s_axi_control_WVALID_slr_0),
    .s_axi_control_WREADY_slr_0(s_axi_control_WREADY_slr_0),
    .s_axi_control_WDATA_slr_0(s_axi_control_WDATA_slr_0),
    .s_axi_control_WSTRB_slr_0(s_axi_control_WSTRB_slr_0),
    .s_axi_control_AWVALID_slr_1(s_axi_control_AWVALID_slr_1),
    .s_axi_control_AWREADY_slr_1(s_axi_control_AWREADY_slr_1),
    .s_axi_control_AWADDR_slr_1(s_axi_control_AWADDR_slr_1),
    .s_axi_control_WVALID_slr_1(s_axi_control_WVALID_slr_1),
    .s_axi_control_WREADY_slr_1(s_axi_control_WREADY_slr_1),
    .s_axi_control_WDATA_slr_1(s_axi_control_WDATA_slr_1),
    .s_axi_control_WSTRB_slr_1(s_axi_control_WSTRB_slr_1),
    .s_axi_control_AWVALID_slr_2(s_axi_control_AWVALID_slr_2),
    .s_axi_control_AWREADY_slr_2(s_axi_control_AWREADY_slr_2),
    .s_axi_control_AWADDR_slr_2(s_axi_control_AWADDR_slr_2),
    .s_axi_control_WVALID_slr_2(s_axi_control_WVALID_slr_2),
    .s_axi_control_WREADY_slr_2(s_axi_control_WREADY_slr_2),
    .s_axi_control_WDATA_slr_2(s_axi_control_WDATA_slr_2),
    .s_axi_control_WSTRB_slr_2(s_axi_control_WSTRB_slr_2),
    .s_axi_control_AWVALID(s_axi_control_AWVALID),
    .s_axi_control_AWREADY(s_axi_control_AWREADY),
    .s_axi_control_AWADDR(s_axi_control_AWADDR),
    .s_axi_control_WVALID(s_axi_control_WVALID),
    .s_axi_control_WREADY(s_axi_control_WREADY),
    .s_axi_control_WDATA(s_axi_control_WDATA),
    .s_axi_control_WSTRB(s_axi_control_WSTRB)
  );


  (* keep_hierarchy = "yes" *) fifo
  #(
    .DATA_WIDTH(65),
    .ADDR_WIDTH(6),
    .DEPTH(33)
  )
  bank_0_t0_buf
  (
    .clk(ap_clk),
    .reset(bank_0_t0_buf__rst__q3),
    .if_dout(bank_0_t0_buf__dout),
    .if_empty_n(bank_0_t0_buf__empty_n),
    .if_read(bank_0_t0_buf__read),
    .if_read_ce(1'b1),
    .if_din(bank_0_t0_buf__din),
    .if_full_n(bank_0_t0_buf__full_n),
    .if_write(bank_0_t0_buf__write),
    .if_write_ce(1'b1)
  );


  (* keep_hierarchy = "yes" *) fifo
  #(
    .DATA_WIDTH(65),
    .ADDR_WIDTH(6),
    .DEPTH(33)
  )
  bank_0_t1_buf
  (
    .clk(ap_clk),
    .reset(bank_0_t1_buf__rst__q3),
    .if_dout(bank_0_t1_buf__dout),
    .if_empty_n(bank_0_t1_buf__empty_n),
    .if_read(bank_0_t1_buf__read),
    .if_read_ce(1'b1),
    .if_din(bank_0_t1_buf__din),
    .if_full_n(bank_0_t1_buf__full_n),
    .if_write(bank_0_t1_buf__write),
    .if_write_ce(1'b1)
  );


  (* keep_hierarchy = "yes" *) fifo
  #(
    .DATA_WIDTH(33),
    .ADDR_WIDTH(2),
    .DEPTH(3)
  )
  from_super_source_to_t1_offset_0
  (
    .clk(ap_clk),
    .reset(from_super_source_to_t1_offset_0__rst__q3),
    .if_dout(from_super_source_to_t1_offset_0__dout),
    .if_empty_n(from_super_source_to_t1_offset_0__empty_n),
    .if_read(from_super_source_to_t1_offset_0__read),
    .if_read_ce(1'b1),
    .if_din(from_super_source_to_t1_offset_0__din),
    .if_full_n(from_super_source_to_t1_offset_0__full_n),
    .if_write(from_super_source_to_t1_offset_0__write),
    .if_write_ce(1'b1)
  );


  (* keep_hierarchy = "yes" *) fifo
  #(
    .DATA_WIDTH(33),
    .ADDR_WIDTH(2),
    .DEPTH(3)
  )
  from_super_source_to_t1_offset_1
  (
    .clk(ap_clk),
    .reset(from_super_source_to_t1_offset_1__rst__q3),
    .if_dout(from_super_source_to_t1_offset_1__dout),
    .if_empty_n(from_super_source_to_t1_offset_1__empty_n),
    .if_read(from_super_source_to_t1_offset_1__read),
    .if_read_ce(1'b1),
    .if_din(from_super_source_to_t1_offset_1__din),
    .if_full_n(from_super_source_to_t1_offset_1__full_n),
    .if_write(from_super_source_to_t1_offset_1__write),
    .if_write_ce(1'b1)
  );


  (* keep_hierarchy = "yes" *) fifo
  #(
    .DATA_WIDTH(33),
    .ADDR_WIDTH(3),
    .DEPTH(5)
  )
  from_t0_pe_0_to_super_sink
  (
    .clk(ap_clk),
    .reset(from_t0_pe_0_to_super_sink__rst__q3),
    .if_dout(from_t0_pe_0_to_super_sink__dout),
    .if_empty_n(from_t0_pe_0_to_super_sink__empty_n),
    .if_read(from_t0_pe_0_to_super_sink__read),
    .if_read_ce(1'b1),
    .if_din(from_t0_pe_0_to_super_sink__din),
    .if_full_n(from_t0_pe_0_to_super_sink__full_n),
    .if_write(from_t0_pe_0_to_super_sink__write),
    .if_write_ce(1'b1)
  );


  (* keep_hierarchy = "yes" *) fifo
  #(
    .DATA_WIDTH(33),
    .ADDR_WIDTH(2),
    .DEPTH(3)
  )
  from_t0_pe_1_to_super_sink
  (
    .clk(ap_clk),
    .reset(from_t0_pe_1_to_super_sink__rst__q3),
    .if_dout(from_t0_pe_1_to_super_sink__dout),
    .if_empty_n(from_t0_pe_1_to_super_sink__empty_n),
    .if_read(from_t0_pe_1_to_super_sink__read),
    .if_read_ce(1'b1),
    .if_din(from_t0_pe_1_to_super_sink__din),
    .if_full_n(from_t0_pe_1_to_super_sink__full_n),
    .if_write(from_t0_pe_1_to_super_sink__write),
    .if_write_ce(1'b1)
  );


  (* keep_hierarchy = "yes" *) fifo
  #(
    .DATA_WIDTH(33),
    .ADDR_WIDTH(2),
    .DEPTH(3)
  )
  from_t1_offset_0_to_t1_offset_2000
  (
    .clk(ap_clk),
    .reset(from_t1_offset_0_to_t1_offset_2000__rst__q3),
    .if_dout(from_t1_offset_0_to_t1_offset_2000__dout),
    .if_empty_n(from_t1_offset_0_to_t1_offset_2000__empty_n),
    .if_read(from_t1_offset_0_to_t1_offset_2000__read),
    .if_read_ce(1'b1),
    .if_din(from_t1_offset_0_to_t1_offset_2000__din),
    .if_full_n(from_t1_offset_0_to_t1_offset_2000__full_n),
    .if_write(from_t1_offset_0_to_t1_offset_2000__write),
    .if_write_ce(1'b1)
  );


  (* keep_hierarchy = "yes" *) fifo
  #(
    .DATA_WIDTH(33),
    .ADDR_WIDTH(3),
    .DEPTH(6)
  )
  from_t1_offset_0_to_tcse_var_0_pe_1
  (
    .clk(ap_clk),
    .reset(from_t1_offset_0_to_tcse_var_0_pe_1__rst__q3),
    .if_dout(from_t1_offset_0_to_tcse_var_0_pe_1__dout),
    .if_empty_n(from_t1_offset_0_to_tcse_var_0_pe_1__empty_n),
    .if_read(from_t1_offset_0_to_tcse_var_0_pe_1__read),
    .if_read_ce(1'b1),
    .if_din(from_t1_offset_0_to_tcse_var_0_pe_1__din),
    .if_full_n(from_t1_offset_0_to_tcse_var_0_pe_1__full_n),
    .if_write(from_t1_offset_0_to_tcse_var_0_pe_1__write),
    .if_write_ce(1'b1)
  );


  (* keep_hierarchy = "yes" *) fifo
  #(
    .DATA_WIDTH(33),
    .ADDR_WIDTH(2),
    .DEPTH(3)
  )
  from_t1_offset_1_to_t1_offset_2001
  (
    .clk(ap_clk),
    .reset(from_t1_offset_1_to_t1_offset_2001__rst__q3),
    .if_dout(from_t1_offset_1_to_t1_offset_2001__dout),
    .if_empty_n(from_t1_offset_1_to_t1_offset_2001__empty_n),
    .if_read(from_t1_offset_1_to_t1_offset_2001__read),
    .if_read_ce(1'b1),
    .if_din(from_t1_offset_1_to_t1_offset_2001__din),
    .if_full_n(from_t1_offset_1_to_t1_offset_2001__full_n),
    .if_write(from_t1_offset_1_to_t1_offset_2001__write),
    .if_write_ce(1'b1)
  );


  (* keep_hierarchy = "yes" *) fifo
  #(
    .DATA_WIDTH(33),
    .ADDR_WIDTH(3),
    .DEPTH(8)
  )
  from_t1_offset_1_to_tcse_var_0_pe_0
  (
    .clk(ap_clk),
    .reset(from_t1_offset_1_to_tcse_var_0_pe_0__rst__q3),
    .if_dout(from_t1_offset_1_to_tcse_var_0_pe_0__dout),
    .if_empty_n(from_t1_offset_1_to_tcse_var_0_pe_0__empty_n),
    .if_read(from_t1_offset_1_to_tcse_var_0_pe_0__read),
    .if_read_ce(1'b1),
    .if_din(from_t1_offset_1_to_tcse_var_0_pe_0__din),
    .if_full_n(from_t1_offset_1_to_tcse_var_0_pe_0__full_n),
    .if_write(from_t1_offset_1_to_tcse_var_0_pe_0__write),
    .if_write_ce(1'b1)
  );


  (* keep_hierarchy = "yes" *) fifo
  #(
    .DATA_WIDTH(33),
    .ADDR_WIDTH(6),
    .DEPTH(61)
  )
  from_t1_offset_2000_to_t0_pe_1
  (
    .clk(ap_clk),
    .reset(from_t1_offset_2000_to_t0_pe_1__rst__q3),
    .if_dout(from_t1_offset_2000_to_t0_pe_1__dout),
    .if_empty_n(from_t1_offset_2000_to_t0_pe_1__empty_n),
    .if_read(from_t1_offset_2000_to_t0_pe_1__read),
    .if_read_ce(1'b1),
    .if_din(from_t1_offset_2000_to_t0_pe_1__din),
    .if_full_n(from_t1_offset_2000_to_t0_pe_1__full_n),
    .if_write(from_t1_offset_2000_to_t0_pe_1__write),
    .if_write_ce(1'b1)
  );


  (* keep_hierarchy = "yes" *) fifo
  #(
    .DATA_WIDTH(33),
    .ADDR_WIDTH(6),
    .DEPTH(54)
  )
  from_t1_offset_2000_to_tcse_var_0_pe_0
  (
    .clk(ap_clk),
    .reset(from_t1_offset_2000_to_tcse_var_0_pe_0__rst__q3),
    .if_dout(from_t1_offset_2000_to_tcse_var_0_pe_0__dout),
    .if_empty_n(from_t1_offset_2000_to_tcse_var_0_pe_0__empty_n),
    .if_read(from_t1_offset_2000_to_tcse_var_0_pe_0__read),
    .if_read_ce(1'b1),
    .if_din(from_t1_offset_2000_to_tcse_var_0_pe_0__din),
    .if_full_n(from_t1_offset_2000_to_tcse_var_0_pe_0__full_n),
    .if_write(from_t1_offset_2000_to_tcse_var_0_pe_0__write),
    .if_write_ce(1'b1)
  );


  (* keep_hierarchy = "yes" *) fifo
  #(
    .DATA_WIDTH(33),
    .ADDR_WIDTH(6),
    .DEPTH(59)
  )
  from_t1_offset_2001_to_t0_pe_0
  (
    .clk(ap_clk),
    .reset(from_t1_offset_2001_to_t0_pe_0__rst__q3),
    .if_dout(from_t1_offset_2001_to_t0_pe_0__dout),
    .if_empty_n(from_t1_offset_2001_to_t0_pe_0__empty_n),
    .if_read(from_t1_offset_2001_to_t0_pe_0__read),
    .if_read_ce(1'b1),
    .if_din(from_t1_offset_2001_to_t0_pe_0__din),
    .if_full_n(from_t1_offset_2001_to_t0_pe_0__full_n),
    .if_write(from_t1_offset_2001_to_t0_pe_0__write),
    .if_write_ce(1'b1)
  );


  (* keep_hierarchy = "yes" *) fifo
  #(
    .DATA_WIDTH(33),
    .ADDR_WIDTH(6),
    .DEPTH(53)
  )
  from_t1_offset_2001_to_tcse_var_0_pe_1
  (
    .clk(ap_clk),
    .reset(from_t1_offset_2001_to_tcse_var_0_pe_1__rst__q3),
    .if_dout(from_t1_offset_2001_to_tcse_var_0_pe_1__dout),
    .if_empty_n(from_t1_offset_2001_to_tcse_var_0_pe_1__empty_n),
    .if_read(from_t1_offset_2001_to_tcse_var_0_pe_1__read),
    .if_read_ce(1'b1),
    .if_din(from_t1_offset_2001_to_tcse_var_0_pe_1__din),
    .if_full_n(from_t1_offset_2001_to_tcse_var_0_pe_1__full_n),
    .if_write(from_t1_offset_2001_to_tcse_var_0_pe_1__write),
    .if_write_ce(1'b1)
  );


  (* keep_hierarchy = "yes" *) fifo
  #(
    .DATA_WIDTH(33),
    .ADDR_WIDTH(6),
    .DEPTH(53)
  )
  from_tcse_var_0_offset_0_to_t0_pe_0
  (
    .clk(ap_clk),
    .reset(from_tcse_var_0_offset_0_to_t0_pe_0__rst__q3),
    .if_dout(from_tcse_var_0_offset_0_to_t0_pe_0__dout),
    .if_empty_n(from_tcse_var_0_offset_0_to_t0_pe_0__empty_n),
    .if_read(from_tcse_var_0_offset_0_to_t0_pe_0__read),
    .if_read_ce(1'b1),
    .if_din(from_tcse_var_0_offset_0_to_t0_pe_0__din),
    .if_full_n(from_tcse_var_0_offset_0_to_t0_pe_0__full_n),
    .if_write(from_tcse_var_0_offset_0_to_t0_pe_0__write),
    .if_write_ce(1'b1)
  );


  (* keep_hierarchy = "yes" *) fifo
  #(
    .DATA_WIDTH(33),
    .ADDR_WIDTH(3),
    .DEPTH(7)
  )
  from_tcse_var_0_offset_0_to_t0_pe_1
  (
    .clk(ap_clk),
    .reset(from_tcse_var_0_offset_0_to_t0_pe_1__rst__q3),
    .if_dout(from_tcse_var_0_offset_0_to_t0_pe_1__dout),
    .if_empty_n(from_tcse_var_0_offset_0_to_t0_pe_1__empty_n),
    .if_read(from_tcse_var_0_offset_0_to_t0_pe_1__read),
    .if_read_ce(1'b1),
    .if_din(from_tcse_var_0_offset_0_to_t0_pe_1__din),
    .if_full_n(from_tcse_var_0_offset_0_to_t0_pe_1__full_n),
    .if_write(from_tcse_var_0_offset_0_to_t0_pe_1__write),
    .if_write_ce(1'b1)
  );


  (* keep_hierarchy = "yes" *) fifo
  #(
    .DATA_WIDTH(33),
    .ADDR_WIDTH(2),
    .DEPTH(3)
  )
  from_tcse_var_0_offset_1_to_t0_pe_0
  (
    .clk(ap_clk),
    .reset(from_tcse_var_0_offset_1_to_t0_pe_0__rst__q3),
    .if_dout(from_tcse_var_0_offset_1_to_t0_pe_0__dout),
    .if_empty_n(from_tcse_var_0_offset_1_to_t0_pe_0__empty_n),
    .if_read(from_tcse_var_0_offset_1_to_t0_pe_0__read),
    .if_read_ce(1'b1),
    .if_din(from_tcse_var_0_offset_1_to_t0_pe_0__din),
    .if_full_n(from_tcse_var_0_offset_1_to_t0_pe_0__full_n),
    .if_write(from_tcse_var_0_offset_1_to_t0_pe_0__write),
    .if_write_ce(1'b1)
  );


  (* keep_hierarchy = "yes" *) fifo
  #(
    .DATA_WIDTH(33),
    .ADDR_WIDTH(6),
    .DEPTH(52)
  )
  from_tcse_var_0_offset_1_to_t0_pe_1
  (
    .clk(ap_clk),
    .reset(from_tcse_var_0_offset_1_to_t0_pe_1__rst__q3),
    .if_dout(from_tcse_var_0_offset_1_to_t0_pe_1__dout),
    .if_empty_n(from_tcse_var_0_offset_1_to_t0_pe_1__empty_n),
    .if_read(from_tcse_var_0_offset_1_to_t0_pe_1__read),
    .if_read_ce(1'b1),
    .if_din(from_tcse_var_0_offset_1_to_t0_pe_1__din),
    .if_full_n(from_tcse_var_0_offset_1_to_t0_pe_1__full_n),
    .if_write(from_tcse_var_0_offset_1_to_t0_pe_1__write),
    .if_write_ce(1'b1)
  );


  (* keep_hierarchy = "yes" *) fifo
  #(
    .DATA_WIDTH(33),
    .ADDR_WIDTH(2),
    .DEPTH(3)
  )
  from_tcse_var_0_pe_0_to_tcse_var_0_offset_1
  (
    .clk(ap_clk),
    .reset(from_tcse_var_0_pe_0_to_tcse_var_0_offset_1__rst__q3),
    .if_dout(from_tcse_var_0_pe_0_to_tcse_var_0_offset_1__dout),
    .if_empty_n(from_tcse_var_0_pe_0_to_tcse_var_0_offset_1__empty_n),
    .if_read(from_tcse_var_0_pe_0_to_tcse_var_0_offset_1__read),
    .if_read_ce(1'b1),
    .if_din(from_tcse_var_0_pe_0_to_tcse_var_0_offset_1__din),
    .if_full_n(from_tcse_var_0_pe_0_to_tcse_var_0_offset_1__full_n),
    .if_write(from_tcse_var_0_pe_0_to_tcse_var_0_offset_1__write),
    .if_write_ce(1'b1)
  );


  (* keep_hierarchy = "yes" *) fifo
  #(
    .DATA_WIDTH(33),
    .ADDR_WIDTH(2),
    .DEPTH(3)
  )
  from_tcse_var_0_pe_1_to_tcse_var_0_offset_0
  (
    .clk(ap_clk),
    .reset(from_tcse_var_0_pe_1_to_tcse_var_0_offset_0__rst__q3),
    .if_dout(from_tcse_var_0_pe_1_to_tcse_var_0_offset_0__dout),
    .if_empty_n(from_tcse_var_0_pe_1_to_tcse_var_0_offset_0__empty_n),
    .if_read(from_tcse_var_0_pe_1_to_tcse_var_0_offset_0__read),
    .if_read_ce(1'b1),
    .if_din(from_tcse_var_0_pe_1_to_tcse_var_0_offset_0__din),
    .if_full_n(from_tcse_var_0_pe_1_to_tcse_var_0_offset_0__full_n),
    .if_write(from_tcse_var_0_pe_1_to_tcse_var_0_offset_0__write),
    .if_write_ce(1'b1)
  );


  (* keep_hierarchy = "yes" *) Mmap2Stream
  Mmap2Stream_0
  (
    .ap_clk(ap_clk),
    .ap_rst_n(Mmap2Stream_0__ap_rst_n__q3),
    .ap_start(Mmap2Stream_0__ap_start),
    .ap_done(Mmap2Stream_0__ap_done),
    .ap_idle(Mmap2Stream_0__ap_idle),
    .ap_ready(Mmap2Stream_0__ap_ready),
    .m_axi_mmap_ARADDR(m_axi_bank_0_t1_ARADDR),
    .m_axi_mmap_ARBURST(m_axi_bank_0_t1_ARBURST),
    .m_axi_mmap_ARID(m_axi_bank_0_t1_ARID),
    .m_axi_mmap_ARLEN(m_axi_bank_0_t1_ARLEN),
    .m_axi_mmap_ARREADY(m_axi_bank_0_t1_ARREADY),
    .m_axi_mmap_ARSIZE(m_axi_bank_0_t1_ARSIZE),
    .m_axi_mmap_ARVALID(m_axi_bank_0_t1_ARVALID),
    .m_axi_mmap_AWADDR(m_axi_bank_0_t1_AWADDR),
    .m_axi_mmap_AWBURST(m_axi_bank_0_t1_AWBURST),
    .m_axi_mmap_AWID(m_axi_bank_0_t1_AWID),
    .m_axi_mmap_AWLEN(m_axi_bank_0_t1_AWLEN),
    .m_axi_mmap_AWREADY(m_axi_bank_0_t1_AWREADY),
    .m_axi_mmap_AWSIZE(m_axi_bank_0_t1_AWSIZE),
    .m_axi_mmap_AWVALID(m_axi_bank_0_t1_AWVALID),
    .m_axi_mmap_BID(m_axi_bank_0_t1_BID),
    .m_axi_mmap_BREADY(m_axi_bank_0_t1_BREADY),
    .m_axi_mmap_BRESP(m_axi_bank_0_t1_BRESP),
    .m_axi_mmap_BVALID(m_axi_bank_0_t1_BVALID),
    .m_axi_mmap_RDATA(m_axi_bank_0_t1_RDATA),
    .m_axi_mmap_RID(m_axi_bank_0_t1_RID),
    .m_axi_mmap_RLAST(m_axi_bank_0_t1_RLAST),
    .m_axi_mmap_RREADY(m_axi_bank_0_t1_RREADY),
    .m_axi_mmap_RRESP(m_axi_bank_0_t1_RRESP),
    .m_axi_mmap_RVALID(m_axi_bank_0_t1_RVALID),
    .m_axi_mmap_WDATA(m_axi_bank_0_t1_WDATA),
    .m_axi_mmap_WLAST(m_axi_bank_0_t1_WLAST),
    .m_axi_mmap_WREADY(m_axi_bank_0_t1_WREADY),
    .m_axi_mmap_WSTRB(m_axi_bank_0_t1_WSTRB),
    .m_axi_mmap_WVALID(m_axi_bank_0_t1_WVALID),
    .m_axi_mmap_ARLOCK(m_axi_bank_0_t1_ARLOCK),
    .m_axi_mmap_ARPROT(m_axi_bank_0_t1_ARPROT),
    .m_axi_mmap_ARQOS(m_axi_bank_0_t1_ARQOS),
    .m_axi_mmap_ARCACHE(m_axi_bank_0_t1_ARCACHE),
    .m_axi_mmap_AWCACHE(m_axi_bank_0_t1_AWCACHE),
    .m_axi_mmap_AWLOCK(m_axi_bank_0_t1_AWLOCK),
    .m_axi_mmap_AWPROT(m_axi_bank_0_t1_AWPROT),
    .m_axi_mmap_AWQOS(m_axi_bank_0_t1_AWQOS),
    .mmap_offset(Mmap2Stream_0___bank_0_t1__q2),
    .stream_din(bank_0_t1_buf__din),
    .stream_full_n(bank_0_t1_buf__full_n),
    .stream_write(bank_0_t1_buf__write),
    .n(Mmap2Stream_0___coalesced_data_num__q2)
  );


  (* keep_hierarchy = "yes" *) Module0Func
  Module0Func_0
  (
    .ap_clk(ap_clk),
    .ap_rst_n(Module0Func_0__ap_rst_n__q3),
    .ap_start(Module0Func_0__ap_start),
    .ap_done(Module0Func_0__ap_done),
    .ap_idle(Module0Func_0__ap_idle),
    .ap_ready(Module0Func_0__ap_ready),
    .dram_t1_bank_0_fifo_s_dout(bank_0_t1_buf__dout),
    .dram_t1_bank_0_fifo_peek_dout(bank_0_t1_buf__dout),
    .dram_t1_bank_0_fifo_s_empty_n(bank_0_t1_buf__empty_n),
    .dram_t1_bank_0_fifo_peek_empty_n(bank_0_t1_buf__empty_n),
    .dram_t1_bank_0_fifo_s_read(bank_0_t1_buf__read),
    .dram_t1_bank_0_fifo_peek_read(),
    .fifo_st_0_din(from_super_source_to_t1_offset_0__din),
    .fifo_st_0_full_n(from_super_source_to_t1_offset_0__full_n),
    .fifo_st_0_write(from_super_source_to_t1_offset_0__write),
    .fifo_st_1_din(from_super_source_to_t1_offset_1__din),
    .fifo_st_1_full_n(from_super_source_to_t1_offset_1__full_n),
    .fifo_st_1_write(from_super_source_to_t1_offset_1__write)
  );


  (* keep_hierarchy = "yes" *) Module1Func
  Module1Func_0
  (
    .ap_clk(ap_clk),
    .ap_rst_n(Module1Func_0__ap_rst_n__q3),
    .ap_start(Module1Func_0__ap_start),
    .ap_done(Module1Func_0__ap_done),
    .ap_idle(Module1Func_0__ap_idle),
    .ap_ready(Module1Func_0__ap_ready),
    .fifo_ld_0_s_dout(from_super_source_to_t1_offset_0__dout),
    .fifo_ld_0_peek_dout(from_super_source_to_t1_offset_0__dout),
    .fifo_ld_0_s_empty_n(from_super_source_to_t1_offset_0__empty_n),
    .fifo_ld_0_peek_empty_n(from_super_source_to_t1_offset_0__empty_n),
    .fifo_ld_0_s_read(from_super_source_to_t1_offset_0__read),
    .fifo_ld_0_peek_read(),
    .fifo_st_0_din(from_t1_offset_0_to_t1_offset_2000__din),
    .fifo_st_0_full_n(from_t1_offset_0_to_t1_offset_2000__full_n),
    .fifo_st_0_write(from_t1_offset_0_to_t1_offset_2000__write),
    .fifo_st_1_din(from_t1_offset_0_to_tcse_var_0_pe_1__din),
    .fifo_st_1_full_n(from_t1_offset_0_to_tcse_var_0_pe_1__full_n),
    .fifo_st_1_write(from_t1_offset_0_to_tcse_var_0_pe_1__write)
  );


  (* keep_hierarchy = "yes" *) Module1Func
  Module1Func_1
  (
    .ap_clk(ap_clk),
    .ap_rst_n(Module1Func_1__ap_rst_n__q3),
    .ap_start(Module1Func_1__ap_start),
    .ap_done(Module1Func_1__ap_done),
    .ap_idle(Module1Func_1__ap_idle),
    .ap_ready(Module1Func_1__ap_ready),
    .fifo_ld_0_s_dout(from_super_source_to_t1_offset_1__dout),
    .fifo_ld_0_peek_dout(from_super_source_to_t1_offset_1__dout),
    .fifo_ld_0_s_empty_n(from_super_source_to_t1_offset_1__empty_n),
    .fifo_ld_0_peek_empty_n(from_super_source_to_t1_offset_1__empty_n),
    .fifo_ld_0_s_read(from_super_source_to_t1_offset_1__read),
    .fifo_ld_0_peek_read(),
    .fifo_st_0_din(from_t1_offset_1_to_t1_offset_2001__din),
    .fifo_st_0_full_n(from_t1_offset_1_to_t1_offset_2001__full_n),
    .fifo_st_0_write(from_t1_offset_1_to_t1_offset_2001__write),
    .fifo_st_1_din(from_t1_offset_1_to_tcse_var_0_pe_0__din),
    .fifo_st_1_full_n(from_t1_offset_1_to_tcse_var_0_pe_0__full_n),
    .fifo_st_1_write(from_t1_offset_1_to_tcse_var_0_pe_0__write)
  );


  (* keep_hierarchy = "yes" *) Module1Func
  Module1Func_2
  (
    .ap_clk(ap_clk),
    .ap_rst_n(Module1Func_2__ap_rst_n__q3),
    .ap_start(Module1Func_2__ap_start),
    .ap_done(Module1Func_2__ap_done),
    .ap_idle(Module1Func_2__ap_idle),
    .ap_ready(Module1Func_2__ap_ready),
    .fifo_ld_0_s_dout(from_t1_offset_0_to_t1_offset_2000__dout),
    .fifo_ld_0_peek_dout(from_t1_offset_0_to_t1_offset_2000__dout),
    .fifo_ld_0_s_empty_n(from_t1_offset_0_to_t1_offset_2000__empty_n),
    .fifo_ld_0_peek_empty_n(from_t1_offset_0_to_t1_offset_2000__empty_n),
    .fifo_ld_0_s_read(from_t1_offset_0_to_t1_offset_2000__read),
    .fifo_ld_0_peek_read(),
    .fifo_st_1_din(from_t1_offset_2000_to_t0_pe_1__din),
    .fifo_st_1_full_n(from_t1_offset_2000_to_t0_pe_1__full_n),
    .fifo_st_1_write(from_t1_offset_2000_to_t0_pe_1__write),
    .fifo_st_0_din(from_t1_offset_2000_to_tcse_var_0_pe_0__din),
    .fifo_st_0_full_n(from_t1_offset_2000_to_tcse_var_0_pe_0__full_n),
    .fifo_st_0_write(from_t1_offset_2000_to_tcse_var_0_pe_0__write)
  );


  (* keep_hierarchy = "yes" *) Module1Func
  Module1Func_3
  (
    .ap_clk(ap_clk),
    .ap_rst_n(Module1Func_3__ap_rst_n__q3),
    .ap_start(Module1Func_3__ap_start),
    .ap_done(Module1Func_3__ap_done),
    .ap_idle(Module1Func_3__ap_idle),
    .ap_ready(Module1Func_3__ap_ready),
    .fifo_ld_0_s_dout(from_t1_offset_1_to_t1_offset_2001__dout),
    .fifo_ld_0_peek_dout(from_t1_offset_1_to_t1_offset_2001__dout),
    .fifo_ld_0_s_empty_n(from_t1_offset_1_to_t1_offset_2001__empty_n),
    .fifo_ld_0_peek_empty_n(from_t1_offset_1_to_t1_offset_2001__empty_n),
    .fifo_ld_0_s_read(from_t1_offset_1_to_t1_offset_2001__read),
    .fifo_ld_0_peek_read(),
    .fifo_st_1_din(from_t1_offset_2001_to_t0_pe_0__din),
    .fifo_st_1_full_n(from_t1_offset_2001_to_t0_pe_0__full_n),
    .fifo_st_1_write(from_t1_offset_2001_to_t0_pe_0__write),
    .fifo_st_0_din(from_t1_offset_2001_to_tcse_var_0_pe_1__din),
    .fifo_st_0_full_n(from_t1_offset_2001_to_tcse_var_0_pe_1__full_n),
    .fifo_st_0_write(from_t1_offset_2001_to_tcse_var_0_pe_1__write)
  );


  (* keep_hierarchy = "yes" *) Module1Func
  Module1Func_4
  (
    .ap_clk(ap_clk),
    .ap_rst_n(Module1Func_4__ap_rst_n__q3),
    .ap_start(Module1Func_4__ap_start),
    .ap_done(Module1Func_4__ap_done),
    .ap_idle(Module1Func_4__ap_idle),
    .ap_ready(Module1Func_4__ap_ready),
    .fifo_st_0_din(from_tcse_var_0_offset_0_to_t0_pe_0__din),
    .fifo_st_0_full_n(from_tcse_var_0_offset_0_to_t0_pe_0__full_n),
    .fifo_st_0_write(from_tcse_var_0_offset_0_to_t0_pe_0__write),
    .fifo_st_1_din(from_tcse_var_0_offset_0_to_t0_pe_1__din),
    .fifo_st_1_full_n(from_tcse_var_0_offset_0_to_t0_pe_1__full_n),
    .fifo_st_1_write(from_tcse_var_0_offset_0_to_t0_pe_1__write),
    .fifo_ld_0_s_dout(from_tcse_var_0_pe_1_to_tcse_var_0_offset_0__dout),
    .fifo_ld_0_peek_dout(from_tcse_var_0_pe_1_to_tcse_var_0_offset_0__dout),
    .fifo_ld_0_s_empty_n(from_tcse_var_0_pe_1_to_tcse_var_0_offset_0__empty_n),
    .fifo_ld_0_peek_empty_n(from_tcse_var_0_pe_1_to_tcse_var_0_offset_0__empty_n),
    .fifo_ld_0_s_read(from_tcse_var_0_pe_1_to_tcse_var_0_offset_0__read),
    .fifo_ld_0_peek_read()
  );


  (* keep_hierarchy = "yes" *) Module1Func
  Module1Func_5
  (
    .ap_clk(ap_clk),
    .ap_rst_n(Module1Func_5__ap_rst_n__q3),
    .ap_start(Module1Func_5__ap_start),
    .ap_done(Module1Func_5__ap_done),
    .ap_idle(Module1Func_5__ap_idle),
    .ap_ready(Module1Func_5__ap_ready),
    .fifo_st_1_din(from_tcse_var_0_offset_1_to_t0_pe_0__din),
    .fifo_st_1_full_n(from_tcse_var_0_offset_1_to_t0_pe_0__full_n),
    .fifo_st_1_write(from_tcse_var_0_offset_1_to_t0_pe_0__write),
    .fifo_st_0_din(from_tcse_var_0_offset_1_to_t0_pe_1__din),
    .fifo_st_0_full_n(from_tcse_var_0_offset_1_to_t0_pe_1__full_n),
    .fifo_st_0_write(from_tcse_var_0_offset_1_to_t0_pe_1__write),
    .fifo_ld_0_s_dout(from_tcse_var_0_pe_0_to_tcse_var_0_offset_1__dout),
    .fifo_ld_0_peek_dout(from_tcse_var_0_pe_0_to_tcse_var_0_offset_1__dout),
    .fifo_ld_0_s_empty_n(from_tcse_var_0_pe_0_to_tcse_var_0_offset_1__empty_n),
    .fifo_ld_0_peek_empty_n(from_tcse_var_0_pe_0_to_tcse_var_0_offset_1__empty_n),
    .fifo_ld_0_s_read(from_tcse_var_0_pe_0_to_tcse_var_0_offset_1__read),
    .fifo_ld_0_peek_read()
  );


  (* keep_hierarchy = "yes" *) Module3Func1
  Module3Func1_0
  (
    .ap_clk(ap_clk),
    .ap_rst_n(Module3Func1_0__ap_rst_n__q3),
    .ap_start(Module3Func1_0__ap_start),
    .ap_done(Module3Func1_0__ap_done),
    .ap_idle(Module3Func1_0__ap_idle),
    .ap_ready(Module3Func1_0__ap_ready),
    .fifo_ld_1_s_dout(from_t1_offset_0_to_tcse_var_0_pe_1__dout),
    .fifo_ld_1_peek_dout(from_t1_offset_0_to_tcse_var_0_pe_1__dout),
    .fifo_ld_1_s_empty_n(from_t1_offset_0_to_tcse_var_0_pe_1__empty_n),
    .fifo_ld_1_peek_empty_n(from_t1_offset_0_to_tcse_var_0_pe_1__empty_n),
    .fifo_ld_1_s_read(from_t1_offset_0_to_tcse_var_0_pe_1__read),
    .fifo_ld_1_peek_read(),
    .fifo_ld_0_s_dout(from_t1_offset_2001_to_tcse_var_0_pe_1__dout),
    .fifo_ld_0_peek_dout(from_t1_offset_2001_to_tcse_var_0_pe_1__dout),
    .fifo_ld_0_s_empty_n(from_t1_offset_2001_to_tcse_var_0_pe_1__empty_n),
    .fifo_ld_0_peek_empty_n(from_t1_offset_2001_to_tcse_var_0_pe_1__empty_n),
    .fifo_ld_0_s_read(from_t1_offset_2001_to_tcse_var_0_pe_1__read),
    .fifo_ld_0_peek_read(),
    .fifo_st_0_din(from_tcse_var_0_pe_1_to_tcse_var_0_offset_0__din),
    .fifo_st_0_full_n(from_tcse_var_0_pe_1_to_tcse_var_0_offset_0__full_n),
    .fifo_st_0_write(from_tcse_var_0_pe_1_to_tcse_var_0_offset_0__write)
  );


  (* keep_hierarchy = "yes" *) Module3Func2
  Module3Func2_0
  (
    .ap_clk(ap_clk),
    .ap_rst_n(Module3Func2_0__ap_rst_n__q3),
    .ap_start(Module3Func2_0__ap_start),
    .ap_done(Module3Func2_0__ap_done),
    .ap_idle(Module3Func2_0__ap_idle),
    .ap_ready(Module3Func2_0__ap_ready),
    .fifo_ld_1_s_dout(from_t1_offset_1_to_tcse_var_0_pe_0__dout),
    .fifo_ld_1_peek_dout(from_t1_offset_1_to_tcse_var_0_pe_0__dout),
    .fifo_ld_1_s_empty_n(from_t1_offset_1_to_tcse_var_0_pe_0__empty_n),
    .fifo_ld_1_peek_empty_n(from_t1_offset_1_to_tcse_var_0_pe_0__empty_n),
    .fifo_ld_1_s_read(from_t1_offset_1_to_tcse_var_0_pe_0__read),
    .fifo_ld_1_peek_read(),
    .fifo_ld_0_s_dout(from_t1_offset_2000_to_tcse_var_0_pe_0__dout),
    .fifo_ld_0_peek_dout(from_t1_offset_2000_to_tcse_var_0_pe_0__dout),
    .fifo_ld_0_s_empty_n(from_t1_offset_2000_to_tcse_var_0_pe_0__empty_n),
    .fifo_ld_0_peek_empty_n(from_t1_offset_2000_to_tcse_var_0_pe_0__empty_n),
    .fifo_ld_0_s_read(from_t1_offset_2000_to_tcse_var_0_pe_0__read),
    .fifo_ld_0_peek_read(),
    .fifo_st_0_din(from_tcse_var_0_pe_0_to_tcse_var_0_offset_1__din),
    .fifo_st_0_full_n(from_tcse_var_0_pe_0_to_tcse_var_0_offset_1__full_n),
    .fifo_st_0_write(from_tcse_var_0_pe_0_to_tcse_var_0_offset_1__write)
  );


  (* keep_hierarchy = "yes" *) Module6Func1
  Module6Func1_0
  (
    .ap_clk(ap_clk),
    .ap_rst_n(Module6Func1_0__ap_rst_n__q3),
    .ap_start(Module6Func1_0__ap_start),
    .ap_done(Module6Func1_0__ap_done),
    .ap_idle(Module6Func1_0__ap_idle),
    .ap_ready(Module6Func1_0__ap_ready),
    .fifo_st_0_din(from_t0_pe_0_to_super_sink__din),
    .fifo_st_0_full_n(from_t0_pe_0_to_super_sink__full_n),
    .fifo_st_0_write(from_t0_pe_0_to_super_sink__write),
    .fifo_ld_2_s_dout(from_t1_offset_2001_to_t0_pe_0__dout),
    .fifo_ld_2_peek_dout(from_t1_offset_2001_to_t0_pe_0__dout),
    .fifo_ld_2_s_empty_n(from_t1_offset_2001_to_t0_pe_0__empty_n),
    .fifo_ld_2_peek_empty_n(from_t1_offset_2001_to_t0_pe_0__empty_n),
    .fifo_ld_2_s_read(from_t1_offset_2001_to_t0_pe_0__read),
    .fifo_ld_2_peek_read(),
    .fifo_ld_0_s_dout(from_tcse_var_0_offset_0_to_t0_pe_0__dout),
    .fifo_ld_0_peek_dout(from_tcse_var_0_offset_0_to_t0_pe_0__dout),
    .fifo_ld_0_s_empty_n(from_tcse_var_0_offset_0_to_t0_pe_0__empty_n),
    .fifo_ld_0_peek_empty_n(from_tcse_var_0_offset_0_to_t0_pe_0__empty_n),
    .fifo_ld_0_s_read(from_tcse_var_0_offset_0_to_t0_pe_0__read),
    .fifo_ld_0_peek_read(),
    .fifo_ld_1_s_dout(from_tcse_var_0_offset_1_to_t0_pe_0__dout),
    .fifo_ld_1_peek_dout(from_tcse_var_0_offset_1_to_t0_pe_0__dout),
    .fifo_ld_1_s_empty_n(from_tcse_var_0_offset_1_to_t0_pe_0__empty_n),
    .fifo_ld_1_peek_empty_n(from_tcse_var_0_offset_1_to_t0_pe_0__empty_n),
    .fifo_ld_1_s_read(from_tcse_var_0_offset_1_to_t0_pe_0__read),
    .fifo_ld_1_peek_read()
  );


  (* keep_hierarchy = "yes" *) Module6Func2
  Module6Func2_0
  (
    .ap_clk(ap_clk),
    .ap_rst_n(Module6Func2_0__ap_rst_n__q3),
    .ap_start(Module6Func2_0__ap_start),
    .ap_done(Module6Func2_0__ap_done),
    .ap_idle(Module6Func2_0__ap_idle),
    .ap_ready(Module6Func2_0__ap_ready),
    .fifo_st_0_din(from_t0_pe_1_to_super_sink__din),
    .fifo_st_0_full_n(from_t0_pe_1_to_super_sink__full_n),
    .fifo_st_0_write(from_t0_pe_1_to_super_sink__write),
    .fifo_ld_2_s_dout(from_t1_offset_2000_to_t0_pe_1__dout),
    .fifo_ld_2_peek_dout(from_t1_offset_2000_to_t0_pe_1__dout),
    .fifo_ld_2_s_empty_n(from_t1_offset_2000_to_t0_pe_1__empty_n),
    .fifo_ld_2_peek_empty_n(from_t1_offset_2000_to_t0_pe_1__empty_n),
    .fifo_ld_2_s_read(from_t1_offset_2000_to_t0_pe_1__read),
    .fifo_ld_2_peek_read(),
    .fifo_ld_1_s_dout(from_tcse_var_0_offset_0_to_t0_pe_1__dout),
    .fifo_ld_1_peek_dout(from_tcse_var_0_offset_0_to_t0_pe_1__dout),
    .fifo_ld_1_s_empty_n(from_tcse_var_0_offset_0_to_t0_pe_1__empty_n),
    .fifo_ld_1_peek_empty_n(from_tcse_var_0_offset_0_to_t0_pe_1__empty_n),
    .fifo_ld_1_s_read(from_tcse_var_0_offset_0_to_t0_pe_1__read),
    .fifo_ld_1_peek_read(),
    .fifo_ld_0_s_dout(from_tcse_var_0_offset_1_to_t0_pe_1__dout),
    .fifo_ld_0_peek_dout(from_tcse_var_0_offset_1_to_t0_pe_1__dout),
    .fifo_ld_0_s_empty_n(from_tcse_var_0_offset_1_to_t0_pe_1__empty_n),
    .fifo_ld_0_peek_empty_n(from_tcse_var_0_offset_1_to_t0_pe_1__empty_n),
    .fifo_ld_0_s_read(from_tcse_var_0_offset_1_to_t0_pe_1__read),
    .fifo_ld_0_peek_read()
  );


  (* keep_hierarchy = "yes" *) Module8Func
  Module8Func_0
  (
    .ap_clk(ap_clk),
    .ap_rst_n(Module8Func_0__ap_rst_n__q3),
    .ap_start(Module8Func_0__ap_start),
    .ap_done(Module8Func_0__ap_done),
    .ap_idle(Module8Func_0__ap_idle),
    .ap_ready(Module8Func_0__ap_ready),
    .dram_t0_bank_0_fifo_din(bank_0_t0_buf__din),
    .dram_t0_bank_0_fifo_full_n(bank_0_t0_buf__full_n),
    .dram_t0_bank_0_fifo_write(bank_0_t0_buf__write),
    .fifo_ld_0_s_dout(from_t0_pe_0_to_super_sink__dout),
    .fifo_ld_0_peek_dout(from_t0_pe_0_to_super_sink__dout),
    .fifo_ld_0_s_empty_n(from_t0_pe_0_to_super_sink__empty_n),
    .fifo_ld_0_peek_empty_n(from_t0_pe_0_to_super_sink__empty_n),
    .fifo_ld_0_s_read(from_t0_pe_0_to_super_sink__read),
    .fifo_ld_0_peek_read(),
    .fifo_ld_1_s_dout(from_t0_pe_1_to_super_sink__dout),
    .fifo_ld_1_peek_dout(from_t0_pe_1_to_super_sink__dout),
    .fifo_ld_1_s_empty_n(from_t0_pe_1_to_super_sink__empty_n),
    .fifo_ld_1_peek_empty_n(from_t0_pe_1_to_super_sink__empty_n),
    .fifo_ld_1_s_read(from_t0_pe_1_to_super_sink__read),
    .fifo_ld_1_peek_read()
  );


  (* keep_hierarchy = "yes" *) Stream2Mmap
  Stream2Mmap_0
  (
    .ap_clk(ap_clk),
    .ap_rst_n(Stream2Mmap_0__ap_rst_n__q3),
    .ap_start(Stream2Mmap_0__ap_start),
    .ap_done(Stream2Mmap_0__ap_done),
    .ap_idle(Stream2Mmap_0__ap_idle),
    .ap_ready(Stream2Mmap_0__ap_ready),
    .m_axi_mmap_ARADDR(m_axi_bank_0_t0_ARADDR),
    .m_axi_mmap_ARBURST(m_axi_bank_0_t0_ARBURST),
    .m_axi_mmap_ARID(m_axi_bank_0_t0_ARID),
    .m_axi_mmap_ARLEN(m_axi_bank_0_t0_ARLEN),
    .m_axi_mmap_ARREADY(m_axi_bank_0_t0_ARREADY),
    .m_axi_mmap_ARSIZE(m_axi_bank_0_t0_ARSIZE),
    .m_axi_mmap_ARVALID(m_axi_bank_0_t0_ARVALID),
    .m_axi_mmap_AWADDR(m_axi_bank_0_t0_AWADDR),
    .m_axi_mmap_AWBURST(m_axi_bank_0_t0_AWBURST),
    .m_axi_mmap_AWID(m_axi_bank_0_t0_AWID),
    .m_axi_mmap_AWLEN(m_axi_bank_0_t0_AWLEN),
    .m_axi_mmap_AWREADY(m_axi_bank_0_t0_AWREADY),
    .m_axi_mmap_AWSIZE(m_axi_bank_0_t0_AWSIZE),
    .m_axi_mmap_AWVALID(m_axi_bank_0_t0_AWVALID),
    .m_axi_mmap_BID(m_axi_bank_0_t0_BID),
    .m_axi_mmap_BREADY(m_axi_bank_0_t0_BREADY),
    .m_axi_mmap_BRESP(m_axi_bank_0_t0_BRESP),
    .m_axi_mmap_BVALID(m_axi_bank_0_t0_BVALID),
    .m_axi_mmap_RDATA(m_axi_bank_0_t0_RDATA),
    .m_axi_mmap_RID(m_axi_bank_0_t0_RID),
    .m_axi_mmap_RLAST(m_axi_bank_0_t0_RLAST),
    .m_axi_mmap_RREADY(m_axi_bank_0_t0_RREADY),
    .m_axi_mmap_RRESP(m_axi_bank_0_t0_RRESP),
    .m_axi_mmap_RVALID(m_axi_bank_0_t0_RVALID),
    .m_axi_mmap_WDATA(m_axi_bank_0_t0_WDATA),
    .m_axi_mmap_WLAST(m_axi_bank_0_t0_WLAST),
    .m_axi_mmap_WREADY(m_axi_bank_0_t0_WREADY),
    .m_axi_mmap_WSTRB(m_axi_bank_0_t0_WSTRB),
    .m_axi_mmap_WVALID(m_axi_bank_0_t0_WVALID),
    .m_axi_mmap_ARLOCK(m_axi_bank_0_t0_ARLOCK),
    .m_axi_mmap_ARPROT(m_axi_bank_0_t0_ARPROT),
    .m_axi_mmap_ARQOS(m_axi_bank_0_t0_ARQOS),
    .m_axi_mmap_ARCACHE(m_axi_bank_0_t0_ARCACHE),
    .m_axi_mmap_AWCACHE(m_axi_bank_0_t0_AWCACHE),
    .m_axi_mmap_AWLOCK(m_axi_bank_0_t0_AWLOCK),
    .m_axi_mmap_AWPROT(m_axi_bank_0_t0_AWPROT),
    .m_axi_mmap_AWQOS(m_axi_bank_0_t0_AWQOS),
    .mmap_offset(Stream2Mmap_0___bank_0_t0__q2),
    .stream_s_dout(bank_0_t0_buf__dout),
    .stream_peek_dout(bank_0_t0_buf__dout),
    .stream_s_empty_n(bank_0_t0_buf__empty_n),
    .stream_peek_empty_n(bank_0_t0_buf__empty_n),
    .stream_s_read(bank_0_t0_buf__read),
    .stream_peek_read()
  );

  assign ap_rst_n__q0 = ap_rst_n;
  assign ap_rst_n_inv = (~ap_rst_n__q3);

  always @(posedge ap_clk) begin
    bank_0_t0_buf__rst__q1 <= bank_0_t0_buf__rst__q0;
    bank_0_t0_buf__rst__q2 <= bank_0_t0_buf__rst__q1;
    bank_0_t0_buf__rst__q3 <= bank_0_t0_buf__rst__q2;
  end

  assign bank_0_t0_buf__rst__q0 = (~ap_rst_n);

  always @(posedge ap_clk) begin
    if(bank_0_t0_buf__read == 1'b1) begin
      $display("info: R: \033[97m                              bank_0_t0_buf\033[0m -> \033[90mStream2Mmap_0                              \033[0m %h", bank_0_t0_buf__dout);
    end 
  end


  always @(posedge ap_clk) begin
    if(bank_0_t0_buf__write == 1'b1) begin
      $display("info: W: \033[90m                              Module8Func_0\033[0m -> \033[97mbank_0_t0_buf                              \033[0m %h", bank_0_t0_buf__din);
    end 
  end


  always @(posedge ap_clk) begin
    bank_0_t1_buf__rst__q1 <= bank_0_t1_buf__rst__q0;
    bank_0_t1_buf__rst__q2 <= bank_0_t1_buf__rst__q1;
    bank_0_t1_buf__rst__q3 <= bank_0_t1_buf__rst__q2;
  end

  assign bank_0_t1_buf__rst__q0 = (~ap_rst_n);

  always @(posedge ap_clk) begin
    if(bank_0_t1_buf__read == 1'b1) begin
      $display("info: R: \033[97m                              bank_0_t1_buf\033[0m -> \033[90mModule0Func_0                              \033[0m %h", bank_0_t1_buf__dout);
    end 
  end


  always @(posedge ap_clk) begin
    if(bank_0_t1_buf__write == 1'b1) begin
      $display("info: W: \033[90m                              Mmap2Stream_0\033[0m -> \033[97mbank_0_t1_buf                              \033[0m %h", bank_0_t1_buf__din);
    end 
  end


  always @(posedge ap_clk) begin
    from_super_source_to_t1_offset_0__rst__q1 <= from_super_source_to_t1_offset_0__rst__q0;
    from_super_source_to_t1_offset_0__rst__q2 <= from_super_source_to_t1_offset_0__rst__q1;
    from_super_source_to_t1_offset_0__rst__q3 <= from_super_source_to_t1_offset_0__rst__q2;
  end

  assign from_super_source_to_t1_offset_0__rst__q0 = (~ap_rst_n);

  always @(posedge ap_clk) begin
    if(from_super_source_to_t1_offset_0__read == 1'b1) begin
      $display("info: R: \033[97m           from_super_source_to_t1_offset_0\033[0m -> \033[90mModule1Func_0                              \033[0m %h", from_super_source_to_t1_offset_0__dout);
    end 
  end


  always @(posedge ap_clk) begin
    if(from_super_source_to_t1_offset_0__write == 1'b1) begin
      $display("info: W: \033[90m                              Module0Func_0\033[0m -> \033[97mfrom_super_source_to_t1_offset_0           \033[0m %h", from_super_source_to_t1_offset_0__din);
    end 
  end


  always @(posedge ap_clk) begin
    from_super_source_to_t1_offset_1__rst__q1 <= from_super_source_to_t1_offset_1__rst__q0;
    from_super_source_to_t1_offset_1__rst__q2 <= from_super_source_to_t1_offset_1__rst__q1;
    from_super_source_to_t1_offset_1__rst__q3 <= from_super_source_to_t1_offset_1__rst__q2;
  end

  assign from_super_source_to_t1_offset_1__rst__q0 = (~ap_rst_n);

  always @(posedge ap_clk) begin
    if(from_super_source_to_t1_offset_1__read == 1'b1) begin
      $display("info: R: \033[97m           from_super_source_to_t1_offset_1\033[0m -> \033[90mModule1Func_1                              \033[0m %h", from_super_source_to_t1_offset_1__dout);
    end 
  end


  always @(posedge ap_clk) begin
    if(from_super_source_to_t1_offset_1__write == 1'b1) begin
      $display("info: W: \033[90m                              Module0Func_0\033[0m -> \033[97mfrom_super_source_to_t1_offset_1           \033[0m %h", from_super_source_to_t1_offset_1__din);
    end 
  end


  always @(posedge ap_clk) begin
    from_t0_pe_0_to_super_sink__rst__q1 <= from_t0_pe_0_to_super_sink__rst__q0;
    from_t0_pe_0_to_super_sink__rst__q2 <= from_t0_pe_0_to_super_sink__rst__q1;
    from_t0_pe_0_to_super_sink__rst__q3 <= from_t0_pe_0_to_super_sink__rst__q2;
  end

  assign from_t0_pe_0_to_super_sink__rst__q0 = (~ap_rst_n);

  always @(posedge ap_clk) begin
    if(from_t0_pe_0_to_super_sink__read == 1'b1) begin
      $display("info: R: \033[97m                 from_t0_pe_0_to_super_sink\033[0m -> \033[90mModule8Func_0                              \033[0m %h", from_t0_pe_0_to_super_sink__dout);
    end 
  end


  always @(posedge ap_clk) begin
    if(from_t0_pe_0_to_super_sink__write == 1'b1) begin
      $display("info: W: \033[90m                             Module6Func1_0\033[0m -> \033[97mfrom_t0_pe_0_to_super_sink                 \033[0m %h", from_t0_pe_0_to_super_sink__din);
    end 
  end


  always @(posedge ap_clk) begin
    from_t0_pe_1_to_super_sink__rst__q1 <= from_t0_pe_1_to_super_sink__rst__q0;
    from_t0_pe_1_to_super_sink__rst__q2 <= from_t0_pe_1_to_super_sink__rst__q1;
    from_t0_pe_1_to_super_sink__rst__q3 <= from_t0_pe_1_to_super_sink__rst__q2;
  end

  assign from_t0_pe_1_to_super_sink__rst__q0 = (~ap_rst_n);

  always @(posedge ap_clk) begin
    if(from_t0_pe_1_to_super_sink__read == 1'b1) begin
      $display("info: R: \033[97m                 from_t0_pe_1_to_super_sink\033[0m -> \033[90mModule8Func_0                              \033[0m %h", from_t0_pe_1_to_super_sink__dout);
    end 
  end


  always @(posedge ap_clk) begin
    if(from_t0_pe_1_to_super_sink__write == 1'b1) begin
      $display("info: W: \033[90m                             Module6Func2_0\033[0m -> \033[97mfrom_t0_pe_1_to_super_sink                 \033[0m %h", from_t0_pe_1_to_super_sink__din);
    end 
  end


  always @(posedge ap_clk) begin
    from_t1_offset_0_to_t1_offset_2000__rst__q1 <= from_t1_offset_0_to_t1_offset_2000__rst__q0;
    from_t1_offset_0_to_t1_offset_2000__rst__q2 <= from_t1_offset_0_to_t1_offset_2000__rst__q1;
    from_t1_offset_0_to_t1_offset_2000__rst__q3 <= from_t1_offset_0_to_t1_offset_2000__rst__q2;
  end

  assign from_t1_offset_0_to_t1_offset_2000__rst__q0 = (~ap_rst_n);

  always @(posedge ap_clk) begin
    if(from_t1_offset_0_to_t1_offset_2000__read == 1'b1) begin
      $display("info: R: \033[97m         from_t1_offset_0_to_t1_offset_2000\033[0m -> \033[90mModule1Func_2                              \033[0m %h", from_t1_offset_0_to_t1_offset_2000__dout);
    end 
  end


  always @(posedge ap_clk) begin
    if(from_t1_offset_0_to_t1_offset_2000__write == 1'b1) begin
      $display("info: W: \033[90m                              Module1Func_0\033[0m -> \033[97mfrom_t1_offset_0_to_t1_offset_2000         \033[0m %h", from_t1_offset_0_to_t1_offset_2000__din);
    end 
  end


  always @(posedge ap_clk) begin
    from_t1_offset_0_to_tcse_var_0_pe_1__rst__q1 <= from_t1_offset_0_to_tcse_var_0_pe_1__rst__q0;
    from_t1_offset_0_to_tcse_var_0_pe_1__rst__q2 <= from_t1_offset_0_to_tcse_var_0_pe_1__rst__q1;
    from_t1_offset_0_to_tcse_var_0_pe_1__rst__q3 <= from_t1_offset_0_to_tcse_var_0_pe_1__rst__q2;
  end

  assign from_t1_offset_0_to_tcse_var_0_pe_1__rst__q0 = (~ap_rst_n);

  always @(posedge ap_clk) begin
    if(from_t1_offset_0_to_tcse_var_0_pe_1__read == 1'b1) begin
      $display("info: R: \033[97m        from_t1_offset_0_to_tcse_var_0_pe_1\033[0m -> \033[90mModule3Func1_0                             \033[0m %h", from_t1_offset_0_to_tcse_var_0_pe_1__dout);
    end 
  end


  always @(posedge ap_clk) begin
    if(from_t1_offset_0_to_tcse_var_0_pe_1__write == 1'b1) begin
      $display("info: W: \033[90m                              Module1Func_0\033[0m -> \033[97mfrom_t1_offset_0_to_tcse_var_0_pe_1        \033[0m %h", from_t1_offset_0_to_tcse_var_0_pe_1__din);
    end 
  end


  always @(posedge ap_clk) begin
    from_t1_offset_1_to_t1_offset_2001__rst__q1 <= from_t1_offset_1_to_t1_offset_2001__rst__q0;
    from_t1_offset_1_to_t1_offset_2001__rst__q2 <= from_t1_offset_1_to_t1_offset_2001__rst__q1;
    from_t1_offset_1_to_t1_offset_2001__rst__q3 <= from_t1_offset_1_to_t1_offset_2001__rst__q2;
  end

  assign from_t1_offset_1_to_t1_offset_2001__rst__q0 = (~ap_rst_n);

  always @(posedge ap_clk) begin
    if(from_t1_offset_1_to_t1_offset_2001__read == 1'b1) begin
      $display("info: R: \033[97m         from_t1_offset_1_to_t1_offset_2001\033[0m -> \033[90mModule1Func_3                              \033[0m %h", from_t1_offset_1_to_t1_offset_2001__dout);
    end 
  end


  always @(posedge ap_clk) begin
    if(from_t1_offset_1_to_t1_offset_2001__write == 1'b1) begin
      $display("info: W: \033[90m                              Module1Func_1\033[0m -> \033[97mfrom_t1_offset_1_to_t1_offset_2001         \033[0m %h", from_t1_offset_1_to_t1_offset_2001__din);
    end 
  end


  always @(posedge ap_clk) begin
    from_t1_offset_1_to_tcse_var_0_pe_0__rst__q1 <= from_t1_offset_1_to_tcse_var_0_pe_0__rst__q0;
    from_t1_offset_1_to_tcse_var_0_pe_0__rst__q2 <= from_t1_offset_1_to_tcse_var_0_pe_0__rst__q1;
    from_t1_offset_1_to_tcse_var_0_pe_0__rst__q3 <= from_t1_offset_1_to_tcse_var_0_pe_0__rst__q2;
  end

  assign from_t1_offset_1_to_tcse_var_0_pe_0__rst__q0 = (~ap_rst_n);

  always @(posedge ap_clk) begin
    if(from_t1_offset_1_to_tcse_var_0_pe_0__read == 1'b1) begin
      $display("info: R: \033[97m        from_t1_offset_1_to_tcse_var_0_pe_0\033[0m -> \033[90mModule3Func2_0                             \033[0m %h", from_t1_offset_1_to_tcse_var_0_pe_0__dout);
    end 
  end


  always @(posedge ap_clk) begin
    if(from_t1_offset_1_to_tcse_var_0_pe_0__write == 1'b1) begin
      $display("info: W: \033[90m                              Module1Func_1\033[0m -> \033[97mfrom_t1_offset_1_to_tcse_var_0_pe_0        \033[0m %h", from_t1_offset_1_to_tcse_var_0_pe_0__din);
    end 
  end


  always @(posedge ap_clk) begin
    from_t1_offset_2000_to_t0_pe_1__rst__q1 <= from_t1_offset_2000_to_t0_pe_1__rst__q0;
    from_t1_offset_2000_to_t0_pe_1__rst__q2 <= from_t1_offset_2000_to_t0_pe_1__rst__q1;
    from_t1_offset_2000_to_t0_pe_1__rst__q3 <= from_t1_offset_2000_to_t0_pe_1__rst__q2;
  end

  assign from_t1_offset_2000_to_t0_pe_1__rst__q0 = (~ap_rst_n);

  always @(posedge ap_clk) begin
    if(from_t1_offset_2000_to_t0_pe_1__read == 1'b1) begin
      $display("info: R: \033[97m             from_t1_offset_2000_to_t0_pe_1\033[0m -> \033[90mModule6Func2_0                             \033[0m %h", from_t1_offset_2000_to_t0_pe_1__dout);
    end 
  end


  always @(posedge ap_clk) begin
    if(from_t1_offset_2000_to_t0_pe_1__write == 1'b1) begin
      $display("info: W: \033[90m                              Module1Func_2\033[0m -> \033[97mfrom_t1_offset_2000_to_t0_pe_1             \033[0m %h", from_t1_offset_2000_to_t0_pe_1__din);
    end 
  end


  always @(posedge ap_clk) begin
    from_t1_offset_2000_to_tcse_var_0_pe_0__rst__q1 <= from_t1_offset_2000_to_tcse_var_0_pe_0__rst__q0;
    from_t1_offset_2000_to_tcse_var_0_pe_0__rst__q2 <= from_t1_offset_2000_to_tcse_var_0_pe_0__rst__q1;
    from_t1_offset_2000_to_tcse_var_0_pe_0__rst__q3 <= from_t1_offset_2000_to_tcse_var_0_pe_0__rst__q2;
  end

  assign from_t1_offset_2000_to_tcse_var_0_pe_0__rst__q0 = (~ap_rst_n);

  always @(posedge ap_clk) begin
    if(from_t1_offset_2000_to_tcse_var_0_pe_0__read == 1'b1) begin
      $display("info: R: \033[97m     from_t1_offset_2000_to_tcse_var_0_pe_0\033[0m -> \033[90mModule3Func2_0                             \033[0m %h", from_t1_offset_2000_to_tcse_var_0_pe_0__dout);
    end 
  end


  always @(posedge ap_clk) begin
    if(from_t1_offset_2000_to_tcse_var_0_pe_0__write == 1'b1) begin
      $display("info: W: \033[90m                              Module1Func_2\033[0m -> \033[97mfrom_t1_offset_2000_to_tcse_var_0_pe_0     \033[0m %h", from_t1_offset_2000_to_tcse_var_0_pe_0__din);
    end 
  end


  always @(posedge ap_clk) begin
    from_t1_offset_2001_to_t0_pe_0__rst__q1 <= from_t1_offset_2001_to_t0_pe_0__rst__q0;
    from_t1_offset_2001_to_t0_pe_0__rst__q2 <= from_t1_offset_2001_to_t0_pe_0__rst__q1;
    from_t1_offset_2001_to_t0_pe_0__rst__q3 <= from_t1_offset_2001_to_t0_pe_0__rst__q2;
  end

  assign from_t1_offset_2001_to_t0_pe_0__rst__q0 = (~ap_rst_n);

  always @(posedge ap_clk) begin
    if(from_t1_offset_2001_to_t0_pe_0__read == 1'b1) begin
      $display("info: R: \033[97m             from_t1_offset_2001_to_t0_pe_0\033[0m -> \033[90mModule6Func1_0                             \033[0m %h", from_t1_offset_2001_to_t0_pe_0__dout);
    end 
  end


  always @(posedge ap_clk) begin
    if(from_t1_offset_2001_to_t0_pe_0__write == 1'b1) begin
      $display("info: W: \033[90m                              Module1Func_3\033[0m -> \033[97mfrom_t1_offset_2001_to_t0_pe_0             \033[0m %h", from_t1_offset_2001_to_t0_pe_0__din);
    end 
  end


  always @(posedge ap_clk) begin
    from_t1_offset_2001_to_tcse_var_0_pe_1__rst__q1 <= from_t1_offset_2001_to_tcse_var_0_pe_1__rst__q0;
    from_t1_offset_2001_to_tcse_var_0_pe_1__rst__q2 <= from_t1_offset_2001_to_tcse_var_0_pe_1__rst__q1;
    from_t1_offset_2001_to_tcse_var_0_pe_1__rst__q3 <= from_t1_offset_2001_to_tcse_var_0_pe_1__rst__q2;
  end

  assign from_t1_offset_2001_to_tcse_var_0_pe_1__rst__q0 = (~ap_rst_n);

  always @(posedge ap_clk) begin
    if(from_t1_offset_2001_to_tcse_var_0_pe_1__read == 1'b1) begin
      $display("info: R: \033[97m     from_t1_offset_2001_to_tcse_var_0_pe_1\033[0m -> \033[90mModule3Func1_0                             \033[0m %h", from_t1_offset_2001_to_tcse_var_0_pe_1__dout);
    end 
  end


  always @(posedge ap_clk) begin
    if(from_t1_offset_2001_to_tcse_var_0_pe_1__write == 1'b1) begin
      $display("info: W: \033[90m                              Module1Func_3\033[0m -> \033[97mfrom_t1_offset_2001_to_tcse_var_0_pe_1     \033[0m %h", from_t1_offset_2001_to_tcse_var_0_pe_1__din);
    end 
  end


  always @(posedge ap_clk) begin
    from_tcse_var_0_offset_0_to_t0_pe_0__rst__q1 <= from_tcse_var_0_offset_0_to_t0_pe_0__rst__q0;
    from_tcse_var_0_offset_0_to_t0_pe_0__rst__q2 <= from_tcse_var_0_offset_0_to_t0_pe_0__rst__q1;
    from_tcse_var_0_offset_0_to_t0_pe_0__rst__q3 <= from_tcse_var_0_offset_0_to_t0_pe_0__rst__q2;
  end

  assign from_tcse_var_0_offset_0_to_t0_pe_0__rst__q0 = (~ap_rst_n);

  always @(posedge ap_clk) begin
    if(from_tcse_var_0_offset_0_to_t0_pe_0__read == 1'b1) begin
      $display("info: R: \033[97m        from_tcse_var_0_offset_0_to_t0_pe_0\033[0m -> \033[90mModule6Func1_0                             \033[0m %h", from_tcse_var_0_offset_0_to_t0_pe_0__dout);
    end 
  end


  always @(posedge ap_clk) begin
    if(from_tcse_var_0_offset_0_to_t0_pe_0__write == 1'b1) begin
      $display("info: W: \033[90m                              Module1Func_4\033[0m -> \033[97mfrom_tcse_var_0_offset_0_to_t0_pe_0        \033[0m %h", from_tcse_var_0_offset_0_to_t0_pe_0__din);
    end 
  end


  always @(posedge ap_clk) begin
    from_tcse_var_0_offset_0_to_t0_pe_1__rst__q1 <= from_tcse_var_0_offset_0_to_t0_pe_1__rst__q0;
    from_tcse_var_0_offset_0_to_t0_pe_1__rst__q2 <= from_tcse_var_0_offset_0_to_t0_pe_1__rst__q1;
    from_tcse_var_0_offset_0_to_t0_pe_1__rst__q3 <= from_tcse_var_0_offset_0_to_t0_pe_1__rst__q2;
  end

  assign from_tcse_var_0_offset_0_to_t0_pe_1__rst__q0 = (~ap_rst_n);

  always @(posedge ap_clk) begin
    if(from_tcse_var_0_offset_0_to_t0_pe_1__read == 1'b1) begin
      $display("info: R: \033[97m        from_tcse_var_0_offset_0_to_t0_pe_1\033[0m -> \033[90mModule6Func2_0                             \033[0m %h", from_tcse_var_0_offset_0_to_t0_pe_1__dout);
    end 
  end


  always @(posedge ap_clk) begin
    if(from_tcse_var_0_offset_0_to_t0_pe_1__write == 1'b1) begin
      $display("info: W: \033[90m                              Module1Func_4\033[0m -> \033[97mfrom_tcse_var_0_offset_0_to_t0_pe_1        \033[0m %h", from_tcse_var_0_offset_0_to_t0_pe_1__din);
    end 
  end


  always @(posedge ap_clk) begin
    from_tcse_var_0_offset_1_to_t0_pe_0__rst__q1 <= from_tcse_var_0_offset_1_to_t0_pe_0__rst__q0;
    from_tcse_var_0_offset_1_to_t0_pe_0__rst__q2 <= from_tcse_var_0_offset_1_to_t0_pe_0__rst__q1;
    from_tcse_var_0_offset_1_to_t0_pe_0__rst__q3 <= from_tcse_var_0_offset_1_to_t0_pe_0__rst__q2;
  end

  assign from_tcse_var_0_offset_1_to_t0_pe_0__rst__q0 = (~ap_rst_n);

  always @(posedge ap_clk) begin
    if(from_tcse_var_0_offset_1_to_t0_pe_0__read == 1'b1) begin
      $display("info: R: \033[97m        from_tcse_var_0_offset_1_to_t0_pe_0\033[0m -> \033[90mModule6Func1_0                             \033[0m %h", from_tcse_var_0_offset_1_to_t0_pe_0__dout);
    end 
  end


  always @(posedge ap_clk) begin
    if(from_tcse_var_0_offset_1_to_t0_pe_0__write == 1'b1) begin
      $display("info: W: \033[90m                              Module1Func_5\033[0m -> \033[97mfrom_tcse_var_0_offset_1_to_t0_pe_0        \033[0m %h", from_tcse_var_0_offset_1_to_t0_pe_0__din);
    end 
  end


  always @(posedge ap_clk) begin
    from_tcse_var_0_offset_1_to_t0_pe_1__rst__q1 <= from_tcse_var_0_offset_1_to_t0_pe_1__rst__q0;
    from_tcse_var_0_offset_1_to_t0_pe_1__rst__q2 <= from_tcse_var_0_offset_1_to_t0_pe_1__rst__q1;
    from_tcse_var_0_offset_1_to_t0_pe_1__rst__q3 <= from_tcse_var_0_offset_1_to_t0_pe_1__rst__q2;
  end

  assign from_tcse_var_0_offset_1_to_t0_pe_1__rst__q0 = (~ap_rst_n);

  always @(posedge ap_clk) begin
    if(from_tcse_var_0_offset_1_to_t0_pe_1__read == 1'b1) begin
      $display("info: R: \033[97m        from_tcse_var_0_offset_1_to_t0_pe_1\033[0m -> \033[90mModule6Func2_0                             \033[0m %h", from_tcse_var_0_offset_1_to_t0_pe_1__dout);
    end 
  end


  always @(posedge ap_clk) begin
    if(from_tcse_var_0_offset_1_to_t0_pe_1__write == 1'b1) begin
      $display("info: W: \033[90m                              Module1Func_5\033[0m -> \033[97mfrom_tcse_var_0_offset_1_to_t0_pe_1        \033[0m %h", from_tcse_var_0_offset_1_to_t0_pe_1__din);
    end 
  end


  always @(posedge ap_clk) begin
    from_tcse_var_0_pe_0_to_tcse_var_0_offset_1__rst__q1 <= from_tcse_var_0_pe_0_to_tcse_var_0_offset_1__rst__q0;
    from_tcse_var_0_pe_0_to_tcse_var_0_offset_1__rst__q2 <= from_tcse_var_0_pe_0_to_tcse_var_0_offset_1__rst__q1;
    from_tcse_var_0_pe_0_to_tcse_var_0_offset_1__rst__q3 <= from_tcse_var_0_pe_0_to_tcse_var_0_offset_1__rst__q2;
  end

  assign from_tcse_var_0_pe_0_to_tcse_var_0_offset_1__rst__q0 = (~ap_rst_n);

  always @(posedge ap_clk) begin
    if(from_tcse_var_0_pe_0_to_tcse_var_0_offset_1__read == 1'b1) begin
      $display("info: R: \033[97mfrom_tcse_var_0_pe_0_to_tcse_var_0_offset_1\033[0m -> \033[90mModule1Func_5                              \033[0m %h", from_tcse_var_0_pe_0_to_tcse_var_0_offset_1__dout);
    end 
  end


  always @(posedge ap_clk) begin
    if(from_tcse_var_0_pe_0_to_tcse_var_0_offset_1__write == 1'b1) begin
      $display("info: W: \033[90m                             Module3Func2_0\033[0m -> \033[97mfrom_tcse_var_0_pe_0_to_tcse_var_0_offset_1\033[0m %h", from_tcse_var_0_pe_0_to_tcse_var_0_offset_1__din);
    end 
  end


  always @(posedge ap_clk) begin
    from_tcse_var_0_pe_1_to_tcse_var_0_offset_0__rst__q1 <= from_tcse_var_0_pe_1_to_tcse_var_0_offset_0__rst__q0;
    from_tcse_var_0_pe_1_to_tcse_var_0_offset_0__rst__q2 <= from_tcse_var_0_pe_1_to_tcse_var_0_offset_0__rst__q1;
    from_tcse_var_0_pe_1_to_tcse_var_0_offset_0__rst__q3 <= from_tcse_var_0_pe_1_to_tcse_var_0_offset_0__rst__q2;
  end

  assign from_tcse_var_0_pe_1_to_tcse_var_0_offset_0__rst__q0 = (~ap_rst_n);

  always @(posedge ap_clk) begin
    if(from_tcse_var_0_pe_1_to_tcse_var_0_offset_0__read == 1'b1) begin
      $display("info: R: \033[97mfrom_tcse_var_0_pe_1_to_tcse_var_0_offset_0\033[0m -> \033[90mModule1Func_4                              \033[0m %h", from_tcse_var_0_pe_1_to_tcse_var_0_offset_0__dout);
    end 
  end


  always @(posedge ap_clk) begin
    if(from_tcse_var_0_pe_1_to_tcse_var_0_offset_0__write == 1'b1) begin
      $display("info: W: \033[90m                             Module3Func1_0\033[0m -> \033[97mfrom_tcse_var_0_pe_1_to_tcse_var_0_offset_0\033[0m %h", from_tcse_var_0_pe_1_to_tcse_var_0_offset_0__din);
    end 
  end


  always @(posedge ap_clk) begin
    Mmap2Stream_0___bank_0_t1__q1 <= Mmap2Stream_0___bank_0_t1__q0;
    Mmap2Stream_0___bank_0_t1__q2 <= Mmap2Stream_0___bank_0_t1__q1;
  end

  assign Mmap2Stream_0___bank_0_t1__q0 = bank_0_t1_slr_0;

  always @(posedge ap_clk) begin
    Mmap2Stream_0___coalesced_data_num__q1 <= Mmap2Stream_0___coalesced_data_num__q0;
    Mmap2Stream_0___coalesced_data_num__q2 <= Mmap2Stream_0___coalesced_data_num__q1;
  end

  assign Mmap2Stream_0___coalesced_data_num__q0 = coalesced_data_num_slr_0;

  always @(posedge ap_clk) begin
    Mmap2Stream_0__ap_rst_n__q1 <= Mmap2Stream_0__ap_rst_n__q0;
    Mmap2Stream_0__ap_rst_n__q2 <= Mmap2Stream_0__ap_rst_n__q1;
    Mmap2Stream_0__ap_rst_n__q3 <= Mmap2Stream_0__ap_rst_n__q2;
  end

  assign Mmap2Stream_0__ap_rst_n__q0 = ap_rst_n;

  always @(posedge ap_clk) begin
    Mmap2Stream_0__ap_start_global__q1 <= Mmap2Stream_0__ap_start_global__q0;
    Mmap2Stream_0__ap_start_global__q2 <= Mmap2Stream_0__ap_start_global__q1;
    Mmap2Stream_0__ap_start_global__q3 <= Mmap2Stream_0__ap_start_global__q2;
  end

  assign Mmap2Stream_0__ap_start_global__q0 = ap_start__q0;

  always @(posedge ap_clk) begin
    Mmap2Stream_0__is_done__q1 <= Mmap2Stream_0__is_done__q0;
    Mmap2Stream_0__is_done__q2 <= Mmap2Stream_0__is_done__q1;
    Mmap2Stream_0__is_done__q3 <= Mmap2Stream_0__is_done__q2;
  end

  assign Mmap2Stream_0__is_done__q0 = (Mmap2Stream_0__state == 2'b10);

  always @(posedge ap_clk) begin
    Mmap2Stream_0__ap_done_global__q1 <= Mmap2Stream_0__ap_done_global__q0;
    Mmap2Stream_0__ap_done_global__q2 <= Mmap2Stream_0__ap_done_global__q1;
    Mmap2Stream_0__ap_done_global__q3 <= Mmap2Stream_0__ap_done_global__q2;
  end

  assign Mmap2Stream_0__ap_done_global__q0 = ap_done__q0;

  always @(posedge ap_clk) begin
    if(~Mmap2Stream_0__ap_rst_n__q3) begin
      Mmap2Stream_0__state <= 2'b00;
    end else begin
      if(Mmap2Stream_0__state == 2'b00) begin
        if(Mmap2Stream_0__ap_start_global__q3) begin
          Mmap2Stream_0__state <= 2'b01;
        end 
      end 
      if(Mmap2Stream_0__state == 2'b01) begin
        if(Mmap2Stream_0__ap_ready) begin
          if(Mmap2Stream_0__ap_done) begin
            Mmap2Stream_0__state <= 2'b10;
          end else begin
            Mmap2Stream_0__state <= 2'b11;
          end
        end 
      end 
      if(Mmap2Stream_0__state == 2'b11) begin
        if(Mmap2Stream_0__ap_done) begin
          Mmap2Stream_0__state <= 2'b10;
        end 
      end 
      if(Mmap2Stream_0__state == 2'b10) begin
        if(Mmap2Stream_0__ap_done_global__q3) begin
          Mmap2Stream_0__state <= 2'b00;
        end 
      end 
    end
  end

  assign Mmap2Stream_0__ap_start = (Mmap2Stream_0__state == 2'b01);

  always @(posedge ap_clk) begin
    Module0Func_0__ap_rst_n__q1 <= Module0Func_0__ap_rst_n__q0;
    Module0Func_0__ap_rst_n__q2 <= Module0Func_0__ap_rst_n__q1;
    Module0Func_0__ap_rst_n__q3 <= Module0Func_0__ap_rst_n__q2;
  end

  assign Module0Func_0__ap_rst_n__q0 = ap_rst_n;

  always @(posedge ap_clk) begin
    Module0Func_0__ap_start_global__q1 <= Module0Func_0__ap_start_global__q0;
    Module0Func_0__ap_start_global__q2 <= Module0Func_0__ap_start_global__q1;
    Module0Func_0__ap_start_global__q3 <= Module0Func_0__ap_start_global__q2;
  end

  assign Module0Func_0__ap_start_global__q0 = ap_start__q0;

  always @(posedge ap_clk) begin
    Module0Func_0__is_done__q1 <= Module0Func_0__is_done__q0;
    Module0Func_0__is_done__q2 <= Module0Func_0__is_done__q1;
    Module0Func_0__is_done__q3 <= Module0Func_0__is_done__q2;
  end

  assign Module0Func_0__is_done__q0 = (Module0Func_0__state == 2'b10);

  always @(posedge ap_clk) begin
    Module0Func_0__ap_done_global__q1 <= Module0Func_0__ap_done_global__q0;
    Module0Func_0__ap_done_global__q2 <= Module0Func_0__ap_done_global__q1;
    Module0Func_0__ap_done_global__q3 <= Module0Func_0__ap_done_global__q2;
  end

  assign Module0Func_0__ap_done_global__q0 = ap_done__q0;

  always @(posedge ap_clk) begin
    if(~Module0Func_0__ap_rst_n__q3) begin
      Module0Func_0__state <= 2'b00;
    end else begin
      if(Module0Func_0__state == 2'b00) begin
        if(Module0Func_0__ap_start_global__q3) begin
          Module0Func_0__state <= 2'b01;
        end 
      end 
      if(Module0Func_0__state == 2'b01) begin
        if(Module0Func_0__ap_ready) begin
          if(Module0Func_0__ap_done) begin
            Module0Func_0__state <= 2'b10;
          end else begin
            Module0Func_0__state <= 2'b11;
          end
        end 
      end 
      if(Module0Func_0__state == 2'b11) begin
        if(Module0Func_0__ap_done) begin
          Module0Func_0__state <= 2'b10;
        end 
      end 
      if(Module0Func_0__state == 2'b10) begin
        if(Module0Func_0__ap_done_global__q3) begin
          Module0Func_0__state <= 2'b00;
        end 
      end 
    end
  end

  assign Module0Func_0__ap_start = (Module0Func_0__state == 2'b01);

  always @(posedge ap_clk) begin
    Module1Func_0__ap_rst_n__q1 <= Module1Func_0__ap_rst_n__q0;
    Module1Func_0__ap_rst_n__q2 <= Module1Func_0__ap_rst_n__q1;
    Module1Func_0__ap_rst_n__q3 <= Module1Func_0__ap_rst_n__q2;
  end

  assign Module1Func_0__ap_rst_n__q0 = ap_rst_n;

  always @(posedge ap_clk) begin
    Module1Func_0__ap_start_global__q1 <= Module1Func_0__ap_start_global__q0;
    Module1Func_0__ap_start_global__q2 <= Module1Func_0__ap_start_global__q1;
    Module1Func_0__ap_start_global__q3 <= Module1Func_0__ap_start_global__q2;
  end

  assign Module1Func_0__ap_start_global__q0 = ap_start__q0;

  always @(posedge ap_clk) begin
    Module1Func_0__is_done__q1 <= Module1Func_0__is_done__q0;
    Module1Func_0__is_done__q2 <= Module1Func_0__is_done__q1;
    Module1Func_0__is_done__q3 <= Module1Func_0__is_done__q2;
  end

  assign Module1Func_0__is_done__q0 = (Module1Func_0__state == 2'b10);

  always @(posedge ap_clk) begin
    Module1Func_0__ap_done_global__q1 <= Module1Func_0__ap_done_global__q0;
    Module1Func_0__ap_done_global__q2 <= Module1Func_0__ap_done_global__q1;
    Module1Func_0__ap_done_global__q3 <= Module1Func_0__ap_done_global__q2;
  end

  assign Module1Func_0__ap_done_global__q0 = ap_done__q0;

  always @(posedge ap_clk) begin
    if(~Module1Func_0__ap_rst_n__q3) begin
      Module1Func_0__state <= 2'b00;
    end else begin
      if(Module1Func_0__state == 2'b00) begin
        if(Module1Func_0__ap_start_global__q3) begin
          Module1Func_0__state <= 2'b01;
        end 
      end 
      if(Module1Func_0__state == 2'b01) begin
        if(Module1Func_0__ap_ready) begin
          if(Module1Func_0__ap_done) begin
            Module1Func_0__state <= 2'b10;
          end else begin
            Module1Func_0__state <= 2'b11;
          end
        end 
      end 
      if(Module1Func_0__state == 2'b11) begin
        if(Module1Func_0__ap_done) begin
          Module1Func_0__state <= 2'b10;
        end 
      end 
      if(Module1Func_0__state == 2'b10) begin
        if(Module1Func_0__ap_done_global__q3) begin
          Module1Func_0__state <= 2'b00;
        end 
      end 
    end
  end

  assign Module1Func_0__ap_start = (Module1Func_0__state == 2'b01);

  always @(posedge ap_clk) begin
    Module1Func_1__ap_rst_n__q1 <= Module1Func_1__ap_rst_n__q0;
    Module1Func_1__ap_rst_n__q2 <= Module1Func_1__ap_rst_n__q1;
    Module1Func_1__ap_rst_n__q3 <= Module1Func_1__ap_rst_n__q2;
  end

  assign Module1Func_1__ap_rst_n__q0 = ap_rst_n;

  always @(posedge ap_clk) begin
    Module1Func_1__ap_start_global__q1 <= Module1Func_1__ap_start_global__q0;
    Module1Func_1__ap_start_global__q2 <= Module1Func_1__ap_start_global__q1;
    Module1Func_1__ap_start_global__q3 <= Module1Func_1__ap_start_global__q2;
  end

  assign Module1Func_1__ap_start_global__q0 = ap_start__q0;

  always @(posedge ap_clk) begin
    Module1Func_1__is_done__q1 <= Module1Func_1__is_done__q0;
    Module1Func_1__is_done__q2 <= Module1Func_1__is_done__q1;
    Module1Func_1__is_done__q3 <= Module1Func_1__is_done__q2;
  end

  assign Module1Func_1__is_done__q0 = (Module1Func_1__state == 2'b10);

  always @(posedge ap_clk) begin
    Module1Func_1__ap_done_global__q1 <= Module1Func_1__ap_done_global__q0;
    Module1Func_1__ap_done_global__q2 <= Module1Func_1__ap_done_global__q1;
    Module1Func_1__ap_done_global__q3 <= Module1Func_1__ap_done_global__q2;
  end

  assign Module1Func_1__ap_done_global__q0 = ap_done__q0;

  always @(posedge ap_clk) begin
    if(~Module1Func_1__ap_rst_n__q3) begin
      Module1Func_1__state <= 2'b00;
    end else begin
      if(Module1Func_1__state == 2'b00) begin
        if(Module1Func_1__ap_start_global__q3) begin
          Module1Func_1__state <= 2'b01;
        end 
      end 
      if(Module1Func_1__state == 2'b01) begin
        if(Module1Func_1__ap_ready) begin
          if(Module1Func_1__ap_done) begin
            Module1Func_1__state <= 2'b10;
          end else begin
            Module1Func_1__state <= 2'b11;
          end
        end 
      end 
      if(Module1Func_1__state == 2'b11) begin
        if(Module1Func_1__ap_done) begin
          Module1Func_1__state <= 2'b10;
        end 
      end 
      if(Module1Func_1__state == 2'b10) begin
        if(Module1Func_1__ap_done_global__q3) begin
          Module1Func_1__state <= 2'b00;
        end 
      end 
    end
  end

  assign Module1Func_1__ap_start = (Module1Func_1__state == 2'b01);

  always @(posedge ap_clk) begin
    Module1Func_2__ap_rst_n__q1 <= Module1Func_2__ap_rst_n__q0;
    Module1Func_2__ap_rst_n__q2 <= Module1Func_2__ap_rst_n__q1;
    Module1Func_2__ap_rst_n__q3 <= Module1Func_2__ap_rst_n__q2;
  end

  assign Module1Func_2__ap_rst_n__q0 = ap_rst_n;

  always @(posedge ap_clk) begin
    Module1Func_2__ap_start_global__q1 <= Module1Func_2__ap_start_global__q0;
    Module1Func_2__ap_start_global__q2 <= Module1Func_2__ap_start_global__q1;
    Module1Func_2__ap_start_global__q3 <= Module1Func_2__ap_start_global__q2;
  end

  assign Module1Func_2__ap_start_global__q0 = ap_start__q0;

  always @(posedge ap_clk) begin
    Module1Func_2__is_done__q1 <= Module1Func_2__is_done__q0;
    Module1Func_2__is_done__q2 <= Module1Func_2__is_done__q1;
    Module1Func_2__is_done__q3 <= Module1Func_2__is_done__q2;
  end

  assign Module1Func_2__is_done__q0 = (Module1Func_2__state == 2'b10);

  always @(posedge ap_clk) begin
    Module1Func_2__ap_done_global__q1 <= Module1Func_2__ap_done_global__q0;
    Module1Func_2__ap_done_global__q2 <= Module1Func_2__ap_done_global__q1;
    Module1Func_2__ap_done_global__q3 <= Module1Func_2__ap_done_global__q2;
  end

  assign Module1Func_2__ap_done_global__q0 = ap_done__q0;

  always @(posedge ap_clk) begin
    if(~Module1Func_2__ap_rst_n__q3) begin
      Module1Func_2__state <= 2'b00;
    end else begin
      if(Module1Func_2__state == 2'b00) begin
        if(Module1Func_2__ap_start_global__q3) begin
          Module1Func_2__state <= 2'b01;
        end 
      end 
      if(Module1Func_2__state == 2'b01) begin
        if(Module1Func_2__ap_ready) begin
          if(Module1Func_2__ap_done) begin
            Module1Func_2__state <= 2'b10;
          end else begin
            Module1Func_2__state <= 2'b11;
          end
        end 
      end 
      if(Module1Func_2__state == 2'b11) begin
        if(Module1Func_2__ap_done) begin
          Module1Func_2__state <= 2'b10;
        end 
      end 
      if(Module1Func_2__state == 2'b10) begin
        if(Module1Func_2__ap_done_global__q3) begin
          Module1Func_2__state <= 2'b00;
        end 
      end 
    end
  end

  assign Module1Func_2__ap_start = (Module1Func_2__state == 2'b01);

  always @(posedge ap_clk) begin
    Module1Func_3__ap_rst_n__q1 <= Module1Func_3__ap_rst_n__q0;
    Module1Func_3__ap_rst_n__q2 <= Module1Func_3__ap_rst_n__q1;
    Module1Func_3__ap_rst_n__q3 <= Module1Func_3__ap_rst_n__q2;
  end

  assign Module1Func_3__ap_rst_n__q0 = ap_rst_n;

  always @(posedge ap_clk) begin
    Module1Func_3__ap_start_global__q1 <= Module1Func_3__ap_start_global__q0;
    Module1Func_3__ap_start_global__q2 <= Module1Func_3__ap_start_global__q1;
    Module1Func_3__ap_start_global__q3 <= Module1Func_3__ap_start_global__q2;
  end

  assign Module1Func_3__ap_start_global__q0 = ap_start__q0;

  always @(posedge ap_clk) begin
    Module1Func_3__is_done__q1 <= Module1Func_3__is_done__q0;
    Module1Func_3__is_done__q2 <= Module1Func_3__is_done__q1;
    Module1Func_3__is_done__q3 <= Module1Func_3__is_done__q2;
  end

  assign Module1Func_3__is_done__q0 = (Module1Func_3__state == 2'b10);

  always @(posedge ap_clk) begin
    Module1Func_3__ap_done_global__q1 <= Module1Func_3__ap_done_global__q0;
    Module1Func_3__ap_done_global__q2 <= Module1Func_3__ap_done_global__q1;
    Module1Func_3__ap_done_global__q3 <= Module1Func_3__ap_done_global__q2;
  end

  assign Module1Func_3__ap_done_global__q0 = ap_done__q0;

  always @(posedge ap_clk) begin
    if(~Module1Func_3__ap_rst_n__q3) begin
      Module1Func_3__state <= 2'b00;
    end else begin
      if(Module1Func_3__state == 2'b00) begin
        if(Module1Func_3__ap_start_global__q3) begin
          Module1Func_3__state <= 2'b01;
        end 
      end 
      if(Module1Func_3__state == 2'b01) begin
        if(Module1Func_3__ap_ready) begin
          if(Module1Func_3__ap_done) begin
            Module1Func_3__state <= 2'b10;
          end else begin
            Module1Func_3__state <= 2'b11;
          end
        end 
      end 
      if(Module1Func_3__state == 2'b11) begin
        if(Module1Func_3__ap_done) begin
          Module1Func_3__state <= 2'b10;
        end 
      end 
      if(Module1Func_3__state == 2'b10) begin
        if(Module1Func_3__ap_done_global__q3) begin
          Module1Func_3__state <= 2'b00;
        end 
      end 
    end
  end

  assign Module1Func_3__ap_start = (Module1Func_3__state == 2'b01);

  always @(posedge ap_clk) begin
    Module1Func_4__ap_rst_n__q1 <= Module1Func_4__ap_rst_n__q0;
    Module1Func_4__ap_rst_n__q2 <= Module1Func_4__ap_rst_n__q1;
    Module1Func_4__ap_rst_n__q3 <= Module1Func_4__ap_rst_n__q2;
  end

  assign Module1Func_4__ap_rst_n__q0 = ap_rst_n;

  always @(posedge ap_clk) begin
    Module1Func_4__ap_start_global__q1 <= Module1Func_4__ap_start_global__q0;
    Module1Func_4__ap_start_global__q2 <= Module1Func_4__ap_start_global__q1;
    Module1Func_4__ap_start_global__q3 <= Module1Func_4__ap_start_global__q2;
  end

  assign Module1Func_4__ap_start_global__q0 = ap_start__q0;

  always @(posedge ap_clk) begin
    Module1Func_4__is_done__q1 <= Module1Func_4__is_done__q0;
    Module1Func_4__is_done__q2 <= Module1Func_4__is_done__q1;
    Module1Func_4__is_done__q3 <= Module1Func_4__is_done__q2;
  end

  assign Module1Func_4__is_done__q0 = (Module1Func_4__state == 2'b10);

  always @(posedge ap_clk) begin
    Module1Func_4__ap_done_global__q1 <= Module1Func_4__ap_done_global__q0;
    Module1Func_4__ap_done_global__q2 <= Module1Func_4__ap_done_global__q1;
    Module1Func_4__ap_done_global__q3 <= Module1Func_4__ap_done_global__q2;
  end

  assign Module1Func_4__ap_done_global__q0 = ap_done__q0;

  always @(posedge ap_clk) begin
    if(~Module1Func_4__ap_rst_n__q3) begin
      Module1Func_4__state <= 2'b00;
    end else begin
      if(Module1Func_4__state == 2'b00) begin
        if(Module1Func_4__ap_start_global__q3) begin
          Module1Func_4__state <= 2'b01;
        end 
      end 
      if(Module1Func_4__state == 2'b01) begin
        if(Module1Func_4__ap_ready) begin
          if(Module1Func_4__ap_done) begin
            Module1Func_4__state <= 2'b10;
          end else begin
            Module1Func_4__state <= 2'b11;
          end
        end 
      end 
      if(Module1Func_4__state == 2'b11) begin
        if(Module1Func_4__ap_done) begin
          Module1Func_4__state <= 2'b10;
        end 
      end 
      if(Module1Func_4__state == 2'b10) begin
        if(Module1Func_4__ap_done_global__q3) begin
          Module1Func_4__state <= 2'b00;
        end 
      end 
    end
  end

  assign Module1Func_4__ap_start = (Module1Func_4__state == 2'b01);

  always @(posedge ap_clk) begin
    Module1Func_5__ap_rst_n__q1 <= Module1Func_5__ap_rst_n__q0;
    Module1Func_5__ap_rst_n__q2 <= Module1Func_5__ap_rst_n__q1;
    Module1Func_5__ap_rst_n__q3 <= Module1Func_5__ap_rst_n__q2;
  end

  assign Module1Func_5__ap_rst_n__q0 = ap_rst_n;

  always @(posedge ap_clk) begin
    Module1Func_5__ap_start_global__q1 <= Module1Func_5__ap_start_global__q0;
    Module1Func_5__ap_start_global__q2 <= Module1Func_5__ap_start_global__q1;
    Module1Func_5__ap_start_global__q3 <= Module1Func_5__ap_start_global__q2;
  end

  assign Module1Func_5__ap_start_global__q0 = ap_start__q0;

  always @(posedge ap_clk) begin
    Module1Func_5__is_done__q1 <= Module1Func_5__is_done__q0;
    Module1Func_5__is_done__q2 <= Module1Func_5__is_done__q1;
    Module1Func_5__is_done__q3 <= Module1Func_5__is_done__q2;
  end

  assign Module1Func_5__is_done__q0 = (Module1Func_5__state == 2'b10);

  always @(posedge ap_clk) begin
    Module1Func_5__ap_done_global__q1 <= Module1Func_5__ap_done_global__q0;
    Module1Func_5__ap_done_global__q2 <= Module1Func_5__ap_done_global__q1;
    Module1Func_5__ap_done_global__q3 <= Module1Func_5__ap_done_global__q2;
  end

  assign Module1Func_5__ap_done_global__q0 = ap_done__q0;

  always @(posedge ap_clk) begin
    if(~Module1Func_5__ap_rst_n__q3) begin
      Module1Func_5__state <= 2'b00;
    end else begin
      if(Module1Func_5__state == 2'b00) begin
        if(Module1Func_5__ap_start_global__q3) begin
          Module1Func_5__state <= 2'b01;
        end 
      end 
      if(Module1Func_5__state == 2'b01) begin
        if(Module1Func_5__ap_ready) begin
          if(Module1Func_5__ap_done) begin
            Module1Func_5__state <= 2'b10;
          end else begin
            Module1Func_5__state <= 2'b11;
          end
        end 
      end 
      if(Module1Func_5__state == 2'b11) begin
        if(Module1Func_5__ap_done) begin
          Module1Func_5__state <= 2'b10;
        end 
      end 
      if(Module1Func_5__state == 2'b10) begin
        if(Module1Func_5__ap_done_global__q3) begin
          Module1Func_5__state <= 2'b00;
        end 
      end 
    end
  end

  assign Module1Func_5__ap_start = (Module1Func_5__state == 2'b01);

  always @(posedge ap_clk) begin
    Module3Func1_0__ap_rst_n__q1 <= Module3Func1_0__ap_rst_n__q0;
    Module3Func1_0__ap_rst_n__q2 <= Module3Func1_0__ap_rst_n__q1;
    Module3Func1_0__ap_rst_n__q3 <= Module3Func1_0__ap_rst_n__q2;
  end

  assign Module3Func1_0__ap_rst_n__q0 = ap_rst_n;

  always @(posedge ap_clk) begin
    Module3Func1_0__ap_start_global__q1 <= Module3Func1_0__ap_start_global__q0;
    Module3Func1_0__ap_start_global__q2 <= Module3Func1_0__ap_start_global__q1;
    Module3Func1_0__ap_start_global__q3 <= Module3Func1_0__ap_start_global__q2;
  end

  assign Module3Func1_0__ap_start_global__q0 = ap_start__q0;

  always @(posedge ap_clk) begin
    Module3Func1_0__is_done__q1 <= Module3Func1_0__is_done__q0;
    Module3Func1_0__is_done__q2 <= Module3Func1_0__is_done__q1;
    Module3Func1_0__is_done__q3 <= Module3Func1_0__is_done__q2;
  end

  assign Module3Func1_0__is_done__q0 = (Module3Func1_0__state == 2'b10);

  always @(posedge ap_clk) begin
    Module3Func1_0__ap_done_global__q1 <= Module3Func1_0__ap_done_global__q0;
    Module3Func1_0__ap_done_global__q2 <= Module3Func1_0__ap_done_global__q1;
    Module3Func1_0__ap_done_global__q3 <= Module3Func1_0__ap_done_global__q2;
  end

  assign Module3Func1_0__ap_done_global__q0 = ap_done__q0;

  always @(posedge ap_clk) begin
    if(~Module3Func1_0__ap_rst_n__q3) begin
      Module3Func1_0__state <= 2'b00;
    end else begin
      if(Module3Func1_0__state == 2'b00) begin
        if(Module3Func1_0__ap_start_global__q3) begin
          Module3Func1_0__state <= 2'b01;
        end 
      end 
      if(Module3Func1_0__state == 2'b01) begin
        if(Module3Func1_0__ap_ready) begin
          if(Module3Func1_0__ap_done) begin
            Module3Func1_0__state <= 2'b10;
          end else begin
            Module3Func1_0__state <= 2'b11;
          end
        end 
      end 
      if(Module3Func1_0__state == 2'b11) begin
        if(Module3Func1_0__ap_done) begin
          Module3Func1_0__state <= 2'b10;
        end 
      end 
      if(Module3Func1_0__state == 2'b10) begin
        if(Module3Func1_0__ap_done_global__q3) begin
          Module3Func1_0__state <= 2'b00;
        end 
      end 
    end
  end

  assign Module3Func1_0__ap_start = (Module3Func1_0__state == 2'b01);

  always @(posedge ap_clk) begin
    Module3Func2_0__ap_rst_n__q1 <= Module3Func2_0__ap_rst_n__q0;
    Module3Func2_0__ap_rst_n__q2 <= Module3Func2_0__ap_rst_n__q1;
    Module3Func2_0__ap_rst_n__q3 <= Module3Func2_0__ap_rst_n__q2;
  end

  assign Module3Func2_0__ap_rst_n__q0 = ap_rst_n;

  always @(posedge ap_clk) begin
    Module3Func2_0__ap_start_global__q1 <= Module3Func2_0__ap_start_global__q0;
    Module3Func2_0__ap_start_global__q2 <= Module3Func2_0__ap_start_global__q1;
    Module3Func2_0__ap_start_global__q3 <= Module3Func2_0__ap_start_global__q2;
  end

  assign Module3Func2_0__ap_start_global__q0 = ap_start__q0;

  always @(posedge ap_clk) begin
    Module3Func2_0__is_done__q1 <= Module3Func2_0__is_done__q0;
    Module3Func2_0__is_done__q2 <= Module3Func2_0__is_done__q1;
    Module3Func2_0__is_done__q3 <= Module3Func2_0__is_done__q2;
  end

  assign Module3Func2_0__is_done__q0 = (Module3Func2_0__state == 2'b10);

  always @(posedge ap_clk) begin
    Module3Func2_0__ap_done_global__q1 <= Module3Func2_0__ap_done_global__q0;
    Module3Func2_0__ap_done_global__q2 <= Module3Func2_0__ap_done_global__q1;
    Module3Func2_0__ap_done_global__q3 <= Module3Func2_0__ap_done_global__q2;
  end

  assign Module3Func2_0__ap_done_global__q0 = ap_done__q0;

  always @(posedge ap_clk) begin
    if(~Module3Func2_0__ap_rst_n__q3) begin
      Module3Func2_0__state <= 2'b00;
    end else begin
      if(Module3Func2_0__state == 2'b00) begin
        if(Module3Func2_0__ap_start_global__q3) begin
          Module3Func2_0__state <= 2'b01;
        end 
      end 
      if(Module3Func2_0__state == 2'b01) begin
        if(Module3Func2_0__ap_ready) begin
          if(Module3Func2_0__ap_done) begin
            Module3Func2_0__state <= 2'b10;
          end else begin
            Module3Func2_0__state <= 2'b11;
          end
        end 
      end 
      if(Module3Func2_0__state == 2'b11) begin
        if(Module3Func2_0__ap_done) begin
          Module3Func2_0__state <= 2'b10;
        end 
      end 
      if(Module3Func2_0__state == 2'b10) begin
        if(Module3Func2_0__ap_done_global__q3) begin
          Module3Func2_0__state <= 2'b00;
        end 
      end 
    end
  end

  assign Module3Func2_0__ap_start = (Module3Func2_0__state == 2'b01);

  always @(posedge ap_clk) begin
    Module6Func1_0__ap_rst_n__q1 <= Module6Func1_0__ap_rst_n__q0;
    Module6Func1_0__ap_rst_n__q2 <= Module6Func1_0__ap_rst_n__q1;
    Module6Func1_0__ap_rst_n__q3 <= Module6Func1_0__ap_rst_n__q2;
  end

  assign Module6Func1_0__ap_rst_n__q0 = ap_rst_n;

  always @(posedge ap_clk) begin
    Module6Func1_0__ap_start_global__q1 <= Module6Func1_0__ap_start_global__q0;
    Module6Func1_0__ap_start_global__q2 <= Module6Func1_0__ap_start_global__q1;
    Module6Func1_0__ap_start_global__q3 <= Module6Func1_0__ap_start_global__q2;
  end

  assign Module6Func1_0__ap_start_global__q0 = ap_start__q0;

  always @(posedge ap_clk) begin
    Module6Func1_0__is_done__q1 <= Module6Func1_0__is_done__q0;
    Module6Func1_0__is_done__q2 <= Module6Func1_0__is_done__q1;
    Module6Func1_0__is_done__q3 <= Module6Func1_0__is_done__q2;
  end

  assign Module6Func1_0__is_done__q0 = (Module6Func1_0__state == 2'b10);

  always @(posedge ap_clk) begin
    Module6Func1_0__ap_done_global__q1 <= Module6Func1_0__ap_done_global__q0;
    Module6Func1_0__ap_done_global__q2 <= Module6Func1_0__ap_done_global__q1;
    Module6Func1_0__ap_done_global__q3 <= Module6Func1_0__ap_done_global__q2;
  end

  assign Module6Func1_0__ap_done_global__q0 = ap_done__q0;

  always @(posedge ap_clk) begin
    if(~Module6Func1_0__ap_rst_n__q3) begin
      Module6Func1_0__state <= 2'b00;
    end else begin
      if(Module6Func1_0__state == 2'b00) begin
        if(Module6Func1_0__ap_start_global__q3) begin
          Module6Func1_0__state <= 2'b01;
        end 
      end 
      if(Module6Func1_0__state == 2'b01) begin
        if(Module6Func1_0__ap_ready) begin
          if(Module6Func1_0__ap_done) begin
            Module6Func1_0__state <= 2'b10;
          end else begin
            Module6Func1_0__state <= 2'b11;
          end
        end 
      end 
      if(Module6Func1_0__state == 2'b11) begin
        if(Module6Func1_0__ap_done) begin
          Module6Func1_0__state <= 2'b10;
        end 
      end 
      if(Module6Func1_0__state == 2'b10) begin
        if(Module6Func1_0__ap_done_global__q3) begin
          Module6Func1_0__state <= 2'b00;
        end 
      end 
    end
  end

  assign Module6Func1_0__ap_start = (Module6Func1_0__state == 2'b01);

  always @(posedge ap_clk) begin
    Module6Func2_0__ap_rst_n__q1 <= Module6Func2_0__ap_rst_n__q0;
    Module6Func2_0__ap_rst_n__q2 <= Module6Func2_0__ap_rst_n__q1;
    Module6Func2_0__ap_rst_n__q3 <= Module6Func2_0__ap_rst_n__q2;
  end

  assign Module6Func2_0__ap_rst_n__q0 = ap_rst_n;

  always @(posedge ap_clk) begin
    Module6Func2_0__ap_start_global__q1 <= Module6Func2_0__ap_start_global__q0;
    Module6Func2_0__ap_start_global__q2 <= Module6Func2_0__ap_start_global__q1;
    Module6Func2_0__ap_start_global__q3 <= Module6Func2_0__ap_start_global__q2;
  end

  assign Module6Func2_0__ap_start_global__q0 = ap_start__q0;

  always @(posedge ap_clk) begin
    Module6Func2_0__is_done__q1 <= Module6Func2_0__is_done__q0;
    Module6Func2_0__is_done__q2 <= Module6Func2_0__is_done__q1;
    Module6Func2_0__is_done__q3 <= Module6Func2_0__is_done__q2;
  end

  assign Module6Func2_0__is_done__q0 = (Module6Func2_0__state == 2'b10);

  always @(posedge ap_clk) begin
    Module6Func2_0__ap_done_global__q1 <= Module6Func2_0__ap_done_global__q0;
    Module6Func2_0__ap_done_global__q2 <= Module6Func2_0__ap_done_global__q1;
    Module6Func2_0__ap_done_global__q3 <= Module6Func2_0__ap_done_global__q2;
  end

  assign Module6Func2_0__ap_done_global__q0 = ap_done__q0;

  always @(posedge ap_clk) begin
    if(~Module6Func2_0__ap_rst_n__q3) begin
      Module6Func2_0__state <= 2'b00;
    end else begin
      if(Module6Func2_0__state == 2'b00) begin
        if(Module6Func2_0__ap_start_global__q3) begin
          Module6Func2_0__state <= 2'b01;
        end 
      end 
      if(Module6Func2_0__state == 2'b01) begin
        if(Module6Func2_0__ap_ready) begin
          if(Module6Func2_0__ap_done) begin
            Module6Func2_0__state <= 2'b10;
          end else begin
            Module6Func2_0__state <= 2'b11;
          end
        end 
      end 
      if(Module6Func2_0__state == 2'b11) begin
        if(Module6Func2_0__ap_done) begin
          Module6Func2_0__state <= 2'b10;
        end 
      end 
      if(Module6Func2_0__state == 2'b10) begin
        if(Module6Func2_0__ap_done_global__q3) begin
          Module6Func2_0__state <= 2'b00;
        end 
      end 
    end
  end

  assign Module6Func2_0__ap_start = (Module6Func2_0__state == 2'b01);

  always @(posedge ap_clk) begin
    Module8Func_0__ap_rst_n__q1 <= Module8Func_0__ap_rst_n__q0;
    Module8Func_0__ap_rst_n__q2 <= Module8Func_0__ap_rst_n__q1;
    Module8Func_0__ap_rst_n__q3 <= Module8Func_0__ap_rst_n__q2;
  end

  assign Module8Func_0__ap_rst_n__q0 = ap_rst_n;

  always @(posedge ap_clk) begin
    Module8Func_0__ap_start_global__q1 <= Module8Func_0__ap_start_global__q0;
    Module8Func_0__ap_start_global__q2 <= Module8Func_0__ap_start_global__q1;
    Module8Func_0__ap_start_global__q3 <= Module8Func_0__ap_start_global__q2;
  end

  assign Module8Func_0__ap_start_global__q0 = ap_start__q0;

  always @(posedge ap_clk) begin
    Module8Func_0__is_done__q1 <= Module8Func_0__is_done__q0;
    Module8Func_0__is_done__q2 <= Module8Func_0__is_done__q1;
    Module8Func_0__is_done__q3 <= Module8Func_0__is_done__q2;
  end

  assign Module8Func_0__is_done__q0 = (Module8Func_0__state == 2'b10);

  always @(posedge ap_clk) begin
    Module8Func_0__ap_done_global__q1 <= Module8Func_0__ap_done_global__q0;
    Module8Func_0__ap_done_global__q2 <= Module8Func_0__ap_done_global__q1;
    Module8Func_0__ap_done_global__q3 <= Module8Func_0__ap_done_global__q2;
  end

  assign Module8Func_0__ap_done_global__q0 = ap_done__q0;

  always @(posedge ap_clk) begin
    if(~Module8Func_0__ap_rst_n__q3) begin
      Module8Func_0__state <= 2'b00;
    end else begin
      if(Module8Func_0__state == 2'b00) begin
        if(Module8Func_0__ap_start_global__q3) begin
          Module8Func_0__state <= 2'b01;
        end 
      end 
      if(Module8Func_0__state == 2'b01) begin
        if(Module8Func_0__ap_ready) begin
          if(Module8Func_0__ap_done) begin
            Module8Func_0__state <= 2'b10;
          end else begin
            Module8Func_0__state <= 2'b11;
          end
        end 
      end 
      if(Module8Func_0__state == 2'b11) begin
        if(Module8Func_0__ap_done) begin
          Module8Func_0__state <= 2'b10;
        end 
      end 
      if(Module8Func_0__state == 2'b10) begin
        if(Module8Func_0__ap_done_global__q3) begin
          Module8Func_0__state <= 2'b00;
        end 
      end 
    end
  end

  assign Module8Func_0__ap_start = (Module8Func_0__state == 2'b01);

  always @(posedge ap_clk) begin
    Stream2Mmap_0___bank_0_t0__q1 <= Stream2Mmap_0___bank_0_t0__q0;
    Stream2Mmap_0___bank_0_t0__q2 <= Stream2Mmap_0___bank_0_t0__q1;
  end

  assign Stream2Mmap_0___bank_0_t0__q0 = bank_0_t0_slr_0;

  always @(posedge ap_clk) begin
    Stream2Mmap_0__ap_rst_n__q1 <= Stream2Mmap_0__ap_rst_n__q0;
    Stream2Mmap_0__ap_rst_n__q2 <= Stream2Mmap_0__ap_rst_n__q1;
    Stream2Mmap_0__ap_rst_n__q3 <= Stream2Mmap_0__ap_rst_n__q2;
  end

  assign Stream2Mmap_0__ap_rst_n__q0 = ap_rst_n;

  always @(posedge ap_clk) begin
    Stream2Mmap_0__ap_start_global__q1 <= Stream2Mmap_0__ap_start_global__q0;
    Stream2Mmap_0__ap_start_global__q2 <= Stream2Mmap_0__ap_start_global__q1;
    Stream2Mmap_0__ap_start_global__q3 <= Stream2Mmap_0__ap_start_global__q2;
  end

  assign Stream2Mmap_0__ap_start_global__q0 = ap_start__q0;

  always @(posedge ap_clk) begin
    Stream2Mmap_0__is_done__q1 <= Stream2Mmap_0__is_done__q0;
    Stream2Mmap_0__is_done__q2 <= Stream2Mmap_0__is_done__q1;
    Stream2Mmap_0__is_done__q3 <= Stream2Mmap_0__is_done__q2;
  end

  assign Stream2Mmap_0__is_done__q0 = (Stream2Mmap_0__state == 2'b10);

  always @(posedge ap_clk) begin
    Stream2Mmap_0__ap_done_global__q1 <= Stream2Mmap_0__ap_done_global__q0;
    Stream2Mmap_0__ap_done_global__q2 <= Stream2Mmap_0__ap_done_global__q1;
    Stream2Mmap_0__ap_done_global__q3 <= Stream2Mmap_0__ap_done_global__q2;
  end

  assign Stream2Mmap_0__ap_done_global__q0 = ap_done__q0;

  always @(posedge ap_clk) begin
    if(~Stream2Mmap_0__ap_rst_n__q3) begin
      Stream2Mmap_0__state <= 2'b00;
    end else begin
      if(Stream2Mmap_0__state == 2'b00) begin
        if(Stream2Mmap_0__ap_start_global__q3) begin
          Stream2Mmap_0__state <= 2'b01;
        end 
      end 
      if(Stream2Mmap_0__state == 2'b01) begin
        if(Stream2Mmap_0__ap_ready) begin
          if(Stream2Mmap_0__ap_done) begin
            Stream2Mmap_0__state <= 2'b10;
          end else begin
            Stream2Mmap_0__state <= 2'b11;
          end
        end 
      end 
      if(Stream2Mmap_0__state == 2'b11) begin
        if(Stream2Mmap_0__ap_done) begin
          Stream2Mmap_0__state <= 2'b10;
        end 
      end 
      if(Stream2Mmap_0__state == 2'b10) begin
        if(Stream2Mmap_0__ap_done_global__q3) begin
          Stream2Mmap_0__state <= 2'b00;
        end 
      end 
    end
  end

  assign Stream2Mmap_0__ap_start = (Stream2Mmap_0__state == 2'b01);

  always @(posedge ap_clk) begin
    if(ap_rst_n_inv) begin
      tapa_state <= 2'b00;
    end else begin
      case(tapa_state)
        2'b00: begin
          if(ap_start__q3) begin
            tapa_state <= 2'b01;
          end 
        end
        2'b01: begin
          if(Mmap2Stream_0__is_done__q3 && Module0Func_0__is_done__q3 && Module1Func_0__is_done__q3 && Module1Func_1__is_done__q3 && Module1Func_2__is_done__q3 && Module1Func_3__is_done__q3 && Module1Func_4__is_done__q3 && Module1Func_5__is_done__q3 && Module3Func1_0__is_done__q3 && Module3Func2_0__is_done__q3 && Module6Func1_0__is_done__q3 && Module6Func2_0__is_done__q3 && Module8Func_0__is_done__q3 && Stream2Mmap_0__is_done__q3) begin
            tapa_state <= 2'b10;
          end 
        end
        2'b10: begin
          tapa_state <= 2'b11;
          countdown <= 2'd2;
        end
        2'b11: begin
          if(countdown == 2'd0) begin
            tapa_state <= 2'b00;
          end else begin
            countdown <= (countdown - 2'd1);
          end
        end
      endcase
    end
  end

  assign ap_idle = (tapa_state == 2'b00);
  assign ap_done = ap_done__q3;
  assign ap_ready = ap_done__q0;

  always @(posedge ap_clk) begin
    ap_start__q1 <= ap_start__q0;
    ap_start__q2 <= ap_start__q1;
    ap_start__q3 <= ap_start__q2;
  end

  assign ap_start__q0 = ap_start;

  always @(posedge ap_clk) begin
    ap_done__q1 <= ap_done__q0;
    ap_done__q2 <= ap_done__q1;
    ap_done__q3 <= ap_done__q2;
  end

  assign ap_done__q0 = (tapa_state == 2'b10);

endmodule

