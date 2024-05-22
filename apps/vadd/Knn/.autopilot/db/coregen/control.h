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

#define CONTROL_ADDR_AP_CTRL          0x00
#define CONTROL_ADDR_GIE              0x04
#define CONTROL_ADDR_IER              0x08
#define CONTROL_ADDR_ISR              0x0c
#define CONTROL_ADDR_IN_0_DATA        0x10
#define CONTROL_BITS_IN_0_DATA        64
#define CONTROL_ADDR_IN_1_DATA        0x1c
#define CONTROL_BITS_IN_1_DATA        64
#define CONTROL_ADDR_IN_2_DATA        0x28
#define CONTROL_BITS_IN_2_DATA        64
#define CONTROL_ADDR_IN_3_DATA        0x34
#define CONTROL_BITS_IN_3_DATA        64
#define CONTROL_ADDR_IN_4_DATA        0x40
#define CONTROL_BITS_IN_4_DATA        64
#define CONTROL_ADDR_IN_5_DATA        0x4c
#define CONTROL_BITS_IN_5_DATA        64
#define CONTROL_ADDR_IN_6_DATA        0x58
#define CONTROL_BITS_IN_6_DATA        64
#define CONTROL_ADDR_IN_7_DATA        0x64
#define CONTROL_BITS_IN_7_DATA        64
#define CONTROL_ADDR_IN_8_DATA        0x70
#define CONTROL_BITS_IN_8_DATA        64
#define CONTROL_ADDR_IN_9_DATA        0x7c
#define CONTROL_BITS_IN_9_DATA        64
#define CONTROL_ADDR_IN_10_DATA       0x88
#define CONTROL_BITS_IN_10_DATA       64
#define CONTROL_ADDR_IN_11_DATA       0x94
#define CONTROL_BITS_IN_11_DATA       64
#define CONTROL_ADDR_IN_12_DATA       0xa0
#define CONTROL_BITS_IN_12_DATA       64
#define CONTROL_ADDR_IN_13_DATA       0xac
#define CONTROL_BITS_IN_13_DATA       64
#define CONTROL_ADDR_IN_14_DATA       0xb8
#define CONTROL_BITS_IN_14_DATA       64
#define CONTROL_ADDR_IN_15_DATA       0xc4
#define CONTROL_BITS_IN_15_DATA       64
#define CONTROL_ADDR_IN_16_DATA       0xd0
#define CONTROL_BITS_IN_16_DATA       64
#define CONTROL_ADDR_IN_17_DATA       0xdc
#define CONTROL_BITS_IN_17_DATA       64
#define CONTROL_ADDR_L3_OUT_DIST_DATA 0xe8
#define CONTROL_BITS_L3_OUT_DIST_DATA 64
#define CONTROL_ADDR_L3_OUT_ID_DATA   0xf4
#define CONTROL_BITS_L3_OUT_ID_DATA   64
