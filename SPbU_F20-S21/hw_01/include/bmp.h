#ifndef BMP_FORMAT_
#define BMP_FORMAT_

#include "stdio.h"
#include "stdint.h"

#pragma pack(push,1)

typedef struct BITMAPFILEHEADER {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved22;
    uint32_t bfOffBits;

} bmp_header_t;

typedef struct BITMAPINFOHEADER {
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} bmp_info_header_t;

typedef struct Pixel {
    char R, G, B;
} pixel;

typedef struct BITMAPFILE {
    bmp_header_t bmp_header;
    bmp_info_header_t bmp_info_header;
    pixel **data;
} bmp_file;

#pragma pack(pop)

int load_bmp(bmp_file *image, FILE *f);
int crop(bmp_file image, bmp_file *new_image, int x, int y, int w, int h);
int rotate(bmp_file image, bmp_file *new_image);
void save_bmp(bmp_file image, FILE *f);

#endif

