# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct D:\Project\sc_camera\code\sc035hgs_hdmi\sc035hgs_hdmi.vitis\sc035hgs_hdmi_wrapper\platform.tcl
# 
# OR launch xsct and run below command.
# source D:\Project\sc_camera\code\sc035hgs_hdmi\sc035hgs_hdmi.vitis\sc035hgs_hdmi_wrapper\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {sc035hgs_hdmi_wrapper}\
-hw {D:\Project\sc_camera\code\sc035hgs_hdmi\sc035hgs_hdmi_wrapper.xsa}\
-out {D:/Project/sc_camera/code/sc035hgs_hdmi/sc035hgs_hdmi.vitis}

platform write
domain create -name {standalone_ps7_cortexa9_0} -display-name {standalone_ps7_cortexa9_0} -os {standalone} -proc {ps7_cortexa9_0} -runtime {cpp} -arch {32-bit} -support-app {hello_world}
platform generate -domains 
platform active {sc035hgs_hdmi_wrapper}
domain active {zynq_fsbl}
domain active {standalone_ps7_cortexa9_0}
platform generate -quick
platform generate
platform config -updatehw {D:/Project/sc_camera/code/sc035hgs_hdmi/sc035hgs_hdmi_wrapper.xsa}
platform generate -domains 
