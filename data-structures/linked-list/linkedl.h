#ifndef LINKEDL_H
#define LINKEDL_H

struct node {
    int value;
    struct node *next;
};

struct node    *list_add(struct node *, int);
struct node *list_remove(struct node *, int);
struct node *list_search(struct node *, int);

#endif

