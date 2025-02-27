run:
	nohup ../b1_instruction/build/X86/gem5.opt ../system/system_6cpu_o3_4G.py --binary ../Camel/l2_mshr_measurement

clean:
	rm -rf m5out*

grep:
	grep -r -e "Begin" -e "End" -e "maxMshrOccupancy" -e "maxROBOccupancy" ./m5out

time: 
	grep -r -e "simTicks" ./m5out

gprof:
	gprof ../gem_dev/build/X86/gem5.fast gmon.out | gprof2dot -w | dot -Tpng -o output.png

func: 
	gprof ../gem_dev/build/X86/gem5.fast gmon.out > report.txt
