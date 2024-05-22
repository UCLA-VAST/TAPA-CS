-- ==============================================================
-- Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
-- Tool Version Limit: 2022.04
-- Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
-- ==============================================================
library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.NUMERIC_STD.all;

entity Knn_control_s_axi is
generic (
    C_S_AXI_ADDR_WIDTH    : INTEGER := 8;
    C_S_AXI_DATA_WIDTH    : INTEGER := 32);
port (
    ACLK                  :in   STD_LOGIC;
    ARESET                :in   STD_LOGIC;
    ACLK_EN               :in   STD_LOGIC;
    AWADDR                :in   STD_LOGIC_VECTOR(C_S_AXI_ADDR_WIDTH-1 downto 0);
    AWVALID               :in   STD_LOGIC;
    AWREADY               :out  STD_LOGIC;
    WDATA                 :in   STD_LOGIC_VECTOR(C_S_AXI_DATA_WIDTH-1 downto 0);
    WSTRB                 :in   STD_LOGIC_VECTOR(C_S_AXI_DATA_WIDTH/8-1 downto 0);
    WVALID                :in   STD_LOGIC;
    WREADY                :out  STD_LOGIC;
    BRESP                 :out  STD_LOGIC_VECTOR(1 downto 0);
    BVALID                :out  STD_LOGIC;
    BREADY                :in   STD_LOGIC;
    ARADDR                :in   STD_LOGIC_VECTOR(C_S_AXI_ADDR_WIDTH-1 downto 0);
    ARVALID               :in   STD_LOGIC;
    ARREADY               :out  STD_LOGIC;
    RDATA                 :out  STD_LOGIC_VECTOR(C_S_AXI_DATA_WIDTH-1 downto 0);
    RRESP                 :out  STD_LOGIC_VECTOR(1 downto 0);
    RVALID                :out  STD_LOGIC;
    RREADY                :in   STD_LOGIC;
    interrupt             :out  STD_LOGIC;
    in_0                  :out  STD_LOGIC_VECTOR(63 downto 0);
    in_1                  :out  STD_LOGIC_VECTOR(63 downto 0);
    in_2                  :out  STD_LOGIC_VECTOR(63 downto 0);
    in_3                  :out  STD_LOGIC_VECTOR(63 downto 0);
    in_4                  :out  STD_LOGIC_VECTOR(63 downto 0);
    in_5                  :out  STD_LOGIC_VECTOR(63 downto 0);
    in_6                  :out  STD_LOGIC_VECTOR(63 downto 0);
    in_7                  :out  STD_LOGIC_VECTOR(63 downto 0);
    in_8                  :out  STD_LOGIC_VECTOR(63 downto 0);
    in_9                  :out  STD_LOGIC_VECTOR(63 downto 0);
    in_10                 :out  STD_LOGIC_VECTOR(63 downto 0);
    in_11                 :out  STD_LOGIC_VECTOR(63 downto 0);
    in_12                 :out  STD_LOGIC_VECTOR(63 downto 0);
    in_13                 :out  STD_LOGIC_VECTOR(63 downto 0);
    in_14                 :out  STD_LOGIC_VECTOR(63 downto 0);
    in_15                 :out  STD_LOGIC_VECTOR(63 downto 0);
    in_16                 :out  STD_LOGIC_VECTOR(63 downto 0);
    in_17                 :out  STD_LOGIC_VECTOR(63 downto 0);
    L3_out_dist           :out  STD_LOGIC_VECTOR(63 downto 0);
    L3_out_id             :out  STD_LOGIC_VECTOR(63 downto 0);
    ap_start              :out  STD_LOGIC;
    ap_done               :in   STD_LOGIC;
    ap_ready              :in   STD_LOGIC;
    ap_idle               :in   STD_LOGIC
);
end entity Knn_control_s_axi;

-- ------------------------Address Info-------------------
-- 0x00 : Control signals
--        bit 0  - ap_start (Read/Write/SC)
--        bit 1  - ap_done (Read/COR)
--        bit 2  - ap_idle (Read)
--        bit 3  - ap_ready (Read/COR)
--        bit 7  - auto_restart (Read/Write)
--        bit 9  - interrupt (Read)
--        others - reserved
-- 0x04 : Global Interrupt Enable Register
--        bit 0  - Global Interrupt Enable (Read/Write)
--        others - reserved
-- 0x08 : IP Interrupt Enable Register (Read/Write)
--        bit 0 - enable ap_done interrupt (Read/Write)
--        others - reserved
-- 0x0c : IP Interrupt Status Register (Read/COR)
--        bit 0 - ap_done (Read/COR)
--        others - reserved
-- 0x10 : Data signal of in_0
--        bit 31~0 - in_0[31:0] (Read/Write)
-- 0x14 : Data signal of in_0
--        bit 31~0 - in_0[63:32] (Read/Write)
-- 0x18 : reserved
-- 0x1c : Data signal of in_1
--        bit 31~0 - in_1[31:0] (Read/Write)
-- 0x20 : Data signal of in_1
--        bit 31~0 - in_1[63:32] (Read/Write)
-- 0x24 : reserved
-- 0x28 : Data signal of in_2
--        bit 31~0 - in_2[31:0] (Read/Write)
-- 0x2c : Data signal of in_2
--        bit 31~0 - in_2[63:32] (Read/Write)
-- 0x30 : reserved
-- 0x34 : Data signal of in_3
--        bit 31~0 - in_3[31:0] (Read/Write)
-- 0x38 : Data signal of in_3
--        bit 31~0 - in_3[63:32] (Read/Write)
-- 0x3c : reserved
-- 0x40 : Data signal of in_4
--        bit 31~0 - in_4[31:0] (Read/Write)
-- 0x44 : Data signal of in_4
--        bit 31~0 - in_4[63:32] (Read/Write)
-- 0x48 : reserved
-- 0x4c : Data signal of in_5
--        bit 31~0 - in_5[31:0] (Read/Write)
-- 0x50 : Data signal of in_5
--        bit 31~0 - in_5[63:32] (Read/Write)
-- 0x54 : reserved
-- 0x58 : Data signal of in_6
--        bit 31~0 - in_6[31:0] (Read/Write)
-- 0x5c : Data signal of in_6
--        bit 31~0 - in_6[63:32] (Read/Write)
-- 0x60 : reserved
-- 0x64 : Data signal of in_7
--        bit 31~0 - in_7[31:0] (Read/Write)
-- 0x68 : Data signal of in_7
--        bit 31~0 - in_7[63:32] (Read/Write)
-- 0x6c : reserved
-- 0x70 : Data signal of in_8
--        bit 31~0 - in_8[31:0] (Read/Write)
-- 0x74 : Data signal of in_8
--        bit 31~0 - in_8[63:32] (Read/Write)
-- 0x78 : reserved
-- 0x7c : Data signal of in_9
--        bit 31~0 - in_9[31:0] (Read/Write)
-- 0x80 : Data signal of in_9
--        bit 31~0 - in_9[63:32] (Read/Write)
-- 0x84 : reserved
-- 0x88 : Data signal of in_10
--        bit 31~0 - in_10[31:0] (Read/Write)
-- 0x8c : Data signal of in_10
--        bit 31~0 - in_10[63:32] (Read/Write)
-- 0x90 : reserved
-- 0x94 : Data signal of in_11
--        bit 31~0 - in_11[31:0] (Read/Write)
-- 0x98 : Data signal of in_11
--        bit 31~0 - in_11[63:32] (Read/Write)
-- 0x9c : reserved
-- 0xa0 : Data signal of in_12
--        bit 31~0 - in_12[31:0] (Read/Write)
-- 0xa4 : Data signal of in_12
--        bit 31~0 - in_12[63:32] (Read/Write)
-- 0xa8 : reserved
-- 0xac : Data signal of in_13
--        bit 31~0 - in_13[31:0] (Read/Write)
-- 0xb0 : Data signal of in_13
--        bit 31~0 - in_13[63:32] (Read/Write)
-- 0xb4 : reserved
-- 0xb8 : Data signal of in_14
--        bit 31~0 - in_14[31:0] (Read/Write)
-- 0xbc : Data signal of in_14
--        bit 31~0 - in_14[63:32] (Read/Write)
-- 0xc0 : reserved
-- 0xc4 : Data signal of in_15
--        bit 31~0 - in_15[31:0] (Read/Write)
-- 0xc8 : Data signal of in_15
--        bit 31~0 - in_15[63:32] (Read/Write)
-- 0xcc : reserved
-- 0xd0 : Data signal of in_16
--        bit 31~0 - in_16[31:0] (Read/Write)
-- 0xd4 : Data signal of in_16
--        bit 31~0 - in_16[63:32] (Read/Write)
-- 0xd8 : reserved
-- 0xdc : Data signal of in_17
--        bit 31~0 - in_17[31:0] (Read/Write)
-- 0xe0 : Data signal of in_17
--        bit 31~0 - in_17[63:32] (Read/Write)
-- 0xe4 : reserved
-- 0xe8 : Data signal of L3_out_dist
--        bit 31~0 - L3_out_dist[31:0] (Read/Write)
-- 0xec : Data signal of L3_out_dist
--        bit 31~0 - L3_out_dist[63:32] (Read/Write)
-- 0xf0 : reserved
-- 0xf4 : Data signal of L3_out_id
--        bit 31~0 - L3_out_id[31:0] (Read/Write)
-- 0xf8 : Data signal of L3_out_id
--        bit 31~0 - L3_out_id[63:32] (Read/Write)
-- 0xfc : reserved
-- (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

architecture behave of Knn_control_s_axi is
    type states is (wridle, wrdata, wrresp, wrreset, rdidle, rddata, rdreset);  -- read and write fsm states
    signal wstate  : states := wrreset;
    signal rstate  : states := rdreset;
    signal wnext, rnext: states;
    constant ADDR_AP_CTRL            : INTEGER := 16#00#;
    constant ADDR_GIE                : INTEGER := 16#04#;
    constant ADDR_IER                : INTEGER := 16#08#;
    constant ADDR_ISR                : INTEGER := 16#0c#;
    constant ADDR_IN_0_DATA_0        : INTEGER := 16#10#;
    constant ADDR_IN_0_DATA_1        : INTEGER := 16#14#;
    constant ADDR_IN_0_CTRL          : INTEGER := 16#18#;
    constant ADDR_IN_1_DATA_0        : INTEGER := 16#1c#;
    constant ADDR_IN_1_DATA_1        : INTEGER := 16#20#;
    constant ADDR_IN_1_CTRL          : INTEGER := 16#24#;
    constant ADDR_IN_2_DATA_0        : INTEGER := 16#28#;
    constant ADDR_IN_2_DATA_1        : INTEGER := 16#2c#;
    constant ADDR_IN_2_CTRL          : INTEGER := 16#30#;
    constant ADDR_IN_3_DATA_0        : INTEGER := 16#34#;
    constant ADDR_IN_3_DATA_1        : INTEGER := 16#38#;
    constant ADDR_IN_3_CTRL          : INTEGER := 16#3c#;
    constant ADDR_IN_4_DATA_0        : INTEGER := 16#40#;
    constant ADDR_IN_4_DATA_1        : INTEGER := 16#44#;
    constant ADDR_IN_4_CTRL          : INTEGER := 16#48#;
    constant ADDR_IN_5_DATA_0        : INTEGER := 16#4c#;
    constant ADDR_IN_5_DATA_1        : INTEGER := 16#50#;
    constant ADDR_IN_5_CTRL          : INTEGER := 16#54#;
    constant ADDR_IN_6_DATA_0        : INTEGER := 16#58#;
    constant ADDR_IN_6_DATA_1        : INTEGER := 16#5c#;
    constant ADDR_IN_6_CTRL          : INTEGER := 16#60#;
    constant ADDR_IN_7_DATA_0        : INTEGER := 16#64#;
    constant ADDR_IN_7_DATA_1        : INTEGER := 16#68#;
    constant ADDR_IN_7_CTRL          : INTEGER := 16#6c#;
    constant ADDR_IN_8_DATA_0        : INTEGER := 16#70#;
    constant ADDR_IN_8_DATA_1        : INTEGER := 16#74#;
    constant ADDR_IN_8_CTRL          : INTEGER := 16#78#;
    constant ADDR_IN_9_DATA_0        : INTEGER := 16#7c#;
    constant ADDR_IN_9_DATA_1        : INTEGER := 16#80#;
    constant ADDR_IN_9_CTRL          : INTEGER := 16#84#;
    constant ADDR_IN_10_DATA_0       : INTEGER := 16#88#;
    constant ADDR_IN_10_DATA_1       : INTEGER := 16#8c#;
    constant ADDR_IN_10_CTRL         : INTEGER := 16#90#;
    constant ADDR_IN_11_DATA_0       : INTEGER := 16#94#;
    constant ADDR_IN_11_DATA_1       : INTEGER := 16#98#;
    constant ADDR_IN_11_CTRL         : INTEGER := 16#9c#;
    constant ADDR_IN_12_DATA_0       : INTEGER := 16#a0#;
    constant ADDR_IN_12_DATA_1       : INTEGER := 16#a4#;
    constant ADDR_IN_12_CTRL         : INTEGER := 16#a8#;
    constant ADDR_IN_13_DATA_0       : INTEGER := 16#ac#;
    constant ADDR_IN_13_DATA_1       : INTEGER := 16#b0#;
    constant ADDR_IN_13_CTRL         : INTEGER := 16#b4#;
    constant ADDR_IN_14_DATA_0       : INTEGER := 16#b8#;
    constant ADDR_IN_14_DATA_1       : INTEGER := 16#bc#;
    constant ADDR_IN_14_CTRL         : INTEGER := 16#c0#;
    constant ADDR_IN_15_DATA_0       : INTEGER := 16#c4#;
    constant ADDR_IN_15_DATA_1       : INTEGER := 16#c8#;
    constant ADDR_IN_15_CTRL         : INTEGER := 16#cc#;
    constant ADDR_IN_16_DATA_0       : INTEGER := 16#d0#;
    constant ADDR_IN_16_DATA_1       : INTEGER := 16#d4#;
    constant ADDR_IN_16_CTRL         : INTEGER := 16#d8#;
    constant ADDR_IN_17_DATA_0       : INTEGER := 16#dc#;
    constant ADDR_IN_17_DATA_1       : INTEGER := 16#e0#;
    constant ADDR_IN_17_CTRL         : INTEGER := 16#e4#;
    constant ADDR_L3_OUT_DIST_DATA_0 : INTEGER := 16#e8#;
    constant ADDR_L3_OUT_DIST_DATA_1 : INTEGER := 16#ec#;
    constant ADDR_L3_OUT_DIST_CTRL   : INTEGER := 16#f0#;
    constant ADDR_L3_OUT_ID_DATA_0   : INTEGER := 16#f4#;
    constant ADDR_L3_OUT_ID_DATA_1   : INTEGER := 16#f8#;
    constant ADDR_L3_OUT_ID_CTRL     : INTEGER := 16#fc#;
    constant ADDR_BITS         : INTEGER := 8;

    signal waddr               : UNSIGNED(ADDR_BITS-1 downto 0);
    signal wmask               : UNSIGNED(C_S_AXI_DATA_WIDTH-1 downto 0);
    signal aw_hs               : STD_LOGIC;
    signal w_hs                : STD_LOGIC;
    signal rdata_data          : UNSIGNED(C_S_AXI_DATA_WIDTH-1 downto 0);
    signal ar_hs               : STD_LOGIC;
    signal raddr               : UNSIGNED(ADDR_BITS-1 downto 0);
    signal AWREADY_t           : STD_LOGIC;
    signal WREADY_t            : STD_LOGIC;
    signal ARREADY_t           : STD_LOGIC;
    signal RVALID_t            : STD_LOGIC;
    -- internal registers
    signal int_ap_idle         : STD_LOGIC := '0';
    signal int_ap_ready        : STD_LOGIC := '0';
    signal task_ap_ready       : STD_LOGIC;
    signal int_ap_done         : STD_LOGIC := '0';
    signal task_ap_done        : STD_LOGIC;
    signal int_task_ap_done    : STD_LOGIC := '0';
    signal int_ap_start        : STD_LOGIC := '0';
    signal int_interrupt       : STD_LOGIC := '0';
    signal int_auto_restart    : STD_LOGIC := '0';
    signal auto_restart_status : STD_LOGIC := '0';
    signal auto_restart_done   : STD_LOGIC;
    signal int_gie             : STD_LOGIC := '0';
    signal int_ier             : STD_LOGIC := '0';
    signal int_isr             : STD_LOGIC := '0';
    signal int_in_0            : UNSIGNED(63 downto 0) := (others => '0');
    signal int_in_1            : UNSIGNED(63 downto 0) := (others => '0');
    signal int_in_2            : UNSIGNED(63 downto 0) := (others => '0');
    signal int_in_3            : UNSIGNED(63 downto 0) := (others => '0');
    signal int_in_4            : UNSIGNED(63 downto 0) := (others => '0');
    signal int_in_5            : UNSIGNED(63 downto 0) := (others => '0');
    signal int_in_6            : UNSIGNED(63 downto 0) := (others => '0');
    signal int_in_7            : UNSIGNED(63 downto 0) := (others => '0');
    signal int_in_8            : UNSIGNED(63 downto 0) := (others => '0');
    signal int_in_9            : UNSIGNED(63 downto 0) := (others => '0');
    signal int_in_10           : UNSIGNED(63 downto 0) := (others => '0');
    signal int_in_11           : UNSIGNED(63 downto 0) := (others => '0');
    signal int_in_12           : UNSIGNED(63 downto 0) := (others => '0');
    signal int_in_13           : UNSIGNED(63 downto 0) := (others => '0');
    signal int_in_14           : UNSIGNED(63 downto 0) := (others => '0');
    signal int_in_15           : UNSIGNED(63 downto 0) := (others => '0');
    signal int_in_16           : UNSIGNED(63 downto 0) := (others => '0');
    signal int_in_17           : UNSIGNED(63 downto 0) := (others => '0');
    signal int_L3_out_dist     : UNSIGNED(63 downto 0) := (others => '0');
    signal int_L3_out_id       : UNSIGNED(63 downto 0) := (others => '0');


begin
-- ----------------------- Instantiation------------------


-- ----------------------- AXI WRITE ---------------------
    AWREADY_t <=  '1' when wstate = wridle else '0';
    AWREADY   <=  AWREADY_t;
    WREADY_t  <=  '1' when wstate = wrdata else '0';
    WREADY    <=  WREADY_t;
    BRESP     <=  "00";  -- OKAY
    BVALID    <=  '1' when wstate = wrresp else '0';
    wmask     <=  (31 downto 24 => WSTRB(3), 23 downto 16 => WSTRB(2), 15 downto 8 => WSTRB(1), 7 downto 0 => WSTRB(0));
    aw_hs     <=  AWVALID and AWREADY_t;
    w_hs      <=  WVALID and WREADY_t;

    -- write FSM
    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                wstate <= wrreset;
            elsif (ACLK_EN = '1') then
                wstate <= wnext;
            end if;
        end if;
    end process;

    process (wstate, AWVALID, WVALID, BREADY)
    begin
        case (wstate) is
        when wridle =>
            if (AWVALID = '1') then
                wnext <= wrdata;
            else
                wnext <= wridle;
            end if;
        when wrdata =>
            if (WVALID = '1') then
                wnext <= wrresp;
            else
                wnext <= wrdata;
            end if;
        when wrresp =>
            if (BREADY = '1') then
                wnext <= wridle;
            else
                wnext <= wrresp;
            end if;
        when others =>
            wnext <= wridle;
        end case;
    end process;

    waddr_proc : process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (aw_hs = '1') then
                    waddr <= UNSIGNED(AWADDR(ADDR_BITS-1 downto 0));
                end if;
            end if;
        end if;
    end process;

-- ----------------------- AXI READ ----------------------
    ARREADY_t <= '1' when (rstate = rdidle) else '0';
    ARREADY <= ARREADY_t;
    RDATA   <= STD_LOGIC_VECTOR(rdata_data);
    RRESP   <= "00";  -- OKAY
    RVALID_t  <= '1' when (rstate = rddata) else '0';
    RVALID    <= RVALID_t;
    ar_hs   <= ARVALID and ARREADY_t;
    raddr   <= UNSIGNED(ARADDR(ADDR_BITS-1 downto 0));

    -- read FSM
    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                rstate <= rdreset;
            elsif (ACLK_EN = '1') then
                rstate <= rnext;
            end if;
        end if;
    end process;

    process (rstate, ARVALID, RREADY, RVALID_t)
    begin
        case (rstate) is
        when rdidle =>
            if (ARVALID = '1') then
                rnext <= rddata;
            else
                rnext <= rdidle;
            end if;
        when rddata =>
            if (RREADY = '1' and RVALID_t = '1') then
                rnext <= rdidle;
            else
                rnext <= rddata;
            end if;
        when others =>
            rnext <= rdidle;
        end case;
    end process;

    rdata_proc : process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (ar_hs = '1') then
                    rdata_data <= (others => '0');
                    case (TO_INTEGER(raddr)) is
                    when ADDR_AP_CTRL =>
                        rdata_data(9) <= int_interrupt;
                        rdata_data(7) <= int_auto_restart;
                        rdata_data(3) <= int_ap_ready;
                        rdata_data(2) <= int_ap_idle;
                        rdata_data(1) <= int_task_ap_done;
                        rdata_data(0) <= int_ap_start;
                    when ADDR_GIE =>
                        rdata_data(0) <= int_gie;
                    when ADDR_IER =>
                        rdata_data(0) <= int_ier;
                    when ADDR_ISR =>
                        rdata_data(0) <= int_isr;
                    when ADDR_IN_0_DATA_0 =>
                        rdata_data <= RESIZE(int_in_0(31 downto 0), 32);
                    when ADDR_IN_0_DATA_1 =>
                        rdata_data <= RESIZE(int_in_0(63 downto 32), 32);
                    when ADDR_IN_1_DATA_0 =>
                        rdata_data <= RESIZE(int_in_1(31 downto 0), 32);
                    when ADDR_IN_1_DATA_1 =>
                        rdata_data <= RESIZE(int_in_1(63 downto 32), 32);
                    when ADDR_IN_2_DATA_0 =>
                        rdata_data <= RESIZE(int_in_2(31 downto 0), 32);
                    when ADDR_IN_2_DATA_1 =>
                        rdata_data <= RESIZE(int_in_2(63 downto 32), 32);
                    when ADDR_IN_3_DATA_0 =>
                        rdata_data <= RESIZE(int_in_3(31 downto 0), 32);
                    when ADDR_IN_3_DATA_1 =>
                        rdata_data <= RESIZE(int_in_3(63 downto 32), 32);
                    when ADDR_IN_4_DATA_0 =>
                        rdata_data <= RESIZE(int_in_4(31 downto 0), 32);
                    when ADDR_IN_4_DATA_1 =>
                        rdata_data <= RESIZE(int_in_4(63 downto 32), 32);
                    when ADDR_IN_5_DATA_0 =>
                        rdata_data <= RESIZE(int_in_5(31 downto 0), 32);
                    when ADDR_IN_5_DATA_1 =>
                        rdata_data <= RESIZE(int_in_5(63 downto 32), 32);
                    when ADDR_IN_6_DATA_0 =>
                        rdata_data <= RESIZE(int_in_6(31 downto 0), 32);
                    when ADDR_IN_6_DATA_1 =>
                        rdata_data <= RESIZE(int_in_6(63 downto 32), 32);
                    when ADDR_IN_7_DATA_0 =>
                        rdata_data <= RESIZE(int_in_7(31 downto 0), 32);
                    when ADDR_IN_7_DATA_1 =>
                        rdata_data <= RESIZE(int_in_7(63 downto 32), 32);
                    when ADDR_IN_8_DATA_0 =>
                        rdata_data <= RESIZE(int_in_8(31 downto 0), 32);
                    when ADDR_IN_8_DATA_1 =>
                        rdata_data <= RESIZE(int_in_8(63 downto 32), 32);
                    when ADDR_IN_9_DATA_0 =>
                        rdata_data <= RESIZE(int_in_9(31 downto 0), 32);
                    when ADDR_IN_9_DATA_1 =>
                        rdata_data <= RESIZE(int_in_9(63 downto 32), 32);
                    when ADDR_IN_10_DATA_0 =>
                        rdata_data <= RESIZE(int_in_10(31 downto 0), 32);
                    when ADDR_IN_10_DATA_1 =>
                        rdata_data <= RESIZE(int_in_10(63 downto 32), 32);
                    when ADDR_IN_11_DATA_0 =>
                        rdata_data <= RESIZE(int_in_11(31 downto 0), 32);
                    when ADDR_IN_11_DATA_1 =>
                        rdata_data <= RESIZE(int_in_11(63 downto 32), 32);
                    when ADDR_IN_12_DATA_0 =>
                        rdata_data <= RESIZE(int_in_12(31 downto 0), 32);
                    when ADDR_IN_12_DATA_1 =>
                        rdata_data <= RESIZE(int_in_12(63 downto 32), 32);
                    when ADDR_IN_13_DATA_0 =>
                        rdata_data <= RESIZE(int_in_13(31 downto 0), 32);
                    when ADDR_IN_13_DATA_1 =>
                        rdata_data <= RESIZE(int_in_13(63 downto 32), 32);
                    when ADDR_IN_14_DATA_0 =>
                        rdata_data <= RESIZE(int_in_14(31 downto 0), 32);
                    when ADDR_IN_14_DATA_1 =>
                        rdata_data <= RESIZE(int_in_14(63 downto 32), 32);
                    when ADDR_IN_15_DATA_0 =>
                        rdata_data <= RESIZE(int_in_15(31 downto 0), 32);
                    when ADDR_IN_15_DATA_1 =>
                        rdata_data <= RESIZE(int_in_15(63 downto 32), 32);
                    when ADDR_IN_16_DATA_0 =>
                        rdata_data <= RESIZE(int_in_16(31 downto 0), 32);
                    when ADDR_IN_16_DATA_1 =>
                        rdata_data <= RESIZE(int_in_16(63 downto 32), 32);
                    when ADDR_IN_17_DATA_0 =>
                        rdata_data <= RESIZE(int_in_17(31 downto 0), 32);
                    when ADDR_IN_17_DATA_1 =>
                        rdata_data <= RESIZE(int_in_17(63 downto 32), 32);
                    when ADDR_L3_OUT_DIST_DATA_0 =>
                        rdata_data <= RESIZE(int_L3_out_dist(31 downto 0), 32);
                    when ADDR_L3_OUT_DIST_DATA_1 =>
                        rdata_data <= RESIZE(int_L3_out_dist(63 downto 32), 32);
                    when ADDR_L3_OUT_ID_DATA_0 =>
                        rdata_data <= RESIZE(int_L3_out_id(31 downto 0), 32);
                    when ADDR_L3_OUT_ID_DATA_1 =>
                        rdata_data <= RESIZE(int_L3_out_id(63 downto 32), 32);
                    when others =>
                        NULL;
                    end case;
                end if;
            end if;
        end if;
    end process;

-- ----------------------- Register logic ----------------
    interrupt            <= int_interrupt;
    ap_start             <= int_ap_start;
    task_ap_done         <= (ap_done and not auto_restart_status) or auto_restart_done;
    task_ap_ready        <= ap_ready and not int_auto_restart;
    auto_restart_done    <= auto_restart_status and (ap_idle and not int_ap_idle);
    in_0                 <= STD_LOGIC_VECTOR(int_in_0);
    in_1                 <= STD_LOGIC_VECTOR(int_in_1);
    in_2                 <= STD_LOGIC_VECTOR(int_in_2);
    in_3                 <= STD_LOGIC_VECTOR(int_in_3);
    in_4                 <= STD_LOGIC_VECTOR(int_in_4);
    in_5                 <= STD_LOGIC_VECTOR(int_in_5);
    in_6                 <= STD_LOGIC_VECTOR(int_in_6);
    in_7                 <= STD_LOGIC_VECTOR(int_in_7);
    in_8                 <= STD_LOGIC_VECTOR(int_in_8);
    in_9                 <= STD_LOGIC_VECTOR(int_in_9);
    in_10                <= STD_LOGIC_VECTOR(int_in_10);
    in_11                <= STD_LOGIC_VECTOR(int_in_11);
    in_12                <= STD_LOGIC_VECTOR(int_in_12);
    in_13                <= STD_LOGIC_VECTOR(int_in_13);
    in_14                <= STD_LOGIC_VECTOR(int_in_14);
    in_15                <= STD_LOGIC_VECTOR(int_in_15);
    in_16                <= STD_LOGIC_VECTOR(int_in_16);
    in_17                <= STD_LOGIC_VECTOR(int_in_17);
    L3_out_dist          <= STD_LOGIC_VECTOR(int_L3_out_dist);
    L3_out_id            <= STD_LOGIC_VECTOR(int_L3_out_id);

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_interrupt <= '0';
            elsif (ACLK_EN = '1') then
                if (int_gie = '1' and (int_isr) = '1') then
                    int_interrupt <= '1';
                else
                    int_interrupt <= '0';
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_ap_start <= '0';
            elsif (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AP_CTRL and WSTRB(0) = '1' and WDATA(0) = '1') then
                    int_ap_start <= '1';
                elsif (ap_done = '1' and int_auto_restart = '1') then
                    int_ap_start <= '1'; -- auto restart
                else
                    int_ap_start <= '0'; -- self clear
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_ap_done <= '0';
            elsif (ACLK_EN = '1') then
                if (true) then
                    int_ap_done <= ap_done;
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_task_ap_done <= '0';
            elsif (ACLK_EN = '1') then
                if (task_ap_done = '1') then
                    int_task_ap_done <= '1';
                elsif (ar_hs = '1' and raddr = ADDR_AP_CTRL) then
                    int_task_ap_done <= '0'; -- clear on read
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_ap_idle <= '0';
            elsif (ACLK_EN = '1') then
                if (true) then
                    int_ap_idle <= ap_idle;
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_ap_ready <= '0';
            elsif (ACLK_EN = '1') then
                if (task_ap_ready = '1') then
                    int_ap_ready <= '1';
                elsif (ar_hs = '1' and raddr = ADDR_AP_CTRL) then
                    int_ap_ready <= '0';
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_auto_restart <= '0';
            elsif (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_AP_CTRL and WSTRB(0) = '1') then
                    int_auto_restart <= WDATA(7);
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                auto_restart_status <= '0';
            elsif (ACLK_EN = '1') then
                if (int_auto_restart = '1') then
                    auto_restart_status <= '1';
                elsif (ap_idle = '1') then
                    auto_restart_status <= '0';
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_gie <= '0';
            elsif (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_GIE and WSTRB(0) = '1') then
                    int_gie <= WDATA(0);
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_ier <= '0';
            elsif (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IER and WSTRB(0) = '1') then
                    int_ier <= WDATA(0);
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ARESET = '1') then
                int_isr <= '0';
            elsif (ACLK_EN = '1') then
                if (int_ier = '1' and ap_done = '1') then
                    int_isr <= '1';
                elsif (ar_hs = '1' and raddr = ADDR_ISR) then
                    int_isr <= '0'; -- clear on read
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_0_DATA_0) then
                    int_in_0(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_0(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_0_DATA_1) then
                    int_in_0(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_0(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_1_DATA_0) then
                    int_in_1(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_1(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_1_DATA_1) then
                    int_in_1(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_1(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_2_DATA_0) then
                    int_in_2(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_2(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_2_DATA_1) then
                    int_in_2(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_2(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_3_DATA_0) then
                    int_in_3(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_3(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_3_DATA_1) then
                    int_in_3(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_3(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_4_DATA_0) then
                    int_in_4(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_4(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_4_DATA_1) then
                    int_in_4(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_4(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_5_DATA_0) then
                    int_in_5(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_5(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_5_DATA_1) then
                    int_in_5(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_5(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_6_DATA_0) then
                    int_in_6(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_6(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_6_DATA_1) then
                    int_in_6(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_6(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_7_DATA_0) then
                    int_in_7(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_7(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_7_DATA_1) then
                    int_in_7(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_7(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_8_DATA_0) then
                    int_in_8(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_8(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_8_DATA_1) then
                    int_in_8(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_8(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_9_DATA_0) then
                    int_in_9(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_9(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_9_DATA_1) then
                    int_in_9(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_9(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_10_DATA_0) then
                    int_in_10(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_10(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_10_DATA_1) then
                    int_in_10(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_10(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_11_DATA_0) then
                    int_in_11(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_11(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_11_DATA_1) then
                    int_in_11(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_11(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_12_DATA_0) then
                    int_in_12(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_12(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_12_DATA_1) then
                    int_in_12(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_12(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_13_DATA_0) then
                    int_in_13(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_13(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_13_DATA_1) then
                    int_in_13(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_13(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_14_DATA_0) then
                    int_in_14(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_14(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_14_DATA_1) then
                    int_in_14(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_14(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_15_DATA_0) then
                    int_in_15(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_15(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_15_DATA_1) then
                    int_in_15(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_15(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_16_DATA_0) then
                    int_in_16(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_16(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_16_DATA_1) then
                    int_in_16(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_16(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_17_DATA_0) then
                    int_in_17(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_17(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_IN_17_DATA_1) then
                    int_in_17(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_in_17(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_L3_OUT_DIST_DATA_0) then
                    int_L3_out_dist(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_L3_out_dist(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_L3_OUT_DIST_DATA_1) then
                    int_L3_out_dist(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_L3_out_dist(63 downto 32));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_L3_OUT_ID_DATA_0) then
                    int_L3_out_id(31 downto 0) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_L3_out_id(31 downto 0));
                end if;
            end if;
        end if;
    end process;

    process (ACLK)
    begin
        if (ACLK'event and ACLK = '1') then
            if (ACLK_EN = '1') then
                if (w_hs = '1' and waddr = ADDR_L3_OUT_ID_DATA_1) then
                    int_L3_out_id(63 downto 32) <= (UNSIGNED(WDATA(31 downto 0)) and wmask(31 downto 0)) or ((not wmask(31 downto 0)) and int_L3_out_id(63 downto 32));
                end if;
            end if;
        end if;
    end process;


-- ----------------------- Memory logic ------------------

end architecture behave;
