#ifndef _BST_H_
#define _BST_H_

#include <string.h>

#include "type.h"

typedef struct _list_node {
    tree_node_t *node;
    struct _list_node *next;
} list_node_t;

#define INSERT_INTO_LIST(list, val)                                            \
    do {                                                                       \
        list_node_t *p = (list_node_t *)malloc(sizeof(list_node_t));           \
        memset(p, 0, sizeof(list_node_t));                                     \
        p->node = val;                                                         \
        p->next = list;                                                        \
        list = p;                                                              \
    } while (0)

#define LIST_HEAD(list) (list)

#define LIST_POP(list)                                                         \
    do {                                                                       \
        if (list) {                                                            \
            list_node_t *tmp = list;                                           \
            list = tmp->next;                                                  \
            free(tmp);                                                         \
            tmp = NULL;                                                        \
        }                                                                      \
    } while (0)

typedef void (*visit_callback_t)(tree_node_t *node);
typedef void (*level_visit_callback_t)(tree_node_t *node, int level);
tree_node_t *insert_into_tree(tree_node_t *root, element_t e);
void preorder_traverse(tree_node_t *root, visit_callback_t visit);
void inorder_traverse(tree_node_t *root, visit_callback_t visit);
void postorder_traverse(tree_node_t *root, visit_callback_t visit);
void levelorder_traverse(tree_node_t *root, level_visit_callback_t visit);
tree_node_t *find_tree_node(tree_node_t *root, element_t e);
tree_node_t *find_min(tree_node_t *root);
tree_node_t *find_max(tree_node_t *root);
tree_node_t *delete_tree_node(tree_node_t *root, element_t e);
void destroy_tree(tree_node_t *root);
element_t get_value(tree_node_t *node);

#endif