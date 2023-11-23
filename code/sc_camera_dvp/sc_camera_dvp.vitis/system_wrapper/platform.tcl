# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct E:\Project\sc_camera\code\sc_camera_dvp\sc_camera_dvp.vitis\system_wrapper\platform.tcl
# 
# OR launch xsct and run below command.
# source E:\Project\sc_camera\code\sc_camera_dvp\sc_camera_dvp.vitis\system_wrapper\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {system_wrapper}\
-hw {E:\Project\sc_camera\code\sc_camera_dvp\system_wrapper.xsa}\
-out {E:/Project/sc_camera/code/sc_camera_dvp/sc_camera_dvp.vitis}

platform write
domain create -name {standalone_ps7_cortexa9_0} -display-name {standalone_ps7_cortexa9_0} -os {standalone} -proc {ps7_cortexa9_0} -runtime {cpp} -arch {32-bit} -support-app {lwip_tcp_perf_client}
platform generate -domains 
platform active {system_wrapper}
domain active {zynq_fsbl}
domain active {standalone_ps7_cortexa9_0}
platform generate -quick
platform generate
platform active {system_wrapper}
platform config -updatehw {E:/Project/sc_camera/code/sc_camera_dvp/system_wrapper.xsa}
platform generate -domains 
platform active {system_wrapper}
domain active {zynq_fsbl}
domain active {standalone_ps7_cortexa9_0}
bsp reload
bsp reload
bsp config stdin "ps7_coresight_comp_0"
bsp config stdout "ps7_coresight_comp_0"
bsp config dhcp_does_arp_check "false"
bsp config lwip_dhcp "false"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_ps7_cortexa9_0,zynq_fsbl 
platform active {system_wrapper}
platform generate -domains 
platform active {system_wrapper}
platform config -updatehw {E:/Project/sc_camera/code/sc_camera_dvp/system_wrapper.xsa}
platform generate -domains 
domain active {zynq_fsbl}
domain active {standalone_ps7_cortexa9_0}
bsp reload
bsp reload
platform generate -domains 
platform config -updatehw {E:/Project/sc_camera/code/sc_camera_dvp/system_wrapper.xsa}
platform generate -domains 
bsp reload
platform config -updatehw {E:/Project/sc_camera/code/sc_camera_dvp/system_wrapper.xsa}
platform generate -domains 
bsp reload
bsp reload
platform config -updatehw {E:/Project/sc_camera/code/sc_camera_dvp/system_wrapper.xsa}
platform generate -domains 
platform config -updatehw {E:/Project/sc_camera/code/sc_camera_dvp/system_wrapper.xsa}
platform generate -domains 
platform config -updatehw {E:/Project/sc_camera/code/sc_camera_dvp/system_wrapper.xsa}
platform generate -domains 
platform config -updatehw {E:/Project/sc_camera/code/sc_camera_dvp/system_wrapper.xsa}
platform generate -domains 
bsp reload
domain active {zynq_fsbl}
bsp reload
domain active {standalone_ps7_cortexa9_0}
platform active {system_wrapper}
domain active {zynq_fsbl}
bsp reload
bsp reload
domain active {standalone_ps7_cortexa9_0}
bsp reload
bsp reload
bsp reload
bsp config stdin "ps7_coresight_comp_0"
bsp config stdin "ps7_coresight_comp_0"
bsp reload
platform generate -domains 
platform active {system_wrapper}
platform config -updatehw {E:/Project/sc_camera/code/sc_camera_dvp/system_wrapper.xsa}
platform generate -domains 
platform active {system_wrapper}
platform config -updatehw {E:/Project/sc_camera/code/sc_camera_dvp/system_wrapper.xsa}
platform generate -domains standalone_ps7_cortexa9_0,zynq_fsbl 
platform active {system_wrapper}
platform config -updatehw {E:/Project/sc_camera/code/sc_camera_dvp/system_wrapper.xsa}
platform generate
platform config -updatehw {E:/Project/sc_camera/code/sc_camera_dvp/system_wrapper.xsa}
platform generate -domains 
platform clean
platform generate
platform active {system_wrapper}
platform config -updatehw {E:/Project/sc_camera/code/sc_camera_dvp/system_wrapper.xsa}
platform generate
platform clean
platform generate
domain active {zynq_fsbl}
bsp reload
platform generate -domains 
domain active {standalone_ps7_cortexa9_0}
bsp reload
platform clean
platform clean
platform clean
platform generate
platform active {system_wrapper}
platform config -updatehw {E:/Project/sc_camera/code/sc_camera_dvp/system_wrapper_with_ila.xsa}
platform generate -domains 
platform active {system_wrapper}
platform config -updatehw {E:/Project/sc_camera/code/sc_camera_dvp/system_wrapper_with_ila.xsa}
platform generate -domains 
platform config -updatehw {E:/Project/sc_camera/code/sc_camera_dvp/system_wrapper_with_ila.xsa}
