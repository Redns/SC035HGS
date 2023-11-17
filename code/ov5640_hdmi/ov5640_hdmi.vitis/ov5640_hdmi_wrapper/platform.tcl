# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct E:\Project\sc_camera\code\20220731ygACd6Xc\ov5640_hdmi_1_3\ov5640_hdmi.vitis\ov5640_hdmi_wrapper\platform.tcl
# 
# OR launch xsct and run below command.
# source E:\Project\sc_camera\code\20220731ygACd6Xc\ov5640_hdmi_1_3\ov5640_hdmi.vitis\ov5640_hdmi_wrapper\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {ov5640_hdmi_wrapper}\
-hw {E:\Project\sc_camera\code\20220731ygACd6Xc\ov5640_hdmi_1_3\ov5640_hdmi_wrapper.xsa}\
-out {E:/Project/sc_camera/code/20220731ygACd6Xc/ov5640_hdmi_1_3/ov5640_hdmi.vitis}

platform write
domain create -name {standalone_ps7_cortexa9_0} -display-name {standalone_ps7_cortexa9_0} -os {standalone} -proc {ps7_cortexa9_0} -runtime {cpp} -arch {32-bit} -support-app {hello_world}
platform generate -domains 
platform active {ov5640_hdmi_wrapper}
domain active {zynq_fsbl}
domain active {standalone_ps7_cortexa9_0}
platform generate -quick
platform generate
platform clean
platform generate
platform active {ov5640_hdmi_wrapper}
domain active {zynq_fsbl}
bsp reload
bsp config stdin "ps7_coresight_comp_0"
bsp config stdout "ps7_coresight_comp_0"
bsp config stdout "ps7_coresight_comp_0"
bsp write
bsp reload
catch {bsp regenerate}
platform generate
platform active {ov5640_hdmi_wrapper}
platform config -updatehw {E:/Project/sc_camera/code/20220731ygACd6Xc/ov5640_hdmi_1_3/ov5640_hdmi_wrapper.xsa}
platform generate -domains 
platform config -updatehw {E:/Project/sc_camera/code/20220731ygACd6Xc/ov5640_hdmi_1_3/ov5640_hdmi_wrapper.xsa}
platform generate -domains 
