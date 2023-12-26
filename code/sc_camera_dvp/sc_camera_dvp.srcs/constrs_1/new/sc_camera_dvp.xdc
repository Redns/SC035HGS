# ETH RESET
set_property PACKAGE_PIN Y20 [get_ports {PHY_RSTN_tri_o[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {PHY_RSTN_tri_o[0]}]

# Camera input 24MHz clk
set_property PACKAGE_PIN AJ14 [get_ports XCLK]
set_property IOSTANDARD LVCMOS18 [get_ports XCLK]

# Source input 200MHz clk
set_property PACKAGE_PIN H9 [get_ports clk_200Mhz_clk_p]
set_property IOSTANDARD LVDS [get_ports clk_200Mhz_clk_p]

# Camera dvp
set_property PACKAGE_PIN AJ15 [get_ports pclk]
set_property PACKAGE_PIN AD16 [get_ports href]
set_property PACKAGE_PIN AD15 [get_ports {vsync[0]}]

set_property PACKAGE_PIN AC13 [get_ports {pixel[7]}]
set_property PACKAGE_PIN AC14 [get_ports {pixel[6]}]
set_property PACKAGE_PIN AB14 [get_ports {pixel[5]}]
set_property PACKAGE_PIN AB15 [get_ports {pixel[4]}]
set_property PACKAGE_PIN AG14 [get_ports {pixel[3]}]
set_property PACKAGE_PIN AF14 [get_ports {pixel[2]}]
set_property PACKAGE_PIN AH14 [get_ports {pixel[1]}]
set_property PACKAGE_PIN AH13 [get_ports {pixel[0]}]

set_property IOSTANDARD LVCMOS18 [get_ports pclk]
set_property IOSTANDARD LVCMOS18 [get_ports href]
set_property IOSTANDARD LVCMOS18 [get_ports {vsync[0]}]
set_property IOSTANDARD LVCMOS18 [get_ports {pixel[7]}]
set_property IOSTANDARD LVCMOS18 [get_ports {pixel[6]}]
set_property IOSTANDARD LVCMOS18 [get_ports {pixel[5]}]
set_property IOSTANDARD LVCMOS18 [get_ports {pixel[4]}]
set_property IOSTANDARD LVCMOS18 [get_ports {pixel[3]}]
set_property IOSTANDARD LVCMOS18 [get_ports {pixel[2]}]
set_property IOSTANDARD LVCMOS18 [get_ports {pixel[1]}]
set_property IOSTANDARD LVCMOS18 [get_ports {pixel[0]}]

set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets pclk]

# Camera IIC
set_property PACKAGE_PIN AE18 [get_ports {I2Cs_SCL_tri_o[0]}]
set_property PACKAGE_PIN AC17 [get_ports {I2Cs_SDA_tri_io[0]}]

set_property IOSTANDARD LVCMOS18 [get_ports {I2Cs_SCL_tri_o[0]}]
set_property IOSTANDARD LVCMOS18 [get_ports {I2Cs_SDA_tri_io[0]}]

set_property PULLUP true [get_ports {I2Cs_SCL_tri_o[0]}]
set_property PULLUP true [get_ports {I2Cs_SDA_tri_io[0]}]

# Camera power down
set_property PACKAGE_PIN AH16 [get_ports {PWDN_tri_o[0]}]
set_property IOSTANDARD LVCMOS18 [get_ports {PWDN_tri_o[0]}]

set_property PACKAGE_PIN AA19 [get_ports {LED_STATE_tri_o[3]}]
set_property PACKAGE_PIN AB19 [get_ports {LED_STATE_tri_o[2]}]
set_property PACKAGE_PIN AB20 [get_ports {LED_STATE_tri_o[1]}]
set_property PACKAGE_PIN AD20 [get_ports {LED_STATE_tri_o[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {LED_STATE_tri_o[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {LED_STATE_tri_o[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {LED_STATE_tri_o[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {LED_STATE_tri_o[0]}]

set_property PACKAGE_PIN AA19 [get_ports {SYS_STATE_tri_o[3]}]
set_property PACKAGE_PIN AB19 [get_ports {SYS_STATE_tri_o[2]}]
set_property PACKAGE_PIN AB20 [get_ports {SYS_STATE_tri_o[1]}]
set_property PACKAGE_PIN AD20 [get_ports {SYS_STATE_tri_o[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {SYS_STATE_tri_o[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {SYS_STATE_tri_o[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {SYS_STATE_tri_o[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {SYS_STATE_tri_o[0]}]
