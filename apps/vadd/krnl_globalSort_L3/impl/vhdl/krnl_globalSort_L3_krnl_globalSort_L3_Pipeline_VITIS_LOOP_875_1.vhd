-- ==============================================================
-- RTL generated by Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
-- Version: 2022.1
-- Copyright (C) Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
-- 
-- ===========================================================

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity krnl_globalSort_L3_krnl_globalSort_L3_Pipeline_VITIS_LOOP_875_1 is
port (
    ap_clk : IN STD_LOGIC;
    ap_rst : IN STD_LOGIC;
    ap_start : IN STD_LOGIC;
    ap_done : OUT STD_LOGIC;
    ap_idle : OUT STD_LOGIC;
    ap_ready : OUT STD_LOGIC;
    in_dist0_s_dout : IN STD_LOGIC_VECTOR (44 downto 0);
    in_dist0_s_empty_n : IN STD_LOGIC;
    in_dist0_s_read : OUT STD_LOGIC;
    in_dist1_s_dout : IN STD_LOGIC_VECTOR (44 downto 0);
    in_dist1_s_empty_n : IN STD_LOGIC;
    in_dist1_s_read : OUT STD_LOGIC;
    local_kNearstDist_partial_1928_out : OUT STD_LOGIC_VECTOR (31 downto 0);
    local_kNearstDist_partial_1928_out_ap_vld : OUT STD_LOGIC;
    local_kNearstDist_partial_1827_out : OUT STD_LOGIC_VECTOR (31 downto 0);
    local_kNearstDist_partial_1827_out_ap_vld : OUT STD_LOGIC;
    local_kNearstDist_partial_1726_out : OUT STD_LOGIC_VECTOR (31 downto 0);
    local_kNearstDist_partial_1726_out_ap_vld : OUT STD_LOGIC;
    local_kNearstDist_partial_1625_out : OUT STD_LOGIC_VECTOR (31 downto 0);
    local_kNearstDist_partial_1625_out_ap_vld : OUT STD_LOGIC;
    local_kNearstDist_partial_1524_out : OUT STD_LOGIC_VECTOR (31 downto 0);
    local_kNearstDist_partial_1524_out_ap_vld : OUT STD_LOGIC;
    local_kNearstDist_partial_1423_out : OUT STD_LOGIC_VECTOR (31 downto 0);
    local_kNearstDist_partial_1423_out_ap_vld : OUT STD_LOGIC;
    local_kNearstDist_partial_1322_out : OUT STD_LOGIC_VECTOR (31 downto 0);
    local_kNearstDist_partial_1322_out_ap_vld : OUT STD_LOGIC;
    local_kNearstDist_partial_1221_out : OUT STD_LOGIC_VECTOR (31 downto 0);
    local_kNearstDist_partial_1221_out_ap_vld : OUT STD_LOGIC;
    local_kNearstDist_partial_1120_out : OUT STD_LOGIC_VECTOR (31 downto 0);
    local_kNearstDist_partial_1120_out_ap_vld : OUT STD_LOGIC;
    local_kNearstDist_partial_1019_out : OUT STD_LOGIC_VECTOR (31 downto 0);
    local_kNearstDist_partial_1019_out_ap_vld : OUT STD_LOGIC;
    local_kNearstDist_partial_918_out : OUT STD_LOGIC_VECTOR (31 downto 0);
    local_kNearstDist_partial_918_out_ap_vld : OUT STD_LOGIC;
    local_kNearstDist_partial_817_out : OUT STD_LOGIC_VECTOR (31 downto 0);
    local_kNearstDist_partial_817_out_ap_vld : OUT STD_LOGIC;
    local_kNearstDist_partial_716_out : OUT STD_LOGIC_VECTOR (31 downto 0);
    local_kNearstDist_partial_716_out_ap_vld : OUT STD_LOGIC;
    local_kNearstDist_partial_615_out : OUT STD_LOGIC_VECTOR (31 downto 0);
    local_kNearstDist_partial_615_out_ap_vld : OUT STD_LOGIC;
    local_kNearstDist_partial_514_out : OUT STD_LOGIC_VECTOR (31 downto 0);
    local_kNearstDist_partial_514_out_ap_vld : OUT STD_LOGIC;
    local_kNearstDist_partial_413_out : OUT STD_LOGIC_VECTOR (31 downto 0);
    local_kNearstDist_partial_413_out_ap_vld : OUT STD_LOGIC;
    local_kNearstDist_partial_312_out : OUT STD_LOGIC_VECTOR (31 downto 0);
    local_kNearstDist_partial_312_out_ap_vld : OUT STD_LOGIC;
    local_kNearstDist_partial_211_out : OUT STD_LOGIC_VECTOR (31 downto 0);
    local_kNearstDist_partial_211_out_ap_vld : OUT STD_LOGIC;
    local_kNearstDist_partial_110_out : OUT STD_LOGIC_VECTOR (31 downto 0);
    local_kNearstDist_partial_110_out_ap_vld : OUT STD_LOGIC;
    local_kNearstDist_partial1_out : OUT STD_LOGIC_VECTOR (31 downto 0);
    local_kNearstDist_partial1_out_ap_vld : OUT STD_LOGIC );
end;


architecture behav of krnl_globalSort_L3_krnl_globalSort_L3_Pipeline_VITIS_LOOP_875_1 is 
    constant ap_const_logic_1 : STD_LOGIC := '1';
    constant ap_const_logic_0 : STD_LOGIC := '0';
    constant ap_ST_fsm_pp0_stage0 : STD_LOGIC_VECTOR (0 downto 0) := "1";
    constant ap_const_lv32_0 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000000000";
    constant ap_const_boolean_1 : BOOLEAN := true;
    constant ap_const_boolean_0 : BOOLEAN := false;
    constant ap_const_lv1_1 : STD_LOGIC_VECTOR (0 downto 0) := "1";
    constant ap_const_lv4_0 : STD_LOGIC_VECTOR (3 downto 0) := "0000";
    constant ap_const_lv1_0 : STD_LOGIC_VECTOR (0 downto 0) := "0";
    constant ap_const_lv4_1 : STD_LOGIC_VECTOR (3 downto 0) := "0001";
    constant ap_const_lv4_2 : STD_LOGIC_VECTOR (3 downto 0) := "0010";
    constant ap_const_lv4_3 : STD_LOGIC_VECTOR (3 downto 0) := "0011";
    constant ap_const_lv4_4 : STD_LOGIC_VECTOR (3 downto 0) := "0100";
    constant ap_const_lv4_5 : STD_LOGIC_VECTOR (3 downto 0) := "0101";
    constant ap_const_lv4_6 : STD_LOGIC_VECTOR (3 downto 0) := "0110";
    constant ap_const_lv4_7 : STD_LOGIC_VECTOR (3 downto 0) := "0111";
    constant ap_const_lv4_8 : STD_LOGIC_VECTOR (3 downto 0) := "1000";
    constant ap_const_lv4_F : STD_LOGIC_VECTOR (3 downto 0) := "1111";
    constant ap_const_lv4_E : STD_LOGIC_VECTOR (3 downto 0) := "1110";
    constant ap_const_lv4_D : STD_LOGIC_VECTOR (3 downto 0) := "1101";
    constant ap_const_lv4_C : STD_LOGIC_VECTOR (3 downto 0) := "1100";
    constant ap_const_lv4_B : STD_LOGIC_VECTOR (3 downto 0) := "1011";
    constant ap_const_lv4_A : STD_LOGIC_VECTOR (3 downto 0) := "1010";
    constant ap_const_lv4_9 : STD_LOGIC_VECTOR (3 downto 0) := "1001";

attribute shreg_extract : string;
    signal ap_CS_fsm : STD_LOGIC_VECTOR (0 downto 0) := "1";
    attribute fsm_encoding : string;
    attribute fsm_encoding of ap_CS_fsm : signal is "none";
    signal ap_CS_fsm_pp0_stage0 : STD_LOGIC;
    attribute fsm_encoding of ap_CS_fsm_pp0_stage0 : signal is "none";
    signal ap_enable_reg_pp0_iter0 : STD_LOGIC;
    signal ap_enable_reg_pp0_iter1 : STD_LOGIC := '0';
    signal ap_idle_pp0 : STD_LOGIC;
    signal ap_block_state1_pp0_stage0_iter0 : BOOLEAN;
    signal ap_block_state2_pp0_stage0_iter1 : BOOLEAN;
    signal ap_block_pp0_stage0_subdone : BOOLEAN;
    signal icmp_ln875_fu_334_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal ap_condition_exit_pp0_iter0_stage0 : STD_LOGIC;
    signal ap_loop_exit_ready : STD_LOGIC;
    signal ap_ready_int : STD_LOGIC;
    signal in_dist1_s_blk_n : STD_LOGIC;
    signal ap_block_pp0_stage0 : BOOLEAN;
    signal in_dist0_s_blk_n : STD_LOGIC;
    signal i_2_reg_674 : STD_LOGIC_VECTOR (3 downto 0);
    signal ap_block_pp0_stage0_11001 : BOOLEAN;
    signal i_fu_90 : STD_LOGIC_VECTOR (3 downto 0);
    signal add_ln875_fu_340_p2 : STD_LOGIC_VECTOR (3 downto 0);
    signal ap_loop_init : STD_LOGIC;
    signal ap_sig_allocacmp_i_2 : STD_LOGIC_VECTOR (3 downto 0);
    signal local_kNearstDist_partial_2_fu_94 : STD_LOGIC_VECTOR (31 downto 0);
    signal local_kNearstDist_partial_fu_355_p1 : STD_LOGIC_VECTOR (31 downto 0);
    signal local_kNearstDist_partial_3_fu_98 : STD_LOGIC_VECTOR (31 downto 0);
    signal local_kNearstDist_partial_4_fu_102 : STD_LOGIC_VECTOR (31 downto 0);
    signal local_kNearstDist_partial_5_fu_106 : STD_LOGIC_VECTOR (31 downto 0);
    signal local_kNearstDist_partial_6_fu_110 : STD_LOGIC_VECTOR (31 downto 0);
    signal local_kNearstDist_partial_7_fu_114 : STD_LOGIC_VECTOR (31 downto 0);
    signal local_kNearstDist_partial_8_fu_118 : STD_LOGIC_VECTOR (31 downto 0);
    signal local_kNearstDist_partial_9_fu_122 : STD_LOGIC_VECTOR (31 downto 0);
    signal local_kNearstDist_partial_10_fu_126 : STD_LOGIC_VECTOR (31 downto 0);
    signal local_kNearstDist_partial_11_fu_130 : STD_LOGIC_VECTOR (31 downto 0);
    signal local_kNearstDist_partial_12_fu_134 : STD_LOGIC_VECTOR (31 downto 0);
    signal local_kNearstDist_partial_22_fu_413_p1 : STD_LOGIC_VECTOR (31 downto 0);
    signal local_kNearstDist_partial_13_fu_138 : STD_LOGIC_VECTOR (31 downto 0);
    signal local_kNearstDist_partial_14_fu_142 : STD_LOGIC_VECTOR (31 downto 0);
    signal local_kNearstDist_partial_15_fu_146 : STD_LOGIC_VECTOR (31 downto 0);
    signal local_kNearstDist_partial_16_fu_150 : STD_LOGIC_VECTOR (31 downto 0);
    signal local_kNearstDist_partial_17_fu_154 : STD_LOGIC_VECTOR (31 downto 0);
    signal local_kNearstDist_partial_18_fu_158 : STD_LOGIC_VECTOR (31 downto 0);
    signal local_kNearstDist_partial_19_fu_162 : STD_LOGIC_VECTOR (31 downto 0);
    signal local_kNearstDist_partial_20_fu_166 : STD_LOGIC_VECTOR (31 downto 0);
    signal local_kNearstDist_partial_21_fu_170 : STD_LOGIC_VECTOR (31 downto 0);
    signal ap_block_pp0_stage0_01001 : BOOLEAN;
    signal tmp_val_data_V_1_fu_351_p1 : STD_LOGIC_VECTOR (31 downto 0);
    signal tmp_val_data_V_fu_409_p1 : STD_LOGIC_VECTOR (31 downto 0);
    signal ap_done_reg : STD_LOGIC := '0';
    signal ap_continue_int : STD_LOGIC;
    signal ap_done_int : STD_LOGIC;
    signal ap_NS_fsm : STD_LOGIC_VECTOR (0 downto 0);
    signal ap_enable_pp0 : STD_LOGIC;
    signal ap_start_int : STD_LOGIC;
    signal ap_ce_reg : STD_LOGIC;

    component krnl_globalSort_L3_flow_control_loop_pipe_sequential_init IS
    port (
        ap_clk : IN STD_LOGIC;
        ap_rst : IN STD_LOGIC;
        ap_start : IN STD_LOGIC;
        ap_ready : OUT STD_LOGIC;
        ap_done : OUT STD_LOGIC;
        ap_start_int : OUT STD_LOGIC;
        ap_loop_init : OUT STD_LOGIC;
        ap_ready_int : IN STD_LOGIC;
        ap_loop_exit_ready : IN STD_LOGIC;
        ap_loop_exit_done : IN STD_LOGIC;
        ap_continue_int : OUT STD_LOGIC;
        ap_done_int : IN STD_LOGIC );
    end component;



begin
    flow_control_loop_pipe_sequential_init_U : component krnl_globalSort_L3_flow_control_loop_pipe_sequential_init
    port map (
        ap_clk => ap_clk,
        ap_rst => ap_rst,
        ap_start => ap_start,
        ap_ready => ap_ready,
        ap_done => ap_done,
        ap_start_int => ap_start_int,
        ap_loop_init => ap_loop_init,
        ap_ready_int => ap_ready_int,
        ap_loop_exit_ready => ap_condition_exit_pp0_iter0_stage0,
        ap_loop_exit_done => ap_done_int,
        ap_continue_int => ap_continue_int,
        ap_done_int => ap_done_int);





    ap_CS_fsm_assign_proc : process(ap_clk)
    begin
        if (ap_clk'event and ap_clk =  '1') then
            if (ap_rst = '1') then
                ap_CS_fsm <= ap_ST_fsm_pp0_stage0;
            else
                ap_CS_fsm <= ap_NS_fsm;
            end if;
        end if;
    end process;


    ap_done_reg_assign_proc : process(ap_clk)
    begin
        if (ap_clk'event and ap_clk =  '1') then
            if (ap_rst = '1') then
                ap_done_reg <= ap_const_logic_0;
            else
                if ((ap_continue_int = ap_const_logic_1)) then 
                    ap_done_reg <= ap_const_logic_0;
                elsif (((ap_loop_exit_ready = ap_const_logic_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_subdone) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
                    ap_done_reg <= ap_const_logic_1;
                end if; 
            end if;
        end if;
    end process;


    ap_enable_reg_pp0_iter1_assign_proc : process(ap_clk)
    begin
        if (ap_clk'event and ap_clk =  '1') then
            if (ap_rst = '1') then
                ap_enable_reg_pp0_iter1 <= ap_const_logic_0;
            else
                if ((ap_const_logic_1 = ap_condition_exit_pp0_iter0_stage0)) then 
                    ap_enable_reg_pp0_iter1 <= ap_const_logic_0;
                elsif (((ap_const_boolean_0 = ap_block_pp0_stage0_subdone) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
                    ap_enable_reg_pp0_iter1 <= ap_start_int;
                end if; 
            end if;
        end if;
    end process;


    i_fu_90_assign_proc : process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then
                if (((icmp_ln875_fu_334_p2 = ap_const_lv1_0) and (ap_enable_reg_pp0_iter0 = ap_const_logic_1))) then 
                    i_fu_90 <= add_ln875_fu_340_p2;
                elsif ((ap_loop_init = ap_const_logic_1)) then 
                    i_fu_90 <= ap_const_lv4_0;
                end if;
            end if; 
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then
                i_2_reg_674 <= ap_sig_allocacmp_i_2;
            end if;
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_enable_reg_pp0_iter1 = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0) and (i_2_reg_674 = ap_const_lv4_8))) then
                local_kNearstDist_partial_10_fu_126 <= local_kNearstDist_partial_fu_355_p1;
                local_kNearstDist_partial_20_fu_166 <= local_kNearstDist_partial_22_fu_413_p1;
            end if;
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_enable_reg_pp0_iter1 = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0) and ((i_2_reg_674 = ap_const_lv4_9) or ((i_2_reg_674 = ap_const_lv4_A) or ((i_2_reg_674 = ap_const_lv4_B) or ((i_2_reg_674 = ap_const_lv4_C) or ((i_2_reg_674 = ap_const_lv4_D) or ((i_2_reg_674 = ap_const_lv4_E) or (i_2_reg_674 = ap_const_lv4_F))))))))) then
                local_kNearstDist_partial_11_fu_130 <= local_kNearstDist_partial_fu_355_p1;
                local_kNearstDist_partial_21_fu_170 <= local_kNearstDist_partial_22_fu_413_p1;
            end if;
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_enable_reg_pp0_iter1 = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0) and (i_2_reg_674 = ap_const_lv4_0))) then
                local_kNearstDist_partial_12_fu_134 <= local_kNearstDist_partial_22_fu_413_p1;
                local_kNearstDist_partial_2_fu_94 <= local_kNearstDist_partial_fu_355_p1;
            end if;
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_enable_reg_pp0_iter1 = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0) and (i_2_reg_674 = ap_const_lv4_1))) then
                local_kNearstDist_partial_13_fu_138 <= local_kNearstDist_partial_22_fu_413_p1;
                local_kNearstDist_partial_3_fu_98 <= local_kNearstDist_partial_fu_355_p1;
            end if;
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_enable_reg_pp0_iter1 = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0) and (i_2_reg_674 = ap_const_lv4_2))) then
                local_kNearstDist_partial_14_fu_142 <= local_kNearstDist_partial_22_fu_413_p1;
                local_kNearstDist_partial_4_fu_102 <= local_kNearstDist_partial_fu_355_p1;
            end if;
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_enable_reg_pp0_iter1 = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0) and (i_2_reg_674 = ap_const_lv4_3))) then
                local_kNearstDist_partial_15_fu_146 <= local_kNearstDist_partial_22_fu_413_p1;
                local_kNearstDist_partial_5_fu_106 <= local_kNearstDist_partial_fu_355_p1;
            end if;
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_enable_reg_pp0_iter1 = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0) and (i_2_reg_674 = ap_const_lv4_4))) then
                local_kNearstDist_partial_16_fu_150 <= local_kNearstDist_partial_22_fu_413_p1;
                local_kNearstDist_partial_6_fu_110 <= local_kNearstDist_partial_fu_355_p1;
            end if;
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_enable_reg_pp0_iter1 = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0) and (i_2_reg_674 = ap_const_lv4_5))) then
                local_kNearstDist_partial_17_fu_154 <= local_kNearstDist_partial_22_fu_413_p1;
                local_kNearstDist_partial_7_fu_114 <= local_kNearstDist_partial_fu_355_p1;
            end if;
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_enable_reg_pp0_iter1 = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0) and (i_2_reg_674 = ap_const_lv4_6))) then
                local_kNearstDist_partial_18_fu_158 <= local_kNearstDist_partial_22_fu_413_p1;
                local_kNearstDist_partial_8_fu_118 <= local_kNearstDist_partial_fu_355_p1;
            end if;
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_enable_reg_pp0_iter1 = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0) and (i_2_reg_674 = ap_const_lv4_7))) then
                local_kNearstDist_partial_19_fu_162 <= local_kNearstDist_partial_22_fu_413_p1;
                local_kNearstDist_partial_9_fu_122 <= local_kNearstDist_partial_fu_355_p1;
            end if;
        end if;
    end process;

    ap_NS_fsm_assign_proc : process (ap_CS_fsm)
    begin
        case ap_CS_fsm is
            when ap_ST_fsm_pp0_stage0 => 
                ap_NS_fsm <= ap_ST_fsm_pp0_stage0;
            when others =>  
                ap_NS_fsm <= "X";
        end case;
    end process;
    add_ln875_fu_340_p2 <= std_logic_vector(unsigned(ap_sig_allocacmp_i_2) + unsigned(ap_const_lv4_1));
    ap_CS_fsm_pp0_stage0 <= ap_CS_fsm(0);
        ap_block_pp0_stage0 <= not((ap_const_boolean_1 = ap_const_boolean_1));

    ap_block_pp0_stage0_01001_assign_proc : process(ap_enable_reg_pp0_iter1, in_dist0_s_empty_n, in_dist1_s_empty_n)
    begin
                ap_block_pp0_stage0_01001 <= ((ap_enable_reg_pp0_iter1 = ap_const_logic_1) and ((in_dist1_s_empty_n = ap_const_logic_0) or (in_dist0_s_empty_n = ap_const_logic_0)));
    end process;


    ap_block_pp0_stage0_11001_assign_proc : process(ap_enable_reg_pp0_iter1, in_dist0_s_empty_n, in_dist1_s_empty_n)
    begin
                ap_block_pp0_stage0_11001 <= ((ap_enable_reg_pp0_iter1 = ap_const_logic_1) and ((in_dist1_s_empty_n = ap_const_logic_0) or (in_dist0_s_empty_n = ap_const_logic_0)));
    end process;


    ap_block_pp0_stage0_subdone_assign_proc : process(ap_enable_reg_pp0_iter1, in_dist0_s_empty_n, in_dist1_s_empty_n)
    begin
                ap_block_pp0_stage0_subdone <= ((ap_enable_reg_pp0_iter1 = ap_const_logic_1) and ((in_dist1_s_empty_n = ap_const_logic_0) or (in_dist0_s_empty_n = ap_const_logic_0)));
    end process;

        ap_block_state1_pp0_stage0_iter0 <= not((ap_const_boolean_1 = ap_const_boolean_1));

    ap_block_state2_pp0_stage0_iter1_assign_proc : process(in_dist0_s_empty_n, in_dist1_s_empty_n)
    begin
                ap_block_state2_pp0_stage0_iter1 <= ((in_dist1_s_empty_n = ap_const_logic_0) or (in_dist0_s_empty_n = ap_const_logic_0));
    end process;


    ap_condition_exit_pp0_iter0_stage0_assign_proc : process(ap_CS_fsm_pp0_stage0, ap_enable_reg_pp0_iter0, ap_block_pp0_stage0_subdone, icmp_ln875_fu_334_p2)
    begin
        if (((icmp_ln875_fu_334_p2 = ap_const_lv1_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_subdone) and (ap_enable_reg_pp0_iter0 = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            ap_condition_exit_pp0_iter0_stage0 <= ap_const_logic_1;
        else 
            ap_condition_exit_pp0_iter0_stage0 <= ap_const_logic_0;
        end if; 
    end process;


    ap_done_int_assign_proc : process(ap_CS_fsm_pp0_stage0, ap_block_pp0_stage0_subdone, ap_loop_exit_ready, ap_done_reg)
    begin
        if (((ap_loop_exit_ready = ap_const_logic_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_subdone) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            ap_done_int <= ap_const_logic_1;
        else 
            ap_done_int <= ap_done_reg;
        end if; 
    end process;

    ap_enable_pp0 <= (ap_idle_pp0 xor ap_const_logic_1);
    ap_enable_reg_pp0_iter0 <= ap_start_int;

    ap_idle_assign_proc : process(ap_CS_fsm_pp0_stage0, ap_idle_pp0, ap_start_int)
    begin
        if (((ap_start_int = ap_const_logic_0) and (ap_idle_pp0 = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            ap_idle <= ap_const_logic_1;
        else 
            ap_idle <= ap_const_logic_0;
        end if; 
    end process;


    ap_idle_pp0_assign_proc : process(ap_enable_reg_pp0_iter0, ap_enable_reg_pp0_iter1)
    begin
        if (((ap_enable_reg_pp0_iter1 = ap_const_logic_0) and (ap_enable_reg_pp0_iter0 = ap_const_logic_0))) then 
            ap_idle_pp0 <= ap_const_logic_1;
        else 
            ap_idle_pp0 <= ap_const_logic_0;
        end if; 
    end process;

    ap_loop_exit_ready <= ap_condition_exit_pp0_iter0_stage0;

    ap_ready_int_assign_proc : process(ap_CS_fsm_pp0_stage0, ap_enable_reg_pp0_iter0, ap_block_pp0_stage0_subdone)
    begin
        if (((ap_const_boolean_0 = ap_block_pp0_stage0_subdone) and (ap_enable_reg_pp0_iter0 = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            ap_ready_int <= ap_const_logic_1;
        else 
            ap_ready_int <= ap_const_logic_0;
        end if; 
    end process;


    ap_sig_allocacmp_i_2_assign_proc : process(ap_CS_fsm_pp0_stage0, ap_block_pp0_stage0, i_fu_90, ap_loop_init)
    begin
        if (((ap_const_boolean_0 = ap_block_pp0_stage0) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0) and (ap_loop_init = ap_const_logic_1))) then 
            ap_sig_allocacmp_i_2 <= ap_const_lv4_0;
        else 
            ap_sig_allocacmp_i_2 <= i_fu_90;
        end if; 
    end process;

    icmp_ln875_fu_334_p2 <= "1" when (ap_sig_allocacmp_i_2 = ap_const_lv4_A) else "0";

    in_dist0_s_blk_n_assign_proc : process(ap_CS_fsm_pp0_stage0, ap_enable_reg_pp0_iter1, in_dist0_s_empty_n, ap_block_pp0_stage0)
    begin
        if (((ap_const_boolean_0 = ap_block_pp0_stage0) and (ap_enable_reg_pp0_iter1 = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            in_dist0_s_blk_n <= in_dist0_s_empty_n;
        else 
            in_dist0_s_blk_n <= ap_const_logic_1;
        end if; 
    end process;


    in_dist0_s_read_assign_proc : process(ap_CS_fsm_pp0_stage0, ap_enable_reg_pp0_iter1, ap_block_pp0_stage0_11001)
    begin
        if (((ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_enable_reg_pp0_iter1 = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            in_dist0_s_read <= ap_const_logic_1;
        else 
            in_dist0_s_read <= ap_const_logic_0;
        end if; 
    end process;


    in_dist1_s_blk_n_assign_proc : process(ap_CS_fsm_pp0_stage0, ap_enable_reg_pp0_iter1, in_dist1_s_empty_n, ap_block_pp0_stage0)
    begin
        if (((ap_const_boolean_0 = ap_block_pp0_stage0) and (ap_enable_reg_pp0_iter1 = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            in_dist1_s_blk_n <= in_dist1_s_empty_n;
        else 
            in_dist1_s_blk_n <= ap_const_logic_1;
        end if; 
    end process;


    in_dist1_s_read_assign_proc : process(ap_CS_fsm_pp0_stage0, ap_enable_reg_pp0_iter1, ap_block_pp0_stage0_11001)
    begin
        if (((ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_enable_reg_pp0_iter1 = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            in_dist1_s_read <= ap_const_logic_1;
        else 
            in_dist1_s_read <= ap_const_logic_0;
        end if; 
    end process;

    local_kNearstDist_partial1_out <= local_kNearstDist_partial_2_fu_94;

    local_kNearstDist_partial1_out_ap_vld_assign_proc : process(ap_CS_fsm_pp0_stage0, icmp_ln875_fu_334_p2, ap_block_pp0_stage0_11001)
    begin
        if (((icmp_ln875_fu_334_p2 = ap_const_lv1_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            local_kNearstDist_partial1_out_ap_vld <= ap_const_logic_1;
        else 
            local_kNearstDist_partial1_out_ap_vld <= ap_const_logic_0;
        end if; 
    end process;

    local_kNearstDist_partial_1019_out <= local_kNearstDist_partial_12_fu_134;

    local_kNearstDist_partial_1019_out_ap_vld_assign_proc : process(ap_CS_fsm_pp0_stage0, icmp_ln875_fu_334_p2, ap_block_pp0_stage0_11001)
    begin
        if (((icmp_ln875_fu_334_p2 = ap_const_lv1_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            local_kNearstDist_partial_1019_out_ap_vld <= ap_const_logic_1;
        else 
            local_kNearstDist_partial_1019_out_ap_vld <= ap_const_logic_0;
        end if; 
    end process;

    local_kNearstDist_partial_110_out <= local_kNearstDist_partial_3_fu_98;

    local_kNearstDist_partial_110_out_ap_vld_assign_proc : process(ap_CS_fsm_pp0_stage0, icmp_ln875_fu_334_p2, ap_block_pp0_stage0_11001)
    begin
        if (((icmp_ln875_fu_334_p2 = ap_const_lv1_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            local_kNearstDist_partial_110_out_ap_vld <= ap_const_logic_1;
        else 
            local_kNearstDist_partial_110_out_ap_vld <= ap_const_logic_0;
        end if; 
    end process;

    local_kNearstDist_partial_1120_out <= local_kNearstDist_partial_13_fu_138;

    local_kNearstDist_partial_1120_out_ap_vld_assign_proc : process(ap_CS_fsm_pp0_stage0, icmp_ln875_fu_334_p2, ap_block_pp0_stage0_11001)
    begin
        if (((icmp_ln875_fu_334_p2 = ap_const_lv1_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            local_kNearstDist_partial_1120_out_ap_vld <= ap_const_logic_1;
        else 
            local_kNearstDist_partial_1120_out_ap_vld <= ap_const_logic_0;
        end if; 
    end process;

    local_kNearstDist_partial_1221_out <= local_kNearstDist_partial_14_fu_142;

    local_kNearstDist_partial_1221_out_ap_vld_assign_proc : process(ap_CS_fsm_pp0_stage0, icmp_ln875_fu_334_p2, ap_block_pp0_stage0_11001)
    begin
        if (((icmp_ln875_fu_334_p2 = ap_const_lv1_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            local_kNearstDist_partial_1221_out_ap_vld <= ap_const_logic_1;
        else 
            local_kNearstDist_partial_1221_out_ap_vld <= ap_const_logic_0;
        end if; 
    end process;

    local_kNearstDist_partial_1322_out <= local_kNearstDist_partial_15_fu_146;

    local_kNearstDist_partial_1322_out_ap_vld_assign_proc : process(ap_CS_fsm_pp0_stage0, icmp_ln875_fu_334_p2, ap_block_pp0_stage0_11001)
    begin
        if (((icmp_ln875_fu_334_p2 = ap_const_lv1_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            local_kNearstDist_partial_1322_out_ap_vld <= ap_const_logic_1;
        else 
            local_kNearstDist_partial_1322_out_ap_vld <= ap_const_logic_0;
        end if; 
    end process;

    local_kNearstDist_partial_1423_out <= local_kNearstDist_partial_16_fu_150;

    local_kNearstDist_partial_1423_out_ap_vld_assign_proc : process(ap_CS_fsm_pp0_stage0, icmp_ln875_fu_334_p2, ap_block_pp0_stage0_11001)
    begin
        if (((icmp_ln875_fu_334_p2 = ap_const_lv1_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            local_kNearstDist_partial_1423_out_ap_vld <= ap_const_logic_1;
        else 
            local_kNearstDist_partial_1423_out_ap_vld <= ap_const_logic_0;
        end if; 
    end process;

    local_kNearstDist_partial_1524_out <= local_kNearstDist_partial_17_fu_154;

    local_kNearstDist_partial_1524_out_ap_vld_assign_proc : process(ap_CS_fsm_pp0_stage0, icmp_ln875_fu_334_p2, ap_block_pp0_stage0_11001)
    begin
        if (((icmp_ln875_fu_334_p2 = ap_const_lv1_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            local_kNearstDist_partial_1524_out_ap_vld <= ap_const_logic_1;
        else 
            local_kNearstDist_partial_1524_out_ap_vld <= ap_const_logic_0;
        end if; 
    end process;

    local_kNearstDist_partial_1625_out <= local_kNearstDist_partial_18_fu_158;

    local_kNearstDist_partial_1625_out_ap_vld_assign_proc : process(ap_CS_fsm_pp0_stage0, icmp_ln875_fu_334_p2, ap_block_pp0_stage0_11001)
    begin
        if (((icmp_ln875_fu_334_p2 = ap_const_lv1_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            local_kNearstDist_partial_1625_out_ap_vld <= ap_const_logic_1;
        else 
            local_kNearstDist_partial_1625_out_ap_vld <= ap_const_logic_0;
        end if; 
    end process;

    local_kNearstDist_partial_1726_out <= local_kNearstDist_partial_19_fu_162;

    local_kNearstDist_partial_1726_out_ap_vld_assign_proc : process(ap_CS_fsm_pp0_stage0, icmp_ln875_fu_334_p2, ap_block_pp0_stage0_11001)
    begin
        if (((icmp_ln875_fu_334_p2 = ap_const_lv1_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            local_kNearstDist_partial_1726_out_ap_vld <= ap_const_logic_1;
        else 
            local_kNearstDist_partial_1726_out_ap_vld <= ap_const_logic_0;
        end if; 
    end process;

    local_kNearstDist_partial_1827_out <= local_kNearstDist_partial_20_fu_166;

    local_kNearstDist_partial_1827_out_ap_vld_assign_proc : process(ap_CS_fsm_pp0_stage0, icmp_ln875_fu_334_p2, ap_block_pp0_stage0_11001)
    begin
        if (((icmp_ln875_fu_334_p2 = ap_const_lv1_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            local_kNearstDist_partial_1827_out_ap_vld <= ap_const_logic_1;
        else 
            local_kNearstDist_partial_1827_out_ap_vld <= ap_const_logic_0;
        end if; 
    end process;

    local_kNearstDist_partial_1928_out <= local_kNearstDist_partial_21_fu_170;

    local_kNearstDist_partial_1928_out_ap_vld_assign_proc : process(ap_CS_fsm_pp0_stage0, icmp_ln875_fu_334_p2, ap_block_pp0_stage0_11001)
    begin
        if (((icmp_ln875_fu_334_p2 = ap_const_lv1_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            local_kNearstDist_partial_1928_out_ap_vld <= ap_const_logic_1;
        else 
            local_kNearstDist_partial_1928_out_ap_vld <= ap_const_logic_0;
        end if; 
    end process;

    local_kNearstDist_partial_211_out <= local_kNearstDist_partial_4_fu_102;

    local_kNearstDist_partial_211_out_ap_vld_assign_proc : process(ap_CS_fsm_pp0_stage0, icmp_ln875_fu_334_p2, ap_block_pp0_stage0_11001)
    begin
        if (((icmp_ln875_fu_334_p2 = ap_const_lv1_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            local_kNearstDist_partial_211_out_ap_vld <= ap_const_logic_1;
        else 
            local_kNearstDist_partial_211_out_ap_vld <= ap_const_logic_0;
        end if; 
    end process;

    local_kNearstDist_partial_22_fu_413_p1 <= tmp_val_data_V_fu_409_p1;
    local_kNearstDist_partial_312_out <= local_kNearstDist_partial_5_fu_106;

    local_kNearstDist_partial_312_out_ap_vld_assign_proc : process(ap_CS_fsm_pp0_stage0, icmp_ln875_fu_334_p2, ap_block_pp0_stage0_11001)
    begin
        if (((icmp_ln875_fu_334_p2 = ap_const_lv1_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            local_kNearstDist_partial_312_out_ap_vld <= ap_const_logic_1;
        else 
            local_kNearstDist_partial_312_out_ap_vld <= ap_const_logic_0;
        end if; 
    end process;

    local_kNearstDist_partial_413_out <= local_kNearstDist_partial_6_fu_110;

    local_kNearstDist_partial_413_out_ap_vld_assign_proc : process(ap_CS_fsm_pp0_stage0, icmp_ln875_fu_334_p2, ap_block_pp0_stage0_11001)
    begin
        if (((icmp_ln875_fu_334_p2 = ap_const_lv1_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            local_kNearstDist_partial_413_out_ap_vld <= ap_const_logic_1;
        else 
            local_kNearstDist_partial_413_out_ap_vld <= ap_const_logic_0;
        end if; 
    end process;

    local_kNearstDist_partial_514_out <= local_kNearstDist_partial_7_fu_114;

    local_kNearstDist_partial_514_out_ap_vld_assign_proc : process(ap_CS_fsm_pp0_stage0, icmp_ln875_fu_334_p2, ap_block_pp0_stage0_11001)
    begin
        if (((icmp_ln875_fu_334_p2 = ap_const_lv1_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            local_kNearstDist_partial_514_out_ap_vld <= ap_const_logic_1;
        else 
            local_kNearstDist_partial_514_out_ap_vld <= ap_const_logic_0;
        end if; 
    end process;

    local_kNearstDist_partial_615_out <= local_kNearstDist_partial_8_fu_118;

    local_kNearstDist_partial_615_out_ap_vld_assign_proc : process(ap_CS_fsm_pp0_stage0, icmp_ln875_fu_334_p2, ap_block_pp0_stage0_11001)
    begin
        if (((icmp_ln875_fu_334_p2 = ap_const_lv1_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            local_kNearstDist_partial_615_out_ap_vld <= ap_const_logic_1;
        else 
            local_kNearstDist_partial_615_out_ap_vld <= ap_const_logic_0;
        end if; 
    end process;

    local_kNearstDist_partial_716_out <= local_kNearstDist_partial_9_fu_122;

    local_kNearstDist_partial_716_out_ap_vld_assign_proc : process(ap_CS_fsm_pp0_stage0, icmp_ln875_fu_334_p2, ap_block_pp0_stage0_11001)
    begin
        if (((icmp_ln875_fu_334_p2 = ap_const_lv1_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            local_kNearstDist_partial_716_out_ap_vld <= ap_const_logic_1;
        else 
            local_kNearstDist_partial_716_out_ap_vld <= ap_const_logic_0;
        end if; 
    end process;

    local_kNearstDist_partial_817_out <= local_kNearstDist_partial_10_fu_126;

    local_kNearstDist_partial_817_out_ap_vld_assign_proc : process(ap_CS_fsm_pp0_stage0, icmp_ln875_fu_334_p2, ap_block_pp0_stage0_11001)
    begin
        if (((icmp_ln875_fu_334_p2 = ap_const_lv1_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            local_kNearstDist_partial_817_out_ap_vld <= ap_const_logic_1;
        else 
            local_kNearstDist_partial_817_out_ap_vld <= ap_const_logic_0;
        end if; 
    end process;

    local_kNearstDist_partial_918_out <= local_kNearstDist_partial_11_fu_130;

    local_kNearstDist_partial_918_out_ap_vld_assign_proc : process(ap_CS_fsm_pp0_stage0, icmp_ln875_fu_334_p2, ap_block_pp0_stage0_11001)
    begin
        if (((icmp_ln875_fu_334_p2 = ap_const_lv1_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            local_kNearstDist_partial_918_out_ap_vld <= ap_const_logic_1;
        else 
            local_kNearstDist_partial_918_out_ap_vld <= ap_const_logic_0;
        end if; 
    end process;

    local_kNearstDist_partial_fu_355_p1 <= tmp_val_data_V_1_fu_351_p1;
    tmp_val_data_V_1_fu_351_p1 <= in_dist0_s_dout(32 - 1 downto 0);
    tmp_val_data_V_fu_409_p1 <= in_dist1_s_dout(32 - 1 downto 0);
end behav;