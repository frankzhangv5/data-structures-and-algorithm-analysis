#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ui/ui.h>

#define NELEM(x) (sizeof(x) / sizeof(x[0]))

static void help(const char *proc) {
    fprintf(stderr, "Usage:\n\t%s [bst|avltree|rbtree]\n", proc);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    int nodes[] = {63, 47, 58, 88, 37, 32, 29, 99, 43, 42,
                   71, 89, 32, 29, 99, 33, 44, 55, 66, 45};
    int i;

    if (argc < 2) {
        help(argv[0]);
    }

    const char *type = argv[1];

    if (!strcmp("bst", type)) {
        tree_node_t *root = NULL;
        int i;
        for (i = 0; i < NELEM(nodes); i++) {
            root = insert_into_tree(root, nodes[i]);
        }
        draw_binary_search_tree(root);
        destroy_tree(root);
    } else if (!strcmp("avltree", type)) {
        avltree_node_t *root = NULL;
        int i;
        for (i = 0; i < NELEM(nodes); i++) {
            root = insert_into_avltree(root, nodes[i]);
        }
        draw_avltree(root);
        destroy_avltree(root);
    } else if (!strcmp("rbtree", type)) {
        rbtree_t *tree = rbtree_init();
        int i;
        for (i = 0; i < NELEM(nodes); i++) {
            tree = rbtree_insert(tree, nodes[i]);
        }
        draw_rbtree(tree);
        dispose_rbtree(tree);
    } else {
        help(argv[0]);
    }

    return 0;
}