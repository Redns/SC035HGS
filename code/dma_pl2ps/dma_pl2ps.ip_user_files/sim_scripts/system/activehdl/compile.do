vlib work
vlib activehdl

vlib activehdl/xilinx_vip
vlib activehdl/xpm
vlib activehdl/axi_infrastructure_v1_1_0
vlib activehdl/axi_vip_v1_1_11
vlib activehdl/processing_system7_vip_v1_0_13
vlib activehdl/xil_defaultlib
vlib activehdl/lib_pkg_v1_0_2
vlib activehdl/fifo_generator_v13_2_6
vlib activehdl/lib_fifo_v1_0_15
vlib activehdl/lib_srl_fifo_v1_0_2
vlib activehdl/lib_cdc_v1_0_2
vlib activehdl/axi_datamover_v5_1_27
vlib activehdl/axi_sg_v4_1_14
vlib activehdl/axi_dma_v7_1_26
vlib activehdl/axi_lite_ipif_v3_0_4
vlib activehdl/interrupt_control_v3_1_4
vlib activehdl/axi_gpio_v2_0_27
vlib activehdl/generic_baseblocks_v2_1_0
vlib activehdl/axi_register_slice_v2_1_25
vlib activehdl/axi_data_fifo_v2_1_24
vlib activehdl/axi_crossbar_v2_1_26
vlib activehdl/proc_sys_reset_v5_0_13
vlib activehdl/gigantic_mux
vlib activehdl/axi_protocol_converter_v2_1_25
vlib activehdl/axi_clock_converter_v2_1_24
vlib activehdl/blk_mem_gen_v8_4_5
vlib activehdl/axi_dwidth_converter_v2_1_25

vmap xilinx_vip activehdl/xilinx_vip
vmap xpm activehdl/xpm
vmap axi_infrastructure_v1_1_0 activehdl/axi_infrastructure_v1_1_0
vmap axi_vip_v1_1_11 activehdl/axi_vip_v1_1_11
vmap processing_system7_vip_v1_0_13 activehdl/processing_system7_vip_v1_0_13
vmap xil_defaultlib activehdl/xil_defaultlib
vmap lib_pkg_v1_0_2 activehdl/lib_pkg_v1_0_2
vmap fifo_generator_v13_2_6 activehdl/fifo_generator_v13_2_6
vmap lib_fifo_v1_0_15 activehdl/lib_fifo_v1_0_15
vmap lib_srl_fifo_v1_0_2 activehdl/lib_srl_fifo_v1_0_2
vmap lib_cdc_v1_0_2 activehdl/lib_cdc_v1_0_2
vmap axi_datamover_v5_1_27 activehdl/axi_datamover_v5_1_27
vmap axi_sg_v4_1_14 activehdl/axi_sg_v4_1_14
vmap axi_dma_v7_1_26 activehdl/axi_dma_v7_1_26
vmap axi_lite_ipif_v3_0_4 activehdl/axi_lite_ipif_v3_0_4
vmap interrupt_control_v3_1_4 activehdl/interrupt_control_v3_1_4
vmap axi_gpio_v2_0_27 activehdl/axi_gpio_v2_0_27
vmap generic_baseblocks_v2_1_0 activehdl/generic_baseblocks_v2_1_0
vmap axi_register_slice_v2_1_25 activehdl/axi_register_slice_v2_1_25
vmap axi_data_fifo_v2_1_24 activehdl/axi_data_fifo_v2_1_24
vmap axi_crossbar_v2_1_26 activehdl/axi_crossbar_v2_1_26
vmap proc_sys_reset_v5_0_13 activehdl/proc_sys_reset_v5_0_13
vmap gigantic_mux activehdl/gigantic_mux
vmap axi_protocol_converter_v2_1_25 activehdl/axi_protocol_converter_v2_1_25
vmap axi_clock_converter_v2_1_24 activehdl/axi_clock_converter_v2_1_24
vmap blk_mem_gen_v8_4_5 activehdl/blk_mem_gen_v8_4_5
vmap axi_dwidth_converter_v2_1_25 activehdl/axi_dwidth_converter_v2_1_25

vlog -work xilinx_vip  -sv2k12 "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"D:/Xilinx/Vivado/2021.2/data/xilinx_vip/hdl/axi4stream_vip_axi4streampc.sv" \
"D:/Xilinx/Vivado/2021.2/data/xilinx_vip/hdl/axi_vip_axi4pc.sv" \
"D:/Xilinx/Vivado/2021.2/data/xilinx_vip/hdl/xil_common_vip_pkg.sv" \
"D:/Xilinx/Vivado/2021.2/data/xilinx_vip/hdl/axi4stream_vip_pkg.sv" \
"D:/Xilinx/Vivado/2021.2/data/xilinx_vip/hdl/axi_vip_pkg.sv" \
"D:/Xilinx/Vivado/2021.2/data/xilinx_vip/hdl/axi4stream_vip_if.sv" \
"D:/Xilinx/Vivado/2021.2/data/xilinx_vip/hdl/axi_vip_if.sv" \
"D:/Xilinx/Vivado/2021.2/data/xilinx_vip/hdl/clk_vip_if.sv" \
"D:/Xilinx/Vivado/2021.2/data/xilinx_vip/hdl/rst_vip_if.sv" \

vlog -work xpm  -sv2k12 "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/1b7e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/122e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/b205/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/fd26/hdl/verilog" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"D:/Xilinx/Vivado/2021.2/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
"D:/Xilinx/Vivado/2021.2/data/ip/xpm/xpm_fifo/hdl/xpm_fifo.sv" \
"D:/Xilinx/Vivado/2021.2/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \

vcom -work xpm -93 \
"D:/Xilinx/Vivado/2021.2/data/ip/xpm/xpm_VCOMP.vhd" \

vlog -work axi_infrastructure_v1_1_0  -v2k5 "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/1b7e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/122e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/b205/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/fd26/hdl/verilog" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/ec67/hdl/axi_infrastructure_v1_1_vl_rfs.v" \

vlog -work axi_vip_v1_1_11  -sv2k12 "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/1b7e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/122e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/b205/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/fd26/hdl/verilog" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/63b7/hdl/axi_vip_v1_1_vl_rfs.sv" \

vlog -work processing_system7_vip_v1_0_13  -sv2k12 "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/1b7e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/122e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/b205/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/fd26/hdl/verilog" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/3007/hdl/processing_system7_vip_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/1b7e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/122e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/b205/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/fd26/hdl/verilog" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../bd/system/ip/system_processing_system7_0_0/sim/system_processing_system7_0_0.v" \

vcom -work lib_pkg_v1_0_2 -93 \
"../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/0513/hdl/lib_pkg_v1_0_rfs.vhd" \

vlog -work fifo_generator_v13_2_6  -v2k5 "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/1b7e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/122e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/b205/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/fd26/hdl/verilog" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/8ae1/simulation/fifo_generator_vlog_beh.v" \

vcom -work fifo_generator_v13_2_6 -93 \
"../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/8ae1/hdl/fifo_generator_v13_2_rfs.vhd" \

vlog -work fifo_generator_v13_2_6  -v2k5 "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/1b7e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/122e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/b205/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/fd26/hdl/verilog" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/8ae1/hdl/fifo_generator_v13_2_rfs.v" \

vcom -work lib_fifo_v1_0_15 -93 \
"../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/a4ed/hdl/lib_fifo_v1_0_rfs.vhd" \

vcom -work lib_srl_fifo_v1_0_2 -93 \
"../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/51ce/hdl/lib_srl_fifo_v1_0_rfs.vhd" \

vcom -work lib_cdc_v1_0_2 -93 \
"../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/ef1e/hdl/lib_cdc_v1_0_rfs.vhd" \

vcom -work axi_datamover_v5_1_27 -93 \
"../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/9b19/hdl/axi_datamover_v5_1_vh_rfs.vhd" \

vcom -work axi_sg_v4_1_14 -93 \
"../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/bcf6/hdl/axi_sg_v4_1_rfs.vhd" \

vcom -work axi_dma_v7_1_26 -93 \
"../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/69a4/hdl/axi_dma_v7_1_vh_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/system/ip/system_axi_dma_0_0/sim/system_axi_dma_0_0.vhd" \

vcom -work axi_lite_ipif_v3_0_4 -93 \
"../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/66ea/hdl/axi_lite_ipif_v3_0_vh_rfs.vhd" \

vcom -work interrupt_control_v3_1_4 -93 \
"../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/a040/hdl/interrupt_control_v3_1_vh_rfs.vhd" \

vcom -work axi_gpio_v2_0_27 -93 \
"../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/a5bb/hdl/axi_gpio_v2_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/system/ip/system_axi_gpio_0_0/sim/system_axi_gpio_0_0.vhd" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/1b7e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/122e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/b205/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/fd26/hdl/verilog" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../bd/system/ipshared/7bbf/fs_cap.v" \
"../../../bd/system/ipshared/7bbf/ui_axisbufw.v" \
"../../../bd/system/ip/system_ui_axisbufw_0_0/sim/system_ui_axisbufw_0_0.v" \

vlog -work generic_baseblocks_v2_1_0  -v2k5 "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/1b7e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/122e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/b205/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/fd26/hdl/verilog" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/b752/hdl/generic_baseblocks_v2_1_vl_rfs.v" \

vlog -work axi_register_slice_v2_1_25  -v2k5 "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/1b7e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/122e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/b205/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/fd26/hdl/verilog" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/e1e6/hdl/axi_register_slice_v2_1_vl_rfs.v" \

vlog -work axi_data_fifo_v2_1_24  -v2k5 "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/1b7e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/122e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/b205/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/fd26/hdl/verilog" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/fa53/hdl/axi_data_fifo_v2_1_vl_rfs.v" \

vlog -work axi_crossbar_v2_1_26  -v2k5 "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/1b7e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/122e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/b205/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/fd26/hdl/verilog" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/ac57/hdl/axi_crossbar_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/1b7e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/122e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/b205/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/fd26/hdl/verilog" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../bd/system/ip/system_xbar_0/sim/system_xbar_0.v" \

vcom -work proc_sys_reset_v5_0_13 -93 \
"../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/8842/hdl/proc_sys_reset_v5_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/system/ip/system_rst_ps7_0_100M_0/sim/system_rst_ps7_0_100M_0.vhd" \
"../../../bd/system/ip/system_axi_gpio_0_1/sim/system_axi_gpio_0_1.vhd" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/1b7e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/122e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/b205/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/fd26/hdl/verilog" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../bd/system/ip/system_system_ila_0_0/bd_0/ip/ip_0/sim/bd_d5b8_ila_lib_0.v" \

vlog -work gigantic_mux  -v2k5 "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/1b7e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/122e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/b205/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/fd26/hdl/verilog" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/e87a/hdl/gigantic_mux_v1_0_cntr.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/1b7e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/122e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/b205/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/fd26/hdl/verilog" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../bd/system/ip/system_system_ila_0_0/bd_0/ip/ip_1/bd_d5b8_g_inst_0_gigantic_mux.v" \
"../../../bd/system/ip/system_system_ila_0_0/bd_0/ip/ip_1/sim/bd_d5b8_g_inst_0.v" \
"../../../bd/system/ip/system_system_ila_0_0/bd_0/sim/bd_d5b8.v" \
"../../../bd/system/ip/system_system_ila_0_0/sim/system_system_ila_0_0.v" \

vlog -work axi_protocol_converter_v2_1_25  -v2k5 "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/1b7e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/122e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/b205/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/fd26/hdl/verilog" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/8fe4/hdl/axi_protocol_converter_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/1b7e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/122e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/b205/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/fd26/hdl/verilog" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../bd/system/ip/system_auto_pc_0/sim/system_auto_pc_0.v" \
"../../../bd/system/ip/system_auto_pc_1/sim/system_auto_pc_1.v" \

vlog -work axi_clock_converter_v2_1_24  -v2k5 "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/1b7e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/122e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/b205/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/fd26/hdl/verilog" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/23c0/hdl/axi_clock_converter_v2_1_vl_rfs.v" \

vlog -work blk_mem_gen_v8_4_5  -v2k5 "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/1b7e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/122e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/b205/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/fd26/hdl/verilog" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/25a8/simulation/blk_mem_gen_v8_4.v" \

vlog -work axi_dwidth_converter_v2_1_25  -v2k5 "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/1b7e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/122e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/b205/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/fd26/hdl/verilog" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/38b4/hdl/axi_dwidth_converter_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/1b7e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/122e/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/b205/hdl/verilog" "+incdir+../../../../dma_pl2ps.gen/sources_1/bd/system/ipshared/fd26/hdl/verilog" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../bd/system/ip/system_auto_us_0/sim/system_auto_us_0.v" \
"../../../bd/system/sim/system.v" \

vlog -work xil_defaultlib \
"glbl.v"

