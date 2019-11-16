#include <ncurses.h>
#include <ui/ui.h>

static void shift_x(tree_node_t *node, int shift) {
    if (node) {
        node->point.x += shift;
        shift_x(node->left, shift);
        shift_x(node->right, shift);
    }
}

static void adjust_tree(tree_node_t *node, tree_node_t *root) {
    if (node && root) {
        adjust_tree(node->left, root);
        adjust_tree(node->right, root);

        int delta_x = node->point.x - root->point.x;
        int delta_y = node->point.y - root->point.y;
        if (node->element < root->element) {  // left subtree
            if (delta_x > 0 || (0 == delta_x &&
                                delta_y > 0)) {  // conflict, need shift subtree
                shift_x(root->left, -delta_x - 4);
            }
        }

        if (node->element > root->element) {  // right subtree
            if (delta_x < 0 || (0 == delta_x &&
                                delta_y > 0)) {  // conflict, need shift subtree
                shift_x(root->right, -delta_x + 4);
            }
        }
    }
}
void adjust(tree_node_t *root) {
    if (root) {
        adjust(root->left);
        adjust(root->right);
        adjust_tree(root, root);
    }
}

void validate(tree_node_t *node, int max_cols, int max_rows) {
    if (node) {
        int x = node->point.x;
        int y = node->point.y;
        if (x < 0) {
            x = 0;
        }
        if (x > max_cols) {
            x = max_cols;
        }
        if (y < 0) {
            y = 0;
        }
        if (y > max_rows) {
            y = max_rows;
        }

        node->point.x = x;
        node->point.y = y;

        validate(node->left, max_cols, max_rows);
        validate(node->right, max_cols, max_rows);
    }
}

static point_t left_shift = {.y = 4, .x = -6};
static point_t right_shift = {.y = 4, .x = 6};
void layout(tree_node_t *root, point_t start, point_t shift) {
    if (root) {
        root->point = start;
        root->point.x += shift.x;
        root->point.y += shift.y;

        layout(root->left, root->point, left_shift);
        layout(root->right, root->point, right_shift);
    }
}

void draw_h_line(int y, int start_x, int end_x) {
    int i = start_x;
    do {
        mvprintw(y, i, "_");
        i++;
    } while (i <= end_x);
}

static void draw_node(tree_node_t *node) {
    if (!node)
        return;

    mvprintw(node->point.y, node->point.x, "[");
    printw("%d", get_value(node));
    printw("]");

    if (node->left) {
        int y = node->point.y + 1;
        int x_start = node->point.x + 1;
        int x_end = node->left->point.x + 2;
        int x_mid = (x_start + x_end) / 2;
        mvprintw(y, x_start, "/");
        draw_h_line(y, x_mid + 1, x_start - 1);
        mvprintw(++y, x_mid, "/");
        draw_h_line(y, x_end + 1, x_mid - 1);
        mvprintw(++y, x_end, "/");
    }

    if (node->right) {
        int y = node->point.y + 1;
        int x_start = node->point.x + 2;
        int x_end = node->right->point.x + 1;
        int x_mid = (x_start + x_end) / 2;
        mvprintw(y, x_start, "\\");
        draw_h_line(y, x_start + 1, x_mid - 1);
        mvprintw(++y, x_mid, "\\");
        draw_h_line(y, x_mid + 1, x_end - 1);
        mvprintw(++y, x_end, "\\");
    }
}

void do_traverse(void *root, visit_callback_t visit) {
    if (root) {
        visit(root);
        do_traverse(((tree_node_t *)root)->left, visit);
        do_traverse(((tree_node_t *)root)->right, visit);
    }
}

void draw_tree(tree_node_t *root) {
    if (!root)
        return;
    initscr();
    curs_set(0);
    point_t root_point = {.y = 1, .x = COLS / 2};
    point_t root_shift = {.y = 0, .x = 0};
    layout(root, root_point, root_shift);
    adjust(root);
    validate(root, COLS, LINES);
    do_traverse(root, draw_node);
    refresh();
    getch();
    endwin();
}

void draw_other_tree(tree_node_t *root, visit_callback_t draw_other_node) {
    if (!root)
        return;
    initscr();
    curs_set(0);
    point_t root_point = {.y = 1, .x = COLS / 2};
    point_t root_shift = {.y = 0, .x = 0};
    layout(root, root_point, root_shift);
    adjust(root);
    validate(root, COLS, LINES);
    do_traverse(root, draw_other_node);
    refresh();
    getch();
    endwin();
}