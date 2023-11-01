vlib modelsim_lib/work
vlib modelsim_lib/msim

vlib modelsim_lib/msim/xil_defaultlib

vmap xil_defaultlib modelsim_lib/msim/xil_defaultlib

vcom -work xil_defaultlib  -93 \
"../../../bd/system/ip/system_axi_iic_0_0/sim/system_axi_iic_0_0.vhd" \

vlog -work xil_defaultlib  -incr -mfcu "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/62b6" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/1b7e/hdl/verilog" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/122e/hdl/verilog" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/b205/hdl/verilog" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/fd26/hdl/verilog" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../bd/system/ip/system_processing_system7_0_0/sim/system_processing_system7_0_0.v" \
"../../../bd/system/ip/system_xbar_0/sim/system_xbar_0.v" \

vcom -work xil_defaultlib  -93 \
"../../../bd/system/ip/system_rst_ps7_0_50M_0/sim/system_rst_ps7_0_50M_0.vhd" \

vlog -work xil_defaultlib  -incr -mfcu "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/62b6" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/1b7e/hdl/verilog" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/122e/hdl/verilog" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/b205/hdl/verilog" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/fd26/hdl/verilog" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../bd/system/ipshared/7bbf/fs_cap.v" \
"../../../bd/system/ipshared/7bbf/ui_axisbufw.v" \
"../../../bd/system/ip/system_ui_axisbufw_0_0/sim/system_ui_axisbufw_0_0.v" \

vcom -work xil_defaultlib  -93 \
"../../../bd/system/ip/system_axi_dma_0_0/sim/system_axi_dma_0_0.vhd" \
"../../../bd/system/ip/system_axi_gpio_0_0/sim/system_axi_gpio_0_0.vhd" \
"../../../bd/system/ip/system_axi_gpio_0_1/sim/system_axi_gpio_0_1.vhd" \

vlog -work xil_defaultlib  -incr -mfcu "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/62b6" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/1b7e/hdl/verilog" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/122e/hdl/verilog" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/b205/hdl/verilog" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/fd26/hdl/verilog" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../bd/system/ip/system_clk_wiz_0_0/system_clk_wiz_0_0_clk_wiz.v" \
"../../../bd/system/ip/system_clk_wiz_0_0/system_clk_wiz_0_0.v" \

vcom -work xil_defaultlib  -93 \
"../../../bd/system/ip/system_axi_gpio_0_5/sim/system_axi_gpio_0_5.vhd" \
"../../../bd/system/ip/system_axi_gpio_1_0/sim/system_axi_gpio_1_0.vhd" \
"../../../bd/system/ip/system_axi_gpio_0_6/sim/system_axi_gpio_0_6.vhd" \

vlog -work xil_defaultlib  -incr -mfcu "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/62b6" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/1b7e/hdl/verilog" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/122e/hdl/verilog" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/b205/hdl/verilog" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/fd26/hdl/verilog" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../bd/system/ip/system_system_ila_0_4/bd_0/ip/ip_0/sim/bd_16b9_ila_lib_0.v" \
"../../../bd/system/ip/system_system_ila_0_4/bd_0/sim/bd_16b9.v" \
"../../../bd/system/ip/system_system_ila_0_4/sim/system_system_ila_0_4.v" \
"../../../bd/system/sim/system.v" \
"../../../bd/system/ip/system_auto_pc_0/sim/system_auto_pc_0.v" \
"../../../bd/system/ip/system_auto_pc_1/sim/system_auto_pc_1.v" \
"../../../bd/system/ip/system_auto_us_0/sim/system_auto_us_0.v" \

vlog -work xil_defaultlib \
"glbl.v"

