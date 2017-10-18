#include <stdio.h>
#include <stdlib.h>
#include "bmp_struct.h"
#include "bmp_func.h"

#define PI 3.14159265

read_error_code read_header(FILE* fin, bmp_header *header_info){
    read_error_code result;
    result = fread(header_info, sizeof(bmp_header), 1, fin) == 1 ? READ_OK : READ_INVALID_HEADER;
    return result;
}

read_error_code read_body(struct picture *image, FILE* file){
    int string_trash, trash_len;
    long array_length = sizeof(struct pixel)*image->width;
    trash_len = (4-(array_length % 4))%4;
    image->data = malloc(array_length*image->height);
    for(int i = 0; i < image->height; i++){
        if(fread(image->data+(image->width * i), array_length, 1, file) != 1) return READ_INVALID_SIGNATURE;
        fread(&string_trash, trash_len, 1, file);
    }
    return READ_OK;
}
