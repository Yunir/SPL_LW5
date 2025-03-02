#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#ifndef BMP_FUNC_H
    #define BMP_FUNC_H

    void load_bmp(FILE* file, struct bmp_header* header, struct picture* image);
    void save_bmp(FILE* file, struct bmp_header* header, struct picture* image);
    struct picture* rotate_right(struct picture const * source);
    struct picture* rotate_left(struct picture const * source);
    struct bmp_header* rotate_header(struct bmp_header const * old_header);
    struct bmp_header* set_header(struct bmp_header* header, int width, int height);
    void set_cube(struct picture*, double[][3], int[][2], int);
    void print_cube(double[][3], int);
    void rotate_cube(int, double [][3], int);
    void render_cube_to_2d(double [][3], int);
#endif
