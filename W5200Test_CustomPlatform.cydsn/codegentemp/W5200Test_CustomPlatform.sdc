# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\chuck.erhardt\Documents\GitHub\PSoC-W5100-Driver\W5200Test_CustomPlatform.cydsn\W5200Test_CustomPlatform.cyprj
# Date: Fri, 22 Aug 2014 19:59:25 GMT
#set_units -time ns
create_clock -name {CyIMO} -period 333.33333333333331 -waveform {0 166.666666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 15.151515151515152 -waveform {0 7.57575757575758} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyILO} -period 1000000 -waveform {0 500000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyMASTER_CLK} -period 15.151515151515152 -waveform {0 7.57575757575758} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {SPI_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 5 9} [list [get_pins {ClockBlock/dclk_glb_0}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]

set_false_path -from [get_pins {__ONE__/q}]

# Component constraints for C:\Users\chuck.erhardt\Documents\GitHub\PSoC-W5100-Driver\W5200Test_CustomPlatform.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\chuck.erhardt\Documents\GitHub\PSoC-W5100-Driver\W5200Test_CustomPlatform.cydsn\W5200Test_CustomPlatform.cyprj
# Date: Fri, 22 Aug 2014 19:59:15 GMT
