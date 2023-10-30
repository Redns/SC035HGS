# Definitional proc to organize widgets for parameters.
proc init_gui { IPINST } {
  ipgui::add_param $IPINST -name "Component_Name"
  #Adding Page
  set Page_0 [ipgui::add_page $IPINST -name "Page 0"]
  ipgui::add_param $IPINST -name "VIDEO_ENABLE" -parent ${Page_0}
  ipgui::add_param $IPINST -name "AXI_DATA_WIDTH" -parent ${Page_0}
  ipgui::add_param $IPINST -name "W_BUFDEPTH" -parent ${Page_0}
  ipgui::add_param $IPINST -name "W_DATAWIDTH" -parent ${Page_0}
  ipgui::add_param $IPINST -name "W_XSIZE" -parent ${Page_0}
  ipgui::add_param $IPINST -name "W_YSIZE" -parent ${Page_0}


}

proc update_PARAM_VALUE.AXI_DATA_WIDTH { PARAM_VALUE.AXI_DATA_WIDTH } {
	# Procedure called to update AXI_DATA_WIDTH when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.AXI_DATA_WIDTH { PARAM_VALUE.AXI_DATA_WIDTH } {
	# Procedure called to validate AXI_DATA_WIDTH
	return true
}

proc update_PARAM_VALUE.VIDEO_ENABLE { PARAM_VALUE.VIDEO_ENABLE } {
	# Procedure called to update VIDEO_ENABLE when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.VIDEO_ENABLE { PARAM_VALUE.VIDEO_ENABLE } {
	# Procedure called to validate VIDEO_ENABLE
	return true
}

proc update_PARAM_VALUE.W_BUFDEPTH { PARAM_VALUE.W_BUFDEPTH } {
	# Procedure called to update W_BUFDEPTH when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.W_BUFDEPTH { PARAM_VALUE.W_BUFDEPTH } {
	# Procedure called to validate W_BUFDEPTH
	return true
}

proc update_PARAM_VALUE.W_DATAWIDTH { PARAM_VALUE.W_DATAWIDTH } {
	# Procedure called to update W_DATAWIDTH when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.W_DATAWIDTH { PARAM_VALUE.W_DATAWIDTH } {
	# Procedure called to validate W_DATAWIDTH
	return true
}

proc update_PARAM_VALUE.W_XSIZE { PARAM_VALUE.W_XSIZE } {
	# Procedure called to update W_XSIZE when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.W_XSIZE { PARAM_VALUE.W_XSIZE } {
	# Procedure called to validate W_XSIZE
	return true
}

proc update_PARAM_VALUE.W_YSIZE { PARAM_VALUE.W_YSIZE } {
	# Procedure called to update W_YSIZE when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.W_YSIZE { PARAM_VALUE.W_YSIZE } {
	# Procedure called to validate W_YSIZE
	return true
}


proc update_MODELPARAM_VALUE.VIDEO_ENABLE { MODELPARAM_VALUE.VIDEO_ENABLE PARAM_VALUE.VIDEO_ENABLE } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.VIDEO_ENABLE}] ${MODELPARAM_VALUE.VIDEO_ENABLE}
}

proc update_MODELPARAM_VALUE.AXI_DATA_WIDTH { MODELPARAM_VALUE.AXI_DATA_WIDTH PARAM_VALUE.AXI_DATA_WIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.AXI_DATA_WIDTH}] ${MODELPARAM_VALUE.AXI_DATA_WIDTH}
}

proc update_MODELPARAM_VALUE.W_BUFDEPTH { MODELPARAM_VALUE.W_BUFDEPTH PARAM_VALUE.W_BUFDEPTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.W_BUFDEPTH}] ${MODELPARAM_VALUE.W_BUFDEPTH}
}

proc update_MODELPARAM_VALUE.W_DATAWIDTH { MODELPARAM_VALUE.W_DATAWIDTH PARAM_VALUE.W_DATAWIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.W_DATAWIDTH}] ${MODELPARAM_VALUE.W_DATAWIDTH}
}

proc update_MODELPARAM_VALUE.W_XSIZE { MODELPARAM_VALUE.W_XSIZE PARAM_VALUE.W_XSIZE } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.W_XSIZE}] ${MODELPARAM_VALUE.W_XSIZE}
}

proc update_MODELPARAM_VALUE.W_YSIZE { MODELPARAM_VALUE.W_YSIZE PARAM_VALUE.W_YSIZE } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.W_YSIZE}] ${MODELPARAM_VALUE.W_YSIZE}
}

