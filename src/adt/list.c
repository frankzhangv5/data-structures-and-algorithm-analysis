#include <adt/list.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

list_t create_list() {
    list_t list = (list_node_t *)malloc(sizeof(list_node_t));
    if (!list) {
        perror("create_list");
        return NULL;
    }
    memset(list, 0, sizeof(list_node_t));
    return list;
}

void dispose_list(list_t list) {
    assert(NULL != list);

    make_list_empty(list);
    free(list);
    list = NULL;
}
void make_list_empty(list_t list) {
    assert(NULL != list);

    position_t p = first(list);
    while (p) {
        position_t tmp = p;
        p = p->next;
        free(tmp);
    }
}
bool is_list_empty(list_t list) {
    assert(NULL != list);

    if (NULL == list->next)
        return true;
    return false;
}
position_t find(list_t list, element_t e) {
    assert(NULL != list);

    position_t p = first(list);
    while (p) {
        if (p->element == e) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}
position_t find_prev(list_t list, element_t e) {
    assert(NULL != list);

    position_t p = first(list);
    position_t prev = header(list);
    while (p) {
        if (p->element == e) {
            return prev;
        }
        prev = p;
        p = p->next;
    }
    return NULL;
}

bool insert(position_t p, element_t e) {
    assert(NULL != p);

    position_t n = (list_node_t *)malloc(sizeof(list_node_t));
    if (!n) {
        perror("insert");
        return false;
    }

    memset(n, 0, sizeof(list_node_t));

    n->element = e;
    n->next = p->next;
    p->next = n;
    return true;
}

void drop(list_t list, element_t e) {
    assert(NULL != list);

    position_t p = first(list);
    position_t prev = header(list);
    while (p) {
        position_t tmp = p;
        if (tmp->element == e) {
            prev->next = tmp->next;
            p = tmp->next;
            free(tmp);
            tmp = NULL;
            continue;
        }
        prev = p;
        p = p->next;
    }
}

position_t header(list_t list) {
    assert(NULL != list);
    return list;
}

position_t first(list_t list) {
    assert(NULL != list);

    return list->next;
}

element_t retrieve(position_t p) {
    assert(NULL != p);
    return p->element;
}
