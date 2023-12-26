# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct D:\Project\sc_camera\code\sc_camera_dvp\sc_camera_dvp.vitis\system_wrapper_standalone\platform.tcl
# 
# OR launch xsct and run below command.
# source D:\Project\sc_camera\code\sc_camera_dvp\sc_camera_dvp.vitis\system_wrapper_standalone\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {system_wrapper_standalone}\
-hw {D:\Project\sc_camera\code\sc_camera_dvp\system_wrapper.xsa}\
-out {D:/Project/sc_camera/code/sc_camera_dvp/sc_camera_dvp.vitis}

platform write
domain create -name {standalone_ps7_cortexa9_0} -display-name {standalone_ps7_cortexa9_0} -os {standalone} -proc {ps7_cortexa9_0} -runtime {cpp} -arch {32-bit} -support-app {lwip_echo_server}
platform generate -domains 
platform active {system_wrapper_standalone}
domain active {zynq_fsbl}
domain active {standalone_ps7_cortexa9_0}
platform generate -quick
domain active {zynq_fsbl}
bsp reload
bsp config stdin "ps7_coresight_comp_0"
bsp config stdout "ps7_coresight_comp_0"
bsp write
bsp reload
catch {bsp regenerate}
domain active {standalone_ps7_cortexa9_0}
bsp reload
bsp config dhcp_does_arp_check "false"
bsp config lwip_dhcp "false"
bsp write
bsp reload
catch {bsp regenerate}
platform active {system_wrapper_standalone}
bsp reload
bsp config stdin "ps7_coresight_comp_0"
bsp config stdout "ps7_coresight_comp_0"
bsp write
bsp reload
catch {bsp regenerate}
platform generate
bsp write
platform generate -domains 
platform clean
platform generate
platform clean
platform generate
platform active {system_wrapper_standalone}
bsp reload
bsp config tcp_snd_buf "32768"
bsp write
bsp reload
catch {bsp regenerate}
bsp config memp_n_tcp_seg "512"
bsp write
bsp reload
catch {bsp regenerate}
platform generate
bsp reload
bsp config tcp_snd_buf "65536"
bsp write
bsp reload
catch {bsp regenerate}
bsp config memp_n_tcp_seg "1024"
bsp write
bsp reload
catch {bsp regenerate}
platform generate
bsp config memp_n_pbuf "16"
bsp config memp_n_tcp_seg "512"
bsp config memp_n_pbuf "32"
bsp write
bsp reload
catch {bsp regenerate}
bsp config tcp_snd_buf "32768"
bsp write
bsp reload
catch {bsp regenerate}
platform generate
bsp config tcp_snd_buf "65536"
bsp config memp_n_tcp_seg "1024"
bsp config memp_n_pbuf "64"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_ps7_cortexa9_0 
bsp config mem_size "524288"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_ps7_cortexa9_0 
bsp config mem_size "524288"
bsp config memp_n_pbuf "512"
bsp config memp_n_tcp_seg "2048"
bsp config pbuf_pool_size "4096"
bsp config tcp_snd_buf "131072"
bsp write
bsp reload
catch {bsp regenerate}
bsp config mem_size "131072"
bsp config memp_n_pbuf "16"
bsp config memp_n_tcp_seg "156"
bsp config memp_n_tcp_seg "256"
bsp config pbuf_pool_size "256"
bsp config tcp_snd_buf "32768"
bsp write
bsp reload
catch {bsp regenerate}
bsp config memp_n_tcp_seg "512"
bsp write
bsp reload
catch {bsp regenerate}
platform generate
bsp reload
platform generate -domains standalone_ps7_cortexa9_0 
bsp reload
bsp config tcp_snd_buf "65536"
bsp write
bsp reload
catch {bsp regenerate}
bsp config memp_n_tcp_seg "1024"
bsp write
bsp reload
catch {bsp regenerate}
platform generate
bsp config tcp_snd_buf "32768"
bsp config memp_n_tcp_seg "512"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_ps7_cortexa9_0 
bsp reload
bsp config tcp_snd_buf "32768"
bsp config tcp_snd_buf "65536"
bsp config tcp_wnd "2048"
bsp config memp_n_tcp_seg "1024"
bsp config memp_n_pbuf "128"
bsp config tcp_wnd "4096"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_ps7_cortexa9_0 
bsp config tcp_snd_buf "32768"
bsp config memp_n_tcp_seg "512"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_ps7_cortexa9_0 
bsp config tcp_wnd "2048"
bsp config tcp_snd_buf "65536"
bsp write
bsp reload
catch {bsp regenerate}
bsp config memp_n_pbuf "16"
bsp config memp_n_tcp_seg "1024"
bsp write
bsp reload
catch {bsp regenerate}
platform generate
bsp config tcp_snd_buf "32768"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_ps7_cortexa9_0 
platform active {system_wrapper_standalone}
bsp reload
bsp config tcp_queue_ooseq "1"
bsp config tcp_snd_buf "524288"
bsp write
bsp reload
catch {bsp regenerate}
bsp config tcp_snd_buf "61440"
bsp write
bsp reload
catch {bsp regenerate}
platform generate
bsp config tcp_snd_buf "32768"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_ps7_cortexa9_0 
bsp reload
bsp config mem_size "524288"
bsp config memp_n_pbuf "2048"
bsp config memp_n_tcp_pcb "1024"
bsp config pbuf_pool_size "4096"
bsp config tcp_snd_buf "65535"
bsp config tcp_wnd "65535"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_ps7_cortexa9_0 
platform generate -domains standalone_ps7_cortexa9_0 
bsp config n_rx_descriptors "256"
bsp config n_tx_descriptors "256"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_ps7_cortexa9_0 
platform generate -domains standalone_ps7_cortexa9_0 
platform config -updatehw {D:/Project/sc_camera/code/sc_camera_dvp/system_wrapper.xsa}
platform generate -domains 
catch {platform remove system_wrapper_freertos}
platform config -updatehw {D:/Project/sc_camera/code/sc_camera_dvp/system_wrapper.xsa}
platform generate -domains 
platform config -updatehw {D:/Project/sc_camera/code/sc_camera_dvp/system_wrapper.xsa}
platform generate -domains 
platform config -updatehw {D:/Project/sc_camera/code/sc_camera_dvp/system_wrapper.xsa}
platform generate -domains 
platform config -updatehw {D:/Project/sc_camera/code/sc_camera_dvp/system_wrapper.xsa}
platform generate -domains 
platform generate -domains standalone_ps7_cortexa9_0 
platform generate -domains standalone_ps7_cortexa9_0 
platform generate -domains standalone_ps7_cortexa9_0 
platform generate -domains standalone_ps7_cortexa9_0 
platform generate -domains standalone_ps7_cortexa9_0 
platform generate -domains standalone_ps7_cortexa9_0 
bsp reload
bsp config tcp_wnd "2048"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_ps7_cortexa9_0 
bsp write
bsp config phy_link_speed "CONFIG_LINKSPEED100"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_ps7_cortexa9_0 
bsp config phy_link_speed "CONFIG_LINKSPEED_AUTODETECT"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_ps7_cortexa9_0 
bsp config emac_number "0"
bsp config mem_size "1048576"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_ps7_cortexa9_0 
bsp config mem_size "640000"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_ps7_cortexa9_0 
bsp config mem_size "131072"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_ps7_cortexa9_0 
bsp config mem_size "262144"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_ps7_cortexa9_0 
bsp reload
bsp config mem_size "786432"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_ps7_cortexa9_0 
bsp config tcp_snd_buf "8192"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_ps7_cortexa9_0 
bsp config tcp_snd_buf "32768"
bsp reload
bsp config mem_size "524288"
bsp config tcp_snd_buf "16384"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_ps7_cortexa9_0 
