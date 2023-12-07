-- Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2021.2 (win64) Build 3367213 Tue Oct 19 02:48:09 MDT 2021
-- Date        : Wed Dec  6 20:04:28 2023
-- Host        : Jing-Laptop running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
--               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ system_ui_axisbufw_0_0_stub.vhdl
-- Design      : system_ui_axisbufw_0_0
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xc7z035ffg676-2
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix is
  Port ( 
    ui_rstn : in STD_LOGIC;
    W_wclk_i : in STD_LOGIC;
    W_FS_i : in STD_LOGIC;
    W_wren_i : in STD_LOGIC;
    W_data_i : in STD_LOGIC_VECTOR ( 31 downto 0 );
    axis_clk : in STD_LOGIC;
    axis_keep : out STD_LOGIC_VECTOR ( 3 downto 0 );
    axis_wdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    axis_wvalid : out STD_LOGIC;
    axis_wready : in STD_LOGIC;
    axis_last : out STD_LOGIC
  );

end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix;

architecture stub of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "ui_rstn,W_wclk_i,W_FS_i,W_wren_i,W_data_i[31:0],axis_clk,axis_keep[3:0],axis_wdata[31:0],axis_wvalid,axis_wready,axis_last";
attribute X_CORE_INFO : string;
attribute X_CORE_INFO of stub : architecture is "ui_axisbufw,Vivado 2021.2";
begin
end;
