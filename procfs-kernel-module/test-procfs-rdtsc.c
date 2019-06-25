#include <algorithm>
#include <cassert>
#include <chrono>
#include <iterator>
#include <iostream>
#include <time.h> 
//asm volatile
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>





int main()

{
   

     
   //static FILE *procfile = fopen("/proc/lttng_jaeger", "w");

    uint64_t jaeger_trace_id = 17266355879;
    uint64_t jaeger_parent_id =673886778992;
    unsigned cycles_low, cycles_high, cycles_low1, cycles_high1;
    uint64_t start,end;
    uint64_t diff=0;
    uint64_t total_diff=0;
    int N = 1000;


    //write the jaeger trace and parent IDs as raw bytes
      uint64_t buf[2];
      buf[0] = jaeger_trace_id;
      buf[1] = jaeger_parent_id;
      
      while(N)
      {
      asm volatile (
           "RDTSC\n\t"
           "mov %%edx, %0\n\t"
           "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low));
      
      
      static FILE *procfile = fopen("/proc/lttng_jaeger", "w");	  
      fwrite(buf, sizeof(uint64_t), 2, procfile);
      
    // flush file to ensure the context is written
      fflush(procfile);

      
       asm volatile (
            "RDTSC\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t": "=r" (cycles_high1), "=r" (cycles_low1));
      
      
       
   start = ( ((uint64_t)cycles_high << 32) | cycles_low );
   end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );



   diff = end-start;
   total_diff += diff;
   N = N-1;
      }

      printf("total-diff-1 = %llu clock cycles\n", (long long unsigned int)diff);
      total_diff = total_diff/1000;
      printf("elapsed time = %llu clock cycles\n", (long long unsigned int) total_diff);
       return 0;
}
