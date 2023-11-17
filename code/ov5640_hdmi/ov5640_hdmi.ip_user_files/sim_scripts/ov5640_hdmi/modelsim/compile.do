vlib modelsim_lib/work
vlib modelsim_lib/msim

vlib modelsim_lib/msim/xilinx_vip
vlib modelsim_lib/msim/xpm
vlib modelsim_lib/msim/xil_defaultlib
vlib modelsim_lib/msim/xlconstant_v1_1_7
vlib modelsim_lib/msim/lib_cdc_v1_0_2
vlib modelsim_lib/msim/proc_sys_reset_v5_0_13
vlib modelsim_lib/msim/smartconnect_v1_0
vlib modelsim_lib/msim/axi_infrastructure_v1_1_0
vlib modelsim_lib/msim/axi_register_slice_v2_1_25
vlib modelsim_lib/msim/axi_vip_v1_1_11
vlib modelsim_lib/msim/lib_pkg_v1_0_2
vlib modelsim_lib/msim/fifo_generator_v13_2_6
vlib modelsim_lib/msim/lib_fifo_v1_0_15
vlib modelsim_lib/msim/blk_mem_gen_v8_4_5
vlib modelsim_lib/msim/lib_bmg_v1_0_14
vlib modelsim_lib/msim/lib_srl_fifo_v1_0_2
vlib modelsim_lib/msim/axi_datamover_v5_1_27
vlib modelsim_lib/msim/axi_vdma_v6_3_13
vlib modelsim_lib/msim/processing_system7_vip_v1_0_13
vlib modelsim_lib/msim/generic_baseblocks_v2_1_0
vlib modelsim_lib/msim/axi_data_fifo_v2_1_24
vlib modelsim_lib/msim/axi_crossbar_v2_1_26
vlib modelsim_lib/msim/axi_lite_ipif_v3_0_4
vlib modelsim_lib/msim/v_tc_v6_1_13
vlib modelsim_lib/msim/v_vid_in_axi4s_v4_0_9
vlib modelsim_lib/msim/v_axi4s_vid_out_v4_0_13
vlib modelsim_lib/msim/v_tc_v6_2_3
vlib modelsim_lib/msim/v_vid_in_axi4s_v5_0_0
vlib modelsim_lib/msim/axi_protocol_converter_v2_1_25

vmap xilinx_vip modelsim_lib/msim/xilinx_vip
vmap xpm modelsim_lib/msim/xpm
vmap xil_defaultlib modelsim_lib/msim/xil_defaultlib
vmap xlconstant_v1_1_7 modelsim_lib/msim/xlconstant_v1_1_7
vmap lib_cdc_v1_0_2 modelsim_lib/msim/lib_cdc_v1_0_2
vmap proc_sys_reset_v5_0_13 modelsim_lib/msim/proc_sys_reset_v5_0_13
vmap smartconnect_v1_0 modelsim_lib/msim/smartconnect_v1_0
vmap axi_infrastructure_v1_1_0 modelsim_lib/msim/axi_infrastructure_v1_1_0
vmap axi_register_slice_v2_1_25 modelsim_lib/msim/axi_register_slice_v2_1_25
vmap axi_vip_v1_1_11 modelsim_lib/msim/axi_vip_v1_1_11
vmap lib_pkg_v1_0_2 modelsim_lib/msim/lib_pkg_v1_0_2
vmap fifo_generator_v13_2_6 modelsim_lib/msim/fifo_generator_v13_2_6
vmap lib_fifo_v1_0_15 modelsim_lib/msim/lib_fifo_v1_0_15
vmap blk_mem_gen_v8_4_5 modelsim_lib/msim/blk_mem_gen_v8_4_5
vmap lib_bmg_v1_0_14 modelsim_lib/msim/lib_bmg_v1_0_14
vmap lib_srl_fifo_v1_0_2 modelsim_lib/msim/lib_srl_fifo_v1_0_2
vmap axi_datamover_v5_1_27 modelsim_lib/msim/axi_datamover_v5_1_27
vmap axi_vdma_v6_3_13 modelsim_lib/msim/axi_vdma_v6_3_13
vmap processing_system7_vip_v1_0_13 modelsim_lib/msim/processing_system7_vip_v1_0_13
vmap generic_baseblocks_v2_1_0 modelsim_lib/msim/generic_baseblocks_v2_1_0
vmap axi_data_fifo_v2_1_24 modelsim_lib/msim/axi_data_fifo_v2_1_24
vmap axi_crossbar_v2_1_26 modelsim_lib/msim/axi_crossbar_v2_1_26
vmap axi_lite_ipif_v3_0_4 modelsim_lib/msim/axi_lite_ipif_v3_0_4
vmap v_tc_v6_1_13 modelsim_lib/msim/v_tc_v6_1_13
vmap v_vid_in_axi4s_v4_0_9 modelsim_lib/msim/v_vid_in_axi4s_v4_0_9
vmap v_axi4s_vid_out_v4_0_13 modelsim_lib/msim/v_axi4s_vid_out_v4_0_13
vmap v_tc_v6_2_3 modelsim_lib/msim/v_tc_v6_2_3
vmap v_vid_in_axi4s_v5_0_0 modelsim_lib/msim/v_vid_in_axi4s_v5_0_0
vmap axi_protocol_converter_v2_1_25 modelsim_lib/msim/axi_protocol_converter_v2_1_25

vlog -work xilinx_vip  -incr -mfcu -sv -L axi_vip_v1_1_11 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_13 -L xilinx_vip "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"D:/Xilinx/Vivado/2021.2/data/xilinx_vip/hdl/axi4stream_vip_axi4streampc.sv" \
"D:/Xilinx/Vivado/2021.2/data/xilinx_vip/hdl/axi_vip_axi4pc.sv" \
"D:/Xilinx/Vivado/2021.2/data/xilinx_vip/hdl/xil_common_vip_pkg.sv" \
"D:/Xilinx/Vivado/2021.2/data/xilinx_vip/hdl/axi4stream_vip_pkg.sv" \
"D:/Xilinx/Vivado/2021.2/data/xilinx_vip/hdl/axi_vip_pkg.sv" \
"D:/Xilinx/Vivado/2021.2/data/xilinx_vip/hdl/axi4stream_vip_if.sv" \
"D:/Xilinx/Vivado/2021.2/data/xilinx_vip/hdl/axi_vip_if.sv" \
"D:/Xilinx/Vivado/2021.2/data/xilinx_vip/hdl/clk_vip_if.sv" \
"D:/Xilinx/Vivado/2021.2/data/xilinx_vip/hdl/rst_vip_if.sv" \

vlog -work xpm  -incr -mfcu -sv -L axi_vip_v1_1_11 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_13 -L xilinx_vip "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"D:/Xilinx/Vivado/2021.2/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
"D:/Xilinx/Vivado/2021.2/data/ip/xpm/xpm_fifo/hdl/xpm_fifo.sv" \
"D:/Xilinx/Vivado/2021.2/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \

vcom -work xpm  -93 \
"D:/Xilinx/Vivado/2021.2/data/ip/xpm/xpm_VCOMP.vhd" \

vlog -work xil_defaultlib  -incr -mfcu "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../bd/ov5640_hdmi/ipshared/31a1/src/asyn_rst_syn.v" \
"../../../bd/ov5640_hdmi/ipshared/31a1/src/dvi_encoder.v" \
"../../../bd/ov5640_hdmi/ipshared/31a1/src/serializer_10_to_1.v" \
"../../../bd/ov5640_hdmi/ipshared/31a1/src/dvi_transmitter_top.v" \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_DVI_Transmitter_0_0/sim/ov5640_hdmi_DVI_Transmitter_0_0.v" \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ab26/src/mmcme2_drp.v" \

vcom -work xil_defaultlib  -93 \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ab26/src/axi_dynclk_S00_AXI.vhd" \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ab26/src/axi_dynclk.vhd" \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_axi_dynclk_0_0/sim/ov5640_hdmi_axi_dynclk_0_0.vhd" \

vlog -work xil_defaultlib  -incr -mfcu "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_axi_smc_1/bd_0/sim/bd_7f4b.v" \

vlog -work xlconstant_v1_1_7  -incr -mfcu "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/fcfc/hdl/xlconstant_v1_1_vl_rfs.v" \

vlog -work xil_defaultlib  -incr -mfcu "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_axi_smc_1/bd_0/ip/ip_0/sim/bd_7f4b_one_0.v" \

vcom -work lib_cdc_v1_0_2  -93 \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ef1e/hdl/lib_cdc_v1_0_rfs.vhd" \

vcom -work proc_sys_reset_v5_0_13  -93 \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/8842/hdl/proc_sys_reset_v5_0_vh_rfs.vhd" \

vcom -work xil_defaultlib  -93 \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_axi_smc_1/bd_0/ip/ip_1/sim/bd_7f4b_psr_aclk_0.vhd" \

vlog -work smartconnect_v1_0  -incr -mfcu -sv -L axi_vip_v1_1_11 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_13 -L xilinx_vip "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/sc_util_v1_0_vl_rfs.sv" \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/c012/hdl/sc_switchboard_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -incr -mfcu -sv -L axi_vip_v1_1_11 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_13 -L xilinx_vip "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_axi_smc_1/bd_0/ip/ip_2/sim/bd_7f4b_arsw_0.sv" \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_axi_smc_1/bd_0/ip/ip_3/sim/bd_7f4b_rsw_0.sv" \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_axi_smc_1/bd_0/ip/ip_4/sim/bd_7f4b_awsw_0.sv" \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_axi_smc_1/bd_0/ip/ip_5/sim/bd_7f4b_wsw_0.sv" \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_axi_smc_1/bd_0/ip/ip_6/sim/bd_7f4b_bsw_0.sv" \

vlog -work smartconnect_v1_0  -incr -mfcu -sv -L axi_vip_v1_1_11 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_13 -L xilinx_vip "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ea34/hdl/sc_mmu_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -incr -mfcu -sv -L axi_vip_v1_1_11 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_13 -L xilinx_vip "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_axi_smc_1/bd_0/ip/ip_7/sim/bd_7f4b_s00mmu_0.sv" \

vlog -work smartconnect_v1_0  -incr -mfcu -sv -L axi_vip_v1_1_11 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_13 -L xilinx_vip "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/4fd2/hdl/sc_transaction_regulator_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -incr -mfcu -sv -L axi_vip_v1_1_11 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_13 -L xilinx_vip "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_axi_smc_1/bd_0/ip/ip_8/sim/bd_7f4b_s00tr_0.sv" \

vlog -work smartconnect_v1_0  -incr -mfcu -sv -L axi_vip_v1_1_11 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_13 -L xilinx_vip "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/8047/hdl/sc_si_converter_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -incr -mfcu -sv -L axi_vip_v1_1_11 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_13 -L xilinx_vip "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_axi_smc_1/bd_0/ip/ip_9/sim/bd_7f4b_s00sic_0.sv" \

vlog -work smartconnect_v1_0  -incr -mfcu -sv -L axi_vip_v1_1_11 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_13 -L xilinx_vip "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/b89e/hdl/sc_axi2sc_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -incr -mfcu -sv -L axi_vip_v1_1_11 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_13 -L xilinx_vip "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_axi_smc_1/bd_0/ip/ip_10/sim/bd_7f4b_s00a2s_0.sv" \

vlog -work smartconnect_v1_0  -incr -mfcu -sv -L axi_vip_v1_1_11 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_13 -L xilinx_vip "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/sc_node_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -incr -mfcu -sv -L axi_vip_v1_1_11 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_13 -L xilinx_vip "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_axi_smc_1/bd_0/ip/ip_11/sim/bd_7f4b_sarn_0.sv" \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_axi_smc_1/bd_0/ip/ip_12/sim/bd_7f4b_srn_0.sv" \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_axi_smc_1/bd_0/ip/ip_13/sim/bd_7f4b_s01mmu_0.sv" \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_axi_smc_1/bd_0/ip/ip_14/sim/bd_7f4b_s01tr_0.sv" \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_axi_smc_1/bd_0/ip/ip_15/sim/bd_7f4b_s01sic_0.sv" \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_axi_smc_1/bd_0/ip/ip_16/sim/bd_7f4b_s01a2s_0.sv" \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_axi_smc_1/bd_0/ip/ip_17/sim/bd_7f4b_sawn_0.sv" \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_axi_smc_1/bd_0/ip/ip_18/sim/bd_7f4b_swn_0.sv" \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_axi_smc_1/bd_0/ip/ip_19/sim/bd_7f4b_sbn_0.sv" \

vlog -work smartconnect_v1_0  -incr -mfcu -sv -L axi_vip_v1_1_11 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_13 -L xilinx_vip "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/7005/hdl/sc_sc2axi_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -incr -mfcu -sv -L axi_vip_v1_1_11 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_13 -L xilinx_vip "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_axi_smc_1/bd_0/ip/ip_20/sim/bd_7f4b_m00s2a_0.sv" \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_axi_smc_1/bd_0/ip/ip_21/sim/bd_7f4b_m00arn_0.sv" \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_axi_smc_1/bd_0/ip/ip_22/sim/bd_7f4b_m00rn_0.sv" \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_axi_smc_1/bd_0/ip/ip_23/sim/bd_7f4b_m00awn_0.sv" \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_axi_smc_1/bd_0/ip/ip_24/sim/bd_7f4b_m00wn_0.sv" \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_axi_smc_1/bd_0/ip/ip_25/sim/bd_7f4b_m00bn_0.sv" \

vlog -work smartconnect_v1_0  -incr -mfcu -sv -L axi_vip_v1_1_11 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_13 -L xilinx_vip "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/93a6/hdl/sc_exit_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -incr -mfcu -sv -L axi_vip_v1_1_11 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_13 -L xilinx_vip "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_axi_smc_1/bd_0/ip/ip_26/sim/bd_7f4b_m00e_0.sv" \

vlog -work axi_infrastructure_v1_1_0  -incr -mfcu "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl/axi_infrastructure_v1_1_vl_rfs.v" \

vlog -work axi_register_slice_v2_1_25  -incr -mfcu "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/e1e6/hdl/axi_register_slice_v2_1_vl_rfs.v" \

vlog -work axi_vip_v1_1_11  -incr -mfcu -sv -L axi_vip_v1_1_11 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_13 -L xilinx_vip "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/63b7/hdl/axi_vip_v1_1_vl_rfs.sv" \

vlog -work xil_defaultlib  -incr -mfcu "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_axi_smc_1/sim/ov5640_hdmi_axi_smc_1.v" \

vcom -work lib_pkg_v1_0_2  -93 \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/0513/hdl/lib_pkg_v1_0_rfs.vhd" \

vlog -work fifo_generator_v13_2_6  -incr -mfcu "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/8ae1/simulation/fifo_generator_vlog_beh.v" \

vcom -work fifo_generator_v13_2_6  -93 \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/8ae1/hdl/fifo_generator_v13_2_rfs.vhd" \

vlog -work fifo_generator_v13_2_6  -incr -mfcu "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/8ae1/hdl/fifo_generator_v13_2_rfs.v" \

vcom -work lib_fifo_v1_0_15  -93 \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/a4ed/hdl/lib_fifo_v1_0_rfs.vhd" \

vlog -work blk_mem_gen_v8_4_5  -incr -mfcu "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/25a8/simulation/blk_mem_gen_v8_4.v" \

vcom -work lib_bmg_v1_0_14  -93 \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3a3e/hdl/lib_bmg_v1_0_rfs.vhd" \

vcom -work lib_srl_fifo_v1_0_2  -93 \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/51ce/hdl/lib_srl_fifo_v1_0_rfs.vhd" \

vcom -work axi_datamover_v5_1_27  -93 \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/9b19/hdl/axi_datamover_v5_1_vh_rfs.vhd" \

vlog -work axi_vdma_v6_3_13  -incr -mfcu "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl/axi_vdma_v6_3_rfs.v" \

vcom -work axi_vdma_v6_3_13  -93 \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl/axi_vdma_v6_3_rfs.vhd" \

vcom -work xil_defaultlib  -93 \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_axi_vdma_0_0/sim/ov5640_hdmi_axi_vdma_0_0.vhd" \

vlog -work xil_defaultlib  -incr -mfcu "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../bd/ov5640_hdmi/ipshared/0a09/src/ov5640_capture_data.v" \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_ov5640_capture_data_0_0/sim/ov5640_hdmi_ov5640_capture_data_0_0.v" \

vlog -work processing_system7_vip_v1_0_13  -incr -mfcu -sv -L axi_vip_v1_1_11 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_13 -L xilinx_vip "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl/processing_system7_vip_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -incr -mfcu "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_processing_system7_0_0/sim/ov5640_hdmi_processing_system7_0_0.v" \

vlog -work generic_baseblocks_v2_1_0  -incr -mfcu "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/b752/hdl/generic_baseblocks_v2_1_vl_rfs.v" \

vlog -work axi_data_fifo_v2_1_24  -incr -mfcu "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/fa53/hdl/axi_data_fifo_v2_1_vl_rfs.v" \

vlog -work axi_crossbar_v2_1_26  -incr -mfcu "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ac57/hdl/axi_crossbar_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -incr -mfcu "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_xbar_0/sim/ov5640_hdmi_xbar_0.v" \

vcom -work xil_defaultlib  -93 \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_rst_ps7_0_100M_1/sim/ov5640_hdmi_rst_ps7_0_100M_1.vhd" \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_rst_ps7_0_50M_0/sim/ov5640_hdmi_rst_ps7_0_50M_0.vhd" \

vcom -work axi_lite_ipif_v3_0_4  -93 \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66ea/hdl/axi_lite_ipif_v3_0_vh_rfs.vhd" \

vcom -work v_tc_v6_1_13  -93 \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/b92e/hdl/v_tc_v6_1_vh_rfs.vhd" \

vlog -work v_vid_in_axi4s_v4_0_9  -incr -mfcu "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/b2aa/hdl/v_vid_in_axi4s_v4_0_vl_rfs.v" \

vlog -work v_axi4s_vid_out_v4_0_13  -incr -mfcu "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/da0d/hdl/v_axi4s_vid_out_v4_0_vl_rfs.v" \

vlog -work xil_defaultlib  -incr -mfcu "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_v_axi4s_vid_out_0_0/sim/ov5640_hdmi_v_axi4s_vid_out_0_0.v" \

vcom -work v_tc_v6_2_3  -93 \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ee1d/hdl/v_tc_v6_2_vh_rfs.vhd" \

vcom -work xil_defaultlib  -93 \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_v_tc_0_0/sim/ov5640_hdmi_v_tc_0_0.vhd" \

vlog -work v_vid_in_axi4s_v5_0_0  -incr -mfcu "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/8664/hdl/v_vid_in_axi4s_v5_0_vl_rfs.v" \

vlog -work xil_defaultlib  -incr -mfcu "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_v_vid_in_axi4s_0_0/sim/ov5640_hdmi_v_vid_in_axi4s_0_0.v" \
"../../../bd/ov5640_hdmi/sim/ov5640_hdmi.v" \

vlog -work axi_protocol_converter_v2_1_25  -incr -mfcu "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/8fe4/hdl/axi_protocol_converter_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -incr -mfcu "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/f0b6/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/66be/hdl/verilog" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/ec67/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/36fa/hdl" "+incdir+../../../../ov5640_hdmi.gen/sources_1/bd/ov5640_hdmi/ipshared/3007/hdl" "+incdir+D:/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../bd/ov5640_hdmi/ip/ov5640_hdmi_auto_pc_0/sim/ov5640_hdmi_auto_pc_0.v" \

vlog -work xil_defaultlib \
"glbl.v"

