`timescale 1ns / 1ps

module frame_check
#(
    parameter FRAME_WIDTH       =   640,
    parameter FRAME_HEIGHT      =   480,
    parameter FRAME_IGNORE_NUMS =   10
)
(
    input clk,
    input rst_n,
    input vsync,
    input href,
    output reg error
);

    // reg [1:0]  frame_cnt_state;

    reg [15:0] frame_ignore_cnt;
    reg [15:0] frame_horizon_line_cnt;
    reg [15:0] frame_horizon_pixel_cnt;

    assign frame_valid_check_enable = frame_ignore_cnt > FRAME_IGNORE_NUMS ? 1'b1 : 1'b0;

    // localparam FRAME_CHECK_READY  =   2'b0,
    //            FRAME_CHECK_START  =   2'b1,
    //            FRAME_CHECK_FINISH =   2'b2;

    /*
     * 摄像头输出前几帧不稳定，直接丢弃
    */
    always@(posedge clk) begin
        if(!rst_n) begin
            frame_ignore_cnt <= 'b0;
        end
        else if(vsync && !frame_valid_check_enable) begin
            frame_ignore_cnt <= frame_ignore_cnt + 1'b1;
        end
        else begin
            frame_ignore_cnt <= frame_ignore_cnt;
        end
    end


    always@(posedge clk) begin
        if(!rst_n) begin
            error <= 1'b0;
            frame_horizon_line_cnt <= 'b0;
            frame_vertical_line_cnt <= 'b0;
        end
        else if(frame_valid_check_enable) begin
            if(href) begin
                frame_vertical_line_cnt <= frame_vertical_line_cnt + 1'b1;
            end
            else if(vsync) begin
                if(frame_horizon_line_cnt != FRAME_HEIGHT) begin
                    error <= 1'b1;
                end
                else begin
                    frame_horizon_line_cnt <= 'b0;
                end
            end
            else begin
                if(frame_horizon_pixel_cnt != FRAME_WIDTH) begin
                    error <= 1'b1;
                end
                else begin
                    frame_horizon_pixel_cnt <= 'b0;
                end

                if(error) begin
                    error <= 1'b0;
                end
                frame_horizon_line_cnt <= frame_horizon_line_cnt + 1'b1;
            end
        end
    end

endmodule
