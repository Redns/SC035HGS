# Camera input 24MHz clk
set_property IOSTANDARD LVCMOS18 [get_ports o_clk_24M]

# Source input 200MHz clk
set_property IOSTANDARD LVDS [get_ports i_clk_200M_clk_p]

# Dvp signals
set_property PACKAGE_PIN AD15 [get_ports {i_camera_vsync[0]}]

set_property IOSTANDARD LVCMOS18 [get_ports i_pclk]
set_property IOSTANDARD LVCMOS18 [get_ports i_href]
set_property IOSTANDARD LVCMOS18 [get_ports {i_camera_vsync[0]}]
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

# Camera IIC

set_property IOSTANDARD LVCMOS18 [get_ports o_camera_iic_scl_io]
set_property IOSTANDARD LVCMOS18 [get_ports o_camera_iic_sda_io]

# PS IIC
set_property PACKAGE_PIN AC17 [get_ports o_ps_iic_sda_io]

set_property IOSTANDARD LVCMOS18 [get_ports o_ps_iic_scl_io]
set_property IOSTANDARD LVCMOS18 [get_ports o_ps_iic_sda_io]

# Camera sh035hgs power down
set_property IOSTANDARD LVCMOS18 [get_ports {o_camera_pwdn[0]}]

# Camera sc035hgs reset
set_property IOSTANDARD LVCMOS18 [get_ports {o_camera_reset[0]}]

# Reset eth phy
set_property IOSTANDARD LVCMOS33 [get_ports {o_phy_rstn[0]}]

# Camera xclk locked
set_property PACKAGE_PIN AB19 [get_ports {o_camera_xclk_locked[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {o_camera_xclk_locked[0]}]

set_property IOSTANDARD LVCMOS33 [get_ports {o_led[0]}]

set_property PULLUP true [get_ports o_camera_iic_sda_io]
set_property PULLUP true [get_ports o_camera_iic_scl_io]
set_property PACKAGE_PIN AJ14 [get_ports o_clk_24M]
set_property PACKAGE_PIN AA19 [get_ports {o_led[0]}]
set_property PACKAGE_PIN AH16 [get_ports {o_camera_pwdn[0]}]
set_property PACKAGE_PIN AE16 [get_ports {o_camera_reset[0]}]
set_property PACKAGE_PIN Y20 [get_ports {o_phy_rstn[0]}]
set_property PACKAGE_PIN AF15 [get_ports o_camera_iic_scl_io]
set_property PACKAGE_PIN AG15 [get_ports o_camera_iic_sda_io]
set_property PACKAGE_PIN AE18 [get_ports o_ps_iic_scl_io]
set_property PULLUP true [get_ports o_ps_iic_sda_io]
set_property PULLUP true [get_ports o_ps_iic_scl_io]
set_property PACKAGE_PIN AH13 [get_ports {i_pixel[0]}]
set_property PACKAGE_PIN AC13 [get_ports {i_pixel[7]}]
set_property PACKAGE_PIN AC14 [get_ports {i_pixel[6]}]
set_property PACKAGE_PIN AB14 [get_ports {i_pixel[5]}]
set_property PACKAGE_PIN AB15 [get_ports {i_pixel[4]}]
set_property PACKAGE_PIN AG14 [get_ports {i_pixel[3]}]
set_property PACKAGE_PIN AF14 [get_ports {i_pixel[2]}]
set_property PACKAGE_PIN AH14 [get_ports {i_pixel[1]}]
set_property PACKAGE_PIN AD16 [get_ports i_href]
set_property PACKAGE_PIN AJ15 [get_ports i_pclk]

set_property PACKAGE_PIN H9 [get_ports i_clk_200M_clk_p]
set_property SLEW SLOW [get_ports o_camera_iic_scl_io]
