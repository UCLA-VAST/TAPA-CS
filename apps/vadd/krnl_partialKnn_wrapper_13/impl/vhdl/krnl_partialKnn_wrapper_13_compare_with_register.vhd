-- ==============================================================
-- RTL generated by Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
-- Version: 2022.1
-- Copyright (C) Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
-- 
-- ===========================================================

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity krnl_partialKnn_wrapper_13_compare_with_register is
port (
    ap_clk : IN STD_LOGIC;
    ap_rst : IN STD_LOGIC;
    in_1 : IN STD_LOGIC_VECTOR (31 downto 0);
    in_2 : IN STD_LOGIC_VECTOR (31 downto 0);
    ap_return : OUT STD_LOGIC_VECTOR (0 downto 0);
    ap_ce : IN STD_LOGIC );
end;


architecture behav of krnl_partialKnn_wrapper_13_compare_with_register is 
    constant ap_const_logic_1 : STD_LOGIC := '1';
    constant ap_const_logic_0 : STD_LOGIC := '0';
    constant ap_const_boolean_1 : BOOLEAN := true;
    constant ap_const_boolean_0 : BOOLEAN := false;
    constant ap_const_lv32_17 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000010111";
    constant ap_const_lv32_1E : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000011110";
    constant ap_const_lv8_FF : STD_LOGIC_VECTOR (7 downto 0) := "11111111";
    constant ap_const_lv23_0 : STD_LOGIC_VECTOR (22 downto 0) := "00000000000000000000000";
    constant ap_const_lv5_4 : STD_LOGIC_VECTOR (4 downto 0) := "00100";

attribute shreg_extract : string;
    signal ap_block_state1_pp0_stage0_iter0 : BOOLEAN;
    signal ap_block_state2_pp0_stage0_iter1 : BOOLEAN;
    signal ap_block_state3_pp0_stage0_iter2 : BOOLEAN;
    signal ap_block_pp0_stage0_11001 : BOOLEAN;
    signal icmp_ln83_fu_82_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal icmp_ln83_reg_136 : STD_LOGIC_VECTOR (0 downto 0);
    signal icmp_ln83_1_fu_88_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal icmp_ln83_1_reg_141 : STD_LOGIC_VECTOR (0 downto 0);
    signal icmp_ln83_2_fu_94_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal icmp_ln83_2_reg_146 : STD_LOGIC_VECTOR (0 downto 0);
    signal icmp_ln83_3_fu_100_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal icmp_ln83_3_reg_151 : STD_LOGIC_VECTOR (0 downto 0);
    signal and_ln83_1_fu_120_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal and_ln83_1_reg_156 : STD_LOGIC_VECTOR (0 downto 0);
    signal ap_block_pp0_stage0 : BOOLEAN;
    signal bitcast_ln83_fu_46_p1 : STD_LOGIC_VECTOR (31 downto 0);
    signal bitcast_ln83_1_fu_64_p1 : STD_LOGIC_VECTOR (31 downto 0);
    signal tmp_fu_50_p4 : STD_LOGIC_VECTOR (7 downto 0);
    signal trunc_ln83_fu_60_p1 : STD_LOGIC_VECTOR (22 downto 0);
    signal tmp_s_fu_68_p4 : STD_LOGIC_VECTOR (7 downto 0);
    signal trunc_ln83_1_fu_78_p1 : STD_LOGIC_VECTOR (22 downto 0);
    signal or_ln83_fu_106_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal or_ln83_1_fu_110_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal and_ln83_fu_114_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal grp_fu_40_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal grp_fu_40_ce : STD_LOGIC;
    signal ap_block_pp0_stage0_00001 : BOOLEAN;
    signal ap_ce_reg : STD_LOGIC;
    signal in_1_int_reg : STD_LOGIC_VECTOR (31 downto 0);
    signal in_2_int_reg : STD_LOGIC_VECTOR (31 downto 0);
    signal ap_return_int_reg : STD_LOGIC_VECTOR (0 downto 0);

    component krnl_partialKnn_wrapper_13_fcmp_32ns_32ns_1_2_no_dsp_1 IS
    generic (
        ID : INTEGER;
        NUM_STAGE : INTEGER;
        din0_WIDTH : INTEGER;
        din1_WIDTH : INTEGER;
        dout_WIDTH : INTEGER );
    port (
        clk : IN STD_LOGIC;
        reset : IN STD_LOGIC;
        din0 : IN STD_LOGIC_VECTOR (31 downto 0);
        din1 : IN STD_LOGIC_VECTOR (31 downto 0);
        ce : IN STD_LOGIC;
        opcode : IN STD_LOGIC_VECTOR (4 downto 0);
        dout : OUT STD_LOGIC_VECTOR (0 downto 0) );
    end component;



begin
    fcmp_32ns_32ns_1_2_no_dsp_1_U361 : component krnl_partialKnn_wrapper_13_fcmp_32ns_32ns_1_2_no_dsp_1
    generic map (
        ID => 1,
        NUM_STAGE => 2,
        din0_WIDTH => 32,
        din1_WIDTH => 32,
        dout_WIDTH => 1)
    port map (
        clk => ap_clk,
        reset => ap_rst,
        din0 => in_1_int_reg,
        din1 => in_2_int_reg,
        ce => grp_fu_40_ce,
        opcode => ap_const_lv5_4,
        dout => grp_fu_40_p2);





    ap_ce_reg_assign_proc : process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            ap_ce_reg <= ap_ce;
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_const_logic_1 = ap_ce_reg))) then
                and_ln83_1_reg_156 <= and_ln83_1_fu_120_p2;
                icmp_ln83_1_reg_141 <= icmp_ln83_1_fu_88_p2;
                icmp_ln83_2_reg_146 <= icmp_ln83_2_fu_94_p2;
                icmp_ln83_3_reg_151 <= icmp_ln83_3_fu_100_p2;
                icmp_ln83_reg_136 <= icmp_ln83_fu_82_p2;
            end if;
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if ((ap_const_logic_1 = ap_ce_reg)) then
                ap_return_int_reg <= and_ln83_1_reg_156;
            end if;
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if ((ap_const_logic_1 = ap_ce)) then
                in_1_int_reg <= in_1;
                in_2_int_reg <= in_2;
            end if;
        end if;
    end process;
    and_ln83_1_fu_120_p2 <= (grp_fu_40_p2 and and_ln83_fu_114_p2);
    and_ln83_fu_114_p2 <= (or_ln83_fu_106_p2 and or_ln83_1_fu_110_p2);
        ap_block_pp0_stage0 <= not((ap_const_boolean_1 = ap_const_boolean_1));
        ap_block_pp0_stage0_00001 <= not((ap_const_boolean_1 = ap_const_boolean_1));
        ap_block_pp0_stage0_11001 <= not((ap_const_boolean_1 = ap_const_boolean_1));
        ap_block_state1_pp0_stage0_iter0 <= not((ap_const_boolean_1 = ap_const_boolean_1));
        ap_block_state2_pp0_stage0_iter1 <= not((ap_const_boolean_1 = ap_const_boolean_1));
        ap_block_state3_pp0_stage0_iter2 <= not((ap_const_boolean_1 = ap_const_boolean_1));

    ap_return_assign_proc : process(and_ln83_1_reg_156, ap_ce_reg, ap_return_int_reg)
    begin
        if ((ap_const_logic_0 = ap_ce_reg)) then 
            ap_return <= ap_return_int_reg;
        elsif ((ap_const_logic_1 = ap_ce_reg)) then 
            ap_return <= and_ln83_1_reg_156;
        else 
            ap_return <= "X";
        end if; 
    end process;

    bitcast_ln83_1_fu_64_p1 <= in_2_int_reg;
    bitcast_ln83_fu_46_p1 <= in_1_int_reg;

    grp_fu_40_ce_assign_proc : process(ap_block_pp0_stage0_11001, ap_ce_reg)
    begin
        if (((ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_const_logic_1 = ap_ce_reg))) then 
            grp_fu_40_ce <= ap_const_logic_1;
        else 
            grp_fu_40_ce <= ap_const_logic_0;
        end if; 
    end process;

    icmp_ln83_1_fu_88_p2 <= "1" when (trunc_ln83_fu_60_p1 = ap_const_lv23_0) else "0";
    icmp_ln83_2_fu_94_p2 <= "0" when (tmp_s_fu_68_p4 = ap_const_lv8_FF) else "1";
    icmp_ln83_3_fu_100_p2 <= "1" when (trunc_ln83_1_fu_78_p1 = ap_const_lv23_0) else "0";
    icmp_ln83_fu_82_p2 <= "0" when (tmp_fu_50_p4 = ap_const_lv8_FF) else "1";
    or_ln83_1_fu_110_p2 <= (icmp_ln83_3_reg_151 or icmp_ln83_2_reg_146);
    or_ln83_fu_106_p2 <= (icmp_ln83_reg_136 or icmp_ln83_1_reg_141);
    tmp_fu_50_p4 <= bitcast_ln83_fu_46_p1(30 downto 23);
    tmp_s_fu_68_p4 <= bitcast_ln83_1_fu_64_p1(30 downto 23);
    trunc_ln83_1_fu_78_p1 <= bitcast_ln83_1_fu_64_p1(23 - 1 downto 0);
    trunc_ln83_fu_60_p1 <= bitcast_ln83_fu_46_p1(23 - 1 downto 0);
end behav;