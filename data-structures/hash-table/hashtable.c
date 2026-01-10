/* 
 *   File: hashtable.c
 * Author: Ryan Rashidian
 *   Date: 2026-01-10
 *
 * Simple hash table demonstration.
 *
 * Future improvements:
 *   - Resize table if > 70% of size if filled.
 *   - Function for removing items.
 *   - Thread safety (C11 <threads.h> library).
 *
 * "Like I said earlier, most languages have hash tables.
 * You don't need to know how to write your own."
 * - Chapter 5: Grokking Algorithms 2e by Aditya Y. Bhargava
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} Item;

typedef struct node {
    Item item;
    struct node *next_item;
} Node;

typedef struct {
    Node **items_arr;
    int size;
} HashTable;

static int hash_key_(char *key, int size);
HashTable *hasht_init(int size);
bool hasht_insert(HashTable *hasht, char *key, int value);
int *hasht_search(HashTable *hasht, char *key);
void hasht_destroy(HashTable *hasht);

static int hash_key_(char *key, int size)
{
    /* Simple hash function. */
    int hash = 0;

    for (int i = 0; key[i]; i++) {
        hash += key[i];
    }

    return hash % size;
}

HashTable *hasht_init(int size)
{
    HashTable *hasht = malloc(sizeof(HashTable));
    if (hasht == NULL) {
        return NULL;
    }
    hasht->items_arr = calloc(size, sizeof(Node*));
    if (hasht->items_arr == NULL) {
        free(hasht);
        return NULL;
    }
    hasht->size = size;
    return hasht;
}

bool hasht_insert(HashTable *hasht, char *key, int value)
{
    int hash = hash_key_(key, hasht->size);

    // Update existing key
    for (Node *cur = hasht->items_arr[hash]; cur; cur = cur->next_item) {
        if (strcmp(cur->item.key, key) == 0) {
            cur->item.value = value;
            return true;
        }
    }

    // Insert new node
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return false;
    }
    node->item.key = malloc(strlen(key) + 1);
    if (node->item.key == NULL) {
        free(node);
        return false;
    }

    strcpy(node->item.key, key);
    node->item.value = value;
    node->next_item = hasht->items_arr[hash];
    hasht->items_arr[hash] = node;
    return true;
}

int *hasht_search(HashTable *hasht, char *key)
{
    int hash = hash_key_(key, hasht->size);
    for (Node *cur = hasht->items_arr[hash]; cur; cur = cur->next_item) {
        if (strcmp(cur->item.key, key) == 0) {
            return &cur->item.value;
        }
    }
    return NULL;
}

void hasht_destroy(HashTable *hasht)
{
    for (int i = 0; i < hasht->size; i++) {
        Node *current = hasht->items_arr[i];
        while (current) {
            Node *next = current->next_item;
            free(current->item.key);
            free(current);
            current = next;
        }
    }

    free(hasht->items_arr);
    free(hasht);
}

