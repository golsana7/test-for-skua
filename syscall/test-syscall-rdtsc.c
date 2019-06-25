#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <chrono>
#include <cstdint>
#include <time.h> 
//clock_gettime
#include <stdlib.h>     /* for exit() definition */
#include <time.h>       /* for clock_gettime */
//asm volatile
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

int main() {

    uint64_t jaeger_trace_id = 17266355;
    uint64_t jaeger_parent_id =67388992;
    long error;
    uint64_t diff=0;
    uint64_t total_diff=0;
   // struct timespec start, end;
    uint64_t start,end;
    int N = 1000;
    //uint64_t cycles_high = 0, cycles_low = 0;
    //uint64_t cycles_high1 = 0, cycles_low1 = 0;
    unsigned cycles_low, cycles_high, cycles_low1, cycles_high1;
        
    while (N)
    
    {
  
   //start time

   //asm volatile ("CPUID\n\t"
  // "RDTSC\n\t"
  // "mov %%edx, %0\n\t"
  // "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
  // "%rax", "%rbx", "%rcx", "%rdx");
 
    asm volatile (
                "RDTSC\n\t"
                "mov %%edx, %0\n\t"
                "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low));
   
   /***********************************/
   /*call the function to measure here*/

   error=syscall(333, jaeger_trace_id, jaeger_parent_id, sizeof(uint64_t));

   /***********************************/

   //end time

  // asm volatile("RDTSCP\n\t"
  // "mov %%edx, %0\n\t"
  // "mov %%eax, %1\n\t"
  // "CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
  // "%rax", "%rbx", "%rcx", "%rdx");
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
   //printf("total-diff-1 = %llu clock cycles\n", ((long long unsigned int)diff/CLOCKS_PER_SEC)*1000000);
    total_diff = total_diff/1000;
    printf("elapsed time = %llu clock cycles\n", (long long unsigned int) total_diff);

    return 0;

  }
