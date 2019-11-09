#include <adt/hashtable.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

hashtable_t *create_hashtable(int capacity) {
    hashtable_t *table = (hashtable_t *)malloc(sizeof(hashtable_t));
    if (!table)
        return NULL;

    int size = capacity * sizeof(hash_node_t *);
    table->arr = (hash_node_t **)malloc(size);
    if (!table->arr) {
        free(table);
        return NULL;
    }

    memset(table->arr, 0, size);
    table->capacity = capacity;
    table->size = 0;

    return table;
}

void dispose_hashtable(hashtable_t *table) {
    if (table) {
        if (!is_hashtable_empty(table)) {
            for (int i = 0; i < table->capacity; i++) {
                hash_node_t *p = table->arr[i];
                while (p) {
                    free(p->key);
                    free(p->value);
                    p = p->next;
                }
            }
        }

        free(table->arr);
        free(table);
    }
}

bool is_hashtable_empty(hashtable_t *table) {
    if (!table || !table->size)
        return true;

    return false;
}
bool is_hashtable_full(hashtable_t *table) {
    if (table && table->size == table->capacity)
        return true;

    return false;
}

/**
 *
 *times33 hash func
 *
 */
static int times33(const char *key) {
    int hash = 5381;  // or 0

    while (*key) {
        hash += (hash << 5) + *key++;
    }

    return hash & 0x7fffffff;
}

void hashtable_set(hashtable_t *table, const char *key, const char *value) {
    if (!is_hashtable_full(table)) {
        int pos = times33(key) % table->capacity;
        // printf("set at pos=%d\n", pos);
        hash_node_t *head = table->arr[pos];
        hash_node_t *p = head;
        while (p) {
            if (!strcmp(p->key, key)) {
                free(p->value);
                p->value = strdup(value);
                return;
            }
            p = p->next;
        }

        p = (hash_node_t *)malloc(sizeof(hash_node_t));
        p->key = strdup(key);
        p->value = strdup(value);

        p->next = head;
        head = p;

        table->arr[pos] = head;
        table->size++;
    }
}
const char *hashtable_get(hashtable_t *table, const char *key) {
    if (!is_hashtable_empty(table)) {
        int pos = times33(key) % table->capacity;
        // printf("get at pos=%d, key=%s\n", pos, key);
        hash_node_t *p = table->arr[pos];
        while (p) {
            // printf("p->key=%s\n", p->key);
            if (!strcmp(p->key, key)) {
                // puts("found it!");
                return p->value;
            }
            p = p->next;
        }
    }

    return NULL;
}

void hashtable_remove(hashtable_t *table, const char *key) {
    if (!is_hashtable_empty(table)) {
        int pos = times33(key) % table->capacity;

        hash_node_t *p = table->arr[pos];
        hash_node_t *prev = p;
        while (p) {
            if (!strcmp(p->key, key)) {
                free(p->key);
                free(p->value);

                if (p == prev) {
                    table->arr[pos] = p->next;
                } else {
                    prev->next = p->next;
                }
                free(p);
                table->size--;
            }
            prev = p;
            p = p->next;
        }
    }
}