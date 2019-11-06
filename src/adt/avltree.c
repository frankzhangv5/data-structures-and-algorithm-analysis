#include <adt/avltree.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define HEIGHT(node) ((node) == NULL ? -1 : node->height)

static avltree_node_t *single_rotate_with_left(avltree_node_t *k2) {
    avltree_node_t *k1 = k2->left;

    k2->left = k1->right;
    k1->right = k2;

    k2->height = MAX(HEIGHT(k2->left), HEIGHT(k2->right)) + 1;
    k1->height = MAX(HEIGHT(k1->left), k2->height) + 1;

    return k1;
}

static avltree_node_t *single_rotate_with_right(avltree_node_t *k1) {
    avltree_node_t *k2 = k1->right;

    k1->right = k2->left;
    k2->left = k1;

    k1->height = MAX(HEIGHT(k1->left), HEIGHT(k1->right)) + 1;
    k2->height = MAX(k1->height, HEIGHT(k2->right)) + 1;

    return k2;
}

static avltree_node_t *double_rotate_with_left(avltree_node_t *k3) {
    /* Rotate between K1 and K2 */
    k3->left = single_rotate_with_right(k3->left);

    /* Rotate between K3 and K2 */
    return single_rotate_with_left(k3);
}

static avltree_node_t *double_rotate_with_right(avltree_node_t *k1) {
    /* Rotate between K3 and K2 */
    k1->right = single_rotate_with_left(k1->right);

    /* Rotate between K1 and K2 */
    return single_rotate_with_right(k1);
}

avltree_node_t *insert_into_avltree(avltree_node_t *root, element_t e) {

    if (!root) {
        root = (avltree_node_t *)malloc(sizeof(avltree_node_t));
        if (!root) {
            perror("insert_into_tree");
            return NULL;
        }
        memset(root, 0, sizeof(avltree_node_t));
        root->element = e;
    } else if (root->element > e) {
        root->left = insert_into_avltree(root->left, e);
        if (HEIGHT(root->left) - HEIGHT(root->right) == 2) {
            if (root->left->element > e) {
                root = single_rotate_with_left(root);
            } else {
                root = double_rotate_with_left(root);
            }
        }
    } else if (root->element < e) {
        root->right = insert_into_avltree(root->right, e);
        if (HEIGHT(root->right) - HEIGHT(root->left) == 2) {
            if (root->right->element < e) {
                root = single_rotate_with_right(root);
            } else {
                root = double_rotate_with_right(root);
            }
        }
    } else {
        fprintf(stderr, "duplcated item ~\n");
    }

    root->height = MAX(HEIGHT(root->left), HEIGHT(root->right)) + 1;
    return root;
}
avltree_node_t *find_avltree_node(avltree_node_t *root, element_t e) {
    if (root) {
        if (root->element == e) {
            return root;
        } else if (root->element > e) {
            return find_avltree_node(root->left, e);
        } else if (root->element < e) {
            return find_avltree_node(root->right, e);
        }
    }
    return NULL;
}
avltree_node_t *find_avltree_min(avltree_node_t *root) {
    if (root) {
        if (root->left)
            return find_avltree_min(root->left);
        return root;
    }
    return NULL;
}
avltree_node_t *find_avltree_max(avltree_node_t *root) {
    if (root) {
        if (root->right)
            return find_avltree_max(root->right);
        return root;
    }
    return NULL;
}

void destroy_avltree(avltree_node_t *root) {
    if (root) {
        destroy_avltree(root->left);
        destroy_avltree(root->right);
        free(root);
        root = NULL;
    }
}
