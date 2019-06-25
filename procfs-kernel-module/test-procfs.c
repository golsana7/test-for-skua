#include <algorithm>
#include <cassert>
#include <chrono>
#include <iterator>
#include <iostream>
#include <time.h> 
//clock_gettime
#include <stdlib.h>     /* for exit() definition */
#include <time.h>       /* for clock_gettime */
//working with write syscall directly
//#include <unistd.h>
//#include <fcntl.h>





int main()

{
   

 
    static FILE *procfile = fopen("/proc/lttng_jaeger", "w");
 //   int fd = open(“/proc/lttng_jaeger”, O_RDWR); 
    uint64_t jaeger_trace_id = 17266355879;
    uint64_t jaeger_parent_id =673886778992;
    #define BILLION 1000000000L
    uint64_t diff=0;
    uint64_t total_diff=0;
    struct timespec start, end;
    int N = 1000;

    //write the jaeger trace and parent IDs as raw bytes
      uint64_t buf[2];
      buf[0] = jaeger_trace_id;
      buf[1] = jaeger_parent_id;
      
      
          
   while (N)
   {

    /* measure monotonic time */
      clock_gettime(CLOCK_MONOTONIC, &start);    /* mark start time */
      
      fwrite(buf, sizeof(uint64_t), 2, procfile);
    //err = write(fd, buf, sizeof(buf));
      
    // flush file to ensure the context is written
      fflush(procfile);

      clock_gettime(CLOCK_MONOTONIC, &end);       /* mark the end time */

      diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
      
      total_diff += diff;
      N = N-1; 
   }

    printf("total-diff-1 = %llu nanoseconds\n", (long long unsigned int) total_diff);
    total_diff = total_diff/1000;
    printf("elapsed time = %llu nanoseconds\n", (long long unsigned int)total_diff);
    
      
      return 0;
}
