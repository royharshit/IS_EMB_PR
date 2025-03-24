run:
	nohup ../b1_instruction/build/X86/gem5.opt ../system/system_6cpu_o3_4G_512.py --binary ../Camel/camel_workload_03

run_visual:
	nohup ../b1_instruction/build/X86/gem5.opt --debug-flags=O3PipeView --debug-file=trace.out ../system/system_6cpu_o3_4G_512.py --binary ../Camel/camel_workload_03

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

pipeview: 
	../b1_instruction/util/o3-pipeview.py -c 250 -o pipeview.out --color m5out/trace.out
