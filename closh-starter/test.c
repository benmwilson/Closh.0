
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>


int main() {
    clock_t timer_end;
        clock_t timer;
        double timer_elapsed;
        long sum;
 
printf("ran test file\n");
// timer = clock();
// for (int i = 0; i < 100000; i++){
//     for(int j = 0; j < 10000; j++){
//     }
// }
// timer_end = clock();
// timer_elapsed = ((double)(timer_end- timer)/CLOCKS_PER_SEC); //should give time elapsed in seconds
// printf("time_elapsed inside test file: %f\n", timer_elapsed);


time_t start = time(NULL);
sleep(6);
time_t end = time(NULL);
printf("The elapsed time in the test program is %ld seconds \n", (end - start));
printf("finished test file\n");
exit(1);
}