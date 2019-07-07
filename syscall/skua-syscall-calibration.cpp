#include <iostream>
#include <fstream>
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
//gettimeofday
#include <bits/stdc++.h>
#include <sys/time.h>

using namespace std;

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
//  ofstream myFile;
//   myFile.open("syscall.csv");
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
    
     
     while (N)

  {

//skua custom syscall
   error=syscall(333, jaeger_trace_id, jaeger_parent_id, sizeof(uint64_t));

   N=N-1;


  }

//end of clock counter
    asm volatile (
           "RDTSC\n\t"
           "mov %%edx, %0\n\t"
           "mov %%eax, %1\n\t": "=r" (cycles_high1), "=r" (cycles_low1));
 

// stop timer.
   gettimeofday(&end1, NULL);


//measuring clock cycles   
   start = ( ((uint64_t)cycles_high << 32) | cycles_low );
   end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
   diff = end-start;   
   

//checking start time is always smaller than end time
    cout<<"start time "<<(start1.tv_sec * 1000000 + start1.tv_usec)<<" end time "<<(end1.tv_sec * 1000000 + end1.tv_usec) <<endl;
   // time_taken = (end1.tv_sec - start1.tv_sec) * 1e6; 
   // time_taken = (time_taken + (end1.tv_usec - start1.tv_usec)) * 1e-6;

   
// Calculating total time taken by the program.
//time in microsec
    time_taken = ((end1.tv_sec * 1000000 + end1.tv_usec)
		  - (start1.tv_sec * 1000000 + start1.tv_usec));
    cout<<"clock: "<<diff<<" clokcs " <<" time: "<<time_taken<< " micro sec "<<endl;
    


    return 0;

  }
