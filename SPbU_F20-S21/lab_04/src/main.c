#include "clist.h"
#include "stdlib.h"
#include "stdio.h" 
#include "string.h"
#include "stddef.h"

#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

typedef struct point {
    int x, y;
    struct intrusive_node node;
} point_t;

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
      point_t *tmp = container_of(cur->next, point_t, node);
      if(tmp->x == x && tmp->y == y){
        remove_node(list, cur->next);
        free(tmp);
      }
      else
        cur = cur->next;
    }
}

void show_all_points(intrusive_list_t *list) {
    intrusive_node_t *cur = list->head;

    while(cur->next){
      point_t *tmp = container_of(cur->next, struct point, node);
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

    while(cur->next){
      struct point *tmp = container_of(cur->next, struct point, node);
      remove_node(list, cur->next);
      free(tmp);
    }
}

int main() {
	char *s = malloc(239 * sizeof(char));
    intrusive_list_t list;
    init_list(&list);

    while(1){
      scanf("%239s", s);
      if(!strcmp(s, "add")) {
        int x = 0, y = 0;
        scanf(" %d %d", &x, &y);
        add_point(&list, x, y);
      } else if(!strcmp(s, "rm")) {
        int x = 0, y = 0;
        scanf(" %d %d", &x, &y);
        remove_point(&list, x, y);
      } else if(!strcmp(s, "print")) {
        show_all_points(&list);
      } else if(!strcmp(s, "rma")) {
        remove_all_points(&list);
      } else if(!strcmp(s, "len")) {
        printf("%d\n", get_length(&list));
      } else if(!strcmp(s, "exit")) {
        break;
      } else {
        printf("Unknown command\n");
      }
    }

    remove_all_points(&list);
    free(s);
    free(list.head);
    return 0;
}
