#ifndef _RB_TREE_H_
#define _RB_TREE_H_

#include "type.h"

typedef enum color {
    RED = 0,
    BLACK,
} color_t;

typedef struct rbtree_node {
    element_t element;
    struct rbtree_node *left, *right;
    point_t point;
    struct rbtree_node *parent;
    color_t color;
} rbtree_node_t;

typedef struct rbtree {
    rbtree_node_t *root;
    rbtree_node_t *nil;
} rbtree_t;

#define IS_NOT_NIL(tree, node) (node != tree->nil)
#define IS_NIL(tree, node) (node == tree->nil)
#define IS_LEFT_CHILD(node) (node->element < node->parent->element)
#define IS_RED(node) (RED == node->color)
#define IS_BLACK(node) (BLACK == node->color)

#define P(x) (x->parent)
#define GP(x) (x->parent->parent)
#define GGP(x) (x->parent->parent->parent)
#define LCHILD(x) (x->left)
#define RCHILD(x) (x->right)

rbtree_t *rbtree_init();
rbtree_t *rbtree_insert(rbtree_t *tree, int k);
rbtree_node_t *rbtree_find_min(rbtree_t *tree);
rbtree_t *rbtree_delete(rbtree_t *tree, int k);
void dispose_rbtree(rbtree_t *tree);

#endif
