`timescale 1 ns / 1 ps 
module Jacobi (
  input  s_axi_control_AWVALID,
  output  s_axi_control_AWREADY,
  input [C_S_AXI_CONTROL_ADDR_WIDTH-1:0] s_axi_control_AWADDR,
  input  s_axi_control_WVALID,
  output  s_axi_control_WREADY,
  input [C_S_AXI_CONTROL_DATA_WIDTH-1:0] s_axi_control_WDATA,
  input [C_S_AXI_CONTROL_WSTRB_WIDTH-1:0] s_axi_control_WSTRB,
  input  s_axi_control_ARVALID,
  output  s_axi_control_ARREADY,
  input [C_S_AXI_CONTROL_ADDR_WIDTH-1:0] s_axi_control_ARADDR,
  output  s_axi_control_RVALID,
  input  s_axi_control_RREADY,
  output [C_S_AXI_CONTROL_DATA_WIDTH-1:0] s_axi_control_RDATA,
  output [1:0] s_axi_control_RRESP,
  output  s_axi_control_BVALID,
  input  s_axi_control_BREADY,
  output [1:0] s_axi_control_BRESP,
  input  ap_clk,
  input  ap_rst_n,
  output  interrupt,
  output [63:0] m_axi_bank_0_t1_ARADDR,
  output [1:0] m_axi_bank_0_t1_ARBURST,
  output [3:0] m_axi_bank_0_t1_ARCACHE,
  output [0:0] m_axi_bank_0_t1_ARID,
  output [7:0] m_axi_bank_0_t1_ARLEN,
  output  m_axi_bank_0_t1_ARLOCK,
  output [2:0] m_axi_bank_0_t1_ARPROT,
  output [3:0] m_axi_bank_0_t1_ARQOS,
  input  m_axi_bank_0_t1_ARREADY,
  output [2:0] m_axi_bank_0_t1_ARSIZE,
  output  m_axi_bank_0_t1_ARVALID,
  output [63:0] m_axi_bank_0_t1_AWADDR,
  output [1:0] m_axi_bank_0_t1_AWBURST,
  output [3:0] m_axi_bank_0_t1_AWCACHE,
  output [0:0] m_axi_bank_0_t1_AWID,
  output [7:0] m_axi_bank_0_t1_AWLEN,
  output  m_axi_bank_0_t1_AWLOCK,
  output [2:0] m_axi_bank_0_t1_AWPROT,
  output [3:0] m_axi_bank_0_t1_AWQOS,
  input  m_axi_bank_0_t1_AWREADY,
  output [2:0] m_axi_bank_0_t1_AWSIZE,
  output  m_axi_bank_0_t1_AWVALID,
  input [0:0] m_axi_bank_0_t1_BID,
  output  m_axi_bank_0_t1_BREADY,
  input [1:0] m_axi_bank_0_t1_BRESP,
  input  m_axi_bank_0_t1_BVALID,
  input [31:0] m_axi_bank_0_t1_RDATA,
  input [0:0] m_axi_bank_0_t1_RID,
  input  m_axi_bank_0_t1_RLAST,
  output  m_axi_bank_0_t1_RREADY,
  input [1:0] m_axi_bank_0_t1_RRESP,
  input  m_axi_bank_0_t1_RVALID,
  output [31:0] m_axi_bank_0_t1_WDATA,
  output  m_axi_bank_0_t1_WLAST,
  input  m_axi_bank_0_t1_WREADY,
  output [3:0] m_axi_bank_0_t1_WSTRB,
  output  m_axi_bank_0_t1_WVALID,
  output [63:0] m_axi_bank_0_t0_ARADDR,
  output [1:0] m_axi_bank_0_t0_ARBURST,
  output [3:0] m_axi_bank_0_t0_ARCACHE,
  output [0:0] m_axi_bank_0_t0_ARID,
  output [7:0] m_axi_bank_0_t0_ARLEN,
  output  m_axi_bank_0_t0_ARLOCK,
  output [2:0] m_axi_bank_0_t0_ARPROT,
  output [3:0] m_axi_bank_0_t0_ARQOS,
  input  m_axi_bank_0_t0_ARREADY,
  output [2:0] m_axi_bank_0_t0_ARSIZE,
  output  m_axi_bank_0_t0_ARVALID,
  output [63:0] m_axi_bank_0_t0_AWADDR,
  output [1:0] m_axi_bank_0_t0_AWBURST,
  output [3:0] m_axi_bank_0_t0_AWCACHE,
  output [0:0] m_axi_bank_0_t0_AWID,
  output [7:0] m_axi_bank_0_t0_AWLEN,
  output  m_axi_bank_0_t0_AWLOCK,
  output [2:0] m_axi_bank_0_t0_AWPROT,
  output [3:0] m_axi_bank_0_t0_AWQOS,
  input  m_axi_bank_0_t0_AWREADY,
  output [2:0] m_axi_bank_0_t0_AWSIZE,
  output  m_axi_bank_0_t0_AWVALID,
  input [0:0] m_axi_bank_0_t0_BID,
  output  m_axi_bank_0_t0_BREADY,
  input [1:0] m_axi_bank_0_t0_BRESP,
  input  m_axi_bank_0_t0_BVALID,
  input [31:0] m_axi_bank_0_t0_RDATA,
  input [0:0] m_axi_bank_0_t0_RID,
  input  m_axi_bank_0_t0_RLAST,
  output  m_axi_bank_0_t0_RREADY,
  input [1:0] m_axi_bank_0_t0_RRESP,
  input  m_axi_bank_0_t0_RVALID,
  output [31:0] m_axi_bank_0_t0_WDATA,
  output  m_axi_bank_0_t0_WLAST,
  input  m_axi_bank_0_t0_WREADY,
  output [3:0] m_axi_bank_0_t0_WSTRB,
  output  m_axi_bank_0_t0_WVALID
);



  parameter C_S_AXI_CONTROL_DATA_WIDTH = 32;
  parameter C_S_AXI_CONTROL_ADDR_WIDTH = 6;
  parameter C_S_AXI_DATA_WIDTH = 32;
  parameter C_S_AXI_CONTROL_WSTRB_WIDTH = 32 / 8;
  parameter C_S_AXI_WSTRB_WIDTH = 32 / 8;
  wire [63:0] m_axi_bank_0_t1_ARADDR_inner;
  wire [1:0] m_axi_bank_0_t1_ARBURST_inner;
  wire [3:0] m_axi_bank_0_t1_ARCACHE_inner;
  wire [0:0] m_axi_bank_0_t1_ARID_inner;
  wire [7:0] m_axi_bank_0_t1_ARLEN_inner;
  wire  m_axi_bank_0_t1_ARLOCK_inner;
  wire [2:0] m_axi_bank_0_t1_ARPROT_inner;
  wire [3:0] m_axi_bank_0_t1_ARQOS_inner;
  wire  m_axi_bank_0_t1_ARREADY_inner;
  wire [2:0] m_axi_bank_0_t1_ARSIZE_inner;
  wire  m_axi_bank_0_t1_ARVALID_inner;
  wire [63:0] m_axi_bank_0_t1_AWADDR_inner;
  wire [1:0] m_axi_bank_0_t1_AWBURST_inner;
  wire [3:0] m_axi_bank_0_t1_AWCACHE_inner;
  wire [0:0] m_axi_bank_0_t1_AWID_inner;
  wire [7:0] m_axi_bank_0_t1_AWLEN_inner;
  wire  m_axi_bank_0_t1_AWLOCK_inner;
  wire [2:0] m_axi_bank_0_t1_AWPROT_inner;
  wire [3:0] m_axi_bank_0_t1_AWQOS_inner;
  wire  m_axi_bank_0_t1_AWREADY_inner;
  wire [2:0] m_axi_bank_0_t1_AWSIZE_inner;
  wire  m_axi_bank_0_t1_AWVALID_inner;
  wire [0:0] m_axi_bank_0_t1_BID_inner;
  wire  m_axi_bank_0_t1_BREADY_inner;
  wire [1:0] m_axi_bank_0_t1_BRESP_inner;
  wire  m_axi_bank_0_t1_BVALID_inner;
  wire [31:0] m_axi_bank_0_t1_RDATA_inner;
  wire [0:0] m_axi_bank_0_t1_RID_inner;
  wire  m_axi_bank_0_t1_RLAST_inner;
  wire  m_axi_bank_0_t1_RREADY_inner;
  wire [1:0] m_axi_bank_0_t1_RRESP_inner;
  wire  m_axi_bank_0_t1_RVALID_inner;
  wire [31:0] m_axi_bank_0_t1_WDATA_inner;
  wire  m_axi_bank_0_t1_WLAST_inner;
  wire  m_axi_bank_0_t1_WREADY_inner;
  wire [3:0] m_axi_bank_0_t1_WSTRB_inner;
  wire  m_axi_bank_0_t1_WVALID_inner;
  wire [63:0] m_axi_bank_0_t0_ARADDR_inner;
  wire [1:0] m_axi_bank_0_t0_ARBURST_inner;
  wire [3:0] m_axi_bank_0_t0_ARCACHE_inner;
  wire [0:0] m_axi_bank_0_t0_ARID_inner;
  wire [7:0] m_axi_bank_0_t0_ARLEN_inner;
  wire  m_axi_bank_0_t0_ARLOCK_inner;
  wire [2:0] m_axi_bank_0_t0_ARPROT_inner;
  wire [3:0] m_axi_bank_0_t0_ARQOS_inner;
  wire  m_axi_bank_0_t0_ARREADY_inner;
  wire [2:0] m_axi_bank_0_t0_ARSIZE_inner;
  wire  m_axi_bank_0_t0_ARVALID_inner;
  wire [63:0] m_axi_bank_0_t0_AWADDR_inner;
  wire [1:0] m_axi_bank_0_t0_AWBURST_inner;
  wire [3:0] m_axi_bank_0_t0_AWCACHE_inner;
  wire [0:0] m_axi_bank_0_t0_AWID_inner;
  wire [7:0] m_axi_bank_0_t0_AWLEN_inner;
  wire  m_axi_bank_0_t0_AWLOCK_inner;
  wire [2:0] m_axi_bank_0_t0_AWPROT_inner;
  wire [3:0] m_axi_bank_0_t0_AWQOS_inner;
  wire  m_axi_bank_0_t0_AWREADY_inner;
  wire [2:0] m_axi_bank_0_t0_AWSIZE_inner;
  wire  m_axi_bank_0_t0_AWVALID_inner;
  wire [0:0] m_axi_bank_0_t0_BID_inner;
  wire  m_axi_bank_0_t0_BREADY_inner;
  wire [1:0] m_axi_bank_0_t0_BRESP_inner;
  wire  m_axi_bank_0_t0_BVALID_inner;
  wire [31:0] m_axi_bank_0_t0_RDATA_inner;
  wire [0:0] m_axi_bank_0_t0_RID_inner;
  wire  m_axi_bank_0_t0_RLAST_inner;
  wire  m_axi_bank_0_t0_RREADY_inner;
  wire [1:0] m_axi_bank_0_t0_RRESP_inner;
  wire  m_axi_bank_0_t0_RVALID_inner;
  wire [31:0] m_axi_bank_0_t0_WDATA_inner;
  wire  m_axi_bank_0_t0_WLAST_inner;
  wire  m_axi_bank_0_t0_WREADY_inner;
  wire [3:0] m_axi_bank_0_t0_WSTRB_inner;
  wire  m_axi_bank_0_t0_WVALID_inner;



  axi_pipeline #(
    .C_M_AXI_ADDR_WIDTH(64),
    .C_M_AXI_DATA_WIDTH(32),
    .PIPELINE_LEVEL    (0)
  ) bank_0_t0 (
    .out_ARADDR  (m_axi_bank_0_t0_ARADDR   ),
    .out_ARBURST  (m_axi_bank_0_t0_ARBURST   ),
    .out_ARID  (m_axi_bank_0_t0_ARID   ),
    .out_ARLEN  (m_axi_bank_0_t0_ARLEN   ),
    .out_ARREADY  (m_axi_bank_0_t0_ARREADY   ),
    .out_ARSIZE  (m_axi_bank_0_t0_ARSIZE   ),
    .out_ARVALID  (m_axi_bank_0_t0_ARVALID   ),
    .out_AWADDR  (m_axi_bank_0_t0_AWADDR   ),
    .out_AWBURST  (m_axi_bank_0_t0_AWBURST   ),
    .out_AWID  (m_axi_bank_0_t0_AWID   ),
    .out_AWLEN  (m_axi_bank_0_t0_AWLEN   ),
    .out_AWREADY  (m_axi_bank_0_t0_AWREADY   ),
    .out_AWSIZE  (m_axi_bank_0_t0_AWSIZE   ),
    .out_AWVALID  (m_axi_bank_0_t0_AWVALID   ),
    .out_BID  (m_axi_bank_0_t0_BID   ),
    .out_BREADY  (m_axi_bank_0_t0_BREADY   ),
    .out_BRESP  (m_axi_bank_0_t0_BRESP   ),
    .out_BVALID  (m_axi_bank_0_t0_BVALID   ),
    .out_RDATA  (m_axi_bank_0_t0_RDATA   ),
    .out_RID  (m_axi_bank_0_t0_RID   ),
    .out_RLAST  (m_axi_bank_0_t0_RLAST   ),
    .out_RREADY  (m_axi_bank_0_t0_RREADY   ),
    .out_RRESP  (m_axi_bank_0_t0_RRESP   ),
    .out_RVALID  (m_axi_bank_0_t0_RVALID   ),
    .out_WDATA  (m_axi_bank_0_t0_WDATA   ),
    .out_WLAST  (m_axi_bank_0_t0_WLAST   ),
    .out_WREADY  (m_axi_bank_0_t0_WREADY   ),
    .out_WSTRB  (m_axi_bank_0_t0_WSTRB   ),
    .out_WVALID  (m_axi_bank_0_t0_WVALID   ),
    .in_ARADDR  (m_axi_bank_0_t0_ARADDR_inner  ),
    .in_ARBURST  (m_axi_bank_0_t0_ARBURST_inner  ),
    .in_ARID  (m_axi_bank_0_t0_ARID_inner  ),
    .in_ARLEN  (m_axi_bank_0_t0_ARLEN_inner  ),
    .in_ARREADY  (m_axi_bank_0_t0_ARREADY_inner  ),
    .in_ARSIZE  (m_axi_bank_0_t0_ARSIZE_inner  ),
    .in_ARVALID  (m_axi_bank_0_t0_ARVALID_inner  ),
    .in_AWADDR  (m_axi_bank_0_t0_AWADDR_inner  ),
    .in_AWBURST  (m_axi_bank_0_t0_AWBURST_inner  ),
    .in_AWID  (m_axi_bank_0_t0_AWID_inner  ),
    .in_AWLEN  (m_axi_bank_0_t0_AWLEN_inner  ),
    .in_AWREADY  (m_axi_bank_0_t0_AWREADY_inner  ),
    .in_AWSIZE  (m_axi_bank_0_t0_AWSIZE_inner  ),
    .in_AWVALID  (m_axi_bank_0_t0_AWVALID_inner  ),
    .in_BID  (m_axi_bank_0_t0_BID_inner  ),
    .in_BREADY  (m_axi_bank_0_t0_BREADY_inner  ),
    .in_BRESP  (m_axi_bank_0_t0_BRESP_inner  ),
    .in_BVALID  (m_axi_bank_0_t0_BVALID_inner  ),
    .in_RDATA  (m_axi_bank_0_t0_RDATA_inner  ),
    .in_RID  (m_axi_bank_0_t0_RID_inner  ),
    .in_RLAST  (m_axi_bank_0_t0_RLAST_inner  ),
    .in_RREADY  (m_axi_bank_0_t0_RREADY_inner  ),
    .in_RRESP  (m_axi_bank_0_t0_RRESP_inner  ),
    .in_RVALID  (m_axi_bank_0_t0_RVALID_inner  ),
    .in_WDATA  (m_axi_bank_0_t0_WDATA_inner  ),
    .in_WLAST  (m_axi_bank_0_t0_WLAST_inner  ),
    .in_WREADY  (m_axi_bank_0_t0_WREADY_inner  ),
    .in_WSTRB  (m_axi_bank_0_t0_WSTRB_inner  ),
    .in_WVALID  (m_axi_bank_0_t0_WVALID_inner  ),
    .ap_clk      (ap_clk)
  );
  axi_pipeline #(
    .C_M_AXI_ADDR_WIDTH(64),
    .C_M_AXI_DATA_WIDTH(32),
    .PIPELINE_LEVEL    (0)
  ) bank_0_t1 (
    .out_ARADDR  (m_axi_bank_0_t1_ARADDR   ),
    .out_ARBURST  (m_axi_bank_0_t1_ARBURST   ),
    .out_ARID  (m_axi_bank_0_t1_ARID   ),
    .out_ARLEN  (m_axi_bank_0_t1_ARLEN   ),
    .out_ARREADY  (m_axi_bank_0_t1_ARREADY   ),
    .out_ARSIZE  (m_axi_bank_0_t1_ARSIZE   ),
    .out_ARVALID  (m_axi_bank_0_t1_ARVALID   ),
    .out_AWADDR  (m_axi_bank_0_t1_AWADDR   ),
    .out_AWBURST  (m_axi_bank_0_t1_AWBURST   ),
    .out_AWID  (m_axi_bank_0_t1_AWID   ),
    .out_AWLEN  (m_axi_bank_0_t1_AWLEN   ),
    .out_AWREADY  (m_axi_bank_0_t1_AWREADY   ),
    .out_AWSIZE  (m_axi_bank_0_t1_AWSIZE   ),
    .out_AWVALID  (m_axi_bank_0_t1_AWVALID   ),
    .out_BID  (m_axi_bank_0_t1_BID   ),
    .out_BREADY  (m_axi_bank_0_t1_BREADY   ),
    .out_BRESP  (m_axi_bank_0_t1_BRESP   ),
    .out_BVALID  (m_axi_bank_0_t1_BVALID   ),
    .out_RDATA  (m_axi_bank_0_t1_RDATA   ),
    .out_RID  (m_axi_bank_0_t1_RID   ),
    .out_RLAST  (m_axi_bank_0_t1_RLAST   ),
    .out_RREADY  (m_axi_bank_0_t1_RREADY   ),
    .out_RRESP  (m_axi_bank_0_t1_RRESP   ),
    .out_RVALID  (m_axi_bank_0_t1_RVALID   ),
    .out_WDATA  (m_axi_bank_0_t1_WDATA   ),
    .out_WLAST  (m_axi_bank_0_t1_WLAST   ),
    .out_WREADY  (m_axi_bank_0_t1_WREADY   ),
    .out_WSTRB  (m_axi_bank_0_t1_WSTRB   ),
    .out_WVALID  (m_axi_bank_0_t1_WVALID   ),
    .in_ARADDR  (m_axi_bank_0_t1_ARADDR_inner  ),
    .in_ARBURST  (m_axi_bank_0_t1_ARBURST_inner  ),
    .in_ARID  (m_axi_bank_0_t1_ARID_inner  ),
    .in_ARLEN  (m_axi_bank_0_t1_ARLEN_inner  ),
    .in_ARREADY  (m_axi_bank_0_t1_ARREADY_inner  ),
    .in_ARSIZE  (m_axi_bank_0_t1_ARSIZE_inner  ),
    .in_ARVALID  (m_axi_bank_0_t1_ARVALID_inner  ),
    .in_AWADDR  (m_axi_bank_0_t1_AWADDR_inner  ),
    .in_AWBURST  (m_axi_bank_0_t1_AWBURST_inner  ),
    .in_AWID  (m_axi_bank_0_t1_AWID_inner  ),
    .in_AWLEN  (m_axi_bank_0_t1_AWLEN_inner  ),
    .in_AWREADY  (m_axi_bank_0_t1_AWREADY_inner  ),
    .in_AWSIZE  (m_axi_bank_0_t1_AWSIZE_inner  ),
    .in_AWVALID  (m_axi_bank_0_t1_AWVALID_inner  ),
    .in_BID  (m_axi_bank_0_t1_BID_inner  ),
    .in_BREADY  (m_axi_bank_0_t1_BREADY_inner  ),
    .in_BRESP  (m_axi_bank_0_t1_BRESP_inner  ),
    .in_BVALID  (m_axi_bank_0_t1_BVALID_inner  ),
    .in_RDATA  (m_axi_bank_0_t1_RDATA_inner  ),
    .in_RID  (m_axi_bank_0_t1_RID_inner  ),
    .in_RLAST  (m_axi_bank_0_t1_RLAST_inner  ),
    .in_RREADY  (m_axi_bank_0_t1_RREADY_inner  ),
    .in_RRESP  (m_axi_bank_0_t1_RRESP_inner  ),
    .in_RVALID  (m_axi_bank_0_t1_RVALID_inner  ),
    .in_WDATA  (m_axi_bank_0_t1_WDATA_inner  ),
    .in_WLAST  (m_axi_bank_0_t1_WLAST_inner  ),
    .in_WREADY  (m_axi_bank_0_t1_WREADY_inner  ),
    .in_WSTRB  (m_axi_bank_0_t1_WSTRB_inner  ),
    .in_WVALID  (m_axi_bank_0_t1_WVALID_inner  ),
    .ap_clk      (ap_clk)
  );



  Jacobi_inner Jacobi_inner_0 (
    .s_axi_control_AWVALID(s_axi_control_AWVALID),
    .s_axi_control_AWREADY(s_axi_control_AWREADY),
    .s_axi_control_AWADDR(s_axi_control_AWADDR),
    .s_axi_control_WVALID(s_axi_control_WVALID),
    .s_axi_control_WREADY(s_axi_control_WREADY),
    .s_axi_control_WDATA(s_axi_control_WDATA),
    .s_axi_control_WSTRB(s_axi_control_WSTRB),
    .s_axi_control_ARVALID(s_axi_control_ARVALID),
    .s_axi_control_ARREADY(s_axi_control_ARREADY),
    .s_axi_control_ARADDR(s_axi_control_ARADDR),
    .s_axi_control_RVALID(s_axi_control_RVALID),
    .s_axi_control_RREADY(s_axi_control_RREADY),
    .s_axi_control_RDATA(s_axi_control_RDATA),
    .s_axi_control_RRESP(s_axi_control_RRESP),
    .s_axi_control_BVALID(s_axi_control_BVALID),
    .s_axi_control_BREADY(s_axi_control_BREADY),
    .s_axi_control_BRESP(s_axi_control_BRESP),
    .ap_clk(ap_clk),
    .ap_rst_n(ap_rst_n),
    .interrupt(interrupt),
    .m_axi_bank_0_t1_ARADDR(m_axi_bank_0_t1_ARADDR_inner),
    .m_axi_bank_0_t1_ARBURST(m_axi_bank_0_t1_ARBURST_inner),
    .m_axi_bank_0_t1_ARCACHE(m_axi_bank_0_t1_ARCACHE_inner),
    .m_axi_bank_0_t1_ARID(m_axi_bank_0_t1_ARID_inner),
    .m_axi_bank_0_t1_ARLEN(m_axi_bank_0_t1_ARLEN_inner),
    .m_axi_bank_0_t1_ARLOCK(m_axi_bank_0_t1_ARLOCK_inner),
    .m_axi_bank_0_t1_ARPROT(m_axi_bank_0_t1_ARPROT_inner),
    .m_axi_bank_0_t1_ARQOS(m_axi_bank_0_t1_ARQOS_inner),
    .m_axi_bank_0_t1_ARREADY(m_axi_bank_0_t1_ARREADY_inner),
    .m_axi_bank_0_t1_ARSIZE(m_axi_bank_0_t1_ARSIZE_inner),
    .m_axi_bank_0_t1_ARVALID(m_axi_bank_0_t1_ARVALID_inner),
    .m_axi_bank_0_t1_AWADDR(m_axi_bank_0_t1_AWADDR_inner),
    .m_axi_bank_0_t1_AWBURST(m_axi_bank_0_t1_AWBURST_inner),
    .m_axi_bank_0_t1_AWCACHE(m_axi_bank_0_t1_AWCACHE_inner),
    .m_axi_bank_0_t1_AWID(m_axi_bank_0_t1_AWID_inner),
    .m_axi_bank_0_t1_AWLEN(m_axi_bank_0_t1_AWLEN_inner),
    .m_axi_bank_0_t1_AWLOCK(m_axi_bank_0_t1_AWLOCK_inner),
    .m_axi_bank_0_t1_AWPROT(m_axi_bank_0_t1_AWPROT_inner),
    .m_axi_bank_0_t1_AWQOS(m_axi_bank_0_t1_AWQOS_inner),
    .m_axi_bank_0_t1_AWREADY(m_axi_bank_0_t1_AWREADY_inner),
    .m_axi_bank_0_t1_AWSIZE(m_axi_bank_0_t1_AWSIZE_inner),
    .m_axi_bank_0_t1_AWVALID(m_axi_bank_0_t1_AWVALID_inner),
    .m_axi_bank_0_t1_BID(m_axi_bank_0_t1_BID_inner),
    .m_axi_bank_0_t1_BREADY(m_axi_bank_0_t1_BREADY_inner),
    .m_axi_bank_0_t1_BRESP(m_axi_bank_0_t1_BRESP_inner),
    .m_axi_bank_0_t1_BVALID(m_axi_bank_0_t1_BVALID_inner),
    .m_axi_bank_0_t1_RDATA(m_axi_bank_0_t1_RDATA_inner),
    .m_axi_bank_0_t1_RID(m_axi_bank_0_t1_RID_inner),
    .m_axi_bank_0_t1_RLAST(m_axi_bank_0_t1_RLAST_inner),
    .m_axi_bank_0_t1_RREADY(m_axi_bank_0_t1_RREADY_inner),
    .m_axi_bank_0_t1_RRESP(m_axi_bank_0_t1_RRESP_inner),
    .m_axi_bank_0_t1_RVALID(m_axi_bank_0_t1_RVALID_inner),
    .m_axi_bank_0_t1_WDATA(m_axi_bank_0_t1_WDATA_inner),
    .m_axi_bank_0_t1_WLAST(m_axi_bank_0_t1_WLAST_inner),
    .m_axi_bank_0_t1_WREADY(m_axi_bank_0_t1_WREADY_inner),
    .m_axi_bank_0_t1_WSTRB(m_axi_bank_0_t1_WSTRB_inner),
    .m_axi_bank_0_t1_WVALID(m_axi_bank_0_t1_WVALID_inner),
    .m_axi_bank_0_t0_ARADDR(m_axi_bank_0_t0_ARADDR_inner),
    .m_axi_bank_0_t0_ARBURST(m_axi_bank_0_t0_ARBURST_inner),
    .m_axi_bank_0_t0_ARCACHE(m_axi_bank_0_t0_ARCACHE_inner),
    .m_axi_bank_0_t0_ARID(m_axi_bank_0_t0_ARID_inner),
    .m_axi_bank_0_t0_ARLEN(m_axi_bank_0_t0_ARLEN_inner),
    .m_axi_bank_0_t0_ARLOCK(m_axi_bank_0_t0_ARLOCK_inner),
    .m_axi_bank_0_t0_ARPROT(m_axi_bank_0_t0_ARPROT_inner),
    .m_axi_bank_0_t0_ARQOS(m_axi_bank_0_t0_ARQOS_inner),
    .m_axi_bank_0_t0_ARREADY(m_axi_bank_0_t0_ARREADY_inner),
    .m_axi_bank_0_t0_ARSIZE(m_axi_bank_0_t0_ARSIZE_inner),
    .m_axi_bank_0_t0_ARVALID(m_axi_bank_0_t0_ARVALID_inner),
    .m_axi_bank_0_t0_AWADDR(m_axi_bank_0_t0_AWADDR_inner),
    .m_axi_bank_0_t0_AWBURST(m_axi_bank_0_t0_AWBURST_inner),
    .m_axi_bank_0_t0_AWCACHE(m_axi_bank_0_t0_AWCACHE_inner),
    .m_axi_bank_0_t0_AWID(m_axi_bank_0_t0_AWID_inner),
    .m_axi_bank_0_t0_AWLEN(m_axi_bank_0_t0_AWLEN_inner),
    .m_axi_bank_0_t0_AWLOCK(m_axi_bank_0_t0_AWLOCK_inner),
    .m_axi_bank_0_t0_AWPROT(m_axi_bank_0_t0_AWPROT_inner),
    .m_axi_bank_0_t0_AWQOS(m_axi_bank_0_t0_AWQOS_inner),
    .m_axi_bank_0_t0_AWREADY(m_axi_bank_0_t0_AWREADY_inner),
    .m_axi_bank_0_t0_AWSIZE(m_axi_bank_0_t0_AWSIZE_inner),
    .m_axi_bank_0_t0_AWVALID(m_axi_bank_0_t0_AWVALID_inner),
    .m_axi_bank_0_t0_BID(m_axi_bank_0_t0_BID_inner),
    .m_axi_bank_0_t0_BREADY(m_axi_bank_0_t0_BREADY_inner),
    .m_axi_bank_0_t0_BRESP(m_axi_bank_0_t0_BRESP_inner),
    .m_axi_bank_0_t0_BVALID(m_axi_bank_0_t0_BVALID_inner),
    .m_axi_bank_0_t0_RDATA(m_axi_bank_0_t0_RDATA_inner),
    .m_axi_bank_0_t0_RID(m_axi_bank_0_t0_RID_inner),
    .m_axi_bank_0_t0_RLAST(m_axi_bank_0_t0_RLAST_inner),
    .m_axi_bank_0_t0_RREADY(m_axi_bank_0_t0_RREADY_inner),
    .m_axi_bank_0_t0_RRESP(m_axi_bank_0_t0_RRESP_inner),
    .m_axi_bank_0_t0_RVALID(m_axi_bank_0_t0_RVALID_inner),
    .m_axi_bank_0_t0_WDATA(m_axi_bank_0_t0_WDATA_inner),
    .m_axi_bank_0_t0_WLAST(m_axi_bank_0_t0_WLAST_inner),
    .m_axi_bank_0_t0_WREADY(m_axi_bank_0_t0_WREADY_inner),
    .m_axi_bank_0_t0_WSTRB(m_axi_bank_0_t0_WSTRB_inner),
    .m_axi_bank_0_t0_WVALID(m_axi_bank_0_t0_WVALID_inner)
  );



endmodule