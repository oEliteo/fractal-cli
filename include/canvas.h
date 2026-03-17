#ifndef CANVAS_H
#define CANVAS_H
#include <string.h>

typedef struct Canvas {
  size_t width;
  size_t height;
  char *data;
} canvas_t;

canvas_t *canvas_create(size_t width, size_t height);

void canvas_destroy(canvas_t *c);

void canvas_clear(canvas_t *c);

void canvas_set_pixel(canvas_t *c, size_t x, size_t y, char ch);

void canvas_draw(const canvas_t *c);

#endif
