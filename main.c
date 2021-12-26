#include <stdio.h>
#include <assert.h>
#include <stdint-gcc.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include "list.h"
#include "merge_sort.h"

time_t diff(struct timespec t1, struct timespec t2)
{
    return (t2.tv_nsec - t1.tv_nsec) + (t2.tv_sec - t1.tv_sec) * 1000000000;
}

void shuffle(int *nums, size_t n)
{
    for (int i = n - 1; i >= 0; i--)
    {
        int idx = rand() % n;
        int temp = nums[idx];
        nums[idx] = nums[i];
        nums[i] = temp;
    }
}


int main(int argc, char **argv)
{
    struct timespec start, end;
    srand(time(NULL));
    const int N = 100000;
    const int epochs = 1000;
    int interval = epochs / 10;

    int nums[N];
    // void (*sorts[])(node_t **) = {mergesort, mergesort_iter_head_tail, mergesort_iter_interval};
    void (*sorts[])(node_t **) = {mergesort_iter_interval, mergesort_iter_interval_v2};
    const int sort_len = sizeof(sorts) / sizeof(void *);
    // node_t *lists[sort_len];
    time_t measures[epochs][sort_len];

    for (int j = 0; j < N; j++)
        nums[j] = j;

    for (int i = 0; i < epochs; i++)
    {
        shuffle(nums, N);

        // measure each sort methods
        for (int k = 0; k < sort_len; k++)
        {
            node_t *list = NULL;
            struct timespec start, end;
            for (int j = 0; j <= N; j++)
                list = list_make_node_t(list, nums[j]);

            clock_gettime(CLOCK_MONOTONIC, &start);
            sorts[k](&list);
            clock_gettime(CLOCK_MONOTONIC, &end);
            assert(list_is_ordered(list));
            measures[i][k] = diff(start, end);
            list_free(&list);
        }
        if ((i + 1) % interval == 0)
        {
            printf("Benchmark %-3d%%\n", 100 * (i + 1) / epochs);
            fflush(stdout);
        }
    }

    FILE *file = fopen("bench_sort.txt", "w+");

    for (size_t j = 0; j < epochs; j++)
    {
        for (size_t i = 0; i < sort_len; i++)
        {
            char *token = i == sort_len - 1 ? j == epochs - 1 ? "" : "\n" : "\t";
            fprintf(file, "%ld%s", measures[j][i], token);
        }
    }
    fclose(file);
    puts("Benchmark Done.");
}
