/*******************************MILIANKE*******************************
*Company : MiLianKe Electronic Technology Co., Ltd.
*WebSite:https://www.milianke.com
*TechWeb:https://www.uisrc.com
*tmall-shop:https://milianke.tmall.com
*jd-shop:https://milianke.jd.com
*taobao-shop1: https://milianke.taobao.com
*Create Date: 2021/10/15
*Module Name:ui_axisbufw
*File Name:ui_axisbufw.v
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
`timescale 1ns / 1ns

module ui_axisbufw#(
parameter  integer                   VIDEO_ENABLE   = 0,  
parameter  integer                   AXI_DATA_WIDTH = 128,
parameter  integer                   W_BUFDEPTH     = 2048,
parameter  integer                   W_DATAWIDTH    = 32,
parameter  integer                   W_XSIZE        = 1024,
parameter  integer                   W_YSIZE        = 1024
)
(

input wire                                  ui_rstn,
//sensor input -W_FIFO--------------
input wire                                  W_wclk_i,
input wire                                  W_FS_i,
input wire                                  W_wren_i,
input wire     [W_DATAWIDTH-1'b1 : 0]       W_data_i,
//----------axis signals write-------          
input wire                                  axis_clk,     
output wire    [AXI_DATA_WIDTH/8-1'b1:0]    axis_keep,                        
output wire    [AXI_DATA_WIDTH-1'b1:0]      axis_wdata,
output wire                                 axis_wvalid,
input  wire                                 axis_wready,
output wire                                 axis_last
);    

genvar var;
generate
  for (var=0; var < (AXI_DATA_WIDTH/8); var=var+1)
  begin: init_keep
      assign axis_keep[var] = 1'b1;
  end
endgenerate 


function integer clog2;
  input integer value;
  begin 
    value = value-1;
    for (clog2=0; value>0; clog2=clog2+1)
      value = value>>1;
    end 
endfunction
  
localparam S_IDLE  =  2'd0;  
localparam S_RST   =  2'd1;  
localparam S_DATA1 =  2'd2;   
localparam S_DATA2 =  2'd3; 

localparam WFIFO_DEPTH = W_BUFDEPTH;
localparam W_WR_DATA_COUNT_WIDTH = clog2(WFIFO_DEPTH)+1;
localparam W_RD_DATA_COUNT_WIDTH = clog2(WFIFO_DEPTH*W_DATAWIDTH/AXI_DATA_WIDTH)+1;//clog2(WFIFO_DEPTH/(AXI_DATA_WIDTH/W_DATAWIDTH))+1;

localparam FDMA_WX_BURST        = (W_XSIZE*W_DATAWIDTH/AXI_DATA_WIDTH);

(*mark_debug = "true"*) (* KEEP = "TRUE" *)wire  W_wren_ri = W_wren_i; 

reg                                                                                W_FIFO_Rst=0; 
(*mark_debug = "true"*) (* KEEP = "TRUE" *)wire                                    W_FS;
(*mark_debug = "true"*) (* KEEP = "TRUE" *)reg [1 :0]                              W_MS=0; 
reg [1 :0]                                                                         W_MS_r = 1'b0;
(*mark_debug = "true"*) (* KEEP = "TRUE" *)reg                                     axis_wvalid_r = 1'b0;
(*mark_debug = "true"*) (* KEEP = "TRUE" *)reg [15:0]                              W_xcnt=0; 
(*mark_debug = "true"*) (* KEEP = "TRUE" *)reg [15:0]                              W_ycnt=0; 

(*mark_debug = "true"*) (* KEEP = "TRUE" *)wire[W_RD_DATA_COUNT_WIDTH-1'b1 :0]     W_rcnt;
(*mark_debug = "true"*) (* KEEP = "TRUE" *)reg                                     W_REQ=0; 
reg [7 :0]                                                                         wrst_cnt =0;

(*mark_debug = "true"*) (* KEEP = "TRUE" *)wire                                    axis_rd_en;
(*mark_debug = "true"*) (* KEEP = "TRUE" *)wire                                    axis_wready_r;


assign axis_wready_r = axis_wready;

fs_cap #
(
.VIDEO_ENABLE(VIDEO_ENABLE)
)
fs_cap_W0
(
 .clk_i(axis_clk),
 .rstn_i(ui_rstn),
 .vs_i(W_FS_i),
 .fs_cap_o(W_FS)
);


assign axis_wvalid = (W_MS == S_DATA2);


assign axis_rd_en = axis_wvalid&axis_wready;

assign axis_last = (W_xcnt == FDMA_WX_BURST - 1'b1 && axis_rd_en == 1'b1) && (W_ycnt == W_YSIZE - 1'b1);

always @(posedge axis_clk) begin
    if(!ui_rstn)begin
        W_MS         <= S_IDLE;
        W_FIFO_Rst   <= 0;
        W_xcnt       <= 0;
        W_ycnt       <= 0;
        wrst_cnt     <= 0;
    end   
    else begin
      case(W_MS)
        S_IDLE:begin
          W_xcnt      <= 0;
          W_ycnt      <= 0;
          wrst_cnt    <= 0;
          if(W_FS) W_MS <= S_RST;
       end
       S_RST:begin
           wrst_cnt <= wrst_cnt + 1'b1;
           if((VIDEO_ENABLE == 1) && (wrst_cnt < 40))
                W_FIFO_Rst <= 1;
           else if((VIDEO_ENABLE == 1) && (wrst_cnt < 100))
                W_FIFO_Rst <= 0;
           else 
                W_MS <= S_DATA1;
       end
       S_DATA1:begin 
          if(axis_wready == 1'b1 && W_REQ )begin
             W_MS    <= S_DATA2;   
          end
       end  
       S_DATA2:begin
            if((axis_wready == 1'b1) && (W_xcnt < FDMA_WX_BURST - 1'b1))
                W_xcnt <= W_xcnt + 1'b1;
            else if((axis_wready == 1'b1) &&( W_xcnt == FDMA_WX_BURST - 1'b1) )begin
                W_xcnt <= 0;
                W_ycnt <= W_ycnt + 1'b1;
                if(W_ycnt == W_YSIZE - 1'b1)
                     W_MS <= S_IDLE;
                else 
                     W_MS <= S_DATA1;
            end
        end
         default: W_MS <= S_IDLE; 
       endcase
    end
end 


wire W_rbusy;
always@(posedge axis_clk)     
     W_REQ  <= (W_rcnt > FDMA_WX_BURST - 2)&&(~W_rbusy); 
     
xpm_fifo_async # (
  .FIFO_MEMORY_TYPE          ("auto"),           //string; "auto", "block", or "distributed";
  .ECC_MODE                  ("no_ecc"),         //string; "no_ecc" or "en_ecc";
  .RELATED_CLOCKS            (0),                //positive integer; 0 or 1
  .FIFO_WRITE_DEPTH          (WFIFO_DEPTH),     //positive integer
  .WRITE_DATA_WIDTH          (W_DATAWIDTH),               //positive integer
  .WR_DATA_COUNT_WIDTH       (W_WR_DATA_COUNT_WIDTH),               //positive integer
  .PROG_FULL_THRESH          (20),               //positive integer
  .FULL_RESET_VALUE          (0),                //positive integer; 0 or 1
  .USE_ADV_FEATURES          ("0707"),           //string; "0000" to "1F1F"; 
  .READ_MODE                 ("fwft"),            //string; "std" or "fwft";
  .FIFO_READ_LATENCY         (0),                //positive integer;
  .READ_DATA_WIDTH           (AXI_DATA_WIDTH),               //positive integer
  .RD_DATA_COUNT_WIDTH       (W_RD_DATA_COUNT_WIDTH),               //positive integer
  .PROG_EMPTY_THRESH         (10),               //positive integer
  .DOUT_RESET_VALUE          ("0"),              //string
  .CDC_SYNC_STAGES           (2),                //positive integer
  .WAKEUP_TIME               (0)                 //positive integer; 0 or 2;
) xpm_fifo_W_inst (
      .rst              ((ui_rstn == 1'b0) || (W_FIFO_Rst == 1'b1)),
      .wr_clk           (W_wclk_i),
      .wr_en            (W_wren_i),
      .din              (W_data_i),
      .full             (),
      .overflow         (),
      .prog_full        (),
      .wr_data_count    (),
      .almost_full      (),
      .wr_ack           (),
      .wr_rst_busy      (),
      .rd_clk           (axis_clk),
      .rd_en            (axis_rd_en),
      .dout             (axis_wdata),
      .empty            (),
      .underflow        (),
      .rd_rst_busy      (W_rbusy),
      .prog_empty       (),
      .rd_data_count    (W_rcnt),
      .almost_empty     (),
      .data_valid       (W_dvalid),
      .sleep            (1'b0),
      .injectsbiterr    (1'b0),
      .injectdbiterr    (1'b0),
      .sbiterr          (),
      .dbiterr          ()

);



endmodule

