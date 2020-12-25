#ifndef STEGANOGRAPHY
#define STEGANOGRAPHY

#include "bmp.h"

typedef struct KEY {
    int x, y;
    char col;
} Key;

int read_key(Key *key, int number_of_bits_for_one_char, FILE *f);
int add_char(bmp_file *image, const Key *keys, char c, int number_of_bits_for_one_char);
char get_char(const bmp_file *image, const Key *keys, int number_of_bits_for_one_char);

#endif
