# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: E:\Project\sc_camera\code\20220731ygACd6Xc\ov5640_hdmi_1_3\ov5640_hdmi.vitis\ov5640_to_hdmi_system\_ide\scripts\debugger_ov5640_to_hdmi-default.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source E:\Project\sc_camera\code\20220731ygACd6Xc\ov5640_hdmi_1_3\ov5640_hdmi.vitis\ov5640_to_hdmi_system\_ide\scripts\debugger_ov5640_to_hdmi-default.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -filter {jtag_cable_name =~ "Digilent JTAG-SMT2 210251A08870" && level==0 && jtag_device_ctx=="jsn-JTAG-SMT2-210251A08870-13722093-0"}
fpga -file E:/Project/sc_camera/code/20220731ygACd6Xc/ov5640_hdmi_1_3/ov5640_hdmi.vitis/ov5640_to_hdmi/_ide/bitstream/ov5640_hdmi_wrapper.bit
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw E:/Project/sc_camera/code/20220731ygACd6Xc/ov5640_hdmi_1_3/ov5640_hdmi.vitis/ov5640_hdmi_wrapper/export/ov5640_hdmi_wrapper/hw/ov5640_hdmi_wrapper.xsa -mem-ranges [list {0x40000000 0xbfffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
source E:/Project/sc_camera/code/20220731ygACd6Xc/ov5640_hdmi_1_3/ov5640_hdmi.vitis/ov5640_to_hdmi/_ide/psinit/ps7_init.tcl
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "*A9*#0"}
dow E:/Project/sc_camera/code/20220731ygACd6Xc/ov5640_hdmi_1_3/ov5640_hdmi.vitis/ov5640_to_hdmi/Debug/ov5640_to_hdmi.elf
configparams force-mem-access 0
bpadd -addr &main
