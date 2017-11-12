#include <stdio.h>
#include <stdlib.h>
#include "bmp_struct.h"
#include "bmp_func.h"
#define count_of_points 8

int main(int argc, char** argv) {
    double points[count_of_points][3] = {{0,0,0}, {1,0,0}, {0,1,0}, {1,1,0}, {0,0,1}, {1,0,1}, {0,1,1}, {1,1,1}};
    int connections[12][2] = {{0, 1}, {0, 2}, {0, 4}, {1, 3}, {1, 5}, {2, 3}, {2, 6}, {3, 7}, {4, 5}, {4, 6}, {5, 7}, {6, 7}};
    FILE* pic_file;
    struct bmp_header* pic_header;
    struct picture* pic_config;
    struct picture* cube_config;
    if (argc > 1) {
        pic_file = fopen(argv[1], "rb");
    } else {
        pic_file = fopen("./images/p.bmp", "rb");
    }
    pic_header = malloc(sizeof(struct bmp_header));
    pic_config = malloc(sizeof(struct picture));
    cube_config = malloc(sizeof(struct picture));
    load_bmp(pic_file, pic_header, pic_config);
    fclose(pic_file);
    pic_file = fopen("./images/rp.bmp", "wb");
    pic_header = rotate_header(pic_header);
    pic_config = rotate_right(pic_config);
    save_bmp(pic_file, pic_header, pic_config);
    fclose(pic_file);
    pic_file = fopen("./images/cube.bmp", "wb");
    set_cube(cube_config, points, connections, count_of_points);
    save_bmp(pic_file, pic_header, cube_config);
    fclose(pic_file);
    return 0;
}
