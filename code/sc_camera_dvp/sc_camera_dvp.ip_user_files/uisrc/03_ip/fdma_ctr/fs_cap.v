`timescale 1ns / 1ps
/*
Company : Liyang Milian Electronic Technology Co., Ltd.
Brand: 米联客(msxbo)
Technical forum:uisrc.com
taobao: osrc.taobao.com
Create Date: 2019/12/17
Module Name: fs_cap
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
////////////////////////////////////////////////////////////////////////////////


module fs_cap(
    input  clk_i,
    input  rstn_i,
    input  vs_i,
    output reg fs_cap_o
    );
    
//----CH0_CNT_FS信号电平计数 实际就是采样VS信号----------------
reg[4:0]CNT_FS   = 6'b0;
reg[4:0]CNT_FS_n = 6'b0;
reg     FS       = 1'b0;
(* ASYNC_REG = "TRUE" *)   reg vs_i_r1;
(* ASYNC_REG = "TRUE" *)   reg vs_i_r2;
(* ASYNC_REG = "TRUE" *)   reg vs_i_r3;
(* ASYNC_REG = "TRUE" *)   reg vs_i_r4;
//----同步整形电路，之前大意没加整形电路导致总是采集vs出错-----
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
         else if({vs_i_r4,vs_i_r3} == 2'b01)begin
            fs_cap_o <= 1'b1;
         end
         else begin
            fs_cap_o <= 1'b0;
         end
    end
        
endmodule
