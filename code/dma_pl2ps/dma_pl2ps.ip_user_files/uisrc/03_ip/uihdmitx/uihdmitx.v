`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
/*
Company : Liyang Milian Electronic Technology Co., Ltd.
Brand: Ã×Áª¿Í(msxbo)
Technical forum£ºuisrc.com
taobao: osrc.taobao.com
Create Date: 2019/12/17
Module Name: uihdmitx.v
Description: 
DMI DVI transmit module, support 7 series FPGA and 
ULTRASCALE, ULTRASCALE + FPGA
Copyright: Copyright (c) msxbo
Revision: 1.0
Signal description£º
1) _i input
2) _o output
3) _n activ low
4) _dg debug signal 
5) _r delay or register
6) _s state mechine
*/
////////////////////////////////////////////////////////////////////////////////

module uihdmitx#
(
parameter  FAMILY = "UFAMILY"			
)
(
input RSTn_i,
input VS_i,
input HS_i,
input VDE_i,
input [23:0] RGB_i,
input PCLKX1_i,
input PCLKX2_5_i,
input PCLKX5_i,
output TMDS_TX_CLK_P,
output TMDS_TX_CLK_N,
output [2:0]TMDS_TX_P,
output [2:0]TMDS_TX_N
);

wire [7:0] RED = RGB_i[23:16];
wire [7:0] GREEN = RGB_i[15:8];
wire [7:0] BLUE = RGB_i[7:0];  
wire [9:0] intTmdsRed;
wire [9:0] intTmdsGreen;
wire [9:0] intTmdsBlue;
    
wire intRst = !RSTn_i;
    
    //----------------------------------------------------------------------------------
    //-- DVI Encoder; DVI 1.0 Specifications
    //-- This component encodes 24-bit RGB video frames with sync signals into 10-bit
    //-- TMDS characters.
    //----------------------------------------------------------------------------------
TMDSEncoder Inst_TMDSEncoder_red
     (
     .D_I(RED),
     .C0_I(1'b0),
     .C1_I(1'b0),
     .DE_I(VDE_i),
     .CLK_I(PCLKX1_i),
     .D_O(intTmdsRed)
     );
TMDSEncoder Inst_TMDSEncoder_green
     (
     .D_I(GREEN),
     .C0_I(1'b0),
     .C1_I(1'b0),
     .DE_I(VDE_i),
     .CLK_I(PCLKX1_i),
     .D_O(intTmdsGreen)
     );
TMDSEncoder Inst_TMDSEncoder_blue(
     .D_I(BLUE),
     .C0_I(HS_i),
     .C1_I(VS_i),
     .DE_I(VDE_i),
     .CLK_I(PCLKX1_i),
     .D_O(intTmdsBlue)
    );
//----------------------------------------------------------------------------------
//-- TMDS serializer; ratio of 10:1; 3 data & 1 clock channel
// -- Since the TMDS clock's period is character-long (10-bit periods), the
// -- serialization of "1111100000" will result in a 10-bit long clock period.
//----------------------------------------------------------------------------------
generate  if(FAMILY == "UFAMILY")begin : ULTRASCALE_FAMILY 
oserdese3_10to1 Inst_clk_oserdese3_10to1
(
.txdata("1111100000"),
.txrst(intRst),
.pclk(PCLKX1_i),
.clkdiv2(PCLKX5_i),
.clkdiv4(PCLKX2_5_i),
.tx_p(TMDS_TX_CLK_P),
.tx_n(TMDS_TX_CLK_N)
); 
oserdese3_10to1 Inst_d2_serializer_10_1
(
.txdata(intTmdsRed),
.txrst(intRst),
.pclk(PCLKX1_i),
.clkdiv2(PCLKX5_i),
.clkdiv4(PCLKX2_5_i),
.tx_p(TMDS_TX_P[2]),
.tx_n(TMDS_TX_N[2])
);

oserdese3_10to1 Inst_d1_serializer_10_1
(
.txdata(intTmdsGreen),
.txrst(intRst),
.pclk(PCLKX1_i),
.clkdiv2(PCLKX5_i),
.clkdiv4(PCLKX2_5_i),
.tx_p(TMDS_TX_P[1]),
.tx_n(TMDS_TX_N[1])
);

oserdese3_10to1 Inst_d0_serializer_10_1
(
.txdata(intTmdsBlue),
.txrst(intRst),
.pclk(PCLKX1_i),
.clkdiv2(PCLKX5_i),
.clkdiv4(PCLKX2_5_i),
.tx_p(TMDS_TX_P[0]),
.tx_n(TMDS_TX_N[0])
);
end
else if(FAMILY == "7FAMILY")begin : family_7 
oserdese2_10to1 Inst_clk_oserdese2_10to1
(
.txdata("1111100000"),
.txrst(intRst),
.pclk(PCLKX1_i),
.clkdiv2(PCLKX5_i),
.tx_p(TMDS_TX_CLK_P),
.tx_n(TMDS_TX_CLK_N)
); 
oserdese2_10to1 Inst_d2_serializer_10_1
(
.txdata(intTmdsRed),
.txrst(intRst),
.pclk(PCLKX1_i),
.clkdiv2(PCLKX5_i),
.tx_p(TMDS_TX_P[2]),
.tx_n(TMDS_TX_N[2])
);

oserdese2_10to1 Inst_d1_serializer_10_1
(
.txdata(intTmdsGreen),
.txrst(intRst),
.pclk(PCLKX1_i),
.clkdiv2(PCLKX5_i),
.tx_p(TMDS_TX_P[1]),
.tx_n(TMDS_TX_N[1])
);

oserdese2_10to1 Inst_d0_serializer_10_1
(
.txdata(intTmdsBlue),
.txrst(intRst),
.pclk(PCLKX1_i),
.clkdiv2(PCLKX5_i),
.tx_p(TMDS_TX_P[0]),
.tx_n(TMDS_TX_N[0])
);
end
endgenerate
endmodule
