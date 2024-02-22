transcript off
onbreak {quit -force}
onerror {quit -force}
transcript on

asim +access +r +m+bd_system  -L xilinx_vip -L xpm -L xil_defaultlib -L xlconstant_v1_1_8 -L lib_cdc_v1_0_2 -L proc_sys_reset_v5_0_14 -L smartconnect_v1_0 -L axi_infrastructure_v1_1_0 -L axi_register_slice_v2_1_29 -L axi_vip_v1_1_15 -L lib_pkg_v1_0_3 -L fifo_generator_v13_2_9 -L lib_fifo_v1_0_18 -L blk_mem_gen_v8_4_7 -L lib_bmg_v1_0_16 -L lib_srl_fifo_v1_0_3 -L axi_datamover_v5_1_31 -L axi_vdma_v6_3_17 -L processing_system7_vip_v1_0_17 -L generic_baseblocks_v2_1_1 -L axi_data_fifo_v2_1_28 -L axi_crossbar_v2_1_30 -L axi_lite_ipif_v3_0_4 -L v_tc_v6_1_13 -L v_vid_in_axi4s_v4_0_11 -L v_axi4s_vid_out_v4_0_17 -L v_tc_v6_2_7 -L v_vid_in_axi4s_v5_0_3 -L interrupt_control_v3_1_5 -L axi_gpio_v2_0_31 -L axi_protocol_converter_v2_1_29 -L xilinx_vip -L unisims_ver -L unimacro_ver -L secureip -O5 xil_defaultlib.bd_system xil_defaultlib.glbl

do {bd_system.udo}

run 1000ns

endsim

quit -force
