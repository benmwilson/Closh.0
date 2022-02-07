
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>


int main() {
 time_t begin = time(NULL);
printf("ran test file\n");
sleep(6);
time_t end = time(NULL);
printf("The elapsed time is %ld seconds \n", (end - begin));
printf("finished test file\n");
exit(1);
}