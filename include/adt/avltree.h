#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

#include "type.h"

typedef struct avltree_node {
    element_t element;
    struct avltree_node *left;
    struct avltree_node *right;
    int height;
    point_t point;
} avltree_node_t;

typedef avltree_node_t *avltree_t;

avltree_node_t *insert_into_avltree(avltree_node_t *root, element_t e);
avltree_node_t *find_avltree_node(avltree_node_t *root, element_t e);
avltree_node_t *find_avltree_min(avltree_node_t *root);
avltree_node_t *find_avltree_max(avltree_node_t *root);
void destroy_avltree(avltree_node_t *root);

#endif