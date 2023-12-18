# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct D:\Project\sc_camera\code\sc_camera_dvp\sc_camera_dvp.vitis\system_wrapper\platform.tcl
# 
# OR launch xsct and run below command.
# source D:\Project\sc_camera\code\sc_camera_dvp\sc_camera_dvp.vitis\system_wrapper\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {system_wrapper}\
-hw {D:\Project\sc_camera\code\sc_camera_dvp\system_wrapper.xsa}\
-out {D:/Project/sc_camera/code/sc_camera_dvp/sc_camera_dvp.vitis}

platform write
domain create -name {standalone_ps7_cortexa9_0} -display-name {standalone_ps7_cortexa9_0} -os {standalone} -proc {ps7_cortexa9_0} -runtime {cpp} -arch {32-bit} -support-app {lwip_echo_server}
platform generate -domains 
platform active {system_wrapper}
domain active {zynq_fsbl}
domain active {standalone_ps7_cortexa9_0}
platform generate -quick
domain active {zynq_fsbl}
bsp reload
bsp reload
domain active {standalone_ps7_cortexa9_0}
bsp reload
bsp config stdin "ps7_coresight_comp_0"
bsp config stdout "ps7_coresight_comp_0"
bsp config dhcp_does_arp_check "false"
bsp config lwip_dhcp "false"
bsp config n_tx_descriptors "64"
bsp config phy_link_speed "CONFIG_LINKSPEED100"
bsp write
bsp reload
catch {bsp regenerate}
platform generate
bsp reload
platform active {system_wrapper}
bsp reload
bsp config phy_link_speed "CONFIG_LINKSPEED_AUTODETECT"
bsp config dhcp_does_arp_check "true"
bsp config lwip_dhcp "true"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_ps7_cortexa9_0 
bsp config tcp_snd_buf "8192"
bsp config tcp_snd_buf "320000"
bsp write
bsp reload
catch {bsp regenerate}
bsp config tcp_snd_buf "8192"
bsp write
bsp reload
catch {bsp regenerate}
platform generate
bsp config n_tx_descriptors "64"
bsp config tcp_snd_buf "81920"
bsp write
bsp reload
catch {bsp regenerate}
bsp config tcp_snd_buf "8192"
bsp write
bsp reload
catch {bsp regenerate}
platform generate
platform generate -domains standalone_ps7_cortexa9_0 
platform write
platform generate -domains standalone_ps7_cortexa9_0 
platform generate -domains standalone_ps7_cortexa9_0,zynq_fsbl 
platform generate
platform generate -domains standalone_ps7_cortexa9_0 
platform generate -domains standalone_ps7_cortexa9_0 
