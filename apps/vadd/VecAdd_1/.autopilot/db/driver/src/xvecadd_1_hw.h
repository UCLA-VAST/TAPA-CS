// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// control
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
// 0x10 : Data signal of a
//        bit 31~0 - a[31:0] (Read/Write)
// 0x14 : Data signal of a
//        bit 31~0 - a[63:32] (Read/Write)
// 0x18 : reserved
// 0x1c : Data signal of b
//        bit 31~0 - b[31:0] (Read/Write)
// 0x20 : Data signal of b
//        bit 31~0 - b[63:32] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of c
//        bit 31~0 - c[31:0] (Read/Write)
// 0x2c : Data signal of c
//        bit 31~0 - c[63:32] (Read/Write)
// 0x30 : reserved
// 0x34 : Data signal of n
//        bit 31~0 - n[31:0] (Read/Write)
// 0x38 : Data signal of n
//        bit 31~0 - n[63:32] (Read/Write)
// 0x3c : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XVECADD_1_CONTROL_ADDR_AP_CTRL 0x00
#define XVECADD_1_CONTROL_ADDR_GIE     0x04
#define XVECADD_1_CONTROL_ADDR_IER     0x08
#define XVECADD_1_CONTROL_ADDR_ISR     0x0c
#define XVECADD_1_CONTROL_ADDR_A_DATA  0x10
#define XVECADD_1_CONTROL_BITS_A_DATA  64
#define XVECADD_1_CONTROL_ADDR_B_DATA  0x1c
#define XVECADD_1_CONTROL_BITS_B_DATA  64
#define XVECADD_1_CONTROL_ADDR_C_DATA  0x28
#define XVECADD_1_CONTROL_BITS_C_DATA  64
#define XVECADD_1_CONTROL_ADDR_N_DATA  0x34
#define XVECADD_1_CONTROL_BITS_N_DATA  64

