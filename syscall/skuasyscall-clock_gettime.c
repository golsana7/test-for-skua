#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <chrono>
#include <cstdint>
#include <time.h> 
//clock_gettime
#include <stdlib.h>     /* for exit() definition */
#include <time.h>       /* for clock_gettime */



int main() {

    uint64_t jaeger_trace_id = 17266355;
    uint64_t jaeger_parent_id =67388992;
    long error;
    uint64_t diff=0;
    uint64_t total_diff=0;
    struct timespec start, end;
    int N = 1000;
    #define BILLION 1000000000L
          
/* measure monotonic time */
    clock_gettime(CLOCK_MONOTONIC, &start);    /* mark start time */
    
    while (N)
    { 
    
    
    /* measure monotonic time */
    //clock_gettime(CLOCK_MONOTONIC, &start);    /* mark start time */
      
    // unsync the I/O of C and C++.
    //ios_base::sync_with_stdio(false);
    
      error=syscall(333, jaeger_trace_id, jaeger_parent_id, sizeof(uint64_t));    /* do stuff */
    
    //clock_gettime(CLOCK_MONOTONIC, &end);       /* mark the end time */
    
    //diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
    //total_diff += diff;
      
      N = N-1;
     }

    clock_gettime(CLOCK_MONOTONIC, &end);       /* mark the end time */

//calculationg elapsed time
    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;

    printf("total-diff-1 = %llu nanoseconds\n", (long long unsigned int) diff);
    total_diff = (diff/1000);
    printf("elapsed time = %llu nanoseconds\n", (long long unsigned int)total_diff);

    return 0;

  }
