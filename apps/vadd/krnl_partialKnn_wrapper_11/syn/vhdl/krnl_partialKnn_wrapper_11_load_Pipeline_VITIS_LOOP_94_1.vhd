-- ==============================================================
-- RTL generated by Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
-- Version: 2022.1
-- Copyright (C) Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
-- 
-- ===========================================================

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity krnl_partialKnn_wrapper_11_load_Pipeline_VITIS_LOOP_94_1 is
port (
    ap_clk : IN STD_LOGIC;
    ap_rst : IN STD_LOGIC;
    ap_start : IN STD_LOGIC;
    ap_done : OUT STD_LOGIC;
    ap_idle : OUT STD_LOGIC;
    ap_ready : OUT STD_LOGIC;
    searchSpace_0_read_data_s_dout : IN STD_LOGIC_VECTOR (256 downto 0);
    searchSpace_0_read_data_s_empty_n : IN STD_LOGIC;
    searchSpace_0_read_data_s_read : OUT STD_LOGIC;
    zext_ln94 : IN STD_LOGIC_VECTOR (18 downto 0);
    searchSpace_0_read_addr_din : OUT STD_LOGIC_VECTOR (64 downto 0);
    searchSpace_0_read_addr_full_n : IN STD_LOGIC;
    searchSpace_0_read_addr_write : OUT STD_LOGIC;
    local_SP_address0 : OUT STD_LOGIC_VECTOR (11 downto 0);
    local_SP_ce0 : OUT STD_LOGIC;
    local_SP_we0 : OUT STD_LOGIC;
    local_SP_d0 : OUT STD_LOGIC_VECTOR (255 downto 0) );
end;


architecture behav of krnl_partialKnn_wrapper_11_load_Pipeline_VITIS_LOOP_94_1 is 
    constant ap_const_logic_1 : STD_LOGIC := '1';
    constant ap_const_logic_0 : STD_LOGIC := '0';
    constant ap_ST_fsm_pp0_stage0 : STD_LOGIC_VECTOR (0 downto 0) := "1";
    constant ap_const_lv32_0 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000000000";
    constant ap_const_boolean_1 : BOOLEAN := true;
    constant ap_const_boolean_0 : BOOLEAN := false;
    constant ap_const_lv1_0 : STD_LOGIC_VECTOR (0 downto 0) := "0";
    constant ap_const_lv1_1 : STD_LOGIC_VECTOR (0 downto 0) := "1";
    constant ap_const_lv32_1 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000000001";
    constant ap_const_lv32_C : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000001100";
    constant ap_const_lv32_1F : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000011111";
    constant ap_const_lv20_1 : STD_LOGIC_VECTOR (19 downto 0) := "00000000000000000001";

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
    signal icmp_ln94_fu_131_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal ap_condition_exit_pp0_iter0_stage0 : STD_LOGIC;
    signal ap_loop_exit_ready : STD_LOGIC;
    signal ap_ready_int : STD_LOGIC;
    signal zext_ln94_cast_fu_104_p1 : STD_LOGIC_VECTOR (31 downto 0);
    signal zext_ln94_cast_reg_230 : STD_LOGIC_VECTOR (31 downto 0);
    signal ap_block_pp0_stage0_11001 : BOOLEAN;
    signal i_resp_1_reg_235 : STD_LOGIC_VECTOR (31 downto 0);
    signal tmp_3_nbreadreq_fu_70_p3 : STD_LOGIC_VECTOR (0 downto 0);
    signal tmp_3_reg_243 : STD_LOGIC_VECTOR (0 downto 0);
    signal elem_val_V_fu_141_p1 : STD_LOGIC_VECTOR (255 downto 0);
    signal elem_val_V_reg_247 : STD_LOGIC_VECTOR (255 downto 0);
    signal zext_ln101_fu_212_p1 : STD_LOGIC_VECTOR (63 downto 0);
    signal ap_block_pp0_stage0 : BOOLEAN;
    signal i_resp_fu_56 : STD_LOGIC_VECTOR (31 downto 0);
    signal i_resp_2_fu_145_p2 : STD_LOGIC_VECTOR (31 downto 0);
    signal ap_loop_init : STD_LOGIC;
    signal ap_sig_allocacmp_i_resp_1 : STD_LOGIC_VECTOR (31 downto 0);
    signal i_req_fu_60 : STD_LOGIC_VECTOR (31 downto 0);
    signal select_ln97_fu_199_p3 : STD_LOGIC_VECTOR (31 downto 0);
    signal icmp_ln97_fu_174_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal ap_block_pp0_stage0_01001 : BOOLEAN;
    signal tmp_fu_121_p4 : STD_LOGIC_VECTOR (19 downto 0);
    signal tmp_4_fu_164_p4 : STD_LOGIC_VECTOR (19 downto 0);
    signal addr_fu_159_p2 : STD_LOGIC_VECTOR (31 downto 0);
    signal sext_ln97_fu_180_p1 : STD_LOGIC_VECTOR (63 downto 0);
    signal select_ln97_fu_199_p0 : STD_LOGIC_VECTOR (0 downto 0);
    signal add_ln98_fu_193_p2 : STD_LOGIC_VECTOR (31 downto 0);
    signal ap_done_reg : STD_LOGIC := '0';
    signal ap_continue_int : STD_LOGIC;
    signal ap_done_int : STD_LOGIC;
    signal ap_NS_fsm : STD_LOGIC_VECTOR (0 downto 0);
    signal ap_enable_pp0 : STD_LOGIC;
    signal ap_start_int : STD_LOGIC;
    signal ap_condition_212 : BOOLEAN;
    signal ap_ce_reg : STD_LOGIC;

    component krnl_partialKnn_wrapper_11_flow_control_loop_pipe_sequential_init IS
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
    flow_control_loop_pipe_sequential_init_U : component krnl_partialKnn_wrapper_11_flow_control_loop_pipe_sequential_init
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


    i_req_fu_60_assign_proc : process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then
                if ((ap_loop_init = ap_const_logic_1)) then 
                    i_req_fu_60 <= ap_const_lv32_0;
                elsif (((ap_enable_reg_pp0_iter1 = ap_const_logic_1) and (icmp_ln97_fu_174_p2 = ap_const_lv1_1))) then 
                    i_req_fu_60 <= select_ln97_fu_199_p3;
                end if;
            end if; 
        end if;
    end process;

    i_resp_fu_56_assign_proc : process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then
                if ((ap_const_boolean_1 = ap_condition_212)) then 
                    i_resp_fu_56 <= i_resp_2_fu_145_p2;
                elsif ((ap_loop_init = ap_const_logic_1)) then 
                    i_resp_fu_56 <= ap_const_lv32_0;
                end if;
            end if; 
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((tmp_3_nbreadreq_fu_70_p3 = ap_const_lv1_1) and (icmp_ln94_fu_131_p2 = ap_const_lv1_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then
                elem_val_V_reg_247 <= elem_val_V_fu_141_p1;
            end if;
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then
                i_resp_1_reg_235 <= ap_sig_allocacmp_i_resp_1;
                    zext_ln94_cast_reg_230(18 downto 0) <= zext_ln94_cast_fu_104_p1(18 downto 0);
            end if;
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((icmp_ln94_fu_131_p2 = ap_const_lv1_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then
                tmp_3_reg_243 <= tmp_3_nbreadreq_fu_70_p3;
            end if;
        end if;
    end process;
    zext_ln94_cast_reg_230(31 downto 19) <= "0000000000000";

    ap_NS_fsm_assign_proc : process (ap_CS_fsm)
    begin
        case ap_CS_fsm is
            when ap_ST_fsm_pp0_stage0 => 
                ap_NS_fsm <= ap_ST_fsm_pp0_stage0;
            when others =>  
                ap_NS_fsm <= "X";
        end case;
    end process;
    add_ln98_fu_193_p2 <= std_logic_vector(unsigned(i_req_fu_60) + unsigned(ap_const_lv32_1));
    addr_fu_159_p2 <= std_logic_vector(unsigned(i_req_fu_60) + unsigned(zext_ln94_cast_reg_230));
    ap_CS_fsm_pp0_stage0 <= ap_CS_fsm(0);
        ap_block_pp0_stage0 <= not((ap_const_boolean_1 = ap_const_boolean_1));
        ap_block_pp0_stage0_01001 <= not((ap_const_boolean_1 = ap_const_boolean_1));
        ap_block_pp0_stage0_11001 <= not((ap_const_boolean_1 = ap_const_boolean_1));
        ap_block_pp0_stage0_subdone <= not((ap_const_boolean_1 = ap_const_boolean_1));
        ap_block_state1_pp0_stage0_iter0 <= not((ap_const_boolean_1 = ap_const_boolean_1));
        ap_block_state2_pp0_stage0_iter1 <= not((ap_const_boolean_1 = ap_const_boolean_1));

    ap_condition_212_assign_proc : process(ap_enable_reg_pp0_iter0, icmp_ln94_fu_131_p2, tmp_3_nbreadreq_fu_70_p3)
    begin
                ap_condition_212 <= ((tmp_3_nbreadreq_fu_70_p3 = ap_const_lv1_1) and (icmp_ln94_fu_131_p2 = ap_const_lv1_1) and (ap_enable_reg_pp0_iter0 = ap_const_logic_1));
    end process;


    ap_condition_exit_pp0_iter0_stage0_assign_proc : process(ap_CS_fsm_pp0_stage0, ap_enable_reg_pp0_iter0, ap_block_pp0_stage0_subdone, icmp_ln94_fu_131_p2)
    begin
        if (((icmp_ln94_fu_131_p2 = ap_const_lv1_0) and (ap_const_boolean_0 = ap_block_pp0_stage0_subdone) and (ap_enable_reg_pp0_iter0 = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
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
        if (((ap_idle_pp0 = ap_const_logic_1) and (ap_start_int = ap_const_logic_0) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
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


    ap_sig_allocacmp_i_resp_1_assign_proc : process(ap_CS_fsm_pp0_stage0, ap_block_pp0_stage0, i_resp_fu_56, ap_loop_init)
    begin
        if (((ap_loop_init = ap_const_logic_1) and (ap_const_boolean_0 = ap_block_pp0_stage0) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            ap_sig_allocacmp_i_resp_1 <= ap_const_lv32_0;
        else 
            ap_sig_allocacmp_i_resp_1 <= i_resp_fu_56;
        end if; 
    end process;

    elem_val_V_fu_141_p1 <= searchSpace_0_read_data_s_dout(256 - 1 downto 0);
    i_resp_2_fu_145_p2 <= std_logic_vector(unsigned(ap_sig_allocacmp_i_resp_1) + unsigned(ap_const_lv32_1));
    icmp_ln94_fu_131_p2 <= "1" when (signed(tmp_fu_121_p4) < signed(ap_const_lv20_1)) else "0";
    icmp_ln97_fu_174_p2 <= "1" when (signed(tmp_4_fu_164_p4) < signed(ap_const_lv20_1)) else "0";
    local_SP_address0 <= zext_ln101_fu_212_p1(12 - 1 downto 0);

    local_SP_ce0_assign_proc : process(ap_CS_fsm_pp0_stage0, ap_enable_reg_pp0_iter1, ap_block_pp0_stage0_11001)
    begin
        if (((ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_enable_reg_pp0_iter1 = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            local_SP_ce0 <= ap_const_logic_1;
        else 
            local_SP_ce0 <= ap_const_logic_0;
        end if; 
    end process;

    local_SP_d0 <= elem_val_V_reg_247;

    local_SP_we0_assign_proc : process(ap_CS_fsm_pp0_stage0, ap_enable_reg_pp0_iter1, ap_block_pp0_stage0_11001, tmp_3_reg_243)
    begin
        if (((tmp_3_reg_243 = ap_const_lv1_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_enable_reg_pp0_iter1 = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            local_SP_we0 <= ap_const_logic_1;
        else 
            local_SP_we0 <= ap_const_logic_0;
        end if; 
    end process;

    searchSpace_0_read_addr_din <= (ap_const_lv1_0 & sext_ln97_fu_180_p1);

    searchSpace_0_read_addr_write_assign_proc : process(ap_CS_fsm_pp0_stage0, ap_enable_reg_pp0_iter1, searchSpace_0_read_addr_full_n, ap_block_pp0_stage0_11001, icmp_ln97_fu_174_p2)
    begin
        if (((searchSpace_0_read_addr_full_n = ap_const_logic_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_enable_reg_pp0_iter1 = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0) and (icmp_ln97_fu_174_p2 = ap_const_lv1_1))) then 
            searchSpace_0_read_addr_write <= ap_const_logic_1;
        else 
            searchSpace_0_read_addr_write <= ap_const_logic_0;
        end if; 
    end process;


    searchSpace_0_read_data_s_read_assign_proc : process(ap_CS_fsm_pp0_stage0, ap_enable_reg_pp0_iter0, icmp_ln94_fu_131_p2, searchSpace_0_read_data_s_empty_n, ap_block_pp0_stage0_11001, tmp_3_nbreadreq_fu_70_p3)
    begin
        if (((tmp_3_nbreadreq_fu_70_p3 = ap_const_lv1_1) and (searchSpace_0_read_data_s_empty_n = ap_const_logic_1) and (icmp_ln94_fu_131_p2 = ap_const_lv1_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_enable_reg_pp0_iter0 = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            searchSpace_0_read_data_s_read <= ap_const_logic_1;
        else 
            searchSpace_0_read_data_s_read <= ap_const_logic_0;
        end if; 
    end process;

    select_ln97_fu_199_p0 <= (0=>searchSpace_0_read_addr_full_n, others=>'-');
    select_ln97_fu_199_p3 <= 
        add_ln98_fu_193_p2 when (select_ln97_fu_199_p0(0) = '1') else 
        i_req_fu_60;
        sext_ln97_fu_180_p1 <= std_logic_vector(IEEE.numeric_std.resize(signed(addr_fu_159_p2),64));

    tmp_3_nbreadreq_fu_70_p3 <= (0=>(searchSpace_0_read_data_s_empty_n), others=>'-');
    tmp_4_fu_164_p4 <= i_req_fu_60(31 downto 12);
    tmp_fu_121_p4 <= ap_sig_allocacmp_i_resp_1(31 downto 12);
    zext_ln101_fu_212_p1 <= std_logic_vector(IEEE.numeric_std.resize(unsigned(i_resp_1_reg_235),64));
    zext_ln94_cast_fu_104_p1 <= std_logic_vector(IEEE.numeric_std.resize(unsigned(zext_ln94),32));
end behav;