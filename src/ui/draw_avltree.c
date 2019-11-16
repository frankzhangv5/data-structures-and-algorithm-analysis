#include <ui/ui.h>

extern void draw_tree(tree_node_t *root);

void draw_avltree(avltree_node_t *root) { draw_tree((tree_node_t *)root); }