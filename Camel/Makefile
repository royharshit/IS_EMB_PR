C=gcc
CXX=g++
RM=rm -f

SRCS=l2_mshr_measurement.cc
OBJS=l2_mshr_measurement
OBJS1=l2_mshr_measurement_naive
GEM_HOME=../b1_instruction

CFLAGS=-std=c++14 -static -O3 -I $(GEM_HOME)/include
LDFLAGS=-L$(GEM_HOME)/util/m5/build/x86/out/ -lm5

l2_mshr_measurement: l2_mshr_measurement.cc
	$(CC) $(CFLAGS) $(SRCS) -o $(OBJS) $(LDFLAGS)

l2_mshr_measurement_naive: l2_mshr_measurement_naive.cc
	$(CC) $(CFLAGS) $(SRCS) -o $(OBJS1) $(LDFLAGS)

clean:
	$(RM) $(OBJS)
