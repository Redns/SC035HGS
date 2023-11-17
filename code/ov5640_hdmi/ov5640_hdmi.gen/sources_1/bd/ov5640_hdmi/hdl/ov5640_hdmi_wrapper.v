//Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2021.2 (win64) Build 3367213 Tue Oct 19 02:48:09 MDT 2021
//Date        : Fri Oct 20 19:54:40 2023
//Host        : JingDevice running 64-bit major release  (build 9200)
//Command     : generate_target ov5640_hdmi_wrapper.bd
//Design      : ov5640_hdmi_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module ov5640_hdmi_wrapper
   (DDR_addr,
    DDR_ba,
    DDR_cas_n,
    DDR_ck_n,
    DDR_ck_p,
    DDR_cke,
    DDR_cs_n,
    DDR_dm,
    DDR_dq,
    DDR_dqs_n,
    DDR_dqs_p,
    DDR_odt,
    DDR_ras_n,
    DDR_reset_n,
    DDR_we_n,
    FIXED_IO_ddr_vrn,
    FIXED_IO_ddr_vrp,
    FIXED_IO_mio,
    FIXED_IO_ps_clk,
    FIXED_IO_ps_porb,
    FIXED_IO_ps_srstb,
    gpio_tri_io,
    i_href,
    i_pclk,
    i_pixel_data,
    i_vsync,
    o_tmds_oen,
    o_tmds_tmds_clk_n,
    o_tmds_tmds_clk_p,
    o_tmds_tmds_data_n,
    o_tmds_tmds_data_p,
    o_xclk_24MHz);
  inout [14:0]DDR_addr;
  inout [2:0]DDR_ba;
  inout DDR_cas_n;
  inout DDR_ck_n;
  inout DDR_ck_p;
  inout DDR_cke;
  inout DDR_cs_n;
  inout [3:0]DDR_dm;
  inout [31:0]DDR_dq;
  inout [3:0]DDR_dqs_n;
  inout [3:0]DDR_dqs_p;
  inout DDR_odt;
  inout DDR_ras_n;
  inout DDR_reset_n;
  inout DDR_we_n;
  inout FIXED_IO_ddr_vrn;
  inout FIXED_IO_ddr_vrp;
  inout [53:0]FIXED_IO_mio;
  inout FIXED_IO_ps_clk;
  inout FIXED_IO_ps_porb;
  inout FIXED_IO_ps_srstb;
  inout [4:0]gpio_tri_io;
  input i_href;
  input i_pclk;
  input [7:0]i_pixel_data;
  input i_vsync;
  output o_tmds_oen;
  output o_tmds_tmds_clk_n;
  output o_tmds_tmds_clk_p;
  output [2:0]o_tmds_tmds_data_n;
  output [2:0]o_tmds_tmds_data_p;
  output o_xclk_24MHz;

  wire [14:0]DDR_addr;
  wire [2:0]DDR_ba;
  wire DDR_cas_n;
  wire DDR_ck_n;
  wire DDR_ck_p;
  wire DDR_cke;
  wire DDR_cs_n;
  wire [3:0]DDR_dm;
  wire [31:0]DDR_dq;
  wire [3:0]DDR_dqs_n;
  wire [3:0]DDR_dqs_p;
  wire DDR_odt;
  wire DDR_ras_n;
  wire DDR_reset_n;
  wire DDR_we_n;
  wire FIXED_IO_ddr_vrn;
  wire FIXED_IO_ddr_vrp;
  wire [53:0]FIXED_IO_mio;
  wire FIXED_IO_ps_clk;
  wire FIXED_IO_ps_porb;
  wire FIXED_IO_ps_srstb;
  wire [0:0]gpio_tri_i_0;
  wire [1:1]gpio_tri_i_1;
  wire [2:2]gpio_tri_i_2;
  wire [3:3]gpio_tri_i_3;
  wire [4:4]gpio_tri_i_4;
  wire [0:0]gpio_tri_io_0;
  wire [1:1]gpio_tri_io_1;
  wire [2:2]gpio_tri_io_2;
  wire [3:3]gpio_tri_io_3;
  wire [4:4]gpio_tri_io_4;
  wire [0:0]gpio_tri_o_0;
  wire [1:1]gpio_tri_o_1;
  wire [2:2]gpio_tri_o_2;
  wire [3:3]gpio_tri_o_3;
  wire [4:4]gpio_tri_o_4;
  wire [0:0]gpio_tri_t_0;
  wire [1:1]gpio_tri_t_1;
  wire [2:2]gpio_tri_t_2;
  wire [3:3]gpio_tri_t_3;
  wire [4:4]gpio_tri_t_4;
  wire i_href;
  wire i_pclk;
  wire [7:0]i_pixel_data;
  wire i_vsync;
  wire o_tmds_oen;
  wire o_tmds_tmds_clk_n;
  wire o_tmds_tmds_clk_p;
  wire [2:0]o_tmds_tmds_data_n;
  wire [2:0]o_tmds_tmds_data_p;
  wire o_xclk_24MHz;

  IOBUF gpio_tri_iobuf_0
       (.I(gpio_tri_o_0),
        .IO(gpio_tri_io[0]),
        .O(gpio_tri_i_0),
        .T(gpio_tri_t_0));
  IOBUF gpio_tri_iobuf_1
       (.I(gpio_tri_o_1),
        .IO(gpio_tri_io[1]),
        .O(gpio_tri_i_1),
        .T(gpio_tri_t_1));
  IOBUF gpio_tri_iobuf_2
       (.I(gpio_tri_o_2),
        .IO(gpio_tri_io[2]),
        .O(gpio_tri_i_2),
        .T(gpio_tri_t_2));
  IOBUF gpio_tri_iobuf_3
       (.I(gpio_tri_o_3),
        .IO(gpio_tri_io[3]),
        .O(gpio_tri_i_3),
        .T(gpio_tri_t_3));
  IOBUF gpio_tri_iobuf_4
       (.I(gpio_tri_o_4),
        .IO(gpio_tri_io[4]),
        .O(gpio_tri_i_4),
        .T(gpio_tri_t_4));
  ov5640_hdmi ov5640_hdmi_i
       (.DDR_addr(DDR_addr),
        .DDR_ba(DDR_ba),
        .DDR_cas_n(DDR_cas_n),
        .DDR_ck_n(DDR_ck_n),
        .DDR_ck_p(DDR_ck_p),
        .DDR_cke(DDR_cke),
        .DDR_cs_n(DDR_cs_n),
        .DDR_dm(DDR_dm),
        .DDR_dq(DDR_dq),
        .DDR_dqs_n(DDR_dqs_n),
        .DDR_dqs_p(DDR_dqs_p),
        .DDR_odt(DDR_odt),
        .DDR_ras_n(DDR_ras_n),
        .DDR_reset_n(DDR_reset_n),
        .DDR_we_n(DDR_we_n),
        .FIXED_IO_ddr_vrn(FIXED_IO_ddr_vrn),
        .FIXED_IO_ddr_vrp(FIXED_IO_ddr_vrp),
        .FIXED_IO_mio(FIXED_IO_mio),
        .FIXED_IO_ps_clk(FIXED_IO_ps_clk),
        .FIXED_IO_ps_porb(FIXED_IO_ps_porb),
        .FIXED_IO_ps_srstb(FIXED_IO_ps_srstb),
        .gpio_tri_i({gpio_tri_i_4,gpio_tri_i_3,gpio_tri_i_2,gpio_tri_i_1,gpio_tri_i_0}),
        .gpio_tri_o({gpio_tri_o_4,gpio_tri_o_3,gpio_tri_o_2,gpio_tri_o_1,gpio_tri_o_0}),
        .gpio_tri_t({gpio_tri_t_4,gpio_tri_t_3,gpio_tri_t_2,gpio_tri_t_1,gpio_tri_t_0}),
        .i_href(i_href),
        .i_pclk(i_pclk),
        .i_pixel_data(i_pixel_data),
        .i_vsync(i_vsync),
        .o_tmds_oen(o_tmds_oen),
        .o_tmds_tmds_clk_n(o_tmds_tmds_clk_n),
        .o_tmds_tmds_clk_p(o_tmds_tmds_clk_p),
        .o_tmds_tmds_data_n(o_tmds_tmds_data_n),
        .o_tmds_tmds_data_p(o_tmds_tmds_data_p),
        .o_xclk_24MHz(o_xclk_24MHz));
endmodule
