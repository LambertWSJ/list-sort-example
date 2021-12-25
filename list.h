#ifndef LIST_H
#define LIST_H

typedef struct __node
{
    int value;
    struct __node *next;
} node_t;

node_t *mergeTwoLists(node_t *left, node_t *right)
{
    node_t *result = NULL;
    node_t **indir = &result;

    for (node_t **node = NULL; left && right; *node = (*node)->next)
    {
        node = left->value < right->value ? &left : &right;
        *indir = *node;
        indir = &(*indir)->next;
    }
    *indir = left ? left : right;
    return result;
}




node_t *list_make_node_t(node_t *list, int val)
{
    node_t *node = malloc(sizeof(node_t));
    node->next = NULL;
    node->value = val;
    if (!list)
    {
        list = node;
    }
    else
    {
        node->next = list;
        list = node;
    }
    return list;
}

bool list_is_ordered(node_t *list)
{
    bool first = true;
    int value;
    while (list)
    {
        if (first)
        {
            value = list->value;
            first = false;
        }
        else
        {
            if (list->value < value)
                return false;
            value = list->value;
        }
        list = list->next;
    }
    return true;
}

void list_display(node_t *list)
{
    printf("%s IN ORDER : ", list_is_ordered(list) ? "   " : "NOT");
    while (list)
    {
        printf("%d ", list->value);
        list = list->next;
    }
    printf("\n");
}


void list_free(node_t **list)
{
    node_t *cur = *list, *next = NULL;
    while (cur)
    {
        next = cur->next;
        free(cur);
        cur = next;
    }
}

#endif