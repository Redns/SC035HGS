# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: E:\Project\sc_camera\code\sc_camera_dvp\sc_camera_dvp.vitis\sc_camera_dvp_system\_ide\scripts\sc_camera_dvp.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source E:\Project\sc_camera\code\sc_camera_dvp\sc_camera_dvp.vitis\sc_camera_dvp_system\_ide\scripts\sc_camera_dvp.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -filter {jtag_cable_name =~ "Digilent JTAG-SMT2 210251878083" && level==0 && jtag_device_ctx=="jsn-JTAG-SMT2-210251878083-03736093-0"}
fpga -file E:/Project/sc_camera/code/sc_camera_dvp/sc_camera_dvp.vitis/sc_camera_dvp/_ide/bitstream/system_wrapper.bit
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw E:/Project/sc_camera/code/sc_camera_dvp/sc_camera_dvp.vitis/system_wrapper/export/system_wrapper/hw/system_wrapper.xsa -mem-ranges [list {0x40000000 0xbfffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
stop
source E:/Project/sc_camera/code/sc_camera_dvp/sc_camera_dvp.vitis/sc_camera_dvp/_ide/psinit/ps7_init.tcl
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "*A9*#0"}
rst -processor
targets -set -nocase -filter {name =~ "*A9*#0"}
dow E:/Project/sc_camera/code/sc_camera_dvp/sc_camera_dvp.vitis/sc_camera_dvp/Debug/sc_camera_dvp.elf
configparams force-mem-access 0
bpadd -addr &main
