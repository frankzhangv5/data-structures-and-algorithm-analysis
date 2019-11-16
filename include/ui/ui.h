#ifndef _UI_H_
#define _UI_H_

#include <adt/avltree.h>
#include <adt/bst.h>
#include <adt/rbtree.h>

void draw_tree(tree_node_t *root);

void draw_binary_search_tree(tree_node_t *root);
void draw_avltree(avltree_node_t *root);
void draw_rbtree(rbtree_t *tree);

#endif