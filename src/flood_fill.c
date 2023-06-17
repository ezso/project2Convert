#include "flood_fill.h"

#include <stdbool.h>
#include <stdlib.h>

#include "structures.h"
#include "util.h"

struct Queue {
    int x;
    int y;
    struct Queue* next;
};
typedef struct Queue Q;

Q* new_node(int x, int y){
    Q* node = malloc(sizeof(Q));
    node->x = x;
    node->y = y;
    return node;
}

void push(Q** root, int x, int y) {
    Q* node = new_node(x, y);
    node->next = *root;
    *root = node;
}

void pop(Q** root, int* x, int* y) {
    Q* temp = *root;
    *root = (*root)->next;
    *x = temp->x;
    *y = temp->y;
    free(temp);
}

void flood(image_t *img, int x, int y, pixel_t *target_color) {
    if (x < 0 || y < 0 || x >= img->w || y >= img->h) return;
    if (target_color->r == img->img[y * img->w + x].r && target_color->g == img->img[y * img->w + x].g && target_color->b == img->img[y * img->w + x].b) 
        return;
    
    pixel_t source_color;
    source_color.r = img->img[y * img->w + x].r;
    source_color.g = img->img[y * img->w + x].g;
    source_color.b = img->img[y * img->w + x].b;
    Q* root = NULL;
    push(&root, x, y);
    while(root) {
        pop(&root, &x, &y);
        if (x < 0 || y < 0 || x >= img->w || y >= img->h) 
            continue;
        if (target_color->r == img->img[y * img->w + x].r && target_color->g == img->img[y * img->w + x].g && target_color->b == img->img[y * img->w + x].b)
            continue;
        if (source_color.r != img->img[y * img->w + x].r || source_color.g != img->img[y * img->w + x].g || source_color.b != img->img[y * img->w + x].b) 
            continue;
        img->img[y * img->w + x] = *target_color;
        push(&root, x + 1, y);
        push(&root, x - 1, y);
        push(&root, x, y + 1);
        push(&root, x, y - 1);
    }
}
