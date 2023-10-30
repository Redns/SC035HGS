# Camera input 24MHz clk
set_property PACKAGE_PIN AB14 [get_ports o_clk_24M]
set_property IOSTANDARD LVCMOS18 [get_ports o_clk_24M]

# Source input 200MHz clk
set_property PACKAGE_PIN H9 [get_ports i_clk_200M_clk_p]
set_property IOSTANDARD LVDS [get_ports i_clk_200M_clk_p]

# Dvp signals
set_property PACKAGE_PIN AB15 [get_ports i_pclk]
set_property PACKAGE_PIN AC14 [get_ports i_href]
set_property PACKAGE_PIN AC13 [get_ports {i_camera_vsync_tri_i[0]}]
set_property PACKAGE_PIN AJ13 [get_ports {i_pixel[7]}]
set_property PACKAGE_PIN AJ14 [get_ports {i_pixel[6]}]
set_property PACKAGE_PIN AK15 [get_ports {i_pixel[5]}]
set_property PACKAGE_PIN AJ15 [get_ports {i_pixel[4]}]
set_property PACKAGE_PIN AH13 [get_ports {i_pixel[3]}]
set_property PACKAGE_PIN AH14 [get_ports {i_pixel[2]}]
set_property PACKAGE_PIN AF14 [get_ports {i_pixel[1]}]
set_property PACKAGE_PIN AG14 [get_ports {i_pixel[0]}]

set_property IOSTANDARD LVCMOS18 [get_ports i_pclk]
set_property IOSTANDARD LVCMOS18 [get_ports i_href]
set_property IOSTANDARD LVCMOS18 [get_ports {i_camera_vsync_tri_i[0]}]
set_property IOSTANDARD LVCMOS18 [get_ports {i_pixel[7]}]
set_property IOSTANDARD LVCMOS18 [get_ports {i_pixel[6]}]
set_property IOSTANDARD LVCMOS18 [get_ports {i_pixel[5]}]
set_property IOSTANDARD LVCMOS18 [get_ports {i_pixel[4]}]
set_property IOSTANDARD LVCMOS18 [get_ports {i_pixel[3]}]
set_property IOSTANDARD LVCMOS18 [get_ports {i_pixel[2]}]
set_property IOSTANDARD LVCMOS18 [get_ports {i_pixel[1]}]
set_property IOSTANDARD LVCMOS18 [get_ports {i_pixel[0]}]

# Camera pclk
set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets i_pclk]

# IIC
set_property PACKAGE_PIN AH17 [get_ports o_camera_iic_scl_io]
set_property PACKAGE_PIN AH16 [get_ports o_camera_iic_sda_io]

set_property IOSTANDARD LVCMOS18 [get_ports o_camera_iic_scl_io]
set_property IOSTANDARD LVCMOS18 [get_ports o_camera_iic_sda_io]

set_property PULLUP true [get_ports o_camera_iic_scl_io]
set_property PULLUP true [get_ports o_camera_iic_sda_io]

# Camera sh035hgs power down
set_property PACKAGE_PIN AD16 [get_ports {o_camera_pwdn_tri_o[0]}]
set_property IOSTANDARD LVCMOS18 [get_ports {o_camera_pwdn_tri_o[0]}]

# Camera sc035hgs reset
set_property PACKAGE_PIN AD15 [get_ports {o_camera_reset_tri_o[0]}]
set_property IOSTANDARD LVCMOS18 [get_ports {o_camera_reset_tri_o[0]}]

# Reset eth phy
set_property IOSTANDARD LVCMOS33 [get_ports {o_phy_rstn_tri_o[0]}]
set_property PACKAGE_PIN Y20 [get_ports {o_phy_rstn_tri_o[0]}]

# Camera xclk locked
set_property PACKAGE_PIN AD14 [get_ports o_camera_xclk_locked]
set_property IOSTANDARD LVCMOS18 [get_ports o_camera_xclk_locked]
