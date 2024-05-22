-- ==============================================================
-- Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
-- Tool Version Limit: 2022.04
-- Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
-- ==============================================================
--
library ieee; 
use ieee.std_logic_1164.all; 
use ieee.std_logic_unsigned.all;

entity krnl_partialKnn_wrapper_3_local_SP_0_A_V_XPM_MEMORY_URAM_1R1W_ram is 
   generic(
  -- Common module parameters
       MEMORY_SIZE        : integer := 1048576;
       MEMORY_PRIMITIVE   : string := "ultra";
       ECC_MODE           : string := "no_ecc";
       MEMORY_INIT_FILE   : string := "none";
       WAKEUP_TIME        : string := "disable_sleep";
       MESSAGE_CONTROL    : integer := 0;

  -- Port A module parameters
       WRITE_DATA_WIDTH_A : integer := 256;
       READ_DATA_WIDTH_A  : integer := 256;
       BYTE_WRITE_WIDTH_A : integer := 256;
       ADDR_WIDTH_A       : integer := 12;
       READ_RESET_VALUE_A : string  := "0";
       READ_LATENCY_A     : integer := 1;
       WRITE_MODE_A       : string := "read_first"

   ); 
    port (
  -- Port A module ports
       clka    : in std_logic;
       rsta    : in std_logic;
       ena     : in std_logic;
       wea     : in std_logic;
       addra   : in std_logic_vector(ADDR_WIDTH_A-1 downto 0);
       dina    : in std_logic_vector(WRITE_DATA_WIDTH_A-1 downto 0);
       douta   : out std_logic_vector(READ_DATA_WIDTH_A-1 downto 0)
   );
end entity;

architecture rtl of krnl_partialKnn_wrapper_3_local_SP_0_A_V_XPM_MEMORY_URAM_1R1W_ram is 
   signal wea_vector : std_logic_vector((WRITE_DATA_WIDTH_A/BYTE_WRITE_WIDTH_A)-1 downto 0);
-- Set generic values and connect ports to instantiate an XPM_MEMORY single port RAM configuration

-----Use the following component declaration in your design-----
component xpm_memory_spram
  generic (

    -- Common module generics
    MEMORY_SIZE        : integer;
    MEMORY_PRIMITIVE   : string;
    ECC_MODE           : string;
    MEMORY_INIT_FILE   : string;
    MEMORY_INIT_PARAM  : string;
    WAKEUP_TIME        : string;
    MESSAGE_CONTROL    : integer;

    -- Port A module generics
    WRITE_DATA_WIDTH_A : integer;
    READ_DATA_WIDTH_A  : integer;
    BYTE_WRITE_WIDTH_A : integer;
    ADDR_WIDTH_A       : integer;
    READ_RESET_VALUE_A : string;
    READ_LATENCY_A     : integer;
    WRITE_MODE_A       : string
  );
  port (

    -- Common module ports
    sleep          : in  std_logic;

    -- Port A module ports
    clka           : in  std_logic;
    rsta           : in  std_logic;
    ena            : in  std_logic;
    regcea         : in  std_logic;
    wea            : in  std_logic_vector((WRITE_DATA_WIDTH_A/BYTE_WRITE_WIDTH_A)-1 downto 0);
    addra          : in  std_logic_vector(ADDR_WIDTH_A-1 downto 0);
    dina           : in  std_logic_vector(WRITE_DATA_WIDTH_A-1 downto 0);
    injectsbiterra : in  std_logic;
    injectdbiterra : in  std_logic;
    douta          : out std_logic_vector(READ_DATA_WIDTH_A-1 downto 0);
    sbiterra       : out std_logic;
    dbiterra       : out std_logic
  );
end component;


begin
   wea_vector(0) <= wea;
-----Cut code below this line and paste into the architecture body-----
xpm_memory_spram_inst : xpm_memory_spram
  generic map (

    -- Common module generics
    MEMORY_SIZE        => MEMORY_SIZE,        --positive integer
    MEMORY_PRIMITIVE   => MEMORY_PRIMITIVE,           --string; "auto", "distributed", "block" or "ultra" 
    ECC_MODE           => ECC_MODE,           --do not change
    MEMORY_INIT_FILE   => MEMORY_INIT_FILE,      --string; "none" or "<filename>.mem" 
    MEMORY_INIT_PARAM  => "",      --string
    WAKEUP_TIME        => WAKEUP_TIME,           --string; "disable_sleep" or "use_sleep_pin"
    MESSAGE_CONTROL    => MESSAGE_CONTROL,           --do not change

    -- Port A module generics
    WRITE_DATA_WIDTH_A => WRITE_DATA_WIDTH_A,          --positive integer
    READ_DATA_WIDTH_A  => READ_DATA_WIDTH_A,          --positive integer
    BYTE_WRITE_WIDTH_A => BYTE_WRITE_WIDTH_A,          --integer; 8, 9, or WRITE_DATA_WIDTH_A value
    ADDR_WIDTH_A       => ADDR_WIDTH_A,           --positive integer
    READ_RESET_VALUE_A => READ_RESET_VALUE_A, --string
    READ_LATENCY_A     => READ_LATENCY_A,           --non-negative integer
    WRITE_MODE_A       => WRITE_MODE_A            --string; "write_first", "read_first", "no_change"
  )
  port map (

    -- Common module ports
    sleep          =>  '0',  --do not change

    -- Port A module ports
    clka           =>  clka,
    rsta           =>  rsta,
    ena            =>  ena,
    regcea         =>  ena,
    wea            =>  wea_vector,
    addra          =>  addra,
    dina           =>  dina,
    injectsbiterra =>  '0',  --do not change
    injectdbiterra =>  '0',  --do not change
    douta          =>  douta,
    sbiterra       =>  open, --do not change
    dbiterra       =>  open  --do not change
  );
end rtl;

Library IEEE;
use IEEE.std_logic_1164.all;

entity krnl_partialKnn_wrapper_3_local_SP_0_A_V_XPM_MEMORY_URAM_1R1W is
    generic (
        DataWidth : INTEGER := 256;
        AddressRange : INTEGER := 4096;
        AddressWidth : INTEGER := 12);
    port (
        reset : IN STD_LOGIC;
        clk : IN STD_LOGIC;
        address0 : IN STD_LOGIC_VECTOR(AddressWidth - 1 DOWNTO 0);
        ce0 : IN STD_LOGIC;
        we0 : IN STD_LOGIC;
        d0 : IN STD_LOGIC_VECTOR(DataWidth - 1 DOWNTO 0);
        q0 : OUT STD_LOGIC_VECTOR(DataWidth - 1 DOWNTO 0));
end entity;

architecture arch of krnl_partialKnn_wrapper_3_local_SP_0_A_V_XPM_MEMORY_URAM_1R1W is
    component krnl_partialKnn_wrapper_3_local_SP_0_A_V_XPM_MEMORY_URAM_1R1W_ram is
        port (
            clka : IN STD_LOGIC;
            rsta : IN STD_LOGIC;
            addra : IN STD_LOGIC_VECTOR;
            ena : IN STD_LOGIC;
            dina : IN STD_LOGIC_VECTOR;
            wea : IN STD_LOGIC;
            douta : OUT STD_LOGIC_VECTOR);
    end component;



begin
    krnl_partialKnn_wrapper_3_local_SP_0_A_V_XPM_MEMORY_URAM_1R1W_ram_U :  component krnl_partialKnn_wrapper_3_local_SP_0_A_V_XPM_MEMORY_URAM_1R1W_ram
    port map (
        clka => clk,
        rsta => reset,
        addra => address0,
        ena => ce0,
        dina => d0,
        wea => we0,
        douta => q0);

end architecture;


