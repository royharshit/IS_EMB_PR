C=gcc
CXX=g++
RM=rm -f

SRCS=camel_workload_03.cc
SRCS1=camel_workload_unroll.cc
OBJS=camel_workload_03
OBJS1=camel_workload_unroll
GEM_HOME=../b1_instruction

CFLAGS=-std=c++14 -static -O3 -I $(GEM_HOME)/include
LDFLAGS=-L$(GEM_HOME)/util/m5/build/x86/out/ -lm5

camel_workload_03: camel_workload_03.cc
	$(CC) $(CFLAGS) $(SRCS) -o $(OBJS) $(LDFLAGS)

camel_workload_unroll: camel_workload_unroll.cc
	$(CC) $(CFLAGS) $(SRCS1) -o $(OBJS1) $(LDFLAGS)

clean:
	$(RM) $(OBJS)
