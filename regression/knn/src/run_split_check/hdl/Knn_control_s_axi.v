// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
`timescale 1ns/1ps
module Knn_control_s_axi
#(parameter
    C_S_AXI_ADDR_WIDTH = 8,
    C_S_AXI_DATA_WIDTH = 32
)(
    input  wire                          ACLK,
    input  wire                          ARESET,
    input  wire                          ACLK_EN,
    input  wire [C_S_AXI_ADDR_WIDTH-1:0] AWADDR,
    input  wire                          AWVALID,
    output wire                          AWREADY,
    input  wire [C_S_AXI_DATA_WIDTH-1:0] WDATA,
    input  wire [C_S_AXI_DATA_WIDTH/8-1:0] WSTRB,
    input  wire                          WVALID,
    output wire                          WREADY,
    output wire [1:0]                    BRESP,
    output wire                          BVALID,
    input  wire                          BREADY,
    input  wire [C_S_AXI_ADDR_WIDTH-1:0] ARADDR,
    input  wire                          ARVALID,
    output wire                          ARREADY,
    output wire [C_S_AXI_DATA_WIDTH-1:0] RDATA,
    output wire [1:0]                    RRESP,
    output wire                          RVALID,
    input  wire                          RREADY,
    output wire                          interrupt,
    output wire [63:0]                   in_0,
    output wire [63:0]                   in_1,
    output wire [63:0]                   in_2,
    output wire [63:0]                   in_3,
    output wire [63:0]                   in_4,
    output wire [63:0]                   in_5,
    output wire [63:0]                   in_6,
    output wire [63:0]                   in_7,
    output wire [63:0]                   in_8,
    output wire [63:0]                   in_9,
    output wire [63:0]                   in_10,
    output wire [63:0]                   in_11,
    output wire [63:0]                   in_12,
    output wire [63:0]                   in_13,
    output wire [63:0]                   in_14,
    output wire [63:0]                   in_15,
    output wire [63:0]                   in_16,
    output wire [63:0]                   in_17,
    output wire [63:0]                   L3_out_dist,
    output wire [63:0]                   L3_out_id,
    output wire                          ap_start,
    input  wire                          ap_done,
    input  wire                          ap_ready,
    input  wire                          ap_idle
);
//------------------------Address Info-------------------
// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/SC)
//        bit 1  - ap_done (Read/COR)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read/COR)
//        bit 7  - auto_restart (Read/Write)
//        bit 9  - interrupt (Read)
//        others - reserved
// 0x04 : Global Interrupt Enable Register
//        bit 0  - Global Interrupt Enable (Read/Write)
//        others - reserved
// 0x08 : IP Interrupt Enable Register (Read/Write)
//        bit 0 - enable ap_done interrupt (Read/Write)
//        others - reserved
// 0x0c : IP Interrupt Status Register (Read/COR)
//        bit 0 - ap_done (Read/COR)
//        others - reserved
// 0x10 : Data signal of in_0
//        bit 31~0 - in_0[31:0] (Read/Write)
// 0x14 : Data signal of in_0
//        bit 31~0 - in_0[63:32] (Read/Write)
// 0x18 : reserved
// 0x1c : Data signal of in_1
//        bit 31~0 - in_1[31:0] (Read/Write)
// 0x20 : Data signal of in_1
//        bit 31~0 - in_1[63:32] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of in_2
//        bit 31~0 - in_2[31:0] (Read/Write)
// 0x2c : Data signal of in_2
//        bit 31~0 - in_2[63:32] (Read/Write)
// 0x30 : reserved
// 0x34 : Data signal of in_3
//        bit 31~0 - in_3[31:0] (Read/Write)
// 0x38 : Data signal of in_3
//        bit 31~0 - in_3[63:32] (Read/Write)
// 0x3c : reserved
// 0x40 : Data signal of in_4
//        bit 31~0 - in_4[31:0] (Read/Write)
// 0x44 : Data signal of in_4
//        bit 31~0 - in_4[63:32] (Read/Write)
// 0x48 : reserved
// 0x4c : Data signal of in_5
//        bit 31~0 - in_5[31:0] (Read/Write)
// 0x50 : Data signal of in_5
//        bit 31~0 - in_5[63:32] (Read/Write)
// 0x54 : reserved
// 0x58 : Data signal of in_6
//        bit 31~0 - in_6[31:0] (Read/Write)
// 0x5c : Data signal of in_6
//        bit 31~0 - in_6[63:32] (Read/Write)
// 0x60 : reserved
// 0x64 : Data signal of in_7
//        bit 31~0 - in_7[31:0] (Read/Write)
// 0x68 : Data signal of in_7
//        bit 31~0 - in_7[63:32] (Read/Write)
// 0x6c : reserved
// 0x70 : Data signal of in_8
//        bit 31~0 - in_8[31:0] (Read/Write)
// 0x74 : Data signal of in_8
//        bit 31~0 - in_8[63:32] (Read/Write)
// 0x78 : reserved
// 0x7c : Data signal of in_9
//        bit 31~0 - in_9[31:0] (Read/Write)
// 0x80 : Data signal of in_9
//        bit 31~0 - in_9[63:32] (Read/Write)
// 0x84 : reserved
// 0x88 : Data signal of in_10
//        bit 31~0 - in_10[31:0] (Read/Write)
// 0x8c : Data signal of in_10
//        bit 31~0 - in_10[63:32] (Read/Write)
// 0x90 : reserved
// 0x94 : Data signal of in_11
//        bit 31~0 - in_11[31:0] (Read/Write)
// 0x98 : Data signal of in_11
//        bit 31~0 - in_11[63:32] (Read/Write)
// 0x9c : reserved
// 0xa0 : Data signal of in_12
//        bit 31~0 - in_12[31:0] (Read/Write)
// 0xa4 : Data signal of in_12
//        bit 31~0 - in_12[63:32] (Read/Write)
// 0xa8 : reserved
// 0xac : Data signal of in_13
//        bit 31~0 - in_13[31:0] (Read/Write)
// 0xb0 : Data signal of in_13
//        bit 31~0 - in_13[63:32] (Read/Write)
// 0xb4 : reserved
// 0xb8 : Data signal of in_14
//        bit 31~0 - in_14[31:0] (Read/Write)
// 0xbc : Data signal of in_14
//        bit 31~0 - in_14[63:32] (Read/Write)
// 0xc0 : reserved
// 0xc4 : Data signal of in_15
//        bit 31~0 - in_15[31:0] (Read/Write)
// 0xc8 : Data signal of in_15
//        bit 31~0 - in_15[63:32] (Read/Write)
// 0xcc : reserved
// 0xd0 : Data signal of in_16
//        bit 31~0 - in_16[31:0] (Read/Write)
// 0xd4 : Data signal of in_16
//        bit 31~0 - in_16[63:32] (Read/Write)
// 0xd8 : reserved
// 0xdc : Data signal of in_17
//        bit 31~0 - in_17[31:0] (Read/Write)
// 0xe0 : Data signal of in_17
//        bit 31~0 - in_17[63:32] (Read/Write)
// 0xe4 : reserved
// 0xe8 : Data signal of L3_out_dist
//        bit 31~0 - L3_out_dist[31:0] (Read/Write)
// 0xec : Data signal of L3_out_dist
//        bit 31~0 - L3_out_dist[63:32] (Read/Write)
// 0xf0 : reserved
// 0xf4 : Data signal of L3_out_id
//        bit 31~0 - L3_out_id[31:0] (Read/Write)
// 0xf8 : Data signal of L3_out_id
//        bit 31~0 - L3_out_id[63:32] (Read/Write)
// 0xfc : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

//------------------------Parameter----------------------
localparam
    ADDR_AP_CTRL            = 8'h00,
    ADDR_GIE                = 8'h04,
    ADDR_IER                = 8'h08,
    ADDR_ISR                = 8'h0c,
    ADDR_IN_0_DATA_0        = 8'h10,
    ADDR_IN_0_DATA_1        = 8'h14,
    ADDR_IN_0_CTRL          = 8'h18,
    ADDR_IN_1_DATA_0        = 8'h1c,
    ADDR_IN_1_DATA_1        = 8'h20,
    ADDR_IN_1_CTRL          = 8'h24,
    ADDR_IN_2_DATA_0        = 8'h28,
    ADDR_IN_2_DATA_1        = 8'h2c,
    ADDR_IN_2_CTRL          = 8'h30,
    ADDR_IN_3_DATA_0        = 8'h34,
    ADDR_IN_3_DATA_1        = 8'h38,
    ADDR_IN_3_CTRL          = 8'h3c,
    ADDR_IN_4_DATA_0        = 8'h40,
    ADDR_IN_4_DATA_1        = 8'h44,
    ADDR_IN_4_CTRL          = 8'h48,
    ADDR_IN_5_DATA_0        = 8'h4c,
    ADDR_IN_5_DATA_1        = 8'h50,
    ADDR_IN_5_CTRL          = 8'h54,
    ADDR_IN_6_DATA_0        = 8'h58,
    ADDR_IN_6_DATA_1        = 8'h5c,
    ADDR_IN_6_CTRL          = 8'h60,
    ADDR_IN_7_DATA_0        = 8'h64,
    ADDR_IN_7_DATA_1        = 8'h68,
    ADDR_IN_7_CTRL          = 8'h6c,
    ADDR_IN_8_DATA_0        = 8'h70,
    ADDR_IN_8_DATA_1        = 8'h74,
    ADDR_IN_8_CTRL          = 8'h78,
    ADDR_IN_9_DATA_0        = 8'h7c,
    ADDR_IN_9_DATA_1        = 8'h80,
    ADDR_IN_9_CTRL          = 8'h84,
    ADDR_IN_10_DATA_0       = 8'h88,
    ADDR_IN_10_DATA_1       = 8'h8c,
    ADDR_IN_10_CTRL         = 8'h90,
    ADDR_IN_11_DATA_0       = 8'h94,
    ADDR_IN_11_DATA_1       = 8'h98,
    ADDR_IN_11_CTRL         = 8'h9c,
    ADDR_IN_12_DATA_0       = 8'ha0,
    ADDR_IN_12_DATA_1       = 8'ha4,
    ADDR_IN_12_CTRL         = 8'ha8,
    ADDR_IN_13_DATA_0       = 8'hac,
    ADDR_IN_13_DATA_1       = 8'hb0,
    ADDR_IN_13_CTRL         = 8'hb4,
    ADDR_IN_14_DATA_0       = 8'hb8,
    ADDR_IN_14_DATA_1       = 8'hbc,
    ADDR_IN_14_CTRL         = 8'hc0,
    ADDR_IN_15_DATA_0       = 8'hc4,
    ADDR_IN_15_DATA_1       = 8'hc8,
    ADDR_IN_15_CTRL         = 8'hcc,
    ADDR_IN_16_DATA_0       = 8'hd0,
    ADDR_IN_16_DATA_1       = 8'hd4,
    ADDR_IN_16_CTRL         = 8'hd8,
    ADDR_IN_17_DATA_0       = 8'hdc,
    ADDR_IN_17_DATA_1       = 8'he0,
    ADDR_IN_17_CTRL         = 8'he4,
    ADDR_L3_OUT_DIST_DATA_0 = 8'he8,
    ADDR_L3_OUT_DIST_DATA_1 = 8'hec,
    ADDR_L3_OUT_DIST_CTRL   = 8'hf0,
    ADDR_L3_OUT_ID_DATA_0   = 8'hf4,
    ADDR_L3_OUT_ID_DATA_1   = 8'hf8,
    ADDR_L3_OUT_ID_CTRL     = 8'hfc,
    WRIDLE                  = 2'd0,
    WRDATA                  = 2'd1,
    WRRESP                  = 2'd2,
    WRRESET                 = 2'd3,
    RDIDLE                  = 2'd0,
    RDDATA                  = 2'd1,
    RDRESET                 = 2'd2,
    ADDR_BITS                = 8;

//------------------------Local signal-------------------
    reg  [1:0]                    wstate = WRRESET;
    reg  [1:0]                    wnext;
    reg  [ADDR_BITS-1:0]          waddr;
    wire [C_S_AXI_DATA_WIDTH-1:0] wmask;
    wire                          aw_hs;
    wire                          w_hs;
    reg  [1:0]                    rstate = RDRESET;
    reg  [1:0]                    rnext;
    reg  [C_S_AXI_DATA_WIDTH-1:0] rdata;
    wire                          ar_hs;
    wire [ADDR_BITS-1:0]          raddr;
    // internal registers
    reg                           int_ap_idle;
    reg                           int_ap_ready = 1'b0;
    wire                          task_ap_ready;
    reg                           int_ap_done = 1'b0;
    wire                          task_ap_done;
    reg                           int_task_ap_done = 1'b0;
    reg                           int_ap_start = 1'b0;
    reg                           int_interrupt = 1'b0;
    reg                           int_auto_restart = 1'b0;
    reg                           auto_restart_status = 1'b0;
    wire                          auto_restart_done;
    reg                           int_gie = 1'b0;
    reg                           int_ier = 1'b0;
    reg                           int_isr = 1'b0;
    reg  [63:0]                   int_in_0 = 'b0;
    reg  [63:0]                   int_in_1 = 'b0;
    reg  [63:0]                   int_in_2 = 'b0;
    reg  [63:0]                   int_in_3 = 'b0;
    reg  [63:0]                   int_in_4 = 'b0;
    reg  [63:0]                   int_in_5 = 'b0;
    reg  [63:0]                   int_in_6 = 'b0;
    reg  [63:0]                   int_in_7 = 'b0;
    reg  [63:0]                   int_in_8 = 'b0;
    reg  [63:0]                   int_in_9 = 'b0;
    reg  [63:0]                   int_in_10 = 'b0;
    reg  [63:0]                   int_in_11 = 'b0;
    reg  [63:0]                   int_in_12 = 'b0;
    reg  [63:0]                   int_in_13 = 'b0;
    reg  [63:0]                   int_in_14 = 'b0;
    reg  [63:0]                   int_in_15 = 'b0;
    reg  [63:0]                   int_in_16 = 'b0;
    reg  [63:0]                   int_in_17 = 'b0;
    reg  [63:0]                   int_L3_out_dist = 'b0;
    reg  [63:0]                   int_L3_out_id = 'b0;

//------------------------Instantiation------------------


//------------------------AXI write fsm------------------
assign AWREADY = (wstate == WRIDLE);
assign WREADY  = (wstate == WRDATA);
assign BRESP   = 2'b00;  // OKAY
assign BVALID  = (wstate == WRRESP);
assign wmask   = { {8{WSTRB[3]}}, {8{WSTRB[2]}}, {8{WSTRB[1]}}, {8{WSTRB[0]}} };
assign aw_hs   = AWVALID & AWREADY;
assign w_hs    = WVALID & WREADY;

// wstate
always @(posedge ACLK) begin
    if (ARESET)
        wstate <= WRRESET;
    else if (ACLK_EN)
        wstate <= wnext;
end

// wnext
always @(*) begin
    case (wstate)
        WRIDLE:
            if (AWVALID)
                wnext = WRDATA;
            else
                wnext = WRIDLE;
        WRDATA:
            if (WVALID)
                wnext = WRRESP;
            else
                wnext = WRDATA;
        WRRESP:
            if (BREADY)
                wnext = WRIDLE;
            else
                wnext = WRRESP;
        default:
            wnext = WRIDLE;
    endcase
end

// waddr
always @(posedge ACLK) begin
    if (ACLK_EN) begin
        if (aw_hs)
            waddr <= AWADDR[ADDR_BITS-1:0];
    end
end

//------------------------AXI read fsm-------------------
assign ARREADY = (rstate == RDIDLE);
assign RDATA   = rdata;
assign RRESP   = 2'b00;  // OKAY
assign RVALID  = (rstate == RDDATA);
assign ar_hs   = ARVALID & ARREADY;
assign raddr   = ARADDR[ADDR_BITS-1:0];

// rstate
always @(posedge ACLK) begin
    if (ARESET)
        rstate <= RDRESET;
    else if (ACLK_EN)
        rstate <= rnext;
end

// rnext
always @(*) begin
    case (rstate)
        RDIDLE:
            if (ARVALID)
                rnext = RDDATA;
            else
                rnext = RDIDLE;
        RDDATA:
            if (RREADY & RVALID)
                rnext = RDIDLE;
            else
                rnext = RDDATA;
        default:
            rnext = RDIDLE;
    endcase
end

// rdata
always @(posedge ACLK) begin
    if (ACLK_EN) begin
        if (ar_hs) begin
            rdata <= 'b0;
            case (raddr)
                ADDR_AP_CTRL: begin
                    rdata[0] <= int_ap_start;
                    rdata[1] <= int_task_ap_done;
                    rdata[2] <= int_ap_idle;
                    rdata[3] <= int_ap_ready;
                    rdata[7] <= int_auto_restart;
                    rdata[9] <= int_interrupt;
                end
                ADDR_GIE: begin
                    rdata <= int_gie;
                end
                ADDR_IER: begin
                    rdata <= int_ier;
                end
                ADDR_ISR: begin
                    rdata <= int_isr;
                end
                ADDR_IN_0_DATA_0: begin
                    rdata <= int_in_0[31:0];
                end
                ADDR_IN_0_DATA_1: begin
                    rdata <= int_in_0[63:32];
                end
                ADDR_IN_1_DATA_0: begin
                    rdata <= int_in_1[31:0];
                end
                ADDR_IN_1_DATA_1: begin
                    rdata <= int_in_1[63:32];
                end
                ADDR_IN_2_DATA_0: begin
                    rdata <= int_in_2[31:0];
                end
                ADDR_IN_2_DATA_1: begin
                    rdata <= int_in_2[63:32];
                end
                ADDR_IN_3_DATA_0: begin
                    rdata <= int_in_3[31:0];
                end
                ADDR_IN_3_DATA_1: begin
                    rdata <= int_in_3[63:32];
                end
                ADDR_IN_4_DATA_0: begin
                    rdata <= int_in_4[31:0];
                end
                ADDR_IN_4_DATA_1: begin
                    rdata <= int_in_4[63:32];
                end
                ADDR_IN_5_DATA_0: begin
                    rdata <= int_in_5[31:0];
                end
                ADDR_IN_5_DATA_1: begin
                    rdata <= int_in_5[63:32];
                end
                ADDR_IN_6_DATA_0: begin
                    rdata <= int_in_6[31:0];
                end
                ADDR_IN_6_DATA_1: begin
                    rdata <= int_in_6[63:32];
                end
                ADDR_IN_7_DATA_0: begin
                    rdata <= int_in_7[31:0];
                end
                ADDR_IN_7_DATA_1: begin
                    rdata <= int_in_7[63:32];
                end
                ADDR_IN_8_DATA_0: begin
                    rdata <= int_in_8[31:0];
                end
                ADDR_IN_8_DATA_1: begin
                    rdata <= int_in_8[63:32];
                end
                ADDR_IN_9_DATA_0: begin
                    rdata <= int_in_9[31:0];
                end
                ADDR_IN_9_DATA_1: begin
                    rdata <= int_in_9[63:32];
                end
                ADDR_IN_10_DATA_0: begin
                    rdata <= int_in_10[31:0];
                end
                ADDR_IN_10_DATA_1: begin
                    rdata <= int_in_10[63:32];
                end
                ADDR_IN_11_DATA_0: begin
                    rdata <= int_in_11[31:0];
                end
                ADDR_IN_11_DATA_1: begin
                    rdata <= int_in_11[63:32];
                end
                ADDR_IN_12_DATA_0: begin
                    rdata <= int_in_12[31:0];
                end
                ADDR_IN_12_DATA_1: begin
                    rdata <= int_in_12[63:32];
                end
                ADDR_IN_13_DATA_0: begin
                    rdata <= int_in_13[31:0];
                end
                ADDR_IN_13_DATA_1: begin
                    rdata <= int_in_13[63:32];
                end
                ADDR_IN_14_DATA_0: begin
                    rdata <= int_in_14[31:0];
                end
                ADDR_IN_14_DATA_1: begin
                    rdata <= int_in_14[63:32];
                end
                ADDR_IN_15_DATA_0: begin
                    rdata <= int_in_15[31:0];
                end
                ADDR_IN_15_DATA_1: begin
                    rdata <= int_in_15[63:32];
                end
                ADDR_IN_16_DATA_0: begin
                    rdata <= int_in_16[31:0];
                end
                ADDR_IN_16_DATA_1: begin
                    rdata <= int_in_16[63:32];
                end
                ADDR_IN_17_DATA_0: begin
                    rdata <= int_in_17[31:0];
                end
                ADDR_IN_17_DATA_1: begin
                    rdata <= int_in_17[63:32];
                end
                ADDR_L3_OUT_DIST_DATA_0: begin
                    rdata <= int_L3_out_dist[31:0];
                end
                ADDR_L3_OUT_DIST_DATA_1: begin
                    rdata <= int_L3_out_dist[63:32];
                end
                ADDR_L3_OUT_ID_DATA_0: begin
                    rdata <= int_L3_out_id[31:0];
                end
                ADDR_L3_OUT_ID_DATA_1: begin
                    rdata <= int_L3_out_id[63:32];
                end
            endcase
        end
    end
end


//------------------------Register logic-----------------
assign interrupt         = int_interrupt;
assign ap_start          = int_ap_start;
assign task_ap_done      = (ap_done && !auto_restart_status) || auto_restart_done;
assign task_ap_ready     = ap_ready && !int_auto_restart;
assign auto_restart_done = auto_restart_status && (ap_idle && !int_ap_idle);
assign in_0              = int_in_0;
assign in_1              = int_in_1;
assign in_2              = int_in_2;
assign in_3              = int_in_3;
assign in_4              = int_in_4;
assign in_5              = int_in_5;
assign in_6              = int_in_6;
assign in_7              = int_in_7;
assign in_8              = int_in_8;
assign in_9              = int_in_9;
assign in_10             = int_in_10;
assign in_11             = int_in_11;
assign in_12             = int_in_12;
assign in_13             = int_in_13;
assign in_14             = int_in_14;
assign in_15             = int_in_15;
assign in_16             = int_in_16;
assign in_17             = int_in_17;
assign L3_out_dist       = int_L3_out_dist;
assign L3_out_id         = int_L3_out_id;
// int_interrupt
always @(posedge ACLK) begin
    if (ARESET)
        int_interrupt <= 1'b0;
    else if (ACLK_EN) begin
        if (int_gie && (|int_isr))
            int_interrupt <= 1'b1;
        else
            int_interrupt <= 1'b0;
    end
end

// int_ap_start
always @(posedge ACLK) begin
    if (ARESET)
        int_ap_start <= 1'b0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AP_CTRL && WSTRB[0] && WDATA[0])
            int_ap_start <= 1'b1;
        else if (ap_done & int_auto_restart)
            int_ap_start <= 1'b1; // auto restart
        else
            int_ap_start <= 1'b0; // self clear
    end
end

// int_ap_done
always @(posedge ACLK) begin
    if (ARESET)
        int_ap_done <= 1'b0;
    else if (ACLK_EN) begin
            int_ap_done <= ap_done;
    end
end

// int_task_ap_done
always @(posedge ACLK) begin
    if (ARESET)
        int_task_ap_done <= 1'b0;
    else if (ACLK_EN) begin
        if (task_ap_done)
            int_task_ap_done <= 1'b1;
        else if (ar_hs && raddr == ADDR_AP_CTRL)
            int_task_ap_done <= 1'b0; // clear on read
    end
end

// int_ap_idle
always @(posedge ACLK) begin
    if (ARESET)
        int_ap_idle <= 1'b0;
    else if (ACLK_EN) begin
            int_ap_idle <= ap_idle;
    end
end

// int_ap_ready
always @(posedge ACLK) begin
    if (ARESET)
        int_ap_ready <= 1'b0;
    else if (ACLK_EN) begin
        if (task_ap_ready)
            int_ap_ready <= 1'b1;
        else if (ar_hs && raddr == ADDR_AP_CTRL)
            int_ap_ready <= 1'b0;
    end
end

// int_auto_restart
always @(posedge ACLK) begin
    if (ARESET)
        int_auto_restart <= 1'b0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_AP_CTRL && WSTRB[0])
            int_auto_restart <=  WDATA[7];
    end
end

// auto_restart_status
always @(posedge ACLK) begin
    if (ARESET)
        auto_restart_status <= 1'b0;
    else if (ACLK_EN) begin
        if (int_auto_restart)
            auto_restart_status <= 1'b1;
        else if (ap_idle)
            auto_restart_status <= 1'b0;
    end
end

// int_gie
always @(posedge ACLK) begin
    if (ARESET)
        int_gie <= 1'b0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_GIE && WSTRB[0])
            int_gie <= WDATA[0];
    end
end

// int_ier
always @(posedge ACLK) begin
    if (ARESET)
        int_ier <= 1'b0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IER && WSTRB[0])
            int_ier <= WDATA[0];
    end
end

// int_isr
always @(posedge ACLK) begin
    if (ARESET)
        int_isr <= 1'b0;
    else if (ACLK_EN) begin
        if (int_ier & ap_done)
            int_isr <= 1'b1;
        else if (ar_hs && raddr == ADDR_ISR)
            int_isr <= 1'b0; // clear on read
    end
end

// int_in_0[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_0[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_0_DATA_0)
            int_in_0[31:0] <= (WDATA[31:0] & wmask) | (int_in_0[31:0] & ~wmask);
    end
end

// int_in_0[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_0[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_0_DATA_1)
            int_in_0[63:32] <= (WDATA[31:0] & wmask) | (int_in_0[63:32] & ~wmask);
    end
end

// int_in_1[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_1[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_1_DATA_0)
            int_in_1[31:0] <= (WDATA[31:0] & wmask) | (int_in_1[31:0] & ~wmask);
    end
end

// int_in_1[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_1[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_1_DATA_1)
            int_in_1[63:32] <= (WDATA[31:0] & wmask) | (int_in_1[63:32] & ~wmask);
    end
end

// int_in_2[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_2[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_2_DATA_0)
            int_in_2[31:0] <= (WDATA[31:0] & wmask) | (int_in_2[31:0] & ~wmask);
    end
end

// int_in_2[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_2[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_2_DATA_1)
            int_in_2[63:32] <= (WDATA[31:0] & wmask) | (int_in_2[63:32] & ~wmask);
    end
end

// int_in_3[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_3[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_3_DATA_0)
            int_in_3[31:0] <= (WDATA[31:0] & wmask) | (int_in_3[31:0] & ~wmask);
    end
end

// int_in_3[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_3[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_3_DATA_1)
            int_in_3[63:32] <= (WDATA[31:0] & wmask) | (int_in_3[63:32] & ~wmask);
    end
end

// int_in_4[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_4[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_4_DATA_0)
            int_in_4[31:0] <= (WDATA[31:0] & wmask) | (int_in_4[31:0] & ~wmask);
    end
end

// int_in_4[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_4[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_4_DATA_1)
            int_in_4[63:32] <= (WDATA[31:0] & wmask) | (int_in_4[63:32] & ~wmask);
    end
end

// int_in_5[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_5[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_5_DATA_0)
            int_in_5[31:0] <= (WDATA[31:0] & wmask) | (int_in_5[31:0] & ~wmask);
    end
end

// int_in_5[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_5[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_5_DATA_1)
            int_in_5[63:32] <= (WDATA[31:0] & wmask) | (int_in_5[63:32] & ~wmask);
    end
end

// int_in_6[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_6[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_6_DATA_0)
            int_in_6[31:0] <= (WDATA[31:0] & wmask) | (int_in_6[31:0] & ~wmask);
    end
end

// int_in_6[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_6[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_6_DATA_1)
            int_in_6[63:32] <= (WDATA[31:0] & wmask) | (int_in_6[63:32] & ~wmask);
    end
end

// int_in_7[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_7[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_7_DATA_0)
            int_in_7[31:0] <= (WDATA[31:0] & wmask) | (int_in_7[31:0] & ~wmask);
    end
end

// int_in_7[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_7[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_7_DATA_1)
            int_in_7[63:32] <= (WDATA[31:0] & wmask) | (int_in_7[63:32] & ~wmask);
    end
end

// int_in_8[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_8[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_8_DATA_0)
            int_in_8[31:0] <= (WDATA[31:0] & wmask) | (int_in_8[31:0] & ~wmask);
    end
end

// int_in_8[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_8[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_8_DATA_1)
            int_in_8[63:32] <= (WDATA[31:0] & wmask) | (int_in_8[63:32] & ~wmask);
    end
end

// int_in_9[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_9[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_9_DATA_0)
            int_in_9[31:0] <= (WDATA[31:0] & wmask) | (int_in_9[31:0] & ~wmask);
    end
end

// int_in_9[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_9[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_9_DATA_1)
            int_in_9[63:32] <= (WDATA[31:0] & wmask) | (int_in_9[63:32] & ~wmask);
    end
end

// int_in_10[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_10[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_10_DATA_0)
            int_in_10[31:0] <= (WDATA[31:0] & wmask) | (int_in_10[31:0] & ~wmask);
    end
end

// int_in_10[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_10[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_10_DATA_1)
            int_in_10[63:32] <= (WDATA[31:0] & wmask) | (int_in_10[63:32] & ~wmask);
    end
end

// int_in_11[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_11[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_11_DATA_0)
            int_in_11[31:0] <= (WDATA[31:0] & wmask) | (int_in_11[31:0] & ~wmask);
    end
end

// int_in_11[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_11[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_11_DATA_1)
            int_in_11[63:32] <= (WDATA[31:0] & wmask) | (int_in_11[63:32] & ~wmask);
    end
end

// int_in_12[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_12[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_12_DATA_0)
            int_in_12[31:0] <= (WDATA[31:0] & wmask) | (int_in_12[31:0] & ~wmask);
    end
end

// int_in_12[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_12[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_12_DATA_1)
            int_in_12[63:32] <= (WDATA[31:0] & wmask) | (int_in_12[63:32] & ~wmask);
    end
end

// int_in_13[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_13[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_13_DATA_0)
            int_in_13[31:0] <= (WDATA[31:0] & wmask) | (int_in_13[31:0] & ~wmask);
    end
end

// int_in_13[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_13[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_13_DATA_1)
            int_in_13[63:32] <= (WDATA[31:0] & wmask) | (int_in_13[63:32] & ~wmask);
    end
end

// int_in_14[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_14[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_14_DATA_0)
            int_in_14[31:0] <= (WDATA[31:0] & wmask) | (int_in_14[31:0] & ~wmask);
    end
end

// int_in_14[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_14[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_14_DATA_1)
            int_in_14[63:32] <= (WDATA[31:0] & wmask) | (int_in_14[63:32] & ~wmask);
    end
end

// int_in_15[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_15[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_15_DATA_0)
            int_in_15[31:0] <= (WDATA[31:0] & wmask) | (int_in_15[31:0] & ~wmask);
    end
end

// int_in_15[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_15[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_15_DATA_1)
            int_in_15[63:32] <= (WDATA[31:0] & wmask) | (int_in_15[63:32] & ~wmask);
    end
end

// int_in_16[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_16[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_16_DATA_0)
            int_in_16[31:0] <= (WDATA[31:0] & wmask) | (int_in_16[31:0] & ~wmask);
    end
end

// int_in_16[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_16[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_16_DATA_1)
            int_in_16[63:32] <= (WDATA[31:0] & wmask) | (int_in_16[63:32] & ~wmask);
    end
end

// int_in_17[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_17[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_17_DATA_0)
            int_in_17[31:0] <= (WDATA[31:0] & wmask) | (int_in_17[31:0] & ~wmask);
    end
end

// int_in_17[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_in_17[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_IN_17_DATA_1)
            int_in_17[63:32] <= (WDATA[31:0] & wmask) | (int_in_17[63:32] & ~wmask);
    end
end

// int_L3_out_dist[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_L3_out_dist[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_L3_OUT_DIST_DATA_0)
            int_L3_out_dist[31:0] <= (WDATA[31:0] & wmask) | (int_L3_out_dist[31:0] & ~wmask);
    end
end

// int_L3_out_dist[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_L3_out_dist[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_L3_OUT_DIST_DATA_1)
            int_L3_out_dist[63:32] <= (WDATA[31:0] & wmask) | (int_L3_out_dist[63:32] & ~wmask);
    end
end

// int_L3_out_id[31:0]
always @(posedge ACLK) begin
    if (ARESET)
        int_L3_out_id[31:0] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_L3_OUT_ID_DATA_0)
            int_L3_out_id[31:0] <= (WDATA[31:0] & wmask) | (int_L3_out_id[31:0] & ~wmask);
    end
end

// int_L3_out_id[63:32]
always @(posedge ACLK) begin
    if (ARESET)
        int_L3_out_id[63:32] <= 0;
    else if (ACLK_EN) begin
        if (w_hs && waddr == ADDR_L3_OUT_ID_DATA_1)
            int_L3_out_id[63:32] <= (WDATA[31:0] & wmask) | (int_L3_out_id[63:32] & ~wmask);
    end
end

//synthesis translate_off
always @(posedge ACLK) begin
    if (ACLK_EN) begin
        if (int_gie & ~int_isr & int_ier & ap_done)
            $display ("// Interrupt Monitor : interrupt for ap_done detected @ \"%0t\"", $time);
    end
end
//synthesis translate_on

//------------------------Memory logic-------------------

endmodule
