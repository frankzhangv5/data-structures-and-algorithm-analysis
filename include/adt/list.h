#ifndef _LIST_H_
#define _LIST_H_

#include "type.h"
#include <stdbool.h>

typedef singly_linked_node_t list_node_t;
typedef list_node_t *list_t;
typedef list_node_t *position_t;

list_t create_list();
void dispose_list(list_t list);
void make_list_empty(list_t list);
bool is_list_empty(list_t list);
position_t find(list_t list, element_t e);
position_t find_prev(list_t list, element_t e);
bool insert(position_t p, element_t e);
void drop(list_t list, element_t e);
position_t header(list_t list);
position_t first(list_t list);
element_t retrieve(position_t p);

#endif /* _LIST_H_ */
