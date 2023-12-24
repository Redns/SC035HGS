# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: D:\Project\sc_camera\code\sc_camera_dvp\sc_camera_dvp.vitis\lwip_echo_system\_ide\scripts\debugger_lwip_echo-default.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source D:\Project\sc_camera\code\sc_camera_dvp\sc_camera_dvp.vitis\lwip_echo_system\_ide\scripts\debugger_lwip_echo-default.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -filter {jtag_cable_name =~ "Digilent JTAG-SMT2 210251878083" && level==0 && jtag_device_ctx=="jsn-JTAG-SMT2-210251878083-03736093-0"}
fpga -file D:/Project/sc_camera/code/sc_camera_dvp/sc_camera_dvp.vitis/lwip_echo/_ide/bitstream/system_wrapper.bit
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw D:/Project/sc_camera/code/sc_camera_dvp/sc_camera_dvp.vitis/system_wrapper_freertos/export/system_wrapper_freertos/hw/system_wrapper.xsa -mem-ranges [list {0x40000000 0xbfffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
source D:/Project/sc_camera/code/sc_camera_dvp/sc_camera_dvp.vitis/lwip_echo/_ide/psinit/ps7_init.tcl
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "*A9*#0"}
dow D:/Project/sc_camera/code/sc_camera_dvp/sc_camera_dvp.vitis/lwip_echo/Debug/lwip_echo.elf
configparams force-mem-access 0
targets -set -nocase -filter {name =~ "*A9*#0"}
con
