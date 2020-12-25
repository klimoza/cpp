#include "bmp.h"
#include "stdlib.h"
#include "string.h"

static int padding_size(int width) {
    return width % 4;
}

static int make_array(const pixel ***data, int w, int h) {
    (*data) = malloc(h * sizeof(pixel*) + h * w * sizeof(pixel));
    if((*data) == NULL)
        return -1;

    (*data)[0] = (pixel*)(*data + h);
    for(int i = 1; i < h; i++)
        (*data)[i] = (*data)[i - 1] + w;

    return 0;
}

static void update_info(bmp_file *image, int w, int h) {
    int padding = padding_size(w);
    image->bmp_info_header.biSizeImage = h * w * sizeof(pixel) + h * padding * sizeof(char);
    image->bmp_header.bfSize = sizeof(bmp_header_t) + sizeof(bmp_info_header_t) 
                    + image->bmp_info_header.biSizeImage;
}

int load_bmp(bmp_file *image, FILE *f) {
    fread(&(image->bmp_header), sizeof(bmp_header_t), 1, f);
    fread(&(image->bmp_info_header), sizeof(bmp_info_header_t), 1, f);

    int h = (image->bmp_info_header).biHeight;
    int w = (image->bmp_info_header).biWidth;
    int padding = padding_size(w);

    if(make_array((const pixel***) &(image->data), w, h))
        return -1;

    char* zero_bytes = malloc(padding * sizeof(char));
    if(zero_bytes == NULL) {
        free(image->data);
        return -1;
    }

    for(int i = h - 1; i >= 0; i--) {
        fread(image->data[i], sizeof(pixel), w, f);
        fread(zero_bytes, sizeof(char), padding, f);
    }

    free(zero_bytes);
    return 0;
}

int crop(bmp_file image, bmp_file *new_image, int x, int y, int w, int h) {
    new_image->bmp_header = image.bmp_header;
    new_image->bmp_info_header = image.bmp_info_header;

    new_image->bmp_info_header.biWidth = w;
    new_image->bmp_info_header.biHeight = h;
    update_info(new_image, w, h);

    if(make_array((const pixel***) &(new_image->data), w, h)) {
        return -1;
    }

    for(int i = 0 ; i < h; i++)
        memcpy(new_image->data[i], image.data[y + i] + x, w * sizeof(pixel));

    return 0;
}

int rotate(bmp_file image, bmp_file *new_image) {
    new_image->bmp_header = image.bmp_header;
    new_image->bmp_info_header = image.bmp_info_header;

    int w = new_image->bmp_info_header.biHeight;
    int h = new_image->bmp_info_header.biWidth;
    new_image->bmp_info_header.biWidth = w;
    new_image->bmp_info_header.biHeight = h;
    update_info(new_image, w, h);

    if(make_array((const pixel***) &(new_image->data), w, h))
        return -1;

    for(int i = 0 ; i < h; i++)
        for(int j = 0; j < w; j++)
            new_image->data[i][j] = image.data[w - j - 1][i];

    return 0;
}

void save_bmp(bmp_file image, FILE *f) { 
    const int max_padding_size = 4;

    fwrite(&(image.bmp_header), sizeof(bmp_header_t), 1, f);
    fwrite(&(image.bmp_info_header), sizeof(bmp_info_header_t), 1, f);

    int h = (image.bmp_info_header).biHeight;
    int w = (image.bmp_info_header).biWidth;
    int padding = padding_size(w);

    char *zero_bytes = calloc(max_padding_size, 1);
    for(int i = h - 1; i >= 0; i--) {
        fwrite(image.data[i], sizeof(pixel), w, f);
        fwrite(zero_bytes, sizeof(char), padding, f);
    }
    free(zero_bytes);
}
