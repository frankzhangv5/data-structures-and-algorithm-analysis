#include <adt/rbtree.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

rbtree_t *rbtree_init() {
    rbtree_node_t *nil = (rbtree_node_t *)malloc(sizeof(rbtree_node_t));
    assert(NULL != nil);

    nil->color = BLACK;
    nil->left = nil->right = nil->parent = NULL;

    rbtree_t *tree = (rbtree_t *)malloc(sizeof(rbtree_t));
    assert(NULL != tree);

    tree->root = tree->nil = nil;

    return tree;
}

static void right_rotate(rbtree_t *tree, rbtree_node_t *k2) {
    rbtree_node_t *k1 = k2->left;

    k2->left = k1->right;
    if (IS_NOT_NIL(tree, k2->left)) {
        k2->left->parent = k2;
    }

    k1->parent = k2->parent;
    if (IS_NIL(tree, k1->parent)) {
        tree->root = k1;
    } else if (IS_LEFT_CHILD(k1)) {
        k1->parent->left = k1;
    } else {
        k1->parent->right = k2;
    }

    k1->right = k2;
    k2->parent = k1;
}

static void left_rotate(rbtree_t *tree, rbtree_node_t *k2) {
    rbtree_node_t *k3 = k2->right;

    k2->right = k3->left;
    if (IS_NOT_NIL(tree, k2->right)) {
        k2->right->parent = k2;
    }

    k3->parent = k2->parent;

    if (IS_NIL(tree, k3->parent)) {
        tree->root = k3;
    } else if (IS_LEFT_CHILD(k3)) {
        k3->parent->left = k3;
    } else {
        k3->parent->right = k3;
    }

    k3->left = k2;
    k2->parent = k3;
}

static void handle_reorient(rbtree_t *tree, rbtree_node_t *x, int k) {
    x->color = RED;
    x->left->color = x->right->color = BLACK;

    if (IS_RED(x->parent)) {
        x->parent->parent->color = RED;

        if (IS_LEFT_CHILD(x->parent)) {
            if (k > x->parent->element) {
                x->color = BLACK;
                left_rotate(tree, x->parent);
                right_rotate(tree, x->parent);
            } else {
                x->parent->color = BLACK;
                right_rotate(tree, x->parent->parent);
            }
        } else {
            if (k < x->parent->element) {
                x->color = BLACK;

                right_rotate(tree, x->parent);
                left_rotate(tree, x->parent);
            } else {
                x->parent->color = BLACK;
                left_rotate(tree, x->parent->parent);
            }
        }
    }

    tree->root->color = BLACK;
}

rbtree_t *rbtree_insert(rbtree_t *tree, int k) {
    rbtree_node_t *x, *p;
    x = tree->root;
    p = x;

    while (x != tree->nil) {
        if (IS_RED(x->left) && IS_RED(x->right)) {
            handle_reorient(tree, x, k);
        }

        p = x;
        if (k < x->element) {
            x = x->left;
        } else if (k > x->element) {
            x = x->right;
        } else {
            return tree;
        }
    }

    x = (rbtree_node_t *)malloc(sizeof(rbtree_node_t));
    assert(NULL != x);

    x->element = k;
    x->color = RED;
    x->left = x->right = tree->nil;
    x->parent = p;

    if (IS_NIL(tree, tree->root)) {
        tree->root = x;
    } else if (k < p->element) {
        p->left = x;
    } else if (k > p->element) {
        p->right = x;
    }

    handle_reorient(tree, x, k);

    return tree;
}

static void swap(rbtree_t *tree, rbtree_node_t *old, rbtree_node_t *new) {
    if (IS_NIL(tree, old->parent))
        tree->root = new;
    else if (IS_LEFT_CHILD(old))
        old->parent->left = new;
    else
        old->parent->right = new;

    new->parent = old->parent;
}

static rbtree_node_t *find_min(rbtree_t *tree, rbtree_node_t *root) {
    if (IS_NIL(tree, root))
        return tree->nil;

    while (IS_NOT_NIL(tree, root->left)) {
        root = root->left;
    }

    return root;
}

rbtree_node_t *rbtree_find_min(rbtree_t *tree) {
    return find_min(tree, tree->root);
}

rbtree_t *rbtree_delete(rbtree_t *tree, int k) {
    assert(NULL != tree);

    rbtree_node_t *target = tree->root, *x;

    while (IS_NOT_NIL(tree, target) && k != target->element) {
        if (k < target->element)
            target = target->left;
        else if (k > target->element)
            target = target->right;
    }

    if (IS_NIL(tree, target)) {
        return tree;
    }

    if (IS_NOT_NIL(tree, target->left) && IS_NOT_NIL(tree, target->right)) {
        rbtree_node_t *min = find_min(tree, target->right);
        k = target->element = min->element;
        target = min;
    }

    if (IS_NIL(tree, target->left)) {
        x = target->right;
        swap(tree, target, target->right);
    } else if (IS_NIL(tree, target->right)) {
        x = target->left;
        swap(tree, target, target->left);
    }

    if (IS_BLACK(target)) {
        while (target != tree->root && IS_BLACK(target)) {
            if (IS_LEFT_CHILD(target)) {
                rbtree_node_t *w = target->parent->right;
                if (IS_RED(w)) {
                    w->color = BLACK;
                    w->parent->color = RED;
                    left_rotate(tree, target->parent);
                    w = target->parent->right;
                }

                if (IS_BLACK(w->left) && IS_BLACK(w->right)) {
                    if (IS_RED(target->parent)) {
                        target->parent->color = BLACK;
                        w->color = RED;
                        break;
                    } else {
                        w->color = RED;
                        target = target->parent;
                        continue;
                    }
                }

                if (IS_BLACK(w->right)) {
                    w->left->color = BLACK;
                    w->color = RED;
                    right_rotate(tree, w);
                    w = target->parent->right;
                }

                w->color = target->parent->color;
                target->parent->color = BLACK;
                w->right->color = BLACK;
                left_rotate(tree, target->parent);
                target = tree->root;
            } else {
                rbtree_node_t *w = target->parent->left;

                if (IS_RED(w)) {
                    w->color = BLACK;
                    w->parent->color = RED;
                    right_rotate(tree, target->parent);
                    w = target->parent->right;
                }

                if (IS_BLACK(w->left) && IS_BLACK(w->right)) {
                    if (IS_RED(target->parent)) {
                        target->parent->color = BLACK;
                        w->color = RED;
                        break;
                    } else {
                        target->parent->color = BLACK;
                        w->color = RED;
                        target = target->parent;
                        continue;
                    }
                }

                if (IS_BLACK(w->left)) {
                    w->right->color = BLACK;
                    w->color = RED;
                    w = target->parent->right;
                }

                w->color = w->parent->color;
                target->parent->color = BLACK;
                w->left->color = BLACK;
                right_rotate(tree, target->parent);
                target = tree->root;
            }
        }

        target->color = BLACK;
    }

    free(target);

    return tree;
}

static void dispose_rbtree_inner(rbtree_t *tree, rbtree_node_t *x) {
    if (x && IS_NOT_NIL(tree, x)) {
        dispose_rbtree_inner(tree, x->left);
        dispose_rbtree_inner(tree, x->right);

        free(x);
        x = NULL;
    }
}

void dispose_rbtree(rbtree_t *tree) {
    dispose_rbtree_inner(tree, tree->root);
    free(tree->nil);
}