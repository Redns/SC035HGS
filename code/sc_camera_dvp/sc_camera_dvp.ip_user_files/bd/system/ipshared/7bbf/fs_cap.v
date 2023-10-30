/*******************************MILIANKE*******************************
*Company : MiLianKe Electronic Technology Co., Ltd.
*WebSite:https://www.milianke.com
*TechWeb:https://www.uisrc.com
*tmall-shop:https://milianke.tmall.com
*jd-shop:https://milianke.jd.com
*taobao-shop1: https://milianke.taobao.com
*Create Date: 2021/10/15
*Module Name:fs_cap
*File Name:fs_cap.v
*Description: 
*The reference demo provided by Milianke is only used for learning. 
*We cannot ensure that the demo itself is free of bugs, so users 
*should be responsible for the technical problems and consequences
*caused by the use of their own products.
*Copyright: Copyright (c) MiLianKe
*All rights reserved.
*Revision: 1.0
*Signal description
*1) _i input
*2) _o output
*3) _n activ low
*4) _dg debug signal 
*5) _r delay or register
*6) _s state mechine
*********************************************************************/
`timescale 1ns / 1ps

module fs_cap#(
parameter  integer  VIDEO_ENABLE   = 1
)
(
input  clk_i,
input  rstn_i,
input  vs_i,
output reg fs_cap_o
);
    

reg[4:0]CNT_FS   = 6'b0;
reg[4:0]CNT_FS_n = 6'b0;
reg     FS       = 1'b0;
(* ASYNC_REG = "TRUE" *)   reg vs_i_r1;
(* ASYNC_REG = "TRUE" *)   reg vs_i_r2;
(* ASYNC_REG = "TRUE" *)   reg vs_i_r3;
(* ASYNC_REG = "TRUE" *)   reg vs_i_r4;

always@(posedge clk_i) begin
      vs_i_r1 <= vs_i;
      vs_i_r2 <= vs_i_r1;
      vs_i_r3 <= vs_i_r2;
      vs_i_r4 <= vs_i_r3;
end

always@(posedge clk_i) begin
   if(!rstn_i)begin
      fs_cap_o <= 1'd0;
   end
   else if(VIDEO_ENABLE == 1)begin
      if({vs_i_r4,vs_i_r3} == 2'b01)begin
         fs_cap_o <= 1'b1;
      end
      else begin
         fs_cap_o <= 1'b0;
      end
   end 
   else begin
         fs_cap_o <= vs_i_r4;
   end
end
        
endmodule
