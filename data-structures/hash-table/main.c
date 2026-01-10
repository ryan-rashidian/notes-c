/* 
 *   File: main.c
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

#include <stdio.h>
#include "hashtable.h"

#define HASH_TABLE_SIZE 50

int main(void)
{
    HashTable *hasht1 = hasht_init(HASH_TABLE_SIZE);
    HashTable *hasht2 = hasht_init(HASH_TABLE_SIZE);

    hasht_insert(hasht1, "apple", 5);
    hasht_insert(hasht2, "apple", 7);
    hasht_insert(hasht1, "cherry", 8);
    hasht_insert(hasht2, "cherry", 9);
    printf("Searching table 1 for 'apple' key: ");
    printf("%d\n", *hasht_search(hasht1, "apple"));
    printf("Searching table 2 for 'apple' key: ");
    printf("%d\n", *hasht_search(hasht2, "apple"));
    printf("Searching table 1 for 'cherry' key: ");
    printf("%d\n", *hasht_search(hasht1, "cherry"));
    printf("Searching table 2 for 'cherry' key: ");
    printf("%d\n", *hasht_search(hasht2, "cherry"));

    hasht_insert(hasht1, "apple", 15);
    printf("Searching table 1 for 'apple' key: ");
    printf("%d\n", *hasht_search(hasht1, "apple"));

    hasht_insert(hasht1, "banana", 26);
    printf("Searching table 1 for 'banana' key: ");
    printf("%d\n", *hasht_search(hasht1, "banana"));

    hasht_destroy(hasht1);
    hasht_destroy(hasht2);

    return 0;
}

