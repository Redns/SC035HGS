vlib work
vlib riviera

vlib riviera/xilinx_vip
vlib riviera/xpm
vlib riviera/axi_infrastructure_v1_1_0
vlib riviera/axi_vip_v1_1_11
vlib riviera/processing_system7_vip_v1_0_13
vlib riviera/xil_defaultlib
vlib riviera/generic_baseblocks_v2_1_0
vlib riviera/axi_register_slice_v2_1_25
vlib riviera/fifo_generator_v13_2_6
vlib riviera/axi_data_fifo_v2_1_24
vlib riviera/axi_crossbar_v2_1_26
vlib riviera/lib_cdc_v1_0_2
vlib riviera/proc_sys_reset_v5_0_13
vlib riviera/lib_pkg_v1_0_2
vlib riviera/lib_fifo_v1_0_15
vlib riviera/lib_srl_fifo_v1_0_2
vlib riviera/axi_datamover_v5_1_27
vlib riviera/axi_sg_v4_1_14
vlib riviera/axi_dma_v7_1_26
vlib riviera/axi_lite_ipif_v3_0_4
vlib riviera/interrupt_control_v3_1_4
vlib riviera/axi_gpio_v2_0_27
vlib riviera/util_vector_logic_v2_0_1
vlib riviera/axi_protocol_converter_v2_1_25
vlib riviera/axi_clock_converter_v2_1_24
vlib riviera/blk_mem_gen_v8_4_5
vlib riviera/axi_dwidth_converter_v2_1_25

vmap xilinx_vip riviera/xilinx_vip
vmap xpm riviera/xpm
vmap axi_infrastructure_v1_1_0 riviera/axi_infrastructure_v1_1_0
vmap axi_vip_v1_1_11 riviera/axi_vip_v1_1_11
vmap processing_system7_vip_v1_0_13 riviera/processing_system7_vip_v1_0_13
vmap xil_defaultlib riviera/xil_defaultlib
vmap generic_baseblocks_v2_1_0 riviera/generic_baseblocks_v2_1_0
vmap axi_register_slice_v2_1_25 riviera/axi_register_slice_v2_1_25
vmap fifo_generator_v13_2_6 riviera/fifo_generator_v13_2_6
vmap axi_data_fifo_v2_1_24 riviera/axi_data_fifo_v2_1_24
vmap axi_crossbar_v2_1_26 riviera/axi_crossbar_v2_1_26
vmap lib_cdc_v1_0_2 riviera/lib_cdc_v1_0_2
vmap proc_sys_reset_v5_0_13 riviera/proc_sys_reset_v5_0_13
vmap lib_pkg_v1_0_2 riviera/lib_pkg_v1_0_2
vmap lib_fifo_v1_0_15 riviera/lib_fifo_v1_0_15
vmap lib_srl_fifo_v1_0_2 riviera/lib_srl_fifo_v1_0_2
vmap axi_datamover_v5_1_27 riviera/axi_datamover_v5_1_27
vmap axi_sg_v4_1_14 riviera/axi_sg_v4_1_14
vmap axi_dma_v7_1_26 riviera/axi_dma_v7_1_26
vmap axi_lite_ipif_v3_0_4 riviera/axi_lite_ipif_v3_0_4
vmap interrupt_control_v3_1_4 riviera/interrupt_control_v3_1_4
vmap axi_gpio_v2_0_27 riviera/axi_gpio_v2_0_27
vmap util_vector_logic_v2_0_1 riviera/util_vector_logic_v2_0_1
vmap axi_protocol_converter_v2_1_25 riviera/axi_protocol_converter_v2_1_25
vmap axi_clock_converter_v2_1_24 riviera/axi_clock_converter_v2_1_24
vmap blk_mem_gen_v8_4_5 riviera/blk_mem_gen_v8_4_5
vmap axi_dwidth_converter_v2_1_25 riviera/axi_dwidth_converter_v2_1_25

vlog -work xilinx_vip  -sv2k12 "+incdir+C:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"C:/Xilinx/Vivado/2021.2/data/xilinx_vip/hdl/axi4stream_vip_axi4streampc.sv" \
"C:/Xilinx/Vivado/2021.2/data/xilinx_vip/hdl/axi_vip_axi4pc.sv" \
"C:/Xilinx/Vivado/2021.2/data/xilinx_vip/hdl/xil_common_vip_pkg.sv" \
"C:/Xilinx/Vivado/2021.2/data/xilinx_vip/hdl/axi4stream_vip_pkg.sv" \
"C:/Xilinx/Vivado/2021.2/data/xilinx_vip/hdl/axi_vip_pkg.sv" \
"C:/Xilinx/Vivado/2021.2/data/xilinx_vip/hdl/axi4stream_vip_if.sv" \
"C:/Xilinx/Vivado/2021.2/data/xilinx_vip/hdl/axi_vip_if.sv" \
"C:/Xilinx/Vivado/2021.2/data/xilinx_vip/hdl/clk_vip_if.sv" \
"C:/Xilinx/Vivado/2021.2/data/xilinx_vip/hdl/rst_vip_if.sv" \

vlog -work xpm  -sv2k12 "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/62b6" "+incdir+C:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"C:/Xilinx/Vivado/2021.2/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
"C:/Xilinx/Vivado/2021.2/data/ip/xpm/xpm_fifo/hdl/xpm_fifo.sv" \
"C:/Xilinx/Vivado/2021.2/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \

vcom -work xpm -93 \
"C:/Xilinx/Vivado/2021.2/data/ip/xpm/xpm_VCOMP.vhd" \

vlog -work axi_infrastructure_v1_1_0  -v2k5 "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/62b6" "+incdir+C:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/ec67/hdl/axi_infrastructure_v1_1_vl_rfs.v" \

vlog -work axi_vip_v1_1_11  -sv2k12 "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/62b6" "+incdir+C:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/63b7/hdl/axi_vip_v1_1_vl_rfs.sv" \

vlog -work processing_system7_vip_v1_0_13  -sv2k12 "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/62b6" "+incdir+C:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/3007/hdl/processing_system7_vip_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/62b6" "+incdir+C:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../bd/system/ip/system_processing_system7_0_0/sim/system_processing_system7_0_0.v" \

vlog -work generic_baseblocks_v2_1_0  -v2k5 "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/62b6" "+incdir+C:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/b752/hdl/generic_baseblocks_v2_1_vl_rfs.v" \

vlog -work axi_register_slice_v2_1_25  -v2k5 "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/62b6" "+incdir+C:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/e1e6/hdl/axi_register_slice_v2_1_vl_rfs.v" \

vlog -work fifo_generator_v13_2_6  -v2k5 "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/62b6" "+incdir+C:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/8ae1/simulation/fifo_generator_vlog_beh.v" \

vcom -work fifo_generator_v13_2_6 -93 \
"../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/8ae1/hdl/fifo_generator_v13_2_rfs.vhd" \

vlog -work fifo_generator_v13_2_6  -v2k5 "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/62b6" "+incdir+C:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/8ae1/hdl/fifo_generator_v13_2_rfs.v" \

vlog -work axi_data_fifo_v2_1_24  -v2k5 "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/62b6" "+incdir+C:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/fa53/hdl/axi_data_fifo_v2_1_vl_rfs.v" \

vlog -work axi_crossbar_v2_1_26  -v2k5 "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/62b6" "+incdir+C:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/ac57/hdl/axi_crossbar_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/62b6" "+incdir+C:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../bd/system/ip/system_xbar_0/sim/system_xbar_0.v" \

vcom -work lib_cdc_v1_0_2 -93 \
"../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/ef1e/hdl/lib_cdc_v1_0_rfs.vhd" \

vcom -work proc_sys_reset_v5_0_13 -93 \
"../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/8842/hdl/proc_sys_reset_v5_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/system/ip/system_rst_ps7_0_50M_0/sim/system_rst_ps7_0_50M_0.vhd" \

vcom -work lib_pkg_v1_0_2 -93 \
"../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/0513/hdl/lib_pkg_v1_0_rfs.vhd" \

vcom -work lib_fifo_v1_0_15 -93 \
"../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/a4ed/hdl/lib_fifo_v1_0_rfs.vhd" \

vcom -work lib_srl_fifo_v1_0_2 -93 \
"../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/51ce/hdl/lib_srl_fifo_v1_0_rfs.vhd" \

vcom -work axi_datamover_v5_1_27 -93 \
"../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/9b19/hdl/axi_datamover_v5_1_vh_rfs.vhd" \

vcom -work axi_sg_v4_1_14 -93 \
"../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/bcf6/hdl/axi_sg_v4_1_rfs.vhd" \

vcom -work axi_dma_v7_1_26 -93 \
"../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/69a4/hdl/axi_dma_v7_1_vh_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/system/ip/system_axi_dma_0_0/sim/system_axi_dma_0_0.vhd" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/62b6" "+incdir+C:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../bd/system/ip/system_clk_wiz_0_0/system_clk_wiz_0_0_clk_wiz.v" \
"../../../bd/system/ip/system_clk_wiz_0_0/system_clk_wiz_0_0.v" \

vcom -work axi_lite_ipif_v3_0_4 -93 \
"../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/66ea/hdl/axi_lite_ipif_v3_0_vh_rfs.vhd" \

vcom -work interrupt_control_v3_1_4 -93 \
"../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/a040/hdl/interrupt_control_v3_1_vh_rfs.vhd" \

vcom -work axi_gpio_v2_0_27 -93 \
"../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/a5bb/hdl/axi_gpio_v2_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/system/ip/system_axi_gpio_0_10/sim/system_axi_gpio_0_10.vhd" \
"../../../bd/system/ip/system_axi_gpio_0_11/sim/system_axi_gpio_0_11.vhd" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/62b6" "+incdir+C:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../bd/system/ipshared/7bbf/fs_cap.v" \
"../../../bd/system/ipshared/7bbf/ui_axisbufw.v" \
"../../../bd/system/ip/system_ui_axisbufw_0_0/sim/system_ui_axisbufw_0_0.v" \

vlog -work util_vector_logic_v2_0_1  -v2k5 "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/62b6" "+incdir+C:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/3f90/hdl/util_vector_logic_v2_0_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/62b6" "+incdir+C:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../bd/system/ip/system_util_vector_logic_0_0/sim/system_util_vector_logic_0_0.v" \
"../../../bd/system/ip/system_util_vector_logic_1_0/sim/system_util_vector_logic_1_0.v" \

vcom -work xil_defaultlib -93 \
"../../../bd/system/ip/system_axi_gpio_0_13/sim/system_axi_gpio_0_13.vhd" \
"../../../bd/system/ip/system_axi_gpio_0_14/sim/system_axi_gpio_0_14.vhd" \
"../../../bd/system/ip/system_axi_gpio_0_15/sim/system_axi_gpio_0_15.vhd" \
"../../../bd/system/ip/system_axi_gpio_0_16/sim/system_axi_gpio_0_16.vhd" \
"../../../bd/system/ip/system_axi_gpio_0_17/sim/system_axi_gpio_0_17.vhd" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/62b6" "+incdir+C:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../bd/system/sim/system.v" \

vcom -work xil_defaultlib -93 \
"../../../bd/system/ip/system_axi_gpio_0_18/sim/system_axi_gpio_0_18.vhd" \

vlog -work axi_protocol_converter_v2_1_25  -v2k5 "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/62b6" "+incdir+C:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/8fe4/hdl/axi_protocol_converter_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/62b6" "+incdir+C:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../bd/system/ip/system_auto_pc_0/sim/system_auto_pc_0.v" \
"../../../bd/system/ip/system_auto_pc_1/sim/system_auto_pc_1.v" \

vlog -work axi_clock_converter_v2_1_24  -v2k5 "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/62b6" "+incdir+C:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/23c0/hdl/axi_clock_converter_v2_1_vl_rfs.v" \

vlog -work blk_mem_gen_v8_4_5  -v2k5 "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/62b6" "+incdir+C:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/25a8/simulation/blk_mem_gen_v8_4.v" \

vlog -work axi_dwidth_converter_v2_1_25  -v2k5 "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/62b6" "+incdir+C:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/38b4/hdl/axi_dwidth_converter_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/ec67/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/3007/hdl" "+incdir+../../../../sc_camera_dvp.gen/sources_1/bd/system/ipshared/62b6" "+incdir+C:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../bd/system/ip/system_auto_us_0/sim/system_auto_us_0.v" \

vlog -work xil_defaultlib \
"glbl.v"

