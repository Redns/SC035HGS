`timescale 1ns / 1ps
/*
Company : Liyang Milian Electronic Technology Co., Ltd.
Brand: 米联客(msxbo)
Technical forum:uisrc.com
taobao: osrc.taobao.com
Create Date: 2019/12/17
Module Name: fdma_controller
Description: 
Copyright: Copyright (c) msxbo
Revision: 1.0
Signal description:
1) _i input
2) _o output
3) _n activ low
4) _dg debug signal 
5) _r delay or register
6) _s state mechine
*/
//////////////////////////////////////////////////////////////////////////////////

module fdma_controller#
(
parameter  integer  ADDR_OFFSET = 0,
parameter  integer  BUF_SIZE = 3,
parameter  integer  H_CNT = 640, 
parameter  integer  V_CNT = 480			
)
(
    input           ui_clk,
    input           ui_rstn,
//sensor input -W0_FIFO--------------
    input           W0_FS_i,
    input           W0_wclk_i,
    input           W0_wren_i,
    input  [31:0]   W0_data_i, 
//hdmi output -R0_FIFO--------------- 
    input           R0_FS_i,
    input           R0_rclk_i,
    input           R0_rden_i,
    output[31:0]    R0_data_o,
//----------fdma signals write-------       
    output  reg     pkg_wr_areq,       
    input           pkg_wr_en,
    input           pkg_wr_last,
    output  [31:0]  pkg_wr_addr,
    output  [127:0] pkg_wr_data,
    output  [31:0]  pkg_wr_size,
//----------fdma signals read---------       
    output  reg     pkg_rd_areq, 
    input           pkg_rd_en,   
    input           pkg_rd_last,         
    output  [31:0]  pkg_rd_addr,
    input   [127:0] pkg_rd_data,
    output  [31:0]  pkg_rd_size    
    );
    
parameter FBUF_SIZE = BUF_SIZE -1'b1;
parameter BURST_SIZE  = 1024*4;// one time 4KB
parameter BURST_TIMES = H_CNT*V_CNT/1024;// one frame burst times
parameter PKG_SIZE    = 256;
assign pkg_wr_size = PKG_SIZE;
assign pkg_rd_size = PKG_SIZE;

//------------vs 滤波---------------
reg  W0_FIFO_Rst; 
reg  R0_FIFO_Rst;
 
wire W0_FS;
wire R0_FS;  

reg [6:0] W0_Fbuf;
reg [6:0] R0_Fbuf;


fs_cap fs_cap_W0(
  .clk_i(ui_clk),
  .rstn_i(ui_rstn),
  .vs_i(W0_FS_i),
  .fs_cap_o(W0_FS)
);

fs_cap fs_cap_R0(
  .clk_i(ui_clk),
  .rstn_i(ui_rstn),
  .vs_i(R0_FS_i),
  .fs_cap_o(R0_FS)
);

parameter S_IDLE  =  2'd0;  
parameter S_RST   =  2'd1;  
parameter S_DATA1 =  2'd2;   
parameter S_DATA2 =  2'd3; 

reg [1  :0]  W_MS;
reg [22:0]  W0_addr;
reg [31 :0]  W0_fcnt;
reg [10  :0] W0_bcnt;
wire [10:0]  W0_rcnt;
reg W0_REQ;
reg [1 :0]  R_MS;
reg [22 :0] R0_addr;
reg [31 :0] R0_fcnt;
reg [10 :0] R0_bcnt;
wire [10:0] R0_wcnt;
reg R0_REQ;

assign pkg_wr_addr = {W0_Fbuf,W0_addr}+ ADDR_OFFSET;
assign pkg_rd_addr = {R0_Fbuf,R0_addr}+ ADDR_OFFSET;
//assign pkg_wr_data = W0_fcnt;
//--------一副图像写入DDR------------
 always @(posedge ui_clk) begin
    if(!ui_rstn)begin
        W_MS <= S_IDLE;
        W0_addr <= 21'd0;
        pkg_wr_areq <= 1'd0;
        W0_FIFO_Rst <= 1'b1;
        W0_fcnt <= 0;
        W0_bcnt <= 0;
        W0_Fbuf <= 7'd0;
    end
    else begin
      case(W_MS)
       S_IDLE:begin
          W0_addr <= 21'd0;
          W0_fcnt <= 0;
          W0_bcnt <= 11'd0;
          if(W0_FS) W_MS <= S_RST;
       end
       S_RST:begin
          if(W0_fcnt > 8'd20 ) W_MS <= S_DATA1;
          W0_FIFO_Rst <= (W0_fcnt < 8'd10); 
          W0_fcnt <= W0_fcnt +1'd1;
        end          
        S_DATA1:begin 
            if(W0_bcnt == BURST_TIMES) begin
                if(W0_Fbuf == FBUF_SIZE) 
                    W0_Fbuf <= 7'd0;
                 else 
                    W0_Fbuf <= W0_Fbuf + 1'b1; 
                 W_MS <= S_IDLE;
            end
            else if(W0_REQ) begin
                W0_fcnt <=0;
                pkg_wr_areq <= 1'b1;
                W_MS <= S_DATA2;  
            end           
         end
         S_DATA2:begin
            pkg_wr_areq <= 1'b0; 
            if(pkg_wr_last)begin
                W_MS <= S_DATA1; 
                W0_bcnt <= W0_bcnt + 1'd1; 
                W0_addr <= W0_addr + BURST_SIZE;
            end
         end
       endcase
    end
 end 

//--------一副图像读出DDR------------
 always @(posedge ui_clk) begin
   if(!ui_rstn)begin
       R_MS <= S_IDLE;
       R0_addr <= 21'd0;
       pkg_rd_areq <= 1'd0;
       R0_fcnt <=0;
       R0_bcnt <=0;
       R0_FIFO_Rst <= 1'b1;
       R0_Fbuf <= 7'd0;       
   end
   else begin
     case(R_MS)
       S_IDLE:begin
         R0_addr <= 21'd0;
         R0_fcnt <=0;
         R0_bcnt <=0;
         if(R0_FS) R_MS <= S_RST;
       end 
       S_RST:begin
         if(R0_fcnt > 8'd20 ) R_MS <= S_DATA1;
         R0_FIFO_Rst <= (R0_fcnt < 8'd10); 
         R0_fcnt <= R0_fcnt + 1'd1;
       end  
       S_DATA1:begin 
           if(R0_bcnt == BURST_TIMES ) begin
               R_MS <= S_IDLE;
               if(W0_Fbuf == 7'd0) 
                    R0_Fbuf <= FBUF_SIZE;
                else 
                    R0_Fbuf <= W0_Fbuf - 1'b1;   
           end
           else if(R0_REQ) begin
               pkg_rd_areq <= 1'b1;
               R_MS <= S_DATA2;  
           end           
        end
        S_DATA2:begin
           pkg_rd_areq <= 1'b0;   
           if(pkg_rd_last)begin
               R_MS <= S_DATA1; 
               R0_bcnt <= R0_bcnt + 1'd1; 
               R0_addr <= R0_addr + BURST_SIZE;
           end
        end
      endcase
   end
end 

 always@(posedge ui_clk)
 begin     
     W0_REQ    <= (W0_rcnt    > PKG_SIZE -5); 
     R0_REQ    <= (R0_wcnt    < PKG_SIZE -5); 
 end
 
W0_FIFO W0_FIFO_0 (
  .rst(W0_FIFO_Rst),  // input wire rst
  .wr_clk(W0_wclk_i),  // input wire wr_clk
  .din(W0_data_i),        // input wire [31 : 0] din
  .wr_en(W0_wren_i),    // input wire wr_en
  .rd_clk(ui_clk),  // input wire rd_clk 
  .rd_en(pkg_wr_en),    // input wire rd_en
  .dout(pkg_wr_data),      // output wire [63 : 0] dout
  .rd_data_count(W0_rcnt)  // output wire [10 : 0] wr_data_count
);

 R0_FIFO R0_FIFO_0 (
  .rst(R0_FIFO_Rst),  // input wire rst
  .wr_clk(ui_clk),  // input wire wr_clk
  .din(pkg_rd_data),        // input wire [63 : 0] din
  .wr_en(pkg_rd_en),    // input wire wr_en
  .wr_data_count(R0_wcnt),  // output wire [6 : 0] rd_data_count
  .rd_clk(R0_rclk_i),  // input wire rd_clk 
  .rd_en(R0_rden_i),    // input wire rd_en
  .dout(R0_data_o)      // output wire [31 : 0] dout
);

endmodule

