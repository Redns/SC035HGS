`timescale 1ns / 1ns
/*
Company : Liyang Milian Electronic Technology Co., Ltd.
Brand: Ã×Áª¿Í(milianke)
Technical forum:uisrc.com
taobao: https://milianke.taobao.com   https://osrc.taobao.com
jd:https://milianke.jd.com
Create Date: 2019/12/17
Module Name: fdma_test
Description: 
Copyright: Copyright (c) milianke
Revision: 1.0
Signal description:
1) _i input
2) _o output
3) _n activ lowpai
4) _dg debug signal 
5) _r delay or register
6) _s state mechine
*/
//////////////////////////////////////////////////////////////////////////////////

module fdma_test#
(
parameter TEST_MEM_SIZE   = 32'd536800000,
parameter FDMA_BURST_LEN  = 16'd1000,
parameter ADDR_MEM_OFFSET = 1024*1024*50
)
(
input               ui_clk,
input               fdma_rstn, 
output     [31: 0]  fdma_waddr,
output reg         fdma_wareq,
output     [15: 0]  fdma_wsize,                                     
input               fdma_wbusy,		
output reg [127:0]  fdma_wdata,
input                fdma_wvalid,
output               fdma_wready,

output     [31: 0]  fdma_raddr,
output reg         fdma_rareq,
output     [15: 0]  fdma_rsize,                                     
input               fdma_rbusy,			
input      [127:0]  fdma_rdata,
input               fdma_rvalid,
output              fdma_rready,
input               init_calib_complete
    );
  
parameter WRITE1 = 0;
parameter WRITE2 = 1;
parameter READ1  = 2;
parameter READ2  = 3;

reg [31: 0] fdma_waddr_r;
reg [16 :0] fdma_rcnt = 0;
reg [1  :0] T_S = 0;

assign fdma_waddr = fdma_waddr_r + ADDR_MEM_OFFSET;
assign fdma_raddr = fdma_waddr;

assign fdma_wsize = FDMA_BURST_LEN;
assign fdma_rsize = FDMA_BURST_LEN;

reg [10:0] rst_cnt = 0;

always @(posedge ui_clk)
    if(fdma_rstn == 1'b0)begin
        rst_cnt <=0;
    end 
    else begin
        if(rst_cnt[10] == 1'b0)
            rst_cnt <= rst_cnt + 1'b1;
        else 
            rst_cnt <= rst_cnt;
    end

assign fdma_wready = 1'b1;
assign fdma_rready = 1'b1;

always @(posedge ui_clk)begin
    if(rst_cnt[10] == 1'b0)begin
        T_S <=0;   
        fdma_wareq  <= 1'b0; 
        fdma_rareq  <= 1'b0; 
        fdma_wdata<=0;
        fdma_waddr_r <=0;       
    end 
    else begin
        case(T_S)      
        WRITE1:begin
            if(fdma_waddr_r>TEST_MEM_SIZE) fdma_waddr_r<=0; 
                if(!fdma_wbusy)begin
                    fdma_wareq  <= 1'b1; 
                    fdma_wdata  <= 0;
                end
                if(fdma_wareq&&fdma_wbusy)begin
                    fdma_wareq  <= 1'b0; 
                    T_S         <= WRITE2;
                end
        end
        WRITE2:begin
            if(!fdma_wbusy) begin
                 T_S <= READ1;
                 fdma_wdata  <= 32'd0;
            end 
            else if(fdma_wvalid) begin
                fdma_wdata <= fdma_wdata + 1'b1;
            end
        end
        
        READ1:begin
            if(!fdma_rbusy)begin
                fdma_rareq  <= 1'b1; 
                fdma_rcnt   <= 0;
            end
            if(fdma_rareq&&fdma_rbusy)begin
                 fdma_rareq  <= 1'b0; 
                 T_S         <= READ2;
            end 
        end
        READ2:begin
            if(!fdma_rbusy) begin
                 T_S <= WRITE1;
                 fdma_rcnt  <= 32'd0;
                 fdma_waddr_r  <= fdma_waddr_r + FDMA_BURST_LEN*16;//128/8=16
            end 
            else if(fdma_rvalid) begin
                fdma_rcnt <= fdma_rcnt + 1'b1;
            end
        end   
        default:
            T_S <= WRITE1;     
        endcase
    end
  end
  
wire test_error = ((fdma_rready&&fdma_rvalid) && (fdma_rcnt[15:0] != fdma_rdata[15:0]));

ila_0 ila_dbg (
	.clk(ui_clk), 
	.probe0({fdma_waddr[15:0],fdma_wdata[15:0],fdma_wareq,fdma_wvalid,fdma_wready,fdma_wbusy}),
	.probe1({fdma_rdata[15:0],fdma_rcnt[15:0],fdma_rvalid,fdma_rready,fdma_rbusy,T_S,test_error,fdma_rstn,init_calib_complete})
);
     
    
    
endmodule
