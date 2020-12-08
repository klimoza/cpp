#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "point_list.h"

#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

point_t* get_point(intrusive_node_t *node) {
    return container_of(node, struct point, node);
}

void add_point(intrusive_list_t *list, int x, int y) {
    point_t *p = malloc(sizeof(point_t));
    p->x = x;
    p->y = y;
    p->node.prev = NULL;
    p->node.next = NULL;
    add_node(list, &(p->node));
}

void remove_point(intrusive_list_t *list, int x, int y) {
    intrusive_node_t *cur = list->head;

    while(cur->next) {
      point_t *tmp = get_point(cur->next);
      if(tmp->x == x && tmp->y == y) {
        remove_node(list, cur->next);
        free(tmp);
      }
      else
        cur = cur->next;
    }
}

void show_all_points(intrusive_list_t *list) {
    intrusive_node_t *cur = list->head;

    while(cur->next) {
      point_t *tmp = get_point(cur->next);
      if(cur->next->next)
        printf("(%d %d) ", tmp->x, tmp->y);
      else
        printf("(%d %d)", tmp->x, tmp->y);
      cur = cur->next;
    }
    printf("\n");
}

void remove_all_points(intrusive_list_t *list) {
    intrusive_node_t *cur = list->head;

    while(cur->next) {
      point_t *tmp = get_point(cur->next);
      remove_node(list, cur->next);
      free(tmp);
    }
}