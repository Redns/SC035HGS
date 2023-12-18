# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct D:\Project\sc_camera\code\sc_camera_dvp\sc_camera_dvp.vitis\system_wrapper_1\platform.tcl
# 
# OR launch xsct and run below command.
# source D:\Project\sc_camera\code\sc_camera_dvp\sc_camera_dvp.vitis\system_wrapper_1\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {system_wrapper_1}\
-hw {D:\Project\sc_camera\code\sc_camera_dvp\system_wrapper.xsa}\
-out {D:/Project/sc_camera/code/sc_camera_dvp/sc_camera_dvp.vitis}

platform write
domain create -name {freertos10_xilinx_ps7_cortexa9_0} -display-name {freertos10_xilinx_ps7_cortexa9_0} -os {freertos10_xilinx} -proc {ps7_cortexa9_0} -runtime {cpp} -arch {32-bit} -support-app {freertos_lwip_echo_server}
platform generate -domains 
platform active {system_wrapper_1}
domain active {zynq_fsbl}
domain active {freertos10_xilinx_ps7_cortexa9_0}
platform generate -quick
platform generate
bsp reload
bsp config stdin "ps7_coresight_comp_0"
bsp config stdout "ps7_coresight_comp_0"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains freertos10_xilinx_ps7_cortexa9_0 
bsp config dhcp_does_arp_check "false"
bsp config lwip_dhcp "false"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains freertos10_xilinx_ps7_cortexa9_0 
platform generate -domains freertos10_xilinx_ps7_cortexa9_0 
platform generate -domains freertos10_xilinx_ps7_cortexa9_0 
platform generate -domains freertos10_xilinx_ps7_cortexa9_0 
platform config -updatehw {D:/Project/sc_camera/code/sc_camera_dvp/system_wrapper.xsa}
platform generate -domains 
platform config -updatehw {D:/Project/sc_camera/code/sc_camera_dvp/system_wrapper.xsa}
platform generate -domains 
platform config -updatehw {D:/Project/sc_camera/code/sc_camera_dvp/system_wrapper.xsa}
platform generate -domains 
platform config -updatehw {D:/Project/sc_camera/code/sc_camera_dvp/system_wrapper.xsa}
platform generate -domains 
platform generate
platform clean
platform generate
platform generate -domains freertos10_xilinx_ps7_cortexa9_0 
platform generate -domains freertos10_xilinx_ps7_cortexa9_0 
platform generate -domains freertos10_xilinx_ps7_cortexa9_0 
platform generate
