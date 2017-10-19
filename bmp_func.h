#include <stdio.h>
#include <stdlib.h>

#ifndef BMP_FUNC_H
    #define BMP_FUNC_H

    void load_bmp(FILE* file, struct bmp_header* header, struct picture* image);

#endif
