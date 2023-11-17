// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "dvi_transmitter_top,Vivado 2018.3" *)
module ov5640_hdmi_DVI_Transmitter_0_0(pclk, pclk_x5, reset_n, video_din, video_hsync, 
  video_vsync, video_de, tmds_clk_p, tmds_clk_n, tmds_data_p, tmds_data_n, tmds_oen);
  input pclk;
  input pclk_x5;
  input reset_n;
  input [23:0]video_din;
  input video_hsync;
  input video_vsync;
  input video_de;
  output tmds_clk_p;
  output tmds_clk_n;
  output [2:0]tmds_data_p;
  output [2:0]tmds_data_n;
  output tmds_oen;
endmodule
