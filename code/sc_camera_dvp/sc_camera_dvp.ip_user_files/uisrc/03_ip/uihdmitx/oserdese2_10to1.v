`timescale 1ns / 1ps
/*
Company : Liyang Milian Electronic Technology Co., Ltd.
Brand: Ã×Áª¿Í(msxbo)
Technical forum£ºuisrc.com
taobao: osrc.taobao.com
Create Date: 2019/12/17
Module Name: oserdese2_10to1
Description: 
10: 1 serial transceiver
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

module oserdese2_10to1
(
input [9:0]txdata,
input pclk,
input clkdiv2,
input txrst,
output tx_p,
output tx_n
); 

wire [13:0] tx_data;
wire cascade_do, cascade_di, cascade_to, cascade_ti;
reg int_rst;
wire dai;

assign tx_data = {4'd0,txdata[9:0]};

//----------------------------------------------------------------------------------
//-- Reset should be asserted asynchronously an de-asserted synchronously
//----------------------------------------------------------------------------------
always @(*)
	if (txrst == 1'b1)
		int_rst <= 1'b1;
	else if(pclk)
		int_rst <= 1'b0;
    else 
        int_rst <= int_rst;
   

OBUFDS #(
      .IOSTANDARD("DEFAULT"), // Specify the output I/O standard
      .SLEW("SLOW")           // Specify the output slew rate
   ) OBUFDS_inst (
      .O(tx_p),     // Diff_p output (connect directly to top-level port)
      .OB(tx_n),   // Diff_n output (connect directly to top-level port)
      .I(dai)      // Buffer input
   );

//----------------------------------------------------------------------------------
//-- Cascaded OSERDES for 10:1 ratio (DDR)
//----------------------------------------------------------------------------------
OSERDESE2 #(
      .DATA_RATE_OQ("DDR"),   // DDR, SDR
      .DATA_RATE_TQ("SDR"),   // DDR, BUF, SDR
      .DATA_WIDTH(10),         // Parallel data width (2-8,10,14)
      .SERDES_MODE("MASTER"), // MASTER, SLAVE
      .TRISTATE_WIDTH(1)      // 3-state converter width (1,4)
   )
   oserdese2_master (
      // D1 - D8: 1-bit (each) input: Parallel data inputs (1-bit each)
      .D1(tx_data[0]),
      .D2(tx_data[1]),
      .D3(tx_data[2]),
      .D4(tx_data[3]),
      .D5(tx_data[4]),
      .D6(tx_data[5]),
      .D7(tx_data[6]),
      .D8(tx_data[7]),  
      // T1 - T4: 1-bit (each) input: Parallel 3-state inputs
      .T1(1'b0),
      .T2(1'b0),
      .T3(1'b0),
      .T4(1'b0), 
      // SHIFTIN1 / SHIFTIN2: 1-bit (each) input: Data input expansion (1-bit each)
      .SHIFTIN1(cascade_di),
      .SHIFTIN2(cascade_ti),
      // SHIFTOUT1 / SHIFTOUT2: 1-bit (each) output: Data output expansion (1-bit each)
      .SHIFTOUT1(),
      .SHIFTOUT2(),   
      .OCE(1'b1),             // 1-bit input: Output data clock enable    
      .CLK(clkdiv2),        // 1-bit input: High speed clock
      .CLKDIV(pclk),     // 1-bit input: Divided clock                       
      .OQ(dai),               // 1-bit output: Data path output
      .TQ(),               // 1-bit output: 3-state control
      .OFB(),             // 1-bit output: Feedback path for data
      .TBYTEIN(1'b0),     // 1-bit input: Byte group tristate      
      .TBYTEOUT(),   // 1-bit output: Byte group tristate
      .TFB(),             // 1-bit output: 3-state control
      .TCE(1'b0),          // 1-bit input: 3-state clock enable      
      .RST(int_rst)             // 1-bit input: Reset
   );

OSERDESE2 #(
      .DATA_RATE_OQ("DDR"),   // DDR, SDR
      .DATA_RATE_TQ("SDR"),   // DDR, BUF, SDR
      .DATA_WIDTH(10),         // Parallel data width (2-8,10,14)
      .SERDES_MODE("SLAVE"), // MASTER, SLAVE
      .TRISTATE_WIDTH(1)      // 3-state converter width (1,4)
   )
   oserdese2_slave (
      // D1 - D8: 1-bit (each) input: Parallel data inputs (1-bit each)
      .D1(1'b0),
      .D2(1'b0),
      .D3(tx_data[8]),
      .D4(tx_data[9]),
      .D5(tx_data[10]),
      .D6(tx_data[11]),
      .D7(tx_data[12]),
      .D8(tx_data[13]),  
      // T1 - T4: 1-bit (each) input: Parallel 3-state inputs
      .T1(1'b0),
      .T2(1'b0),
      .T3(1'b0),
      .T4(1'b0), 
      // SHIFTOUT1 / SHIFTOUT2: 1-bit (each) output: Data output expansion (1-bit each)
      .SHIFTOUT1(cascade_di),
      .SHIFTOUT2(cascade_ti),         
      // SHIFTIN1 / SHIFTIN2: 1-bit (each) input: Data input expansion (1-bit each)
      .SHIFTIN1(1'b0),
      .SHIFTIN2(1'b0),
      .OCE(1'b1),             // 1-bit input: Output data clock enable    
      .CLK(clkdiv2),        // 1-bit input: High speed clock
      .CLKDIV(pclk),     // 1-bit input: Divided clock                       
      .OQ(),               // 1-bit output: Data path output
      .TQ(),               // 1-bit output: 3-state control
      .OFB(),             // 1-bit output: Feedback path for data
      .TFB(),             // 1-bit output: 3-state control
      .TBYTEIN(1'b0),     // 1-bit input: Byte group tristate      
      .TBYTEOUT(),   // 1-bit output: Byte group tristate
      .TCE(1'b0),          // 1-bit input: 3-state clock enable      
      .RST(int_rst)             // 1-bit input: Reset
   ); 
    
endmodule
