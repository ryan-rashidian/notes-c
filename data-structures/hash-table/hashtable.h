/* 
 *   File: hashtable.h
 * Author: Ryan Rashidian
 *   Date: 2026-01-10
 *
 * Simple hash table demonstration.
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdbool.h>

typedef struct HashTable HashTable;

HashTable *hasht_init(int size);
bool hasht_insert(HashTable *hasht, char *key, int value);
int *hasht_search(HashTable *hasht, char *key);
void hasht_destroy(HashTable *hasht);

#endif

