#include <stdio.h>
#include <stdlib.h>
#include "bmp_struct.h"
#include "bmp_func.h"

void error_check(read_error_code work_result){
    if(work_result != READ_OK) exit(1);
}

void main() {
    bmp_header pic_header;
    FILE *pic = fopen("./images/picture.bmp", "r+");
    FILE *modified_pic = fopen("./images/rotated_picture.bmp", "r+");
    error_check(read_header(pic, &pic_header) != 0);
    struct picture *image = malloc(sizeof(struct picture));
    image->width = pic_header.biWidth;
    image->height = pic_header.biHeight;
    error_check(read_body(image, pic) != 0);
    fclose(pic);
}
