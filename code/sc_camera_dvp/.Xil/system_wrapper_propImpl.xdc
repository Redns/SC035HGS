set_property SRC_FILE_INFO {cfile:e:/Project/sc_camera/code/sc_camera_dvp/sc_camera_dvp.gen/sources_1/bd/system/ip/system_processing_system7_0_0/system_processing_system7_0_0.xdc rfile:../sc_camera_dvp.gen/sources_1/bd/system/ip/system_processing_system7_0_0/system_processing_system7_0_0.xdc id:1 order:EARLY scoped_inst:system_i/processing_system7_0/inst} [current_design]
set_property SRC_FILE_INFO {cfile:e:/Project/sc_camera/code/sc_camera_dvp/sc_camera_dvp.gen/sources_1/bd/system/ip/system_axi_dma_0_0/system_axi_dma_0_0.xdc rfile:../sc_camera_dvp.gen/sources_1/bd/system/ip/system_axi_dma_0_0/system_axi_dma_0_0.xdc id:2 order:EARLY scoped_inst:system_i/axi_dma_0/U0} [current_design]
set_property SRC_FILE_INFO {cfile:e:/Project/sc_camera/code/sc_camera_dvp/sc_camera_dvp.gen/sources_1/bd/system/ip/system_clk_wiz_0_0/system_clk_wiz_0_0.xdc rfile:../sc_camera_dvp.gen/sources_1/bd/system/ip/system_clk_wiz_0_0/system_clk_wiz_0_0.xdc id:3 order:EARLY scoped_inst:system_i/camera_clk_wiz/inst} [current_design]
set_property SRC_FILE_INFO {cfile:D:/Xilinx/Vivado/2021.2/data/ip/xpm/xpm_cdc/tcl/xpm_cdc_gray.tcl rfile:D:/Xilinx/Vivado/2021.2/data/ip/xpm/xpm_cdc/tcl/xpm_cdc_gray.tcl id:4 order:LATE scoped_inst:system_i/ui_axisbufw_0/inst/xpm_fifo_W_inst/gnuram_async_fifo.xpm_fifo_base_inst/gen_cdc_pntr.wr_pntr_cdc_inst unmanaged:yes} [current_design]
set_property SRC_FILE_INFO {cfile:D:/Xilinx/Vivado/2021.2/data/ip/xpm/xpm_cdc/tcl/xpm_cdc_gray.tcl rfile:D:/Xilinx/Vivado/2021.2/data/ip/xpm/xpm_cdc/tcl/xpm_cdc_gray.tcl id:5 order:LATE scoped_inst:system_i/ui_axisbufw_0/inst/xpm_fifo_W_inst/gnuram_async_fifo.xpm_fifo_base_inst/gen_cdc_pntr.wr_pntr_cdc_dc_inst unmanaged:yes} [current_design]
set_property SRC_FILE_INFO {cfile:D:/Xilinx/Vivado/2021.2/data/ip/xpm/xpm_cdc/tcl/xpm_cdc_gray.tcl rfile:D:/Xilinx/Vivado/2021.2/data/ip/xpm/xpm_cdc/tcl/xpm_cdc_gray.tcl id:6 order:LATE scoped_inst:system_i/ui_axisbufw_0/inst/xpm_fifo_W_inst/gnuram_async_fifo.xpm_fifo_base_inst/gen_cdc_pntr.rd_pntr_cdc_inst unmanaged:yes} [current_design]
set_property SRC_FILE_INFO {cfile:D:/Xilinx/Vivado/2021.2/data/ip/xpm/xpm_cdc/tcl/xpm_cdc_gray.tcl rfile:D:/Xilinx/Vivado/2021.2/data/ip/xpm/xpm_cdc/tcl/xpm_cdc_gray.tcl id:7 order:LATE scoped_inst:system_i/ui_axisbufw_0/inst/xpm_fifo_W_inst/gnuram_async_fifo.xpm_fifo_base_inst/gen_cdc_pntr.rd_pntr_cdc_dc_inst unmanaged:yes} [current_design]
current_instance system_i/processing_system7_0/inst
set_property src_info {type:SCOPED_XDC file:1 line:21 export:INPUT save:INPUT read:READ} [current_design]
set_input_jitter clk_fpga_0 0.3
current_instance
current_instance system_i/axi_dma_0/U0
set_property src_info {type:SCOPED_XDC file:2 line:52 export:INPUT save:INPUT read:READ} [current_design]
create_waiver -internal -scope -type CDC -id {CDC-1} -user "axi_dma" -tags "9601" -desc "The CDC-1 warning is waived as it is safe in the context of AXI DMA. The Address and Data value does not change until AXI transaction is complete." -to [get_pins -hier -quiet -filter {NAME =~*I_AXI_DMA_REG_MODULE/GEN_AXI_LITE_IF.AXI_LITE_IF_I/GEN_ASYNC_WRITE.REG_WADDR_TO_IPCLK/GENERATE_LEVEL_P_S_CDC.MULTI_BIT.FOR_IN_cdc_to[*].CROSS2_PLEVEL_IN2SCNDRY_IN_cdc_to/D}]
set_property src_info {type:SCOPED_XDC file:2 line:56 export:INPUT save:INPUT read:READ} [current_design]
create_waiver -internal -scope -type CDC -id {CDC-1} -user "axi_dma" -tags "9601" -desc "The CDC-1 warning is waived as it is safe in the context of AXI DMA. The Address and Data value does not change until AXI transaction is complete." -to [get_pins -hier -quiet -filter {NAME =~*I_AXI_DMA_REG_MODULE/GEN_AXI_LITE_IF.AXI_LITE_IF_I/GEN_ASYNC_WRITE.REG_WADDR_TO_IPCLK1/GENERATE_LEVEL_P_S_CDC.MULTI_BIT.FOR_IN_cdc_to[*].CROSS2_PLEVEL_IN2SCNDRY_IN_cdc_to/D}]
set_property src_info {type:SCOPED_XDC file:2 line:61 export:INPUT save:INPUT read:READ} [current_design]
create_waiver -internal -scope -type CDC -id {CDC-1} -user "axi_dma" -tags "9601" -desc "The CDC-1 warning is waived as it is safe in the context of AXI DMA. In multi channel mode, it is safe to ignore this." -from [get_pins -hier -quiet -filter {NAME =~*MM2S_SPLIT.I_COMMAND_MM2S_SPLITTER/vsize_data_int_reg[*]/C}]
current_instance
current_instance system_i/camera_clk_wiz/inst
set_property src_info {type:SCOPED_XDC file:3 line:57 export:INPUT save:INPUT read:READ} [current_design]
set_input_jitter [get_clocks -of_objects [get_ports clk_in1_p]] 0.050
current_instance
current_instance system_i/ui_axisbufw_0/inst/xpm_fifo_W_inst/gnuram_async_fifo.xpm_fifo_base_inst/gen_cdc_pntr.wr_pntr_cdc_inst
set_property src_info {type:SCOPED_XDC file:4 line:23 export:INPUT save:NONE read:READ} [current_design]
create_waiver -internal -scoped -type CDC -id {CDC-6} -user "xpm_cdc" -tags "1009444" -desc "The CDC-6 warning is waived as it is safe in the context of XPM_CDC_GRAY." -from [get_pins -quiet {src_gray_ff_reg*/C}] -to [get_pins -quiet {dest_graysync_ff_reg*/D}]
current_instance
current_instance system_i/ui_axisbufw_0/inst/xpm_fifo_W_inst/gnuram_async_fifo.xpm_fifo_base_inst/gen_cdc_pntr.wr_pntr_cdc_dc_inst
set_property src_info {type:SCOPED_XDC file:5 line:23 export:INPUT save:NONE read:READ} [current_design]
create_waiver -internal -scoped -type CDC -id {CDC-6} -user "xpm_cdc" -tags "1009444" -desc "The CDC-6 warning is waived as it is safe in the context of XPM_CDC_GRAY." -from [get_pins -quiet {src_gray_ff_reg*/C}] -to [get_pins -quiet {dest_graysync_ff_reg*/D}]
current_instance
current_instance system_i/ui_axisbufw_0/inst/xpm_fifo_W_inst/gnuram_async_fifo.xpm_fifo_base_inst/gen_cdc_pntr.rd_pntr_cdc_inst
set_property src_info {type:SCOPED_XDC file:6 line:23 export:INPUT save:NONE read:READ} [current_design]
create_waiver -internal -scoped -type CDC -id {CDC-6} -user "xpm_cdc" -tags "1009444" -desc "The CDC-6 warning is waived as it is safe in the context of XPM_CDC_GRAY." -from [get_pins -quiet {src_gray_ff_reg*/C}] -to [get_pins -quiet {dest_graysync_ff_reg*/D}]
current_instance
current_instance system_i/ui_axisbufw_0/inst/xpm_fifo_W_inst/gnuram_async_fifo.xpm_fifo_base_inst/gen_cdc_pntr.rd_pntr_cdc_dc_inst
set_property src_info {type:SCOPED_XDC file:7 line:23 export:INPUT save:NONE read:READ} [current_design]
create_waiver -internal -scoped -type CDC -id {CDC-6} -user "xpm_cdc" -tags "1009444" -desc "The CDC-6 warning is waived as it is safe in the context of XPM_CDC_GRAY." -from [get_pins -quiet {src_gray_ff_reg*/C}] -to [get_pins -quiet {dest_graysync_ff_reg*/D}]
