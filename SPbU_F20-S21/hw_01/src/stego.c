#include "stego.h"
#include "ctype.h"

static int char_to_id(char c) {
    switch(c) {
        case ',':
            return 28;
        case '.':
            return 27;
        case ' ':
            return 26;  
        default:
            if(isupper(c))
               return (c - 'A');
            else
               return -1;
    }
}

static char id_to_char(int x) {
    switch(x) { 
        case 28:
            return ',';
        case 27:
            return '.';
        case 26:
            return ' ';
        default:
            if(x <= 25)
                return ('A' + x);
            else
                return 0;
    }
}

static int get_last_bit(char c){
    return (c & 1);
}

static void replace_last_bit(char *c, int x) {
    *c = (*c) - get_last_bit(*c) + x;
}

static int check_key(const bmp_file *image, Key key){
    if(key.x < 0 || key.x >= (int)image->bmp_info_header.biWidth)
        return -1;
    if(key.y < 0 || key.y >= (int)image->bmp_info_header.biHeight)
        return -1;
    return 0;
}

int read_key(Key *keys, int number_of_bits_for_one_char, FILE *f) {
    for(int i = 0; i < number_of_bits_for_one_char; i++) {
        if(fscanf(f, "%d %d %c", &(keys[i].x), &(keys[i].y), &(keys[i].col)) == EOF)
            return -1;
    }
    return 0;
}

int add_char(bmp_file *image, const Key *keys, char c, int number_of_bits_for_one_char) {
    int x = char_to_id(c);

    for(int i = 0; i < number_of_bits_for_one_char; i++) {
        if(check_key(image, keys[i]))
            return -1;

        int current_bit = get_last_bit(x >> i);

        switch(keys[i].col) {
            case 'R':
                replace_last_bit(&(image->data[keys[i].x][keys[i].y].R), current_bit);
                break;
            case 'G':
                replace_last_bit(&(image->data[keys[i].x][keys[i].y].G), current_bit);
                break;
            case 'B':
                replace_last_bit(&(image->data[keys[i].x][keys[i].y].B), current_bit);
                break;
            default:
                return -1; 
        } 
    }
    return 0;
}

char get_char(const bmp_file *image, const Key *keys, int number_of_bits_for_one_char) {
    int id = 0;

    for(int i = 0; i < number_of_bits_for_one_char; i++) {
        if(check_key(image, keys[i]))
            return 0;

        switch(keys[i].col) {
            case 'R':
                id += (get_last_bit(image->data[keys[i].x][keys[i].y].R)) << i;
                break;
            case 'G':
                id += (get_last_bit(image->data[keys[i].x][keys[i].y].G)) << i;
                break;
            case 'B':
                id += (get_last_bit(image->data[keys[i].x][keys[i].y].B)) << i;
                break;
            default:
                return 0;
        }
    }
    return id_to_char(id);
}
