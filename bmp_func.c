#include <stdio.h>
#include <stdlib.h>
#include "bmp_struct.h"
#include "bmp_func.h"

void load_bmp(FILE* file, struct bmp_header* header, struct picture* image) {
    uint32_t i;
    int padding = (4 - (header->biWidth * sizeof(struct pixel)) % 4) % 4;
    /* fetch header */
    fread(header, sizeof(struct bmp_header), 1, file);
    if (header->biSizeImage == 0) header->biSizeImage = header->bfileSize;
    image->width = header->biWidth;
    image->height = header->biHeight;
    image->data = (struct pixel*)malloc((header->biWidth* sizeof(struct pixel) + padding) * header->biHeight);
    /* fetch body */
    for (i = 0; i < image->height; ++i) {
        fread(image->data + i*image->width, sizeof(struct pixel), image->width, file);
		fseek(file, padding, SEEK_CUR);
    }
}

struct picture* rotate_left(struct picture const * source) {
    uint32_t i, j;
    struct picture* new_img = (struct picture*)malloc(sizeof(struct picture));
	new_img->width = source->height;
	new_img->height = source->width;
	new_img->data = (struct pixel*)malloc(sizeof(struct pixel)*new_img->width*new_img->height);
	for (i = 0; i<new_img->height; i++) {
		for (j = 0; j<new_img->width; j++) {
			*(new_img->data + i*new_img->width + j) = *(source->data + (new_img->width - j - 1)*new_img->height + i);
		}
	}
	return new_img;
}
struct picture* rotate_right(struct picture const * source) {
	uint32_t i, j;
    struct picture* new_img = (struct picture*)malloc(sizeof(struct picture));
	new_img->width = source->height;
	new_img->height = source->width;
	new_img->data = (struct pixel*)malloc(sizeof(struct pixel)*new_img->width*new_img->height);
	for (i = 0; i<new_img->height; i++) {
		for (j = 0; j<new_img->width; j++) {
			*(new_img->data + i*new_img->width + j) = *(source->data + j*source->width + (new_img->width-1-i));
		}
	}
	return new_img;
}

struct bmp_header* rotate_header(struct bmp_header const * old_header) {
	uint32_t new_width = old_header->biHeight;
	uint32_t new_height = old_header->biWidth;
	const int padding = (4 - (new_width * sizeof(struct pixel)) % 4) % 4;
	uint32_t new_fileSize = sizeof(struct bmp_header) + (new_width + padding)*new_height;
	uint32_t new_sizeImage = (new_width + padding)*new_height;
	struct bmp_header* new_header = (struct bmp_header*)malloc(sizeof(struct bmp_header));
	new_header->biHeight = new_height;
	new_header->biWidth = new_width;
	new_header->bfileSize = new_fileSize;
	new_header->biSizeImage = new_sizeImage;
	return new_header;
}

void save_bmp(FILE* file, struct bmp_header* header, struct picture* image) {
    uint32_t i;
    int padding = (4 - (header->biWidth * sizeof(struct pixel)) % 4) % 4;
    struct bmp_header new_header = { 0x4D42, -1, 0, 54, 40, -1, -1, 1, 24, 0, -1, 0, 0, 0, 0 };
    new_header.bfileSize = sizeof(struct bmp_header) + (image->width * sizeof(struct pixel) + padding)*image->height;
    new_header.biWidth = image->width;
    new_header.biHeight = image->height;
    new_header.biSizeImage = (image->width* sizeof(struct pixel)  + padding)*image->height;
    fwrite(&new_header, sizeof(struct bmp_header), 1, file);
    for (i = 0; i < image->height; ++i) {
        fwrite(image->data + i*image->width, sizeof(struct pixel), image->width, file);
		fseek(file, padding, SEEK_CUR);
    }
}

/*struct bmp_header* set_header(int width, int height) {
    struct bmp_header new_header = { 0x4D42, -1, 0, 54, 40, -1, -1, 1, 24, 0, -1, 0, 0, 0, 0 };
    new_header.bfileSize = sizeof(struct bmp_header) + (width * sizeof(struct pixel) + padding)*height;
    new_header.biWidth = width;
    new_header.biHeight = height;
    new_header.biSizeImage = (width* sizeof(struct pixel)  + padding)*height;
}*/

void set_cube(struct picture* cube_config, int points[][3], int connections[][2], int count_of_points) {
    int i, x_start, y_start;
    int step_x = -10;
    int step_y = 10;
    cube_config->width = 100;
    cube_config->height = 100;
    x_start = cube_config->width + step_x;
    y_start = cube_config->height + step_y;
    printf("%d %d %d\n", x_start, y_start, connections[0][0]);
    for(i = 0; i < count_of_points; ++i) {
        printf("%d ", points[i][0]);
    }
}
