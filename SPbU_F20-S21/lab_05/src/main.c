#include "point_list.h"
#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "stdbool.h"
#include "string.h"

void print(intrusive_node_t *node, void *data) {
    point_t *point = get_point(node);
    printf((char*)data, point->x, point->y);
}

void count(intrusive_node_t *node, void *data) {
    if(node != NULL)
        (*(int*)data)++;
}

int main(int argc, char** argv) {
    assert(argc > 2);
    const size_t bin_size = 3;

    intrusive_list_t list;
    intrusive_list_t *l = &list;
    init_list(l);

    FILE *f;
    if(!strcmp(argv[1], "loadtext")) {
        f = fopen(argv[2], "r");
        int x = 0, y = 0;
        while(fscanf(f, "%d %d", &x, &y) != EOF)
            add_point(l, x, y);
    } else {
        f = fopen(argv[2], "rb");
        int x = 0, y = 0;
        while(fread(&x, bin_size, 1, f) == 1 && fread(&y, bin_size, 1, f) == 1)
            add_point(l, x, y);
    }
    fclose(f);

    if(!strcmp(argv[3], "savetext") || !strcmp(argv[3], "savebin")) {
        bool isBin = !strcmp(argv[3], "savebin");
        if(!isBin)
            f = fopen(argv[4], "w");
        else
            f = fopen(argv[4], "wb");

        intrusive_node_t* cur = l->head;
        while(cur->next) {
            point_t* point = get_point(cur->next);
            if(!isBin)
                fprintf(f, "%d %d\n", point->x, point->y);
            else {
                fwrite(&point->x, bin_size, 1, f);
                fwrite(&point->y, bin_size, 1, f);
            }
            cur = cur->next; 
        }
        fclose(f);
    } else if(!strcmp(argv[3], "print")) {
        apply(l, (*print), argv[4]);
        printf("\n");
    } else {
        int cnt = 0;
        apply(l, (*count), &cnt);
        printf("%d\n", cnt);
    }

    remove_all_points(l);
    free(l->head);
    return 0;
}
