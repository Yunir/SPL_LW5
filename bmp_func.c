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
