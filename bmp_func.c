#include <math.h>
#include "bmp_struct.h"
#include "bmp_func.h"
#define PI 3.14159265
#define XX 1
#define YY 2

void load_bmp(FILE* file, struct bmp_header* header, struct picture* image) {
    uint32_t i;
    int padding = (4 - (header->biWidth * sizeof(struct pixel)) % 4) % 4;
    /* fetch header */
    fread(header, sizeof(struct bmp_header), 1, file);
    if (header->biSizeImage == 0) header->biSizeImage = header->bfileSize;
    image->width = header->biWidth;
    image->height = header->biHeight;
    image->data = (struct pixel*)malloc((header->biWidth* sizeof(struct pixel) + padding) * header->biHeight);
    /* fetch body */
    for (i = 0; i < image->height; ++i) {
        fread(image->data + i*image->width, sizeof(struct pixel), image->width, file);
		fseek(file, padding, SEEK_CUR);
        /*printf("[ ");
        for(j = 0; j < image->width; ++j) {
            printf("%d%d%d ", (image->data+i)->b, (image->data+i)->g, (image->data+i)->r);
        }
        printf(" ]\n");*/
    }
}

struct picture* rotate_left(struct picture const * source) {
    uint32_t i, j;
    struct picture* new_img = (struct picture*)malloc(sizeof(struct picture));
	new_img->width = source->height;
	new_img->height = source->width;
	new_img->data = (struct pixel*)malloc(sizeof(struct pixel)*new_img->width*new_img->height);
	for (i = 0; i<new_img->height; i++) {
		for (j = 0; j<new_img->width; j++) {
			*(new_img->data + i*new_img->width + j) = *(source->data + (new_img->width - j - 1)*new_img->height + i);
		}
	}
	return new_img;
}
struct picture* rotate_right(struct picture const * source) {
	uint32_t i, j;
    struct picture* new_img = (struct picture*)malloc(sizeof(struct picture));
	new_img->width = source->height;
	new_img->height = source->width;
	new_img->data = (struct pixel*)malloc(sizeof(struct pixel)*new_img->width*new_img->height);
	for (i = 0; i<new_img->height; i++) {
		for (j = 0; j<new_img->width; j++) {
			*(new_img->data + i*new_img->width + j) = *(source->data + j*source->width + (new_img->width-1-i));
		}
	}
	return new_img;
}

struct bmp_header* rotate_header(struct bmp_header const * old_header) {
	uint32_t new_width = old_header->biHeight;
	uint32_t new_height = old_header->biWidth;
	const int padding = (4 - (new_width * sizeof(struct pixel)) % 4) % 4;
	uint32_t new_fileSize = sizeof(struct bmp_header) + (new_width + padding)*new_height;
	uint32_t new_sizeImage = (new_width + padding)*new_height;
	struct bmp_header* new_header = (struct bmp_header*)malloc(sizeof(struct bmp_header));
	new_header->biHeight = new_height;
	new_header->biWidth = new_width;
	new_header->bfileSize = new_fileSize;
	new_header->biSizeImage = new_sizeImage;
	return new_header;
}

void save_bmp(FILE* file, struct bmp_header* header, struct picture* image) {
    uint32_t i;
    int padding = (4 - (header->biWidth * sizeof(struct pixel)) % 4) % 4;
    struct bmp_header new_header = { 0x4D42, -1, 0, 54, 40, -1, -1, 1, 24, 0, -1, 0, 0, 0, 0 };
    new_header.bfileSize = sizeof(struct bmp_header) + (image->width * sizeof(struct pixel) + padding)*image->height;
    new_header.biWidth = image->width;
    new_header.biHeight = image->height;
    new_header.biSizeImage = (image->width* sizeof(struct pixel)  + padding)*image->height;
    fwrite(&new_header, sizeof(struct bmp_header), 1, file);
    for (i = 0; i < image->height; ++i) {
        fwrite(image->data + i*image->width, sizeof(struct pixel), image->width, file);
		fseek(file, padding, SEEK_CUR);
    }
}

/*struct bmp_header* set_header(struct bmp_header* header, int width, int height) {
    int padding = (4 - (header->biWidth * sizeof(struct pixel)) % 4) % 4;
    struct bmp_header new_header = { 0x4D42, -1, 0, 54, 40, -1, -1, 1, 24, 0, -1, 0, 0, 0, 0 };
    new_header.bfileSize = sizeof(struct bmp_header) + (width * sizeof(struct pixel) + padding)*height;
    new_header.biWidth = width;
    new_header.biHeight = height;
    new_header.biSizeImage = (width* sizeof(struct pixel)  + padding)*height;
}*/

void set_cube(struct picture* cube_config, double points[][3], int connections[][2], int count_of_points) {
    uint32_t i, j;
    int k;
    int x_start, y_start;
    int step_x = 30;
    int step_y = 30;
    cube_config->width = 100;
    cube_config->height = 100;
    cube_config->data = (struct pixel*)malloc((cube_config->width* sizeof(struct pixel) + 0) * cube_config->height);
    x_start = step_x;
    y_start = step_y;
    printf("X and Y Start: %d %d \n", x_start, y_start);
    print_cube(points, count_of_points);
    rotate_cube(60, points, count_of_points);
    render_cube_to_2d(points, count_of_points);
    print_cube(points, count_of_points);
    for (i = 0; i < cube_config->height; ++i) {
        for(j = 0; j < cube_config->width; ++j) {
            (cube_config->data + i*cube_config->width + j)->b = 255;
            (cube_config->data + i*cube_config->width + j)->g = 255;
            (cube_config->data + i*cube_config->width + j)->r = 255;
        }
    }
    for (k = 0; k < count_of_points; ++k) {
        int x = (int)(points[k][XX]*step_x);
        int y = (int)(points[k][YY]*step_y);
        printf("%d. [ %d %d ]\n", k+1, (x_start+x), (y_start+y));
        (cube_config->data + (y_start+y)*cube_config->width + (x_start+x))->b = 0;
        (cube_config->data + (y_start+y)*cube_config->width + (x_start+x))->g = 127;
        (cube_config->data + (y_start+y)*cube_config->width + (x_start+x))->r = 255;
    }
    for (k = 0; k < 12; ++k) {
        int x1 = (int)(points[connections[k][0]][XX]*step_x);
        int y1 = (int)(points[connections[k][0]][YY]*step_y);
        int x2 = (int)(points[connections[k][1]][XX]*step_x);
        int y2 = (int)(points[connections[k][1]][YY]*step_y);
        int s_x = ((x1 < x2) ? 1 : -1);
        int s_y = ((y1 < y2) ? 1 : -1);
        int z, t;
        int x_whole = (x2-x1)*s_x;
        int y_whole = (y2-y1)*s_y;
        bool x_lower = (x_whole < y_whole ? true : false);
        int diff;
        if(x_whole == 0 || y_whole == 0) {
            diff = 1;
        } else {
            diff = (int)(x_lower ? y_whole/x_whole : x_whole/y_whole);
        }
        printf("\n[%d, %d] -> [%d, %d]\n", x1, y1, x2, y2);
        for (z = 0; z < (x_lower ? x_whole : y_whole); ++z) {
            x1 += s_x;
            y1 += s_y;
            printf("[ %d %d ] 1 phase\n", (x_start+x1), (y_start+y1));
            (cube_config->data + (y_start+y1)*cube_config->width + (x_start+x1))->b = 0;
            (cube_config->data + (y_start+y1)*cube_config->width + (x_start+x1))->g = 127;
            (cube_config->data + (y_start+y1)*cube_config->width + (x_start+x1))->r = 255;
            for(t = 0; t < diff-1; ++t) {
                if (x_lower) {
                    y1 += s_y;
                } else {
                    x1 += s_x;
                }
                printf("[ %d %d ] 2 phase\n", (x_start+x1), (y_start+y1));
                (cube_config->data + (y_start+y1)*cube_config->width + (x_start+x1))->b = 0;
                (cube_config->data + (y_start+y1)*cube_config->width + (x_start+x1))->g = 127;
                (cube_config->data + (y_start+y1)*cube_config->width + (x_start+x1))->r = 255;
            }
        }
        while (x1 != x2) {
            x1 += s_x;
            printf("[ %d %d ] 3 phase\n", (x_start+x1), (y_start+y1));
            (cube_config->data + (y_start+y1)*cube_config->width + (x_start+x1))->b = 0;
            (cube_config->data + (y_start+y1)*cube_config->width + (x_start+x1))->g = 127;
            (cube_config->data + (y_start+y1)*cube_config->width + (x_start+x1))->r = 255;

        }
        while (y1 != y2) {
            y1 += s_y;
            printf("[ %d %d ] 4 phase\n", (x_start+x1), (y_start+y1));
            (cube_config->data + (y_start+y1)*cube_config->width + (x_start+x1))->b = 0;
            (cube_config->data + (y_start+y1)*cube_config->width + (x_start+x1))->g = 127;
            (cube_config->data + (y_start+y1)*cube_config->width + (x_start+x1))->r = 255;
        }
    }
}

void print_cube(double points[][3], int count_of_points) {
    int i;
    for(i = 0; i < count_of_points; ++i) {
        printf("%d. [ %f %f %f ]\n", i+1, points[i][0], points[i][1], points[i][2]);
    }
    printf("\n");
}

void rotate_cube(int angle, double points[][3], int count_of_points) {
    int i;
    double sina, cosa, val, x_temp, y_temp;
    val = PI / 180;
    sina = sin(angle*val);
    cosa = cos(angle*val);
    for(i = 0; i < count_of_points; ++i) {
        x_temp = points[i][0];
        y_temp = points[i][1];
        points[i][0] = x_temp * cosa + y_temp * sina;
        points[i][1] = x_temp * sina + y_temp * cosa;
    }
}

void render_cube_to_2d(double points[][3], int count_of_points) {
    int i;
    printf("%f\n", points[1][0]/2);
    for(i = 0; i < count_of_points; ++i) {
        points[i][2] += points[i][0]/2;
        points[i][1] += points[i][0]/2;
        points[i][0] = 0;
    }
}
