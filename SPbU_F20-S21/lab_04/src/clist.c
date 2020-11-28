#include "clist.h"
#include "stdlib.h"

void init_list(intrusive_list_t *list) {
	list->head = malloc(sizeof(intrusive_node_t));
	list->head->prev = NULL;
	list->head->next = NULL;
}

void add_node(intrusive_list_t *list, intrusive_node_t *node) {
	intrusive_node_t *cur = list->head;

	if(cur->next) {
		node->next = cur->next;
		cur->next->prev = node;
	}
	node->prev = cur;
	cur->next = node;
}

void remove_node(intrusive_list_t *list, intrusive_node_t *node) {
	intrusive_node_t *tmp = node->prev;

	tmp->next = node->next;
	if(node->next)
		node->next->prev = tmp;
}

int get_length(intrusive_list_t *list) {
	intrusive_node_t *cur = list->head;
	int cnt = 0;

	while(cur->next) {
		cnt++;
		cur = cur->next;
	}
	return cnt;
}