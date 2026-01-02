#ifndef DYNARR_H
#define DYNARR_H

#include <stddef.h>

typedef struct {
    int *data;
    size_t len;
    size_t cap;
} Dynarr;

int  dynarr_init(Dynarr *);
int  dynarr_push(Dynarr *, int);
int  dynarr_pop (Dynarr *, int *);
void dynarr_free(Dynarr *);

#endif
