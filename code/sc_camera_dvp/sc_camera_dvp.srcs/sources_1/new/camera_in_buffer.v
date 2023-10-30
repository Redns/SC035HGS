`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/10/22 14:37:02
// Design Name: 
// Module Name: camera_in_buffer
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module camera_in_buffer#(
    parameter IGNORE_FRAME_CNT  =   10,
    parameter REF_CLK_FREQ      =   24_000_000
)
(
    input i_rst_n,
    input i_ref_clk,
    input i_pclk,
    input [7:0] i_pixel,
    input i_href,
    input i_vsync,
    output [7:0] o_pixel,
    output reg o_pixel_de,
    output reg [15:0] o_frame_width,
    output reg [15:0] o_frame_height,
    output reg [7:0] o_fps
);

    reg [7:0] frame_cnt;

    reg [1:0] href;
    reg [1:0] vsync;

    reg [7:0] fps_cnt;
    reg [31:0] ref_clk_cnt;
    reg [15:0] frame_width_cnt;
    reg [15:0] frame_height_cnt;

    wire [7:0] o_pixel = i_pixel;

    // 输入行场信号打拍
    always@(posedge i_pclk or negedge i_rst_n) begin
        if(!i_rst_n) begin
            href <= 'b0;
            vsync <= 'b0;
        end
        else begin
            href <= {href[0], i_href};
            vsync <= {vsync[0], i_vsync};
        end
    end

    // 帧高度计数器
    always@(posedge i_pclk or negedge i_rst_n) begin
        if(!i_rst_n) begin
            frame_height_cnt <= 'b0;
        end
        else if(!vsync[0] && i_vsync) begin
            frame_height_cnt <= 'b0;
        end
        else if(!href[0] && i_href) begin
            frame_height_cnt <= frame_height_cnt + 1'b1;
        end
        else begin
            frame_height_cnt <= frame_height_cnt;
        end
    end

    always@(posedge i_pclk or negedge i_rst_n) begin
        if(!i_rst_n) begin
            o_frame_height <= 'b0;
        end        
        else if(!vsync[0] && i_vsync) begin
            o_frame_height <= frame_height_cnt;
        end
        else begin
            o_frame_height <= o_frame_height;
        end
    end

    // 帧宽度计数器
    always@(posedge i_pclk or negedge i_rst_n) begin
        if(!i_rst_n) begin
            frame_width_cnt <= 'b0;
        end
        else if(i_href) begin
            frame_width_cnt <= frame_width_cnt + 1'b1;
        end
        else if(href[0] && !i_href) begin
            frame_width_cnt <= 'b0;
        end
        else begin
            frame_width_cnt <= frame_width_cnt;
        end
    end

    always@(posedge i_pclk or negedge i_rst_n) begin
        if(!i_rst_n) begin
            o_frame_width <= 'b0;
        end        
        else if(href[0] && !i_href) begin
            o_frame_width <= frame_width_cnt;
        end
        else begin
            o_frame_width <= o_frame_width;
        end
    end

    // 摄像头配置完成后，输出前几帧不稳定
    // 丢弃帧数由参数 IGNORE_FRAME_CNT 指定，默认 10 帧
    always@(posedge i_pclk or negedge i_rst_n) begin
        if(!i_rst_n) begin
            frame_cnt <= 'b0;
        end
        else if(!vsync[0] && i_vsync && (frame_cnt < IGNORE_FRAME_CNT)) begin
            frame_cnt <= frame_cnt + 1'b1;
        end
        else begin
            frame_cnt <= frame_cnt;
        end
    end

    always@(posedge i_pclk or negedge i_rst_n) begin
        if(!i_rst_n) begin
            o_pixel_de <= 1'b0;
        end
        else if(frame_cnt > IGNORE_FRAME_CNT) begin
            o_pixel_de <= i_href;
        end
        else begin
            o_pixel_de <= o_pixel_de;
        end
    end

    // 帧率计数器
    always@(posedge i_ref_clk or negedge i_rst_n) begin
        if(!i_rst_n) begin
            ref_clk_cnt <= 'b0;
        end
        else if(ref_clk_cnt < REF_CLK_FREQ) begin
            ref_clk_cnt <= ref_clk_cnt + 1'b1;
        end
        else begin
            ref_clk_cnt <= 'b0;
        end
    end

    always@(posedge i_ref_clk or negedge i_rst_n) begin
        if(!i_rst_n) begin
            o_fps <= 'b0;
        end
        else if(ref_clk_cnt == REF_CLK_FREQ) begin
            o_fps <= fps_cnt;
        end
    end

    always@(posedge i_pclk or negedge i_rst_n) begin
        if(!i_rst_n) begin
            fps_cnt <= 'b0;
        end
        else if(!vsync[0] && i_vsync) begin
            if(ref_clk_cnt < REF_CLK_FREQ) begin
                fps_cnt <= fps_cnt + 1'b1;
            end
            else begin
                fps_cnt <= 'b1;
            end
            fps_cnt <= 'b0;
        end
    end

endmodule
