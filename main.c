#include <stdio.h>
#include <stdlib.h>
#include "bmp_struct.h"
#include "bmp_func.h"

void main() {
    FILE *pic_file = fopen("./images/p.bmp", "rb");
    struct bmp_header *pic_header = malloc(sizeof(struct bmp_header));
    struct picture *pic_config = malloc(sizeof(struct picture));
    load_bmp(pic_file, pic_header, pic_config);
    fclose(pic_file);
    pic_file = fopen("./images/rp.bmp", "wb");
}
