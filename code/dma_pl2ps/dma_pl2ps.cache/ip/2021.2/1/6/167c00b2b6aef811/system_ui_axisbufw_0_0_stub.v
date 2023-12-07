// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2021.2 (win64) Build 3367213 Tue Oct 19 02:48:09 MDT 2021
// Date        : Wed Dec  6 20:04:28 2023
// Host        : Jing-Laptop running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
//               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ system_ui_axisbufw_0_0_stub.v
// Design      : system_ui_axisbufw_0_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7z035ffg676-2
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "ui_axisbufw,Vivado 2021.2" *)
module decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix(ui_rstn, W_wclk_i, W_FS_i, W_wren_i, W_data_i, 
  axis_clk, axis_keep, axis_wdata, axis_wvalid, axis_wready, axis_last)
/* synthesis syn_black_box black_box_pad_pin="ui_rstn,W_wclk_i,W_FS_i,W_wren_i,W_data_i[31:0],axis_clk,axis_keep[3:0],axis_wdata[31:0],axis_wvalid,axis_wready,axis_last" */;
  input ui_rstn;
  input W_wclk_i;
  input W_FS_i;
  input W_wren_i;
  input [31:0]W_data_i;
  input axis_clk;
  output [3:0]axis_keep;
  output [31:0]axis_wdata;
  output axis_wvalid;
  input axis_wready;
  output axis_last;
endmodule
