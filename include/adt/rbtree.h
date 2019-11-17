/**
 *
 红黑树是每个结点都带有颜色属性的二叉查找树，颜色为红色或黑色。在二叉查找树强制一般要求以外，对于任何有效的红黑树我们增加了如下的额外要求：

列表项结点是红色或黑色。
根是黑色。
所有叶子都是黑色（叶子是NIL结点）。
每个红色结点必须有两个黑色的子结点。（从每个叶子到根的所有路径上不能有两个连续的红色结点。）
从任一结点到其每个叶子的所有简单路径都包含相同数目的黑色结点。
为了便于处理红黑树中的边界情况，使用一个哨兵来代表所有的NIL结点，也就是说所有指向NIL的指针都指向哨兵T.nil。
 *
版权声明：本文为CSDN博主「weewqrer」的原创文章，遵循 CC 4.0 BY-SA
版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/weewqrer/article/details/51866488
 */
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
