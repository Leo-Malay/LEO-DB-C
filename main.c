#include <stdio.h>
#include <time.h>
#include "table.c"
#include "record.c"
#include "log.c"
int main()
{
    clock_t start, end;
    start = clock();

    // Write your db functions here!

    end = clock();
    printf("Time Taken: %f\n", ((double)(end - start)) / CLOCKS_PER_SEC);
    return 0;
}