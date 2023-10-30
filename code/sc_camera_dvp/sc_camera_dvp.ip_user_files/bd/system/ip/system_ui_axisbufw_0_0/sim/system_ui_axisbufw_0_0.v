// (c) Copyright 1995-2023 Xilinx, Inc. All rights reserved.
// 
// This file contains confidential and proprietary information
// of Xilinx, Inc. and is protected under U.S. and
// international copyright and other intellectual property
// laws.
// 
// DISCLAIMER
// This disclaimer is not a license and does not grant any
// rights to the materials distributed herewith. Except as
// otherwise provided in a valid license issued to you by
// Xilinx, and to the maximum extent permitted by applicable
// law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
// WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
// AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
// BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
// INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
// (2) Xilinx shall not be liable (whether in contract or tort,
// including negligence, or under any other theory of
// liability) for any loss or damage of any kind or nature
// related to, arising under or in connection with these
// materials, including for any direct, or any indirect,
// special, incidental, or consequential loss or damage
// (including loss of data, profits, goodwill, or any type of
// loss or damage suffered as a result of any action brought
// by a third party) even if such damage or loss was
// reasonably foreseeable or Xilinx had been advised of the
// possibility of the same.
// 
// CRITICAL APPLICATIONS
// Xilinx products are not designed or intended to be fail-
// safe, or for use in any application requiring fail-safe
// performance, such as life-support or safety devices or
// systems, Class III medical devices, nuclear facilities,
// applications related to the deployment of airbags, or any
// other applications that could lead to death, personal
// injury, or severe property or environmental damage
// (individually and collectively, "Critical
// Applications"). Customer assumes the sole risk and
// liability of any use of Xilinx products in Critical
// Applications, subject only to applicable laws and
// regulations governing limitations on product liability.
// 
// THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
// PART OF THIS FILE AT ALL TIMES.
// 
// DO NOT MODIFY THIS FILE.


// IP VLNV: xilinx.com:user:ui_axisbufw:1.0
// IP Revision: 4

`timescale 1ns/1ps

(* IP_DEFINITION_SOURCE = "package_project" *)
(* DowngradeIPIdentifiedWarnings = "yes" *)
module system_ui_axisbufw_0_0 (
  ui_rstn,
  W_wclk_i,
  W_FS_i,
  W_wren_i,
  W_data_i,
  axis_clk,
  axis_keep,
  axis_wdata,
  axis_wvalid,
  axis_wready,
  axis_last
);

input wire ui_rstn;
input wire W_wclk_i;
input wire W_FS_i;
input wire W_wren_i;
input wire [7 : 0] W_data_i;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME axis_clk, ASSOCIATED_BUSIF axis_m, FREQ_TOLERANCE_HZ 0, PHASE 0.0, CLK_DOMAIN system_processing_system7_0_0_FCLK_CLK0, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 axis_clk CLK" *)
input wire axis_clk;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 axis_m TKEEP" *)
output wire [3 : 0] axis_keep;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 axis_m TDATA" *)
output wire [31 : 0] axis_wdata;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 axis_m TVALID" *)
output wire axis_wvalid;
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 axis_m TREADY" *)
input wire axis_wready;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME axis_m, TDATA_NUM_BYTES 4, TDEST_WIDTH 0, TID_WIDTH 0, TUSER_WIDTH 0, HAS_TREADY 1, HAS_TSTRB 0, HAS_TKEEP 1, HAS_TLAST 1, PHASE 0.0, CLK_DOMAIN system_processing_system7_0_0_FCLK_CLK0, LAYERED_METADATA undef, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 axis_m TLAST" *)
output wire axis_last;

  ui_axisbufw #(
    .VIDEO_ENABLE(1'B0),
    .AXI_DATA_WIDTH(32),
    .W_BUFDEPTH(2048),
    .W_DATAWIDTH(8),
    .W_XSIZE(1024),
    .W_YSIZE(1024)
  ) inst (
    .ui_rstn(ui_rstn),
    .W_wclk_i(W_wclk_i),
    .W_FS_i(W_FS_i),
    .W_wren_i(W_wren_i),
    .W_data_i(W_data_i),
    .axis_clk(axis_clk),
    .axis_keep(axis_keep),
    .axis_wdata(axis_wdata),
    .axis_wvalid(axis_wvalid),
    .axis_wready(axis_wready),
    .axis_last(axis_last)
  );
endmodule
