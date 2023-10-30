module camera_dvp_simulator#(
    parameter FRAME_WIDTH   =   640,
    parameter FRAME_HEIGHT  =   480,
    parameter FRAME_VBLANK  =   80,
    parameter FRAME_HBLANK  =   80 
)
(
    input i_rst_n,
    input i_pclk,
    output reg o_fsync,
    output reg o_lref,
    output reg [7:0] o_pixel
);

    localparam LINE_WIDTH   =   FRAME_WIDTH + FRAME_HBLANK;
    localparam FRAME_LINES  =   FRAME_HEIGHT + FRAME_VBLANK;

    reg [31:0] pixel_cnt;

    always@(posedge i_pclk or negedge i_rst_n) begin
        if(!i_rst_n) begin
            pixel_cnt <= 'b0;
        end
        else if(pixel_cnt / LINE_WIDTH < FRAME_LINES) begin
            pixel_cnt <= pixel_cnt + 1'b1;
        end
        else begin
            pixel_cnt <= 'b0;
        end
    end

    always@(posedge i_pclk or negedge i_rst_n) begin
        if(i_rst_n) begin
            o_fsync <= 'b0;
        end
        else if(pixel_cnt / LINE_WIDTH == FRAME_VBLANK) begin
            o_fsync <= 'b1;
        end
        else begin
            o_fsync <= 'b0;
        end
    end

    always@(negedge i_pclk or negedge i_rst_n) begin
        if(i_rst_n) begin
            o_lref <= 'b0;
        end
        else if(pixel_cnt / LINE_WIDTH != FRAME_VBLANK) begin
            if(pixel_cnt % LINE_WIDTH < FRAME_HBLANK) begin
                o_lref <= 'b1;
            end
            else begin
                o_lref <= 'b0;
            end
        end
        else begin
            o_lref <= 'b0;
        end
    end

    always@(posedge i_pclk or negedge i_rst_n) begin
        if(!i_rst_n) begin
            o_pixel <= 'b0;
        end
        else begin
            o_pixel <= o_pixel + 1'b1;
        end
    end

endmodule