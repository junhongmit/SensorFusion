connect -url tcp:127.0.0.1:3121
source /home/junhonglin/Xilinx/STsensorhub/sdk_arduino_IKS01A1/base_hw_platform_0/ps7_init.tcl
targets -set -nocase -filter {name =~"APU*" && jtag_cable_name =~ "Xilinx TUL 1234-tulA"} -index 0
loadhw -hw /home/junhonglin/Xilinx/STsensorhub/sdk_arduino_IKS01A1/base_hw_platform_0/system.hdf -mem-ranges [list {0x40000000 0xbfffffff}]
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*" && jtag_cable_name =~ "Xilinx TUL 1234-tulA"} -index 0
stop
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "microblaze*#2" && bscan=="USER2"  && jtag_cable_name =~ "Xilinx TUL 1234-tulA"} -index 1
rst -processor
targets -set -nocase -filter {name =~ "microblaze*#2" && bscan=="USER2"  && jtag_cable_name =~ "Xilinx TUL 1234-tulA"} -index 1
dow /home/junhonglin/Xilinx/STsensorhub/sdk_arduino_IKS01A1/IKS01A1_test/Debug/IKS01A1_test.elf
configparams force-mem-access 0
bpadd -addr &main
