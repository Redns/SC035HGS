`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
/*
Company : Liyang Milian Electronic Technology Co., Ltd.
Brand: Ã×Áª¿Í(msxbo)
Technical forum£ºuisrc.com
taobao: osrc.taobao.com
Create Date: 2019/12/17
Module Name: oserdese3_10to1
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


module oserdese3_10to1(
input [9:0] txdata,    // 7-bit pixel data
input       txrst,      // Reset for pixel logic synchronus to pclk
input       pclk,       // Pixel clock running at 1/7 transmit rate
input       clkdiv2,    // Transmit clock running at 1/2 transmit rate
input       clkdiv4,    // Transmit clock running at 1/4 transmit rate
output      tx_p,      // Transmit output P-side
output      tx_n       // Transmit output N-side
);

reg  [3:0]  wr_addr;
reg  [3:0]  rd_addr;
wire [9:0]  rd_curr;
reg  [9:2]  rd_last;
reg  [2:0]  RD_S;

reg  [3:0]  tx_data;
wire        oserdes_out;       
//
// FIFO Write address is continuous counter
//
reg [7:0]cnt_rst = 8'd0;
always @ (posedge pclk)begin
    if(txrst)begin
        cnt_rst <= 8'd0;
    end
    else if(!cnt_rst[7])
        cnt_rst <= cnt_rst + 1'b1;
end

always @ (posedge pclk)begin
      if(!cnt_rst[7])begin
       wr_addr <= 4'd0;
      end 
      else begin
       wr_addr <= wr_addr + 1'b1;
      end
end
//
// Generate 7 Dual Port Distributed RAMS for FIFO
//
genvar i;
generate
for (i = 0 ; i <= 9 ; i = i+1) begin : bit
  RAM32X1D mem (
     .D     (txdata[i]),
     .WCLK  (pclk),
     .WE    (cnt_rst[7]),
     .A0    (wr_addr[0]),
     .A1    (wr_addr[1]),
     .A2    (wr_addr[2]),
     .A3    (wr_addr[3]),
     .A4    (1'b0),
     .SPO   (),
     .DPRA0 (rd_addr[0]),
     .DPRA1 (rd_addr[1]),
     .DPRA2 (rd_addr[2]),
     .DPRA3 (rd_addr[3]),
     .DPRA4 (1'b0),
     .DPO   (rd_curr[i]));
end

endgenerate

//
// Store last read data for one cycle
//
always @ (posedge clkdiv4)begin
    rd_last[9:2] <= rd_curr[9:2];
end

//
// Read state machine and gear box
//
always @ (posedge clkdiv4)begin
    if(!cnt_rst[7])begin
       RD_S<= 3'd0;
       rd_addr <= 4'd0;
    end 
    else begin
       case (RD_S) 
         3'h0 : begin 
            rd_addr <= rd_addr;
            tx_data <= rd_curr[3:0];
            RD_S<= RD_S + 1'b1;
            end
         3'h1 : begin 
            rd_addr <= rd_addr + 1'b1;
            tx_data <= rd_curr[7:4];
            RD_S<= RD_S + 1'b1;
            end				
         3'h2 : begin 
            rd_addr <= rd_addr;
            tx_data <= {rd_curr[1:0], rd_last[9:8]};
            RD_S<= RD_S + 1'b1;
            end
         3'h3 : begin 
            rd_addr <= rd_addr + 1'b1;
            tx_data <= rd_curr[5:2];
            RD_S<= RD_S + 1'b1;
            end
         3'h4 : begin 
            rd_addr <= rd_addr; 
            tx_data <= rd_last[9:6];
            RD_S<= 3'h0;
            end              
          default:begin
            RD_S<= 3'd0;
            rd_addr <= 4'd0;
          end
       endcase
     end
end

//
// OSERDESE3 in 4:1 DDR Mode
//
   OSERDESE3 #(
      .DATA_WIDTH(4),            // Parallel Data Width (4-8)
      .INIT(1'b0),               // Initialization value of the OSERDES flip-flops
      .IS_CLKDIV_INVERTED(1'b0), // Optional inversion for CLKDIV
      .IS_CLK_INVERTED(1'b0),    // Optional inversion for CLK
      .IS_RST_INVERTED(1'b0),    // Optional inversion for RST
      .SIM_DEVICE("ULTRASCALE")  // Set the device version (ULTRASCALE, ULTRASCALE_PLUS, ULTRASCALE_PLUS_ES1, // ULTRASCALE_PLUS_ES2)                           
   )
   OSERDESE3_inst (
      .OQ(oserdes_out),         // 1-bit output: Serial Output Data
      .T_OUT(),   // 1-bit output: 3-state control output to IOB
      .CLK(clkdiv2),       // 1-bit input: High-speed clock
      .CLKDIV(clkdiv4), // 1-bit input: Divided Clock
      .D({4'b0,tx_data[3:0]}),           // 8-bit input: Parallel Data Input
      .RST(!cnt_rst[7]),       // 1-bit input: Asynchronous Reset
      .T(1'b0)            // 1-bit input: Tristate input from fabric
   );
 
OBUFDS io_clk_out (
    .I        (oserdes_out),
    .O        (tx_p),
    .OB       (tx_n));

endmodule
  
