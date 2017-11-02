#include <stdio.h>
#include <stdlib.h>
#include "bmp_struct.h"
#include "bmp_func.h"

int main(int argc, char** argv) {
    FILE* pic_file;
    struct bmp_header* pic_header;
    struct picture* pic_config;
    if (argc > 1) {
        pic_file = fopen(argv[1], "rb");
    } else {
        pic_file = fopen("./images/p.bmp", "rb");
    }
    pic_header = malloc(sizeof(struct bmp_header));
    pic_config = malloc(sizeof(struct picture));
    load_bmp(pic_file, pic_header, pic_config);
    fclose(pic_file);
    pic_file = fopen("./images/rp.bmp", "wb");
    pic_header = rotate_header(pic_header);
    pic_config = rotate_right(pic_config);
    save_bmp(pic_file, pic_header, pic_config);
    fclose(pic_file);
    something
    return 0;
}
