#include "assert.h"
#include "string.h"
#include "stdlib.h"
#include "bmp.h"

void free_memory(bmp_file *image) {
	free(image->data);
}

int main(int argc, char** argv) {
	if(argc != 8)
		return -1;
	if(strcmp(argv[1], "crop-rotate"))
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
