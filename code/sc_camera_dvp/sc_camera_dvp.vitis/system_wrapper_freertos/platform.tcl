# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct D:\Project\sc_camera\code\sc_camera_dvp\sc_camera_dvp.vitis\system_wrapper_freertos\platform.tcl
# 
# OR launch xsct and run below command.
# source D:\Project\sc_camera\code\sc_camera_dvp\sc_camera_dvp.vitis\system_wrapper_freertos\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {system_wrapper_freertos}\
-hw {D:\Project\sc_camera\code\sc_camera_dvp\system_wrapper.xsa}\
-out {D:/Project/sc_camera/code/sc_camera_dvp/sc_camera_dvp.vitis}

platform write
domain create -name {freertos10_xilinx_ps7_cortexa9_0} -display-name {freertos10_xilinx_ps7_cortexa9_0} -os {freertos10_xilinx} -proc {ps7_cortexa9_0} -runtime {cpp} -arch {32-bit} -support-app {freertos_lwip_echo_server}
platform generate -domains 
platform active {system_wrapper_freertos}
domain active {zynq_fsbl}
domain active {freertos10_xilinx_ps7_cortexa9_0}
platform generate -quick
bsp reload
bsp config dhcp_does_arp_check "false"
bsp config lwip_dhcp "false"
bsp write
bsp reload
catch {bsp regenerate}
platform generate
bsp config stdin "ps7_coresight_comp_0"
bsp config stdout "ps7_coresight_comp_0"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains freertos10_xilinx_ps7_cortexa9_0 
catch {platform remove system_wrapper_1}
platform clean
platform generate
platform generate
platform active {system_wrapper_freertos}
bsp reload
domain active {zynq_fsbl}
bsp reload
domain active {freertos10_xilinx_ps7_cortexa9_0}
bsp config stdin "ps7_coresight_comp_0"
bsp reload
platform generate -domains 
bsp config tcp_snd_buf "8192"
bsp config tcp_queue_ooseq "1"
bsp config tcp_snd_buf "307200"
bsp write
bsp reload
catch {bsp regenerate}
bsp config mem_size "307200"
bsp config tcp_snd_buf "8192"
bsp write
bsp reload
catch {bsp regenerate}
platform generate
bsp config memp_n_pbuf "1024"
bsp config mem_size "409600"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains freertos10_xilinx_ps7_cortexa9_0 
bsp config mem_size "131072"
bsp config memp_n_pbuf "128"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains freertos10_xilinx_ps7_cortexa9_0 
bsp config tcp_snd_buf "65536"
bsp write
bsp reload
catch {bsp regenerate}
bsp config tcp_snd_buf "16384"
bsp write
bsp reload
catch {bsp regenerate}
platform generate
bsp config tcp_snd_buf "32768"
bsp write
bsp reload
catch {bsp regenerate}
platform generate
bsp reload
bsp config memp_n_tcp_seg "512"
bsp config tcp_snd_buf "16384"
bsp write
bsp reload
catch {bsp regenerate}
platform generate
bsp config pbuf_pool_size "4096"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains freertos10_xilinx_ps7_cortexa9_0 
platform clean
platform generate
platform clean
platform generate
platform clean
platform clean
platform generate
platform clean
platform generate
platform generate -domains freertos10_xilinx_ps7_cortexa9_0 
platform generate -domains freertos10_xilinx_ps7_cortexa9_0 
platform config -updatehw {D:/Project/sc_camera/code/sc_camera_dvp/system_wrapper.xsa}
platform generate -domains 
platform clean
platform generate
platform generate -domains freertos10_xilinx_ps7_cortexa9_0 
platform write
platform active {system_wrapper_freertos}
domain active {freertos10_xilinx_ps7_cortexa9_0}
bsp reload
platform active {system_wrapper_freertos}
domain active {zynq_fsbl}
bsp reload
platform active {system_wrapper_freertos}
bsp reload
domain active {zynq_fsbl}
bsp reload
