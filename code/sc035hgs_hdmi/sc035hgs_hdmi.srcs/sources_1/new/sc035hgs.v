`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2024/02/22 20:38:01
// Design Name: 
// Module Name: sc035hgs
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


module sc035hgs
(
    input pclk,
    input fsync,
    input href,
    input [7:0] pixel,
    output vid_clk,
    output vid_vsync,
    output vid_hsync,
    output [23:0] vid_data
);

    assign vid_clk = pclk;
    assign vid_vsync = ~(fsync & (~href));
    assign vid_hsync = href;
    assign vid_data = { pixel, pixel, pixel };

endmodule
