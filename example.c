#include <stdio.h>
#include <assert.h>
#include <stdint-gcc.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include "list.h"
#include "merge_sort.h"

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

int main()
{
    int nums[] = {5, 7, 20, 19, 32, 25, 4, 6, 3, 1, 8, 14, 12};
    int len = sizeof(nums) / sizeof(int);

    void (*sorts[])(node_t **) = {mergesort, mergesort_iter_head_tail, mergesort_iter_interval};
    char *titles[] = {"mergesort", "head-tail", "title"};
    const int sort_len = sizeof(sorts) / sizeof(void *);
    for (int i = 0; i < sort_len; i++)
    {
        node_t *list = NULL;
        for (int i = 0; i < len; i++)
            list = list_make_node_t(list, nums[i]);
        puts(titles[i]);
        list_display(list);
        sorts[i](&list);
        list_display(list);
        shuffle(nums, len);
    }
}
