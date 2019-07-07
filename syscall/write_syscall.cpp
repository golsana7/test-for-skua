
// C program to illustrate 
// write system Call 
#include <fcntl.h> 
#include <iostream>
#include <unistd.h>
#include <time.h>
//asm volatile
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
//gettimeofday
#include <bits/stdc++.h>
#include <sys/time.h>



using namespace std;


main() 
{ 
  int sz; 
  unsigned cycles_low, cycles_high, cycles_low1, cycles_high1;
  uint64_t start,end;
  uint64_t diff=0;
  uint64_t total_diff=0;
  int N = 1000;
  double time_taken;
  struct timeval start1, end1; 
  uint64_t buf = 17266355879;
 // buf[0] = 17266355879;
 // buf[1] = 673886778992;
  int fd = open("foo.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644); 
  
  if (fd < 0) 
  { 
     perror("r1"); 
     exit(1); 
  } 
  

//measuring write() syscall time and clock
  

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

        sz = write(fd, &buf, sizeof(uint64_t)); 
  	N=N-1;
        
  }

//end of clock counter
   asm volatile (
           "RDTSC\n\t"
           "mov %%edx, %0\n\t"
           "mov %%eax, %1\n\t": "=r" (cycles_high1), "=r" (cycles_low1));


// stop timer.
   gettimeofday(&end1, NULL);

//for clock counter
   start = ( ((uint64_t)cycles_high << 32) | cycles_low );
   end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
   diff = end-start;
	
//calculating total time taken by write syscall for 1000 times
   time_taken = ((end1.tv_sec * 1000000 + end1.tv_usec)
                  - (start1.tv_sec * 1000000 + start1.tv_usec));


//for checking that start time is smaller than end time
   cout<<"start time "<<(start1.tv_sec * 1000000 + start1.tv_usec)<<" end time "<<(end1.tv_sec * 1000000 + end1.tv_usec) <<endl;	

//printing final result
   cout<<"clock: "<<diff<<" clokcs " <<" time: "<<time_taken<< " micro sec "<<endl;
	
   close(fd); 
} 




