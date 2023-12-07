/*******************************MILIANKE*******************************
*Company : MiLianKe Electronic Technology Co., Ltd.
*WebSite:https://www.milianke.com
*TechWeb:https://www.uisrc.com
*tmall-shop:https://milianke.tmall.com
*jd-shop:https://milianke.jd.com
*taobao-shop1: https://milianke.taobao.com
*Create Date: 2019/12/17
*Module Name:fdma_ddr_test
*File Name:fdma_ddr_test.v
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
module fdma_ddr_test(
  output [14:0]DDR3_addr,
  output [2:0]DDR3_ba,
  output DDR3_cas_n,
  output [0:0]DDR3_ck_n,
  output [0:0]DDR3_ck_p,
  output [0:0]DDR3_cke,
  output [0:0]DDR3_cs_n,
  output [3:0]DDR3_dm,
  inout [31:0]DDR3_dq,
  inout [3:0]DDR3_dqs_n,
  inout [3:0]DDR3_dqs_p,
  output [0:0]DDR3_odt,
  output DDR3_ras_n,
  output DDR3_reset_n,
  output DDR3_we_n,
  output init_calib_complete,
  input  sysclk
);
    wire [31:0]   fdma_raddr;
    reg           fdma_rareq;
    wire          fdma_rbusy;
    wire [127:0]  fdma_rdata;
    wire [15:0]   fdma_rsize;
    wire          fdma_rvalid;
    wire [31:0]   fdma_waddr;
    reg           fdma_wareq;
    wire          fdma_wbusy;
    wire [127:0]   fdma_wdata;
    wire [15:0]   fdma_wsize;
    wire          fdma_wvalid;
    wire [0:0]    fdma_rstn;
    wire          ui_clk;


    parameter TEST_MEM_SIZE   = 32'd512*1024*1024; //1GB
    parameter FDMA_BURST_LEN  = 16'd512;
    parameter ADDR_MEM_OFFSET = 0;
    parameter ADDR_INC = FDMA_BURST_LEN * 16;

    parameter WRITE1 = 0;
    parameter WRITE2 = 1;
    parameter WAIT   = 2;
    parameter READ1  = 3;
    parameter READ2  = 4;

    reg [31: 0] t_data;
    reg [31: 0] fdma_waddr_r;
    reg [2  :0] T_S = 0;

    assign fdma_waddr = fdma_waddr_r + ADDR_MEM_OFFSET;
    assign fdma_raddr = fdma_waddr;

    assign fdma_wsize = FDMA_BURST_LEN;
    assign fdma_rsize = FDMA_BURST_LEN;
    assign fdma_wdata ={t_data,t_data,t_data,t_data};

    reg [8:0] rst_cnt = 0;

    always @(posedge ui_clk)
    if((fdma_rstn & init_calib_complete)==1'b0)begin
        rst_cnt <=0;
    end
    else begin
        if(rst_cnt[8] == 1'b0)
            rst_cnt <= rst_cnt + 1'b1;
        else
            rst_cnt <= rst_cnt;
    end

    always @(posedge ui_clk)begin
        if(rst_cnt[8] == 1'b0)begin
            T_S <=0;
            fdma_wareq  <= 1'b0;
            fdma_rareq  <= 1'b0;
            t_data<=0;
            fdma_waddr_r <=0;
        end
        else begin
            case(T_S)
                WRITE1:begin
                    if(fdma_waddr_r>TEST_MEM_SIZE) fdma_waddr_r<=0;
                    if(!fdma_wbusy)begin
                        fdma_wareq  <= 1'b1;
                        t_data  <= 0;
                    end
                    if(fdma_wareq&&fdma_wbusy)begin
                        fdma_wareq  <= 1'b0;
                        T_S         <= WRITE2;
                    end
                end
                WRITE2:begin
                    if(!fdma_wbusy) begin
                        T_S <= WAIT;
                        t_data  <= 32'd0;
                    end
                    else if(fdma_wvalid) begin
                        t_data <= t_data + 1'b1;
                    end
                end
                WAIT:begin //not needed
                    T_S <= READ1;
                end
                READ1:begin
                    if(!fdma_rbusy)begin
                        fdma_rareq  <= 1'b1;
                        t_data   <= 0;
                    end
                    if(fdma_rareq&&fdma_rbusy)begin
                        fdma_rareq  <= 1'b0;
                        T_S         <= READ2;
                    end
                end
                READ2:begin
                    if(!fdma_rbusy) begin
                        T_S <= WRITE1;
                        t_data  <= 32'd0;
                        fdma_waddr_r  <= fdma_waddr_r + ADDR_INC; //128/8=16
                    end
                    else if(fdma_rvalid) begin
                        t_data <= t_data + 1'b1;
                    end
                end
                default:
                T_S <= WRITE1;
            endcase
        end
    end

    wire test_error = (fdma_rvalid && (t_data[15:0] != fdma_rdata[15:0]));

    ila_0 ila_dbg (
        .clk(ui_clk),
        .probe0({fdma_wdata[15:0],fdma_wareq,fdma_wvalid,fdma_wbusy}),
        .probe1({fdma_rdata[15:0],t_data[15:0],fdma_rvalid,fdma_rbusy,T_S,test_error})
    );

    system system_i
    (.DDR3_addr(DDR3_addr),
        .DDR3_ba(DDR3_ba),
        .DDR3_cas_n(DDR3_cas_n),
        .DDR3_ck_n(DDR3_ck_n),
        .DDR3_ck_p(DDR3_ck_p),
        .DDR3_cke(DDR3_cke),
        .DDR3_cs_n(DDR3_cs_n),
        .DDR3_dm(DDR3_dm),
        .DDR3_dq(DDR3_dq),
        .DDR3_dqs_n(DDR3_dqs_n),
        .DDR3_dqs_p(DDR3_dqs_p),
        .DDR3_odt(DDR3_odt),
        .DDR3_ras_n(DDR3_ras_n),
        .DDR3_reset_n(DDR3_reset_n),
        .DDR3_we_n(DDR3_we_n),

        .FDMA_S_0_fdma_raddr(fdma_raddr),
        .FDMA_S_0_fdma_rareq(fdma_rareq),
        .FDMA_S_0_fdma_rbusy(fdma_rbusy),
        .FDMA_S_0_fdma_rdata(fdma_rdata),
        .FDMA_S_0_fdma_rready(1'b1),
        .FDMA_S_0_fdma_rsize(fdma_rsize),
        .FDMA_S_0_fdma_rvalid(fdma_rvalid),
        .FDMA_S_0_fdma_waddr(fdma_waddr),
        .FDMA_S_0_fdma_wareq(fdma_wareq),
        .FDMA_S_0_fdma_wbusy(fdma_wbusy),
        .FDMA_S_0_fdma_wdata(fdma_wdata),
        .FDMA_S_0_fdma_wready(1'b1),
        .FDMA_S_0_fdma_wsize(fdma_wsize),
        .FDMA_S_0_fdma_wvalid(fdma_wvalid),
        .init_calib_complete(init_calib_complete),
        .fdma_rstn(fdma_rstn),
        .sysclk(sysclk),
        .ui_clk(ui_clk));
endmodule