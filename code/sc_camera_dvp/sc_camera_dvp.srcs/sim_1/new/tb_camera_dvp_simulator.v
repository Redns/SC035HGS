`timescale 1ns / 1ns
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/10/23 20:21:00
// Design Name: 
// Module Name: tb_camera_dvp_simulator
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


module tb_camera_dvp_simulator;

    `define     HALF_CLK    1
    `define     FULL_CLK    `HALF_CLK * 2

    reg rst_n;
    reg pclk;

    wire fsync;
    wire lref;
    wire [7:0] pixel;

    camera_dvp_simulator#(
        .FRAME_WIDTH(64),
        .FRAME_HEIGHT(48),
        .FRAME_VBLANK(2),
        .FRAME_HBLANK(6)
    ) camera_dvp_simulator(
        .i_rst_n(rst_n),
        .i_pclk(pclk),
        .o_fsync(fsync),
        .o_lref(lref),
        .o_pixel(pixel)
    );

    initial begin
        pclk = 'b0;
        forever #(`HALF_CLK) pclk = ~pclk;
    end

    initial begin
        rst_n = 'b0;
        #(`FULL_CLK * 10) rst_n = 'b1;
        #(`FULL_CLK * 64 * 48 * 5) $stop;
    end

endmodule
