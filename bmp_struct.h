#include <stdint.h>

#ifndef BMP_STRUCT_H
    #define BMP_STRUCT_H

    struct pixel {
        unsigned char b, g, r;
    };

    struct picture {
        uint32_t width;
        uint32_t height;
        struct pixel *data;
    };

    typedef struct __attribute__((packed)) {
        uint16_t bfType;
        uint32_t bfileSize;
        uint32_t bfReserved;
        uint32_t bOffBits;
        uint32_t biSize;
        uint32_t biWidth;
        uint32_t biHeight;
        uint16_t biPlanes;
        uint16_t biBitCount;
        uint32_t biCompression;
        uint32_t biSizeImage;
        uint32_t biXPelsPerMeter;
        uint32_t biYPelsPerMeter;
        uint32_t biClrUsed;
        uint32_t biClrImportant;
    } bmp_header;

#endif
