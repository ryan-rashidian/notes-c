/* Demonstration of a linked list. */

#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *next;
};

struct node *add_to_list(struct node *list, int value);
struct node *delete_from_list(struct node *list, int value);
struct node *search_list(struct node *list, int value);


struct node *add_to_list(struct node *list, int value)
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

struct node *delete_from_list(struct node *list, int value)
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

struct node *search_list(struct node *list, int value)
{
    for (; list != NULL && list->value != value; list = list->next)
        ;
    return list;
}

