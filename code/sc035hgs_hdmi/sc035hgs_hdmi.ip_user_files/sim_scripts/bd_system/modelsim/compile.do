vlib modelsim_lib/work
vlib modelsim_lib/msim

vlib modelsim_lib/msim/xilinx_vip
vlib modelsim_lib/msim/xpm
vlib modelsim_lib/msim/xil_defaultlib
vlib modelsim_lib/msim/xlconstant_v1_1_8
vlib modelsim_lib/msim/lib_cdc_v1_0_2
vlib modelsim_lib/msim/proc_sys_reset_v5_0_14
vlib modelsim_lib/msim/smartconnect_v1_0
vlib modelsim_lib/msim/axi_infrastructure_v1_1_0
vlib modelsim_lib/msim/axi_register_slice_v2_1_29
vlib modelsim_lib/msim/axi_vip_v1_1_15
vlib modelsim_lib/msim/lib_pkg_v1_0_3
vlib modelsim_lib/msim/fifo_generator_v13_2_9
vlib modelsim_lib/msim/lib_fifo_v1_0_18
vlib modelsim_lib/msim/blk_mem_gen_v8_4_7
vlib modelsim_lib/msim/lib_bmg_v1_0_16
vlib modelsim_lib/msim/lib_srl_fifo_v1_0_3
vlib modelsim_lib/msim/axi_datamover_v5_1_31
vlib modelsim_lib/msim/axi_vdma_v6_3_17
vlib modelsim_lib/msim/processing_system7_vip_v1_0_17
vlib modelsim_lib/msim/generic_baseblocks_v2_1_1
vlib modelsim_lib/msim/axi_data_fifo_v2_1_28
vlib modelsim_lib/msim/axi_crossbar_v2_1_30
vlib modelsim_lib/msim/axi_lite_ipif_v3_0_4
vlib modelsim_lib/msim/v_tc_v6_1_13
vlib modelsim_lib/msim/v_vid_in_axi4s_v4_0_11
vlib modelsim_lib/msim/v_axi4s_vid_out_v4_0_17
vlib modelsim_lib/msim/v_tc_v6_2_7
vlib modelsim_lib/msim/v_vid_in_axi4s_v5_0_3
vlib modelsim_lib/msim/interrupt_control_v3_1_5
vlib modelsim_lib/msim/axi_gpio_v2_0_31
vlib modelsim_lib/msim/axi_protocol_converter_v2_1_29

vmap xilinx_vip modelsim_lib/msim/xilinx_vip
vmap xpm modelsim_lib/msim/xpm
vmap xil_defaultlib modelsim_lib/msim/xil_defaultlib
vmap xlconstant_v1_1_8 modelsim_lib/msim/xlconstant_v1_1_8
vmap lib_cdc_v1_0_2 modelsim_lib/msim/lib_cdc_v1_0_2
vmap proc_sys_reset_v5_0_14 modelsim_lib/msim/proc_sys_reset_v5_0_14
vmap smartconnect_v1_0 modelsim_lib/msim/smartconnect_v1_0
vmap axi_infrastructure_v1_1_0 modelsim_lib/msim/axi_infrastructure_v1_1_0
vmap axi_register_slice_v2_1_29 modelsim_lib/msim/axi_register_slice_v2_1_29
vmap axi_vip_v1_1_15 modelsim_lib/msim/axi_vip_v1_1_15
vmap lib_pkg_v1_0_3 modelsim_lib/msim/lib_pkg_v1_0_3
vmap fifo_generator_v13_2_9 modelsim_lib/msim/fifo_generator_v13_2_9
vmap lib_fifo_v1_0_18 modelsim_lib/msim/lib_fifo_v1_0_18
vmap blk_mem_gen_v8_4_7 modelsim_lib/msim/blk_mem_gen_v8_4_7
vmap lib_bmg_v1_0_16 modelsim_lib/msim/lib_bmg_v1_0_16
vmap lib_srl_fifo_v1_0_3 modelsim_lib/msim/lib_srl_fifo_v1_0_3
vmap axi_datamover_v5_1_31 modelsim_lib/msim/axi_datamover_v5_1_31
vmap axi_vdma_v6_3_17 modelsim_lib/msim/axi_vdma_v6_3_17
vmap processing_system7_vip_v1_0_17 modelsim_lib/msim/processing_system7_vip_v1_0_17
vmap generic_baseblocks_v2_1_1 modelsim_lib/msim/generic_baseblocks_v2_1_1
vmap axi_data_fifo_v2_1_28 modelsim_lib/msim/axi_data_fifo_v2_1_28
vmap axi_crossbar_v2_1_30 modelsim_lib/msim/axi_crossbar_v2_1_30
vmap axi_lite_ipif_v3_0_4 modelsim_lib/msim/axi_lite_ipif_v3_0_4
vmap v_tc_v6_1_13 modelsim_lib/msim/v_tc_v6_1_13
vmap v_vid_in_axi4s_v4_0_11 modelsim_lib/msim/v_vid_in_axi4s_v4_0_11
vmap v_axi4s_vid_out_v4_0_17 modelsim_lib/msim/v_axi4s_vid_out_v4_0_17
vmap v_tc_v6_2_7 modelsim_lib/msim/v_tc_v6_2_7
vmap v_vid_in_axi4s_v5_0_3 modelsim_lib/msim/v_vid_in_axi4s_v5_0_3
vmap interrupt_control_v3_1_5 modelsim_lib/msim/interrupt_control_v3_1_5
vmap axi_gpio_v2_0_31 modelsim_lib/msim/axi_gpio_v2_0_31
vmap axi_protocol_converter_v2_1_29 modelsim_lib/msim/axi_protocol_converter_v2_1_29

vlog -work xilinx_vip  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_17 -L xilinx_vip "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"C:/Xilinx/Vivado/2023.2/data/xilinx_vip/hdl/axi4stream_vip_axi4streampc.sv" \
"C:/Xilinx/Vivado/2023.2/data/xilinx_vip/hdl/axi_vip_axi4pc.sv" \
"C:/Xilinx/Vivado/2023.2/data/xilinx_vip/hdl/xil_common_vip_pkg.sv" \
"C:/Xilinx/Vivado/2023.2/data/xilinx_vip/hdl/axi4stream_vip_pkg.sv" \
"C:/Xilinx/Vivado/2023.2/data/xilinx_vip/hdl/axi_vip_pkg.sv" \
"C:/Xilinx/Vivado/2023.2/data/xilinx_vip/hdl/axi4stream_vip_if.sv" \
"C:/Xilinx/Vivado/2023.2/data/xilinx_vip/hdl/axi_vip_if.sv" \
"C:/Xilinx/Vivado/2023.2/data/xilinx_vip/hdl/clk_vip_if.sv" \
"C:/Xilinx/Vivado/2023.2/data/xilinx_vip/hdl/rst_vip_if.sv" \

vlog -work xpm  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_17 -L xilinx_vip "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"C:/Xilinx/Vivado/2023.2/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
"C:/Xilinx/Vivado/2023.2/data/ip/xpm/xpm_fifo/hdl/xpm_fifo.sv" \
"C:/Xilinx/Vivado/2023.2/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \

vcom -work xpm  -93  \
"C:/Xilinx/Vivado/2023.2/data/ip/xpm/xpm_VCOMP.vhd" \

vlog -work xil_defaultlib  -incr -mfcu  "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../bd/bd_system/ipshared/31a1/src/asyn_rst_syn.v" \
"../../../bd/bd_system/ipshared/31a1/src/dvi_encoder.v" \
"../../../bd/bd_system/ipshared/31a1/src/serializer_10_to_1.v" \
"../../../bd/bd_system/ipshared/31a1/src/dvi_transmitter_top.v" \
"../../../bd/bd_system/ip/bd_system_DVI_Transmitter_0_0/sim/bd_system_DVI_Transmitter_0_0.v" \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ab26/src/mmcme2_drp.v" \

vcom -work xil_defaultlib  -93  \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ab26/src/axi_dynclk_S00_AXI.vhd" \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ab26/src/axi_dynclk.vhd" \
"../../../bd/bd_system/ip/bd_system_axi_dynclk_0_0/sim/bd_system_axi_dynclk_0_0.vhd" \

vlog -work xil_defaultlib  -incr -mfcu  "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../bd/bd_system/ip/bd_system_axi_smc_0/bd_0/sim/bd_3952.v" \

vlog -work xlconstant_v1_1_8  -incr -mfcu  "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/d390/hdl/xlconstant_v1_1_vl_rfs.v" \

vlog -work xil_defaultlib  -incr -mfcu  "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../bd/bd_system/ip/bd_system_axi_smc_0/bd_0/ip/ip_0/sim/bd_3952_one_0.v" \

vcom -work lib_cdc_v1_0_2  -93  \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ef1e/hdl/lib_cdc_v1_0_rfs.vhd" \

vcom -work proc_sys_reset_v5_0_14  -93  \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/408c/hdl/proc_sys_reset_v5_0_vh_rfs.vhd" \

vcom -work xil_defaultlib  -93  \
"../../../bd/bd_system/ip/bd_system_axi_smc_0/bd_0/ip/ip_1/sim/bd_3952_psr_aclk_0.vhd" \

vlog -work smartconnect_v1_0  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_17 -L xilinx_vip "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/sc_util_v1_0_vl_rfs.sv" \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/bd53/hdl/sc_switchboard_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_17 -L xilinx_vip "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../bd/bd_system/ip/bd_system_axi_smc_0/bd_0/ip/ip_2/sim/bd_3952_arsw_0.sv" \
"../../../bd/bd_system/ip/bd_system_axi_smc_0/bd_0/ip/ip_3/sim/bd_3952_rsw_0.sv" \
"../../../bd/bd_system/ip/bd_system_axi_smc_0/bd_0/ip/ip_4/sim/bd_3952_awsw_0.sv" \
"../../../bd/bd_system/ip/bd_system_axi_smc_0/bd_0/ip/ip_5/sim/bd_3952_wsw_0.sv" \
"../../../bd/bd_system/ip/bd_system_axi_smc_0/bd_0/ip/ip_6/sim/bd_3952_bsw_0.sv" \

vlog -work smartconnect_v1_0  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_17 -L xilinx_vip "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/c6b2/hdl/sc_mmu_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_17 -L xilinx_vip "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../bd/bd_system/ip/bd_system_axi_smc_0/bd_0/ip/ip_7/sim/bd_3952_s00mmu_0.sv" \

vlog -work smartconnect_v1_0  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_17 -L xilinx_vip "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/abb8/hdl/sc_transaction_regulator_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_17 -L xilinx_vip "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../bd/bd_system/ip/bd_system_axi_smc_0/bd_0/ip/ip_8/sim/bd_3952_s00tr_0.sv" \

vlog -work smartconnect_v1_0  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_17 -L xilinx_vip "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7827/hdl/sc_si_converter_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_17 -L xilinx_vip "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../bd/bd_system/ip/bd_system_axi_smc_0/bd_0/ip/ip_9/sim/bd_3952_s00sic_0.sv" \

vlog -work smartconnect_v1_0  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_17 -L xilinx_vip "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/79ce/hdl/sc_axi2sc_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_17 -L xilinx_vip "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../bd/bd_system/ip/bd_system_axi_smc_0/bd_0/ip/ip_10/sim/bd_3952_s00a2s_0.sv" \

vlog -work smartconnect_v1_0  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_17 -L xilinx_vip "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/sc_node_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_17 -L xilinx_vip "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../bd/bd_system/ip/bd_system_axi_smc_0/bd_0/ip/ip_11/sim/bd_3952_sarn_0.sv" \
"../../../bd/bd_system/ip/bd_system_axi_smc_0/bd_0/ip/ip_12/sim/bd_3952_srn_0.sv" \
"../../../bd/bd_system/ip/bd_system_axi_smc_0/bd_0/ip/ip_13/sim/bd_3952_s01mmu_0.sv" \
"../../../bd/bd_system/ip/bd_system_axi_smc_0/bd_0/ip/ip_14/sim/bd_3952_s01tr_0.sv" \
"../../../bd/bd_system/ip/bd_system_axi_smc_0/bd_0/ip/ip_15/sim/bd_3952_s01sic_0.sv" \
"../../../bd/bd_system/ip/bd_system_axi_smc_0/bd_0/ip/ip_16/sim/bd_3952_s01a2s_0.sv" \
"../../../bd/bd_system/ip/bd_system_axi_smc_0/bd_0/ip/ip_17/sim/bd_3952_sawn_0.sv" \
"../../../bd/bd_system/ip/bd_system_axi_smc_0/bd_0/ip/ip_18/sim/bd_3952_swn_0.sv" \
"../../../bd/bd_system/ip/bd_system_axi_smc_0/bd_0/ip/ip_19/sim/bd_3952_sbn_0.sv" \

vlog -work smartconnect_v1_0  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_17 -L xilinx_vip "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ebf7/hdl/sc_sc2axi_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_17 -L xilinx_vip "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../bd/bd_system/ip/bd_system_axi_smc_0/bd_0/ip/ip_20/sim/bd_3952_m00s2a_0.sv" \
"../../../bd/bd_system/ip/bd_system_axi_smc_0/bd_0/ip/ip_21/sim/bd_3952_m00arn_0.sv" \
"../../../bd/bd_system/ip/bd_system_axi_smc_0/bd_0/ip/ip_22/sim/bd_3952_m00rn_0.sv" \
"../../../bd/bd_system/ip/bd_system_axi_smc_0/bd_0/ip/ip_23/sim/bd_3952_m00awn_0.sv" \
"../../../bd/bd_system/ip/bd_system_axi_smc_0/bd_0/ip/ip_24/sim/bd_3952_m00wn_0.sv" \
"../../../bd/bd_system/ip/bd_system_axi_smc_0/bd_0/ip/ip_25/sim/bd_3952_m00bn_0.sv" \

vlog -work smartconnect_v1_0  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_17 -L xilinx_vip "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6eea/hdl/sc_exit_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_17 -L xilinx_vip "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../bd/bd_system/ip/bd_system_axi_smc_0/bd_0/ip/ip_26/sim/bd_3952_m00e_0.sv" \

vlog -work axi_infrastructure_v1_1_0  -incr -mfcu  "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl/axi_infrastructure_v1_1_vl_rfs.v" \

vlog -work axi_register_slice_v2_1_29  -incr -mfcu  "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ff9f/hdl/axi_register_slice_v2_1_vl_rfs.v" \

vlog -work axi_vip_v1_1_15  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_17 -L xilinx_vip "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/5753/hdl/axi_vip_v1_1_vl_rfs.sv" \

vlog -work xil_defaultlib  -incr -mfcu  "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../bd/bd_system/ip/bd_system_axi_smc_0/sim/bd_system_axi_smc_0.v" \

vcom -work lib_pkg_v1_0_3  -93  \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/56d9/hdl/lib_pkg_v1_0_rfs.vhd" \

vlog -work fifo_generator_v13_2_9  -incr -mfcu  "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ac72/simulation/fifo_generator_vlog_beh.v" \

vcom -work fifo_generator_v13_2_9  -93  \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ac72/hdl/fifo_generator_v13_2_rfs.vhd" \

vlog -work fifo_generator_v13_2_9  -incr -mfcu  "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ac72/hdl/fifo_generator_v13_2_rfs.v" \

vcom -work lib_fifo_v1_0_18  -93  \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/1531/hdl/lib_fifo_v1_0_rfs.vhd" \

vlog -work blk_mem_gen_v8_4_7  -incr -mfcu  "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/3c0c/simulation/blk_mem_gen_v8_4.v" \

vcom -work lib_bmg_v1_0_16  -93  \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/5c9c/hdl/lib_bmg_v1_0_rfs.vhd" \

vcom -work lib_srl_fifo_v1_0_3  -93  \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/02c4/hdl/lib_srl_fifo_v1_0_rfs.vhd" \

vcom -work axi_datamover_v5_1_31  -93  \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/d786/hdl/axi_datamover_v5_1_vh_rfs.vhd" \

vlog -work axi_vdma_v6_3_17  -incr -mfcu  "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl/axi_vdma_v6_3_rfs.v" \

vcom -work axi_vdma_v6_3_17  -93  \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl/axi_vdma_v6_3_rfs.vhd" \

vcom -work xil_defaultlib  -93  \
"../../../bd/bd_system/ip/bd_system_axi_vdma_0_0/sim/bd_system_axi_vdma_0_0.vhd" \

vlog -work processing_system7_vip_v1_0_17  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_17 -L xilinx_vip "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl/processing_system7_vip_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -incr -mfcu  "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../bd/bd_system/ip/bd_system_processing_system7_0_0/sim/bd_system_processing_system7_0_0.v" \

vlog -work generic_baseblocks_v2_1_1  -incr -mfcu  "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/10ab/hdl/generic_baseblocks_v2_1_vl_rfs.v" \

vlog -work axi_data_fifo_v2_1_28  -incr -mfcu  "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/279e/hdl/axi_data_fifo_v2_1_vl_rfs.v" \

vlog -work axi_crossbar_v2_1_30  -incr -mfcu  "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/fb47/hdl/axi_crossbar_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -incr -mfcu  "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../bd/bd_system/ip/bd_system_xbar_0/sim/bd_system_xbar_0.v" \

vcom -work xil_defaultlib  -93  \
"../../../bd/bd_system/ip/bd_system_rst_ps7_0_100M_0/sim/bd_system_rst_ps7_0_100M_0.vhd" \
"../../../bd/bd_system/ip/bd_system_rst_ps7_0_50M_0/sim/bd_system_rst_ps7_0_50M_0.vhd" \

vcom -work axi_lite_ipif_v3_0_4  -93  \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/66ea/hdl/axi_lite_ipif_v3_0_vh_rfs.vhd" \

vcom -work v_tc_v6_1_13  -93  \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/b92e/hdl/v_tc_v6_1_vh_rfs.vhd" \

vlog -work v_vid_in_axi4s_v4_0_11  -incr -mfcu  "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/4705/hdl/v_vid_in_axi4s_v4_0_vl_rfs.v" \

vlog -work v_axi4s_vid_out_v4_0_17  -incr -mfcu  "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/b7a6/hdl/v_axi4s_vid_out_v4_0_vl_rfs.v" \

vlog -work xil_defaultlib  -incr -mfcu  "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../bd/bd_system/ip/bd_system_v_axi4s_vid_out_0_0/sim/bd_system_v_axi4s_vid_out_0_0.v" \

vcom -work v_tc_v6_2_7  -93  \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/0e63/hdl/v_tc_v6_2_vh_rfs.vhd" \

vcom -work xil_defaultlib  -93  \
"../../../bd/bd_system/ip/bd_system_v_tc_0_0/sim/bd_system_v_tc_0_0.vhd" \

vlog -work v_vid_in_axi4s_v5_0_3  -incr -mfcu  "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7302/hdl/v_vid_in_axi4s_v5_0_vl_rfs.v" \

vlog -work xil_defaultlib  -incr -mfcu  "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../bd/bd_system/ip/bd_system_v_vid_in_axi4s_0_0/sim/bd_system_v_vid_in_axi4s_0_0.v" \
"../../../bd/bd_system/ip/bd_system_sc035hgs_0_0/sim/bd_system_sc035hgs_0_0.v" \

vcom -work interrupt_control_v3_1_5  -93  \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/d8cc/hdl/interrupt_control_v3_1_vh_rfs.vhd" \

vcom -work axi_gpio_v2_0_31  -93  \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6fbe/hdl/axi_gpio_v2_0_vh_rfs.vhd" \

vcom -work xil_defaultlib  -93  \
"../../../bd/bd_system/ip/bd_system_axi_gpio_0_0/sim/bd_system_axi_gpio_0_0.vhd" \
"../../../bd/bd_system/ip/bd_system_axi_gpio_0_1/sim/bd_system_axi_gpio_0_1.vhd" \
"../../../bd/bd_system/ip/bd_system_axi_gpio_0_2/sim/bd_system_axi_gpio_0_2.vhd" \

vlog -work xil_defaultlib  -incr -mfcu  "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../bd/bd_system/sim/bd_system.v" \

vcom -work xil_defaultlib  -93  \
"../../../bd/bd_system/ip/bd_system_axi_gpio_0_3/sim/bd_system_axi_gpio_0_3.vhd" \

vlog -work axi_protocol_converter_v2_1_29  -incr -mfcu  "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/a63f/hdl/axi_protocol_converter_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -incr -mfcu  "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/f0b6/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/35de/hdl/verilog" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/ec67/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/7fb4/hdl" "+incdir+../../../../sc035hgs_hdmi.gen/sources_1/bd/bd_system/ipshared/6b2b/hdl" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../bd/bd_system/ip/bd_system_auto_pc_0/sim/bd_system_auto_pc_0.v" \

vlog -work xil_defaultlib \
"glbl.v"

