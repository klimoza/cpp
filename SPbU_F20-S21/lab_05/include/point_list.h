#ifndef POINT_LIST_H_
#define POINT_LIST_H_

#include "clist.h"

typedef struct point {
    int x, y;
    struct intrusive_node node;
} point_t;

point_t* get_point(intrusive_node_t *node);

void remove_point(intrusive_list_t *list, int x, int y);

void add_point(intrusive_list_t *list, int x, int y);

void show_all_points(intrusive_list_t *list);

void remove_all_points(intrusive_list_t *list);

#endif
