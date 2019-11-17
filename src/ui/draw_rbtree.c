#include <ncurses.h>
#include <ui/ui.h>

extern void draw_h_line(int y, int start_x, int end_x);
extern void adjust(tree_node_t *root);
extern void validate(tree_node_t *node, int max_cols, int max_rows);
extern void layout(tree_node_t *root, point_t start, point_t shift);
extern void do_traverse(void *root, visit_callback_t visit);

static void process_nil_node(rbtree_node_t *root, rbtree_node_t *nil) {
    if (root) {
        process_nil_node(root->left, nil);
        process_nil_node(root->right, nil);

        if (root->left == nil)
            root->left = NULL;

        if (root->right == nil)
            root->right = NULL;
    }
}

static void draw_rbtree_node(rbtree_node_t *node) {
    if (!node)
        return;

    attron(COLOR_PAIR(IS_RED(node) ? COLOR_RED : COLOR_BLACK));
    mvprintw(node->point.y, node->point.x, "[");
    printw("%d", node->element);
    printw("]");
    attroff(COLOR_PAIR(IS_RED(node) ? COLOR_RED : COLOR_BLACK));

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
    } else {
        int y = node->point.y;
        int x = node->point.x;
        mvprintw(y + 1, x + 1, "/");
        attron(COLOR_PAIR(COLOR_BLACK));
        mvprintw(y + 2, x - 2, "nil");
        attroff(COLOR_PAIR(COLOR_BLACK));
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
    } else {
        int y = node->point.y;
        int x = node->point.x;
        mvprintw(y + 1, x + 2, "\\");
        attron(COLOR_PAIR(COLOR_BLACK));
        mvprintw(y + 2, x + 3, "nil");
        attroff(COLOR_PAIR(COLOR_BLACK));
    }
}

void draw_rbtree(rbtree_t *tree) {
    if (!tree)
        return;

    process_nil_node(tree->root, tree->nil);

    tree_node_t *root = (tree_node_t *)(tree->root);

    initscr();
    curs_set(0);
    start_color(); /* Start color 			*/
    init_pair(COLOR_BLACK, COLOR_BLACK, COLOR_WHITE);
    init_pair(COLOR_RED, COLOR_WHITE, COLOR_RED);

    point_t root_point = {.y = 1, .x = COLS / 2};
    point_t root_shift = {.y = 0, .x = 0};
    layout(root, root_point, root_shift);
    adjust(root);
    validate(root, COLS, LINES);
    do_traverse(root, (visit_callback_t)draw_rbtree_node);

    refresh();
    getch();
    endwin();
}
