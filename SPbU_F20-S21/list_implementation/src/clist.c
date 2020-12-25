#include "clist.h"
#include "stdlib.h"
#include "stdbool.h"
#include "stdio.h"

static bool eq(point a, point b) {
    return ((a.x == b.x) && (a.y == b.y));
}

static node_t *set_node(point p) {
    node_t *r = malloc(sizeof(node_t));
    r->p.x = p.x;
    r->p.y = p.y;
    r->prev = NULL;
    r->next = NULL;
}

static void print_point(point p){
    printf("(%d %d) ", p.x, p.y);
}

void init_list(list_t *list) {
    point p = {-1, -1};
    list->head = set_node(p);
}

void add_point(const list_t *list, int x, int y) {
    point p = {x, y};
    node_t *cur = list->head;

    while(cur->next != NULL)
        cur = cur->next;

    cur->next = set_node(p);
    cur->next->prev = cur;
}

void remove_point(const list_t *list, int x, int y) {
    point p = {x, y};
    node_t *cur = list->head;
    
    while(cur->next != NULL) {
        if(eq(cur->next->p, p)) {
            node_t *tmp = cur->next->next;
            free(cur->next);
            cur->next = tmp;
            if(tmp != NULL)
                tmp->prev = cur;
        } else {
            cur = cur->next;
        }
    }
}

int get_length(const list_t *list) {
    node_t *cur = list->head;
    int ans = 0;

    while(cur->next != NULL) {
        ans++;
        cur = cur->next;
    }
    return ans;
}

void show_all_points(const list_t *list) {
    node_t *cur = list->head;

    while(cur->next != NULL){
        print_point(cur->next->p);
        cur = cur->next;
    }
    printf("\n");
}

void remove_all_points(const list_t* list) {
    node_t *cur = list->head;
    while(cur->next != NULL) {
        node_t *tmp = cur->next->next;
        free(cur->next);
        cur->next = tmp;
        if(tmp != NULL)
            tmp->prev = cur;
    }
}
