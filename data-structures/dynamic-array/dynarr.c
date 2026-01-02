/* Demonstration of a dynamically allocated array. */

#include <stddef.h>
#include <stdlib.h>
#include "dynarr.h"

#define STARTING_CAP 10

int  dynarr_init(Dynarr *);
int  dynarr_push(Dynarr *, int);
int  dynarr_pop (Dynarr *, int *);
void dynarr_free(Dynarr *);

int dynarr_init(Dynarr *arr)
{
    arr->cap = STARTING_CAP;
    arr->len = 0;
    arr->data = malloc(arr->cap * sizeof(int));
    return arr->data ? 0 : -1;
}

int dynarr_push(Dynarr *arr, int value)
{
    if (arr->cap == arr->len) {
        size_t new_cap = arr->cap * 2;
        int *tmp = realloc(arr->data, new_cap * sizeof(int));
        if (!tmp) return -1;
        arr->data = tmp;
        arr->cap = new_cap;
    }
    arr->data[arr->len++] = value;
    return 0;
}

int dynarr_pop(Dynarr *arr, int *out)
{
    if (arr->len == 0) return -1;
    *out = arr->data[--arr->len];
    return 0;
}

void dynarr_free(Dynarr *arr)
{
    free(arr->data);
    arr->data = NULL;
    arr->len = arr->cap = 0;
}

