#include <unistd.h>
#include <asm/unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdint>
#include <cinttypes>


#include <gem5/m5ops.h>


const size_t memsize = 128*1024*1024;
const size_t elems = memsize / sizeof(uint32_t);
const int DISTANCE = 32;
const int UNROLL = 16;

uint32_t hash(uint32_t data) {
    return 9*data % 17;
}

uint32_t time_nonprefetch_h0(uint32_t** data) {
    uint32_t sum = 0;
    
    m5_reset_stats(100000, 0);
    m5_work_begin(0, 0);
    for (uint32_t i = 0; i < elems; i++) {
	sum += *data[i];
    }
    m5_work_end(0, 0);
    m5_dump_stats(0, 0);

    return sum;
}

uint32_t time_prefetch_h0(uint32_t **data) {
    uint32_t sum = 0;

    m5_reset_stats(100000, 0);
    m5_work_begin(0, 0);
    for (int i = 0; i < elems; i++) {
	__builtin_prefetch(data[i + DISTANCE]);
    	sum += *data[i];
    }
    m5_work_end(0, 0);
    m5_dump_stats(0, 0);

    return sum;
}

uint32_t time_nonprefetch_h1(uint32_t **data) {
    uint32_t sum = 0;
    m5_reset_stats(100000, 0);
    m5_work_begin(0, 0);
    for (int i = 0; i < elems; i++) {
    	sum += hash(*data[i]);
    }
    m5_work_end(0, 0);
    m5_dump_stats(0, 0);
    return sum;
}

uint32_t time_prefetch_h1(uint32_t **data) {
    uint32_t sum = 0;
    m5_reset_stats(100000, 0);
    m5_work_begin(0, 0);
    for (int i = 0; i < elems - DISTANCE; i++) {
	__builtin_prefetch(data[i + DISTANCE]);
    	sum += hash(*data[i]);
    }
    for (int i = elems - DISTANCE; i < elems; i++) {
    	sum += hash(*data[i]);
    }
    m5_work_end(0, 0);
    m5_dump_stats(0, 0);
    return sum;
}


uint32_t time_nonprefetch_h2(uint32_t **data) {
    uint32_t sum = 0; 
    m5_reset_stats(100000, 0);
    m5_work_begin(0, 0);
    for (int i = 0; i < elems; i++) {
    	sum += hash(hash(*data[i]));
    }
    m5_work_end(0, 0);
    m5_dump_stats(0, 0);
    return sum;
}


uint32_t time_prefetch_h2(uint32_t **data) {
    uint32_t sum = 0; 
    m5_reset_stats(100000, 0);
    m5_work_begin(0, 0);
    for (int i = 0; i < elems - DISTANCE; i++) {
	__builtin_prefetch(data[i + DISTANCE]);
    	sum += hash(hash(*data[i]));
    }
    for (int i = elems - DISTANCE; i < elems; i++) {
    	sum += hash(hash(*data[i]));
    }
    m5_work_end(0, 0);
    m5_dump_stats(0, 0);
    return sum;
}

uint32_t time_nonprefetch_h3(uint32_t **data) {
    uint32_t sum = 0; 
    m5_reset_stats(100000, 0);
    m5_work_begin(0, 0);
    for (int i = 0; i < elems; i++) {
    	sum += hash(hash(hash(*data[i])));
    }
    m5_work_end(0, 0);
    m5_dump_stats(0, 0);
    return sum;
}


uint32_t time_prefetch_h3(uint32_t **data) {
    uint32_t sum = 0; 
    m5_reset_stats(100000, 0);
    m5_work_begin(0, 0);
    for (int i = 0; i < elems - DISTANCE; i++) {
	__builtin_prefetch(data[i + DISTANCE]);
    	sum += hash(hash(hash(*data[i])));
    }
    for (int i = elems - DISTANCE; i < elems; i++) {
    	sum += hash(hash(hash(*data[i])));
    }
    m5_work_end(0, 0);
    m5_dump_stats(0, 0);
    return sum;
}


uint32_t time_nonprefetch_h4(uint32_t **data) {
    uint32_t sum = 0; 
    m5_reset_stats(100000, 0);
    m5_work_begin(0, 0);
    for (int i = 0; i < elems; i++) {
    	sum += hash(hash(hash(hash(*data[i]))));
    }
    m5_work_end(0, 0);
    m5_dump_stats(0, 0);
    return sum;
}


uint32_t time_prefetch_h4(uint32_t **data) {
    uint32_t sum = 0; 
    m5_reset_stats(100000, 0);
    m5_work_begin(0, 0);
    for (int i = 0; i < elems - DISTANCE; i++) {
	__builtin_prefetch(data[i + DISTANCE]);
    	sum += hash(hash(hash(hash(*data[i]))));
    }
    for (int i = elems - DISTANCE; i < elems; i++) {
    	sum += hash(hash(hash(hash(*data[i]))));
    }
    m5_work_end(0, 0);
    m5_dump_stats(0, 0);
    return sum;
}

uint32_t time_nonprefetch_h5(uint32_t **data) {
    uint32_t sum = 0; 
    m5_reset_stats(100000, 0);
    m5_work_begin(0, 0);
    for (int i = 0; i < elems; i++) {
    	sum += hash(hash(hash(hash(hash(*data[i])))));
    }
    m5_work_end(0, 0);
    m5_dump_stats(0, 0);
    return sum;
}


uint32_t time_prefetch_h5(uint32_t **data) {
    uint32_t sum = 0; 
    m5_reset_stats(100000, 0);
    m5_work_begin(0, 0);
    for (int i = 0; i < elems - DISTANCE; i++) {
	__builtin_prefetch(data[i + DISTANCE]);
    	sum += hash(hash(hash(hash(hash(*data[i])))));
    }
    for (int i = elems - DISTANCE; i < elems; i++) {
    	sum += hash(hash(hash(hash(hash(*data[i])))));
    }
    m5_work_end(0, 0);
    m5_dump_stats(0, 0);
    return sum;
}


uint32_t time_nonprefetch_h6(uint32_t **data) {
    uint32_t sum = 0; 
    m5_reset_stats(100000, 0);
    m5_work_begin(0, 0);
    for (int i = 0; i < elems; i++) {
    	sum += hash(hash(hash(hash(hash(hash(*data[i]))))));
    }
    m5_work_end(0, 0);
    m5_dump_stats(0, 0);
    return sum;
}


uint32_t time_prefetch_h6(uint32_t **data) {
    uint32_t sum = 0; 
    m5_reset_stats(100000, 0);
    m5_work_begin(0, 0);
    for (int i = 0; i < elems - DISTANCE; i++) {
	__builtin_prefetch(data[i + DISTANCE]);
    	sum += hash(hash(hash(hash(hash(hash(*data[i]))))));
    }
    for (int i = elems - DISTANCE; i < elems; i++) {
    	sum += hash(hash(hash(hash(hash(hash(*data[i]))))));
    }
    m5_work_end(0, 0);
    m5_dump_stats(0, 0);
    return sum;
}


uint32_t time_nonprefetch_h7(uint32_t **data) {
    uint32_t sum = 0; 
    m5_reset_stats(100000, 0);
    m5_work_begin(0, 0);
    for (int i = 0; i < elems; i++) {
    	sum += hash(hash(hash(hash(hash(hash(hash(*data[i])))))));
    }
    m5_work_end(0, 0);
    m5_dump_stats(0, 0);
    return sum;
}


uint32_t time_prefetch_h7(uint32_t **data) {
    uint32_t sum = 0; 
    m5_reset_stats(100000, 0);
    m5_work_begin(0, 0);
    for (int i = 0; i < elems - DISTANCE; i++) {
	__builtin_prefetch(data[i + DISTANCE]);
    	sum += hash(hash(hash(hash(hash(hash(hash(*data[i])))))));
    }
    for (int i = elems - DISTANCE; i < elems; i++) {
    	sum += hash(hash(hash(hash(hash(hash(hash(*data[i])))))));
    }
    m5_work_end(0, 0);
    m5_dump_stats(0, 0);
    return sum;
}

uint32_t time_nonprefetch_h8(uint32_t **data) {
    uint32_t sum = 0; 
    m5_reset_stats(100000, 0);
    m5_work_begin(0, 0);
    for (int i = 0; i < elems; i++) {
    	sum += hash(hash(hash(hash(hash(hash(hash(hash(*data[i]))))))));
    }
    m5_work_end(0, 0);
    m5_dump_stats(0, 0);
    return sum;
}


uint32_t time_prefetch_h8(uint32_t **data) {
    uint32_t sum = 0; 
    m5_reset_stats(100000, 0);
    m5_work_begin(0, 0);
    for (int i = 0; i < elems - DISTANCE; i++) {
	__builtin_prefetch(data[i + DISTANCE]);
    	sum += hash(hash(hash(hash(hash(hash(hash(hash(*data[i]))))))));
    }
    for (int i = elems - DISTANCE; i < elems; i++) {
    	sum += hash(hash(hash(hash(hash(hash(hash(hash(*data[i]))))))));
    }
    m5_work_end(0, 0);
    m5_dump_stats(0, 0);
    return sum;
}


uint32_t time_nonprefetch_h9(uint32_t **data) {
    uint32_t sum = 0; 
    m5_reset_stats(100000, 0);
    m5_work_begin(0, 0);
    for (int i = 0; i < elems; i++) {
    	sum += hash(hash(hash(hash(hash(hash(hash(hash(hash(*data[i])))))))));
    }
    m5_work_end(0, 0);
    m5_dump_stats(0, 0);
    return sum;
}


uint32_t time_prefetch_h9(uint32_t **data) {
    uint32_t sum = 0; 
    m5_reset_stats(100000, 0);
    m5_work_begin(0, 0);
    for (int i = 0; i < elems - DISTANCE; i++) {
	__builtin_prefetch(data[i + DISTANCE]);
    	sum += hash(hash(hash(hash(hash(hash(hash(hash(hash(*data[i])))))))));
    }
    for (int i = elems - DISTANCE; i < elems; i++) {
    	sum += hash(hash(hash(hash(hash(hash(hash(hash(hash(*data[i])))))))));
    }
    m5_work_end(0, 0);
    m5_dump_stats(0, 0);
    return sum;
}

void swap (uint32_t **a, uint32_t **b)
{
    uint32_t* temp = *a;
    *a = *b;
    *b = temp;
}

void randomize (uint32_t **arr, uint32_t n)
{
    srand (time_t(NULL));
    for (uint32_t i = n - 1; i > 0; i--)
    {
        uint32_t j = rand() % (i + 1);
        swap(&arr[i], &arr[j]);
    }
}

int main() {

    uint32_t* data = (uint32_t*)malloc(memsize);
    uint32_t** data_pointer = (uint32_t**)malloc(elems*sizeof(uint32_t*));
    uint64_t sum1, sum2;

    for (uint32_t i = 0; i < elems; i++) {
    	data[i] = i;
	data_pointer[i] = &data[i];
    }

    randomize(data_pointer, elems);

    int32_t N = 0;

        while (N < 10) { 
            if (N == 0) {
		printf("Non Prefetch H0\n");
		sum1 = time_nonprefetch_h0(data_pointer);
		printf("Non Prefetch H0 sum %lu\n", sum1);
            }
            if (N == 1) {
		printf("Non Prefetch H1\n");
                sum1 = time_nonprefetch_h1(data_pointer);
		printf("Non Prefetch H1 sum %lu\n", sum1);
            }
            else if (N == 2) {
		printf("Non Prefetch H2\n");
                sum1 = time_nonprefetch_h2(data_pointer);
		printf("Non Prefetch H2 sum %lu\n", sum1);
	    }
            else if (N == 3) {
		printf("Non Prefetch H3\n");
                sum1 = time_nonprefetch_h3(data_pointer);
		printf("Non Prefetch H3 sum %lu\n", sum1);
	    }
            else if (N == 4) {
		printf("Non Prefetch H4\n");
                sum1 = time_nonprefetch_h4(data_pointer);
		printf("Non Prefetch H4 sum %lu\n", sum1);
	    }
            else if (N == 5) {
		printf("Non Prefetch H5\n");
                sum1 = time_nonprefetch_h5(data_pointer);
		printf("Non Prefetch H5 sum %lu\n", sum1);
	    }
            else if (N == 6) {
		printf("Non Prefetch H6\n");
                sum1 = time_nonprefetch_h6(data_pointer);
		printf("Non Prefetch H6 sum %lu\n", sum1);
	    }
            else if (N == 7) {
		printf("Non Prefetch H7\n");
                sum1 = time_nonprefetch_h7(data_pointer);
		printf("Non Prefetch H7 sum %lu\n", sum1);
	    }
            else if (N == 8) {
		printf("Non Prefetch H8\n");
                sum1 = time_nonprefetch_h8(data_pointer);
		printf("Non Prefetch H8 sum %lu\n", sum1);
	    }
            else if (N == 9) {
		printf("Non Prefetch H9\n");
                sum1 = time_nonprefetch_h9(data_pointer);
		printf("Non Prefetch H9 sum %lu\n", sum1);
	    }
            if (N == 0) {
		printf("Prefetch H0\n");
            	sum2 = time_prefetch_h0(data_pointer);
		printf("Prefetch H0 sum %lu\n", sum2);
	    }
            if (N == 1) {
		printf("Prefetch H1\n");
            	sum2 = time_prefetch_h1(data_pointer);
		printf("Prefetch H1 sum %lu\n", sum2);
	    }
            else if (N == 2) {    
		printf("Prefetch H2\n");
            	sum2 = time_prefetch_h2(data_pointer);
		printf("Prefetch H2 sum %lu\n", sum2);
	    }
            else if (N == 3) {
		printf("Prefetch H3\n");
            	sum2 = time_prefetch_h3(data_pointer);
		printf("Prefetch H3 sum %lu\n", sum2);
	    }
            else if (N == 4) {
		printf("Prefetch H4\n");
            	sum2 = time_prefetch_h4(data_pointer);
		printf("Prefetch H4 sum %lu\n", sum2);
	    }
            else if (N == 5) {
		printf("Prefetch H5\n");
            	sum2 = time_prefetch_h5(data_pointer);
		printf("Prefetch H5 sum %lu\n", sum2);
	    }
            else if (N == 6) {
		printf("Prefetch H6\n");
            	sum2 = time_prefetch_h6(data_pointer);
		printf("Prefetch H6 sum %lu\n", sum2);
	    }
            else if (N == 7) {
		printf("Prefetch H7\n");
            	sum2 = time_prefetch_h7(data_pointer);
		printf("Prefetch H7 sum %lu\n", sum2);
	    }
            else if (N == 8) {
		printf("Prefetch H8\n");
            	sum2 = time_prefetch_h8(data_pointer);
		printf("Prefetch H8 sum %lu\n", sum2);
	    }
            else if (N == 9) {
		printf("Prefetch H9\n");
            	sum2 = time_prefetch_h9(data_pointer);
		printf("Prefetch H9 sum %lu\n", sum2);
	    }
            N++;

        }
}
