#include <stdio.h>
#include <stdlib.h>
#include "bmp_struct.h"
#include "bmp_func.h"

void load_bmp(FILE* file, struct bmp_header* header, struct picture* image) {
    //fetch header
    fread(header, sizeof(struct bmp_header), 1, file);
    if (header->biSizeImage == 0) header->biSizeImage = header->bfileSize;
    image->width = header->biWidth;
    image->height = header->biHeight;
    int padding = (4 - (header->biWidth * sizeof(struct pixel)) % 4) % 4;
    image->data = (struct pixel*)malloc((header->biWidth* sizeof(struct pixel) + padding) * header->biHeight);
    //fetch body
    for (int i = 0; i < image->height; ++i) {
        fread(image->data + i*image->width, sizeof(struct pixel), image->width, file);
		fseek(file, padding, SEEK_CUR);
    }
}
