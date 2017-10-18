#include <stdio.h>
#include <stdlib.h>
#include "bmp_struct.h"
#include "readwrite.h"

void main() {
    FILE *pic = fopen("./images/picture.bmp", "r+");
    FILE *modified_pic = fopen("./images/rotated_picture.bmp", "r+");
    if (pic != NULL) {
        struct picture *image = malloc(sizeof(struct picture));
    } else {
        printf("Picture does not exist!");
    }
}
