#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <chrono>
#include <cstdint>
#include <time.h> 
//clock_gettime
#include <stdlib.h>     /* for exit() definition */
#include <time.h>       /* for clock_gettime */

/*
int main() {

    uint64_t jaeger_trace_id = 17266355;
    uint64_t jaeger_parent_id =67388992;
    long error;
    clock_t t;

    printf("syscall is used,trap to kernel level\n");
    t = clock();
    error=syscall(333, jaeger_trace_id, jaeger_parent_id, sizeof(uint64_t));
    t = clock() - t;
    double time_taken =( ((double)t)/CLOCKS_PER_SEC)*1000000; // in micro seconds
    printf("syscall() took %f seconds to execute \n", time_taken);

    printf("Back to user level\n");

    return 0;
}

*/

//using namespace std;

int main() {

    uint64_t jaeger_trace_id = 17266355;
    uint64_t jaeger_parent_id =67388992;
    long error;
    #define BILLION 1000000000L
    uint64_t diff=0;
    uint64_t total_diff=0;
    struct timespec start, end;
    int N = 1000;
          
   while (N)
    { 
    
    
    /* measure monotonic time */
      clock_gettime(CLOCK_MONOTONIC, &start);    /* mark start time */
      
    // unsync the I/O of C and C++.
    //ios_base::sync_with_stdio(false);
    
      error=syscall(333, jaeger_trace_id, jaeger_parent_id, sizeof(uint64_t));    /* do stuff */
    
      clock_gettime(CLOCK_MONOTONIC, &end);       /* mark the end time */
    
      //diff = (end.tv_sec - start.tv_sec) * 1e9;
      //diff = (diff + (end.tv_nsec - start.tv_nsec)) * 1e-9; 
      diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
      
       total_diff += diff;
       N = N-1;
     
   
    }

    printf("total-diff-1 = %llu nanoseconds\n", (long long unsigned int) total_diff);
    total_diff = (total_diff/1000);
    printf("elapsed time = %llu nanoseconds\n", (long long unsigned int)total_diff);

    return 0;

  }
