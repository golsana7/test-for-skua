#include <iostream>
#include <fstream>
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
//gettimeofday
#include <bits/stdc++.h>
#include <sys/time.h>

using namespace std;


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
    struct timeval start1, end1;
    double time_taken;


    // start timer. 
    gettimeofday(&start1, NULL);

    // unsync the I/O of C and C++. 
    ios_base::sync_with_stdio(false);

    //start counter 
    asm volatile (
              "RDTSC\n\t"
              "mov %%edx, %0\n\t"
              "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low));

    //write the jaeger trace and parent IDs as raw bytes
      uint64_t buf[2];
      buf[0] = jaeger_trace_id;
      buf[1] = jaeger_parent_id;
    

      while(N)
      {
    //  asm volatile (
      //     "RDTSC\n\t"
        //   "mov %%edx, %0\n\t"
          // "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low));
     
      
      static FILE *procfile = fopen("/proc/lttng_jaeger", "w");	  
      fwrite(buf, sizeof(uint64_t), 2, procfile);
      
    // flush file to ensure the context is written
      fflush(procfile);

    //end time  
      // asm volatile (
        //    "RDTSC\n\t"
          //  "mov %%edx, %0\n\t"
            //"mov %%eax, %1\n\t": "=r" (cycles_high1), "=r" (cycles_low1));
      
      
       
  // start = ( ((uint64_t)cycles_high << 32) | cycles_low );
 //  end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );



   // diff = end-start;
   // myFile<< diff<<",";
  //  printf("diff = %llu,\n", (long long unsigned int)diff);

    N=N-1;
      }

    //end of clock counter
    asm volatile (
           "RDTSC\n\t"
           "mov %%edx, %0\n\t"
           "mov %%eax, %1\n\t": "=r" (cycles_high1), "=r" (cycles_low1));


   // stop timer.
   gettimeofday(&end1, NULL);

   start = ( ((uint64_t)cycles_high << 32) | cycles_low );
   end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
   diff = end-start;

    // Calculating total time taken by the program.
    //checking whether start time is less than end time
    cout<<"start time "<<(start1.tv_sec * 1000000 + start1.tv_usec)<<" end time "<<(end1.tv_sec * 1000000 + end1.tv_usec) <<endl;

    time_taken = ((end1.tv_sec * 1000000 + end1.tv_usec)
                  - (start1.tv_sec * 1000000 + start1.tv_usec));
    cout<<"clock: "<<diff<<" clokcs " <<" time: "<<time_taken<< " usec sec "<<endl;
    
    return 0;
}
