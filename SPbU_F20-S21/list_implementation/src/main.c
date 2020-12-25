#include "clist.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main() {
    list_t list;
    init_list(&list);

    char *s = malloc(239 * sizeof(char));
    while(1) {
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
    free(list.head);
    free(s);
    return 0;
}
