onbreak {quit -f}
onerror {quit -f}

vsim -lib xil_defaultlib ov5640_hdmi_opt

set NumericStdNoWarnings 1
set StdArithNoWarnings 1

do {wave.do}

view wave
view structure
view signals

do {ov5640_hdmi.udo}

run -all

quit -force
