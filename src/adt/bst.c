#include <adt/bst.h>
#include <stdio.h>
#include <stdlib.h>

tree_node_t *insert_into_tree(tree_node_t *root, element_t e) {
    if (!root) {
        root = (tree_node_t *)malloc(sizeof(tree_node_t));
        if (!root) {
            perror("insert_into_tree");
            return NULL;
        }
        memset(root, 0, sizeof(tree_node_t));
        root->element = e;
    } else if (root->element > e) {
        root->left = insert_into_tree(root->left, e);
    } else if (root->element < e) {
        root->right = insert_into_tree(root->right, e);
    } else {
        fprintf(stderr, "duplcated item ~\n");
    }

    return root;
}

void preorder_traverse(tree_node_t *root, visit_callback_t visit) {
    if (root) {
        visit(root);
        preorder_traverse(root->left, visit);
        preorder_traverse(root->right, visit);
    }
}
void inorder_traverse(tree_node_t *root, visit_callback_t visit) {
    if (root) {
        inorder_traverse(root->left, visit);
        visit(root);
        inorder_traverse(root->right, visit);
    }
}
void postorder_traverse(tree_node_t *root, visit_callback_t visit) {
    if (root) {
        postorder_traverse(root->left, visit);
        postorder_traverse(root->right, visit);
        visit(root);
    }
}
void levelorder_traverse(tree_node_t *root, level_visit_callback_t visit) {
    if (root) {
        list_node_t *curr_list, *next_list;
        curr_list = next_list = NULL;
        INSERT_INTO_LIST(curr_list, root);
        int level = 0;

        do {
            if (LIST_HEAD(next_list) != NULL) {
                curr_list = next_list;
                next_list = NULL;
            }
            level++;
            while (LIST_HEAD(curr_list)) {
                list_node_t *head = LIST_HEAD(curr_list);
                visit(head->node, level);
                if (head->node && head->node->left) {
                    INSERT_INTO_LIST(next_list, head->node->left);
                }

                if (head->node && head->node->right) {
                    INSERT_INTO_LIST(next_list, head->node->right);
                }
                LIST_POP(curr_list);
            }

        } while (LIST_HEAD(next_list));
    }
}
tree_node_t *find_tree_node(tree_node_t *root, element_t e) {
    if (root) {
        if (root->element == e) {
            return root;
        } else if (root->element > e) {
            return find_tree_node(root->left, e);
        } else if (root->element < e) {
            return find_tree_node(root->right, e);
        }
    }
    return NULL;
}
tree_node_t *find_min(tree_node_t *root) {
    if (root) {
        if (root->left)
            return find_min(root->left);
        return root;
    }
    return NULL;
}
tree_node_t *find_max(tree_node_t *root) {
    if (root) {
        if (root->right)
            return find_max(root->right);
        return root;
    }
    return NULL;
}
tree_node_t *delete_tree_node(tree_node_t *root, element_t e) {
    if (root) {
        if (root->element == e) {
            if (root->left && root->right) {
                tree_node_t *tmp = find_min(root->right);
                root->element = tmp->element;
                root->right = delete_tree_node(root->right, root->element);
            } else {
                tree_node_t *tmp = root;
                if (!root->left) {
                    root = root->right;
                } else if (!root->right) {
                    root = root->left;
                }
                free(tmp);
            }
        } else if (root->element > e) {
            root->left = delete_tree_node(root->left, e);
        } else if (root->element < e) {
            root->right = delete_tree_node(root->right, e);
        }
        return root;
    }
    return NULL;
}
element_t get_value(tree_node_t *node) {
    if (node)
        return node->element;
    return -1;
}
void destroy_tree(tree_node_t *root) {
    if (root) {
        destroy_tree(root->left);
        destroy_tree(root->right);
        free(root);
        root = NULL;
    }
}
