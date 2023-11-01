//Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Command: generate_target bd_16b9.bd
//Design : bd_16b9
//Purpose: IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CORE_GENERATION_INFO = "bd_16b9,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=bd_16b9,x_ipVersion=1.00.a,x_ipLanguage=VERILOG,numBlks=1,numReposBlks=1,numNonXlnxBlks=0,numHierBlks=0,maxHierDepth=0,numSysgenBlks=0,numHlsBlks=0,numHdlrefBlks=0,numPkgbdBlks=0,bdsource=SBD,synth_mode=OOC_per_IP}" *) (* HW_HANDOFF = "system_system_ila_0_4.hwdef" *) 
module bd_16b9
   (SLOT_0_IIC_scl_i,
    SLOT_0_IIC_scl_o,
    SLOT_0_IIC_scl_t,
    SLOT_0_IIC_sda_i,
    SLOT_0_IIC_sda_o,
    SLOT_0_IIC_sda_t,
    clk,
    probe0,
    probe1,
    probe2,
    probe3,
    probe4,
    probe5);
  (* X_INTERFACE_INFO = "xilinx.com:interface:iic:1.0 SLOT_0_IIC SCL_I" *) input SLOT_0_IIC_scl_i;
  (* X_INTERFACE_INFO = "xilinx.com:interface:iic:1.0 SLOT_0_IIC SCL_O" *) input SLOT_0_IIC_scl_o;
  (* X_INTERFACE_INFO = "xilinx.com:interface:iic:1.0 SLOT_0_IIC SCL_T" *) input SLOT_0_IIC_scl_t;
  (* X_INTERFACE_INFO = "xilinx.com:interface:iic:1.0 SLOT_0_IIC SDA_I" *) input SLOT_0_IIC_sda_i;
  (* X_INTERFACE_INFO = "xilinx.com:interface:iic:1.0 SLOT_0_IIC SDA_O" *) input SLOT_0_IIC_sda_o;
  (* X_INTERFACE_INFO = "xilinx.com:interface:iic:1.0 SLOT_0_IIC SDA_T" *) input SLOT_0_IIC_sda_t;
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 CLK.CLK CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME CLK.CLK, CLK_DOMAIN system_processing_system7_0_0_FCLK_CLK0, FREQ_HZ 1e+08, FREQ_TOLERANCE_HZ 0, INSERT_VIP 0, PHASE 0.0" *) input clk;
  input [0:0]probe0;
  input [7:0]probe1;
  input [0:0]probe2;
  input [0:0]probe3;
  input [0:0]probe4;
  input [0:0]probe5;

  wire SLOT_0_IIC_scl_i_1;
  wire SLOT_0_IIC_scl_o_1;
  wire SLOT_0_IIC_scl_t_1;
  wire SLOT_0_IIC_sda_i_1;
  wire SLOT_0_IIC_sda_o_1;
  wire SLOT_0_IIC_sda_t_1;
  wire clk_1;
  wire [0:0]probe0_1;
  wire [7:0]probe1_1;
  wire [0:0]probe2_1;
  wire [0:0]probe3_1;
  wire [0:0]probe4_1;
  wire [0:0]probe5_1;

  assign SLOT_0_IIC_scl_i_1 = SLOT_0_IIC_scl_i;
  assign SLOT_0_IIC_scl_o_1 = SLOT_0_IIC_scl_o;
  assign SLOT_0_IIC_scl_t_1 = SLOT_0_IIC_scl_t;
  assign SLOT_0_IIC_sda_i_1 = SLOT_0_IIC_sda_i;
  assign SLOT_0_IIC_sda_o_1 = SLOT_0_IIC_sda_o;
  assign SLOT_0_IIC_sda_t_1 = SLOT_0_IIC_sda_t;
  assign clk_1 = clk;
  assign probe0_1 = probe0[0];
  assign probe1_1 = probe1[7:0];
  assign probe2_1 = probe2[0];
  assign probe3_1 = probe3[0];
  assign probe4_1 = probe4[0];
  assign probe5_1 = probe5[0];
  bd_16b9_ila_lib_0 ila_lib
       (.clk(clk_1),
        .probe0(probe0_1),
        .probe1(probe1_1),
        .probe10(SLOT_0_IIC_sda_o_1),
        .probe11(SLOT_0_IIC_sda_t_1),
        .probe2(probe2_1),
        .probe3(probe3_1),
        .probe4(probe4_1),
        .probe5(probe5_1),
        .probe6(SLOT_0_IIC_scl_i_1),
        .probe7(SLOT_0_IIC_scl_o_1),
        .probe8(SLOT_0_IIC_scl_t_1),
        .probe9(SLOT_0_IIC_sda_i_1));
endmodule
