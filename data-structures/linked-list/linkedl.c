/* Demonstration of a linked list. */

#include <stdio.h>
#include <stdlib.h>
#include "linkedl.h"

struct node    *list_add(struct node *, int);
struct node *list_remove(struct node *, int);
struct node *list_search(struct node *, int);

struct node *list_add(struct node *list, int value)
{
    struct node *new_node;

    new_node = malloc(sizeof(struct node));
    if (new_node == NULL) {
        printf("Error: add_to_list malloc failure");
        exit(EXIT_FAILURE);
    }
    new_node->value = value;
    new_node->next = list;
    return new_node;
}

struct node *list_remove(struct node *list, int value)
{
    struct node *cur, *prev;

    for (cur = list, prev = NULL;
         cur != NULL && cur->value != value;
         prev = cur, cur = cur->next)
        ;

    if (cur == NULL)
        return list;
    else if (prev == NULL)
        list = list->next;
    else
        prev->next = cur->next;
    free(cur);
    return list;
}

struct node *list_search(struct node *list, int value)
{
    for (; list != NULL && list->value != value; list = list->next)
        ;
    return list;
}

