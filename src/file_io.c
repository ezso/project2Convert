#include "file_io.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "structures.h"
#include "util.h"

int image_read(image_t *img, FILE *fin) {
    if(fin != NULL) {
        char format[2];
        int max_value = 0;

        if(fscanf(fin, "%c%c", format, format + 1) != 2) return -1;
        if (format[0] != 'P' || format[1] != '3')   return -1;

        if(fscanf(fin, "%d %d", &img->w, &img->h) != 2) return -1;
        if(fscanf(fin, "%d", &max_value) != 1) return -1;

        if (img->h < 1 || img->w < 1)   return -1;

        if (max_value != 255)   return -1;
        int w = img->w;
        img->img = malloc(sizeof(pixel_t) * img->h * img->w);
        for(int i = 0; i < img->h; i++) {
            for(int j = 0; j < img->w; j++) {
                if(fscanf(fin, "%d %d %d", &img->img[i*w+j].r, &img->img[i*w+j].g, &img->img[i*w+j].b) != 3) return -1;
            }
        }
        return 0;
    } else return -1;
}

void image_write(const image_t *img, FILE *fout) {
    if (img != NULL) {
        fprintf(fout, "P3\n");
        fprintf(fout, "%d %d\n", img->w, img->h);
        fprintf(fout, "255\n");
        int w = img->w;
        for(int i = 0; i < img->h; i++) {
            for(int j = 0; j < img->w; j++) {
                fprintf(fout, "%d %d %d ", img->img[i*w+j].r, img->img[i*w+j].g, img->img[i*w+j].b);
            }
            fprintf(fout, "\n");
        }

    } else printf("no data to write");
}

void image_free(image_t *img) {
    if (img->img != NULL) {
        free(img->img);
    }
    img->w = img->h = 0;
    img->img = NULL;
}
