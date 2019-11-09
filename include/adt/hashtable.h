#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include <stdbool.h>

#include "type.h"

typedef struct hash_node {
    char *key;
    char *value;
    struct hash_node *next;
} hash_node_t;

typedef struct hashtable {
    int size;
    int capacity;
    hash_node_t **arr;
} hashtable_t;

hashtable_t *create_hashtable(int capacity);
void dispose_hashtable(hashtable_t *table);
bool is_hashtable_empty(hashtable_t *table);
bool is_hashtable_full(hashtable_t *table);
void hashtable_set(hashtable_t *table, const char *key, const char *value);
const char *hashtable_get(hashtable_t *table, const char *key);
void hashtable_remove(hashtable_t *table, const char *key);

#endif