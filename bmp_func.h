#include <stdio.h>
#include <stdlib.h>

#ifndef BMP_FUNC_H
    #define BMP_FUNC_H

    typedef enum {
        READ_OK = 0,
        READ_INVALID_SIGNATURE,
        READ_INVALID_BITS,
        READ_INVALID_HEADER
    } read_error_code;

    read_error_code read_header(FILE* fin, bmp_header *header_info);

#endif
