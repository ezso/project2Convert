#include "image_edit.h"

#include <stdlib.h>

#include "structures.h"
#include "util.h"

void rotate_counterclockwise(image_t *img) {
    int w = img->w;
    int h = img->h;
    pixel_t *temp = malloc(sizeof(pixel_t) * w * h);
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            temp[(w - x - 1) * h + y] = img->img[y * w + x];
        }
    }
    free(img->img);
    img->img = temp;
    img->h = w;
    img->w = h;
}

void rotate_clockwise(image_t *img) {
    int w = img->w;
    int h = img->h;
    pixel_t *temp = malloc(sizeof(pixel_t) * w * h);
    for (int y = 0; y < w; y++) {
        for (int x = 0; x < h; x++) {
            temp[y * h + x] = img->img[(h - 1 - x) * w + y];
        }
    }
    free(img->img);
    img->img = temp;
    img->h = w;
    img->w = h;
}

void mirror_horizontal(image_t *img) {
    int w = img->w;
    int h = img->h;
    pixel_t *temp = malloc(sizeof(pixel_t) * w * h);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            temp[i * w + (w - j - 1)] = img->img[i * w + j];
        }
    }
    free(img->img);
    img->img = temp;
}

void mirror_vertical(image_t *img) {
    int w = img->w;
    int h = img->h;
    pixel_t *temp = malloc(sizeof(pixel_t) * w * h);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            temp[(h - i - 1) * w + j] = img->img[i * w + j];
        }
    }
    free(img->img);
    img->img = temp;
}

void resize(image_t *img, int new_width, int new_height) {
    pixel_t *temp = malloc(sizeof(pixel_t) * new_width * new_height);

    if (new_height <= img->h && new_width <= img->w) {
        for (int i = 0; i < new_height; i++) {
            for (int j = 0; j < new_width; j++) {
                temp[i * new_width + j] = img->img[i * img->w + j];
            }
        }
    }
    else if (new_height > img->h && new_width > img->w) {
        for (int i = 0; i < img->h; i++) {
            for (int j = 0; j < img->w; j++) {
                temp[i * new_width + j] = img->img[i * img->w + j];
            }
        }
        for (int i = img->h; i < new_height; i++) {
            for (int j = img->w; j < new_width; j++) {
                temp[i * new_width + j].r = 0;
                temp[i * new_width + j].g = 0;
                temp[i * new_width + j].b = 0;
            }
        }
        for (int i = 0; i < new_height; i++) {
            for (int j = img->w; j < new_width; j++) {
                temp[i * new_width + j].r = 0;
                temp[i * new_width + j].g = 0;
                temp[i * new_width + j].b = 0;
            }
        }
        for (int i = img->h; i < new_height; i++) {
            for (int j = 0; j < new_width; j++) {
                temp[i * new_width + j].r = 0;
                temp[i * new_width + j].g = 0;
                temp[i * new_width + j].b = 0;
            }
        }
    }
    else if (new_height <= img->h && new_width > img->w) {
        for (int i = 0; i < new_height; i++) {
            for (int j = 0; j < img->w; j++) {
                temp[i * new_width + j] = img->img[i * img->w + j];
            }
        }
        for (int i = 0; i < new_height; i++) {
            for (int j = img->w; j < new_width; j++) {
                temp[i * new_width + j].r = 0;
                temp[i * new_width + j].g = 0;
                temp[i * new_width + j].b = 0;
            }
        }
    }
    else {
        for (int i = 0; i < img->h; i++) {
            for (int j = 0; j < new_width; j++) {
                temp[i * new_width + j] = img->img[i * img->w + j];
            }
        }
        for (int i = img->h; i < new_height; i++) {
            for (int j = 0; j < new_width; j++) {
                temp[i * new_width + j].r = 0;
                temp[i * new_width + j].g = 0;
                temp[i * new_width + j].b = 0;
            }
        }
    }
    free(img->img);
    img->img = temp;
    img->h = new_height;
    img->w = new_width;
}
