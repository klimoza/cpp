#ifndef CLIST
#define CLIST

typedef struct point {
    int x, y;
} point;

typedef struct node {
    point p;
    struct node *prev;
    struct node *next;
} node_t;

typedef struct list {
    node_t *head;
} list_t;

void init_list(list_t *list);
void add_point(const list_t *list, int x, int y);
void remove_point(const list_t *list, int x, int y);
int get_length(const list_t *list);
void show_all_points(const list_t *list);
void remove_all_points(const list_t *list);

#endif
