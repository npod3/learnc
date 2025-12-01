// Purpose: time() and simple pseudo-random.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int example_time_random(void){ srand((unsigned)time(NULL)); int r=rand()%100; printf("rand=%d time=%ld\n", r, (long)time(NULL)); return 0; }
