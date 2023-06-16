// ==============================================================
// RTL generated by Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Version: 2022.1
// Copyright (C) Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

(* CORE_GENERATION_INFO="Module8Func_Module8Func,hls_ip_2022_1,{HLS_INPUT_TYPE=cxx,HLS_INPUT_FLOAT=0,HLS_INPUT_FIXED=0,HLS_INPUT_PART=xcu55c-fsvh2892-2L-e,HLS_INPUT_CLOCK=3.333000,HLS_INPUT_ARCH=others,HLS_SYN_CLOCK=3.186090,HLS_SYN_LAT=-1,HLS_SYN_TPT=none,HLS_SYN_MEM=0,HLS_SYN_DSP=0,HLS_SYN_FF=73,HLS_SYN_LUT=195,HLS_VERSION=2022_1}" *)

module Module8Func (
        ap_clk,
        ap_rst_n,
        ap_start,
        ap_done,
        ap_idle,
        ap_ready,
        dram_t0_bank_0_fifo_din,
        dram_t0_bank_0_fifo_full_n,
        dram_t0_bank_0_fifo_write,
        fifo_ld_0_s_dout,
        fifo_ld_0_s_empty_n,
        fifo_ld_0_s_read,
        fifo_ld_0_peek_dout,
        fifo_ld_0_peek_empty_n,
        fifo_ld_0_peek_read,
        fifo_ld_1_s_dout,
        fifo_ld_1_s_empty_n,
        fifo_ld_1_s_read,
        fifo_ld_1_peek_dout,
        fifo_ld_1_peek_empty_n,
        fifo_ld_1_peek_read
);

parameter    ap_ST_fsm_state1 = 4'd1;
parameter    ap_ST_fsm_state2 = 4'd2;
parameter    ap_ST_fsm_state3 = 4'd4;
parameter    ap_ST_fsm_state4 = 4'd8;

input   ap_clk;
input   ap_rst_n;
input   ap_start;
output   ap_done;
output   ap_idle;
output   ap_ready;
output  [64:0] dram_t0_bank_0_fifo_din;
input   dram_t0_bank_0_fifo_full_n;
output   dram_t0_bank_0_fifo_write;
input  [32:0] fifo_ld_0_s_dout;
input   fifo_ld_0_s_empty_n;
output   fifo_ld_0_s_read;
input  [32:0] fifo_ld_0_peek_dout;
input   fifo_ld_0_peek_empty_n;
output   fifo_ld_0_peek_read;
input  [32:0] fifo_ld_1_s_dout;
input   fifo_ld_1_s_empty_n;
output   fifo_ld_1_s_read;
input  [32:0] fifo_ld_1_peek_dout;
input   fifo_ld_1_peek_empty_n;
output   fifo_ld_1_peek_read;

reg ap_done;
reg ap_idle;
reg ap_ready;
reg[64:0] dram_t0_bank_0_fifo_din;
reg dram_t0_bank_0_fifo_write;
reg fifo_ld_0_s_read;
reg fifo_ld_0_peek_read;
reg fifo_ld_1_s_read;
reg fifo_ld_1_peek_read;

 reg    ap_rst_n_inv;
(* fsm_encoding = "none" *) reg   [3:0] ap_CS_fsm;
wire    ap_CS_fsm_state1;
reg    dram_t0_bank_0_fifo_blk_n;
wire    ap_CS_fsm_state4;
wire    grp_Module8Func_Pipeline_module_8_epoch_fu_88_ap_start;
wire    grp_Module8Func_Pipeline_module_8_epoch_fu_88_ap_done;
wire    grp_Module8Func_Pipeline_module_8_epoch_fu_88_ap_idle;
wire    grp_Module8Func_Pipeline_module_8_epoch_fu_88_ap_ready;
wire   [64:0] grp_Module8Func_Pipeline_module_8_epoch_fu_88_dram_t0_bank_0_fifo_din;
wire    grp_Module8Func_Pipeline_module_8_epoch_fu_88_dram_t0_bank_0_fifo_write;
wire    grp_Module8Func_Pipeline_module_8_epoch_fu_88_fifo_ld_0_s_read;
wire    grp_Module8Func_Pipeline_module_8_epoch_fu_88_fifo_ld_1_s_read;
wire    grp_Module8Func_Pipeline_module_8_epoch_fu_88_fifo_ld_0_peek_read;
wire    grp_Module8Func_Pipeline_module_8_epoch_fu_88_fifo_ld_1_peek_read;
reg    grp_Module8Func_Pipeline_module_8_epoch_fu_88_ap_start_reg;
wire    ap_CS_fsm_state2;
wire    ap_CS_fsm_state3;
reg   [3:0] ap_NS_fsm;
reg    ap_ST_fsm_state1_blk;
wire    ap_ST_fsm_state2_blk;
reg    ap_ST_fsm_state3_blk;
reg    ap_ST_fsm_state4_blk;
wire    ap_ce_reg;

// power-on initialization
initial begin
#0 ap_CS_fsm = 4'd1;
#0 grp_Module8Func_Pipeline_module_8_epoch_fu_88_ap_start_reg = 1'b0;
end

Module8Func_Module8Func_Pipeline_module_8_epoch grp_Module8Func_Pipeline_module_8_epoch_fu_88(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst_n_inv),
    .ap_start(grp_Module8Func_Pipeline_module_8_epoch_fu_88_ap_start),
    .ap_done(grp_Module8Func_Pipeline_module_8_epoch_fu_88_ap_done),
    .ap_idle(grp_Module8Func_Pipeline_module_8_epoch_fu_88_ap_idle),
    .ap_ready(grp_Module8Func_Pipeline_module_8_epoch_fu_88_ap_ready),
    .dram_t0_bank_0_fifo_din(grp_Module8Func_Pipeline_module_8_epoch_fu_88_dram_t0_bank_0_fifo_din),
    .dram_t0_bank_0_fifo_full_n(dram_t0_bank_0_fifo_full_n),
    .dram_t0_bank_0_fifo_write(grp_Module8Func_Pipeline_module_8_epoch_fu_88_dram_t0_bank_0_fifo_write),
    .fifo_ld_0_s_dout(fifo_ld_0_s_dout),
    .fifo_ld_0_s_empty_n(fifo_ld_0_s_empty_n),
    .fifo_ld_0_s_read(grp_Module8Func_Pipeline_module_8_epoch_fu_88_fifo_ld_0_s_read),
    .fifo_ld_1_s_dout(fifo_ld_1_s_dout),
    .fifo_ld_1_s_empty_n(fifo_ld_1_s_empty_n),
    .fifo_ld_1_s_read(grp_Module8Func_Pipeline_module_8_epoch_fu_88_fifo_ld_1_s_read),
    .fifo_ld_0_peek_dout(fifo_ld_0_peek_dout),
    .fifo_ld_0_peek_empty_n(fifo_ld_0_peek_empty_n),
    .fifo_ld_0_peek_read(grp_Module8Func_Pipeline_module_8_epoch_fu_88_fifo_ld_0_peek_read),
    .fifo_ld_1_peek_dout(fifo_ld_1_peek_dout),
    .fifo_ld_1_peek_empty_n(fifo_ld_1_peek_empty_n),
    .fifo_ld_1_peek_read(grp_Module8Func_Pipeline_module_8_epoch_fu_88_fifo_ld_1_peek_read)
);

always @ (posedge ap_clk) begin
    if (ap_rst_n_inv == 1'b1) begin
        ap_CS_fsm <= ap_ST_fsm_state1;
    end else begin
        ap_CS_fsm <= ap_NS_fsm;
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst_n_inv == 1'b1) begin
        grp_Module8Func_Pipeline_module_8_epoch_fu_88_ap_start_reg <= 1'b0;
    end else begin
        if ((1'b1 == ap_CS_fsm_state2)) begin
            grp_Module8Func_Pipeline_module_8_epoch_fu_88_ap_start_reg <= 1'b1;
        end else if ((grp_Module8Func_Pipeline_module_8_epoch_fu_88_ap_ready == 1'b1)) begin
            grp_Module8Func_Pipeline_module_8_epoch_fu_88_ap_start_reg <= 1'b0;
        end
    end
end

always @ (*) begin
    if ((ap_start == 1'b0)) begin
        ap_ST_fsm_state1_blk = 1'b1;
    end else begin
        ap_ST_fsm_state1_blk = 1'b0;
    end
end

assign ap_ST_fsm_state2_blk = 1'b0;

always @ (*) begin
    if ((grp_Module8Func_Pipeline_module_8_epoch_fu_88_ap_done == 1'b0)) begin
        ap_ST_fsm_state3_blk = 1'b1;
    end else begin
        ap_ST_fsm_state3_blk = 1'b0;
    end
end

always @ (*) begin
    if ((dram_t0_bank_0_fifo_full_n == 1'b0)) begin
        ap_ST_fsm_state4_blk = 1'b1;
    end else begin
        ap_ST_fsm_state4_blk = 1'b0;
    end
end

always @ (*) begin
    if (((dram_t0_bank_0_fifo_full_n == 1'b1) & (1'b1 == ap_CS_fsm_state4))) begin
        ap_done = 1'b1;
    end else begin
        ap_done = 1'b0;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b0))) begin
        ap_idle = 1'b1;
    end else begin
        ap_idle = 1'b0;
    end
end

always @ (*) begin
    if (((dram_t0_bank_0_fifo_full_n == 1'b1) & (1'b1 == ap_CS_fsm_state4))) begin
        ap_ready = 1'b1;
    end else begin
        ap_ready = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state4)) begin
        dram_t0_bank_0_fifo_blk_n = dram_t0_bank_0_fifo_full_n;
    end else begin
        dram_t0_bank_0_fifo_blk_n = 1'b1;
    end
end

always @ (*) begin
    if (((dram_t0_bank_0_fifo_full_n == 1'b1) & (1'b1 == ap_CS_fsm_state4))) begin
        dram_t0_bank_0_fifo_din = 65'd18446744073709551616;
    end else if ((1'b1 == ap_CS_fsm_state3)) begin
        dram_t0_bank_0_fifo_din = grp_Module8Func_Pipeline_module_8_epoch_fu_88_dram_t0_bank_0_fifo_din;
    end else begin
        dram_t0_bank_0_fifo_din = grp_Module8Func_Pipeline_module_8_epoch_fu_88_dram_t0_bank_0_fifo_din;
    end
end

always @ (*) begin
    if (((dram_t0_bank_0_fifo_full_n == 1'b1) & (1'b1 == ap_CS_fsm_state4))) begin
        dram_t0_bank_0_fifo_write = 1'b1;
    end else if ((1'b1 == ap_CS_fsm_state3)) begin
        dram_t0_bank_0_fifo_write = grp_Module8Func_Pipeline_module_8_epoch_fu_88_dram_t0_bank_0_fifo_write;
    end else begin
        dram_t0_bank_0_fifo_write = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state3)) begin
        fifo_ld_0_peek_read = grp_Module8Func_Pipeline_module_8_epoch_fu_88_fifo_ld_0_peek_read;
    end else begin
        fifo_ld_0_peek_read = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state3)) begin
        fifo_ld_0_s_read = grp_Module8Func_Pipeline_module_8_epoch_fu_88_fifo_ld_0_s_read;
    end else begin
        fifo_ld_0_s_read = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state3)) begin
        fifo_ld_1_peek_read = grp_Module8Func_Pipeline_module_8_epoch_fu_88_fifo_ld_1_peek_read;
    end else begin
        fifo_ld_1_peek_read = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state3)) begin
        fifo_ld_1_s_read = grp_Module8Func_Pipeline_module_8_epoch_fu_88_fifo_ld_1_s_read;
    end else begin
        fifo_ld_1_s_read = 1'b0;
    end
end

always @ (*) begin
    case (ap_CS_fsm)
        ap_ST_fsm_state1 : begin
            if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1))) begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end
        end
        ap_ST_fsm_state2 : begin
            ap_NS_fsm = ap_ST_fsm_state3;
        end
        ap_ST_fsm_state3 : begin
            if (((grp_Module8Func_Pipeline_module_8_epoch_fu_88_ap_done == 1'b1) & (1'b1 == ap_CS_fsm_state3))) begin
                ap_NS_fsm = ap_ST_fsm_state4;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state3;
            end
        end
        ap_ST_fsm_state4 : begin
            if (((dram_t0_bank_0_fifo_full_n == 1'b1) & (1'b1 == ap_CS_fsm_state4))) begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state4;
            end
        end
        default : begin
            ap_NS_fsm = 'bx;
        end
    endcase
end

assign ap_CS_fsm_state1 = ap_CS_fsm[32'd0];

assign ap_CS_fsm_state2 = ap_CS_fsm[32'd1];

assign ap_CS_fsm_state3 = ap_CS_fsm[32'd2];

assign ap_CS_fsm_state4 = ap_CS_fsm[32'd3];

always @ (*) begin
    ap_rst_n_inv = ~ap_rst_n;
end

assign grp_Module8Func_Pipeline_module_8_epoch_fu_88_ap_start = grp_Module8Func_Pipeline_module_8_epoch_fu_88_ap_start_reg;

endmodule //Module8Func
