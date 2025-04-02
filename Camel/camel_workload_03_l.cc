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

uint32_t time_prefetch_h0(uint32_t **data) {
    uint32_t sum = 0;

    m5_reset_stats(0, 0);
    m5_work_begin(0, 0);
    for (int i = 0; i < elems; i++) {
	__builtin_prefetch(data[i + DISTANCE]);
    	sum += *data[i];
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
    uint64_t sum1;

    for (uint32_t i = 0; i < elems; i++) {
    	data[i] = i;
	data_pointer[i] = &data[i];
    }

    randomize(data_pointer, elems);

    printf("Prefetch H0\n");
    sum1 = time_prefetch_h0(data_pointer);
    printf("Prefetch H0 sum %lu\n", sum1);

}
