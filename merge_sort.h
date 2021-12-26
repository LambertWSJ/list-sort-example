#ifndef MERGE_SORT_LIST_H
#define MERGE_SORT_LIST_H

#include "list.h"



node_t *mergesort_list(node_t *head)
{
    if (!head || !head->next)
        return head;
    node_t *slow = head;
    node_t *fast;
    for (fast = head->next; fast && fast->next; fast = fast->next->next)
        slow = slow->next;
    node_t *mid = slow->next;
    slow->next = NULL;

    node_t *left = mergesort_list(head);
    node_t *right = mergesort_list(mid);
    return mergeTwoLists(left, right);
}

void mergesort(node_t **list)
{
    *list = mergesort_list(*list);
}



void mergesort_iter_head_tail(node_t **list)
{
    node_t *head = *list;
    if (!head || !head->next)
        return;

    int listsSize = 0;
    const size_t n = 100000;
    node_t *lists[n];
    node_t *sorted = head;

    // split list to sorted lists
    for (node_t *node = head, *next; node; node = next)
    {
        next = node->next;
        node->next = NULL;
        lists[listsSize++] = node;
    }
    
    // merge K Lists
    while (listsSize > 1)
    {
        for (int i = 0, j = listsSize - 1; i < j; i++, j--)
            lists[i] = mergeTwoLists(lists[i], lists[j]);
        listsSize = (listsSize + 1) >> 1;
    }
    *list = lists[0];
}

void mergesort_iter_interval_v2(node_t **list) {
    node_t *head = *list;
    if (!head || !head->next)
        return;

    int listsSize = 0;
    const size_t n = 100000;
    node_t *lists[n];
    node_t *sorted = head;

    // split list to sorted lists
    while (sorted)
    {
        node_t *iter = sorted;
        while (iter && iter->next)
        {
            if (iter->value < iter->next->value)
                iter = iter->next;
            else
                break;
        }
        lists[listsSize++] = sorted;
        sorted = iter->next;
        iter->next = NULL;
    }


    for (int interval = 1; interval < listsSize; interval *= 2)
        for (int i = 0; i + interval < listsSize; i += interval * 2)
            lists[i] = mergeTwoLists(lists[i], lists[i + interval]);

    *list = lists[0];
}
void mergesort_iter_interval(node_t **list)
{
    node_t *head = *list;
    if (!head || !head->next)
        return;

    int listsSize = 0;
    const size_t n = 100000;
    node_t *lists[n];
    node_t *sorted = head;

    // split list to sorted lists
    while (sorted)
    {
        node_t *iter = sorted;
        while (iter && iter->next)
        {
            if (iter->value < iter->next->value)
                iter = iter->next;
            else
                break;
        }
        lists[listsSize++] = sorted;
        sorted = iter->next;
        iter->next = NULL;
    }

    for (int interval = 1; interval < listsSize; interval *= 2)
        for (int i = 0; i + interval < listsSize; i += interval * 2)
            lists[i] = mergeTwoLists(lists[i], lists[i + interval]);

    *list = lists[0];
}

#endif