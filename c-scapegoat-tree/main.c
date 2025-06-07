#include "btree.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

int main()
{
    int root  = 0;
    int count = 0;
    int seed  = time(NULL);
    int cost_time = 0;
    int start_time = 0;
    unsigned int insert = 0;
    struct timeval tv;

    for (int i = 1; i < MAXN; i++) {
        seed = seed * (count + (count + 1) * 7);
        srand(seed);
        count++;
        insert = (unsigned int)floor(rand() * 100) % 1000;
        printf("insert: %d\n", insert);
        gettimeofday(&tv, NULL);
        start_time = tv.tv_sec * 1000000 + tv.tv_usec;
        insert_node(&root, insert);
        gettimeofday(&tv, NULL);
        cost_time = tv.tv_sec * 1000000 + tv.tv_usec -  start_time;
        usleep(100);
    }
    printf("insert %d, rebuild %d, pro: %g%%\n", count, get_rebc(),
           ((double)get_rebc() / (double)count) * 100);
    printf("cost time is: %f(s) %d(us)\n", (float)cost_time / 1000000, cost_time);
    return 0;
}
