-- Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
-- Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2023.2 (win64) Build 4029153 Fri Oct 13 20:14:34 MDT 2023
-- Date        : Thu Feb 22 20:52:33 2024
-- Host        : Jing-WorkStation running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode funcsim
--               d:/Project/sc_camera/code/sc035hgs_hdmi/sc035hgs_hdmi.gen/sources_1/bd/bd_system/ip/bd_system_sc035hgs_0_0/bd_system_sc035hgs_0_0_sim_netlist.vhdl
-- Design      : bd_system_sc035hgs_0_0
-- Purpose     : This VHDL netlist is a functional simulation representation of the design and should not be modified or
--               synthesized. This netlist cannot be used for SDF annotated simulation.
-- Device      : xc7z010clg400-2
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity bd_system_sc035hgs_0_0 is
  port (
    pclk : in STD_LOGIC;
    fsync : in STD_LOGIC;
    href : in STD_LOGIC;
    pixel : in STD_LOGIC_VECTOR ( 7 downto 0 );
    vid_clk : out STD_LOGIC;
    vid_vsync : out STD_LOGIC;
    vid_hsync : out STD_LOGIC;
    vid_data : out STD_LOGIC_VECTOR ( 23 downto 0 )
  );
  attribute NotValidForBitStream : boolean;
  attribute NotValidForBitStream of bd_system_sc035hgs_0_0 : entity is true;
  attribute CHECK_LICENSE_TYPE : string;
  attribute CHECK_LICENSE_TYPE of bd_system_sc035hgs_0_0 : entity is "bd_system_sc035hgs_0_0,sc035hgs,{}";
  attribute DowngradeIPIdentifiedWarnings : string;
  attribute DowngradeIPIdentifiedWarnings of bd_system_sc035hgs_0_0 : entity is "yes";
  attribute IP_DEFINITION_SOURCE : string;
  attribute IP_DEFINITION_SOURCE of bd_system_sc035hgs_0_0 : entity is "module_ref";
  attribute X_CORE_INFO : string;
  attribute X_CORE_INFO of bd_system_sc035hgs_0_0 : entity is "sc035hgs,Vivado 2023.2";
end bd_system_sc035hgs_0_0;

architecture STRUCTURE of bd_system_sc035hgs_0_0 is
  signal \^href\ : STD_LOGIC;
  signal \^pclk\ : STD_LOGIC;
  signal \^pixel\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  attribute X_INTERFACE_INFO : string;
  attribute X_INTERFACE_INFO of vid_clk : signal is "xilinx.com:signal:clock:1.0 vid_clk CLK";
  attribute X_INTERFACE_PARAMETER : string;
  attribute X_INTERFACE_PARAMETER of vid_clk : signal is "XIL_INTERFACENAME vid_clk, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, PHASE 0.0, CLK_DOMAIN bd_system_sc035hgs_0_0_vid_clk, INSERT_VIP 0";
begin
  \^href\ <= href;
  \^pclk\ <= pclk;
  \^pixel\(7 downto 0) <= pixel(7 downto 0);
  vid_clk <= \^pclk\;
  vid_data(23 downto 16) <= \^pixel\(7 downto 0);
  vid_data(15 downto 8) <= \^pixel\(7 downto 0);
  vid_data(7 downto 0) <= \^pixel\(7 downto 0);
  vid_hsync <= \^href\;
vid_vsync_INST_0: unisim.vcomponents.LUT2
    generic map(
      INIT => X"B"
    )
        port map (
      I0 => \^href\,
      I1 => fsync,
      O => vid_vsync
    );
end STRUCTURE;
