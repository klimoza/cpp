#include "assert.h"
#include "string.h"
#include "stdlib.h"
#include "bmp.h"
#include "stego.h"

void free_memory(const bmp_file *image) {
    free(image->data);
}

void free_all(FILE *f1, FILE *f2, const bmp_file *image){
    fclose(f1);
    fclose(f2);
    free_memory(image);
}

int crop_rotate(int argc, char** argv) {
    if(argc != 8)
        return -1;

    FILE *fin = fopen(argv[2], "rb");
    if(fin == NULL)
        return -1;

    bmp_file image;
    if(load_bmp(&image, fin)) {
        fclose(fin);
        return -1;
    }

    fclose(fin);

    int x = atoi(argv[4]);
    int y = atoi(argv[5]);
    int w = atoi(argv[6]);
    int h = atoi(argv[7]);
    if(x < 0 || w <= 0 || x + w > (int)image.bmp_info_header.biWidth) {
        free_memory(&image);
        return -1;
    }
    if(y < 0 || h <= 0 || y + h > (int)image.bmp_info_header.biHeight) {
        free_memory(&image);
        return -1;
    }

    bmp_file cropped_image;
    if(crop(image, &cropped_image, x, y, w, h)) {
        free_memory(&image);
        return -1;
    }
    free_memory(&image);

    bmp_file rotated_image;
    if(rotate(cropped_image, &rotated_image)) {
        free_memory(&cropped_image);
        return -1;
    }
    free_memory(&cropped_image);

    FILE *fout = fopen(argv[3], "wb");
    if(fout == NULL) {
        free_memory(&rotated_image);
        return -1;    
    }

    save_bmp(rotated_image, fout);

    free_memory(&rotated_image);
    fclose(fout);
    return 0;
}

int insert(int argc, char** argv) {
    const int number_of_bits_for_one_char = 5;

    if(argc != 6)
        return -1;

    FILE *fin = fopen(argv[2], "rb");
    if(fin == NULL)
        return -1;

    bmp_file image;
    if(load_bmp(&image, fin)) {
        fclose(fin);
        return -1;
    }

    fclose(fin);

    FILE *f_key = fopen(argv[4], "r"); 
    FILE *f_msg = fopen(argv[5], "r");

    char c;
    while(fscanf(f_msg, "%c", &c) != EOF) {
        Key keys[number_of_bits_for_one_char];

        if(read_key(keys, number_of_bits_for_one_char, f_key)) {
            free_all(f_key, f_msg, &image);
            return -1;
        }

        if(add_char(&image, keys, c, number_of_bits_for_one_char)) {
            free_all(f_key, f_msg, &image);
            return -1;
        } 
    }

    FILE *fout = fopen(argv[3], "wb");
    if(fout == NULL) {
        free_all(f_key, f_msg, &image);
        return -1;
    }

    save_bmp(image, fout);

    fclose(fout);
    free_all(f_key, f_msg, &image);
    return 0;
}

int extract(int argc, char** argv) {
    const int number_of_bits_for_one_char = 5;

    if(argc != 5)
        return -1;

    FILE *fin = fopen(argv[2], "rb");
    if(fin == NULL)
        return -1;

    bmp_file image;
    if(load_bmp(&image, fin)) { 
        fclose(fin);
        return -1;
    }
    fclose(fin);

    FILE *f_key = fopen(argv[3], "r");
    FILE *f_msg = fopen(argv[4], "w");

    Key keys[number_of_bits_for_one_char];
    while(!read_key(keys, number_of_bits_for_one_char, f_key)) {
        char c = get_char(&image, keys, number_of_bits_for_one_char); 
        
        if(!c) {
            free_all(f_key, f_msg, &image);
            return -1;
        }

        fprintf(f_msg, "%c", c);
    }
    fprintf(f_msg, "\n");

    free_all(f_key, f_msg, &image);
    return 0;
}

int main(int argc, char** argv) {
    if(argc < 3)
        return -1;

    if(!strcmp(argv[1], "crop-rotate")) {
        if(crop_rotate(argc, argv))
            return -1;
    } else if(!strcmp(argv[1], "insert")) {
        if(insert(argc, argv))
            return -1;
    } else if(!strcmp(argv[1], "extract")) {
        if(extract(argc, argv))
            return -1;
    } else {
        return -1;
    }

    return 0;
}
